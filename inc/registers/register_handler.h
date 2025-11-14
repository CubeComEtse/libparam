/*
 * register_handler.h
 *
 * Created: 2021/08/03 14:34:22
 *  Author: Kolijn
 */ 

#ifndef REGISTER_HANDLER_H_
#define REGISTER_HANDLER_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "register_map.h"
#include "platform.h"

void REG_vSetPlatformPointer(platform_t * handle, bsp_t * bsp_handle);
bool REG_CheckAddress(const uint16_t address);

bool REG_ReadFromAddress(const uint16_t address, uint8_t * buff);
bool REG_WriteToAddress(const uint16_t address, const uint8_t * data);

// These functions are used by the libparam parameter system
void REG_vReadFromAddress(const uint16_t address, void * value);
void REG_vWriteToAddress(const uint16_t address, const void * value);

#endif /* REGISTER_HANDLER_H_ */