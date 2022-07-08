#ifndef OBC_H_
#define OBC_H_
#include <stdint.h>
#include <stdbool.h>

#define OBC_REG_BOARD_ID                             0x10
#define OBC_REG_FW_VERSION                           0x11
#define OBC_REG_HW_VERSION                           0x12
#define OBC_REG_SCRATCHPAD                           0x13
#define OBC_REG_SUPPORTED_BOARDS                     0x14
#define OBC_REG_CONFIGURED_BOARDS                    0x15
#define OBC_REG_UPTIME                               0x16
#define OBC_REG_EVENT_CONFA                          0x17
#define OBC_REG_EVENT                                0x18
#define OBC_REG_CONFPOWER                            0x20
#define OBC_REG_MEASUREVI_V3                         0x21
#define OBC_REG_MEASUREPOWER_V3                      0x22
#define OBC_REG_MEASUREVI_V5                         0x23
#define OBC_REG_MEASUREPOWER_V5                      0x24
#define OBC_REG_MEASUREVI_VBAT                       0x25
#define OBC_REG_MEASUREPOWER_VBAT                    0x26
#define OBC_REG_MEASUREVI_VBATALT                    0x27
#define OBC_REG_MEASUREPOWER_VBATALT                 0x28
#define OBC_REG_I2CCONFA                             0x29
#define OBC_REG_I2CCONFB                             0x2a
#define OBC_REG_XTXPINS                              0x30
#define OBC_REG_XDCCONFIG                            0x40


/*************** Bit definition for Board_ID register ************************/
#define OBC_REG_BOARD_ID_CCIDENTIFIER_Pos            (24UL)
#define OBC_REG_BOARD_ID_CCIDENTIFIER_Msk            (0x00ff << OBC_REG_BOARD_ID_CCIDENTIFIER_Pos)
#define OBC_REG_BOARD_ID_CCIDENTIFIER                OBC_REG_BOARD_ID_CCIDENTIFIER_Msk
#define OBC_REG_BOARD_ID_ID0_Pos                     (16UL)
#define OBC_REG_BOARD_ID_ID0_Msk                     (0x00ff << OBC_REG_BOARD_ID_ID0_Pos)
#define OBC_REG_BOARD_ID_ID0                         OBC_REG_BOARD_ID_ID0_Msk
#define OBC_REG_BOARD_ID_ID1_Pos                     (8UL)
#define OBC_REG_BOARD_ID_ID1_Msk                     (0x00ff << OBC_REG_BOARD_ID_ID1_Pos)
#define OBC_REG_BOARD_ID_ID1                         OBC_REG_BOARD_ID_ID1_Msk
#define OBC_REG_BOARD_ID_ID2_Pos                     (0UL)
#define OBC_REG_BOARD_ID_ID2_Msk                     (0x00ff << OBC_REG_BOARD_ID_ID2_Pos)
#define OBC_REG_BOARD_ID_ID2                         OBC_REG_BOARD_ID_ID2_Msk

/*************** Bit definition for Event_ConfA register *********************/
#define OBC_REG_EVENT_CONFA_COUNT_Pos                (0UL)
#define OBC_REG_EVENT_CONFA_COUNT_Msk                (0xffff << OBC_REG_EVENT_CONFA_COUNT_Pos)
#define OBC_REG_EVENT_CONFA_COUNT                    OBC_REG_EVENT_CONFA_COUNT_Msk

/*************** Bit definition for Event register ***************************/
#define OBC_REG_EVENT_SECTION_Pos                    (24UL)
#define OBC_REG_EVENT_SECTION_Msk                    (0x00ff << OBC_REG_EVENT_SECTION_Pos)
#define OBC_REG_EVENT_SECTION                        OBC_REG_EVENT_SECTION_Msk
#define OBC_REG_EVENT_DETAIL_Pos                     (16UL)
#define OBC_REG_EVENT_DETAIL_Msk                     (0x00ff << OBC_REG_EVENT_DETAIL_Pos)
#define OBC_REG_EVENT_DETAIL                         OBC_REG_EVENT_DETAIL_Msk
#define OBC_REG_EVENT_TIMESTAMP_Pos                  (0UL)
#define OBC_REG_EVENT_TIMESTAMP_Msk                  (0xffff << OBC_REG_EVENT_TIMESTAMP_Pos)
#define OBC_REG_EVENT_TIMESTAMP                      OBC_REG_EVENT_TIMESTAMP_Msk

