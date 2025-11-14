/*
* csp_app.c
*
* Created: 11/12/2025 3:35:19 PM
*  Author: Adriaan van der West
*/

#include "csp_app.h"

#include "csp/csp_hooks.h"
#include "csp/autoconfig.h"
#include "csp/interfaces/csp_if_kiss.h"
#include "csp/drivers/usart.h"
#include "param/param.h"
#include "param/param_server.h"
#include "vmem/vmem_server.h"
#include "vmem/vmem_fram.h"

#include "config.h"

#include "csp_usart_cc.h"
#include "csp_can_cc.h"
#include "register_map.h"

csp_usart_cc_context_t csp_usart_cc_ctx_tel = { 0 };
csp_usart_cc_context_t csp_usart_cc_ctx_bus = { 0 };

csp_can_cc_context_t csp_can_cc_ctx_bus = { 0 };

static void csp_router_task(void * params);

void csp_app_init(bsp_t * bsp)
{
    mm_comms_protocol_t can_comms_protocol;
    mm_comms_protocol_t tel_uart_comms_protocol;
    mm_comms_protocol_t bus_uart_comms_protocol;
    
    configASSERT(mm_getConfCommsProtocol_BUS_CAN(&can_comms_protocol) == mm_OK);
    configASSERT(mm_getConfCommsProtocol_TEL_UART(&tel_uart_comms_protocol) == mm_OK);
    configASSERT(mm_getConfCommsProtocol_BUS_UART(&bus_uart_comms_protocol) == mm_OK);
    
    if (can_comms_protocol != reg_comms_protocol_csp && 
        tel_uart_comms_protocol != reg_comms_protocol_csp && 
        bus_uart_comms_protocol != reg_comms_protocol_csp )
    {
        return;
    }
    
    // Initialize CSP (TODO: Move to platform init function and setup task to match project structure)
    csp_conf.hostname = "EGSE"; // TODO: replace with parameter value
    csp_conf.model = "V2";
    csp_init();
    
    // BUS CAN
    if (can_comms_protocol == reg_comms_protocol_csp)
    {
        csp_can_cc_ctx_bus.iface.addr = CSP_ADDRESS_BUS_CAN;
        csp_can_cc_ctx_bus.iface.netmask = CSP_NETMASK_BUS_CAN;
        csp_can_cc_ctx_bus.iface.name = "CAN_BUS";
        csp_can_cc_ctx_bus.iface.interface_data = &csp_can_cc_ctx_bus.ifdata;
        csp_can_cc_ctx_bus.iface.driver_data = &csp_can_cc_ctx_bus;
        csp_can_cc_ctx_bus.ifdata.tx_func = csp_can_tx_frame;
        csp_can_cc_ctx_bus.lock = xSemaphoreCreateMutexStatic(&csp_can_cc_ctx_bus.lock_buffer);
        xSemaphoreGive(csp_can_cc_ctx_bus.lock);
        csp_can_cc_ctx_bus.ccd_driver = bsp->bus_can;
        csp_can_add_interface(&csp_can_cc_ctx_bus.iface);
    }
    
    // Telemetry UART
    if (tel_uart_comms_protocol == reg_comms_protocol_csp)
    {
        csp_usart_cc_ctx_tel.iface.addr = CSP_ADDRESS_TEL_UART;
        csp_usart_cc_ctx_tel.iface.netmask = CSP_NETMASK_TEL_UART;
        csp_usart_cc_ctx_tel.iface.name = "KISS_TEL";
        csp_usart_cc_ctx_tel.iface.interface_data = &csp_usart_cc_ctx_tel.ifdata;
        csp_usart_cc_ctx_tel.iface.driver_data = &csp_usart_cc_ctx_tel;
        csp_usart_cc_ctx_tel.ifdata.tx_func = csp_usart_cc_write;
        csp_usart_cc_ctx_tel.lock = xSemaphoreCreateMutexStatic(&csp_usart_cc_ctx_tel.lock_buffer);
        xSemaphoreGive(csp_usart_cc_ctx_tel.lock);
        csp_usart_cc_ctx_tel.ccd_driver = bsp->telemetry_uart;
        csp_kiss_add_interface(&csp_usart_cc_ctx_tel.iface);
    }
    
    // BUS UART
    if (bus_uart_comms_protocol == reg_comms_protocol_csp)
    {
        csp_usart_cc_ctx_bus.iface.addr = CSP_ADDRESS_BUS_UART,
        csp_usart_cc_ctx_bus.iface.netmask = CSP_NETMASK_BUS_UART;
        csp_usart_cc_ctx_bus.iface.name = "KISS_BUS";
        csp_usart_cc_ctx_bus.iface.interface_data = &csp_usart_cc_ctx_bus.ifdata;
        csp_usart_cc_ctx_bus.iface.driver_data = &csp_usart_cc_ctx_bus;
        csp_usart_cc_ctx_bus.ifdata.tx_func = csp_usart_cc_write;
        csp_usart_cc_ctx_bus.lock = xSemaphoreCreateMutexStatic(&csp_usart_cc_ctx_bus.lock_buffer);
        xSemaphoreGive(csp_usart_cc_ctx_bus.lock);
        csp_usart_cc_ctx_bus.ccd_driver = bsp->bus_uart;
        csp_kiss_add_interface(&csp_usart_cc_ctx_bus.iface);
    }
    
    csp_iflist_check_dfl();
    
    csp_bind_callback(csp_service_handler, CSP_ANY);
    csp_bind_callback(param_serve, PARAM_PORT_SERVER);
    
    xTaskCreate(csp_router_task, "CSP Route", 1024, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(vmem_server_loop, "VMEM Server", 1024, NULL, tskIDLE_PRIORITY + 2, NULL);
}

static void csp_router_task(void * params)
{
    (void) params; // unused
    
    while (1)
    {
        csp_route_work();
    }
    
    vTaskDelete(NULL);
}