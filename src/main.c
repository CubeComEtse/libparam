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

#include "csp/csp.h"
#include "csp/csp_hooks.h"
#include "csp/autoconfig.h"
#include "csp/interfaces/csp_if_kiss.h"
#include "csp/drivers/usart.h"
#include "param/param.h"
#include "param/param_server.h"
#include "vmem/vmem_server.h"
#include "vmem/vmem_fram.h"

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

// ================================================================================
// Defines
// ================================================================================

#define TEST_PC_CSP_ADDRESS    69
#define UART_CSP_ADDRESS       420

#define PARAMID_STATE          1
#define PARAMID_LED_COLOR      1
#define PARAMID_DEVICE_NAME    2

#define DEVICE_NAME            "EGSE"
#define DEVICE_NAME_MAX_LEN    16

// ================================================================================
// Variables
// ================================================================================

static bsp_t bsp;
static platform_t * platform;

// Experimental libcsp stuff
csp_iface_t * csp_usart_iface;
// Experimental libparam stuff
uint8_t _state[2];
char _device_name[16] = DEVICE_NAME;
uint8_t _led_color = 0;

// ================================================================================
// Function prototypes
// ================================================================================

static void SETUP_Task(void* handle);
static void DEVTOOLS_Task(void* handle);

static void monitor_tasks_task(void * param);

static void ErrorHandler(void);

// --- Experimental libcsp stuff ---
static void csp_router_task(void* param);
static void csp_ping_task(void * param);

// ---Experimental libparam stuff ---
void led_color_cb(param_t * param, int index);

// ================================================================================
// Macros
// ================================================================================

// --- Experimental libparam stuff---
PARAM_DEFINE_STATIC_RAM(PARAMID_LED_COLOR, led_color, PARAM_TYPE_UINT8, 1, 1, PM_CONF, led_color_cb, NULL, &_led_color, "0 = off, 1 = red, 2 = green, 3 = blue");
PARAM_DEFINE_STATIC_RAM(PARAMID_DEVICE_NAME, device_name, PARAM_TYPE_STRING, sizeof(_device_name) / sizeof(_device_name[0]), sizeof(_device_name[0]), PM_CONF, NULL, NULL, &_device_name, NULL);
// VMEM_DEFINE_STATIC_RAM(apmtest, "apmtest", 1024);
// PARAM_DEFINE_STATIC_VMEM(157, vmem_u8, PARAM_TYPE_UINT8, 0, sizeof(uint8_t), PM_CONF, NULL, "", apmtest, 0x0, "Test VMEM U8");
// PARAM_DEFINE_STATIC_VMEM(158, vmem_u16, PARAM_TYPE_UINT16, 0, sizeof(uint16_t), PM_CONF, NULL, "", apmtest, 0x1, "Test VMEM U16");

// ================================================================================
// Application entry point
// ================================================================================

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
    
    // Initialize CSP (TODO: Move to platform init function and setup task to match project structure)
    csp_conf.hostname = "EGSE"; // TODO: replace with parameter value
    csp_conf.model = "V2";
    csp_init();
    csp_usart_conf_t csp_usart_conf = {
        .device = "BUS UART",
        .baudrate = 115200,
        .databits = 8,
        .stopbits = 1,
        .paritysetting = 0,
        .ccd_usart_handle = bsp.bus_uart,
    };
    if (csp_usart_open_and_add_kiss_interface(&csp_usart_conf, CSP_IF_KISS_DEFAULT_NAME, UART_CSP_ADDRESS, &csp_usart_iface) != CSP_ERR_NONE)
    {
        ErrorHandler();
    }
    csp_iflist_check_dfl();
    csp_bind_callback(csp_service_handler, CSP_ANY);
    csp_bind_callback(param_serve, PARAM_PORT_SERVER);
    
    xTaskCreate(SETUP_Task, "Startup", 1024, NULL, tskIDLE_PRIORITY + 1, NULL );
        
    // Entire startup until here is very fast. Starting the scheduler and entering
    // the setup task takes almost 300ms. Don't know why.
    vTaskStartScheduler();
    
    // TODO: Reboot if we get here!
    while(1);
}

// ================================================================================
// Application tasks
// ================================================================================