/*************** Bit definition for ConfPower register ***********************/
#define OBC_REG_CONFPOWER_VOLTAGE5TOGGLE_Pos         (0UL)
#define OBC_REG_CONFPOWER_VOLTAGE5TOGGLE_Msk         (0x0001 << OBC_REG_CONFPOWER_VOLTAGE5TOGGLE_Pos)
#define OBC_REG_CONFPOWER_VOLTAGE5TOGGLE             OBC_REG_CONFPOWER_VOLTAGE5TOGGLE_Msk
#define OBC_REG_CONFPOWER_VOLTAGE3TOGGLE_Pos         (1UL)
#define OBC_REG_CONFPOWER_VOLTAGE3TOGGLE_Msk         (0x0001 << OBC_REG_CONFPOWER_VOLTAGE3TOGGLE_Pos)
#define OBC_REG_CONFPOWER_VOLTAGE3TOGGLE             OBC_REG_CONFPOWER_VOLTAGE3TOGGLE_Msk
#define OBC_REG_CONFPOWER_VOLTAGEVBATTOGGLE_Pos      (2UL)
#define OBC_REG_CONFPOWER_VOLTAGEVBATTOGGLE_Msk      (0x0001 << OBC_REG_CONFPOWER_VOLTAGEVBATTOGGLE_Pos)
#define OBC_REG_CONFPOWER_VOLTAGEVBATTOGGLE          OBC_REG_CONFPOWER_VOLTAGEVBATTOGGLE_Msk
#define OBC_REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Pos   (3UL)
#define OBC_REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Msk   (0x0001 << OBC_REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Pos)
#define OBC_REG_CONFPOWER_VOLTAGEVBATALTTOGGLE       OBC_REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Msk

/*************** Bit definition for I2CConfA register ************************/
#define OBC_REG_I2CCONFA_TRDEL_Pos                   (16UL)
#define OBC_REG_I2CCONFA_TRDEL_Msk                   (0x00ff << OBC_REG_I2CCONFA_TRDEL_Pos)
#define OBC_REG_I2CCONFA_TRDEL                       OBC_REG_I2CCONFA_TRDEL_Msk
#define OBC_REG_I2CCONFA_WRDEL_Pos                   (8UL)
#define OBC_REG_I2CCONFA_WRDEL_Msk                   (0x00ff << OBC_REG_I2CCONFA_WRDEL_Pos)
#define OBC_REG_I2CCONFA_WRDEL                       OBC_REG_I2CCONFA_WRDEL_Msk
#define OBC_REG_I2CCONFA_SPD_Pos                     (0UL)
#define OBC_REG_I2CCONFA_SPD_Msk                     (0x00ff << OBC_REG_I2CCONFA_SPD_Pos)
#define OBC_REG_I2CCONFA_SPD                         OBC_REG_I2CCONFA_SPD_Msk

/*************** Bit definition for I2CConfB register ************************/
#define OBC_REG_I2CCONFB_ADDR_Pos                    (0UL)
#define OBC_REG_I2CCONFB_ADDR_Msk                    (0x00ff << OBC_REG_I2CCONFB_ADDR_Pos)
#define OBC_REG_I2CCONFB_ADDR                        OBC_REG_I2CCONFB_ADDR_Msk

/*************** Bit definition for XTXpins register *************************/
#define OBC_REG_XTXPINS_ENA_Pos                      (0UL)
#define OBC_REG_XTXPINS_ENA_Msk                      (0x0001 << OBC_REG_XTXPINS_ENA_Pos)
#define OBC_REG_XTXPINS_ENA                          OBC_REG_XTXPINS_ENA_Msk
#define OBC_REG_XTXPINS_NRST_Pos                     (1UL)
#define OBC_REG_XTXPINS_NRST_Msk                     (0x0001 << OBC_REG_XTXPINS_NRST_Pos)
#define OBC_REG_XTXPINS_NRST                         OBC_REG_XTXPINS_NRST_Msk
#define OBC_REG_XTXPINS_RDY_Pos                      (2UL)
#define OBC_REG_XTXPINS_RDY_Msk                      (0x0001 << OBC_REG_XTXPINS_RDY_Pos)
#define OBC_REG_XTXPINS_RDY                          OBC_REG_XTXPINS_RDY_Msk

