#include "main.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "asf.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include "trcRecorder.h"

// TODO: [ADRIAAN] Figure out how to ignore the 500'ish warnings from this library when compiling
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wall"
#include "csp/csp.h"
#include "csp/csp_hooks.h"
#include "csp/autoconfig.h"
#include "csp/interfaces/csp_if_kiss.h"
#include "csp/drivers/usart.h"
#include "param/param.h"
#include "param/param_server.h"
#include "vmem/vmem_server.h"
#include "vmem/vmem_fram.h"
#pragma GCC diagnostic pop

#include "bsp.h"
#include "platform.h"

#include "register_handler.h"
#include "register_map.h"
#include "ltc2499.h"
#include "ltc2992.h"
#include "gse_manager.h"
#include "sermux_v3.h"
#include "pc_messages.h"
#include "led_indicator.h"
#include "can_target.h"
#include "i2c_target.h"
#include "local_target.h"
#include "uart_target.h"
#include "te_adaptors.h"
#include "csp_usart_cc.h"
#include "csp_can_cc.h"

// ================================================================================
// Defines
// ================================================================================

#define CSP_DEVICE_NAME            "EGSE"
#define CSP_DEVICE_NAME_MAX_LEN    16

// ================================================================================
// Variables
// ================================================================================

static bsp_t bsp;
static platform_t * platform;

// --- Experimental libcsp stuff ---

// ================================================================================
// Function prototypes
// ================================================================================

static void setup_task(void* handle);
static void devtools_task(void* handle);

// --- Experimental libcsp stuff ---
static void csp_app_init(void);
static void csp_router_task(void* param);

// ================================================================================
// Application entry point
// ================================================================================

int main(void)
{
    // Board initialization
    BSP_Init(&bsp);

    // Platform Initialization
    PLATFORM_vInit(&bsp);

    // Initialize memory map
    mm_init();

    // Configure all external ICs
    platform = PLATFORM_get();
    PLATFORM_vConfigureAll(platform);

    // Configure Tracealyzer tracing
    if(xTraceEnable(TRC_START_FROM_HOST) != TRC_SUCCESS)
    {
        ErrorHandler();
    }

    // Configure CubeSat Protocol (CSP)
    csp_app_init();

    xTaskCreate(setup_task, "Startup", 1024, NULL, tskIDLE_PRIORITY + 1, NULL );

    // Entire startup until here is very fast. Starting the scheduler and entering
    // the setup task takes almost 300ms. Don't know why.
    vTaskStartScheduler();

    // TODO: Reboot if we get here!
    while(1);
}

// ================================================================================
// Application tasks
// ================================================================================

