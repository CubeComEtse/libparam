/*
 * The drivers are an attempt to present a common hardware interface for the 
 * application code.
 * This driver interacts with ASF's UART driver. It implements 2 FreeRTOS 
 * streams to send UART bytes to and from the application 
 *
 * Created: 2024/10/04 08:52:01
 *  Author: Kolijn
 */ 

#include "ccd_uart_driver.h"

#include <assert.h>

#include "FreeRTOS.h"
#include "task.h"

void ccd_uart_Init(ccd_uart_t * driver, Usart * base_usart, uint8_t interrupt_priority)
{
	if (driver->doFlowControl)
    {
		assert(driver->cts_pin);	
	}
	
	// Todo: These buffer levels are guesses. Monitor and adjust them
	driver->uart_rx_buffer = xStreamBufferCreate(512, 1);
	driver->uart_tx_buffer = xStreamBufferCreate(512, 1);
	driver->base_usart = base_usart;
	
	driver->rx_buffer_read = 0;
	driver->rx_buffer_write = 0;
	
	driver->tx_buffer_read = 0;
	driver->tx_buffer_write = 0;
	
	ccd_uart_clear_error_status(driver);
	
	// Disable the Interrupts while configuring the usart
	usart_disable_interrupt(driver->base_usart, 0xFFFFFFFF);

	// Enable Clock to this module
	if (driver->base_usart == USART0)
	{
		sysclk_enable_peripheral_clock(ID_USART0); 
	}
	if (driver->base_usart == USART1)
	{
		sysclk_enable_peripheral_clock(ID_USART1);
	}
	if (driver->base_usart == USART2)
	{
		sysclk_enable_peripheral_clock(ID_USART2);
	}
		
	ccd_uart_setCommMode(driver, driver->uart_comm_mode);
	
	ccd_uart_ReInit(driver);
	
	// UART needs a priority above FreeRTOS tasks - there is a very small window to copy the received byte out of the register.
	if (driver->base_usart == USART0)
    {
		NVIC_SetPriority(USART0_IRQn, interrupt_priority);
		NVIC_EnableIRQ(USART0_IRQn);
	}
	if (driver->base_usart == USART1)
    {
		NVIC_SetPriority(USART1_IRQn, interrupt_priority);
		NVIC_EnableIRQ(USART1_IRQn);
	}
	if (driver->base_usart == USART2)
    {
		NVIC_SetPriority(USART2_IRQn, interrupt_priority);
		NVIC_EnableIRQ(USART2_IRQn);
	}
	
	if (driver->doFlowControl)
    {
		ccd_uart_StartFlowControl(driver);
	}
	
}

void ccd_uart_ReInit(ccd_uart_t * driver)
{
	usart_disable_interrupt(driver->base_usart, 0xFFFFFFFF);
	
	sam_usart_opt_t sUsartOptions;
	sUsartOptions.baudrate = driver->baudrate;
	sUsartOptions.char_length = US_MR_CHRL_8_BIT;
	
	if (driver->uart_parity_enabled == Enabled)
	{
		if (driver->uart_parity_mode == Odd) {
			sUsartOptions.parity_type = US_MR_PAR_ODD;
		}
		else {
			sUsartOptions.parity_type = US_MR_PAR_EVEN;
		}
	}
	else
	{
		sUsartOptions.parity_type = US_MR_PAR_NO;
	}
	sUsartOptions.stop_bits = US_MR_NBSTOP_1_BIT;
	
	sUsartOptions.channel_mode = US_MR_CHMODE_NORMAL;
	usart_init_rs232(driver->base_usart, &sUsartOptions, sysclk_get_peripheral_hz());

	usart_enable_tx(driver->base_usart);
	usart_enable_rx(driver->base_usart);
		
	usart_enable_interrupt(driver->base_usart, US_IER_RXRDY | US_IER_TXEMPTY);
}

