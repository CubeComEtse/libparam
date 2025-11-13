/*
 * csp_usart_cc.h
 *
 * Created: 10/16/2025 10:37:09 AM
 *  Author: Adriaan van der Westhuizen
 */ 

#ifndef CSP_USART_CC_H_
#define CSP_USART_CC_H_

// ================================================================================
// Includes
// ================================================================================

#include <stdint.h>

#include "FreeRTOS.h"
#include "semphr.h"

#include "csp/interfaces/csp_if_kiss.h"

#include "ccd_uart_driver.h"

// ================================================================================
// Definitions
// ================================================================================



// ================================================================================
// Type definitions
// ================================================================================

typedef struct csp_usart_cc_context_s
{
    csp_iface_t iface;
    csp_kiss_interface_data_t ifdata;
    
    SemaphoreHandle_t lock;
    StaticSemaphore_t lock_buffer;
    
    ccd_uart_t* ccd_driver;
} csp_usart_cc_context_t;

// ================================================================================
// Public function prototypes
// ================================================================================

int csp_usart_cc_write(void  * driver_data, const uint8_t * data, size_t len);

#endif /* CSP_USART_CC_H_ */