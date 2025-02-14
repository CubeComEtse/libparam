#include <asf.h>
#include <assert.h>

#include "led_indicator.h"

#include <FreeRTOS.h>
#include <task.h>

static spline_definition_t power_on_breathing;
static spline_definition_t uart_comms_breathing;
static spline_definition_t comms_active_bounce;

static led_indicator_t * static_ref;

control_point_t points[] ={
	
	//Statup point
	{
		.coordinate      = (vec3_t) {.x=0.0, .y=0.0, .z=0.0},
		.forward_toggle  = (vec3_t) {.x=0.0, .y=0.0, .z=0.0},
		.backward_toggle = (vec3_t) {.x=0.0, .y=0.0, .z=0.0},
		.ticks_to_stay_on = 0,
		.ticks_speed = 1000,
	},
	//Bright yellow - breathing 1
	{
		.coordinate      = (vec3_t) {.x=0.816, .y=0.746, .z=0.176},
		.forward_toggle  = (vec3_t) {.x=0.615, .y=0.592, .z=0.401},
		.backward_toggle = (vec3_t) {.x=0.615, .y=0.592, .z=0.401},
		.ticks_to_stay_on = 700,
		.ticks_speed = 1500,
	},
	//Dark yellow - breathing 2
	{
		.coordinate      = (vec3_t) {.x=0.057, .y=0.054, .z=0.042},
		.forward_toggle  = (vec3_t) {.x=0.221, .y=0.212, .z=0.144},
		.backward_toggle = (vec3_t) {.x=0.221, .y=0.212, .z=0.144},
		.ticks_to_stay_on = 100,
		.ticks_speed = 1700,
	},
	//Bright Green - Comms Breathing 1
	{
		.coordinate      = (vec3_t) {.x=0.100, .y=0.900, .z=0.010},
		.forward_toggle  = (vec3_t) {.x=0.000, .y=0.800, .z=0.000},
		.backward_toggle = (vec3_t) {.x=0.000, .y=0.800, .z=0.000},
		.ticks_to_stay_on = 200,
		.ticks_speed = 500,
	},
	//Dark Green - breathing 2
	{
		.coordinate      = (vec3_t) {.x=0.000, .y=0.100, .z=0.000},
		.forward_toggle  = (vec3_t) {.x=0.000, .y=0.200, .z=0.000},
		.backward_toggle = (vec3_t) {.x=0.000, .y=0.200, .z=0.000},
		.ticks_to_stay_on = 100,
		.ticks_speed = 1700,
	}
};

control_point_t green_blue_bounce[] ={
	{
		//Black
		.coordinate      = (vec3_t) {.x=0.0, .y=0.0, .z=0.0},
		.forward_toggle  = (vec3_t) {.x=0.0, .y=1.0, .z=0.0},
		.backward_toggle = (vec3_t) {.x=0.0, .y=0.0, .z=0.0},
		.ticks_to_stay_on = 1000,
		.ticks_speed = 2000,
	},
	{
		//GreenBlue
		.coordinate      = (vec3_t) {.x=0.0, .y=1.0, .z=1.0},
		.forward_toggle  = (vec3_t) {.x=0.0, .y=0.0, .z=0.9},
		.backward_toggle = (vec3_t) {.x=0.0, .y=0.9, .z=0.0},
		.ticks_to_stay_on = 1000,
		.ticks_speed = 2000,
	},
	{
		//Black
		.coordinate      = (vec3_t) {.x=0.0, .y=0.0, .z=0.0},
		.forward_toggle  = (vec3_t) {.x=1.0, .y=0.0, .z=0.0},
		.backward_toggle = (vec3_t) {.x=0.0, .y=0.0, .z=0.0},
		.ticks_to_stay_on = 1000,
		.ticks_speed = 2000,
	},
	{
		//Purple
		.coordinate      = (vec3_t) {.x=1.0, .y=0.0, .z=1.0},
		.forward_toggle  = (vec3_t) {.x=0.0, .y=0.0, .z=0.9},
		.backward_toggle = (vec3_t) {.x=0.9, .y=0.0, .z=0.0},
		.ticks_to_stay_on = 1000,
		.ticks_speed = 2000,
	}
};

