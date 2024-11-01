/*
 * ccd_i2c_driver.c
 *
 * Created: 2024/10/04 14:57:52
 *  Author: Kolijn
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "ccd_i2c_driver.h"

#include <asf.h>


void ccd_i2c_driver_Init(ccd_i2c_t * driver, Twihs * instance)
{
	driver->base_twihs = instance;
 
	// Disable interrupts while we setup
	twihs_disable_interrupt(driver->base_twihs, 0xFFFFFFFF);
 
	// Enable Clocks
	if (driver->base_twihs == TWIHS0)
		sysclk_enable_peripheral_clock(ID_TWIHS0);
	if (driver->base_twihs == TWIHS1)
		sysclk_enable_peripheral_clock(ID_TWIHS1);
	if (driver->base_twihs == TWIHS2)
		sysclk_enable_peripheral_clock(ID_TWIHS2);
 
	// Setup
	twihs_options_t i2cOptions;
	i2cOptions.chip = 0x26;
	i2cOptions.smbus = 0;
	i2cOptions.master_clk = sysclk_get_peripheral_hz();
	i2cOptions.speed = 400000;
	twihs_master_init(driver->base_twihs, &i2cOptions);
}

bool ccd_i2c_driver_Write(void * handle, const uint8_t dev_addr, const uint8_t * data, const size_t data_len)
{
	ccd_i2c_t * driver = (ccd_i2c_t *) handle;
	
	twihs_packet_t write_packet;
	write_packet.chip = dev_addr;
	memcpy(write_packet.addr, data, 1);
	write_packet.addr_length = 1;
	write_packet.buffer = &data[1];
	write_packet.length = ((uint32_t) data_len-1);


	uint32_t result = twihs_master_write(driver->base_twihs, &write_packet);
	twihs_read_byte(driver->base_twihs);

	return (result == TWIHS_SUCCESS);
}

bool ccd_i2c_driver_Read(void * handle, const uint8_t dev_addr, const uint8_t * addr, const size_t addr_len, uint8_t * read_buffer, size_t read_len)
{
	ccd_i2c_t * driver = (ccd_i2c_t *) handle;
	
	twihs_packet_t read_packet;
	read_packet.chip = dev_addr;
	memcpy(read_packet.addr, addr, min(addr_len,3));
	read_packet.addr_length = addr_len;
	read_packet.buffer = read_buffer;
	read_packet.length = ((uint32_t) read_len);
	uint32_t result =0;

	result = twihs_master_read(driver->base_twihs, &read_packet);
	

	// Clear buffer
	// twihs_read_byte(drv->p_twihs);

	// Todo: all of this
	/*
	if (result == TWIHS_ERROR_TIMEOUT) {
		ioport_enable_pin(I2C_PC104_SCL_PIN);
		ioport_set_pin_dir(I2C_PC104_SCL_PIN, IOPORT_DIR_OUTPUT);
		
		for (int i = 0; i < 32; i++) {
			ioport_toggle_pin_level(I2C_PC104_SCL_PIN);
			delay_us(50);
		}
		
		ioport_reset_pin_mode(I2C_PC104_SCL_PIN);

		// I2C_DRIVER_vInitPC104(drv, i2c_speed);
	}
	*/

	bool retVal = (result == TWIHS_SUCCESS);

	return retVal;
}
