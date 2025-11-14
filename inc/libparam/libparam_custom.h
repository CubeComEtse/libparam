/*
 * libparam_custom.h
 *
 * Created: 11/14/2025 10:30:29 AM
 *  Author: Adriaan van der West
 */ 


#ifndef LIBPARAM_CUSTOM_H_
#define LIBPARAM_CUSTOM_H_

#include "libparam.h"

#include <stdint.h>

#include "vmem/vmem.h"
#include "param/param.h"

#include "register_handler.h"

#define PARAM_DEFINE_CC_STATIC_RAM_UINT32(_reg_addr, _name, _flags) \
    ; /* Catch const param defines */ \
    csp_timestamp_t _timestamp_##_name = { .tv_sec = 0, .tv_nsec = 0 }; \
    uint16_t _node_##_name = 0; \
    __attribute__((section("param"))) \
    __attribute__((used, no_reorder)) \
    param_t _name = { \
        /* Parameter declaration */ \
        .id = _reg_addr, \
        .node = &_node_##_name, \
        .type = PARAM_TYPE_UINT32, \
        .mask = _flags, \
        .name = #_name, \
        .unit = NULL, \
        .docstr = NULL, \
        /* Storage */ \
        .addr = NULL, \
        .vaddr = 0, \
        .vmem = NULL, \
        .array_size = 1, \
        .array_step = 0, \
        /* Local info */ \
        .read_func = REG_vReadFromAddress, \
        .write_func = REG_vWriteToAddress, \
        .callback = NULL, \
        .timestamp = &_timestamp_##_name, \
    }

#endif /* LIBPARAM_CUSTOM_H_ */