/*************** Bit definition for XDCConfig register ***********************/
#define OBC_REG_XDCCONFIG_ADDR_Pos                   (0UL)
#define OBC_REG_XDCCONFIG_ADDR_Msk                   (0x00ff << OBC_REG_XDCCONFIG_ADDR_Pos)
#define OBC_REG_XDCCONFIG_ADDR                       OBC_REG_XDCCONFIG_ADDR_Msk

/*************** Bit definition for boardflag register ***********************/
#define OBC_REG_BOARDFLAG_BOARDS_Pos                 (0UL)
#define OBC_REG_BOARDFLAG_BOARDS_Msk                 (0x00ff << OBC_REG_BOARDFLAG_BOARDS_Pos)
#define OBC_REG_BOARDFLAG_BOARDS                     OBC_REG_BOARDFLAG_BOARDS_Msk

/*************** Bit definition for Version register *************************/
#define OBC_REG_VERSION_MAJOR_VERSION_Pos            (16UL)
#define OBC_REG_VERSION_MAJOR_VERSION_Msk            (0x00ff << OBC_REG_VERSION_MAJOR_VERSION_Pos)
#define OBC_REG_VERSION_MAJOR_VERSION                OBC_REG_VERSION_MAJOR_VERSION_Msk
#define OBC_REG_VERSION_MINOR_VERSION_Pos            (8UL)
#define OBC_REG_VERSION_MINOR_VERSION_Msk            (0x00ff << OBC_REG_VERSION_MINOR_VERSION_Pos)
#define OBC_REG_VERSION_MINOR_VERSION                OBC_REG_VERSION_MINOR_VERSION_Msk
#define OBC_REG_VERSION_PATCH_VERSION_Pos            (0UL)
#define OBC_REG_VERSION_PATCH_VERSION_Msk            (0x00ff << OBC_REG_VERSION_PATCH_VERSION_Pos)
#define OBC_REG_VERSION_PATCH_VERSION                OBC_REG_VERSION_PATCH_VERSION_Msk

/*************** Bit definition for MeasureVI register ***********************/
#define OBC_REG_MEASUREVI_VOLTAGE_Pos                (16UL)
#define OBC_REG_MEASUREVI_VOLTAGE_Msk                (0xffff << OBC_REG_MEASUREVI_VOLTAGE_Pos)
#define OBC_REG_MEASUREVI_VOLTAGE                    OBC_REG_MEASUREVI_VOLTAGE_Msk
#define OBC_REG_MEASUREVI_CURRENT_Pos                (0UL)
#define OBC_REG_MEASUREVI_CURRENT_Msk                (0xffff << OBC_REG_MEASUREVI_CURRENT_Pos)
#define OBC_REG_MEASUREVI_CURRENT                    OBC_REG_MEASUREVI_CURRENT_Msk

/*************** Bit definition for MeasurePower register ********************/
#define OBC_REG_MEASUREPOWER_POWER_Pos               (0UL)
#define OBC_REG_MEASUREPOWER_POWER_Msk               (0xffffffff << OBC_REG_MEASUREPOWER_POWER_Pos)
#define OBC_REG_MEASUREPOWER_POWER                   OBC_REG_MEASUREPOWER_POWER_Msk



typedef enum {
    reg_enabled_enabled = 1,                        // Enabled
    reg_enabled_disabled = 0,                       // Disabled
} reg_enabled_t;

typedef enum {
    reg_boardidentifier_none = 0,                   // Disabled
    reg_boardidentifier_xtx = 1,                    // XTX
    reg_boardidentifier_xsteer = 2,                 // XSTEER
    reg_boardidentifier_xdc = 4,                    // XDC
} reg_boardidentifier_t;


