#include <asf.h>

#include "led_driver.h"

#include <FreeRTOS.h>
#include <task.h>

#include "extra_maths.h"


static spline_definition_t green_blue_bounce;
static control_point_t gb_points[4];

//Todo: All of this should be somewhere else
void setup_pwm_for_the_damn_led(void){
	// Setup GPIO pin
	// Pin PA15 - supports PWMC0_ PWML3 on Peripheral C
	
	PIOA->PIO_ABCDSR[0] &= ~PIO_ABCDSR_P15;
	PIOA->PIO_ABCDSR[1] |= PIO_ABCDSR_P15;

	// Set Pin to Peripheral mode
	PIOA->PIO_PDR |= PIO_PDR_P15;


	// Enable clock to PWM module
	PMC->PMC_PCER0 = PMC_PCER0_PID31;


	Pwm * pwm = PWM0;

	// Enable Channel ID 3

	// Select peripheral clock - 100 Mhz
	pwm->PWM_CLK = PWM_CLK_PREA(PWM_CLK_PREA_CLK) | PWM_CLK_DIVA(1);

	// Channel Mode register:
	// CALG     0   Channel is left aligned
	// CPRE     0   Prescaler is MCK
	// CPOL     0   Output starts low (we use inverted output)
	// DPOL     1   When disabled, output is 1 (inverted output is 0)
	pwm->PWM_CH_NUM[3].PWM_CMR = PWM_CMR_DPOLI;

	// Set to 100 for now - 1 Mhz. Poor LED
	pwm->PWM_CH_NUM[3].PWM_CPRD = 120;
	pwm->PWM_CH_NUM[3].PWM_CDTYUPD = 0;

	// Enable interrupts on the channel

	pwm->PWM_IER1 |= PWM_IER1_CHID3;
}

void LED_DRIVER_Setup(void){
	setup_pwm_for_the_damn_led();
	
    green_blue_bounce.num_control_points = 4;
    green_blue_bounce.control_points = gb_points;

    gb_points[0].coordinate      = (vec3_t) {.x=0.0, .y=0.0, .z=0.0};
    gb_points[0].forward_toggle  = (vec3_t) {.x=0.0, .y=1.0, .z=0.0};
    gb_points[0].backward_toggle = (vec3_t) {.x=0.0, .y=0.0, .z=1.0};
    
    gb_points[1].coordinate      = (vec3_t) {.x=0.0, .y=1.0, .z=1.0};
    gb_points[1].forward_toggle  = (vec3_t) {.x=0.0, .y=0.0, .z=0.9};
    gb_points[1].backward_toggle = (vec3_t) {.x=0.0, .y=0.9, .z=0.0};

    gb_points[2].coordinate      = (vec3_t) {.x=0.0, .y=0.0, .z=0.0};
    gb_points[2].forward_toggle  = (vec3_t) {.x=1.0, .y=0.0, .z=0.0};
    gb_points[2].backward_toggle = (vec3_t) {.x=0.0, .y=0.0, .z=1.0};

    gb_points[3].coordinate      = (vec3_t) {.x=1.0, .y=0.0, .z=1.0};
    gb_points[3].forward_toggle  = (vec3_t) {.x=0.0, .y=0.0, .z=0.9};
    gb_points[3].backward_toggle = (vec3_t) {.x=0.9, .y=0.0, .z=0.0};
    
}


void LED_DRIVER_UpdateTask(void * parameters)
{

    vec3_t new_led = {0};
    double t = 0;
    uint32_t pattern1 = 0;
	
	uint8_t counter = 0;

    while(1)
    {
		TickType_t ticks = xTaskGetTickCount();
        t = ((double) ticks)/ 3000;
        E_MATH_CalculateSplinePoint(&green_blue_bounce, t, &new_led);

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

        pattern1 =   (((uint32_t)(new_led.x * 255) << 16) & 0xFF0000) | 
                    (((uint32_t)(new_led.y * 255) << 8)  & 0x00FF00) | 
                    (((uint32_t)(new_led.z * 255))       & 0x0000FF);

/*
        t = ((double) (xTaskGetTickCount()+2000)/ 1500);
        E_MATH_CalculateSplinePoint(&green_blue_bounce, t, &new_led);

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

        pattern2 =   (((uint32_t)(new_led.x * 255) << 16) & 0xFF0000) | 
                    (((uint32_t)(new_led.y * 255) << 8)  & 0x00FF00) | 
                    (((uint32_t)(new_led.z * 255))       & 0x0000FF);*/

        write_led_value_over_pwm(pattern1);
        vTaskDelay(pdMS_TO_TICKS(20)); 
    }
}

void write_led_value_over_pwm(uint32_t value)
{
    Pwm * pwm = PWM0;
	
	// Reverse the value for quicker computation
	uint32_t value_reversed = 0;
	for (int i = 0; i < 24; i++){
		value_reversed = value_reversed << 1;
		
		value_reversed |= (value & 0x01);
		
		value = value >> 1;
	}

    int short_period = 30;
    int long_period = 90;
	taskENTER_CRITICAL();
	

    // Start by setting the duty cycle to 0 so that the first cycle
    // doesn't count as a bit
    pwm->PWM_CH_NUM[3].PWM_CDTY = 0;
	pwm->PWM_CH_NUM[3].PWM_CDTYUPD = 0;
	
    // Force a read to clear the bit
    volatile int temp;
    temp = pwm->PWM_ISR1 & PWM_ISR1_CHID3;
	 
    // Enable the channel
    pwm->PWM_ENA = PWM_ENA_CHID3;
    // Wait for 24 interrupts
    for (int i = 0; i < 24; i ++)
    {
        // Load the next value while we wait
		if ((value_reversed & 0x01) > 0)
        {
            pwm->PWM_CH_NUM[3].PWM_CDTYUPD = long_period;
        }
        else
        {
            pwm->PWM_CH_NUM[3].PWM_CDTYUPD = short_period;
        }
        value_reversed = value_reversed >> 1;

        // And wait
        while ((pwm->PWM_ISR1 & PWM_ISR1_CHID3) == 0);
    }
    pwm->PWM_DIS = PWM_ENA_CHID3;
	pwm->PWM_CH_NUM[3].PWM_CDTY = 0;
	pwm->PWM_CH_NUM[3].PWM_CDTYUPD = 0;

	taskEXIT_CRITICAL();
}
