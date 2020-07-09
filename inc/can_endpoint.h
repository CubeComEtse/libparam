/*
 * can_endpoint.h
 *
 * Created: 2020/06/26 12:38:39
 *  Author: Kolijn
 */ 


#ifndef CAN_ENDPOINT_H_
#define CAN_ENDPOINT_H_

#include <stdint.h>
#include <stdbool.h>

void can_endpoint_init(void);
void can_endpoint_process(void);
bool can_endpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);

#endif /* CAN_ENDPOINT_H_ */