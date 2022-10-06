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

typedef enum channel{
	Position1 = 1,
	Position2 = 2,
	Position3 = 3,
	Position4 = 4
} channel_id_t;


bool MULTI_vInit(void);
void MULTI_vDeinit(void);

void MULTI_vProcess(void);
/*
 * Setting/Clear of the individual bits
*/
void MULTI_vSetChannelEnabled(channel_id_t channel, bool ena);
void MULTI_vSetChannelPowerPins(const uint16_t pins);
void MULTI_vSetChannelnReset(channel_id_t channel, bool ena);
void MULTI_vSetChannelFan(channel_id_t channel, bool ena);
bool MULTI_bGetChannelFan(const channel_id_t channel);

/*
 * Enabled the multitester
*/
void MULTI_vSetEnabled(const bool ena);
bool MULTI_bGetEnabled(void);

void MULTI_vSetAutoClear(bool ena);
bool MULTI_bGetAutoClear(void);

uint32_t MULTI_u32GetPins(void);

bool MULTI_bGetRfSwitchEnabled(void);
void MULTI_vSetRfSwitchEnabled(bool value);
uint8_t MULTI_u8GetRFSwitchChannel(void);
void MULTI_vSetRFSwitchChannel(uint8_t channel);

#endif /* MULTITESTER_H_ */