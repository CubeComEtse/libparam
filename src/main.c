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
#include "platform.h"

#include "register_handler.h"
#include "register_map.h"
#include "ltc2499.h"
#include "ltc2992.h"
#include "gse_manager.h"
#include "sermux_v3.h"
#include "pc_messages.h"
#include "led_driver.h"

#include "can_target.h"
#include "i2c_target.h"
#include "local_target.h"


static bsp_t bsp;
static platform_t * platform;

static void DEVTOOLS_Task(void * handle);
static void SETUP_Task(void* handle);

StackType_t exampleTaskStack[512] = {0};
StaticTask_t sermux_task;

int main (void)
{
    // Board initialization
    BSP_Init(&bsp);
	
	// Platform Initialization
	PLATFORM_vInit(&bsp);
	platform = PLATFORM_get();
	
	//Initialize memory map
	mm_init();
	
	// Configure all external ICs
	PLATFORM_vConfigureAll(platform);
	
	xTaskCreate(SETUP_Task, "Startup", 1024, NULL, tskIDLE_PRIORITY + 1, NULL );
	
	vTaskStartScheduler();
	
	//Todo: Reboot if we get here!
	while(1);
}


static void DEVTOOLS_Task(void * handle){
	platform_t * pHandle = (platform_t *) handle;
	
	while(1){
	
		RFRelay_Process(pHandle->rf_relay_1);
		RFRelay_Process(pHandle->rf_relay_2);
		MULTI_Process(pHandle->multitester);
		
		vTaskDelay(pdMS_TO_TICKS(20));
	}
	
}

/*
 * This function calls all the sub-modules to store their configured values in 
 * the memory map. This is a FreeRTOS task which runs one at startup, then 
 * configures the rest
*/
void SETUP_Task(void* handle)
{
	
	mm_setBoard_ID(0x634F4243);
	mm_setFW_Version(0x00020203);
	mm_setHW_Version_major_version(BSP_u8GetVersion());
	
	mm_setI2CConfA_SPD(40);
	mm_setI2CConfA_WRDEL(platform->i2c_target->write_read_delay);
	mm_setI2CConfA_TRDEL(platform->i2c_target->tr_delay);
	
	mm_setI2CConfB_ADDR(platform->i2c_target->legacy_address);
		
	// Create all the FreeRTOS Tasks
	xTaskCreate(GSE_MANAGER_Task, "GSE Manager", 1024, (void*) platform->gse_manager, tskIDLE_PRIORITY + 1, NULL );
	
	xTaskCreate(SERMUX_V3_ReceiveTask, "Serial MUX RX", 512, (void*) platform->sermux_v3, tskIDLE_PRIORITY+4, NULL);
	xTaskCreate(SERMUX_V3_TransmitTask, "Serial MUX TX", 512, (void*) platform->sermux_v3, tskIDLE_PRIORITY+4, NULL);
	
	xTaskCreate(I2CTARGET_Task, "I2C Target", 512, (void*) platform->i2c_target,  tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(LOCALTARGET_Task, "Local Target", 512, (void*) platform->local_target,  tskIDLE_PRIORITY+3, NULL);
	
	// High priority for this, to always keep the RX buffer empty and not loose data.
	xTaskCreate(ccd_usart_RXProcessingTask, "UART RX", 512, (void*) bsp.telemetry_uart, tskIDLE_PRIORITY + 4, &(bsp.telemetry_uart->task_reference));
	xTaskCreate(ccd_usart_TXProcessingTask, "UART TX", 512, (void*) bsp.telemetry_uart, tskIDLE_PRIORITY + 4, NULL);
	
	// Process RF Relay and multitester
	xTaskCreate(DEVTOOLS_Task, "RF Tools", 512, (void *) platform, tskIDLE_PRIORITY+2, NULL);
	
	// LED task has lowest priority
	xTaskCreate(LED_DRIVER_UpdateTask, "LED", 512, (void*) platform->led_driver, tskIDLE_PRIORITY+1, NULL);
	
	// Delete the setup task
	vTaskDelete( NULL );
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