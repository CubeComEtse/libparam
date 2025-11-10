/*
 * csp_can.c
 *
 * Created: 10/15/2025 4:46:55 PM
 *  Author: Adriaan van der Westhuizen
 */ 

// ================================================================================
// Includes
// ================================================================================

#include "csp_can_cc.h"

// ================================================================================
// Private variables
// ================================================================================

csp_can_cc_context_t csp_can_cc_ctx_bus = { 0 };

// ================================================================================
// Function prototypes
// ================================================================================

static int csp_can_tx_frame(void * driver_data, uint32_t id, const uint8_t * data, uint8_t dlc);

// ================================================================================
// Function definitions
// ================================================================================

static int csp_can_tx_frame(void * driver_data, uint32_t id, const uint8_t * data, uint8_t dlc)
{
    configASSERT(driver_data != NULL);
    csp_can_cc_context_t * csp_can_context = (csp_can_cc_context_t *) driver_data;
    
    xSemaphoreTake(csp_can_context->lock, portMAX_DELAY);

    ccd_can_Send_message(csp_can_context->ccd_driver, id, data, dlc);
    
    xSemaphoreGive(csp_can_context->lock);
    
    return CSP_ERR_NONE;
}

int csp_can_cc_init(bsp_t * bsp)
{
    csp_can_cc_ctx_bus.iface.addr = 128;
    csp_can_cc_ctx_bus.iface.netmask = 8;
    csp_can_cc_ctx_bus.iface.name = "CAN_BUS";
    csp_can_cc_ctx_bus.iface.interface_data = &csp_can_cc_ctx_bus.ifdata;
    csp_can_cc_ctx_bus.iface.driver_data = &csp_can_cc_ctx_bus;
    
    csp_can_cc_ctx_bus.ifdata.tx_func = csp_can_tx_frame;
    
    csp_can_cc_ctx_bus.lock = xSemaphoreCreateMutexStatic(&csp_can_cc_ctx_bus.lock_buffer);
    xSemaphoreGive(csp_can_cc_ctx_bus.lock);
    
    csp_can_cc_ctx_bus.ccd_driver = bsp->bus_can;
    
    csp_can_add_interface(&csp_can_cc_ctx_bus.iface);
    
    return CSP_ERR_NONE;
}