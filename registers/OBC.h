#ifndef memory_map_h
#define memory_map_h

#include <stdint.h>
#include <stdbool.h>

// Possible memory map responses
typedef enum {
	mm_OK = 0,
	mm_OutOfRange = 1,
	mm_NotReady = 2,
} mm_response_t;

/*************** Bit definition for Board_ID register ************************/
#define REG_BOARD_ID_CCIDENTIFIER_Pos                (24UL)
#define REG_BOARD_ID_CCIDENTIFIER_Msk                (0x00ff << REG_BOARD_ID_CCIDENTIFIER_Pos)
#define REG_BOARD_ID_ID0_Pos                         (16UL)
#define REG_BOARD_ID_ID0_Msk                         (0x00ff << REG_BOARD_ID_ID0_Pos)
#define REG_BOARD_ID_ID1_Pos                         (8UL)
#define REG_BOARD_ID_ID1_Msk                         (0x00ff << REG_BOARD_ID_ID1_Pos)
#define REG_BOARD_ID_ID2_Pos                         (0UL)
#define REG_BOARD_ID_ID2_Msk                         (0x00ff << REG_BOARD_ID_ID2_Pos)

/*************** Bit definition for Event_ConfA register *********************/
#define REG_EVENT_CONFA_COUNT_Pos                    (0UL)
#define REG_EVENT_CONFA_COUNT_Msk                    (0xffff << REG_EVENT_CONFA_COUNT_Pos)

/*************** Bit definition for Event register ***************************/
#define REG_EVENT_SECTION_Pos                        (24UL)
#define REG_EVENT_SECTION_Msk                        (0x00ff << REG_EVENT_SECTION_Pos)
#define REG_EVENT_DETAIL_Pos                         (16UL)
#define REG_EVENT_DETAIL_Msk                         (0x00ff << REG_EVENT_DETAIL_Pos)
#define REG_EVENT_TIMESTAMP_Pos                      (0UL)
#define REG_EVENT_TIMESTAMP_Msk                      (0xffff << REG_EVENT_TIMESTAMP_Pos)

/*************** Bit definition for ConfPower register ***********************/
#define REG_CONFPOWER_VOLTAGE5TOGGLE_Pos             (0UL)
#define REG_CONFPOWER_VOLTAGE5TOGGLE_Msk             (0x0001 << REG_CONFPOWER_VOLTAGE5TOGGLE_Pos)
#define REG_CONFPOWER_VOLTAGE3TOGGLE_Pos             (1UL)
#define REG_CONFPOWER_VOLTAGE3TOGGLE_Msk             (0x0001 << REG_CONFPOWER_VOLTAGE3TOGGLE_Pos)
#define REG_CONFPOWER_VOLTAGEVBATTOGGLE_Pos          (2UL)
#define REG_CONFPOWER_VOLTAGEVBATTOGGLE_Msk          (0x0001 << REG_CONFPOWER_VOLTAGEVBATTOGGLE_Pos)
#define REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Pos       (3UL)
#define REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Msk       (0x0001 << REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Pos)

/*************** Bit definition for I2CConfA register ************************/
#define REG_I2CCONFA_TRDEL_Pos                       (16UL)
#define REG_I2CCONFA_TRDEL_Msk                       (0x00ff << REG_I2CCONFA_TRDEL_Pos)
#define REG_I2CCONFA_WRDEL_Pos                       (8UL)
#define REG_I2CCONFA_WRDEL_Msk                       (0x00ff << REG_I2CCONFA_WRDEL_Pos)
#define REG_I2CCONFA_SPD_Pos                         (0UL)
#define REG_I2CCONFA_SPD_Msk                         (0x00ff << REG_I2CCONFA_SPD_Pos)

/*************** Bit definition for I2CConfB register ************************/
#define REG_I2CCONFB_ADDR_Pos                        (0UL)
#define REG_I2CCONFB_ADDR_Msk                        (0x00ff << REG_I2CCONFB_ADDR_Pos)

/*************** Bit definition for ConfMulti register ***********************/
#define REG_CONFMULTI_MENABLED_Pos                   (0UL)
#define REG_CONFMULTI_MENABLED_Msk                   (0x0001 << REG_CONFMULTI_MENABLED_Pos)
#define REG_CONFMULTI_AUTOCLR_Pos                    (1UL)
#define REG_CONFMULTI_AUTOCLR_Msk                    (0x0001 << REG_CONFMULTI_AUTOCLR_Pos)
#define REG_CONFMULTI_RFSWENA_Pos                    (2UL)
#define REG_CONFMULTI_RFSWENA_Msk                    (0x0001 << REG_CONFMULTI_RFSWENA_Pos)
#define REG_CONFMULTI_FANPOS1_Pos                    (4UL)
#define REG_CONFMULTI_FANPOS1_Msk                    (0x0001 << REG_CONFMULTI_FANPOS1_Pos)
#define REG_CONFMULTI_FANPOS2_Pos                    (5UL)
#define REG_CONFMULTI_FANPOS2_Msk                    (0x0001 << REG_CONFMULTI_FANPOS2_Pos)
#define REG_CONFMULTI_FANPOS3_Pos                    (6UL)
#define REG_CONFMULTI_FANPOS3_Msk                    (0x0001 << REG_CONFMULTI_FANPOS3_Pos)
#define REG_CONFMULTI_FANPOS4_Pos                    (7UL)
#define REG_CONFMULTI_FANPOS4_Msk                    (0x0001 << REG_CONFMULTI_FANPOS4_Pos)
#define REG_CONFMULTI_RFSWCHAN_Pos                   (8UL)
#define REG_CONFMULTI_RFSWCHAN_Msk                   (0x00ff << REG_CONFMULTI_RFSWCHAN_Pos)

