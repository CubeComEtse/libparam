/*
 * ltc2992.h
 *
 * Created: 2020/04/23 09:21:26
 *  Author: Kolijn
 */ 

#ifndef LTC2992_H_
#define LTC2992_H_

#include <stdint.h>
#include <stdbool.h>


struct ltc2992_device {
    uint8_t i2c_bus_addres;
    void (*i2c_write_function)(const uint8_t chip_addr, const uint8_t mem_address, const uint8_t* tx_buffer, const uint16_t length);
    void (*i2c_read_function)(const uint8_t chip_addr, const uint8_t mem_address, uint8_t* rx_buffer, uint16_t length);
};

/**
 * \brief Setup the device normally, storing values in the provided struct.
 * 
 * \param dev           Pointer to a ltc2992_device struct
 * \param bus_address   The address on the i2c bus. See LTC2992_u8GenAddr to generate this 
 * 
 * \return void
 */
void LTC2992_vNormalSetup(struct ltc2992_device* dev, uint8_t bus_address);

/**
 * \brief Generate the bus address, given the pin configurations
 * 
 * \param adr0 0 - tied to ground, 1 - high, 2 - floating
 * \param adr1 0 - tied to ground, 1 - high, 2 - floating
 * 
 * \return uint8_t
 */
uint8_t LTC2992_u8GenAddr(uint8_t adr0, uint8_t adr1);

uint8_t LTC2992_vGetRegister(struct ltc2992_device* dev, uint8_t register_address);
void LTC2992_vSetRegister(struct ltc2992_device* dev, uint8_t register_address, uint8_t flags);

void LTC2992_vReadPower(struct ltc2992_device* dev, uint32_t* power_1, uint32_t* power_2);
void LTC2992_vReadVoltage(struct ltc2992_device* dev, uint16_t* voltage_1, uint16_t* voltage_2);

#define LTC2992_CTRLA               0x00
#define LTC2992_CTRLB               0x01
#define LTC2992_ALERT1              0x02
#define LTC2992_FAULT1              0x03
#define LTC2992_NADC                0x04
#define LTC2992_P1                  0x05
#define LTC2992_P1_MAX              0x08
#define LTC2992_P1_MIN              0x0B
#define LTC2992_P1_MAX_THRESHOLD    0x0E
#define LTC2992_P1_MIN_THRESHOLD    0x11
#define LTC2992_I1                  0x14
#define LTC2992_I1_MAX              0x16
#define LTC2992_I1_MIN              0x18
#define LTC2992_I1_MAX_THRESHOLD    0x1A
#define LTC2992_I1_MIN_THRESHOLD    0x1C
#define LTC2992_G1                  0x28

#define CTRLA_CALIBRATE_ON_DEMAND   (0b1<<7)
#define CTRLA_CALIBRATE_EVERY_CONV  (0b0<<7)

#define CTRLA_MEASUREMENT_MODE_SHUTDOWN     (0b11 << 5)
#define CTRLA_MEASUREMENT_MODE_SINGLE       (0b10 << 5)
#define CTRLA_MEASUREMENT_MODE_SNAPSHOT     (0b01 << 5)
#define CTRLA_MEASUREMENT_MODE_CONTINUOUS   (0b00 << 5)

#define CTRLA_V_CONT_MODE_GPIOS             (0b10 << 3)
#define CTRLA_V_CONT_MODE_GPIO1_GPIO2       (0b11 << 3)
#define CTRLA_V_CONT_MODE_SENSE             (0b01 << 3)
#define CTRLA_V_CONT_MODE_ALL               (0b00 << 3)

#define CTRLA_V_SNAP_MODE_GPIO1_GPIO2       (0b111)
#define CTRLA_V_SNAP_MODE_SENSE             (0b110)
#define CTRLA_V_SNAP_MODE_GPIO4             (0b101)
#define CTRLA_V_SNAP_MODE_GPIO3             (0b100)
#define CTRLA_V_SNAP_MODE_GPIO2             (0b011)
#define CTRLA_V_SNAP_MODE_GPIO1             (0b010)
#define CTRLA_V_SNAP_MODE_SENSE2            (0b001)
#define CTRLA_V_SNAP_MODE_SENSE1            (0b000)

#define CTRLB_CLEAR_ALERT                   (0b1<<7)
#define CTRLB_COR_CONTROL                   (0b1<<5)
#define CTRLB_STUCK_BUS_TIMEOUT             (0b1<<4)
#define CTRLB_RESET_PEAK_HOLD_VALUES        (0b1<<3)
#define CTRLB_RESET                         (0b1<<0)



#define LTC2992_P2                          0x37
#define LTC2992_G2                          0x5A


#endif /* LTC2992_H_ */