/*
* can_driver.c
*
* Created: 2020/07/02 14:57:03
*  Author: Kolijn
*/

#include "ccd_can_driver.h"

#include <assert.h>
#include <string.h>

#include "asf.h"

void ccd_can_Init(ccd_can_t * pHandle, Mcan * can_device)
{
    pmc_disable_pck(PMC_PCK_5);
    pmc_pck_set_source(PMC_PCK_5, PMC_PCK_CSS_UPLL_CLK);
    pmc_pck_set_prescaler(PMC_PCK_5, PMC_PCK_PRES(5));
    pmc_enable_pck(PMC_PCK_5);
    
    struct mcan_config sCanConfig;
    mcan_get_config_defaults(&sCanConfig);
    sCanConfig.automatic_retransmission = false;
    sCanConfig.nonmatching_frames_action_extended = MCAN_NONMATCHING_FRAMES_REJECT;
    mcan_init(&pHandle->can_module, can_device, &sCanConfig);
    
    mcan_set_baudrate(can_device, pHandle->baudrate);
    
    // Will set CCR.INIT bit to 0, so module runs
    mcan_start(&pHandle->can_module);
    
    if (can_device == MCAN0)
    {
        irq_register_handler(MCAN0_INT0_IRQn, 1);
        NVIC_SetPriority(MCAN0_INT0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY >> (8 - __NVIC_PRIO_BITS));
    }
    else if (can_device == MCAN1)
    {
        irq_register_handler(MCAN1_INT0_IRQn, 1);
        NVIC_SetPriority(MCAN1_INT0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY >> (8 - __NVIC_PRIO_BITS));
    }
    mcan_enable_interrupt(&pHandle->can_module, MCAN_RX_BUFFER_NEW_MESSAGE | MCAN_RX_FIFO_0_NEW_MESSAGE | MCAN_RX_FIFO_1_NEW_MESSAGE | MCAN_FORMAT_ERROR | MCAN_ACKNOWLEDGE_ERROR | MCAN_BUS_OFF);
    
    // This buffer was too small once, got incremented from 32 to 64.
    pHandle->rx_buffer = xMessageBufferCreate(sizeof(struct mcan_rx_element_fifo_0) * 64);
}

void ccd_can_SetAddress(void * vHandle, uint32_t filter, uint32_t mask)
{
    ccd_can_t * pHandle = (ccd_can_t *) vHandle;
    
    pHandle->gse_address = filter;
    pHandle->gse_address_mask = mask;
    
    struct mcan_extended_message_filter_element et_filter;
    mcan_get_extended_message_filter_element_default(&et_filter);
    
    // TODO: [ADRIAAN] FIXME - accepting all CAN messages for CSP testing
    //et_filter.F0.reg = MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFID1(filter) | MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC(MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_STF0M_Val);
    //et_filter.F1.reg = MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFID2(mask) | MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_CLASSIC;
    et_filter.F0.bit.EFID1 = 0;
    et_filter.F0.bit.EFEC = MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_STF0M_Val;
    et_filter.F1.bit.EFID2 = 0x1FFFFFFF;
    et_filter.F1.bit.EFT = MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_RANGE;

    for (uint8_t i = 0; i < 16; i++)
    {
        mcan_set_rx_extended_filter(&pHandle->can_module, &et_filter, i);
    }
}

