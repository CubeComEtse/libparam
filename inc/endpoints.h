/*
 * endpoints.h
 *
 * Created: 2020/07/09 19:24:13
 *  Author: Kolijn
 */ 


#ifndef ENDPOINTS_H_
#define ENDPOINTS_H_

#define TEXT_ENDPOINT 0
#define I2C_ENDPOINT 1
#define BOARD_ENDPOINT 2
#define CAN_ENDPOINT 3
#define SPI_ENDPOINT 4
#define XTX_ENDPOINT 5 
#define HDRTX_ENDPOINT 6

// Renumbered some of the endpoints
// #define TEXT_ENDPOINT       0x10
#define I2C_ENDPOINT_CHKSM  0x11
#define I2C_ENDPOINT_PLAIN  0x12
// #define CAN_ENDPOINT        0x13
#define CAN_ENDPOINT_DFA	0x14
#define CAN_ENDPOINT_DFA_FW 0x15

#endif /* ENDPOINTS_H_ */