/*************** Bit definition for ConfTempSense register *******************/
#define REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Pos     (0UL)
#define REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Msk     (0x0001 << REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Pos)

/*************** Bit definition for XTXpins register *************************/
#define REG_XTXPINS_ENA_Pos                          (0UL)
#define REG_XTXPINS_ENA_Msk                          (0x0001 << REG_XTXPINS_ENA_Pos)
#define REG_XTXPINS_NRST_Pos                         (1UL)
#define REG_XTXPINS_NRST_Msk                         (0x0001 << REG_XTXPINS_NRST_Pos)
#define REG_XTXPINS_RDY_Pos                          (2UL)
#define REG_XTXPINS_RDY_Msk                          (0x0001 << REG_XTXPINS_RDY_Pos)

/*************** Bit definition for XTXMultitester register ******************/
#define REG_XTXMULTITESTER_POS1_XTX_EN_Pos           (0UL)
#define REG_XTXMULTITESTER_POS1_XTX_EN_Msk           (0x0001 << REG_XTXMULTITESTER_POS1_XTX_EN_Pos)
#define REG_XTXMULTITESTER_POS1_XTX_POWER_Pos        (1UL)
#define REG_XTXMULTITESTER_POS1_XTX_POWER_Msk        (0x0001 << REG_XTXMULTITESTER_POS1_XTX_POWER_Pos)
#define REG_XTXMULTITESTER_POS1_XTX_NRESET_Pos       (2UL)
#define REG_XTXMULTITESTER_POS1_XTX_NRESET_Msk       (0x0001 << REG_XTXMULTITESTER_POS1_XTX_NRESET_Pos)
#define REG_XTXMULTITESTER_POS2_XTX_EN_Pos           (4UL)
#define REG_XTXMULTITESTER_POS2_XTX_EN_Msk           (0x0001 << REG_XTXMULTITESTER_POS2_XTX_EN_Pos)
#define REG_XTXMULTITESTER_POS2_XTX_POWER_Pos        (5UL)
#define REG_XTXMULTITESTER_POS2_XTX_POWER_Msk        (0x0001 << REG_XTXMULTITESTER_POS2_XTX_POWER_Pos)
#define REG_XTXMULTITESTER_POS2_XTX_NRESET_Pos       (6UL)
#define REG_XTXMULTITESTER_POS2_XTX_NRESET_Msk       (0x0001 << REG_XTXMULTITESTER_POS2_XTX_NRESET_Pos)
#define REG_XTXMULTITESTER_POS3_XTX_EN_Pos           (8UL)
#define REG_XTXMULTITESTER_POS3_XTX_EN_Msk           (0x0001 << REG_XTXMULTITESTER_POS3_XTX_EN_Pos)
#define REG_XTXMULTITESTER_POS3_XTX_POWER_Pos        (9UL)
#define REG_XTXMULTITESTER_POS3_XTX_POWER_Msk        (0x0001 << REG_XTXMULTITESTER_POS3_XTX_POWER_Pos)
#define REG_XTXMULTITESTER_POS3_XTX_NRESET_Pos       (10UL)
#define REG_XTXMULTITESTER_POS3_XTX_NRESET_Msk       (0x0001 << REG_XTXMULTITESTER_POS3_XTX_NRESET_Pos)
#define REG_XTXMULTITESTER_POS4_XTX_EN_Pos           (12UL)
#define REG_XTXMULTITESTER_POS4_XTX_EN_Msk           (0x0001 << REG_XTXMULTITESTER_POS4_XTX_EN_Pos)
#define REG_XTXMULTITESTER_POS4_XTX_POWER_Pos        (13UL)
#define REG_XTXMULTITESTER_POS4_XTX_POWER_Msk        (0x0001 << REG_XTXMULTITESTER_POS4_XTX_POWER_Pos)
#define REG_XTXMULTITESTER_POS4_XTX_NRESET_Pos       (14UL)
#define REG_XTXMULTITESTER_POS4_XTX_NRESET_Msk       (0x0001 << REG_XTXMULTITESTER_POS4_XTX_NRESET_Pos)

/*************** Bit definition for XDCConfig register ***********************/
#define REG_XDCCONFIG_ADDR_Pos                       (0UL)
#define REG_XDCCONFIG_ADDR_Msk                       (0x00ff << REG_XDCCONFIG_ADDR_Pos)

/*************** Bit definition for boardflag register ***********************/
#define REG_BOARDFLAG_BOARDS_Pos                     (0UL)
#define REG_BOARDFLAG_BOARDS_Msk                     (0x00ff << REG_BOARDFLAG_BOARDS_Pos)

/*************** Bit definition for Version register *************************/
#define REG_VERSION_MAJOR_VERSION_Pos                (16UL)
#define REG_VERSION_MAJOR_VERSION_Msk                (0x00ff << REG_VERSION_MAJOR_VERSION_Pos)
#define REG_VERSION_MINOR_VERSION_Pos                (8UL)
#define REG_VERSION_MINOR_VERSION_Msk                (0x00ff << REG_VERSION_MINOR_VERSION_Pos)
#define REG_VERSION_PATCH_VERSION_Pos                (0UL)
#define REG_VERSION_PATCH_VERSION_Msk                (0x00ff << REG_VERSION_PATCH_VERSION_Pos)

