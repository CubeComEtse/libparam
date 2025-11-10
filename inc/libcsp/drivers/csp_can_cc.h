/*
 * csp_can_cc.h
 *
 * Created: 10/16/2025 10:36:53 AM
 *  Author: Adriaan van der Westhuizen
 */

#ifndef CSP_CAN_CC_H_
#define CSP_CAN_CC_H_

// ================================================================================
// Includes
// ================================================================================

#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "semphr.h"

#include "csp/interfaces/csp_if_can.h"

#include "bsp.h"
#include "ccd_can_driver.h"

// ================================================================================
// Definitions
// ================================================================================

#define CSP_EGSE_CAN_NETWORK_MASK       8

#define CSP_BUS1_CAN_ADDRESS            5
#define CSP_BUS2_CAN_ADDRESS            5

// ================================================================================
// Type definitions
// ================================================================================

typedef struct csp_can_context_s
{
    csp_iface_t iface;
    csp_can_interface_data_t ifdata;
    
    SemaphoreHandle_t lock;
    StaticSemaphore_t lock_buffer;
    
    ccd_can_t * ccd_driver;
} csp_can_cc_context_t;

// ================================================================================
// Public function prototypes
// ================================================================================

int csp_can_cc_init(bsp_t * bsp);

#endif /* CSP_CAN_CC_H_ */