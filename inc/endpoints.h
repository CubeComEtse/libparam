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

// Renumbered some of the endpoints
#define I2C_ENDPOINT_CHKSM  0x10
#define I2C_ENDPOINT_PLAIN  0x11

#endif /* ENDPOINTS_H_ */