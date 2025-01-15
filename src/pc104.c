/*
 * pc104.c
 *
 * Created: 2024/10/03 18:40:08
 *  Author: Kolijn
 */ 

#include "pc104.h"

#include "stddef.h"


void PC104_setEnaPin(pc104_t * handle, bool value)
{
	if (handle->set_pin != NULL){
		handle->set_pin(handle->ena_Pin, value);
	}
}

void PC104_setnRstPin(pc104_t * handle, bool value)
{
	if (handle->set_pin != NULL){
		handle->set_pin(handle->nrst_Pin, value);
	}
}
