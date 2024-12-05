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

static void SetupRegisters(void);
static void DEVTOOLS_Task(void * handle);

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
	
	// Setup registers to their defaults.
    SetupRegisters();
	
	// Configure all external ICs
	PLATFORM_vConfigureAll(platform);
	
	
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
 * Setup the registers to all the default values, and set all the peripherals
 * to the same values. This is done with direct access to the memory map, because
 * the normal memory map functions can only be used when the task scheduler is 
 * running
*/
void SetupRegisters(void){
	mm_init();
	
	mm_t * register_map =  get_mm_ptr();
	
	register_map->Board_ID = 0x634F4243;
	register_map->FW_Version = 0x00020203;
	register_map->HW_Version = 0x00000001;
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