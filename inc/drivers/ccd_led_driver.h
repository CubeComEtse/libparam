/*
 * ccd_led_driver.h
 *
 * Created: 2025/01/21 08:47:01
 *  Author: Kolijn
 *
 * This is a driver for driving a single RGB led using the 800kHz protocol.
 * It uses the PWM module to achieve the timings required.
 *
 * This module disables the UART interrupt while writing to the LED, otherwise 
 * the interrupt disturbs the timings.
 */ 

#ifndef CCD_LED_DRIVER_H_
#define CCD_LED_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "asf.h"

/*
 * Writing to the LED  
*/
typedef void (*uart_disable_fc_t)(void * handle);
typedef void (*uart_enable_fc_t)(void * handle);

typedef struct {
	Pwm * pwm;
	
	uart_disable_fc_t uart_disable_fc;
	uart_enable_fc_t uart_enable_fc;
	void *uart_handle;
}ccd_led_t;

void ccd_led_driver_Init(ccd_led_t * driver, Pwm * pwm_instance);
void ccd_led_driver_DisableInterrupts(ccd_led_t * driver, bool value);
void ccd_led_driver_SetLed(ccd_led_t * driver, uint8_t r, uint8_t g, uint8_t b);

#endif /* CCD_LED_DRIVER_H_ */