typedef struct  {
    uint32_t board_id;
    uint32_t fw_version;
    uint32_t hw_version;
    uint32_t scratchpad;
    uint32_t supported_boards;
    uint32_t configured_boards;
    uint32_t uptime;
    uint32_t event_confa;
    uint32_t event;
    uint8_t confpower;
    uint32_t measurevi_v3;
    uint32_t measurepower_v3;
    uint32_t measurevi_v5;
    uint32_t measurepower_v5;
    uint32_t measurevi_vbat;
    uint32_t measurepower_vbat;
    uint32_t measurevi_vbatalt;
    uint32_t measurepower_vbatalt;
    uint32_t i2cconfa;
    uint32_t i2cconfb;
    uint32_t xtxpins;
    uint32_t xdcconfig;
} OBC_RegisterData_t;

static inline uint32_t REG_Get_Board_ID_ccIdentifier(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->board_id & OBC_REG_BOARD_ID_CCIDENTIFIER_Msk) >> OBC_REG_BOARD_ID_CCIDENTIFIER_Pos);
}

static inline void REG_Set_Board_ID_ccIdentifier(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->board_id = (registers->board_id & ~OBC_REG_BOARD_ID_CCIDENTIFIER_Msk) | (value << OBC_REG_BOARD_ID_CCIDENTIFIER_Pos);
}

static inline uint32_t REG_Get_Board_ID_id0(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->board_id & OBC_REG_BOARD_ID_ID0_Msk) >> OBC_REG_BOARD_ID_ID0_Pos);
}

static inline void REG_Set_Board_ID_id0(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->board_id = (registers->board_id & ~OBC_REG_BOARD_ID_ID0_Msk) | (value << OBC_REG_BOARD_ID_ID0_Pos);
}

static inline uint32_t REG_Get_Board_ID_id1(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->board_id & OBC_REG_BOARD_ID_ID1_Msk) >> OBC_REG_BOARD_ID_ID1_Pos);
}

static inline void REG_Set_Board_ID_id1(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->board_id = (registers->board_id & ~OBC_REG_BOARD_ID_ID1_Msk) | (value << OBC_REG_BOARD_ID_ID1_Pos);
}

static inline uint32_t REG_Get_Board_ID_id2(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->board_id & OBC_REG_BOARD_ID_ID2_Msk) >> OBC_REG_BOARD_ID_ID2_Pos);
}

static inline void REG_Set_Board_ID_id2(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->board_id = (registers->board_id & ~OBC_REG_BOARD_ID_ID2_Msk) | (value << OBC_REG_BOARD_ID_ID2_Pos);
}

static inline uint32_t REG_Get_FW_Version_major_version(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->fw_version & OBC_REG_VERSION_MAJOR_VERSION_Msk) >> OBC_REG_VERSION_MAJOR_VERSION_Pos);
}

static inline void REG_Set_FW_Version_major_version(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->fw_version = (registers->fw_version & ~OBC_REG_VERSION_MAJOR_VERSION_Msk) | (value << OBC_REG_VERSION_MAJOR_VERSION_Pos);
}

static inline uint32_t REG_Get_FW_Version_minor_version(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->fw_version & OBC_REG_VERSION_MINOR_VERSION_Msk) >> OBC_REG_VERSION_MINOR_VERSION_Pos);
}

static inline void REG_Set_FW_Version_minor_version(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->fw_version = (registers->fw_version & ~OBC_REG_VERSION_MINOR_VERSION_Msk) | (value << OBC_REG_VERSION_MINOR_VERSION_Pos);
}

static inline uint32_t REG_Get_FW_Version_patch_version(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->fw_version & OBC_REG_VERSION_PATCH_VERSION_Msk) >> OBC_REG_VERSION_PATCH_VERSION_Pos);
}

static inline void REG_Set_FW_Version_patch_version(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->fw_version = (registers->fw_version & ~OBC_REG_VERSION_PATCH_VERSION_Msk) | (value << OBC_REG_VERSION_PATCH_VERSION_Pos);
}