void ccd_uart_setCommMode(void * vHandle, uart_comm_mode_t uart_comm_mode)
{
	ccd_uart_t * driver = (ccd_uart_t*) vHandle;
	driver->uart_comm_mode = uart_comm_mode;
	
	switch (uart_comm_mode)
    {
        case UART:
        {
            // Both in shutdown mode for RS422/RS485
            driver->set_gpio_pin(driver->sout_de_pin, 0);
            driver->set_gpio_pin(driver->sout_nre_pin, 1);
            driver->set_gpio_pin(driver->sin_de_pin, 0);
            driver->set_gpio_pin(driver->sin_nre_pin, 1);
            
            break;
        }
        case RS485:
        {
            // RS485 mode, start in receiving mode
            driver->set_gpio_pin(driver->sout_de_pin, 0);
            driver->set_gpio_pin(driver->sout_nre_pin, 0);
            
            // SIN lines are in shutdown
            driver->set_gpio_pin(driver->sin_de_pin, 0);
            driver->set_gpio_pin(driver->sin_nre_pin, 1);
            
            break;
        }
        case RS422:
        {
            // RS422 SOUT IC in drive mode
            driver->set_gpio_pin(driver->sout_de_pin, 1);
            driver->set_gpio_pin(driver->sout_nre_pin, 1);
            
            // SIN IC in receive mode
            driver->set_gpio_pin(driver->sin_de_pin, 0);
            driver->set_gpio_pin(driver->sin_nre_pin, 0);
            
            break;
        }
        default:
        {
            // TODO: We should probably handle this
            break;
        }
    }
}

void ccd_uart_setParityEnabled(void * vHandle, uart_parity_enabled_t ParityEnabled)
{
	ccd_uart_t * driver = (ccd_uart_t*) vHandle;
	driver->uart_parity_enabled = ParityEnabled;
	ccd_uart_ReInit(driver);
}

void ccd_uart_setParityMode(void * vHandle, uart_parity_mode_t ParityMode)
{
	ccd_uart_t * driver = (ccd_uart_t*) vHandle;
	driver->uart_parity_mode = ParityMode;
	ccd_uart_ReInit(driver);
}

void ccd_uart_setBaudRate(void * vHandle, uart_baud_rates_t BaudRate)
{
	ccd_uart_t * driver = (ccd_uart_t*) vHandle;
	
	if (BaudRate == baud_115200)
	{
		driver->baudrate = 115200;
	}
	if (BaudRate == baud_230400)
	{
		driver->baudrate = 230400;
	}
	if (BaudRate == baud_460800)
	{
		driver->baudrate = 460800;
	}
	if (BaudRate == baud_921600){
		driver->baudrate = 921600;
	}
	ccd_uart_ReInit(driver);
}

/*
 * Re-enable the interrupt. Call this after data was loaded into the buffer,
 * to start sending it again.
*/
void ccd_uart_EnableTXInterrupt(ccd_uart_t * driver)
{
	usart_enable_interrupt(driver->base_usart, US_IER_TXEMPTY);
}

inline void ccd_uart_StopFlowControl(void * handle)
{
    assert(handle != NULL);
    
	ccd_uart_t * driver =  (ccd_uart_t *) handle;
    
	ioport_set_pin_level(driver->cts_pin, true);
}

inline void ccd_uart_StartFlowControl(void * handle)
{
    assert(handle != NULL);
    
	ccd_uart_t * driver =  (ccd_uart_t *) handle;
	
	if ((UART_HOLDING_BUFFER_SIZE - driver->rx_buffer_write + driver->rx_buffer_read - 1)% UART_HOLDING_BUFFER_SIZE > 5)
	{
		ioport_set_pin_level(driver->cts_pin, false);
	}
}

