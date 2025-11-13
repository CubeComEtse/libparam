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



// ================================================================================
// Function prototypes
// ================================================================================



// ================================================================================
// Function definitions
// ================================================================================

int csp_can_tx_frame(void * driver_data, uint32_t id, const uint8_t * data, uint8_t dlc)
{
    configASSERT(driver_data != NULL);
    csp_can_cc_context_t * csp_can_context = (csp_can_cc_context_t *) driver_data;
    
    xSemaphoreTake(csp_can_context->lock, portMAX_DELAY);

    ccd_can_Send_message(csp_can_context->ccd_driver, id, data, dlc);
    
    xSemaphoreGive(csp_can_context->lock);
    
    return CSP_ERR_NONE;
}