/*
 * The config endpoint is responsible for all the obc-controller settings.
 * It will report which boards are supported, and provide and interface to 
 * enable and measure power to the board.
 */ 
 
#include <stdbool.h>
#include <stdint.h>

#include "config.h"
#include "bsp.h"
#include "ltc2992.h"
#include "serial_multiplexer.h"
#include "std_message.h"
#include "tmr.h"
#include "xtx.h"

// Local Variables
static struct ltc2992_device power_measure_1;
static struct ltc2992_device power_measure_2;
static uint8_t currentBoardConfig = 0;
static uint8_t u8BoardEndpoint;

// Current power line configuration
static uint8_t u8PowerConfig;

// Sets what values to sample and send to the PC
static uint u8PowerMeasureConfig = 0;
// Struct to keep track of the timer
static tmr_t sUpdateTimer;
// Set the interval to sample with - in milliseconds
static uint16_t u16PowerMeasurementInterval = 250;


// Local functions
void CONFIG_vDecodePower(const uint8_t value);
uint8_t CONFIG_vDecodeBoardSet(const uint8_t rw, const uint8_t value);
void CONFIG_vGetPowerMeasurements(uint8_t* tx_buffer, uint16_t* tx_length);
void CONFIG_vGetVoltageMeasurements(uint8_t* tx_buffer, uint16_t* tx_length);
void CONFIG_vGetCurrentMeasurements(uint8_t* tx_buffer, uint16_t* tx_length);

/**
 * \brief Sets up the board to its default state
 */
void CONFIG_vInit(uint8_t endpoint) {

    u8BoardEndpoint = endpoint;

    LTC2992_vNormalSetup(&power_measure_1, LTC2992_u8GenAddr(0, 0));
    LTC2992_vNormalSetup(&power_measure_2, LTC2992_u8GenAddr(0, 2));

    //The LTC2992's are independant of i2c functions, so setup them
    power_measure_1.i2c_write_function = BSP_vPowerSenseWriteFunction;
    power_measure_1.i2c_read_function = BSP_vPowerSenseReadFunction;
    power_measure_2.i2c_write_function = BSP_vPowerSenseWriteFunction;
    power_measure_2.i2c_read_function = BSP_vPowerSenseReadFunction;

    TMR_vInit(&sUpdateTimer, BSP_u16TmrGetTick, 1);
    TMR_vStart(&sUpdateTimer, u16PowerMeasurementInterval);
}

/**
 * \brief Decode message from UART, and execute the action.
 * 
 * \param rx_buffer Buffer of received data
 * \param rx_length Length of the data
 * \param tx_buffer Buffer to retransmit.
 * \param tx_length Length to retransmit.
 * 
 * \return bool
 */
bool CONFIG_bConfigEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length)
{
    // Send message back with first byte set to header
    if (rx_buffer[DIR_idx] == WRITE) {
        switch(rx_buffer[ADDR_idx]) {
        case CONF_POWER:
            CONFIG_vDecodePower(rx_buffer[DATA_idx]);
            break;
        case CONF_MEASURE:
            u8PowerMeasureConfig = rx_buffer[DATA_idx];
            break;
        case CONF_BOARD_SET:
            CONFIG_vDecodeBoardSet(rx_buffer[DIR_idx], rx_buffer[DATA_idx]);
            break;
        default:
            break;
        }
        return false;
    } else {
        // A Read!
        tx_buffer[ADDR_idx] = rx_buffer[ADDR_idx];
        tx_buffer[DIR_idx] = rx_buffer[DIR_idx];
        *tx_length = 4;
        switch (rx_buffer[ADDR_idx]) {
        case CONF_TEST:
            tx_buffer[LEN_idx] = 0;
            *tx_length = 3;
            break;
        case CONF_POWER:
            tx_buffer[LEN_idx] = 1;
            tx_buffer[DATA_idx] = u8PowerConfig;
            break;
        case CONF_MEASURE:
            tx_buffer[LEN_idx] = 1;
            tx_buffer[DATA_idx] = u8PowerMeasureConfig;
            break;
        }
        return true;
    }
}

