/*
 * event.h
 *
 * Created: 2022/06/23 20:34:14
 *  Author: Kolijn
 */ 


#ifndef EVENT_H_
#define EVENT_H_

#include <stdint.h>

#define EVENT_SECTION_I2C               10
#define EVENT_SECTION_MULTI             11

#define MULTITESTER_DID_NOT_RESPOND     2

typedef struct event_s
{
    uint8_t section;            // Section will be I2C, GPIO, etc.
    uint8_t detail;             // Details are left to the section self. This explains what type of event it was.
    uint32_t timestamp;         // Timestamp is added automatically
} event_t;

void EVENT_AddEvent(uint8_t section, uint8_t detail);

/*
* Returns the number of events in the current buffer
*/
uint16_t EVENT_EventCount(void);

void EVENT_GetEvent(event_t * dest);

#endif /* EVENT_H_ */