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

static void ccd_can_driver_SetAddress(ccd_can_t * pHandle, uint32_t filter, uint32_t mask);

void ccd_can_Init(ccd_can_t * pHandle, Mcan * can_device)
{
	
	struct mcan_config sCanConfig;
	mcan_get_config_defaults(&sCanConfig);
	sCanConfig.automatic_retransmission = true;
	sCanConfig.nonmatching_frames_action_extended = MCAN_NONMATCHING_FRAMES_REJECT;
	mcan_init(&pHandle->can_module, can_device, &sCanConfig);
	
	pmc_pck_set_prescaler(PMC_PCK_5, PMC_PCK_PRES(14));
	pmc_pck_set_source(PMC_PCK_5, PMC_PCK_CSS_PLLA_CLK);
	pmc_enable_pck(PMC_PCK_5);
	mcan_set_baudrate(can_device, pHandle->baudrate);
	
	// Will set CCR.INIT bit to 0, so module runs
	mcan_start(&pHandle->can_module);
	
	ccd_can_driver_SetAddress(pHandle, pHandle->gse_address, pHandle->gse_address_mask);
		
	if (can_device == MCAN0)
	{
		irq_register_handler(MCAN0_INT0_IRQn, 1);
		NVIC_SetPriority(MCAN0_INT0_IRQn, 4);
		mcan_enable_interrupt(&pHandle->can_module, MCAN_RX_BUFFER_NEW_MESSAGE | MCAN_RX_FIFO_0_NEW_MESSAGE | MCAN_RX_FIFO_1_NEW_MESSAGE | MCAN_FORMAT_ERROR | MCAN_ACKNOWLEDGE_ERROR | MCAN_BUS_OFF);
	}
	if (can_device == MCAN1)
	{
		irq_register_handler(MCAN1_INT0_IRQn, 1);
		NVIC_SetPriority(MCAN1_INT0_IRQn, 4);
		mcan_enable_interrupt(&pHandle->can_module, MCAN_RX_BUFFER_NEW_MESSAGE | MCAN_RX_FIFO_0_NEW_MESSAGE | MCAN_RX_FIFO_1_NEW_MESSAGE | MCAN_FORMAT_ERROR | MCAN_ACKNOWLEDGE_ERROR | MCAN_BUS_OFF);
	}
	
	pHandle->receiveMessageBuffer = xMessageBufferCreate(sizeof(struct mcan_rx_element_fifo_0) * 32);
}

void ccd_can_Send_message(void * vHandle, uint32_t header, uint8_t * data, size_t data_len)
{
	// Todo: Apply some sanity checks to the incoming data?
	if (data_len > 8){
		return;
	}
	
	ccd_can_t * pHandle = (ccd_can_t*) vHandle;
	
	 // Construct a message
    struct mcan_tx_element tx_element;
    mcan_get_tx_buffer_element_defaults(&tx_element);
	tx_element.T0.reg = MCAN_TX_ELEMENT_T0_EXTENDED_ID(header)| MCAN_TX_ELEMENT_T0_XTD;
    tx_element.T1.bit.DLC = data_len;
    memcpy(tx_element.data, data, data_len);
	
	// Wait for the TX Buffer to be open
	// Todo: THis might need a timeout?
	while (((pHandle->can_module.hw->MCAN_TXFQS) & MCAN_TXFQS_TFQF)  > 1);
	
	// tfqpi should indicate where to write to next, and what bit to set to send?
	// Datasheet 49.5.5.3 Tx FIFO, page 1416
	uint32_t buffer_index = ((pHandle->can_module.hw->MCAN_TXFQS & MCAN_TXFQS_TFQPI_Msk) >> MCAN_TXFQS_TFQPI_Pos);
	// Code copied from the mcan_set_tx_buffer_element function
     mcan_set_tx_buffer_element(&pHandle->can_module, &tx_element, buffer_index);
	
	 while (mcan_tx_transfer_request(&pHandle->can_module, 1 << buffer_index) == ERR_BUSY);
}