static inline uint32_t REG_Get_HW_Version_major_version(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->hw_version & OBC_REG_VERSION_MAJOR_VERSION_Msk) >> OBC_REG_VERSION_MAJOR_VERSION_Pos);
}

static inline void REG_Set_HW_Version_major_version(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->hw_version = (registers->hw_version & ~OBC_REG_VERSION_MAJOR_VERSION_Msk) | (value << OBC_REG_VERSION_MAJOR_VERSION_Pos);
}

static inline uint32_t REG_Get_HW_Version_minor_version(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->hw_version & OBC_REG_VERSION_MINOR_VERSION_Msk) >> OBC_REG_VERSION_MINOR_VERSION_Pos);
}

static inline void REG_Set_HW_Version_minor_version(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->hw_version = (registers->hw_version & ~OBC_REG_VERSION_MINOR_VERSION_Msk) | (value << OBC_REG_VERSION_MINOR_VERSION_Pos);
}

static inline uint32_t REG_Get_HW_Version_patch_version(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->hw_version & OBC_REG_VERSION_PATCH_VERSION_Msk) >> OBC_REG_VERSION_PATCH_VERSION_Pos);
}

static inline void REG_Set_HW_Version_patch_version(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->hw_version = (registers->hw_version & ~OBC_REG_VERSION_PATCH_VERSION_Msk) | (value << OBC_REG_VERSION_PATCH_VERSION_Pos);
}

static inline uint32_t REG_Get_Event_ConfA_count(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->event_confa & OBC_REG_EVENT_CONFA_COUNT_Msk) >> OBC_REG_EVENT_CONFA_COUNT_Pos);
}

static inline void REG_Set_Event_ConfA_count(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->event_confa = (registers->event_confa & ~OBC_REG_EVENT_CONFA_COUNT_Msk) | (value << OBC_REG_EVENT_CONFA_COUNT_Pos);
}

static inline uint32_t REG_Get_Event_section(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->event & OBC_REG_EVENT_SECTION_Msk) >> OBC_REG_EVENT_SECTION_Pos);
}

static inline void REG_Set_Event_section(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->event = (registers->event & ~OBC_REG_EVENT_SECTION_Msk) | (value << OBC_REG_EVENT_SECTION_Pos);
}

static inline uint32_t REG_Get_Event_detail(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->event & OBC_REG_EVENT_DETAIL_Msk) >> OBC_REG_EVENT_DETAIL_Pos);
}

static inline void REG_Set_Event_detail(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->event = (registers->event & ~OBC_REG_EVENT_DETAIL_Msk) | (value << OBC_REG_EVENT_DETAIL_Pos);
}

static inline uint32_t REG_Get_Event_timestamp(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->event & OBC_REG_EVENT_TIMESTAMP_Msk) >> OBC_REG_EVENT_TIMESTAMP_Pos);
}

static inline void REG_Set_Event_timestamp(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->event = (registers->event & ~OBC_REG_EVENT_TIMESTAMP_Msk) | (value << OBC_REG_EVENT_TIMESTAMP_Pos);
}

static inline reg_enabled_t REG_Get_ConfPower_voltage5Toggle(OBC_RegisterData_t *registers)
{
    return (reg_enabled_t)((registers->confpower & OBC_REG_CONFPOWER_VOLTAGE5TOGGLE_Msk) >> OBC_REG_CONFPOWER_VOLTAGE5TOGGLE_Pos);
}

static inline void REG_Set_ConfPower_voltage5Toggle(OBC_RegisterData_t *registers, reg_enabled_t value)
{
    registers->confpower = (registers->confpower & ~OBC_REG_CONFPOWER_VOLTAGE5TOGGLE_Msk) | (value << OBC_REG_CONFPOWER_VOLTAGE5TOGGLE_Pos);
}

static inline reg_enabled_t REG_Get_ConfPower_voltage3Toggle(OBC_RegisterData_t *registers)
{
    return (reg_enabled_t)((registers->confpower & OBC_REG_CONFPOWER_VOLTAGE3TOGGLE_Msk) >> OBC_REG_CONFPOWER_VOLTAGE3TOGGLE_Pos);
}

