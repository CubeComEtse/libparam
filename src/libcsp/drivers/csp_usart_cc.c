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



// ================================================================================
// Function prototypes
// ================================================================================



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

int csp_usart_cc_write(void  * driver_data, const uint8_t * data, size_t len)
{
    configASSERT(driver_data != NULL);
    csp_usart_cc_context_t * csp_usart_cc_context = (csp_usart_cc_context_t *) driver_data;
    
    ccd_b_uart_Send_message((void *)csp_usart_cc_context->ccd_driver, (uint8_t *) data, len);
    
    return len;
}
