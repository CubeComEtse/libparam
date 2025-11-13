/*
 * main.c
 *
 * Created:
 *  Author: Kolijn
 */

// Standard includes
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// ASF includes
#include "asf.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

// Application configuration includes
#include "bsp.h"
#include "platform.h"
#include "config.h"

// 3rd Party libraries includes
#if defined(DEBUG) && TRACE_ENABLED
#include "trcRecorder.h"
#endif
// TODO: Figure out how to ignore the 500'ish warnings from these libraries when compiling
#include "csp_app.h"
#include "cants.h"

// Application includes
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



// ================================================================================
// Variables
// ================================================================================

static bsp_t bsp;
static platform_t * platform;

// ================================================================================
// Function prototypes
// ================================================================================

static void system_init(void);

static void devtools_task(void * handle);

#if defined(DEBUG) && TRACE_ENABLED
static void tracealyzer_init(void);
#endif
#if defined(DEBUG) && XTXG2_DEBUG_ENABLE
static void initialize_xtxg2_task(void * params);
#endif
#ifdef DEBUG
static void cants_test_task(void * params);
#endif

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
    
#if defined(DEBUG) && TRACE_ENABLED
    // Configure Tracealyzer tracing
    tracealyzer_init();
#endif

    system_init();

    // Entire startup until here is very fast. Starting the scheduler and entering
    // the setup task takes almost 300ms. Don't know why.
    vTaskStartScheduler();

    // TODO: Reboot if we get here!
    while(1);
}

