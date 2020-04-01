/*
 * usart_bufferc.c
 *
 * Created: 2020/04/01 10:08:32
 *  Author: Kolijn
 */ 
#include <asf.h>

struct buffer{
    uint8_t* buf;
    uint16_t buf_length;
    uint16_t read_pos;
    uint16_t write_pos;
};

typedef struct usart_config_t {
    struct buffer tx_buffer;
    struct buffer rx_buffer;
    uint8_t end_char;
} usart_config_t;


void SerialBuffer_vInit(usart_config_t* drv, int tx_buf_size, int rx_buf_size);




//int USART_vSetCallbackFunction(usart_config_t* drv);