bool cc_can_Receive_message(void * vHandle, uint32_t * header, uint8_t ** data, size_t * data_len)
{
	ccd_can_t * pHandle = (ccd_can_t*) vHandle;
	struct mcan_rx_element_fifo_0 rx_element;
	
	if (xMessageBufferReceive(pHandle->receiveMessageBuffer, &rx_element, sizeof(rx_element), pdMS_TO_TICKS(200)) > 0)
	{
		*header = rx_element.R0.reg;
		*data_len = rx_element.R1.bit.DLC;
		memcpy(*data, rx_element.data, *data_len);
		return true;
	}	
	return false;
}



static void ccd_can_driver_SetAddress(ccd_can_t * pHandle, uint32_t filter, uint32_t mask){
	struct mcan_extended_message_filter_element et_filter;
	mcan_get_extended_message_filter_element_default(&et_filter);
	et_filter.F0.reg = MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFID1(filter) | MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC(1);
	et_filter.F1.reg = MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFID2(mask) | MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_CLASSIC;

	mcan_set_rx_extended_filter(&pHandle->can_module, &et_filter, 0);
	mcan_set_rx_extended_filter(&pHandle->can_module, &et_filter, 1);
}



// Called from interrupt
void ccd_can_driver_ReceiveCallback(ccd_can_t* pHandle)
{
	
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	// Static here is dodgy
	static uint32_t fifo_receive_index = 0;
	
	volatile uint32_t status, i;
	status = mcan_read_interrupt_status(&pHandle->can_module);

	if (status & MCAN_RX_BUFFER_NEW_MESSAGE ) {
		mcan_clear_interrupt_status(&pHandle->can_module, MCAN_RX_BUFFER_NEW_MESSAGE);
		static struct mcan_rx_element_buffer rx_element_buffer;

		for (i = 0; i < CONF_MCAN0_RX_BUFFER_NUM; i++) {
			if (mcan_rx_get_buffer_status(&pHandle->can_module, i)) {
				mcan_rx_clear_buffer_status(&pHandle->can_module, i);
				mcan_get_rx_buffer_element(&pHandle->can_module, &rx_element_buffer, i);
			}
		}
	}

	if (status & MCAN_RX_FIFO_0_NEW_MESSAGE) {
		
		// Rather than fifo_receive_index, this should probably be
		// (MCAN0->MCAN_RXF0S & ~MCAN_RXF0S_F0GI_Msk)
		// This is the read index pointer.
		// See 48.6.28 in the datasheet
		
		// Copy the message from the mcan buffer, to our own buffer.
		struct mcan_rx_element_fifo_0 rx_element;
		mcan_get_rx_fifo_0_element(&pHandle->can_module, &rx_element, fifo_receive_index);
		
		xMessageBufferSendFromISR(pHandle->receiveMessageBuffer, &rx_element, sizeof(struct mcan_rx_element_fifo_0), &xHigherPriorityTaskWoken);

		// Ack the message, Suspect this allows a new message to be received
		mcan_rx_fifo_acknowledge(&pHandle->can_module, 0, fifo_receive_index);

		fifo_receive_index++;
		if(fifo_receive_index == CONF_MCAN0_RX_FIFO_0_NUM)
		{
			fifo_receive_index = 0;
		}
	
		// Finally, clear interupt flag
		mcan_clear_interrupt_status(&pHandle->can_module, MCAN_RX_FIFO_0_NEW_MESSAGE);
	}

	if (status & MCAN_RX_FIFO_1_NEW_MESSAGE) {
		mcan_clear_interrupt_status(&pHandle->can_module, MCAN_RX_FIFO_1_NEW_MESSAGE);
		mcan_rx_fifo_acknowledge(&pHandle->can_module, 1, 0);

		struct mcan_rx_element_fifo_1 rx_element_fifo_1;

		mcan_get_rx_fifo_1_element(&pHandle->can_module, &rx_element_fifo_1, 0);
		mcan_rx_fifo_acknowledge(&pHandle->can_module, 0, 0);
	}

	if (status & MCAN_BUS_OFF) {
		mcan_clear_interrupt_status(&pHandle->can_module, MCAN_BUS_OFF);
	}

	if (status & MCAN_ACKNOWLEDGE_ERROR) {
		mcan_clear_interrupt_status(&pHandle->can_module, MCAN_ACKNOWLEDGE_ERROR);
	}

	if (status & MCAN_FORMAT_ERROR) {
		mcan_clear_interrupt_status(&pHandle->can_module, MCAN_FORMAT_ERROR);
	}
	
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
