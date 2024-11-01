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

#include "OBC.h"


void REG_vInit(void);

/*
 * Checks if the provided register address is a valid one. Returns true if it 
 * is, false otherwise
*/
bool REG_CheckAddress(const uint8_t address);

/*
Gets the register given by address, copies it's data into the data argument
Returns true if the address is valid, false otherwise.
*/
bool REG_vReadFromAddress(const uint32_t address, uint8_t * buff, uint8_t * size);

/*
 * Process all the stored messages. This function should be called regularly.
*/
void REG_vWriteToAddress(const uint32_t address, const uint8_t * data, const size_t length);





/*
 * Add a flag to the I2C Status. The status can only be appended to, it is cleared when the user 
 * reads it
*/
void REG_vSetI2CStatus(uint32_t flag);

void REG_UpdateTemperature(uint16_t temperature);


void REG_Copyu32ToArray(const uint32_t value, uint8_t* data);


uint8_t REG_GetI2CSpeed(void);
void REG_SetI2CSpeed(uint32_t newSpeed);

uint32_t REG_GetI2CAddress(void);
void REG_vSetI2CAddress(uint8_t address);


#endif /* REGISTER_HANDLER_H_ */