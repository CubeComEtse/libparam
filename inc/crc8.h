/*
 * crc8.h
 *
 * Created: 2025/07/24 16:49:39
 *  Author: Kolijn
 */ 

#ifndef CRC8_H_
#define CRC8_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
	uint8_t polynomial;
	uint8_t table[256];
} crc_module_t;

void CRC8_Initialize(crc_module_t * crc, uint8_t polynomial);
uint8_t CRC8_Calculate(crc_module_t * crc, uint8_t * buffer, size_t length);

#endif /* CRC8_H_ */