/*************** Bit definition for MeasureVI register ***********************/
#define REG_MEASUREVI_VOLTAGE_Pos                    (16UL)
#define REG_MEASUREVI_VOLTAGE_Msk                    (0xffff << REG_MEASUREVI_VOLTAGE_Pos)
#define REG_MEASUREVI_CURRENT_Pos                    (0UL)
#define REG_MEASUREVI_CURRENT_Msk                    (0xffff << REG_MEASUREVI_CURRENT_Pos)

/*************** Bit definition for MeasurePower register ********************/
#define REG_MEASUREPOWER_POWER_Pos                   (0UL)
#define REG_MEASUREPOWER_POWER_Msk                   (0xffffffff << REG_MEASUREPOWER_POWER_Pos)


typedef struct {
    uint32_t Board_ID;
    uint32_t FW_Version;
    uint32_t HW_Version;
    uint32_t Scratchpad;
    uint32_t Supported_Boards;
    uint32_t Configured_Boards;
    uint32_t Uptime;
    uint32_t Event_ConfA;
    uint32_t Event;
    uint32_t ConfPower;
    uint32_t MeasureVI_V3;
    uint32_t MeasurePower_V3;
    uint32_t MeasureVI_V5;
    uint32_t MeasurePower_V5;
    uint32_t MeasureVI_VBat;
    uint32_t MeasurePower_VBat;
    uint32_t MeasureVI_VBatAlt;
    uint32_t MeasurePower_VBatAlt;
    uint32_t I2CConfA;
    uint32_t I2CConfB;
    uint32_t ConfMulti;
    uint32_t ConfTempSense;
    uint32_t XTXpins;
    uint32_t XTXMultitester;
    uint32_t XDCConfig;
    uint32_t CSBoard_T0;
    uint32_t CSBoard_T1;
    uint32_t CSBoard_T2;
    uint32_t CSBoard_T3;
    uint32_t CSBoard_T4;
    uint32_t CSBoard_T5;
    uint32_t CSBoard_T6;
    uint32_t CSBoard_T7;
    uint32_t CSBoard_Current0I0;
    uint32_t CSBoard_Current0I1;
    uint32_t CSBoard_Current0I2;
    uint32_t CSBoard_Current1I0;
    uint32_t CSBoard_Current1I1;
    uint32_t CSBoard_Current1I2;
    uint32_t CSBoard_Current2I0;
    uint32_t CSBoard_Current2I1;
    uint32_t CSBoard_Current2I2;
    uint32_t CSBoard_Current3I0;
    uint32_t CSBoard_Current3I1;
    uint32_t CSBoard_Current3I2;
    uint32_t CSBoard_Current4I0;
    uint32_t CSBoard_Current4I1;
    uint32_t CSBoard_Current4I2;
    uint32_t CSBoard_Current5I0;
    uint32_t CSBoard_Current5I1;
    uint32_t CSBoard_Current5I2;
    uint32_t CSBoard_Current6I0;
    uint32_t CSBoard_Current6I1;
    uint32_t CSBoard_Current6I2;
    uint32_t CSBoard_Current7I0;
    uint32_t CSBoard_Current7I1;
    uint32_t CSBoard_Current7I2;
} mm_t;

typedef enum {
    reg_Board_ID_addr = 0x10,
    reg_FW_Version_addr = 0x11,
    reg_HW_Version_addr = 0x12,
    reg_Scratchpad_addr = 0x13,
    reg_Supported_Boards_addr = 0x14,
    reg_Configured_Boards_addr = 0x15,
    reg_Uptime_addr = 0x16,
    reg_Event_ConfA_addr = 0x17,
    reg_Event_addr = 0x18,
    reg_ConfPower_addr = 0x20,
    reg_MeasureVI_V3_addr = 0x21,
    reg_MeasurePower_V3_addr = 0x22,
    reg_MeasureVI_V5_addr = 0x23,
    reg_MeasurePower_V5_addr = 0x24,
    reg_MeasureVI_VBat_addr = 0x25,
    reg_MeasurePower_VBat_addr = 0x26,
    reg_MeasureVI_VBatAlt_addr = 0x27,
    reg_MeasurePower_VBatAlt_addr = 0x28,
    reg_I2CConfA_addr = 0x29,
    reg_I2CConfB_addr = 0x2A,
    reg_ConfMulti_addr = 0x2B,
    reg_ConfTempSense_addr = 0x2C,
    reg_XTXpins_addr = 0x30,
    reg_XTXMultitester_addr = 0x31,
    reg_XDCConfig_addr = 0x40,
    reg_CSBoard_T0_addr = 0x50,
    reg_CSBoard_T1_addr = 0x51,
    reg_CSBoard_T2_addr = 0x52,
    reg_CSBoard_T3_addr = 0x53,
    reg_CSBoard_T4_addr = 0x54,
    reg_CSBoard_T5_addr = 0x55,
    reg_CSBoard_T6_addr = 0x56,
    reg_CSBoard_T7_addr = 0x57,
    reg_CSBoard_Current0I0_addr = 0x58,
    reg_CSBoard_Current0I1_addr = 0x59,
    reg_CSBoard_Current0I2_addr = 0x5A,
    reg_CSBoard_Current1I0_addr = 0x5B,
    reg_CSBoard_Current1I1_addr = 0x5C,
    reg_CSBoard_Current1I2_addr = 0x5D,
    reg_CSBoard_Current2I0_addr = 0x5E,
    reg_CSBoard_Current2I1_addr = 0x5F,
    reg_CSBoard_Current2I2_addr = 0x60,
    reg_CSBoard_Current3I0_addr = 0x61,
    reg_CSBoard_Current3I1_addr = 0x62,
    reg_CSBoard_Current3I2_addr = 0x63,
    reg_CSBoard_Current4I0_addr = 0x64,
    reg_CSBoard_Current4I1_addr = 0x65,
    reg_CSBoard_Current4I2_addr = 0x66,
    reg_CSBoard_Current5I0_addr = 0x67,
    reg_CSBoard_Current5I1_addr = 0x68,
    reg_CSBoard_Current5I2_addr = 0x69,
    reg_CSBoard_Current6I0_addr = 0x6A,
    reg_CSBoard_Current6I1_addr = 0x6B,
    reg_CSBoard_Current6I2_addr = 0x6C,
    reg_CSBoard_Current7I0_addr = 0x6D,
    reg_CSBoard_Current7I1_addr = 0x6E,
    reg_CSBoard_Current7I2_addr = 0x6F,
} mm_register_address_t;

