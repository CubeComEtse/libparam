/*
 * crc8.c
 *
 * Created: 2025/07/24 16:29:24
 *  Author: Kolijn
 */ 

#include "crc8.h"

/*
	Initialize the CRC module, calculating the array for easy computation
*/
void CRC8_Initialize(crc_module_t * crc, uint8_t polynomial)
{
	crc->polynomial = polynomial;
	
	for (int i = 0; i < 256; i++)
	{
		crc->table[i] = i;
	}
	
    for (int i = 0; i < 256; i++)
    {
	    for (int j = 7; j >= 0; j--)
	    {
		    uint8_t temp = crc->table[i] & 0x80;

			crc->table[i] = crc->table[i] << 1;
		    if (temp)
		    {
			    crc->table[i] ^= polynomial;
		    }
	    }
    }
}

uint8_t CRC8_Calculate(crc_module_t * pHandle, uint8_t * buffer, size_t length)
{
	uint16_t crc = 0x0;
	uint16_t index;
	
	for (size_t i = 0; i < length; i ++)
	{
		index = (crc ^ buffer[i]) & 0xFF;
		crc = (pHandle->table[index] ^ (crc << 8)) & 0xFF;
	}

	return crc & 0xFF;
}