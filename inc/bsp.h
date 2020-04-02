/*
 * bsp.h
 *
 * Created: 2020/04/01 08:19:42
 *  Author: Kolijn
 */ 


#ifndef BSP_H_
#define BSP_H_

#include "usart_buffer.h"

void BSP_vInit(void);
USART_data_t* BSP_psGetTelemetryDriver(void);
void BSP_vEnableUartTXInterrupt(void);
#endif /* BSP_H_ */