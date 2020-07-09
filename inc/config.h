/*

 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdbool.h>
#include <stdint.h>

#define REG_ADDR                0
#define RW_ADDR                 1
#define VALUE_ADDR              2
#define DATA_ADDR               3

#define CONF_READ  0x00
#define CONF_WRITE 0x01

/*
    Configure power supply

    This command enables the power rails to the PC104 header. Each rail can be
    individually enabled or disabled. To send the command, send the CONF_POWER
    byte, followed by a read or write byte. It writing, the next byte should
    contain flags, one for each power rail.
    CONF_POWER, WRITE, CONF_POWER_5V_FLAG | CONF_POWER_VBAT_FLAG
*/
#define CONF_POWER              0x01

#define CONF_POWER_5V_FLAG      0x01
#define CONF_POWER_3V3_FLAG     0x02
#define CONF_POWER_VBAT_FLAG    0x04
#define CONF_POWER_VBATALT_FLAG 0x08 

// Set power measurements
// Next flag sets which settings to monitor
#define CONF_MEASURE            0x02

#define CONF_MEASURE_VOLTAGE    (1<<0)
#define CONF_MEASURE_CURRENT    (1<<1)
#define CONF_MEASURE_POWER      (1<<2)

/*
    Supported boards

    Read this register to get supported boards. writing has no effect
*/
#define CONF_SUPPORTED_BOARDS   0x03
#define CONF_BOARD_BITFIELD (1<< CONF_BOARD_XTX)

/*
    Configure board

    Write to this address to configure a board. The first byte is register 
    address, write_byte, followed by an index, as per the previous register
    The rest of the data will be passed on to the board
*/
#define CONF_BOARD_SET          0x04

#define CONF_BOARD_NONE 0
#define CONF_BOARD_XTX 1


/*
    Read power measurements from the LTC2992 ICs
*/
#define CONF_READ_POWER         0x05

/*
    Read voltage measurements from the LTC2992 ICs
*/
#define CONF_READ_VOLTAGE       0x06
#define CONF_READ_CURRENT       0x07


void CONFIG_vInit(void);
void CONFIG_vUpdate(void);
bool CONFIG_bConfigEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);

#endif /* CONFIG_H_ */