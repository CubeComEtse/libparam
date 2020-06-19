/*
 * The config endpoint is responsible for all the obc-controller settings.
 * It will report which boards are supported, and provide and interface to 
 * enable and measure power to the board.
 */ 

 // config endpoint
 // First byte - What to set

 // 

#include "config.h"
#include "bsp.h"
#include "ltc2992.h"
#include <stdbool.h>
#include <stdint.h>
#include "xtx.h"

// Local Variables
static struct ltc2992_device power_measure_1;
static struct ltc2992_device power_measure_2;
static uint8_t currentBoardConfig = 0;

// Local functions
uint8_t CONFIG_vDecodePower(const uint8_t rw, const uint8_t value, const uint8_t* data);
uint8_t CONFIG_vDecodeSupportedBoards(const uint8_t rw, const uint8_t value, const uint8_t* data);
uint8_t CONFIG_vDecodeBoardSet(const uint8_t rw, const uint8_t value, const uint8_t* data);
void CONFIG_vGetPowerMeasurement(uint8_t* tx_buffer, uint16_t* tx_length);
void CONFIG_vGetVoltageMeasurements(uint8_t* tx_buffer, uint16_t* tx_length);

/**
 * \brief Sets up the board to its default state
 */
void CONFIG_vInit(void) {

    LTC2992_vNormalSetup(&power_measure_1, LTC2992_u8GenAddr(0, 0));
    LTC2992_vNormalSetup(&power_measure_2, LTC2992_u8GenAddr(0, 2));

    //Setup functions for LTC2992
    power_measure_1.i2c_write_function = BSP_vPowerSenseWriteFunction;
    power_measure_1.i2c_read_function = BSP_vPowerSenseReadFunction;

    power_measure_2.i2c_write_function = BSP_vPowerSenseWriteFunction;
    power_measure_2.i2c_read_function = BSP_vPowerSenseReadFunction;

}

bool CONFIG_bConfigEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length)
{
    bool returnTransmit = false;
    *tx_length = 0;

    // Send message back with first byte set to header
    tx_buffer[0] = rx_buffer[REG_ADDR];
    switch(rx_buffer[REG_ADDR]) {
        case CONF_POWER:
            CONFIG_vDecodePower(rx_buffer[RW_ADDR], rx_buffer[VALUE_ADDR], &rx_buffer[DATA_ADDR]);
            break;
        case CONF_MEASURE:
            break;
        case CONF_SUPPORTED_BOARDS:
            CONFIG_vDecodeSupportedBoards(rx_buffer[RW_ADDR], rx_buffer[VALUE_ADDR], &rx_buffer[DATA_ADDR]);
            break;
        case CONF_BOARD_SET:
            CONFIG_vDecodeBoardSet(rx_buffer[RW_ADDR], rx_buffer[VALUE_ADDR], &rx_buffer[DATA_ADDR]);
            break;
        case CONF_READ_POWER:
            CONFIG_vGetPowerMeasurement(&tx_buffer[1], tx_length);
            *tx_length += 1;
            returnTransmit = true;
            break;
        case CONF_READ_VOLTAGE:
            CONFIG_vGetVoltageMeasurements(&tx_buffer[1], tx_length);
            *tx_length += 1;
            returnTransmit = true;
            break;
        default:
            break;
    }

    return returnTransmit;
}


/**
 * \brief Decode a power message from the controller
 * 
 * \param rw    CONF_READ of CONF_WRITE
 * \param value The new value, a bitfield
 * \param data  Unused
 * 
 * \return uint8_t The current on power rails
 */
uint8_t CONFIG_vDecodePower(const uint8_t rw, const uint8_t value, const uint8_t* data) {
    if (CONF_WRITE == rw) {
        BSP_vSetPowerEn(EN_5V_BUS, (value & CONF_POWER_5V_FLAG) > 0 );
        BSP_vSetPowerEn(EN_3V3_BUS, (value & CONF_POWER_3V3_FLAG) > 0 );
        BSP_vSetPowerEn(EN_VBAT_BUS, (value & CONF_POWER_VBAT_FLAG) > 0 );
        BSP_vSetPowerEn(EN_VBATALT_BUS, (value & CONF_POWER_VBATALT_FLAG) > 0 );
        return 0;
    }

    return value;
}