/**
 * \brief Call this function regularly, it will check if power/ voltage
 * values need to be send to the board
 * 
 * \return void
 */
void CONFIG_vProcess(void) {
    if (TMR_bExpired(&sUpdateTimer)) {
        // Max require length is 16+1 for power measurements
        uint8_t tx_buffer[20];
        uint16_t tx_length;

        tx_buffer[DIR_idx] = READ;
        tx_buffer[LEN_idx] = 2;

        if (u8PowerMeasureConfig & CONF_MEASURE_VOLTAGE) {
            // Measurements, send values
            CONFIG_vGetVoltageMeasurements(&tx_buffer[DATA_idx], &tx_length);
            tx_buffer[ADDR_idx] = CONF_READ_VOLTAGE;
            tx_buffer[LEN_idx] = tx_length;
            // Todo: Refactor 2 to be BOARD_ENDPOINT
            SERMUX_vTransmit(2, tx_buffer, tx_length+3);
        }

        if (u8PowerMeasureConfig & CONF_MEASURE_CURRENT) {
            // Measurements, send values
            CONFIG_vGetCurrentMeasurements(&tx_buffer[DATA_idx], &tx_length);
            tx_buffer[ADDR_idx] = CONF_READ_CURRENT;
            tx_buffer[LEN_idx] = tx_length;
            // Todo: Refactor 2 to be BOARD_ENDPOINT
            SERMUX_vTransmit(2, tx_buffer, tx_length+3);
        }

        if (u8PowerMeasureConfig & CONF_MEASURE_POWER) {
            // Measurements, send values
            CONFIG_vGetPowerMeasurements(&tx_buffer[DATA_idx], &tx_length);
            tx_buffer[ADDR_idx] = CONF_READ_POWER;
            tx_buffer[LEN_idx] = tx_length;
            // Todo: Refactor 2 to be BOARD_ENDPOINT
            SERMUX_vTransmit(2, tx_buffer, tx_length+3);
        }
        // Restart timer
        TMR_vStart(&sUpdateTimer, u16PowerMeasurementInterval);
    }
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
void CONFIG_vDecodePower(const uint8_t value) {
    u8PowerConfig = value;

    BSP_vSetPowerEn(EN_5V_BUS, (value & CONF_POWER_5V_FLAG) > 0 );
    BSP_vSetPowerEn(EN_3V3_BUS, (value & CONF_POWER_3V3_FLAG) > 0 );
    BSP_vSetPowerEn(EN_VBAT_BUS, (value & CONF_POWER_VBAT_FLAG) > 0 );
    BSP_vSetPowerEn(EN_VBATALT_BUS, (value & CONF_POWER_VBATALT_FLAG) > 0 );
}

/**
 * \brief Configure the obc controller for a new board
 * 
 * \param rw    No Effect
 * \param value The new board
 * 
 * \return void
 */
uint8_t CONFIG_vDecodeBoardSet(const uint8_t rw, const uint8_t value)
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
void CONFIG_vGetPowerMeasurements(uint8_t* tx_buffer, uint16_t* tx_length){
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

void CONFIG_vGetCurrentMeasurements(uint8_t* tx_buffer, uint16_t* tx_length) {
    uint16_t current1 = 0;
    uint16_t current2 = 0;

    LTC2992_vReadCurrent(&power_measure_1, &current1, &current2);
    tx_buffer[0] = 0xFF & (current1);
    tx_buffer[1] = 0xFF & (current1 >> 8);
    tx_buffer[2] = 0xFF & (current2);
    tx_buffer[3] = 0xFF & (current2 >> 8);

    LTC2992_vReadCurrent(&power_measure_2, &current1, &current2);
    tx_buffer[4] = 0xFF & (current1);
    tx_buffer[5] = 0xFF & (current1 >> 8);
    tx_buffer[6] = 0xFF & (current2);
    tx_buffer[7] = 0xFF & (current2 >> 8);

    *tx_length = 8;
}
