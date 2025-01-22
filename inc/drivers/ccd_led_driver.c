/*
 * ccd_led_driver.c
 *
 * Created: 2025/01/21 08:46:51
 *  Author: Kolijn
 */ 
#include "ccd_led_driver.h"
#include "FreeRTOS.h"
#include "task.h"

void ccd_led_driver_Init(ccd_led_t * driver, Pwm * pwm_instance)
{
	driver->pwm = pwm_instance;

	// Select peripheral clock - 100 Mhz
	driver->pwm->PWM_CLK = PWM_CLK_PREA(PWM_CLK_PREA_CLK) | PWM_CLK_DIVA(1);

	// Channel Mode register:
	// CALG     0   Channel is left aligned
	// CPRE     0   Prescaler is MCK
	// CPOL     0   Output starts low (we use inverted output)
	// DPOL     1   When disabled, output is 1 (inverted output is 0)
	driver->pwm->PWM_CH_NUM[3].PWM_CMR = PWM_CMR_DPOLI;

	// Set to 100 for now - 1 Mhz. Poor LED
	driver->pwm->PWM_CH_NUM[3].PWM_CPRD = 120;
	driver->pwm->PWM_CH_NUM[3].PWM_CDTYUPD = 0;

	// Enable interrupts on the channel
	driver->pwm->PWM_IER1 |= PWM_IER1_CHID3;
}


void ccd_led_driver_SetLed(ccd_led_t * driver, uint8_t r, uint8_t g, uint8_t b){
	Pwm * pwm = PWM0;
	
	uint32_t value = (r << 16) | (g << 8) | (b);
	    
	// Reverse the value for quicker computation
	uint32_t value_reversed = 0;
	for (int i = 0; i < 24; i++){
		value_reversed = value_reversed << 1;
		    
		value_reversed |= (value & 0x01);
		    
		value = value >> 1;
	}

	int short_period = 30;
	int long_period = 90;
	    
	    
	// Hacks: The UART interrupt is very important to respond to, otherwise we miss
	// messages from the PC. It is so important it gets priority above the RTOS.
	// But if it triggers in the middle of an LED update, the LED is borked, and that
	// looks bad, which is somehow even worse. So just for this short while, disable
	// the UART interrupt. By setting flow control.
	    
	if (driver->uart_disable_fc){
		driver->uart_disable_fc(driver->uart_handle);
	}
	    
	taskENTER_CRITICAL();
	__disable_irq();

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

	__enable_irq();
	taskEXIT_CRITICAL();
	    
	if (driver->uart_enable_fc){
		driver->uart_enable_fc(driver->uart_handle);
	}
}