/**
 * \brief List the supported boards
 * 
 * \param rw    Unused
 * \param value Unused
 * \param data  Unused
 * 
 * \return uint8_t
 */
uint8_t CONFIG_vDecodeSupportedBoards(const uint8_t rw, const uint8_t value, const uint8_t* data) {
    return CONF_BOARD_BITFIELD;
}


/**
 * \brief Configure the obc controller for a new board
 * 
 * \param rw    No Effect
 * \param value The new board
 * \param data  Data string for the board configuration
 * 
 * \return void
 */
uint8_t CONFIG_vDecodeBoardSet(const uint8_t rw, const uint8_t value, const uint8_t* data)
{
    if (currentBoardConfig != 0) {
        //De-configure previous board
        switch (currentBoardConfig) {
        case CONF_BOARD_XTX:
            XTX_vDeConfig();
        }
    }

    // Just set the newBoard
    switch (value) {
    case  CONF_BOARD_NONE:
        break;
    case CONF_BOARD_XTX:
        XTX_vConfig();
    }
    currentBoardConfig = value;
    return 0;
}

/**
 * \brief Read the LTC2992 Power measurements, and return them
 * 
 * \param tx_buffer     Buffer in which the values will be stored
 * \param tx_length     Length of the final
 * 
 * \return void
 */
void CONFIG_vGetPowerMeasurement(uint8_t* tx_buffer, uint16_t* tx_length){
    uint32_t power1 =0;
    uint32_t power2 = 0;

    LTC2992_vReadPower(&power_measure_1, &power1, &power2);
    tx_buffer[0] = 0xFF & (power1);
    tx_buffer[1] = 0xFF & (power1 >> 8);
    tx_buffer[2] = 0xFF & (power1 >> 16);
    tx_buffer[3] = 0xFF & (power1 >> 24);

    tx_buffer[4] = 0xFF & (power2);
    tx_buffer[5] = 0xFF & (power2 >> 8);
    tx_buffer[6] = 0xFF & (power2 >> 16);
    tx_buffer[7] = 0xFF & (power2 >> 24);

    power1 = 0;
    power2 = 0;
    LTC2992_vReadPower(&power_measure_2, &power1, &power2);
    tx_buffer[8] = 0xFF & (power1);
    tx_buffer[9] = 0xFF & (power1 >> 8);
    tx_buffer[10] = 0xFF & (power1 >> 16);
    tx_buffer[11] = 0xFF & (power1 >> 24);

    tx_buffer[12] = 0xFF & (power2);
    tx_buffer[13] = 0xFF & (power2 >> 8);
    tx_buffer[14] = 0xFF & (power2 >> 16);
    tx_buffer[15] = 0xFF & (power2 >> 24);

    *tx_length = 16;
}

void CONFIG_vGetVoltageMeasurements(uint8_t* tx_buffer, uint16_t* tx_length) {
    uint16_t voltage1 = 0;
    uint16_t voltage2 = 0;

    LTC2992_vReadVoltage(&power_measure_1, &voltage1, &voltage2);
    tx_buffer[0] = 0xFF & (voltage1);
    tx_buffer[1] = 0xFF & (voltage1 >> 8);
    tx_buffer[2] = 0xFF & (voltage2);
    tx_buffer[3] = 0xFF & (voltage2 >> 8);

    LTC2992_vReadVoltage(&power_measure_2, &voltage1, &voltage2);
    tx_buffer[4] = 0xFF & (voltage1);
    tx_buffer[5] = 0xFF & (voltage1 >> 8);
    tx_buffer[6] = 0xFF & (voltage2);
    tx_buffer[7] = 0xFF & (voltage2 >> 8);

    *tx_length = 8;
}