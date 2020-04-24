/*

 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdbool.h>
#include <stdint.h>

#define CONF_POWER              0x01
// Configure using flags
#define CONF_POWER_5V_FLAG      0x01
#define CONF_POWER_3V3_FLAG     0x02
#define CONF_POWER_VBAT_FLAG    0x04
#define CONF_POWER_VBATALT_FLAG 0x08 

#define CONF_MEASURE            0x02

#define CONF_SPI                0x03

void CONFIG_vInit(void);
bool CONFIG_bConfigEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);

#endif /* CONFIG_H_ */