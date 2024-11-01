/*
 * local_target.h
 *
 * Created: 2024/10/04 08:29:12
 *  Author: Kolijn
 */ 


#ifndef LOCAL_TARGET_H_
#define LOCAL_TARGET_H_

#include "FreeRTOS.h"
#include "message_buffer.h"

typedef struct {
	MessageBufferHandle_t incoming_messages;
	MessageBufferHandle_t outgoing_messages;
}local_target_t;

void LOCALTARGET_Init(local_target_t * handle);
void LOCALTARGET_Task(void *handle);

#endif /* LOCAL_TARGET_H_ */