static void SETUP_Task(void* handle)
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
    xTaskCreate(GSE_MANAGER_Task, "GSE Manager", 1024, (void *) platform->gse_manager, tskIDLE_PRIORITY + 2, NULL);
    
    xTaskCreate(SERMUX_V3_ReceiveTask, "Serial MUX RX", 512, (void *) platform->sermux_v3, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(SERMUX_V3_TransmitTask, "Serial MUX TX", 512, (void *) platform->sermux_v3, tskIDLE_PRIORITY + 2, NULL);
    
    xTaskCreate(I2CTARGET_Task, "I2C Target", 512, (void *) platform->i2c_target,  tskIDLE_PRIORITY + 3, NULL);
    
    xTaskCreate(CANTARGET_TxTask, "CAN TX Task", 512, (void *) platform->can_target, tskIDLE_PRIORITY + 3, NULL);
    xTaskCreate(CANTARGET_RxTask, "CAN RX Task", 512, (void *) platform->can_target, tskIDLE_PRIORITY + 2, NULL);
    
    xTaskCreate(UARTTARGET_TxTask, "UART TX Task", 512, (void *) platform->uart_target, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(UARTTARGET_RxTask, "UART RX Task", 512, (void *) platform->uart_target, tskIDLE_PRIORITY + 2, NULL);
    
    xTaskCreate(LOCALTARGET_Task, "Local Target", 512, (void *) platform->local_target,  tskIDLE_PRIORITY + 2, NULL);
    
    // High priority for this, to always keep the RX buffer empty and not loose data.
    xTaskCreate(ccd_usart_RXProcessingTask, "UART RX", 512, (void *) bsp.telemetry_uart, tskIDLE_PRIORITY + 4, &bsp.telemetry_uart->rx_task_handle);
    xTaskCreate(ccd_usart_TXProcessingTask, "UART TX", 512, (void *) bsp.telemetry_uart, tskIDLE_PRIORITY + 4, &bsp.telemetry_uart->tx_task_handle);
    
    xTaskCreate(ccd_usart_TXProcessingTask, "UART TX", 512, (void *) bsp.bus_uart, tskIDLE_PRIORITY + 2, &bsp.bus_uart->rx_task_handle);
    xTaskCreate(ccd_usart_RXProcessingTask, "UART RX", 512, (void *) bsp.bus_uart, tskIDLE_PRIORITY + 2, &bsp.bus_uart->tx_task_handle);
    
    // Process RF Relay, multitester and TE Adapters
    xTaskCreate(DEVTOOLS_Task, "RF Tools", 512, (void *) platform, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(TE_Adaptors_Task, "TE Adapters", 512, (void *) platform->te_scanner, tskIDLE_PRIORITY + 2, NULL);
    
    // Multitester task
    xTaskCreate(MTCV2_Task, "MTC Task", 512, (void *) platform->multitester, tskIDLE_PRIORITY + 2, NULL);
    
    // LED task has lowest priority
    xTaskCreate(LEDIndicator_UpdateTask, "LED", 512, (void *) platform->led_indicator, tskIDLE_PRIORITY + 1, NULL);
    
    // CSP tasks
    xTaskCreate(csp_router_task, "CSP Route", 1024, NULL, tskIDLE_PRIORITY + 2, NULL);
//     xTaskCreate(csp_ping_task, "CSP Ping", 256, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(vmem_server_loop, "VMEM Server", 1024, NULL, tskIDLE_PRIORITY + 2, NULL);

    // Tasks monitoring task
    xTaskCreate(monitor_tasks_task, "Task Monitor", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
    
    // Delete the setup task
    vTaskDelete(NULL);
}

static void DEVTOOLS_Task(void* handle)
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

static void csp_ping_task(void * param)
{
    while(1)
    {
//         csp_ping_noreply(16);
        uint8_t opts = CSP_O_NONE;
//         int res = csp_ping(TEST_PC_CSP_ADDRESS, 1000, 0, opts);
        int res = csp_ping(UART_CSP_ADDRESS, 1000, 0, opts);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

static void csp_server_task(void * param)
{
    csp_socket_t sock = {0};
    csp_bind(&sock, CSP_ANY);
    csp_listen(&sock, 10);
    
    while (1)
    {
        csp_conn_t* conn;
        if((conn = csp_accept(&sock, 10000)) == NULL)
        {
            // Timeout
            continue;
        }
        
        /* Read packets on connection, timeout is 50 ms */
		csp_packet_t *packet;
		while ((packet = csp_read(conn, 50)) != NULL) {
			switch (csp_conn_dport(conn)) {
			    case 10:
                {
				    /* Process packet here */
				    csp_buffer_free(packet);
				    break;
                }                    

			    default:
                {
				    /* Call the default CSP service handler, handle pings, buffer use, etc. */
				    csp_service_handler(packet);
				    break;
                }                    
			}
		}

		/* Close current connection */
		csp_close(conn);
    }
}

static void monitor_tasks_task(void * param)
{
    while (1)
    {
        UBaseType_t uxHighWaterMark1 = uxTaskGetStackHighWaterMark(bsp.telemetry_uart->rx_task_handle);
        UBaseType_t uxHighWaterMark2 = uxTaskGetStackHighWaterMark(bsp.telemetry_uart->tx_task_handle);
        UBaseType_t uxHighWaterMark3 = uxTaskGetStackHighWaterMark(bsp.bus_uart->rx_task_handle);
        UBaseType_t uxHighWaterMark4 = uxTaskGetStackHighWaterMark(bsp.bus_uart->tx_task_handle);
        
        vTaskDelay(pdMS_TO_TICKS(5000));
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
// libparam callbacks
// ================================================================================

void led_color_cb(param_t * param, int index)
{
    LEDIndicator_SetNextState(param_get_uint8_array(param, index));
    // TODO: handle parameter set event (parameter already assigned with a new value)
    return;
}

// ================================================================================
// Miscellaneous
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