static void setup_task(void* handle)
{
    mm_setBoard_ID(0x634F4243);
    mm_setFW_Version(0x00020206);
    mm_setHW_Version_major_version(BSP_u8GetVersion());

    mm_setI2CConfA_SPD(40);
    mm_setI2CConfA_WRDEL(platform->i2c_target->write_read_delay);
    mm_setI2CConfA_TRDEL(platform->i2c_target->tr_delay);

    mm_setI2CConfB_ADDR(platform->i2c_target->legacy_address);

    mm_setCANConfB_Address(platform->can_target->radio_can_address);
    mm_setUtilI2CConfA_SPD(bsp.util_i2c->baud / 10000);

    mm_setRFRelaysConf_ScanEnabled(true);
    mm_setMultiConf0_ScanEnabled(true);

    mm_setTE_Addr_0_ScanEnabled(true);
    mm_setTE_Addr_1_ScanEnabled(true);
    mm_setTE_Addr_2_ScanEnabled(true);
    mm_setTE_Addr_3_ScanEnabled(true);

    // Create all the FreeRTOS Tasks
    xTaskCreate(GSE_MANAGER_Task,               "GSE Manager",      1024,   (void *) platform->gse_manager,     tskIDLE_PRIORITY + 2, NULL);

    xTaskCreate(SERMUX_V3_ReceiveTask,          "SERMUX RX",        512,    (void *) platform->sermux_v3,       tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(SERMUX_V3_TransmitTask,         "SERMUX TX",        512,    (void *) platform->sermux_v3,       tskIDLE_PRIORITY + 2, NULL);

    xTaskCreate(I2CTARGET_Task,                 "I2C Target RX",    512,    (void *) platform->i2c_target,      tskIDLE_PRIORITY + 3, NULL);

    xTaskCreate(CANTARGET_RxTask,               "CAN Target RX",    512,    (void *) platform->can_target,      tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(CANTARGET_TxTask,               "CAN Target TX",    512,    (void *) platform->can_target,      tskIDLE_PRIORITY + 3, NULL);

    xTaskCreate(UARTTARGET_RxTask,              "UART Target RX",   512,    (void *) platform->uart_target,     tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(UARTTARGET_TxTask,              "UART Target TX",   512,    (void *) platform->uart_target,     tskIDLE_PRIORITY + 2, NULL);

    xTaskCreate(LOCALTARGET_Task,               "Local Target RX",  512,    (void *) platform->local_target,    tskIDLE_PRIORITY + 2, NULL);

    // High priority for this, to always keep the RX buffer empty and not loose data.
    xTaskCreate(ccd_usart_RXProcessingTask,     "TEL UART RX",      512,    (void *) bsp.telemetry_uart,        tskIDLE_PRIORITY + 4, &bsp.telemetry_uart->rx_task_handle);
    xTaskCreate(ccd_usart_TXProcessingTask,     "TEL UART TX",      512,    (void *) bsp.telemetry_uart,        tskIDLE_PRIORITY + 4, &bsp.telemetry_uart->tx_task_handle);

    xTaskCreate(ccd_usart_RXProcessingTask,     "BUS UART RX",      512,    (void *) bsp.bus_uart,              tskIDLE_PRIORITY + 2, &bsp.bus_uart->rx_task_handle);
    xTaskCreate(ccd_usart_TXProcessingTask,     "BUS UART TX",      512,    (void *) bsp.bus_uart,              tskIDLE_PRIORITY + 2, &bsp.bus_uart->tx_task_handle);

    // Process RF Relay, multitester and TE Adapters
    xTaskCreate(devtools_task,                  "RF Tools",         512,    (void *) platform,                  tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(TE_Adaptors_Task,               "TE Adapters",      512,    (void *) platform->te_scanner,      tskIDLE_PRIORITY + 2, NULL);

    // Multitester task
    xTaskCreate(MTCV2_Task,                     "MTC Task",         512,    (void *) platform->multitester,     tskIDLE_PRIORITY + 2, NULL);

    // LED task has lowest priority
    xTaskCreate(LEDIndicator_UpdateTask,        "LED",              512,    (void *) platform->led_indicator,   tskIDLE_PRIORITY + 1, NULL);

    // CSP tasks
    xTaskCreate(csp_router_task,                "CSP Route",        1024,   NULL,                               tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(vmem_server_loop,               "VMEM Server",      1024,   NULL,                               tskIDLE_PRIORITY + 2, NULL);

    // Delete the setup task
    vTaskDelete(NULL);
}

static void devtools_task(void* handle)
{
    platform_t * pHandle = (platform_t *) handle;

    while(1){

        RFRelay_Process(pHandle->rf_relay_1);
        RFRelay_Process(pHandle->rf_relay_2);
        MULTI_Process(pHandle->multitester);

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

static void csp_router_task(void * param)
{
    while(1)
    {
        csp_route_work();
    }
}

// ================================================================================
// FreeRTOS hooks
// ================================================================================

void vApplicationStackOverflowHook( TaskHandle_t xTask,char * pcTaskName )
{
    // Check pcTaskName for the name of the offending task,
    // or pxCurrentTCB if pcTaskName has itself been corrupted.
    ( void ) xTask;
    ( void ) pcTaskName;
    ErrorHandler();
}

void vApplicationMallocFailedHook(void)
{
    ErrorHandler();
}

void vApplicationTickHook(void)
{
    return;
}

// ================================================================================
// Miscellaneous
// ================================================================================

void csp_app_init(void)
{
    // Initialize CSP (TODO: Move to platform init function and setup task to match project structure)
    csp_conf.hostname = "EGSE"; // TODO: replace with parameter value
    csp_conf.model = "V2";
    csp_init();
    
    csp_usart_cc_init(&bsp);
    csp_can_cc_init(&bsp);
    
    csp_iflist_check_dfl();
    csp_bind_callback(csp_service_handler, CSP_ANY);
    csp_bind_callback(param_serve, PARAM_PORT_SERVER);
}

// ================================================================================
// Hardfault/Error handlers
// ================================================================================

void ErrorHandler(void)
{
    while(1)
    {
         continue;
    }
}

void HardFault_Handler(void)
{
    ErrorHandler();
}

void MemManage_Handler(void)
{
    ErrorHandler();
}

void BusFault_Handler(void)
{
    ErrorHandler();
}

void UsageFault_Handler(void)
{
    ErrorHandler();
}
