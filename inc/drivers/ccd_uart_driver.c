/*
 * The drivers are an attempt to present a common hardware interface for the 
 * application code.
 * This driver interacts with ASF's UART driver. It implements 2 Freertos 
 * streams to send uart bytes to and from the application 
 *
 * Created: 2024/10/04 08:52:01
 *  Author: Kolijn
 */ 

#include "ccd_uart_driver.h"

#include "FreeRTOS.h"
#include "task.h"

#include "assert.h"


void ccd_uart_Init(ccd_uart_t * driver, Usart * base_usart, const uint32_t baud)
{
	assert(driver->cts_pin);
	
	// Todo: These buffer levels are guesses. Monitor and adjust them
	driver->uart_rx_buffer = xStreamBufferCreate(512, 1);
	driver->uart_tx_buffer = xStreamBufferCreate(512, 1);
	driver->base_usart = base_usart;
	
	driver->rx_buffer_read = 0;
	driver->rx_buffer_write = 0;
	
	driver->tx_buffer_read = 0;
	driver->tx_buffer_write = 0;
	
	// Disable the Interrupts while configuring the usart
	usart_disable_interrupt(driver->base_usart, 0xFFFFFFFF);


	// Enable Clock to this module
	if (driver->base_usart == USART0)
		sysclk_enable_peripheral_clock(ID_USART0); 
	if (driver->base_usart == USART1)
		sysclk_enable_peripheral_clock(ID_USART1); 
	if (driver->base_usart == USART2)
		sysclk_enable_peripheral_clock(ID_USART2);
		
	// Setup for Telemetry USART
	sam_usart_opt_t sUsartOptions;
	sUsartOptions.baudrate = baud;
	sUsartOptions.char_length = US_MR_CHRL_8_BIT;
	sUsartOptions.parity_type = US_MR_PAR_NO;
	sUsartOptions.stop_bits = US_MR_NBSTOP_1_BIT;
	sUsartOptions.channel_mode = US_MR_CHMODE_NORMAL;

	usart_init_rs232(driver->base_usart, &sUsartOptions, sysclk_get_peripheral_hz());
	usart_enable_tx(driver->base_usart);
	usart_enable_rx(driver->base_usart);

	// Re-enable Interrupts
	usart_enable_interrupt(driver->base_usart, US_IER_RXRDY | US_IER_TXEMPTY);
	
	// UART needs a priority above FreeRTOS tasks - there is a very small window to copy the received byte out of the register.
	if (driver->base_usart == USART0){
		NVIC_SetPriority(USART0_IRQn, 1);
		NVIC_EnableIRQ(USART0_IRQn);
	}
	if (driver->base_usart == USART1){
		NVIC_SetPriority(USART1_IRQn, 1);
		NVIC_EnableIRQ(USART1_IRQn);
		}
	if (driver->base_usart == USART2){
		NVIC_SetPriority(USART2_IRQn, 1);
		NVIC_EnableIRQ(USART2_IRQn);
		}

	ccd_uart_SetCTS(driver, false);
	
}

void ccd_uart_SetCTS(ccd_uart_t * driver, bool dir){
	ioport_set_pin_level(driver->cts_pin, dir);
}

/*
 * Re-enable the interrupt. Call this after data was loaded into the buffer,
 * to start sending it again.
*/
void ccd_uart_EnableTXInterrupt(ccd_uart_t * driver) {
	usart_enable_interrupt(driver->base_usart, US_IER_TXEMPTY);
}

#include "bsp.h"
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
		// Wait forever until the task notification is set.
		ulTaskNotifyTakeIndexed(0, pdTRUE, portMAX_DELAY);
		
		// Check if there are more bytes in the buffer since the previous time -
		//if (driver->rx_buffer_read != driver->rx_buffer_write)
		//{
			// Make a copy of the write location - interrupt can still increment it 
			volatile size_t copied_write = driver->rx_buffer_write;
			
			// First copy all data from the read position until the end of the buffer.
			// If all these bytes are copied the pointer will be reset to the beginning of 
			// the buffer
			if (copied_write < driver->rx_buffer_read) {
				size_t bytes_sent = xStreamBufferSend(driver->uart_rx_buffer, &driver->rx_holding_buffer[driver->rx_buffer_read], (UART_HOLDING_BUFFER_SIZE - driver->rx_buffer_read), 0);
				driver->rx_buffer_read = (driver->rx_buffer_read + bytes_sent) % UART_HOLDING_BUFFER_SIZE;
			}
			
			// Then if there are more bytes available until the write pointer, copy them too.
			if (driver->rx_buffer_read < copied_write )
			{
				size_t bytes_sent = xStreamBufferSend(driver->uart_rx_buffer, &driver->rx_holding_buffer[driver->rx_buffer_read], (copied_write - driver->rx_buffer_read), 0);
				driver->rx_buffer_read = (driver->rx_buffer_read + bytes_sent) % UART_HOLDING_BUFFER_SIZE;
			}
			
			// We just copied data out of the buffer, there should be space
			ccd_uart_SetCTS(driver, false);
		//}	
	}
}

