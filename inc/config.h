
#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdbool.h>
#include <stdint.h>

/*
    Testing point to test if the device is responding.
*/

#define CONF_TEST               0x00

/*
    Configure power supply

    This command enables the power rails to the PC104 header. Each rail can be
    individually enabled or disabled. To send the command, send the CONF_POWER
    byte, followed by a read or write byte. It writing, the next byte should
    contain flags, one for each power rail.
    CONF_POWER, WRITE, 0x00, CONF_POWER_5V_FLAG | CONF_POWER_VBAT_FLAG
*/
#define CONF_POWER              0x01

#define CONF_POWER_5V_FLAG      0x01
#define CONF_POWER_3V3_FLAG     0x02
#define CONF_POWER_VBAT_FLAG    0x04
#define CONF_POWER_VBATALT_FLAG 0x08 

/*
    Power Measurements

    Set which measurements to send to the PC. These are measured and sent at a
    regular interval. Read from this address to see which are set

    CONF_MEASURE, WRITE, CONF_MEASURE_VOLTAGE | CONF_MEASURE_CURRENT | CONF_MEASURE_POWER

*/
#define CONF_MEASURE            0x02

#define CONF_MEASURE_VOLTAGE    (1<<0)
#define CONF_MEASURE_CURRENT    (1<<1)
#define CONF_MEASURE_POWER      (1<<2)


/*
    Supported Boards

    Read this value to receive a list of supported boards
*/
#define CONF_SUPPORTED_BOARDS   0x03

/*
    Configure board

    Write to this address to configure a board. The first byte is register 
    address, write_byte, followed by an index, as per the previous register
    The rest of the data will be passed on to the board
*/
#define CONF_BOARD_SET          0x04

#define CONF_BOARD_NONE         0
#define CONF_BOARD_XTX          1
#define CONF_BOARD_XSTEER       2
#define CONF_BOARD_XDC          4
#define CONF_BOARD_HDRTX_DFA	8


/*
    Transmit measured values to PC

    These addresses are used to send values to the PC. 8 Bytes are send for 
    current and voltage, 16 bytes for power.

    CONF_READ_POWER, 8 Bytes 
*/
#define CONF_READ_POWER         0x05
#define CONF_READ_VOLTAGE       0x06
#define CONF_READ_CURRENT       0x07

#define CONF_READ_VERSION       0x08

void CONFIG_vInit(uint8_t endpoint);
bool CONFIG_bConfigEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);
void CONFIG_vDecodePower(const uint8_t value);
uint8_t CONFIG_vDecodeBoardSet(const uint8_t rw, const uint8_t value);
void CONFIG_vProcess(void);
uint8_t CONFIG_GetCurrentBoardconfig(void);

#endif /* CONFIG_H_ */