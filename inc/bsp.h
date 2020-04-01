/*
 * bsp.h
 *
 * Created: 2020/04/01 08:19:42
 *  Author: Kolijn
 */ 


#ifndef BSP_H_
#define BSP_H_

#include "usart_driver.h"

void BOARD_vInit(void);
struct usart_driver* BOARD_psGetTelemetryDriver(void);
void BOARD_vEnableUartTXInterrupt(void);
#endif /* BSP_H_ */