/*
 * So: This chip is not fast enough to service the UART interrupt AND
 * add the data to a FreeRTOS message buffer. Instead add the data to a
 * temporary buffer, and then use this task to add it to an actual 
 * steam. The interrupt is still allowed to append data while this task is
 * running, but it should be fast enough that we don't run into an issue.
*/
void ccd_usart_RXProcessingTask(void * parameters)
{
	ccd_uart_t * driver = (ccd_uart_t*) parameters;
	
	while(1)
	{
		// Wait for new data to be received
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY); 
		
		// Check if there are more bytes in the buffer since the previous time -
		if (driver->rx_buffer_read != driver->rx_buffer_write)
		{
			// Make a copy of the write location - interrupt can still increment it 
			volatile size_t copied_write = driver->rx_buffer_write;
			
			// First copy all data from the read position until the end of the buffer.
			// If all these bytes are copied the pointer will be reset to the beginning of 
			// the buffer
			if (copied_write < driver->rx_buffer_read) {
				size_t bytes_sent = xStreamBufferSend(driver->uart_rx_buffer, &driver->rx_holding_buffer[driver->rx_buffer_read], (UART_HOLDING_BUFFER_SIZE - driver->rx_buffer_read), 0);
				driver->rx_buffer_read = (driver->rx_buffer_read + bytes_sent) % UART_HOLDING_BUFFER_SIZE;
				
				if (bytes_sent == 0){
					// Stream buffer overflow
					driver->rx_streaming_buffer_overflow = true;
				}
			}
			
			// Then if there are more bytes available until the write pointer, copy them too.
			if (driver->rx_buffer_read < copied_write )
			{
				size_t bytes_sent = xStreamBufferSend(driver->uart_rx_buffer, &driver->rx_holding_buffer[driver->rx_buffer_read], (copied_write - driver->rx_buffer_read), 0);
				driver->rx_buffer_read = (driver->rx_buffer_read + bytes_sent) % UART_HOLDING_BUFFER_SIZE;
				
				if (bytes_sent == 0){
					// Stream buffer overflow
					driver->rx_streaming_buffer_overflow = true;
				}
			}
			
			// Check if there is space, then clear CTS
			ccd_uart_StartFlowControl(driver);
		}	
		
		//vTaskDelay(pdMS_TO_TICKS(1));
	}
}

void ccd_usart_TXProcessingTask(void * parameters)
{
	ccd_uart_t * driver = (ccd_uart_t*) parameters;
	
	while(1)
	{
		// Calculate the max space available
		size_t max_bytes_to_read = (UART_HOLDING_BUFFER_SIZE - driver->tx_buffer_write + driver->tx_buffer_read - 1)% UART_HOLDING_BUFFER_SIZE;
		
		// If write pointer is past read pointer the max data to receive is to the 
		// end of the buffer
		if (driver->tx_buffer_read <= driver->tx_buffer_write){
			max_bytes_to_read = min(max_bytes_to_read, UART_HOLDING_BUFFER_SIZE - driver->tx_buffer_write);
		}
		
		// If max_bytes_to_read is zero the buffer is full. We don't even need to 
		// try reading 0 from the StreamBuffer.
		if (max_bytes_to_read == 0){
			driver->tx_holding_buffer_overflow = true;
		}
		else
		{
			size_t read_size = xStreamBufferReceive(driver->uart_tx_buffer, &driver->tx_holding_buffer[driver->tx_buffer_write], max_bytes_to_read, portMAX_DELAY);
			driver->tx_buffer_write = (driver->tx_buffer_write + read_size) % UART_HOLDING_BUFFER_SIZE;
		
			// If we copied any data into the buffer, enable the interrupt
			if (read_size > 0){
				usart_enable_interrupt(driver->base_usart, US_IER_TXEMPTY);
			}
		}
	}
}