typedef enum {
    reg_enabled_enabled = 1,                        // Enabled
    reg_enabled_disabled = 0,                       // Disabled
} mm_enabled_t;

typedef enum {
    reg_boardidentifier_none = 0,                   // Disabled
    reg_boardidentifier_xtx = 1,                    // XTX
    reg_boardidentifier_xsteer = 2,                 // XSTEER
    reg_boardidentifier_xdc = 4,                    // XDC
    reg_boardidentifier_hdrtx_dfa = 8,              // HDRTX(DFA)
    reg_boardidentifier_hdrtx = 16,                 // HDRTX
} mm_boardidentifier_t;

void mm_init(void);
mm_t * get_mm_ptr(void);

/*************** Get/Set functions for Board_ID register **********************************************************************/
mm_response_t mm_setBoard_ID(const uint32_t val);
mm_response_t mm_getBoard_ID(uint32_t * dest);
mm_response_t mm_setBoard_ID_ccIdentifier(const uint8_t val);
mm_response_t mm_getBoard_ID_ccIdentifier(uint8_t * dest);
mm_response_t mm_getBoard_ID_ccIdentifierFrom(uint8_t * dest, const uint32_t source);
mm_response_t mm_setBoard_ID_id0(const uint8_t val);
mm_response_t mm_getBoard_ID_id0(uint8_t * dest);
mm_response_t mm_getBoard_ID_id0From(uint8_t * dest, const uint32_t source);
mm_response_t mm_setBoard_ID_id1(const uint8_t val);
mm_response_t mm_getBoard_ID_id1(uint8_t * dest);
mm_response_t mm_getBoard_ID_id1From(uint8_t * dest, const uint32_t source);
mm_response_t mm_setBoard_ID_id2(const uint8_t val);
mm_response_t mm_getBoard_ID_id2(uint8_t * dest);
mm_response_t mm_getBoard_ID_id2From(uint8_t * dest, const uint32_t source);

/*************** Get/Set functions for FW_Version register ********************************************************************/
mm_response_t mm_setFW_Version(const uint32_t val);
mm_response_t mm_getFW_Version(uint32_t * dest);
mm_response_t mm_setFW_Version_major_version(const uint8_t val);
mm_response_t mm_getFW_Version_major_version(uint8_t * dest);
mm_response_t mm_getFW_Version_major_versionFrom(uint8_t * dest, const uint32_t source);
mm_response_t mm_setFW_Version_minor_version(const uint8_t val);
mm_response_t mm_getFW_Version_minor_version(uint8_t * dest);
mm_response_t mm_getFW_Version_minor_versionFrom(uint8_t * dest, const uint32_t source);
mm_response_t mm_setFW_Version_patch_version(const uint8_t val);
mm_response_t mm_getFW_Version_patch_version(uint8_t * dest);
mm_response_t mm_getFW_Version_patch_versionFrom(uint8_t * dest, const uint32_t source);

/*************** Get/Set functions for HW_Version register ********************************************************************/
mm_response_t mm_setHW_Version(const uint32_t val);
mm_response_t mm_getHW_Version(uint32_t * dest);
mm_response_t mm_setHW_Version_major_version(const uint8_t val);
mm_response_t mm_getHW_Version_major_version(uint8_t * dest);
mm_response_t mm_getHW_Version_major_versionFrom(uint8_t * dest, const uint32_t source);
mm_response_t mm_setHW_Version_minor_version(const uint8_t val);
mm_response_t mm_getHW_Version_minor_version(uint8_t * dest);
mm_response_t mm_getHW_Version_minor_versionFrom(uint8_t * dest, const uint32_t source);
mm_response_t mm_setHW_Version_patch_version(const uint8_t val);
mm_response_t mm_getHW_Version_patch_version(uint8_t * dest);
mm_response_t mm_getHW_Version_patch_versionFrom(uint8_t * dest, const uint32_t source);

