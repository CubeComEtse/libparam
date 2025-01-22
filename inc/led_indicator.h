#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include <stdint.h>

#include "ccd_led_driver.h"
#include "extra_maths.h"

typedef enum {
	/* Only used for startup */
	LED_STATE_IDLE=0,
	
	/* Busy with the transition */
	LED_STATE_TRANSITIONING=1,
	
	/* Waiting out on this point */
	LED_STATE_WAITING=2,
	
	/* In-between state to check the next thing to do */
	LED_STATE_CALCULATE_NEXT_POINT=3,
} led_state_t;


typedef enum {
	LED_UNUSED = 0,
	LED_POWER_ON = 1,
	LED_UART_COMMS = 2,
	LED_RADIO_ACTIVE = 3,
} led_board_state_t;

typedef struct {
	ccd_led_t * led_driver;
	
	/* Used to control the actual animation */
	led_state_t state;
	uint32_t state_start_tick;
	control_point_t * current_point;
	control_point_t * next_point;
	
	spline_definition_t * spline_to_use;
	size_t spline_index;
	
	led_board_state_t board_state;
	led_board_state_t desired_board_state;
	
	
} led_indicator_t;


void LEDIndicator_Setup(led_indicator_t * handle);
void LEDIndicator_UpdateTask(void * parameters);
void LEDIndicator_SetNextState(led_indicator_t * handle, led_board_state_t new_state);

#endif /* LED_DRIVER_H_ */