void ccd_usart_TXProcessingTask(void * parameters)
{
	ccd_uart_t * driver = (ccd_uart_t*) parameters;
	
	while(1)
	{
		// Calculate the max space available
		size_t bytes_to_read = (UART_HOLDING_BUFFER_SIZE - driver->tx_buffer_write + driver->tx_buffer_read - 1)% UART_HOLDING_BUFFER_SIZE;
		
		// If write pointer is past read pointer the max data to receive is to the 
		// end of the buffer
		if (driver->tx_buffer_read <= driver->tx_buffer_write){
			bytes_to_read = min(bytes_to_read, UART_HOLDING_BUFFER_SIZE - driver->tx_buffer_write);
		}
		
		size_t read_size = xStreamBufferReceive(driver->uart_tx_buffer, &driver->tx_holding_buffer[driver->tx_buffer_write], bytes_to_read, portMAX_DELAY);
		driver->tx_buffer_write = (driver->tx_buffer_write + read_size) % UART_HOLDING_BUFFER_SIZE;
		
		// If we copied any data into the buffer, enable the interrupt
		if (read_size > 1){
			usart_enable_interrupt(driver->base_usart, US_IER_TXEMPTY);
		}
		
		/*
		if (xStreamBufferBytesAvailable(driver->uart_tx_buffer))
		{
			volatile size_t copied_read = driver->tx_buffer_read;
			
			size_t space_available = (UART_HOLDING_BUFFER_SIZE - driver->tx_buffer_write + copied_read - 1)% UART_HOLDING_BUFFER_SIZE;
			
			//Check if there is space in the buffer - more than 10 spaces.
			if (space_available > 10){
				if (driver->tx_buffer_write >= copied_read)
				{
					// If Read pointer is at 0 we can't fill to the end of the buffer, so get the minimum
					// possible size here.
					size_t bytes_to_read = min(space_available, UART_HOLDING_BUFFER_SIZE - driver->tx_buffer_write);
					size_t read_size = xStreamBufferReceive(driver->uart_tx_buffer, &driver->tx_holding_buffer[driver->tx_buffer_write], bytes_to_read, 0);
					driver->tx_buffer_write = (driver->tx_buffer_write + read_size) % UART_HOLDING_BUFFER_SIZE;
					usart_enable_interrupt(driver->base_usart, US_IER_TXEMPTY);
				}
				
				
				// If the write pointer was smaller than the read pointer, or we just filled up that part of the buffer.
				if (driver->tx_buffer_write < copied_read)
				{
					// Fill until the copied read
					size_t read_size = xStreamBufferReceive(driver->uart_tx_buffer, &driver->tx_holding_buffer[driver->tx_buffer_write], (copied_read - driver->tx_buffer_write - 1), 0);
					driver->tx_buffer_write = (driver->tx_buffer_write + read_size) % UART_HOLDING_BUFFER_SIZE;
					
					usart_enable_interrupt(driver->base_usart, US_IER_TXEMPTY);
				}
			}		
		}		
		
		vTaskDelay(pdMS_TO_TICKS(1));*/
	}
}





/*
 * This function should be installed into the interrupt handler for the corresponding UART
*/
inline void ccd_uart_InterruptHandler(ccd_uart_t * driver)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	uint32_t dw_status = usart_get_status(driver->base_usart);
	//ioport_set_pin_level(PIN_DEBUG_1, 1);

	// A Value is received
	if (dw_status & US_CSR_RXRDY) {
		uint32_t received_byte_u32;

		while (usart_read(driver->base_usart, &received_byte_u32) == 0)
		{
			// Add the received byte to the holding buffer
			driver->rx_holding_buffer[driver->rx_buffer_write] = received_byte_u32;
			driver->rx_buffer_write = (driver->rx_buffer_write + 1) % UART_HOLDING_BUFFER_SIZE;
			
			// Todo: Is this timeout correct?
		
			// Todo: We should set CTS here if the buffer is close to full.
			// Todo: Raise an event if no bytes could be written.
			size_t space_available = (UART_HOLDING_BUFFER_SIZE - driver->rx_buffer_write + driver->rx_buffer_read - 1) % UART_HOLDING_BUFFER_SIZE;
			if (space_available < 10)
			{
				ccd_uart_SetCTS(driver, true);
			}
			
			// Notify the task that we received some values.
			vTaskNotifyGiveIndexedFromISR (driver->task_reference, 0, &xHigherPriorityTaskWoken );  
		}
	}

	// TX Buffer and shift register empty	
	if ((dw_status & US_CSR_TXEMPTY)) {
		if (driver->tx_buffer_read != driver->tx_buffer_write)
		{
			usart_write(driver->base_usart, driver->tx_holding_buffer[driver->tx_buffer_read]);
			driver->tx_buffer_read = (driver->tx_buffer_read + 1) % UART_HOLDING_BUFFER_SIZE;
		}
		else {
			usart_disable_interrupt(driver->base_usart, US_IER_TXEMPTY);
		}
	}
	
	//ioport_set_pin_level(PIN_DEBUG_1, 0);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}