/*
Enables or disable retries in the CAN module.
This is a hardware feature of the CAN module. If enabled it will automatically
resend any messages that it did not detect on its RX line. it does sometimes cause
crashes because the CAN module keeps resending a message.

When this is ported to FreeRTOS there should also be a lock on the CAN module to make
sure we don't change it while transmitting a message.
*/
void ccd_can_SetRetries(void * vHandle, bool enabled)
{
    ccd_can_t * pHandle = (ccd_can_t *) vHandle;
    
    mcan_stop(&pHandle->can_module);
    
    // Allow us to make change to registers
    pHandle->can_module.hw->MCAN_CCCR |= MCAN_CCCR_CCE;
    while (!(pHandle->can_module.hw->MCAN_CCCR & MCAN_CCCR_CCE));
    
    // DAR 0 - Automatic retransmission enabled
    // DAR 1 - Automatic retransmission disabled
    if (enabled)
    {
        pHandle->can_module.hw->MCAN_CCCR &= ~MCAN_CCCR_DAR;
    }
    else
    {
        pHandle->can_module.hw->MCAN_CCCR |= MCAN_CCCR_DAR;
    }
    
    
    pHandle->can_module.hw->MCAN_CCCR &= ~MCAN_CCCR_CCE;
    while (pHandle->can_module.hw->MCAN_CCCR & MCAN_CCCR_CCE);

    mcan_start(&pHandle->can_module);
}

bool ccd_can_SetBaudRate(void * vHandle, uint32_t baud)
{
    // There are very specific accepted values for the baud rate.
    if (baud != 2000000 && baud != 1000000 && baud != 500000)
    {
        return false;
    }
    
    ccd_can_t * pHandle = (ccd_can_t *) vHandle;
    pHandle->baudrate = baud;
    
    mcan_stop(&pHandle->can_module);
    
    pHandle->can_module.hw->MCAN_CCCR |= MCAN_CCCR_CCE;
    while (!(pHandle->can_module.hw->MCAN_CCCR & MCAN_CCCR_CCE));
    
    mcan_set_baudrate(pHandle->can_module.hw, pHandle->baudrate);
    
    pHandle->can_module.hw->MCAN_CCCR &= ~MCAN_CCCR_CCE;
    while (pHandle->can_module.hw->MCAN_CCCR & MCAN_CCCR_CCE);
    
    mcan_start(&pHandle->can_module);
    
    return true;
}

void ccd_can_Send_message(void * vHandle, uint32_t header, uint8_t * data, size_t len)
{
    configASSERT(vHandle != NULL);
    configASSERT(len <= 8);
    
    ccd_can_t * pHandle = (ccd_can_t *) vHandle;
    
    // Construct a message
    struct mcan_tx_element tx_element;
    mcan_get_tx_buffer_element_defaults(&tx_element);
    tx_element.T0.reg = MCAN_TX_ELEMENT_T0_EXTENDED_ID(header) | MCAN_TX_ELEMENT_T0_XTD;
    tx_element.T1.bit.DLC = len;
    memcpy(tx_element.data, data, len);
    
    // Wait for the TX Buffer to be open
    // This doesn't need a big timeout - if the buffer isn't open very quickly, drop the message.
    
    /*
    TODO:
    There is some sort of bug here with CAN at different speeds. If there is something else on the
    bus at the same speed the CAN module will keep sending messages. If the CAN module and the
    radio speeds mismatch the CAN FIFO will get full, and it will refuse to send. I have no idea
    why, since it sends a few messages. There is no indicator in the status registers, and the
    bus lines are fine.
    */
    
    uint32_t timeout = 1000;
    
    while (((pHandle->can_module.hw->MCAN_TXFQS) & MCAN_TXFQS_TFQF)  > 1 && (--timeout > 0));
    
    configASSERT(timeout > 0);
    
    // TXFQi should indicate where to write to next, and what bit to set to send?
    // Datasheet 49.5.5.3 TX FIFO, page 1416
    uint32_t buffer_index = ((pHandle->can_module.hw->MCAN_TXFQS & MCAN_TXFQS_TFQPI_Msk) >> MCAN_TXFQS_TFQPI_Pos);
    
    // Code copied from the mcan_set_tx_buffer_element function
    mcan_set_tx_buffer_element(&pHandle->can_module, &tx_element, buffer_index);
    
    // TODO: Surely this should timeout and cause an error???
    while (mcan_tx_transfer_request(&pHandle->can_module, 1 << buffer_index) == ERR_BUSY);
}

