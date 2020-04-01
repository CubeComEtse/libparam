#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_

#include <stdbool.h>
#include <stdint.h>

#define USART_BUF_LENGTH 128
struct usart_driver {
    uint8_t rx_buffer[USART_BUF_LENGTH];
    uint8_t tx_buffer[USART_BUF_LENGTH];
    uint16_t rx_index;
    uint16_t tx_read_index;
    uint16_t tx_write_index;
    char end_char;
    bool has_message;
};

void USART_init(struct usart_driver* drv);

void USART_setEndChar(struct usart_driver* drv, char end_char);

// TX buffer interaction
bool USART_putChar(struct usart_driver* drv, uint8_t data);

//RX buffer interaction
bool USART_hasMessage(struct usart_driver* drv);
uint8_t* USART_getRxBuffer(struct usart_driver* drv);
void USART_clearMessage(struct usart_driver* drv);

//Callbacks from interrupt
bool USART_byteReceived(struct usart_driver* drv, uint8_t received_byte);
bool USART_byteTransmitted(struct usart_driver* drv, uint8_t *received_byte);

#endif /* USART_DRIVER_H_ */