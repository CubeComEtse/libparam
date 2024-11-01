/*
 * Multitester.h
 *
 * Created: 2022/08/15 15:42:14
 *  Author: Kolijn
 */ 

#ifndef MULTITESTER_H_
#define MULTITESTER_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
	bool (*i2c_write_function)(void * handle, const uint8_t dev_addr, const uint8_t * data, const size_t data_len);
	bool (*i2c_read_function)(void * handle, const uint8_t dev_addr, const uint8_t * addr, const size_t addr_len, uint8_t * read_buffer, size_t read_len);
	void * i2c_handle;
} multitester_t;

typedef enum channel{
	Position1 = 1,
	Position2 = 2,
	Position3 = 3,
	Position4 = 4
} channel_id_t;


bool MULTI_vInit(multitester_t * handle);
void MULTI_vDeinit(multitester_t * handle);
void MULTI_vProcess(multitester_t * handle);
/*
 * Setting/Clear of the individual bits
*/
void MULTI_vSetChannelEnabled(multitester_t * handle, channel_id_t channel, bool ena);
void MULTI_vSetChannelPowerPins(multitester_t * handle, const uint16_t pins);
void MULTI_vSetChannelnReset(multitester_t * handle, channel_id_t channel, bool ena);
void MULTI_vSetChannelFan(multitester_t * handle, channel_id_t channel, bool ena);
bool MULTI_bGetChannelFan(multitester_t * handle, const channel_id_t channel);

/*
 * Enabled the multitester
*/
void MULTI_vSetEnabled(multitester_t * handle, const bool ena);
bool MULTI_bGetEnabled(multitester_t * handle);

void MULTI_vSetAutoClear(multitester_t * handle, bool ena);
bool MULTI_bGetAutoClear(multitester_t * handle);

uint32_t MULTI_u32GetPins(multitester_t * handle);

bool MULTI_bGetRfSwitchEnabled(multitester_t * handle);
void MULTI_vSetRfSwitchEnabled(multitester_t * handle, bool value);
uint8_t MULTI_u8GetRFSwitchChannel(multitester_t * handle);
void MULTI_vSetRFSwitchChannel(multitester_t * handle, uint8_t channel);

#endif /* MULTITESTER_H_ */