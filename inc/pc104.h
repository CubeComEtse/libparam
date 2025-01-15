/*
 * pc104.h
 *
 * Created: 2024/12/13 07:47:07
 *  Author: Kolijn
 */ 


#ifndef PC104_H_
#define PC104_H_

#include <stdbool.h>
#include <stdint.h>

typedef void (*set_pin_function_t)(uint32_t * pin, bool dir);

typedef struct {
	set_pin_function_t set_pin;
	uint32_t ena_Pin;
	uint32_t nrst_Pin;
} pc104_t;

void PC104_setEnaPin(pc104_t * handle, bool value);
void PC104_setnRstPin(pc104_t * handle, bool value);


#endif /* PC104_H_ */