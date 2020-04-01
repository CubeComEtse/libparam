#include "usart_driver.h"
#include "bsp.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * \brief Initialize the USART Driver struct
 * 
 * \param drv
 * 
 * \return void
 */
void USART_init(struct usart_driver* drv) {
    drv->rx_index = 0;
    drv->tx_read_index = 0;
    drv->tx_write_index = 0;
}

/**
 * \brief Set the ending character to look for when parsing messages
 * 
 * \param drv
 * \param end_char
 * 
 * \return void
 */
void USART_setEndChar(struct usart_driver* drv, char end_char) {
    drv->end_char = end_char;
}


bool USART_putChar(struct usart_driver* drv, uint8_t data){
    drv->tx_buffer[drv->tx_write_index] = data;
    drv->tx_write_index += 1;

    BOARD_vEnableUartTXInterrupt();
    // Returns true if there is more space
    return drv->tx_write_index != drv->tx_read_index;
}

//RX buffer interaction
bool USART_hasMessage(struct usart_driver* drv) {
    return drv->has_message;
}


uint8_t* USART_getRxBuffer(struct usart_driver* drv){
    return drv->rx_buffer;
}


void USART_clearMessage(struct usart_driver* drv) {
    drv->rx_index = 0;
    drv->has_message = false;
}

bool USART_byteReceived(struct usart_driver* drv, uint8_t received_byte) {
    // Store value
    if (drv->rx_index <= USART_BUF_LENGTH - 1) {
        drv->rx_buffer[drv->rx_index] = received_byte;

        // Check for end character
        if (received_byte == drv->end_char) {
            drv->has_message = true;
        }
        drv->rx_index += 1;
        // Add 0 for string handling
        drv->rx_buffer[drv->rx_index] = 0;
    }

    // If there is still space after incrementing
    if (drv->rx_index < USART_BUF_LENGTH - 1) {
        return true;
    }

    return false;
}

bool USART_byteTransmitted(struct usart_driver* drv, uint8_t *received_byte){
    // If there is another byte, send it and reply true
    if (drv->tx_read_index != drv->tx_write_index) {
        *received_byte = drv->tx_buffer[drv->tx_read_index];
        drv->tx_read_index += 1;
        return true;
    }
    return false;
}