void LEDIndicator_Setup(led_indicator_t * handle)
{	
	assert(handle);
	assert(handle->led_driver);
	power_on_breathing.num_control_points = 2;
	power_on_breathing.control_points = &points[1];
	
	uart_comms_breathing.num_control_points=2;
	uart_comms_breathing.control_points= &points[3];
	
	handle->state = LED_STATE_IDLE;
	handle->state_start_tick = 0;
	handle->current_point = &points[0];
	handle->next_point = &points[0];
	
	handle->spline_to_use = &power_on_breathing;
	handle->desired_board_state = LED_UNUSED;
	handle->board_state = LED_UNUSED;
	
	ccd_led_driver_SetLed(handle->led_driver, 0, 0, 0);
}

void LEDIndicator_SetStatic(led_indicator_t * handle)
{
	static_ref = handle;
}

void LEDIndicator_SetNextState(led_board_state_t new_state)
{
	static_ref->desired_board_state = new_state;
	
	if (static_ref->state == LED_STATE_IDLE){
		static_ref->state = LED_STATE_CALCULATE_NEXT_POINT;
	}
}


void LEDIndicator_UpdateTask(void * parameters)
{
	led_indicator_t * handle = (led_indicator_t*) parameters;
	vec3_t new_led = {0};
	double t = 0;

    while(1)
    {		
		uint32_t current_tick = xTaskGetTickCount();
		
		switch (handle->state){
			case LED_STATE_IDLE:
				break;

			case LED_STATE_TRANSITIONING:
			{
				if (current_tick >= handle->state_start_tick + handle->current_point->ticks_speed)
				{
					// Transition done, go to next state
					handle->state = LED_STATE_WAITING;
					handle->state_start_tick = current_tick;
				}
				else
				{
					t = (double)(current_tick - handle->state_start_tick) / (double)handle->current_point->ticks_speed;
					
					E_MATH_CalculateSplinePoint(handle->current_point, handle->next_point, t, &new_led);
					
					// Range limits
					if (new_led.x > 1.0)
					new_led.x = 1.0;
					if (new_led.y > 1.0)
					new_led.y = 1.0;
					if (new_led.z > 1.0)
					new_led.z = 1.0;

					if (new_led.x < 0)
					new_led.x = 0;
					if (new_led.y < 0)
					new_led.y = 0;
					if (new_led.z < 0)
					new_led.z = 0;

					ccd_led_driver_SetLed(handle->led_driver,
					(uint8_t)(new_led.x * 255),
					(uint8_t)(new_led.y * 255),
					(uint8_t)(new_led.z * 255));
				}
			}
			break;
			
			case LED_STATE_WAITING:
			if (current_tick > handle->state_start_tick + handle->current_point->ticks_to_stay_on)
			{
				handle->state = LED_STATE_CALCULATE_NEXT_POINT;
				handle->state_start_tick = current_tick;
			}
			break;
			
			case LED_STATE_CALCULATE_NEXT_POINT:
			if (handle->board_state == handle->desired_board_state){
				// Just go on to the next point in the spline
				handle->current_point = handle->next_point;
				handle->next_point = &handle->spline_to_use->control_points[handle->spline_index];
				handle->spline_index += 1;
				if (handle->spline_index >= handle->spline_to_use->num_control_points){
					handle->spline_index = 0;
				}
				handle->state = LED_STATE_TRANSITIONING;
				handle->state_start_tick = current_tick;
			}
			else{
				// Select the new spline
				if (handle->desired_board_state == LED_POWER_ON)
				{
					handle->spline_to_use = &power_on_breathing;
				}
				if (handle->desired_board_state == LED_UART_COMMS)
				{
					handle->spline_to_use = &uart_comms_breathing;
				}
				if (handle->desired_board_state == LED_RADIO_ACTIVE)
				{
					handle->spline_to_use = &comms_active_bounce;
				}
					
				handle->current_point = handle->next_point;
				handle->next_point = &handle->spline_to_use->control_points[0];
				//Already loaded the first point
				handle->spline_index = 1;
				
				handle->board_state = handle->desired_board_state;
				
				handle->state = LED_STATE_TRANSITIONING;
				handle->state_start_tick = current_tick;
			}
			break;
		}
	      
		vTaskDelay(pdMS_TO_TICKS(20)); 
    }
}
