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

#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "semphr.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#include "csp/interfaces/csp_if_kiss.h"
#include "csp/drivers/usart.h"
#pragma GCC diagnostic pop

#include "bsp.h"
#include "ccd_uart_driver.h"

// ================================================================================
// Definitions
// ================================================================================

#define CSP_PC_UART_NETWORK_MASK        12
#define CSP_EGSE_UART_NETWORK_MASK      8

#define CSP_PC_UART_ADDRESS             420
#define CSP_TEL_UART_ADDRESS            421
#define CSP_BUS_UART_ADDRESS            5

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

int csp_usart_cc_init(bsp_t * bsp);

#endif /* CSP_USART_CC_H_ */