/*
 * event.c
 *
 * Created: 2022/06/23 20:31:56
 *  Author: Kolijn
 */ 

#include "event.h"
#include "register_handler.h"
#include "bsp.h"


// 128 * 6 bytes
#define EVENT_BUFFER_SIZE 128
static event_t events[128];
static uint32_t read_index = 0;
static uint32_t write_index = 0;


/*
* Add an event for the given section and detail.
*/
void EVENT_AddEvent(uint8_t section, uint8_t detail){
    events[write_index].section = section;
    events[write_index].detail = detail;
	uint32_t uptime;
	mm_getUptime(&uptime);
	
    uint64_t ts = BSP_u64GetTimestamp() - (1000 * 60 * (uptime / 60));
    events[write_index].timestamp = (uint16_t)ts ;

    write_index = (write_index+1) % EVENT_BUFFER_SIZE;
}

/*
* Returns the number of events in the current buffer
*/
uint16_t EVENT_EventCount(){
    if (write_index >= read_index)
    {
        return write_index-read_index;
    }
    else{
        return EVENT_BUFFER_SIZE + write_index- read_index;
    }
}

void EVENT_GetEvent(event_t * dest){
    if (EVENT_EventCount() == 0){
        return;
    }
    dest->section = events[read_index].section;
    dest->detail = events[read_index].detail;
    dest->timestamp = events[read_index].timestamp;

    read_index += 1;
}