static void system_init(void)
{
    BaseType_t rtos_ret;
    mm_comms_protocol_t can_comms_protocol;
    
    // TODO: These should likely all come from the config.h file
    
    mm_setBoard_ID(BOARD_IDENTIFIER);
    mm_setFW_Version(((uint32_t) SOFTWARE_VERSION_MAJOR << 16) | ((uint32_t) SOFTWARE_VERSION_MINOR << 8) | ((uint32_t) SOFTWARE_VERSION_PATCH << 0));
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
    
#if DEBUG
    // This is just for overriding the communication protocols for debugging purposes
    mm_setConfCommsProtocol_TEL_UART(reg_comms_protocol_cubecom);
    mm_setConfCommsProtocol_BUS_UART(reg_comms_protocol_cubecom);
    mm_setConfCommsProtocol_BUS_CAN(reg_comms_protocol_cants);
#endif

    mm_getConfCommsProtocol_BUS_CAN(&can_comms_protocol);
    
    csp_app_init(&bsp);
    if (can_comms_protocol == reg_comms_protocol_cants)
    {
        struct cants_cfg cfg = {
            .utm_ch_min = 0,
            .utm_ch_max = 1,
            .ka_period = 100,
            .utm_period = 100,
            .utm_counter = 100
        };
        cants_init(&cfg);
#ifdef DEBUG
        rtos_ret = xTaskCreate(cants_test_task, "CANTS Test", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
        configASSERT(rtos_ret == pdPASS);
#endif
    }

    // Create all the FreeRTOS Tasks
    rtos_ret = xTaskCreate(GSE_MANAGER_Task, "GSE Manager", 1024, (void *) platform->gse_manager, tskIDLE_PRIORITY + 2, NULL);
    configASSERT(rtos_ret == pdPASS);

    rtos_ret = xTaskCreate(SERMUX_V3_ReceiveTask, "SERMUX RX", 512, (void *) platform->sermux_v3, tskIDLE_PRIORITY + 2, NULL);
    configASSERT(rtos_ret == pdPASS);
    rtos_ret = xTaskCreate(SERMUX_V3_TransmitTask, "SERMUX TX", 512, (void *) platform->sermux_v3, tskIDLE_PRIORITY + 2, NULL);
    configASSERT(rtos_ret == pdPASS);

    rtos_ret = xTaskCreate(I2CTARGET_Task, "I2C Target RX", 512, (void *) platform->i2c_target, tskIDLE_PRIORITY + 3, NULL);
    configASSERT(rtos_ret == pdPASS);

    rtos_ret = xTaskCreate(CANTARGET_ReceiveTask, "CAN Target RX", 512, (void *) platform->can_target, tskIDLE_PRIORITY + 2, NULL);
    configASSERT(rtos_ret == pdPASS);
    rtos_ret = xTaskCreate(CANTARGET_TransmitTask, "CAN Target TX", 512, (void *) platform->can_target, tskIDLE_PRIORITY + 3, NULL);
    configASSERT(rtos_ret == pdPASS);

    rtos_ret = xTaskCreate(UARTTARGET_ReceiveTask, "UART Target RX", 512, (void *) platform->uart_target, tskIDLE_PRIORITY + 2, NULL);
    configASSERT(rtos_ret == pdPASS);
    rtos_ret = xTaskCreate(UARTTARGET_TransmitTask, "UART Target TX", 512, (void *) platform->uart_target, tskIDLE_PRIORITY + 2, NULL);
    configASSERT(rtos_ret == pdPASS);

    rtos_ret = xTaskCreate(LOCALTARGET_Task, "Local Target RX", 512, (void *) platform->local_target, tskIDLE_PRIORITY + 2, NULL);
    configASSERT(rtos_ret == pdPASS);

    // High priority for this, to always keep the RX buffer empty and not loose data.
    rtos_ret = xTaskCreate(ccd_usart_RXProcessingTask, "TEL UART RX", 512, (void *) bsp.telemetry_uart, tskIDLE_PRIORITY + 4, &bsp.telemetry_uart->rx_task_handle);
    configASSERT(rtos_ret == pdPASS);
    rtos_ret = xTaskCreate(ccd_usart_TXProcessingTask, "TEL UART TX", 512, (void *) bsp.telemetry_uart, tskIDLE_PRIORITY + 4, &bsp.telemetry_uart->tx_task_handle);
    configASSERT(rtos_ret == pdPASS);

    rtos_ret = xTaskCreate(ccd_usart_RXProcessingTask, "BUS UART RX", 512, (void *) bsp.bus_uart, tskIDLE_PRIORITY + 2, &bsp.bus_uart->rx_task_handle);
    configASSERT(rtos_ret == pdPASS);
    rtos_ret = xTaskCreate(ccd_usart_TXProcessingTask, "BUS UART TX", 512, (void *) bsp.bus_uart, tskIDLE_PRIORITY + 2, &bsp.bus_uart->tx_task_handle);
    configASSERT(rtos_ret == pdPASS);

    // Process RF Relay, multitester and TE Adapters
    rtos_ret = xTaskCreate(devtools_task, "RF Tools", 512, (void *) platform, tskIDLE_PRIORITY + 2, NULL);
    configASSERT(rtos_ret == pdPASS);
    rtos_ret = xTaskCreate(TE_Adaptors_Task, "TE Adapters", 512, (void *) platform->te_scanner, tskIDLE_PRIORITY + 2, NULL);
    configASSERT(rtos_ret == pdPASS);

    // Multitester task
    rtos_ret = xTaskCreate(MTCV2_Task, "MTC", 512, (void *) platform->multitester, tskIDLE_PRIORITY + 2, NULL);
    configASSERT(rtos_ret == pdPASS);

    // LED task has lowest priority
    rtos_ret = xTaskCreate(LEDIndicator_UpdateTask, "LED", 512, (void *) platform->led_indicator, tskIDLE_PRIORITY + 1, NULL);
    configASSERT(rtos_ret == pdPASS);
    
#if defined(DEBUG) && XTXG2_DEBUG_ENABLE
    rtos_ret = xTaskCreate(initialize_xtxg2_task, "Init XTXG2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    configASSERT(rtos_ret == pdPASS);
#endif
}

static void devtools_task(void * params)
{
    configASSERT(params != NULL);
    platform_t * pHandle = (platform_t *) params;

    while (1)
    {
        RFRelay_Process(pHandle->rf_relay_1);
        RFRelay_Process(pHandle->rf_relay_2);
        //MULTI_Process(pHandle->multitester);

        vTaskDelay(pdMS_TO_TICKS(20));
    }
    
    vTaskDelete(NULL);
}

#if defined(DEBUG) && TRACE_ENABLED
static void tracealyzer_init(void)
{
    configASSERT(xTraceEnable(TRC_START_FROM_HOST) == TRC_SUCCESS);
}
#endif

#ifdef DEBUG
static void cants_test_task(void * params)
{   
    (void) params; // unused
    
    struct cants_msg msg;
    uint8_t counter = 0;
    
    msg.source = CANTS_NODE_ID;
    msg.destination = CANTS_NODE_ID;
    msg.type = cants_type_telecommand;
    msg.command = CANTS_CHANNEL_PARAMETERS;
    msg.length = 6;
    msg.data[0] = (uint8_t) (reg_Scratchpad_addr >> 8);
    msg.data[1] = (uint8_t) (reg_Scratchpad_addr >> 0);
    
    while (1)
    {
        msg.data[2] = counter++;
        msg.data[3] = counter++;
        msg.data[4] = counter++;
        msg.data[5] = counter++;
        cants_send_msg(&msg, 1);
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    vTaskDelete(NULL);
}
#endif

#if defined(DEBUG) && XTXG2_DEBUG_ENABLE
static void initialize_xtxg2_task(void * params)
{
    (void) params; // unused
    
    GSE_MANAGER_SetBusPowerSwitch(platform->gse_manager, POWER_3V3, true);
    GSE_MANAGER_SetBusPowerSwitch(platform->gse_manager, POWER_VBAT, true);
    GSE_MANAGER_SetBusPowerSwitch(platform->gse_manager, POWER_3V3_UTIL, true);
    mm_setConfigured_Boards(reg_boardidentifier_gen2);
    vTaskDelay(100); // Allow some time for TE discovery
    TE_Adaptor_SetTeBits(platform->te_scanner, 0, (0x04000000 >> 16) & 0x0FFF);
    TE_Adaptor_SetTeBits(platform->te_scanner, 0, (0x02000000 >> 16) & 0x0FFF);
    TE_Adaptor_SetTeBits(platform->te_scanner, 0, (0x01000000 >> 16) & 0x0FFF);
    
    vTaskDelete(NULL);
}
#endif

void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName)
{
    (void) xTask; // unused
    (void) pcTaskName; // unused
    configASSERT(false);
}

void vApplicationMallocFailedHook(void)
{
    configASSERT(false);
}

void vApplicationTickHook(void)
{
    return;
}

void HardFault_Handler(void)
{
    configASSERT(false);
}

void MemManage_Handler(void)
{
    configASSERT(false);
}

void BusFault_Handler(void)
{
    configASSERT(false);
}

void UsageFault_Handler(void)
{
    configASSERT(false);
}
