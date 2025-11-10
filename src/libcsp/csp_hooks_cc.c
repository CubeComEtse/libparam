/*
 * csp_hooks.c
 *
 * Created: 10/15/2025 4:49:59 PM
 *  Author: Adriaan van der Westhuizen
 */ 

#include "csp/csp_hooks.h"

#include "core_cm7.h"

void csp_reboot_hook(void)
{
    NVIC_SystemReset();
}

void csp_shutdown_hook(void)
{
    NVIC_SystemReset();
}