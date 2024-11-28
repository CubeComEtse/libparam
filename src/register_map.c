#include "register_map.h"
#include "FreeRTOS.h"
#include "semphr.h"

#ifndef MEMORY_MAP_MUTEX_WAIT_ms
#define MEMORY_MAP_MUTEX_WAIT_ms 100
#endif

static SemaphoreHandle_t _mm_mutex;
static mm_t mm;

void mm_init(void)
{
    // Create the mutex lock
    _mm_mutex =  xSemaphoreCreateMutex();
    
    // Initialize the values in the memory map
}
mm_t * get_mm_ptr(void)
{
    return &mm;
}

/*************** Get/Set functions for Board_ID register **********************************************************************/
mm_response_t mm_setBoard_ID(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Board_ID = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getBoard_ID(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.Board_ID;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setBoard_ID_ccIdentifier(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Board_ID = (mm.Board_ID & ~REG_BOARD_ID_CCIDENTIFIER_Msk) | (val << REG_BOARD_ID_CCIDENTIFIER_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getBoard_ID_ccIdentifier(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.Board_ID & REG_BOARD_ID_CCIDENTIFIER_Msk) >> REG_BOARD_ID_CCIDENTIFIER_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getBoard_ID_ccIdentifierFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_BOARD_ID_CCIDENTIFIER_Msk) >> REG_BOARD_ID_CCIDENTIFIER_Pos);
    return mm_OK;
}
mm_response_t mm_setBoard_ID_id0(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Board_ID = (mm.Board_ID & ~REG_BOARD_ID_ID0_Msk) | (val << REG_BOARD_ID_ID0_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getBoard_ID_id0(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.Board_ID & REG_BOARD_ID_ID0_Msk) >> REG_BOARD_ID_ID0_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getBoard_ID_id0From(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_BOARD_ID_ID0_Msk) >> REG_BOARD_ID_ID0_Pos);
    return mm_OK;
}
mm_response_t mm_setBoard_ID_id1(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Board_ID = (mm.Board_ID & ~REG_BOARD_ID_ID1_Msk) | (val << REG_BOARD_ID_ID1_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getBoard_ID_id1(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.Board_ID & REG_BOARD_ID_ID1_Msk) >> REG_BOARD_ID_ID1_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getBoard_ID_id1From(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_BOARD_ID_ID1_Msk) >> REG_BOARD_ID_ID1_Pos);
    return mm_OK;
}
mm_response_t mm_setBoard_ID_id2(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Board_ID = (mm.Board_ID & ~REG_BOARD_ID_ID2_Msk) | (val << REG_BOARD_ID_ID2_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getBoard_ID_id2(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.Board_ID & REG_BOARD_ID_ID2_Msk) >> REG_BOARD_ID_ID2_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getBoard_ID_id2From(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_BOARD_ID_ID2_Msk) >> REG_BOARD_ID_ID2_Pos);
    return mm_OK;
}
/*************** Get/Set functions for FW_Version register ********************************************************************/
mm_response_t mm_setFW_Version(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.FW_Version = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getFW_Version(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.FW_Version;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setFW_Version_major_version(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.FW_Version = (mm.FW_Version & ~REG_VERSION_MAJOR_VERSION_Msk) | (val << REG_VERSION_MAJOR_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getFW_Version_major_version(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.FW_Version & REG_VERSION_MAJOR_VERSION_Msk) >> REG_VERSION_MAJOR_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getFW_Version_major_versionFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_VERSION_MAJOR_VERSION_Msk) >> REG_VERSION_MAJOR_VERSION_Pos);
    return mm_OK;
}
mm_response_t mm_setFW_Version_minor_version(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.FW_Version = (mm.FW_Version & ~REG_VERSION_MINOR_VERSION_Msk) | (val << REG_VERSION_MINOR_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getFW_Version_minor_version(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.FW_Version & REG_VERSION_MINOR_VERSION_Msk) >> REG_VERSION_MINOR_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getFW_Version_minor_versionFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_VERSION_MINOR_VERSION_Msk) >> REG_VERSION_MINOR_VERSION_Pos);
    return mm_OK;
}
mm_response_t mm_setFW_Version_patch_version(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.FW_Version = (mm.FW_Version & ~REG_VERSION_PATCH_VERSION_Msk) | (val << REG_VERSION_PATCH_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getFW_Version_patch_version(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.FW_Version & REG_VERSION_PATCH_VERSION_Msk) >> REG_VERSION_PATCH_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getFW_Version_patch_versionFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_VERSION_PATCH_VERSION_Msk) >> REG_VERSION_PATCH_VERSION_Pos);
    return mm_OK;
}
/*************** Get/Set functions for HW_Version register ********************************************************************/
mm_response_t mm_setHW_Version(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.HW_Version = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getHW_Version(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.HW_Version;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setHW_Version_major_version(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.HW_Version = (mm.HW_Version & ~REG_VERSION_MAJOR_VERSION_Msk) | (val << REG_VERSION_MAJOR_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getHW_Version_major_version(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.HW_Version & REG_VERSION_MAJOR_VERSION_Msk) >> REG_VERSION_MAJOR_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getHW_Version_major_versionFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_VERSION_MAJOR_VERSION_Msk) >> REG_VERSION_MAJOR_VERSION_Pos);
    return mm_OK;
}
mm_response_t mm_setHW_Version_minor_version(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.HW_Version = (mm.HW_Version & ~REG_VERSION_MINOR_VERSION_Msk) | (val << REG_VERSION_MINOR_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getHW_Version_minor_version(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.HW_Version & REG_VERSION_MINOR_VERSION_Msk) >> REG_VERSION_MINOR_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getHW_Version_minor_versionFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_VERSION_MINOR_VERSION_Msk) >> REG_VERSION_MINOR_VERSION_Pos);
    return mm_OK;
}
mm_response_t mm_setHW_Version_patch_version(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.HW_Version = (mm.HW_Version & ~REG_VERSION_PATCH_VERSION_Msk) | (val << REG_VERSION_PATCH_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getHW_Version_patch_version(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.HW_Version & REG_VERSION_PATCH_VERSION_Msk) >> REG_VERSION_PATCH_VERSION_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getHW_Version_patch_versionFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_VERSION_PATCH_VERSION_Msk) >> REG_VERSION_PATCH_VERSION_Pos);
    return mm_OK;
}
/*************** Get/Set functions for Scratchpad register ********************************************************************/
mm_response_t mm_setScratchpad(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Scratchpad = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getScratchpad(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.Scratchpad;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getScratchpadFrom(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for Configured_Boards register *************************************************************/
mm_response_t mm_setConfigured_Boards(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Configured_Boards = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getConfigured_Boards(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.Configured_Boards;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getConfigured_BoardsFrom(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for Uptime register ************************************************************************/
mm_response_t mm_setUptime(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Uptime = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getUptime(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.Uptime;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getUptimeFrom(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for Event_ConfA register *******************************************************************/
mm_response_t mm_setEvent_ConfA(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Event_ConfA = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getEvent_ConfA(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.Event_ConfA;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setEvent_ConfA_count(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Event_ConfA = (mm.Event_ConfA & ~REG_EVENT_CONFA_COUNT_Msk) | (val << REG_EVENT_CONFA_COUNT_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getEvent_ConfA_count(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.Event_ConfA & REG_EVENT_CONFA_COUNT_Msk) >> REG_EVENT_CONFA_COUNT_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getEvent_ConfA_countFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_EVENT_CONFA_COUNT_Msk) >> REG_EVENT_CONFA_COUNT_Pos);
    return mm_OK;
}
/*************** Get/Set functions for Event register *************************************************************************/
mm_response_t mm_setEvent(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Event = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getEvent(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.Event;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setEvent_section(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Event = (mm.Event & ~REG_EVENT_SECTION_Msk) | (val << REG_EVENT_SECTION_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getEvent_section(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.Event & REG_EVENT_SECTION_Msk) >> REG_EVENT_SECTION_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getEvent_sectionFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_EVENT_SECTION_Msk) >> REG_EVENT_SECTION_Pos);
    return mm_OK;
}
mm_response_t mm_setEvent_detail(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Event = (mm.Event & ~REG_EVENT_DETAIL_Msk) | (val << REG_EVENT_DETAIL_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getEvent_detail(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.Event & REG_EVENT_DETAIL_Msk) >> REG_EVENT_DETAIL_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getEvent_detailFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_EVENT_DETAIL_Msk) >> REG_EVENT_DETAIL_Pos);
    return mm_OK;
}
mm_response_t mm_setEvent_timestamp(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.Event = (mm.Event & ~REG_EVENT_TIMESTAMP_Msk) | (val << REG_EVENT_TIMESTAMP_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getEvent_timestamp(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.Event & REG_EVENT_TIMESTAMP_Msk) >> REG_EVENT_TIMESTAMP_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getEvent_timestampFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_EVENT_TIMESTAMP_Msk) >> REG_EVENT_TIMESTAMP_Pos);
    return mm_OK;
}
/*************** Get/Set functions for ConfPower register *********************************************************************/
mm_response_t mm_setConfPower(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfPower = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getConfPower(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.ConfPower;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setConfPower_voltage5Toggle(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfPower = (mm.ConfPower & ~REG_CONFPOWER_VOLTAGE5TOGGLE_Msk) | (val << REG_CONFPOWER_VOLTAGE5TOGGLE_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getConfPower_voltage5Toggle(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.ConfPower & REG_CONFPOWER_VOLTAGE5TOGGLE_Msk) >> REG_CONFPOWER_VOLTAGE5TOGGLE_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getConfPower_voltage5ToggleFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_CONFPOWER_VOLTAGE5TOGGLE_Msk) >> REG_CONFPOWER_VOLTAGE5TOGGLE_Pos);
    return mm_OK;
}
mm_response_t mm_setConfPower_voltage3Toggle(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfPower = (mm.ConfPower & ~REG_CONFPOWER_VOLTAGE3TOGGLE_Msk) | (val << REG_CONFPOWER_VOLTAGE3TOGGLE_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getConfPower_voltage3Toggle(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.ConfPower & REG_CONFPOWER_VOLTAGE3TOGGLE_Msk) >> REG_CONFPOWER_VOLTAGE3TOGGLE_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getConfPower_voltage3ToggleFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_CONFPOWER_VOLTAGE3TOGGLE_Msk) >> REG_CONFPOWER_VOLTAGE3TOGGLE_Pos);
    return mm_OK;
}
mm_response_t mm_setConfPower_voltageVBatToggle(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfPower = (mm.ConfPower & ~REG_CONFPOWER_VOLTAGEVBATTOGGLE_Msk) | (val << REG_CONFPOWER_VOLTAGEVBATTOGGLE_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getConfPower_voltageVBatToggle(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.ConfPower & REG_CONFPOWER_VOLTAGEVBATTOGGLE_Msk) >> REG_CONFPOWER_VOLTAGEVBATTOGGLE_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getConfPower_voltageVBatToggleFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_CONFPOWER_VOLTAGEVBATTOGGLE_Msk) >> REG_CONFPOWER_VOLTAGEVBATTOGGLE_Pos);
    return mm_OK;
}
mm_response_t mm_setConfPower_voltageVBatAltToggle(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfPower = (mm.ConfPower & ~REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Msk) | (val << REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getConfPower_voltageVBatAltToggle(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.ConfPower & REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Msk) >> REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getConfPower_voltageVBatAltToggleFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Msk) >> REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Pos);
    return mm_OK;
}
/*************** Get/Set functions for MeasureVI_V3 register ******************************************************************/
mm_response_t mm_setMeasureVI_V3(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_V3 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_V3(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.MeasureVI_V3;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setMeasureVI_V3_voltage(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_V3 = (mm.MeasureVI_V3 & ~REG_MEASUREVI_VOLTAGE_Msk) | (val << REG_MEASUREVI_VOLTAGE_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_V3_voltage(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.MeasureVI_V3 & REG_MEASUREVI_VOLTAGE_Msk) >> REG_MEASUREVI_VOLTAGE_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasureVI_V3_voltageFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_MEASUREVI_VOLTAGE_Msk) >> REG_MEASUREVI_VOLTAGE_Pos);
    return mm_OK;
}
mm_response_t mm_setMeasureVI_V3_current(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_V3 = (mm.MeasureVI_V3 & ~REG_MEASUREVI_CURRENT_Msk) | (val << REG_MEASUREVI_CURRENT_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_V3_current(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.MeasureVI_V3 & REG_MEASUREVI_CURRENT_Msk) >> REG_MEASUREVI_CURRENT_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasureVI_V3_currentFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_MEASUREVI_CURRENT_Msk) >> REG_MEASUREVI_CURRENT_Pos);
    return mm_OK;
}
/*************** Get/Set functions for MeasurePower_V3 register ***************************************************************/
mm_response_t mm_setMeasurePower_V3(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasurePower_V3 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasurePower_V3(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.MeasurePower_V3;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setMeasurePower_V3_power(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasurePower_V3 = (mm.MeasurePower_V3 & ~REG_MEASUREPOWER_POWER_Msk) | (val << REG_MEASUREPOWER_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasurePower_V3_power(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint32_t) ((mm.MeasurePower_V3 & REG_MEASUREPOWER_POWER_Msk) >> REG_MEASUREPOWER_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasurePower_V3_powerFrom(uint32_t * dest, const uint32_t source) {
    *dest = (uint32_t) ((source & REG_MEASUREPOWER_POWER_Msk) >> REG_MEASUREPOWER_POWER_Pos);
    return mm_OK;
}
/*************** Get/Set functions for MeasureVI_V5 register ******************************************************************/
mm_response_t mm_setMeasureVI_V5(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_V5 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_V5(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.MeasureVI_V5;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setMeasureVI_V5_voltage(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_V5 = (mm.MeasureVI_V5 & ~REG_MEASUREVI_VOLTAGE_Msk) | (val << REG_MEASUREVI_VOLTAGE_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_V5_voltage(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.MeasureVI_V5 & REG_MEASUREVI_VOLTAGE_Msk) >> REG_MEASUREVI_VOLTAGE_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasureVI_V5_voltageFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_MEASUREVI_VOLTAGE_Msk) >> REG_MEASUREVI_VOLTAGE_Pos);
    return mm_OK;
}
mm_response_t mm_setMeasureVI_V5_current(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_V5 = (mm.MeasureVI_V5 & ~REG_MEASUREVI_CURRENT_Msk) | (val << REG_MEASUREVI_CURRENT_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_V5_current(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.MeasureVI_V5 & REG_MEASUREVI_CURRENT_Msk) >> REG_MEASUREVI_CURRENT_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasureVI_V5_currentFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_MEASUREVI_CURRENT_Msk) >> REG_MEASUREVI_CURRENT_Pos);
    return mm_OK;
}
/*************** Get/Set functions for MeasurePower_V5 register ***************************************************************/
mm_response_t mm_setMeasurePower_V5(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasurePower_V5 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasurePower_V5(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.MeasurePower_V5;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setMeasurePower_V5_power(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasurePower_V5 = (mm.MeasurePower_V5 & ~REG_MEASUREPOWER_POWER_Msk) | (val << REG_MEASUREPOWER_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasurePower_V5_power(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint32_t) ((mm.MeasurePower_V5 & REG_MEASUREPOWER_POWER_Msk) >> REG_MEASUREPOWER_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasurePower_V5_powerFrom(uint32_t * dest, const uint32_t source) {
    *dest = (uint32_t) ((source & REG_MEASUREPOWER_POWER_Msk) >> REG_MEASUREPOWER_POWER_Pos);
    return mm_OK;
}
/*************** Get/Set functions for MeasureVI_VBat register ****************************************************************/
mm_response_t mm_setMeasureVI_VBat(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_VBat = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_VBat(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.MeasureVI_VBat;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setMeasureVI_VBat_voltage(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_VBat = (mm.MeasureVI_VBat & ~REG_MEASUREVI_VOLTAGE_Msk) | (val << REG_MEASUREVI_VOLTAGE_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_VBat_voltage(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.MeasureVI_VBat & REG_MEASUREVI_VOLTAGE_Msk) >> REG_MEASUREVI_VOLTAGE_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasureVI_VBat_voltageFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_MEASUREVI_VOLTAGE_Msk) >> REG_MEASUREVI_VOLTAGE_Pos);
    return mm_OK;
}
mm_response_t mm_setMeasureVI_VBat_current(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_VBat = (mm.MeasureVI_VBat & ~REG_MEASUREVI_CURRENT_Msk) | (val << REG_MEASUREVI_CURRENT_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_VBat_current(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.MeasureVI_VBat & REG_MEASUREVI_CURRENT_Msk) >> REG_MEASUREVI_CURRENT_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasureVI_VBat_currentFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_MEASUREVI_CURRENT_Msk) >> REG_MEASUREVI_CURRENT_Pos);
    return mm_OK;
}
/*************** Get/Set functions for MeasurePower_VBat register *************************************************************/
mm_response_t mm_setMeasurePower_VBat(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasurePower_VBat = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasurePower_VBat(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.MeasurePower_VBat;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setMeasurePower_VBat_power(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasurePower_VBat = (mm.MeasurePower_VBat & ~REG_MEASUREPOWER_POWER_Msk) | (val << REG_MEASUREPOWER_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasurePower_VBat_power(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint32_t) ((mm.MeasurePower_VBat & REG_MEASUREPOWER_POWER_Msk) >> REG_MEASUREPOWER_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasurePower_VBat_powerFrom(uint32_t * dest, const uint32_t source) {
    *dest = (uint32_t) ((source & REG_MEASUREPOWER_POWER_Msk) >> REG_MEASUREPOWER_POWER_Pos);
    return mm_OK;
}
/*************** Get/Set functions for MeasureVI_VBatAlt register *************************************************************/
mm_response_t mm_setMeasureVI_VBatAlt(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_VBatAlt = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_VBatAlt(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.MeasureVI_VBatAlt;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setMeasureVI_VBatAlt_voltage(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_VBatAlt = (mm.MeasureVI_VBatAlt & ~REG_MEASUREVI_VOLTAGE_Msk) | (val << REG_MEASUREVI_VOLTAGE_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_VBatAlt_voltage(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.MeasureVI_VBatAlt & REG_MEASUREVI_VOLTAGE_Msk) >> REG_MEASUREVI_VOLTAGE_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasureVI_VBatAlt_voltageFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_MEASUREVI_VOLTAGE_Msk) >> REG_MEASUREVI_VOLTAGE_Pos);
    return mm_OK;
}
mm_response_t mm_setMeasureVI_VBatAlt_current(const uint16_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasureVI_VBatAlt = (mm.MeasureVI_VBatAlt & ~REG_MEASUREVI_CURRENT_Msk) | (val << REG_MEASUREVI_CURRENT_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasureVI_VBatAlt_current(uint16_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint16_t) ((mm.MeasureVI_VBatAlt & REG_MEASUREVI_CURRENT_Msk) >> REG_MEASUREVI_CURRENT_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasureVI_VBatAlt_currentFrom(uint16_t * dest, const uint32_t source) {
    *dest = (uint16_t) ((source & REG_MEASUREVI_CURRENT_Msk) >> REG_MEASUREVI_CURRENT_Pos);
    return mm_OK;
}
/*************** Get/Set functions for MeasurePower_VBatAlt register **********************************************************/
mm_response_t mm_setMeasurePower_VBatAlt(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasurePower_VBatAlt = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasurePower_VBatAlt(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.MeasurePower_VBatAlt;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setMeasurePower_VBatAlt_power(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.MeasurePower_VBatAlt = (mm.MeasurePower_VBatAlt & ~REG_MEASUREPOWER_POWER_Msk) | (val << REG_MEASUREPOWER_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getMeasurePower_VBatAlt_power(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint32_t) ((mm.MeasurePower_VBatAlt & REG_MEASUREPOWER_POWER_Msk) >> REG_MEASUREPOWER_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getMeasurePower_VBatAlt_powerFrom(uint32_t * dest, const uint32_t source) {
    *dest = (uint32_t) ((source & REG_MEASUREPOWER_POWER_Msk) >> REG_MEASUREPOWER_POWER_Pos);
    return mm_OK;
}
/*************** Get/Set functions for I2CConfA register **********************************************************************/
mm_response_t mm_setI2CConfA(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.I2CConfA = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getI2CConfA(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.I2CConfA;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setI2CConfA_TRDEL(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.I2CConfA = (mm.I2CConfA & ~REG_I2CCONFA_TRDEL_Msk) | (val << REG_I2CCONFA_TRDEL_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getI2CConfA_TRDEL(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.I2CConfA & REG_I2CCONFA_TRDEL_Msk) >> REG_I2CCONFA_TRDEL_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getI2CConfA_TRDELFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_I2CCONFA_TRDEL_Msk) >> REG_I2CCONFA_TRDEL_Pos);
    return mm_OK;
}
mm_response_t mm_setI2CConfA_WRDEL(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.I2CConfA = (mm.I2CConfA & ~REG_I2CCONFA_WRDEL_Msk) | (val << REG_I2CCONFA_WRDEL_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getI2CConfA_WRDEL(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.I2CConfA & REG_I2CCONFA_WRDEL_Msk) >> REG_I2CCONFA_WRDEL_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getI2CConfA_WRDELFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_I2CCONFA_WRDEL_Msk) >> REG_I2CCONFA_WRDEL_Pos);
    return mm_OK;
}
mm_response_t mm_setI2CConfA_SPD(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.I2CConfA = (mm.I2CConfA & ~REG_I2CCONFA_SPD_Msk) | (val << REG_I2CCONFA_SPD_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getI2CConfA_SPD(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.I2CConfA & REG_I2CCONFA_SPD_Msk) >> REG_I2CCONFA_SPD_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getI2CConfA_SPDFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_I2CCONFA_SPD_Msk) >> REG_I2CCONFA_SPD_Pos);
    return mm_OK;
}
/*************** Get/Set functions for I2CConfB register **********************************************************************/
mm_response_t mm_setI2CConfB(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.I2CConfB = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getI2CConfB(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.I2CConfB;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setI2CConfB_ADDR(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.I2CConfB = (mm.I2CConfB & ~REG_I2CCONFB_ADDR_Msk) | (val << REG_I2CCONFB_ADDR_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getI2CConfB_ADDR(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.I2CConfB & REG_I2CCONFB_ADDR_Msk) >> REG_I2CCONFB_ADDR_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getI2CConfB_ADDRFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_I2CCONFB_ADDR_Msk) >> REG_I2CCONFB_ADDR_Pos);
    return mm_OK;
}
/*************** Get/Set functions for ConfMulti register *********************************************************************/
mm_response_t mm_setConfMulti(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfMulti = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getConfMulti(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.ConfMulti;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setConfMulti_MEnabled(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfMulti = (mm.ConfMulti & ~REG_CONFMULTI_MENABLED_Msk) | (val << REG_CONFMULTI_MENABLED_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getConfMulti_MEnabled(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.ConfMulti & REG_CONFMULTI_MENABLED_Msk) >> REG_CONFMULTI_MENABLED_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getConfMulti_MEnabledFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_CONFMULTI_MENABLED_Msk) >> REG_CONFMULTI_MENABLED_Pos);
    return mm_OK;
}
mm_response_t mm_setConfMulti_AutoCLR(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfMulti = (mm.ConfMulti & ~REG_CONFMULTI_AUTOCLR_Msk) | (val << REG_CONFMULTI_AUTOCLR_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getConfMulti_AutoCLR(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.ConfMulti & REG_CONFMULTI_AUTOCLR_Msk) >> REG_CONFMULTI_AUTOCLR_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getConfMulti_AutoCLRFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_CONFMULTI_AUTOCLR_Msk) >> REG_CONFMULTI_AUTOCLR_Pos);
    return mm_OK;
}
mm_response_t mm_setConfMulti_FanPos1(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfMulti = (mm.ConfMulti & ~REG_CONFMULTI_FANPOS1_Msk) | (val << REG_CONFMULTI_FANPOS1_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getConfMulti_FanPos1(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.ConfMulti & REG_CONFMULTI_FANPOS1_Msk) >> REG_CONFMULTI_FANPOS1_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getConfMulti_FanPos1From(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_CONFMULTI_FANPOS1_Msk) >> REG_CONFMULTI_FANPOS1_Pos);
    return mm_OK;
}
mm_response_t mm_setConfMulti_FanPos2(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfMulti = (mm.ConfMulti & ~REG_CONFMULTI_FANPOS2_Msk) | (val << REG_CONFMULTI_FANPOS2_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getConfMulti_FanPos2(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.ConfMulti & REG_CONFMULTI_FANPOS2_Msk) >> REG_CONFMULTI_FANPOS2_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getConfMulti_FanPos2From(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_CONFMULTI_FANPOS2_Msk) >> REG_CONFMULTI_FANPOS2_Pos);
    return mm_OK;
}
mm_response_t mm_setConfMulti_FanPos3(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfMulti = (mm.ConfMulti & ~REG_CONFMULTI_FANPOS3_Msk) | (val << REG_CONFMULTI_FANPOS3_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getConfMulti_FanPos3(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.ConfMulti & REG_CONFMULTI_FANPOS3_Msk) >> REG_CONFMULTI_FANPOS3_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getConfMulti_FanPos3From(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_CONFMULTI_FANPOS3_Msk) >> REG_CONFMULTI_FANPOS3_Pos);
    return mm_OK;
}
mm_response_t mm_setConfMulti_FanPos4(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfMulti = (mm.ConfMulti & ~REG_CONFMULTI_FANPOS4_Msk) | (val << REG_CONFMULTI_FANPOS4_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getConfMulti_FanPos4(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.ConfMulti & REG_CONFMULTI_FANPOS4_Msk) >> REG_CONFMULTI_FANPOS4_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getConfMulti_FanPos4From(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_CONFMULTI_FANPOS4_Msk) >> REG_CONFMULTI_FANPOS4_Pos);
    return mm_OK;
}
/*************** Get/Set functions for ConfTempSense register *****************************************************************/
mm_response_t mm_setConfTempSense(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfTempSense = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getConfTempSense(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.ConfTempSense;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setConfTempSense_EnableMeasurements(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.ConfTempSense = (mm.ConfTempSense & ~REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Msk) | (val << REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getConfTempSense_EnableMeasurements(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.ConfTempSense & REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Msk) >> REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getConfTempSense_EnableMeasurementsFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Msk) >> REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Pos);
    return mm_OK;
}
/*************** Get/Set functions for CANConfA register **********************************************************************/
mm_response_t mm_setCANConfA(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CANConfA = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCANConfA(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CANConfA;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setCANConfA_BaudRate(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CANConfA = (mm.CANConfA & ~REG_CANCONFA_BAUDRATE_Msk) | (val << REG_CANCONFA_BAUDRATE_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getCANConfA_BaudRate(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint32_t) ((mm.CANConfA & REG_CANCONFA_BAUDRATE_Msk) >> REG_CANCONFA_BAUDRATE_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getCANConfA_BaudRateFrom(uint32_t * dest, const uint32_t source) {
    *dest = (uint32_t) ((source & REG_CANCONFA_BAUDRATE_Msk) >> REG_CANCONFA_BAUDRATE_Pos);
    return mm_OK;
}
/*************** Get/Set functions for XTXpins register ***********************************************************************/
mm_response_t mm_setXTXpins(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXpins = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXpins(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.XTXpins;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setXTXpins_ENA(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXpins = (mm.XTXpins & ~REG_XTXPINS_ENA_Msk) | (val << REG_XTXPINS_ENA_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXpins_ENA(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXpins & REG_XTXPINS_ENA_Msk) >> REG_XTXPINS_ENA_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXpins_ENAFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXPINS_ENA_Msk) >> REG_XTXPINS_ENA_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXpins_nRST(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXpins = (mm.XTXpins & ~REG_XTXPINS_NRST_Msk) | (val << REG_XTXPINS_NRST_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXpins_nRST(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXpins & REG_XTXPINS_NRST_Msk) >> REG_XTXPINS_NRST_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXpins_nRSTFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXPINS_NRST_Msk) >> REG_XTXPINS_NRST_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXpins_RDY(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXpins = (mm.XTXpins & ~REG_XTXPINS_RDY_Msk) | (val << REG_XTXPINS_RDY_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXpins_RDY(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXpins & REG_XTXPINS_RDY_Msk) >> REG_XTXPINS_RDY_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXpins_RDYFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXPINS_RDY_Msk) >> REG_XTXPINS_RDY_Pos);
    return mm_OK;
}
/*************** Get/Set functions for XTXMultitester register ****************************************************************/
mm_response_t mm_setXTXMultitester(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.XTXMultitester;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setXTXMultitester_POS1_XTX_EN(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS1_XTX_EN_Msk) | (val << REG_XTXMULTITESTER_POS1_XTX_EN_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS1_XTX_EN(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS1_XTX_EN_Msk) >> REG_XTXMULTITESTER_POS1_XTX_EN_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS1_XTX_ENFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS1_XTX_EN_Msk) >> REG_XTXMULTITESTER_POS1_XTX_EN_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXMultitester_POS1_XTX_Power(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS1_XTX_POWER_Msk) | (val << REG_XTXMULTITESTER_POS1_XTX_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS1_XTX_Power(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS1_XTX_POWER_Msk) >> REG_XTXMULTITESTER_POS1_XTX_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS1_XTX_PowerFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS1_XTX_POWER_Msk) >> REG_XTXMULTITESTER_POS1_XTX_POWER_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXMultitester_POS1_XTX_nReset(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS1_XTX_NRESET_Msk) | (val << REG_XTXMULTITESTER_POS1_XTX_NRESET_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS1_XTX_nReset(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS1_XTX_NRESET_Msk) >> REG_XTXMULTITESTER_POS1_XTX_NRESET_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS1_XTX_nResetFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS1_XTX_NRESET_Msk) >> REG_XTXMULTITESTER_POS1_XTX_NRESET_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXMultitester_POS2_XTX_EN(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS2_XTX_EN_Msk) | (val << REG_XTXMULTITESTER_POS2_XTX_EN_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS2_XTX_EN(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS2_XTX_EN_Msk) >> REG_XTXMULTITESTER_POS2_XTX_EN_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS2_XTX_ENFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS2_XTX_EN_Msk) >> REG_XTXMULTITESTER_POS2_XTX_EN_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXMultitester_POS2_XTX_Power(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS2_XTX_POWER_Msk) | (val << REG_XTXMULTITESTER_POS2_XTX_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS2_XTX_Power(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS2_XTX_POWER_Msk) >> REG_XTXMULTITESTER_POS2_XTX_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS2_XTX_PowerFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS2_XTX_POWER_Msk) >> REG_XTXMULTITESTER_POS2_XTX_POWER_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXMultitester_POS2_XTX_nReset(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS2_XTX_NRESET_Msk) | (val << REG_XTXMULTITESTER_POS2_XTX_NRESET_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS2_XTX_nReset(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS2_XTX_NRESET_Msk) >> REG_XTXMULTITESTER_POS2_XTX_NRESET_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS2_XTX_nResetFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS2_XTX_NRESET_Msk) >> REG_XTXMULTITESTER_POS2_XTX_NRESET_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXMultitester_POS3_XTX_EN(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS3_XTX_EN_Msk) | (val << REG_XTXMULTITESTER_POS3_XTX_EN_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS3_XTX_EN(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS3_XTX_EN_Msk) >> REG_XTXMULTITESTER_POS3_XTX_EN_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS3_XTX_ENFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS3_XTX_EN_Msk) >> REG_XTXMULTITESTER_POS3_XTX_EN_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXMultitester_POS3_XTX_Power(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS3_XTX_POWER_Msk) | (val << REG_XTXMULTITESTER_POS3_XTX_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS3_XTX_Power(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS3_XTX_POWER_Msk) >> REG_XTXMULTITESTER_POS3_XTX_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS3_XTX_PowerFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS3_XTX_POWER_Msk) >> REG_XTXMULTITESTER_POS3_XTX_POWER_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXMultitester_POS3_XTX_nReset(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS3_XTX_NRESET_Msk) | (val << REG_XTXMULTITESTER_POS3_XTX_NRESET_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS3_XTX_nReset(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS3_XTX_NRESET_Msk) >> REG_XTXMULTITESTER_POS3_XTX_NRESET_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS3_XTX_nResetFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS3_XTX_NRESET_Msk) >> REG_XTXMULTITESTER_POS3_XTX_NRESET_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXMultitester_POS4_XTX_EN(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS4_XTX_EN_Msk) | (val << REG_XTXMULTITESTER_POS4_XTX_EN_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS4_XTX_EN(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS4_XTX_EN_Msk) >> REG_XTXMULTITESTER_POS4_XTX_EN_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS4_XTX_ENFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS4_XTX_EN_Msk) >> REG_XTXMULTITESTER_POS4_XTX_EN_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXMultitester_POS4_XTX_Power(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS4_XTX_POWER_Msk) | (val << REG_XTXMULTITESTER_POS4_XTX_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS4_XTX_Power(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS4_XTX_POWER_Msk) >> REG_XTXMULTITESTER_POS4_XTX_POWER_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS4_XTX_PowerFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS4_XTX_POWER_Msk) >> REG_XTXMULTITESTER_POS4_XTX_POWER_Pos);
    return mm_OK;
}
mm_response_t mm_setXTXMultitester_POS4_XTX_nReset(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XTXMultitester = (mm.XTXMultitester & ~REG_XTXMULTITESTER_POS4_XTX_NRESET_Msk) | (val << REG_XTXMULTITESTER_POS4_XTX_NRESET_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXTXMultitester_POS4_XTX_nReset(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XTXMultitester & REG_XTXMULTITESTER_POS4_XTX_NRESET_Msk) >> REG_XTXMULTITESTER_POS4_XTX_NRESET_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXTXMultitester_POS4_XTX_nResetFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XTXMULTITESTER_POS4_XTX_NRESET_Msk) >> REG_XTXMULTITESTER_POS4_XTX_NRESET_Pos);
    return mm_OK;
}
/*************** Get/Set functions for RFRelaysConf register ******************************************************************/
mm_response_t mm_setRFRelaysConf(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.RFRelaysConf = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getRFRelaysConf(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.RFRelaysConf;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setRFRelaysConf_RFSW1_Detected(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.RFRelaysConf = (mm.RFRelaysConf & ~REG_RFRELAYSCONF_RFSW1_DETECTED_Msk) | (val << REG_RFRELAYSCONF_RFSW1_DETECTED_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getRFRelaysConf_RFSW1_Detected(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.RFRelaysConf & REG_RFRELAYSCONF_RFSW1_DETECTED_Msk) >> REG_RFRELAYSCONF_RFSW1_DETECTED_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getRFRelaysConf_RFSW1_DetectedFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_RFRELAYSCONF_RFSW1_DETECTED_Msk) >> REG_RFRELAYSCONF_RFSW1_DETECTED_Pos);
    return mm_OK;
}
mm_response_t mm_setRFRelaysConf_RFSW2_Detected(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.RFRelaysConf = (mm.RFRelaysConf & ~REG_RFRELAYSCONF_RFSW2_DETECTED_Msk) | (val << REG_RFRELAYSCONF_RFSW2_DETECTED_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getRFRelaysConf_RFSW2_Detected(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.RFRelaysConf & REG_RFRELAYSCONF_RFSW2_DETECTED_Msk) >> REG_RFRELAYSCONF_RFSW2_DETECTED_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getRFRelaysConf_RFSW2_DetectedFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_RFRELAYSCONF_RFSW2_DETECTED_Msk) >> REG_RFRELAYSCONF_RFSW2_DETECTED_Pos);
    return mm_OK;
}
mm_response_t mm_setRFRelaysConf_RfSw1Chan(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.RFRelaysConf = (mm.RFRelaysConf & ~REG_RFRELAYSCONF_RFSW1CHAN_Msk) | (val << REG_RFRELAYSCONF_RFSW1CHAN_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getRFRelaysConf_RfSw1Chan(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.RFRelaysConf & REG_RFRELAYSCONF_RFSW1CHAN_Msk) >> REG_RFRELAYSCONF_RFSW1CHAN_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getRFRelaysConf_RfSw1ChanFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_RFRELAYSCONF_RFSW1CHAN_Msk) >> REG_RFRELAYSCONF_RFSW1CHAN_Pos);
    return mm_OK;
}
mm_response_t mm_setRFRelaysConf_RfSw2Chan(const uint8_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.RFRelaysConf = (mm.RFRelaysConf & ~REG_RFRELAYSCONF_RFSW2CHAN_Msk) | (val << REG_RFRELAYSCONF_RFSW2CHAN_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getRFRelaysConf_RfSw2Chan(uint8_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (uint8_t) ((mm.RFRelaysConf & REG_RFRELAYSCONF_RFSW2CHAN_Msk) >> REG_RFRELAYSCONF_RFSW2CHAN_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getRFRelaysConf_RfSw2ChanFrom(uint8_t * dest, const uint32_t source) {
    *dest = (uint8_t) ((source & REG_RFRELAYSCONF_RFSW2CHAN_Msk) >> REG_RFRELAYSCONF_RFSW2CHAN_Pos);
    return mm_OK;
}
/*************** Get/Set functions for XDCConfig register *********************************************************************/
mm_response_t mm_setXDCConfig(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XDCConfig = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getXDCConfig(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.XDCConfig;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_setXDCConfig_ADDR(const mm_enabled_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.XDCConfig = (mm.XDCConfig & ~REG_XDCCONFIG_ADDR_Msk) | (val << REG_XDCCONFIG_ADDR_Pos);
        xSemaphoreGive(_mm_mutex);
        return  mm_OK;
    }
        else{
        return mm_NotReady;
    }
}
mm_response_t mm_getXDCConfig_ADDR(mm_enabled_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) 
    {
        *dest = (mm_enabled_t) ((mm.XDCConfig & REG_XDCCONFIG_ADDR_Msk) >> REG_XDCCONFIG_ADDR_Pos);
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    return response;
}

mm_response_t mm_getXDCConfig_ADDRFrom(mm_enabled_t * dest, const uint32_t source) {
    *dest = (mm_enabled_t) ((source & REG_XDCCONFIG_ADDR_Msk) >> REG_XDCCONFIG_ADDR_Pos);
    return mm_OK;
}
/*************** Get/Set functions for CSBoard_T0 register ********************************************************************/
mm_response_t mm_setCSBoard_T0(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_T0 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_T0(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_T0;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_T0From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_T1 register ********************************************************************/
mm_response_t mm_setCSBoard_T1(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_T1 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_T1(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_T1;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_T1From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_T2 register ********************************************************************/
mm_response_t mm_setCSBoard_T2(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_T2 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_T2(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_T2;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_T2From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_T3 register ********************************************************************/
mm_response_t mm_setCSBoard_T3(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_T3 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_T3(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_T3;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_T3From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_T4 register ********************************************************************/
mm_response_t mm_setCSBoard_T4(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_T4 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_T4(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_T4;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_T4From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_T5 register ********************************************************************/
mm_response_t mm_setCSBoard_T5(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_T5 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_T5(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_T5;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_T5From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_T6 register ********************************************************************/
mm_response_t mm_setCSBoard_T6(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_T6 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_T6(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_T6;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_T6From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_T7 register ********************************************************************/
mm_response_t mm_setCSBoard_T7(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_T7 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_T7(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_T7;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_T7From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current0I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current0I0(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current0I0 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current0I0(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current0I0;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current0I0From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current0I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current0I1(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current0I1 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current0I1(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current0I1;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current0I1From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current0I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current0I2(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current0I2 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current0I2(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current0I2;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current0I2From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current1I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current1I0(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current1I0 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current1I0(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current1I0;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current1I0From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current1I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current1I1(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current1I1 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current1I1(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current1I1;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current1I1From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current1I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current1I2(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current1I2 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current1I2(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current1I2;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current1I2From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current2I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current2I0(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current2I0 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current2I0(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current2I0;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current2I0From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current2I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current2I1(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current2I1 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current2I1(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current2I1;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current2I1From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current2I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current2I2(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current2I2 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current2I2(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current2I2;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current2I2From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current3I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current3I0(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current3I0 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current3I0(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current3I0;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current3I0From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current3I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current3I1(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current3I1 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current3I1(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current3I1;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current3I1From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current3I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current3I2(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current3I2 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current3I2(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current3I2;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current3I2From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current4I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current4I0(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current4I0 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current4I0(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current4I0;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current4I0From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current4I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current4I1(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current4I1 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current4I1(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current4I1;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current4I1From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current4I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current4I2(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current4I2 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current4I2(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current4I2;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current4I2From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current5I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current5I0(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current5I0 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current5I0(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current5I0;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current5I0From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current5I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current5I1(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current5I1 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current5I1(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current5I1;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current5I1From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current5I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current5I2(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current5I2 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current5I2(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current5I2;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current5I2From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current6I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current6I0(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current6I0 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current6I0(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current6I0;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current6I0From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current6I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current6I1(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current6I1 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current6I1(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current6I1;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current6I1From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current6I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current6I2(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current6I2 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current6I2(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current6I2;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current6I2From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current7I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current7I0(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current7I0 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current7I0(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current7I0;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current7I0From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current7I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current7I1(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current7I1 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current7I1(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current7I1;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current7I1From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for CSBoard_Current7I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current7I2(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.CSBoard_Current7I2 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getCSBoard_Current7I2(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.CSBoard_Current7I2;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getCSBoard_Current7I2From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_0 register *********************************************************************/
mm_response_t mm_setTE_Addr_0(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_0 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_0(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_0;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_0From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_0_Set register *****************************************************************/
mm_response_t mm_setTE_Addr_0_Set(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_0_Set = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_0_Set(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_0_Set;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_0_SetFrom(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_0_Clr register *****************************************************************/
mm_response_t mm_setTE_Addr_0_Clr(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_0_Clr = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_0_Clr(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_0_Clr;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_0_ClrFrom(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_1 register *********************************************************************/
mm_response_t mm_setTE_Addr_1(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_1 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_1(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_1;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_1From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_1_Set register *****************************************************************/
mm_response_t mm_setTE_Addr_1_Set(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_1_Set = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_1_Set(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_1_Set;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_1_SetFrom(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_1_Clr register *****************************************************************/
mm_response_t mm_setTE_Addr_1_Clr(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_1_Clr = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_1_Clr(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_1_Clr;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_1_ClrFrom(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_2 register *********************************************************************/
mm_response_t mm_setTE_Addr_2(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_2 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_2(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_2;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_2From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_2_Set register *****************************************************************/
mm_response_t mm_setTE_Addr_2_Set(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_2_Set = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_2_Set(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_2_Set;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_2_SetFrom(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_2_Clr register *****************************************************************/
mm_response_t mm_setTE_Addr_2_Clr(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_2_Clr = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_2_Clr(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_2_Clr;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_2_ClrFrom(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_3 register *********************************************************************/
mm_response_t mm_setTE_Addr_3(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_3 = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_3(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_3;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_3From(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_3_Set register *****************************************************************/
mm_response_t mm_setTE_Addr_3_Set(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_3_Set = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_3_Set(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_3_Set;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_3_SetFrom(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


/*************** Get/Set functions for TE_Addr_3_Clr register *****************************************************************/
mm_response_t mm_setTE_Addr_3_Clr(const uint32_t val) {
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        mm.TE_Addr_3_Clr = val;
        xSemaphoreGive(_mm_mutex);
        return mm_OK;
    }
    else {
        return mm_NotReady;
    }
}
mm_response_t mm_getTE_Addr_3_Clr(uint32_t * dest) {
    mm_response_t response = mm_NotReady;
    if(xSemaphoreTake(_mm_mutex, pdMS_TO_TICKS(MEMORY_MAP_MUTEX_WAIT_ms))) {
        *dest = mm.TE_Addr_3_Clr;
        response = mm_OK;
        xSemaphoreGive(_mm_mutex);
    }
    return response;
}
mm_response_t mm_getTE_Addr_3_ClrFrom(uint32_t * dest, const uint32_t source) {
    *dest = source;
    return mm_OK;
}


