#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include <stdint.h>

typedef void (*uart_disable_fc_t)(void * handle);
typedef void (*uart_enable_fc_t)(void * handle);

typedef struct {
	uart_disable_fc_t uart_disable_fc;
	uart_enable_fc_t uart_enable_fc;
	void * uart_handle;
} led_driver_t;

#ifdef __cplusplus
extern "C" {
#endif

void LED_DRIVER_Setup(led_driver_t * handle);
void LED_DRIVER_UpdateTask(void * parameters);

void write_led_value_over_pwm(led_driver_t * handle, uint32_t value);

#ifdef __cplusplus
}
#endif

#endif /* LED_DRIVER_H_ */