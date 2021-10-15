/*
 * xdc.h
 *
 * Created: 2021/09/03 09:35:24
 *  Author: Kolijn
 */ 


#ifndef XDC_H_
#define XDC_H_

#include <stdint.h>
#include <stdbool.h>

void XDC_vConfig(void);
void XDC_SetAddress(uint8_t newAddress);
void XDC_vDeConfig(void);

#endif /* XDC_H_ */