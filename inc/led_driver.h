#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void LED_DRIVER_Setup(void);
void LED_DRIVER_UpdateTask(void * parameters);

void write_led_value_over_pwm(uint32_t value);

#ifdef __cplusplus
}
#endif

#endif /* LED_DRIVER_H_ */