/*
 * csp_uart_cc.c
 *
 * Created: 10/15/2025 4:47:05 PM
 *  Author: Adriaan van der Westhuizen
 */

// ================================================================================
// Includes
// ================================================================================

#include "csp_usart_cc.h"

// ================================================================================
// Private variables
// ================================================================================

csp_usart_cc_context_t csp_usart_cc_ctx_tel = { 0 };
csp_usart_cc_context_t csp_usart_cc_ctx_bus = { 0 };

// ================================================================================
// Function prototypes
// ================================================================================
    
static int csp_usart_cc_write(void  * driver_data, const uint8_t * data, size_t len);

// ================================================================================
// Function definitions
// ================================================================================

void csp_usart_lock(void * driver_data)
{
    csp_usart_cc_context_t * csp_usart_cc_context = driver_data;
    
    configASSERT(csp_usart_cc_context != NULL);
    configASSERT(csp_usart_cc_context->lock != NULL);
    
    xSemaphoreTake(csp_usart_cc_context->lock, portMAX_DELAY);
}

void csp_usart_unlock(void * driver_data)
{
    configASSERT(driver_data != NULL);
    csp_usart_cc_context_t * csp_usart_cc_context = (csp_usart_cc_context_t *) driver_data;
    
    configASSERT(csp_usart_cc_context != NULL);
    configASSERT(csp_usart_cc_context->lock != NULL);
    
    xSemaphoreGive(csp_usart_cc_context->lock);
}

static int csp_usart_cc_write(void  * driver_data, const uint8_t * data, size_t len)
{
    configASSERT(driver_data != NULL);
    csp_usart_cc_context_t * csp_usart_cc_context = (csp_usart_cc_context_t *) driver_data;
    
    ccd_b_uart_Send_message((void *)csp_usart_cc_context->ccd_driver, (uint8_t *) data, len);
    
    return len;
}

int csp_usart_cc_init(bsp_t * bsp)
{
    // --- Telemetry UART ---
    
    csp_usart_cc_ctx_tel.iface.addr = 209;
    csp_usart_cc_ctx_tel.iface.netmask = 12;
    csp_usart_cc_ctx_tel.iface.name = "KISS_TEL";
    csp_usart_cc_ctx_tel.iface.interface_data = &csp_usart_cc_ctx_tel.ifdata;
    csp_usart_cc_ctx_tel.iface.driver_data = &csp_usart_cc_ctx_tel;
    
    csp_usart_cc_ctx_tel.ifdata.tx_func = csp_usart_cc_write;
    
    csp_usart_cc_ctx_tel.lock = xSemaphoreCreateMutexStatic(&csp_usart_cc_ctx_tel.lock_buffer);
    xSemaphoreGive(csp_usart_cc_ctx_tel.lock);
    
    csp_usart_cc_ctx_tel.ccd_driver = bsp->telemetry_uart;
    
    csp_kiss_add_interface(&csp_usart_cc_ctx_tel.iface);
    
    // --- BUS UART ---
    
//     csp_usart_cc_ctx_bus.iface.addr = 197,
//     csp_usart_cc_ctx_bus.iface.netmask = 12;
//     csp_usart_cc_ctx_bus.iface.name = "KISS_BUS";
//     csp_usart_cc_ctx_bus.iface.interface_data = &csp_usart_cc_ctx_bus.ifdata;
//     csp_usart_cc_ctx_bus.iface.driver_data = &csp_usart_cc_ctx_bus;
//     
//     csp_usart_cc_ctx_bus.ifdata.tx_func = csp_usart_cc_write;
//     
//     csp_usart_cc_ctx_bus.lock = xSemaphoreCreateMutexStatic(&csp_usart_cc_ctx_bus.lock_buffer);
//     xSemaphoreGive(csp_usart_cc_ctx_bus.lock);
//     
//     csp_usart_cc_ctx_bus.ccd_driver = bsp->bus_uart;
//     
//     csp_kiss_add_interface(&csp_usart_cc_ctx_bus.iface);
    
    return CSP_ERR_NONE;
}