static inline void REG_Set_ConfPower_voltage3Toggle(OBC_RegisterData_t *registers, reg_enabled_t value)
{
    registers->confpower = (registers->confpower & ~OBC_REG_CONFPOWER_VOLTAGE3TOGGLE_Msk) | (value << OBC_REG_CONFPOWER_VOLTAGE3TOGGLE_Pos);
}

static inline reg_enabled_t REG_Get_ConfPower_voltageVBatToggle(OBC_RegisterData_t *registers)
{
    return (reg_enabled_t)((registers->confpower & OBC_REG_CONFPOWER_VOLTAGEVBATTOGGLE_Msk) >> OBC_REG_CONFPOWER_VOLTAGEVBATTOGGLE_Pos);
}

static inline void REG_Set_ConfPower_voltageVBatToggle(OBC_RegisterData_t *registers, reg_enabled_t value)
{
    registers->confpower = (registers->confpower & ~OBC_REG_CONFPOWER_VOLTAGEVBATTOGGLE_Msk) | (value << OBC_REG_CONFPOWER_VOLTAGEVBATTOGGLE_Pos);
}

static inline reg_enabled_t REG_Get_ConfPower_voltageVBatAltToggle(OBC_RegisterData_t *registers)
{
    return (reg_enabled_t)((registers->confpower & OBC_REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Msk) >> OBC_REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Pos);
}

static inline void REG_Set_ConfPower_voltageVBatAltToggle(OBC_RegisterData_t *registers, reg_enabled_t value)
{
    registers->confpower = (registers->confpower & ~OBC_REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Msk) | (value << OBC_REG_CONFPOWER_VOLTAGEVBATALTTOGGLE_Pos);
}

static inline uint32_t REG_Get_MeasureVI_V3_voltage(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurevi_v3 & OBC_REG_MEASUREVI_VOLTAGE_Msk) >> OBC_REG_MEASUREVI_VOLTAGE_Pos);
}

static inline void REG_Set_MeasureVI_V3_voltage(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurevi_v3 = (registers->measurevi_v3 & ~OBC_REG_MEASUREVI_VOLTAGE_Msk) | (value << OBC_REG_MEASUREVI_VOLTAGE_Pos);
}

static inline uint32_t REG_Get_MeasureVI_V3_current(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurevi_v3 & OBC_REG_MEASUREVI_CURRENT_Msk) >> OBC_REG_MEASUREVI_CURRENT_Pos);
}

static inline void REG_Set_MeasureVI_V3_current(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurevi_v3 = (registers->measurevi_v3 & ~OBC_REG_MEASUREVI_CURRENT_Msk) | (value << OBC_REG_MEASUREVI_CURRENT_Pos);
}

static inline uint32_t REG_Get_MeasurePower_V3_power(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurepower_v3 & OBC_REG_MEASUREPOWER_POWER_Msk) >> OBC_REG_MEASUREPOWER_POWER_Pos);
}

static inline void REG_Set_MeasurePower_V3_power(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurepower_v3 = (registers->measurepower_v3 & ~OBC_REG_MEASUREPOWER_POWER_Msk) | (value << OBC_REG_MEASUREPOWER_POWER_Pos);
}

static inline uint32_t REG_Get_MeasureVI_V5_voltage(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurevi_v5 & OBC_REG_MEASUREVI_VOLTAGE_Msk) >> OBC_REG_MEASUREVI_VOLTAGE_Pos);
}

static inline void REG_Set_MeasureVI_V5_voltage(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurevi_v5 = (registers->measurevi_v5 & ~OBC_REG_MEASUREVI_VOLTAGE_Msk) | (value << OBC_REG_MEASUREVI_VOLTAGE_Pos);
}

static inline uint32_t REG_Get_MeasureVI_V5_current(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurevi_v5 & OBC_REG_MEASUREVI_CURRENT_Msk) >> OBC_REG_MEASUREVI_CURRENT_Pos);
}

static inline void REG_Set_MeasureVI_V5_current(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurevi_v5 = (registers->measurevi_v5 & ~OBC_REG_MEASUREVI_CURRENT_Msk) | (value << OBC_REG_MEASUREVI_CURRENT_Pos);
}