/*
 * This function should be installed into the interrupt handler for the corresponding UART
*/
inline void ccd_uart_InterruptHandler(ccd_uart_t * driver)
{
	uint32_t dw_status = usart_get_status(driver->base_usart);
    
	// A Value is received
	if (dw_status & US_CSR_RXRDY)
    {
		uint32_t received_byte_u32;

		while (usart_read(driver->base_usart, &received_byte_u32) == 0)
		{
			size_t space_available = (UART_HOLDING_BUFFER_SIZE - driver->rx_buffer_write + driver->rx_buffer_read - 1) % UART_HOLDING_BUFFER_SIZE;
			
			if (space_available <= 2)
			{
				// No more space in buffer, drop the byte, and notify
				driver->rx_holding_buffer_overflow = true;
			}
			else
			{
				// Add the received byte to the holding buffer
				driver->rx_holding_buffer[driver->rx_buffer_write] = received_byte_u32;
				driver->rx_buffer_write = (driver->rx_buffer_write + 1) % UART_HOLDING_BUFFER_SIZE;
					
				if (space_available < 10)
				{
					ccd_uart_StopFlowControl(driver);
				}

				// Notify RX data processing task of new data
                // TODO: Handle interrupts that also triggered before this task was created
                if (driver->rx_task_handle != NULL)
                {
                    vTaskNotifyGiveFromISR(driver->rx_task_handle, NULL);
                }
			}
		}
	}

	// TX Buffer and shift register empty
	if (dw_status & US_CSR_TXEMPTY)
    {
		if (driver->tx_buffer_read != driver->tx_buffer_write)
		{
			if (driver->uart_comm_mode == RS485)
            {
				// One pin enables drive, the other disables receive.
				// Otherwise we receive our own signal, a few microseconds later.
				driver->set_gpio_pin(driver->sout_de_pin, 1);
				driver->set_gpio_pin(driver->sout_nre_pin, 1);
			}
			usart_write(driver->base_usart, driver->tx_holding_buffer[driver->tx_buffer_read]);
			driver->tx_buffer_read = (driver->tx_buffer_read + 1) % UART_HOLDING_BUFFER_SIZE;
		}
		else
        {
			if (driver->uart_comm_mode == RS485)
            {
				driver->set_gpio_pin(driver->sout_de_pin, 0);
				driver->set_gpio_pin(driver->sout_nre_pin, 0);
			}
			usart_disable_interrupt(driver->base_usart, US_IER_TXEMPTY);
		}
	}
    
    // Overrun Error    
    if (dw_status & US_CSR_OVRE)
    {
        driver->base_usart->US_CR |= US_CR_RSTSTA;
        __NOP();
    }
}

uint32_t ccd_uart_get_error_status(void * vHandle)
{
	ccd_uart_t * pHandle = (ccd_uart_t*) vHandle;
	uint32_t res = 0 ;
	
	if (pHandle->rx_holding_buffer_overflow)
	{
		res |= UART_RX_HB_OVERFLOW;
	}
	if (pHandle->rx_streaming_buffer_overflow)
	{
		res |= UART_RX_SB_OVERFLOW;
	}
	if (pHandle->tx_holding_buffer_overflow)
	{
		res |= UART_TX_SB_OVERFLOW;
	}
	return res;
}

void ccd_uart_clear_error_status(void * vHandle)
{
	ccd_uart_t * pHandle = (ccd_uart_t*) vHandle;
	
	pHandle->rx_holding_buffer_overflow = false;
	pHandle->rx_streaming_buffer_overflow = false;
	pHandle->tx_holding_buffer_overflow = false;
}

void ccd_b_uart_Send_message(void * vHandle, uint8_t * data, size_t data_len)
{
	ccd_uart_t * pHandle = (ccd_uart_t*) vHandle;
	
	size_t bytes_sent = xStreamBufferSend(pHandle->uart_tx_buffer, data, data_len, 0);
	
	if (bytes_sent > 0){
		ccd_uart_EnableTXInterrupt(pHandle);
	}
}

size_t ccd_b_uart_Receive_message(void * vHandle, uint8_t * data, size_t data_len) 
{
	ccd_uart_t * pHandle = (ccd_uart_t*) vHandle;

	size_t bytes_received = xStreamBufferReceive(pHandle->uart_rx_buffer, data, data_len, portMAX_DELAY);
	
	return bytes_received; // returns size of actual streambuffer received
}