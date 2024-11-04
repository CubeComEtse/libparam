#include <stdint.h>
#include <stdbool.h>
#include "string.h"

#include <asf.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>

#include "bsp.h"
#include "register_handler.h"
#include "ltc2499.h"
#include "ltc2992.h"
#include "gse_manager.h"
#include "sermux_v3.h"
#include "pc_messages.h"
#include "led_driver.h"

#include "can_target.h"
#include "i2c_target.h"
#include "local_target.h"


static ltc2992_device_t power_measure_1;
static ltc2992_device_t power_measure_2;
static ltc2499_device_t cs_board;

static gse_manager_t gse_manager;

static local_target_t local_target;
static i2c_target_t i2c_target;
static can_target_t can_target;

sermux_v3_t sermux_v3;
static bsp_t bsp;

void uart_test_Task(void * handle);

StackType_t exampleTaskStack[512] = {0};
StaticTask_t sermux_task;

int main (void)
{
    // Board initialization
    BSP_Init(&bsp);
	
	//Initialize memory map
    mm_init();
	
	// Initialize register map
	REG_vInit();
	
	// NEW! IMPROVED! SHINY!
	
	LED_DRIVER_Setup();
	
	//The LTC2992's are independent of i2c functions, so setup them
	power_measure_1.i2c_write_function = ccd_i2c_driver_Write;
	power_measure_1.i2c_read_function = ccd_i2c_driver_Read;
	power_measure_1.i2c_handle = bsp.local_i2c;
	power_measure_2.i2c_write_function = ccd_i2c_driver_Write;
	power_measure_2.i2c_read_function = ccd_i2c_driver_Read;
	power_measure_1.i2c_handle = bsp.local_i2c;
	
	// Todo: This all depends on the type of board this code is for
	// LTC2992_vNormalSetup(&power_measure_1, LTC2992_u8GenAddr(0, 0));
	// LTC2992_vNormalSetup(&power_measure_2, LTC2992_u8GenAddr(0, 2));
	
	cs_board.i2c_read_function = ccd_i2c_driver_Read;
	cs_board.i2c_write_function = ccd_i2c_driver_Write;
	LTC2499_vInit(&cs_board);
		
	gse_manager.power_measure_1  = &power_measure_1;
	gse_manager.power_measure_2 = &power_measure_2;
	gse_manager.cs_board = &cs_board;
	GSE_MANAGER_Init(&gse_manager);
	
	LOCALTARGET_Init(&local_target);

	i2c_target.i2c_read = ccd_i2c_driver_Read;
	i2c_target.i2c_write = ccd_i2c_driver_Write;
	i2c_target.i2c_handle = bsp.bus_i2c;
	I2CTARGET_Init(&i2c_target);
	
	can_target.can_send = ccd_can_Send_message;
	CANTARGET_Init(&can_target);
	
	
	sermux_v3.in_stream = bsp.telemetry_uart->uart_rx_buffer;
	sermux_v3.out_stream = bsp.telemetry_uart->uart_tx_buffer;
	SERMUX_V3_Init(&sermux_v3);

	//Add Local Targets
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_GSE, local_target.incoming_messages, local_target.outgoing_messages);
	
	// Add I2C Targets
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_I2C_CC, i2c_target.incoming_messages, i2c_target.outgoing_messages);
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_I2C_CC_CHECKSUM, i2c_target.incoming_messages, i2c_target.outgoing_messages);
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_I2C_CC_2, i2c_target.incoming_messages, i2c_target.outgoing_messages);
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_I2C_CC_3, i2c_target.incoming_messages, i2c_target.outgoing_messages);

	// Add CAN Targets
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_I2C_CC, can_target.incoming_messages, can_target.outgoing_messages);
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_I2C_CC_CHECKSUM, can_target.incoming_messages, can_target.outgoing_messages);
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_I2C_CC_2, can_target.incoming_messages, can_target.outgoing_messages);
	

	//xTaskCreate(GSE_MANAGER_Task, "GSE Manager", 1024, (void*) &gse_manager, tskIDLE_PRIORITY + 1, NULL );
	
	xTaskCreate(SERMUX_V3_ReceiveTask, "Serial MUX RX", 512, (void*) &sermux_v3, tskIDLE_PRIORITY+4, NULL);
	xTaskCreate(SERMUX_V3_TransmitTask, "Serial MUX TX", 512, (void*) &sermux_v3, tskIDLE_PRIORITY+4, NULL);
	
	//xTaskCreate(I2CTARGET_Task, "I2C Target", 512, (void*) &i2c_target,  tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(LOCALTARGET_Task, "Local Target", 512, (void*) &local_target,  tskIDLE_PRIORITY+3, NULL);
	
	// High priority for this, to always keep the RX buffer empty and not loose data.
	xTaskCreate(ccd_usart_RXProcessingTask, "UART RX", 512, (void*) bsp.telemetry_uart, tskIDLE_PRIORITY + 4, &(bsp.telemetry_uart->task_reference));
	xTaskCreate(ccd_usart_TXProcessingTask, "UART TX", 512, (void*) bsp.telemetry_uart, tskIDLE_PRIORITY + 4, NULL);
	
	// LED task has lowest priority
	// xTaskCreate(LED_DRIVER_UpdateTask, "LED", 512, (void*) NULL, tskIDLE_PRIORITY, NULL);
	
	vTaskStartScheduler();
	
	//Todo: Reboot!
	while(1);
	
	// Might be needed:
	// BSP_vTelemetrySetCTS(false);
	







}


void vApplicationStackOverflowHook( TaskHandle_t xTask,char * pcTaskName )
{
    // Check pcTaskName for the name of the offending task,
	// or pxCurrentTCB if pcTaskName has itself been corrupted. 
    ( void ) xTask;
    ( void ) pcTaskName;
}

void vApplicationMallocFailedHook(void){
	while(1){
		
	}
}

void vApplicationTickHook(void){
}