/*************** Get/Set functions for Scratchpad register ********************************************************************/
mm_response_t mm_setScratchpad(const uint32_t val);
mm_response_t mm_getScratchpad(uint32_t * dest);
mm_response_t mm_getScratchpadFrom(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for Supported_Boards register **************************************************************/
mm_response_t mm_setSupported_Boards(const uint32_t val);
mm_response_t mm_getSupported_Boards(uint32_t * dest);
mm_response_t mm_getSupported_BoardsFrom(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for Configured_Boards register *************************************************************/
mm_response_t mm_setConfigured_Boards(const uint32_t val);
mm_response_t mm_getConfigured_Boards(uint32_t * dest);
mm_response_t mm_getConfigured_BoardsFrom(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for Uptime register ************************************************************************/
mm_response_t mm_setUptime(const uint32_t val);
mm_response_t mm_getUptime(uint32_t * dest);
mm_response_t mm_getUptimeFrom(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for Event_ConfA register *******************************************************************/
mm_response_t mm_setEvent_ConfA(const uint32_t val);
mm_response_t mm_getEvent_ConfA(uint32_t * dest);
mm_response_t mm_setEvent_ConfA_count(const uint16_t val);
mm_response_t mm_getEvent_ConfA_count(uint16_t * dest);
mm_response_t mm_getEvent_ConfA_countFrom(uint16_t * dest, const uint32_t source);

/*************** Get/Set functions for Event register *************************************************************************/
mm_response_t mm_setEvent(const uint32_t val);
mm_response_t mm_getEvent(uint32_t * dest);
mm_response_t mm_setEvent_section(const uint16_t val);
mm_response_t mm_getEvent_section(uint16_t * dest);
mm_response_t mm_getEvent_sectionFrom(uint16_t * dest, const uint32_t source);
mm_response_t mm_setEvent_detail(const uint16_t val);
mm_response_t mm_getEvent_detail(uint16_t * dest);
mm_response_t mm_getEvent_detailFrom(uint16_t * dest, const uint32_t source);
mm_response_t mm_setEvent_timestamp(const uint16_t val);
mm_response_t mm_getEvent_timestamp(uint16_t * dest);
mm_response_t mm_getEvent_timestampFrom(uint16_t * dest, const uint32_t source);

/*************** Get/Set functions for ConfPower register *********************************************************************/
mm_response_t mm_setConfPower(const uint32_t val);
mm_response_t mm_getConfPower(uint32_t * dest);
mm_response_t mm_setConfPower_voltage5Toggle(const mm_enabled_t val);
mm_response_t mm_getConfPower_voltage5Toggle(mm_enabled_t * dest);
mm_response_t mm_getConfPower_voltage5ToggleFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setConfPower_voltage3Toggle(const mm_enabled_t val);
mm_response_t mm_getConfPower_voltage3Toggle(mm_enabled_t * dest);
mm_response_t mm_getConfPower_voltage3ToggleFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setConfPower_voltageVBatToggle(const mm_enabled_t val);
mm_response_t mm_getConfPower_voltageVBatToggle(mm_enabled_t * dest);
mm_response_t mm_getConfPower_voltageVBatToggleFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setConfPower_voltageVBatAltToggle(const mm_enabled_t val);
mm_response_t mm_getConfPower_voltageVBatAltToggle(mm_enabled_t * dest);
mm_response_t mm_getConfPower_voltageVBatAltToggleFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for MeasureVI_V3 register ******************************************************************/
mm_response_t mm_setMeasureVI_V3(const uint32_t val);
mm_response_t mm_getMeasureVI_V3(uint32_t * dest);
mm_response_t mm_setMeasureVI_V3_voltage(const uint16_t val);
mm_response_t mm_getMeasureVI_V3_voltage(uint16_t * dest);
mm_response_t mm_getMeasureVI_V3_voltageFrom(uint16_t * dest, const uint32_t source);
mm_response_t mm_setMeasureVI_V3_current(const uint16_t val);
mm_response_t mm_getMeasureVI_V3_current(uint16_t * dest);
mm_response_t mm_getMeasureVI_V3_currentFrom(uint16_t * dest, const uint32_t source);

/*************** Get/Set functions for MeasurePower_V3 register ***************************************************************/
mm_response_t mm_setMeasurePower_V3(const uint32_t val);
mm_response_t mm_getMeasurePower_V3(uint32_t * dest);
mm_response_t mm_setMeasurePower_V3_power(const uint32_t val);
mm_response_t mm_getMeasurePower_V3_power(uint32_t * dest);
mm_response_t mm_getMeasurePower_V3_powerFrom(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for MeasureVI_V5 register ******************************************************************/
mm_response_t mm_setMeasureVI_V5(const uint32_t val);
mm_response_t mm_getMeasureVI_V5(uint32_t * dest);
mm_response_t mm_setMeasureVI_V5_voltage(const uint16_t val);
mm_response_t mm_getMeasureVI_V5_voltage(uint16_t * dest);
mm_response_t mm_getMeasureVI_V5_voltageFrom(uint16_t * dest, const uint32_t source);
mm_response_t mm_setMeasureVI_V5_current(const uint16_t val);
mm_response_t mm_getMeasureVI_V5_current(uint16_t * dest);
mm_response_t mm_getMeasureVI_V5_currentFrom(uint16_t * dest, const uint32_t source);

/*************** Get/Set functions for MeasurePower_V5 register ***************************************************************/
mm_response_t mm_setMeasurePower_V5(const uint32_t val);
mm_response_t mm_getMeasurePower_V5(uint32_t * dest);
mm_response_t mm_setMeasurePower_V5_power(const uint32_t val);
mm_response_t mm_getMeasurePower_V5_power(uint32_t * dest);
mm_response_t mm_getMeasurePower_V5_powerFrom(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for MeasureVI_VBat register ****************************************************************/
mm_response_t mm_setMeasureVI_VBat(const uint32_t val);
mm_response_t mm_getMeasureVI_VBat(uint32_t * dest);
mm_response_t mm_setMeasureVI_VBat_voltage(const uint16_t val);
mm_response_t mm_getMeasureVI_VBat_voltage(uint16_t * dest);
mm_response_t mm_getMeasureVI_VBat_voltageFrom(uint16_t * dest, const uint32_t source);
mm_response_t mm_setMeasureVI_VBat_current(const uint16_t val);
mm_response_t mm_getMeasureVI_VBat_current(uint16_t * dest);
mm_response_t mm_getMeasureVI_VBat_currentFrom(uint16_t * dest, const uint32_t source);

/*************** Get/Set functions for MeasurePower_VBat register *************************************************************/
mm_response_t mm_setMeasurePower_VBat(const uint32_t val);
mm_response_t mm_getMeasurePower_VBat(uint32_t * dest);
mm_response_t mm_setMeasurePower_VBat_power(const uint32_t val);
mm_response_t mm_getMeasurePower_VBat_power(uint32_t * dest);
mm_response_t mm_getMeasurePower_VBat_powerFrom(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for MeasureVI_VBatAlt register *************************************************************/
mm_response_t mm_setMeasureVI_VBatAlt(const uint32_t val);
mm_response_t mm_getMeasureVI_VBatAlt(uint32_t * dest);
mm_response_t mm_setMeasureVI_VBatAlt_voltage(const uint16_t val);
mm_response_t mm_getMeasureVI_VBatAlt_voltage(uint16_t * dest);
mm_response_t mm_getMeasureVI_VBatAlt_voltageFrom(uint16_t * dest, const uint32_t source);
mm_response_t mm_setMeasureVI_VBatAlt_current(const uint16_t val);
mm_response_t mm_getMeasureVI_VBatAlt_current(uint16_t * dest);
mm_response_t mm_getMeasureVI_VBatAlt_currentFrom(uint16_t * dest, const uint32_t source);

/*************** Get/Set functions for MeasurePower_VBatAlt register **********************************************************/
mm_response_t mm_setMeasurePower_VBatAlt(const uint32_t val);
mm_response_t mm_getMeasurePower_VBatAlt(uint32_t * dest);
mm_response_t mm_setMeasurePower_VBatAlt_power(const uint32_t val);
mm_response_t mm_getMeasurePower_VBatAlt_power(uint32_t * dest);
mm_response_t mm_getMeasurePower_VBatAlt_powerFrom(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for I2CConfA register **********************************************************************/
mm_response_t mm_setI2CConfA(const uint32_t val);
mm_response_t mm_getI2CConfA(uint32_t * dest);
mm_response_t mm_setI2CConfA_TRDEL(const uint8_t val);
mm_response_t mm_getI2CConfA_TRDEL(uint8_t * dest);
mm_response_t mm_getI2CConfA_TRDELFrom(uint8_t * dest, const uint32_t source);
mm_response_t mm_setI2CConfA_WRDEL(const uint8_t val);
mm_response_t mm_getI2CConfA_WRDEL(uint8_t * dest);
mm_response_t mm_getI2CConfA_WRDELFrom(uint8_t * dest, const uint32_t source);
mm_response_t mm_setI2CConfA_SPD(const uint8_t val);
mm_response_t mm_getI2CConfA_SPD(uint8_t * dest);
mm_response_t mm_getI2CConfA_SPDFrom(uint8_t * dest, const uint32_t source);

/*************** Get/Set functions for I2CConfB register **********************************************************************/
mm_response_t mm_setI2CConfB(const uint32_t val);
mm_response_t mm_getI2CConfB(uint32_t * dest);
mm_response_t mm_setI2CConfB_ADDR(const uint8_t val);
mm_response_t mm_getI2CConfB_ADDR(uint8_t * dest);
mm_response_t mm_getI2CConfB_ADDRFrom(uint8_t * dest, const uint32_t source);

/*************** Get/Set functions for ConfMulti register *********************************************************************/
mm_response_t mm_setConfMulti(const uint32_t val);
mm_response_t mm_getConfMulti(uint32_t * dest);
mm_response_t mm_setConfMulti_MEnabled(const mm_enabled_t val);
mm_response_t mm_getConfMulti_MEnabled(mm_enabled_t * dest);
mm_response_t mm_getConfMulti_MEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setConfMulti_AutoCLR(const mm_enabled_t val);
mm_response_t mm_getConfMulti_AutoCLR(mm_enabled_t * dest);
mm_response_t mm_getConfMulti_AutoCLRFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setConfMulti_RfSwENA(const mm_enabled_t val);
mm_response_t mm_getConfMulti_RfSwENA(mm_enabled_t * dest);
mm_response_t mm_getConfMulti_RfSwENAFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setConfMulti_FanPos1(const mm_enabled_t val);
mm_response_t mm_getConfMulti_FanPos1(mm_enabled_t * dest);
mm_response_t mm_getConfMulti_FanPos1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setConfMulti_FanPos2(const mm_enabled_t val);
mm_response_t mm_getConfMulti_FanPos2(mm_enabled_t * dest);
mm_response_t mm_getConfMulti_FanPos2From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setConfMulti_FanPos3(const mm_enabled_t val);
mm_response_t mm_getConfMulti_FanPos3(mm_enabled_t * dest);
mm_response_t mm_getConfMulti_FanPos3From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setConfMulti_FanPos4(const mm_enabled_t val);
mm_response_t mm_getConfMulti_FanPos4(mm_enabled_t * dest);
mm_response_t mm_getConfMulti_FanPos4From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setConfMulti_RfSwChan(const uint8_t val);
mm_response_t mm_getConfMulti_RfSwChan(uint8_t * dest);
mm_response_t mm_getConfMulti_RfSwChanFrom(uint8_t * dest, const uint32_t source);

/*************** Get/Set functions for ConfTempSense register *****************************************************************/
mm_response_t mm_setConfTempSense(const uint32_t val);
mm_response_t mm_getConfTempSense(uint32_t * dest);
mm_response_t mm_setConfTempSense_EnableMeasurements(const mm_enabled_t val);
mm_response_t mm_getConfTempSense_EnableMeasurements(mm_enabled_t * dest);
mm_response_t mm_getConfTempSense_EnableMeasurementsFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for XTXpins register ***********************************************************************/
mm_response_t mm_setXTXpins(const uint32_t val);
mm_response_t mm_getXTXpins(uint32_t * dest);
mm_response_t mm_setXTXpins_ENA(const mm_enabled_t val);
mm_response_t mm_getXTXpins_ENA(mm_enabled_t * dest);
mm_response_t mm_getXTXpins_ENAFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXpins_nRST(const mm_enabled_t val);
mm_response_t mm_getXTXpins_nRST(mm_enabled_t * dest);
mm_response_t mm_getXTXpins_nRSTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXpins_RDY(const mm_enabled_t val);
mm_response_t mm_getXTXpins_RDY(mm_enabled_t * dest);
mm_response_t mm_getXTXpins_RDYFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for XTXMultitester register ****************************************************************/
mm_response_t mm_setXTXMultitester(const uint32_t val);
mm_response_t mm_getXTXMultitester(uint32_t * dest);
mm_response_t mm_setXTXMultitester_POS1_XTX_EN(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS1_XTX_EN(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS1_XTX_ENFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXMultitester_POS1_XTX_Power(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS1_XTX_Power(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS1_XTX_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXMultitester_POS1_XTX_nReset(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS1_XTX_nReset(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS1_XTX_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXMultitester_POS2_XTX_EN(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS2_XTX_EN(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS2_XTX_ENFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXMultitester_POS2_XTX_Power(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS2_XTX_Power(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS2_XTX_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXMultitester_POS2_XTX_nReset(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS2_XTX_nReset(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS2_XTX_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXMultitester_POS3_XTX_EN(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS3_XTX_EN(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS3_XTX_ENFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXMultitester_POS3_XTX_Power(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS3_XTX_Power(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS3_XTX_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXMultitester_POS3_XTX_nReset(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS3_XTX_nReset(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS3_XTX_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXMultitester_POS4_XTX_EN(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS4_XTX_EN(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS4_XTX_ENFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXMultitester_POS4_XTX_Power(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS4_XTX_Power(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS4_XTX_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setXTXMultitester_POS4_XTX_nReset(const mm_enabled_t val);
mm_response_t mm_getXTXMultitester_POS4_XTX_nReset(mm_enabled_t * dest);
mm_response_t mm_getXTXMultitester_POS4_XTX_nResetFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for XDCConfig register *********************************************************************/
mm_response_t mm_setXDCConfig(const uint32_t val);
mm_response_t mm_getXDCConfig(uint32_t * dest);
mm_response_t mm_setXDCConfig_ADDR(const mm_enabled_t val);
mm_response_t mm_getXDCConfig_ADDR(mm_enabled_t * dest);
mm_response_t mm_getXDCConfig_ADDRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_T0 register ********************************************************************/
mm_response_t mm_setCSBoard_T0(const uint32_t val);
mm_response_t mm_getCSBoard_T0(uint32_t * dest);
mm_response_t mm_getCSBoard_T0From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_T1 register ********************************************************************/
mm_response_t mm_setCSBoard_T1(const uint32_t val);
mm_response_t mm_getCSBoard_T1(uint32_t * dest);
mm_response_t mm_getCSBoard_T1From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_T2 register ********************************************************************/
mm_response_t mm_setCSBoard_T2(const uint32_t val);
mm_response_t mm_getCSBoard_T2(uint32_t * dest);
mm_response_t mm_getCSBoard_T2From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_T3 register ********************************************************************/
mm_response_t mm_setCSBoard_T3(const uint32_t val);
mm_response_t mm_getCSBoard_T3(uint32_t * dest);
mm_response_t mm_getCSBoard_T3From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_T4 register ********************************************************************/
mm_response_t mm_setCSBoard_T4(const uint32_t val);
mm_response_t mm_getCSBoard_T4(uint32_t * dest);
mm_response_t mm_getCSBoard_T4From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_T5 register ********************************************************************/
mm_response_t mm_setCSBoard_T5(const uint32_t val);
mm_response_t mm_getCSBoard_T5(uint32_t * dest);
mm_response_t mm_getCSBoard_T5From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_T6 register ********************************************************************/
mm_response_t mm_setCSBoard_T6(const uint32_t val);
mm_response_t mm_getCSBoard_T6(uint32_t * dest);
mm_response_t mm_getCSBoard_T6From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_T7 register ********************************************************************/
mm_response_t mm_setCSBoard_T7(const uint32_t val);
mm_response_t mm_getCSBoard_T7(uint32_t * dest);
mm_response_t mm_getCSBoard_T7From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current0I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current0I0(const uint32_t val);
mm_response_t mm_getCSBoard_Current0I0(uint32_t * dest);
mm_response_t mm_getCSBoard_Current0I0From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current0I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current0I1(const uint32_t val);
mm_response_t mm_getCSBoard_Current0I1(uint32_t * dest);
mm_response_t mm_getCSBoard_Current0I1From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current0I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current0I2(const uint32_t val);
mm_response_t mm_getCSBoard_Current0I2(uint32_t * dest);
mm_response_t mm_getCSBoard_Current0I2From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current1I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current1I0(const uint32_t val);
mm_response_t mm_getCSBoard_Current1I0(uint32_t * dest);
mm_response_t mm_getCSBoard_Current1I0From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current1I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current1I1(const uint32_t val);
mm_response_t mm_getCSBoard_Current1I1(uint32_t * dest);
mm_response_t mm_getCSBoard_Current1I1From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current1I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current1I2(const uint32_t val);
mm_response_t mm_getCSBoard_Current1I2(uint32_t * dest);
mm_response_t mm_getCSBoard_Current1I2From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current2I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current2I0(const uint32_t val);
mm_response_t mm_getCSBoard_Current2I0(uint32_t * dest);
mm_response_t mm_getCSBoard_Current2I0From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current2I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current2I1(const uint32_t val);
mm_response_t mm_getCSBoard_Current2I1(uint32_t * dest);
mm_response_t mm_getCSBoard_Current2I1From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current2I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current2I2(const uint32_t val);
mm_response_t mm_getCSBoard_Current2I2(uint32_t * dest);
mm_response_t mm_getCSBoard_Current2I2From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current3I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current3I0(const uint32_t val);
mm_response_t mm_getCSBoard_Current3I0(uint32_t * dest);
mm_response_t mm_getCSBoard_Current3I0From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current3I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current3I1(const uint32_t val);
mm_response_t mm_getCSBoard_Current3I1(uint32_t * dest);
mm_response_t mm_getCSBoard_Current3I1From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current3I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current3I2(const uint32_t val);
mm_response_t mm_getCSBoard_Current3I2(uint32_t * dest);
mm_response_t mm_getCSBoard_Current3I2From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current4I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current4I0(const uint32_t val);
mm_response_t mm_getCSBoard_Current4I0(uint32_t * dest);
mm_response_t mm_getCSBoard_Current4I0From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current4I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current4I1(const uint32_t val);
mm_response_t mm_getCSBoard_Current4I1(uint32_t * dest);
mm_response_t mm_getCSBoard_Current4I1From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current4I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current4I2(const uint32_t val);
mm_response_t mm_getCSBoard_Current4I2(uint32_t * dest);
mm_response_t mm_getCSBoard_Current4I2From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current5I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current5I0(const uint32_t val);
mm_response_t mm_getCSBoard_Current5I0(uint32_t * dest);
mm_response_t mm_getCSBoard_Current5I0From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current5I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current5I1(const uint32_t val);
mm_response_t mm_getCSBoard_Current5I1(uint32_t * dest);
mm_response_t mm_getCSBoard_Current5I1From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current5I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current5I2(const uint32_t val);
mm_response_t mm_getCSBoard_Current5I2(uint32_t * dest);
mm_response_t mm_getCSBoard_Current5I2From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current6I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current6I0(const uint32_t val);
mm_response_t mm_getCSBoard_Current6I0(uint32_t * dest);
mm_response_t mm_getCSBoard_Current6I0From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current6I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current6I1(const uint32_t val);
mm_response_t mm_getCSBoard_Current6I1(uint32_t * dest);
mm_response_t mm_getCSBoard_Current6I1From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current6I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current6I2(const uint32_t val);
mm_response_t mm_getCSBoard_Current6I2(uint32_t * dest);
mm_response_t mm_getCSBoard_Current6I2From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current7I0 register ************************************************************/
mm_response_t mm_setCSBoard_Current7I0(const uint32_t val);
mm_response_t mm_getCSBoard_Current7I0(uint32_t * dest);
mm_response_t mm_getCSBoard_Current7I0From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current7I1 register ************************************************************/
mm_response_t mm_setCSBoard_Current7I1(const uint32_t val);
mm_response_t mm_getCSBoard_Current7I1(uint32_t * dest);
mm_response_t mm_getCSBoard_Current7I1From(uint32_t * dest, const uint32_t source);

/*************** Get/Set functions for CSBoard_Current7I2 register ************************************************************/
mm_response_t mm_setCSBoard_Current7I2(const uint32_t val);
mm_response_t mm_getCSBoard_Current7I2(uint32_t * dest);
mm_response_t mm_getCSBoard_Current7I2From(uint32_t * dest, const uint32_t source);


#endif /* memory_map_h */