bool ccd_can_Receive_message(void * vHandle, uint32_t * header, uint8_t * data, size_t * data_len)
{
    ccd_can_t * pHandle = (ccd_can_t*) vHandle;
    struct mcan_rx_element_fifo_0 rx_element;
    
    if (xMessageBufferReceive(pHandle->rx_buffer, &rx_element, sizeof(rx_element), pdMS_TO_TICKS(200)) <= 0)
    {
        return false;
    }
    
    *header = rx_element.R0.reg;
    *data_len = rx_element.R1.bit.DLC;
    memcpy(data, rx_element.data, *data_len);
    
    return true;
}

void ccd_can_ReceiveCallback(ccd_can_t* pHandle)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    volatile uint32_t status, i;
    status = mcan_read_interrupt_status(&pHandle->can_module);

    if (status & MCAN_RX_BUFFER_NEW_MESSAGE)
    {
        struct mcan_rx_element_buffer rx_element_buffer;

        for (i = 0; i < CONF_MCAN0_RX_BUFFER_NUM; i++)
        {
            if (mcan_rx_get_buffer_status(&pHandle->can_module, i))
            {
                mcan_rx_clear_buffer_status(&pHandle->can_module, i);
                mcan_get_rx_buffer_element(&pHandle->can_module, &rx_element_buffer, i);
            }
        }
        
        mcan_clear_interrupt_status(&pHandle->can_module, MCAN_RX_BUFFER_NEW_MESSAGE);
    }
    
    if (status & MCAN_RX_FIFO_0_NEW_MESSAGE)
    {
        struct mcan_rx_element_fifo_0 rx_element_fifo_0;
        
        uint32_t fifo_receive_index = (pHandle->can_module.hw->MCAN_RXF0S & MCAN_RXF0S_F0GI_Msk) >> MCAN_RXF0S_F0GI_Pos;
        mcan_get_rx_fifo_0_element(&pHandle->can_module, &rx_element_fifo_0, fifo_receive_index);
        
        xMessageBufferSendFromISR(pHandle->rx_buffer, &rx_element_fifo_0, sizeof(struct mcan_rx_element_fifo_0), &xHigherPriorityTaskWoken);
        
        mcan_rx_fifo_acknowledge(&pHandle->can_module, 0, fifo_receive_index);
        mcan_clear_interrupt_status(&pHandle->can_module, MCAN_RX_FIFO_0_NEW_MESSAGE);
    }

    if (status & MCAN_RX_FIFO_1_NEW_MESSAGE)
    {
        struct mcan_rx_element_fifo_1 rx_element_fifo_1;
        
        uint32_t fifo_receive_index = (pHandle->can_module.hw->MCAN_RXF1S & MCAN_RXF1S_F1GI_Msk) >> MCAN_RXF1S_F1GI_Pos;
        mcan_get_rx_fifo_1_element(&pHandle->can_module, &rx_element_fifo_1, fifo_receive_index);
        
        // TODO: Investigate if we are even sending any messages to this FIFO buffer. If so, why are we just discarding them?
        
        mcan_rx_fifo_acknowledge(&pHandle->can_module, 1, fifo_receive_index);
        mcan_clear_interrupt_status(&pHandle->can_module, MCAN_RX_FIFO_1_NEW_MESSAGE);
    }

    if (status & MCAN_BUS_OFF)
    {
        mcan_clear_interrupt_status(&pHandle->can_module, MCAN_BUS_OFF);
    }

    if (status & MCAN_ACKNOWLEDGE_ERROR)
    {
        mcan_clear_interrupt_status(&pHandle->can_module, MCAN_ACKNOWLEDGE_ERROR);
    }

    if (status & MCAN_FORMAT_ERROR)
    {
        mcan_clear_interrupt_status(&pHandle->can_module, MCAN_FORMAT_ERROR);
    }
    
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