static inline uint32_t REG_Get_MeasurePower_V5_power(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurepower_v5 & OBC_REG_MEASUREPOWER_POWER_Msk) >> OBC_REG_MEASUREPOWER_POWER_Pos);
}

static inline void REG_Set_MeasurePower_V5_power(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurepower_v5 = (registers->measurepower_v5 & ~OBC_REG_MEASUREPOWER_POWER_Msk) | (value << OBC_REG_MEASUREPOWER_POWER_Pos);
}

static inline uint32_t REG_Get_MeasureVI_VBat_voltage(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurevi_vbat & OBC_REG_MEASUREVI_VOLTAGE_Msk) >> OBC_REG_MEASUREVI_VOLTAGE_Pos);
}

static inline void REG_Set_MeasureVI_VBat_voltage(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurevi_vbat = (registers->measurevi_vbat & ~OBC_REG_MEASUREVI_VOLTAGE_Msk) | (value << OBC_REG_MEASUREVI_VOLTAGE_Pos);
}

static inline uint32_t REG_Get_MeasureVI_VBat_current(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurevi_vbat & OBC_REG_MEASUREVI_CURRENT_Msk) >> OBC_REG_MEASUREVI_CURRENT_Pos);
}

static inline void REG_Set_MeasureVI_VBat_current(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurevi_vbat = (registers->measurevi_vbat & ~OBC_REG_MEASUREVI_CURRENT_Msk) | (value << OBC_REG_MEASUREVI_CURRENT_Pos);
}

static inline uint32_t REG_Get_MeasurePower_VBat_power(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurepower_vbat & OBC_REG_MEASUREPOWER_POWER_Msk) >> OBC_REG_MEASUREPOWER_POWER_Pos);
}

static inline void REG_Set_MeasurePower_VBat_power(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurepower_vbat = (registers->measurepower_vbat & ~OBC_REG_MEASUREPOWER_POWER_Msk) | (value << OBC_REG_MEASUREPOWER_POWER_Pos);
}

static inline uint32_t REG_Get_MeasureVI_VBatAlt_voltage(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurevi_vbatalt & OBC_REG_MEASUREVI_VOLTAGE_Msk) >> OBC_REG_MEASUREVI_VOLTAGE_Pos);
}

static inline void REG_Set_MeasureVI_VBatAlt_voltage(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurevi_vbatalt = (registers->measurevi_vbatalt & ~OBC_REG_MEASUREVI_VOLTAGE_Msk) | (value << OBC_REG_MEASUREVI_VOLTAGE_Pos);
}

static inline uint32_t REG_Get_MeasureVI_VBatAlt_current(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurevi_vbatalt & OBC_REG_MEASUREVI_CURRENT_Msk) >> OBC_REG_MEASUREVI_CURRENT_Pos);
}

static inline void REG_Set_MeasureVI_VBatAlt_current(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurevi_vbatalt = (registers->measurevi_vbatalt & ~OBC_REG_MEASUREVI_CURRENT_Msk) | (value << OBC_REG_MEASUREVI_CURRENT_Pos);
}

static inline uint32_t REG_Get_MeasurePower_VBatAlt_power(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->measurepower_vbatalt & OBC_REG_MEASUREPOWER_POWER_Msk) >> OBC_REG_MEASUREPOWER_POWER_Pos);
}

static inline void REG_Set_MeasurePower_VBatAlt_power(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->measurepower_vbatalt = (registers->measurepower_vbatalt & ~OBC_REG_MEASUREPOWER_POWER_Msk) | (value << OBC_REG_MEASUREPOWER_POWER_Pos);
}

static inline uint32_t REG_Get_I2CConfA_TRDEL(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->i2cconfa & OBC_REG_I2CCONFA_TRDEL_Msk) >> OBC_REG_I2CCONFA_TRDEL_Pos);
}

static inline void REG_Set_I2CConfA_TRDEL(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->i2cconfa = (registers->i2cconfa & ~OBC_REG_I2CCONFA_TRDEL_Msk) | (value << OBC_REG_I2CCONFA_TRDEL_Pos);
}

static inline uint32_t REG_Get_I2CConfA_WRDEL(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->i2cconfa & OBC_REG_I2CCONFA_WRDEL_Msk) >> OBC_REG_I2CCONFA_WRDEL_Pos);
}

static inline void REG_Set_I2CConfA_WRDEL(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->i2cconfa = (registers->i2cconfa & ~OBC_REG_I2CCONFA_WRDEL_Msk) | (value << OBC_REG_I2CCONFA_WRDEL_Pos);
}

static inline uint32_t REG_Get_I2CConfA_SPD(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->i2cconfa & OBC_REG_I2CCONFA_SPD_Msk) >> OBC_REG_I2CCONFA_SPD_Pos);
}

static inline void REG_Set_I2CConfA_SPD(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->i2cconfa = (registers->i2cconfa & ~OBC_REG_I2CCONFA_SPD_Msk) | (value << OBC_REG_I2CCONFA_SPD_Pos);
}

static inline uint32_t REG_Get_I2CConfB_ADDR(OBC_RegisterData_t *registers)
{
    return (uint32_t)((registers->i2cconfb & OBC_REG_I2CCONFB_ADDR_Msk) >> OBC_REG_I2CCONFB_ADDR_Pos);
}

static inline void REG_Set_I2CConfB_ADDR(OBC_RegisterData_t *registers, uint32_t value)
{
    registers->i2cconfb = (registers->i2cconfb & ~OBC_REG_I2CCONFB_ADDR_Msk) | (value << OBC_REG_I2CCONFB_ADDR_Pos);
}

static inline reg_enabled_t REG_Get_XTXpins_ENA(OBC_RegisterData_t *registers)
{
    return (reg_enabled_t)((registers->xtxpins & OBC_REG_XTXPINS_ENA_Msk) >> OBC_REG_XTXPINS_ENA_Pos);
}

static inline void REG_Set_XTXpins_ENA(OBC_RegisterData_t *registers, reg_enabled_t value)
{
    registers->xtxpins = (registers->xtxpins & ~OBC_REG_XTXPINS_ENA_Msk) | (value << OBC_REG_XTXPINS_ENA_Pos);
}

static inline reg_enabled_t REG_Get_XTXpins_nRST(OBC_RegisterData_t *registers)
{
    return (reg_enabled_t)((registers->xtxpins & OBC_REG_XTXPINS_NRST_Msk) >> OBC_REG_XTXPINS_NRST_Pos);
}

static inline void REG_Set_XTXpins_nRST(OBC_RegisterData_t *registers, reg_enabled_t value)
{
    registers->xtxpins = (registers->xtxpins & ~OBC_REG_XTXPINS_NRST_Msk) | (value << OBC_REG_XTXPINS_NRST_Pos);
}

static inline reg_enabled_t REG_Get_XTXpins_RDY(OBC_RegisterData_t *registers)
{
    return (reg_enabled_t)((registers->xtxpins & OBC_REG_XTXPINS_RDY_Msk) >> OBC_REG_XTXPINS_RDY_Pos);
}

static inline void REG_Set_XTXpins_RDY(OBC_RegisterData_t *registers, reg_enabled_t value)
{
    registers->xtxpins = (registers->xtxpins & ~OBC_REG_XTXPINS_RDY_Msk) | (value << OBC_REG_XTXPINS_RDY_Pos);
}

static inline reg_enabled_t REG_Get_XDCConfig_ADDR(OBC_RegisterData_t *registers)
{
    return (reg_enabled_t)((registers->xdcconfig & OBC_REG_XDCCONFIG_ADDR_Msk) >> OBC_REG_XDCCONFIG_ADDR_Pos);
}

static inline void REG_Set_XDCConfig_ADDR(OBC_RegisterData_t *registers, reg_enabled_t value)
{
    registers->xdcconfig = (registers->xdcconfig & ~OBC_REG_XDCCONFIG_ADDR_Msk) | (value << OBC_REG_XDCCONFIG_ADDR_Pos);
}

#endif /* OBC_H_ */
