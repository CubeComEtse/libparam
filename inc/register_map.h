#ifndef OBC_H
#define OBC_H

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

/*************** Bit definition for MultiConf0 register **********************/
#define REG_MULTICONF0_DETECTED_Pos                  (0UL)
#define REG_MULTICONF0_DETECTED_Msk                  (0x0001 << REG_MULTICONF0_DETECTED_Pos)
#define REG_MULTICONF0_AUTOCLR_Pos                   (1UL)
#define REG_MULTICONF0_AUTOCLR_Msk                   (0x0001 << REG_MULTICONF0_AUTOCLR_Pos)
#define REG_MULTICONF0_SCANENABLED_Pos               (2UL)
#define REG_MULTICONF0_SCANENABLED_Msk               (0x0001 << REG_MULTICONF0_SCANENABLED_Pos)
#define REG_MULTICONF0_FANPOS1_Pos                   (4UL)
#define REG_MULTICONF0_FANPOS1_Msk                   (0x0001 << REG_MULTICONF0_FANPOS1_Pos)
#define REG_MULTICONF0_FANPOS2_Pos                   (5UL)
#define REG_MULTICONF0_FANPOS2_Msk                   (0x0001 << REG_MULTICONF0_FANPOS2_Pos)
#define REG_MULTICONF0_FANPOS3_Pos                   (6UL)
#define REG_MULTICONF0_FANPOS3_Msk                   (0x0001 << REG_MULTICONF0_FANPOS3_Pos)
#define REG_MULTICONF0_FANPOS4_Pos                   (7UL)
#define REG_MULTICONF0_FANPOS4_Msk                   (0x0001 << REG_MULTICONF0_FANPOS4_Pos)

/*************** Bit definition for ConfTempSense register *******************/
#define REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Pos     (0UL)
#define REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Msk     (0x0001 << REG_CONFTEMPSENSE_ENABLEMEASUREMENTS_Pos)

/*************** Bit definition for CANConfA register ************************/
#define REG_CANCONFA_BAUDRATE_Pos                    (0UL)
#define REG_CANCONFA_BAUDRATE_Msk                    (0xffff << REG_CANCONFA_BAUDRATE_Pos)
#define REG_CANCONFA_ENABLERETRIES_Pos               (16UL)
#define REG_CANCONFA_ENABLERETRIES_Msk               (0x0001 << REG_CANCONFA_ENABLERETRIES_Pos)
#define REG_CANCONFA_FLIPCANBYTES_Pos                (31UL)
#define REG_CANCONFA_FLIPCANBYTES_Msk                (0x0001 << REG_CANCONFA_FLIPCANBYTES_Pos)

/*************** Bit definition for CANConfB register ************************/
#define REG_CANCONFB_ADDRESS_Pos                     (0UL)
#define REG_CANCONFB_ADDRESS_Msk                     (0x00ff << REG_CANCONFB_ADDRESS_Pos)

/*************** Bit definition for SerialConf register **********************/
#define REG_SERIALCONF_SERIALMODE_Pos                (0UL)
#define REG_SERIALCONF_SERIALMODE_Msk                (0x0003 << REG_SERIALCONF_SERIALMODE_Pos)

/*************** Bit definition for PC104Pins register ***********************/
#define REG_PC104PINS_ENA_Pos                        (0UL)
#define REG_PC104PINS_ENA_Msk                        (0x0001 << REG_PC104PINS_ENA_Pos)
#define REG_PC104PINS_NRST_Pos                       (1UL)
#define REG_PC104PINS_NRST_Msk                       (0x0001 << REG_PC104PINS_NRST_Pos)
#define REG_PC104PINS_RDY_Pos                        (2UL)
#define REG_PC104PINS_RDY_Msk                        (0x0001 << REG_PC104PINS_RDY_Pos)

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

/*************** Bit definition for RFRelaysConf register ********************/
#define REG_RFRELAYSCONF_RFSW1_DETECTED_Pos          (0UL)
#define REG_RFRELAYSCONF_RFSW1_DETECTED_Msk          (0x0001 << REG_RFRELAYSCONF_RFSW1_DETECTED_Pos)
#define REG_RFRELAYSCONF_RFSW2_DETECTED_Pos          (1UL)
#define REG_RFRELAYSCONF_RFSW2_DETECTED_Msk          (0x0001 << REG_RFRELAYSCONF_RFSW2_DETECTED_Pos)
#define REG_RFRELAYSCONF_SCANENABLED_Pos             (2UL)
#define REG_RFRELAYSCONF_SCANENABLED_Msk             (0x0001 << REG_RFRELAYSCONF_SCANENABLED_Pos)
#define REG_RFRELAYSCONF_RFSW1CHAN_Pos               (8UL)
#define REG_RFRELAYSCONF_RFSW1CHAN_Msk               (0x00ff << REG_RFRELAYSCONF_RFSW1CHAN_Pos)
#define REG_RFRELAYSCONF_RFSW2CHAN_Pos               (16UL)
#define REG_RFRELAYSCONF_RFSW2CHAN_Msk               (0x00ff << REG_RFRELAYSCONF_RFSW2CHAN_Pos)

/*************** Bit definition for XDCConfig register ***********************/
#define REG_XDCCONFIG_ADDR_Pos                       (0UL)
#define REG_XDCCONFIG_ADDR_Msk                       (0x00ff << REG_XDCCONFIG_ADDR_Pos)

/*************** Bit definition for RTOS_Status0 register ********************/
#define REG_RTOS_STATUS0_UARTRXHBOVERFLOW_Pos        (0UL)
#define REG_RTOS_STATUS0_UARTRXHBOVERFLOW_Msk        (0x0001 << REG_RTOS_STATUS0_UARTRXHBOVERFLOW_Pos)
#define REG_RTOS_STATUS0_UARTRXSBOVERFLOW_Pos        (1UL)
#define REG_RTOS_STATUS0_UARTRXSBOVERFLOW_Msk        (0x0001 << REG_RTOS_STATUS0_UARTRXSBOVERFLOW_Pos)
#define REG_RTOS_STATUS0_UARTTXSBOVERFLOW_Pos        (2UL)
#define REG_RTOS_STATUS0_UARTTXSBOVERFLOW_Msk        (0x0001 << REG_RTOS_STATUS0_UARTTXSBOVERFLOW_Pos)
#define REG_RTOS_STATUS0_UARTTXHBOVERFLOW_Pos        (3UL)
#define REG_RTOS_STATUS0_UARTTXHBOVERFLOW_Msk        (0x0001 << REG_RTOS_STATUS0_UARTTXHBOVERFLOW_Pos)
#define REG_RTOS_STATUS0_I2CTARGETINCOMINGOVERFLOW_Pos (4UL)
#define REG_RTOS_STATUS0_I2CTARGETINCOMINGOVERFLOW_Msk (0x0001 << REG_RTOS_STATUS0_I2CTARGETINCOMINGOVERFLOW_Pos)
#define REG_RTOS_STATUS0_I2CTARGETOUTGOINGOVERFLOW_Pos (5UL)
#define REG_RTOS_STATUS0_I2CTARGETOUTGOINGOVERFLOW_Msk (0x0001 << REG_RTOS_STATUS0_I2CTARGETOUTGOINGOVERFLOW_Pos)
#define REG_RTOS_STATUS0_CANTARGETINCOMINGOVERFLOW_Pos (6UL)
#define REG_RTOS_STATUS0_CANTARGETINCOMINGOVERFLOW_Msk (0x0001 << REG_RTOS_STATUS0_CANTARGETINCOMINGOVERFLOW_Pos)
#define REG_RTOS_STATUS0_CANINTERRUPTBUFFEROVERFLOW_Pos (7UL)
#define REG_RTOS_STATUS0_CANINTERRUPTBUFFEROVERFLOW_Msk (0x0001 << REG_RTOS_STATUS0_CANINTERRUPTBUFFEROVERFLOW_Pos)
#define REG_RTOS_STATUS0_CANTARGETOUTGOINGOVERFLOW_Pos (8UL)
#define REG_RTOS_STATUS0_CANTARGETOUTGOINGOVERFLOW_Msk (0x0001 << REG_RTOS_STATUS0_CANTARGETOUTGOINGOVERFLOW_Pos)

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

/*************** Bit definition for TE_Config register ***********************/
#define REG_TE_CONFIG_SCANENABLED_Pos                (0UL)
#define REG_TE_CONFIG_SCANENABLED_Msk                (0x0001 << REG_TE_CONFIG_SCANENABLED_Pos)
#define REG_TE_CONFIG_DETECTED_Pos                   (1UL)
#define REG_TE_CONFIG_DETECTED_Msk                   (0x0001 << REG_TE_CONFIG_DETECTED_Pos)
#define REG_TE_CONFIG_TYPE_Pos                       (2UL)
#define REG_TE_CONFIG_TYPE_Msk                       (0x000f << REG_TE_CONFIG_TYPE_Pos)
#define REG_TE_CONFIG_SEL_CAN0_Pos                   (16UL)
#define REG_TE_CONFIG_SEL_CAN0_Msk                   (0x0001 << REG_TE_CONFIG_SEL_CAN0_Pos)
#define REG_TE_CONFIG_SEL_CAN1_Pos                   (17UL)
#define REG_TE_CONFIG_SEL_CAN1_Msk                   (0x0001 << REG_TE_CONFIG_SEL_CAN1_Pos)
#define REG_TE_CONFIG_SEL_RS485_Pos                  (18UL)
#define REG_TE_CONFIG_SEL_RS485_Msk                  (0x0001 << REG_TE_CONFIG_SEL_RS485_Pos)
#define REG_TE_CONFIG_SEL_I2C_Pos                    (19UL)
#define REG_TE_CONFIG_SEL_I2C_Msk                    (0x0001 << REG_TE_CONFIG_SEL_I2C_Pos)
#define REG_TE_CONFIG_SEL_RS422_Pos                  (20UL)
#define REG_TE_CONFIG_SEL_RS422_Msk                  (0x0001 << REG_TE_CONFIG_SEL_RS422_Pos)
#define REG_TE_CONFIG_SEL_SPI_Pos                    (21UL)
#define REG_TE_CONFIG_SEL_SPI_Msk                    (0x0001 << REG_TE_CONFIG_SEL_SPI_Pos)
#define REG_TE_CONFIG_SEL_UART_Pos                   (22UL)
#define REG_TE_CONFIG_SEL_UART_Msk                   (0x0001 << REG_TE_CONFIG_SEL_UART_Pos)
#define REG_TE_CONFIG_POWER_Pos                      (24UL)
#define REG_TE_CONFIG_POWER_Msk                      (0x0001 << REG_TE_CONFIG_POWER_Pos)
#define REG_TE_CONFIG_ENABLE_Pos                     (25UL)
#define REG_TE_CONFIG_ENABLE_Msk                     (0x0001 << REG_TE_CONFIG_ENABLE_Pos)
#define REG_TE_CONFIG_NRESET_Pos                     (26UL)
#define REG_TE_CONFIG_NRESET_Msk                     (0x0001 << REG_TE_CONFIG_NRESET_Pos)
#define REG_TE_CONFIG_COMM_TR_Pos                    (27UL)
#define REG_TE_CONFIG_COMM_TR_Msk                    (0x0001 << REG_TE_CONFIG_COMM_TR_Pos)

/*************** Bit definition for Multitester register *********************/
#define REG_MULTITESTER_POS1_ENABLE_Pos              (0UL)
#define REG_MULTITESTER_POS1_ENABLE_Msk              (0x0001 << REG_MULTITESTER_POS1_ENABLE_Pos)
#define REG_MULTITESTER_POS1_POWER_Pos               (1UL)
#define REG_MULTITESTER_POS1_POWER_Msk               (0x0001 << REG_MULTITESTER_POS1_POWER_Pos)
#define REG_MULTITESTER_POS1_NRESET_Pos              (2UL)
#define REG_MULTITESTER_POS1_NRESET_Msk              (0x0001 << REG_MULTITESTER_POS1_NRESET_Pos)
#define REG_MULTITESTER_POS1_FAN_Pos                 (3UL)
#define REG_MULTITESTER_POS1_FAN_Msk                 (0x0001 << REG_MULTITESTER_POS1_FAN_Pos)
#define REG_MULTITESTER_POS2_ENABLE_Pos              (4UL)
#define REG_MULTITESTER_POS2_ENABLE_Msk              (0x0001 << REG_MULTITESTER_POS2_ENABLE_Pos)
#define REG_MULTITESTER_POS2_POWER_Pos               (5UL)
#define REG_MULTITESTER_POS2_POWER_Msk               (0x0001 << REG_MULTITESTER_POS2_POWER_Pos)
#define REG_MULTITESTER_POS2_NRESET_Pos              (6UL)
#define REG_MULTITESTER_POS2_NRESET_Msk              (0x0001 << REG_MULTITESTER_POS2_NRESET_Pos)
#define REG_MULTITESTER_POS2_FAN_Pos                 (7UL)
#define REG_MULTITESTER_POS2_FAN_Msk                 (0x0001 << REG_MULTITESTER_POS2_FAN_Pos)
#define REG_MULTITESTER_POS3_ENABLE_Pos              (8UL)
#define REG_MULTITESTER_POS3_ENABLE_Msk              (0x0001 << REG_MULTITESTER_POS3_ENABLE_Pos)
#define REG_MULTITESTER_POS3_POWER_Pos               (9UL)
#define REG_MULTITESTER_POS3_POWER_Msk               (0x0001 << REG_MULTITESTER_POS3_POWER_Pos)
#define REG_MULTITESTER_POS3_NRESET_Pos              (10UL)
#define REG_MULTITESTER_POS3_NRESET_Msk              (0x0001 << REG_MULTITESTER_POS3_NRESET_Pos)
#define REG_MULTITESTER_POS3_FAN_Pos                 (11UL)
#define REG_MULTITESTER_POS3_FAN_Msk                 (0x0001 << REG_MULTITESTER_POS3_FAN_Pos)
#define REG_MULTITESTER_POS4_ENABLE_Pos              (12UL)
#define REG_MULTITESTER_POS4_ENABLE_Msk              (0x0001 << REG_MULTITESTER_POS4_ENABLE_Pos)
#define REG_MULTITESTER_POS4_POWER_Pos               (13UL)
#define REG_MULTITESTER_POS4_POWER_Msk               (0x0001 << REG_MULTITESTER_POS4_POWER_Pos)
#define REG_MULTITESTER_POS4_NRESET_Pos              (14UL)
#define REG_MULTITESTER_POS4_NRESET_Msk              (0x0001 << REG_MULTITESTER_POS4_NRESET_Pos)
#define REG_MULTITESTER_POS4_FAN_Pos                 (15UL)
#define REG_MULTITESTER_POS4_FAN_Msk                 (0x0001 << REG_MULTITESTER_POS4_FAN_Pos)


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
    uint32_t MultiConf0;
    uint32_t ConfTempSense;
    uint32_t CANConfA;
    uint32_t CANConfB;
    uint32_t SerialConf;
    uint32_t PC104Pins;
    uint32_t XTXMultitester;
    uint32_t RFRelaysConf;
    uint32_t MultiConf1_Status;
    uint32_t MultiConf1_Set;
    uint32_t MultiConf1_Clear;
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
    uint32_t TE_Addr_0;
    uint32_t TE_Addr_0_Set;
    uint32_t TE_Addr_0_Clear;
    uint32_t TE_Addr_1;
    uint32_t TE_Addr_1_Set;
    uint32_t TE_Addr_1_Clear;
    uint32_t TE_Addr_2;
    uint32_t TE_Addr_2_Set;
    uint32_t TE_Addr_2_Clear;
    uint32_t TE_Addr_3;
    uint32_t TE_Addr_3_Set;
    uint32_t TE_Addr_3_Clear;
    uint32_t RTOS_Status0;
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
    reg_MultiConf0_addr = 0x2B,
    reg_ConfTempSense_addr = 0x2C,
    reg_CANConfA_addr = 0x2D,
    reg_CANConfB_addr = 0x2E,
    reg_SerialConf_addr = 0x2F,
    reg_PC104Pins_addr = 0x30,
    reg_XTXMultitester_addr = 0x31,
    reg_RFRelaysConf_addr = 0x32,
    reg_MultiConf1_Status_addr = 0x33,
    reg_MultiConf1_Set_addr = 0x34,
    reg_MultiConf1_Clear_addr = 0x35,
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
    reg_TE_Addr_0_addr = 0x80,
    reg_TE_Addr_0_Set_addr = 0x81,
    reg_TE_Addr_0_Clear_addr = 0x82,
    reg_TE_Addr_1_addr = 0x83,
    reg_TE_Addr_1_Set_addr = 0x84,
    reg_TE_Addr_1_Clear_addr = 0x85,
    reg_TE_Addr_2_addr = 0x86,
    reg_TE_Addr_2_Set_addr = 0x87,
    reg_TE_Addr_2_Clear_addr = 0x88,
    reg_TE_Addr_3_addr = 0x89,
    reg_TE_Addr_3_Set_addr = 0x8A,
    reg_TE_Addr_3_Clear_addr = 0x8B,
    reg_RTOS_Status0_addr = 0x90,
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
    reg_boardidentifier_gen2 = 32,                  // GEN2
} mm_boardidentifier_t;

typedef enum {
    reg_te_types_pc104 = 0,                         // PC104 Adaptor
    reg_te_types_ud = 1,                            // uD Adaptor
    reg_te_types_gecko = 2,                         // Gecko Adaptor
} mm_te_types_t;

typedef enum {
    reg_serialmode_uart = 0,                        // UART
    reg_serialmode_rs485 = 1,                       // RS485
    reg_serialmode_rs422 = 2,                       // RS422
} mm_serialmode_t;

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

/*************** Get/Set functions for MultiConf0 register ********************************************************************/
mm_response_t mm_setMultiConf0(const uint32_t val);
mm_response_t mm_getMultiConf0(uint32_t * dest);
mm_response_t mm_setMultiConf0_Detected(const mm_enabled_t val);
mm_response_t mm_getMultiConf0_Detected(mm_enabled_t * dest);
mm_response_t mm_getMultiConf0_DetectedFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf0_AutoCLR(const mm_enabled_t val);
mm_response_t mm_getMultiConf0_AutoCLR(mm_enabled_t * dest);
mm_response_t mm_getMultiConf0_AutoCLRFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf0_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getMultiConf0_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getMultiConf0_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf0_FanPos1(const mm_enabled_t val);
mm_response_t mm_getMultiConf0_FanPos1(mm_enabled_t * dest);
mm_response_t mm_getMultiConf0_FanPos1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf0_FanPos2(const mm_enabled_t val);
mm_response_t mm_getMultiConf0_FanPos2(mm_enabled_t * dest);
mm_response_t mm_getMultiConf0_FanPos2From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf0_FanPos3(const mm_enabled_t val);
mm_response_t mm_getMultiConf0_FanPos3(mm_enabled_t * dest);
mm_response_t mm_getMultiConf0_FanPos3From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf0_FanPos4(const mm_enabled_t val);
mm_response_t mm_getMultiConf0_FanPos4(mm_enabled_t * dest);
mm_response_t mm_getMultiConf0_FanPos4From(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for ConfTempSense register *****************************************************************/
mm_response_t mm_setConfTempSense(const uint32_t val);
mm_response_t mm_getConfTempSense(uint32_t * dest);
mm_response_t mm_setConfTempSense_EnableMeasurements(const mm_enabled_t val);
mm_response_t mm_getConfTempSense_EnableMeasurements(mm_enabled_t * dest);
mm_response_t mm_getConfTempSense_EnableMeasurementsFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for CANConfA register **********************************************************************/
mm_response_t mm_setCANConfA(const uint32_t val);
mm_response_t mm_getCANConfA(uint32_t * dest);
mm_response_t mm_setCANConfA_BaudRate(const uint16_t val);
mm_response_t mm_getCANConfA_BaudRate(uint16_t * dest);
mm_response_t mm_getCANConfA_BaudRateFrom(uint16_t * dest, const uint32_t source);
mm_response_t mm_setCANConfA_EnableRetries(const mm_enabled_t val);
mm_response_t mm_getCANConfA_EnableRetries(mm_enabled_t * dest);
mm_response_t mm_getCANConfA_EnableRetriesFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setCANConfA_FlipCanBytes(const mm_enabled_t val);
mm_response_t mm_getCANConfA_FlipCanBytes(mm_enabled_t * dest);
mm_response_t mm_getCANConfA_FlipCanBytesFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for CANConfB register **********************************************************************/
mm_response_t mm_setCANConfB(const uint32_t val);
mm_response_t mm_getCANConfB(uint32_t * dest);
mm_response_t mm_setCANConfB_Address(const uint8_t val);
mm_response_t mm_getCANConfB_Address(uint8_t * dest);
mm_response_t mm_getCANConfB_AddressFrom(uint8_t * dest, const uint32_t source);

/*************** Get/Set functions for SerialConf register ********************************************************************/
mm_response_t mm_setSerialConf(const uint32_t val);
mm_response_t mm_getSerialConf(uint32_t * dest);
mm_response_t mm_setSerialConf_SerialMode(const mm_serialmode_t val);
mm_response_t mm_getSerialConf_SerialMode(mm_serialmode_t * dest);
mm_response_t mm_getSerialConf_SerialModeFrom(mm_serialmode_t * dest, const uint32_t source);

/*************** Get/Set functions for PC104Pins register *********************************************************************/
mm_response_t mm_setPC104Pins(const uint32_t val);
mm_response_t mm_getPC104Pins(uint32_t * dest);
mm_response_t mm_setPC104Pins_ENA(const mm_enabled_t val);
mm_response_t mm_getPC104Pins_ENA(mm_enabled_t * dest);
mm_response_t mm_getPC104Pins_ENAFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setPC104Pins_nRST(const mm_enabled_t val);
mm_response_t mm_getPC104Pins_nRST(mm_enabled_t * dest);
mm_response_t mm_getPC104Pins_nRSTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setPC104Pins_RDY(const mm_enabled_t val);
mm_response_t mm_getPC104Pins_RDY(mm_enabled_t * dest);
mm_response_t mm_getPC104Pins_RDYFrom(mm_enabled_t * dest, const uint32_t source);

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

/*************** Get/Set functions for RFRelaysConf register ******************************************************************/
mm_response_t mm_setRFRelaysConf(const uint32_t val);
mm_response_t mm_getRFRelaysConf(uint32_t * dest);
mm_response_t mm_setRFRelaysConf_RFSW1_Detected(const mm_enabled_t val);
mm_response_t mm_getRFRelaysConf_RFSW1_Detected(mm_enabled_t * dest);
mm_response_t mm_getRFRelaysConf_RFSW1_DetectedFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setRFRelaysConf_RFSW2_Detected(const mm_enabled_t val);
mm_response_t mm_getRFRelaysConf_RFSW2_Detected(mm_enabled_t * dest);
mm_response_t mm_getRFRelaysConf_RFSW2_DetectedFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setRFRelaysConf_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getRFRelaysConf_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getRFRelaysConf_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setRFRelaysConf_RfSw1Chan(const uint8_t val);
mm_response_t mm_getRFRelaysConf_RfSw1Chan(uint8_t * dest);
mm_response_t mm_getRFRelaysConf_RfSw1ChanFrom(uint8_t * dest, const uint32_t source);
mm_response_t mm_setRFRelaysConf_RfSw2Chan(const uint8_t val);
mm_response_t mm_getRFRelaysConf_RfSw2Chan(uint8_t * dest);
mm_response_t mm_getRFRelaysConf_RfSw2ChanFrom(uint8_t * dest, const uint32_t source);

/*************** Get/Set functions for MultiConf1_Status register *************************************************************/
mm_response_t mm_setMultiConf1_Status(const uint32_t val);
mm_response_t mm_getMultiConf1_Status(uint32_t * dest);
mm_response_t mm_setMultiConf1_Status_POS1_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS1_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS1_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS1_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS1_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS1_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS1_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS1_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS1_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS1_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS1_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS1_FANFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS2_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS2_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS2_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS2_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS2_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS2_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS2_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS2_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS2_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS2_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS2_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS2_FANFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS3_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS3_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS3_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS3_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS3_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS3_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS3_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS3_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS3_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS3_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS3_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS3_FANFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS4_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS4_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS4_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS4_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS4_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS4_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS4_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS4_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS4_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Status_POS4_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Status_POS4_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Status_POS4_FANFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for MultiConf1_Set register ****************************************************************/
mm_response_t mm_setMultiConf1_Set(const uint32_t val);
mm_response_t mm_getMultiConf1_Set(uint32_t * dest);
mm_response_t mm_setMultiConf1_Set_POS1_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS1_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS1_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS1_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS1_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS1_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS1_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS1_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS1_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS1_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS1_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS1_FANFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS2_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS2_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS2_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS2_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS2_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS2_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS2_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS2_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS2_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS2_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS2_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS2_FANFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS3_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS3_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS3_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS3_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS3_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS3_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS3_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS3_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS3_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS3_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS3_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS3_FANFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS4_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS4_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS4_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS4_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS4_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS4_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS4_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS4_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS4_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Set_POS4_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Set_POS4_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Set_POS4_FANFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for MultiConf1_Clear register **************************************************************/
mm_response_t mm_setMultiConf1_Clear(const uint32_t val);
mm_response_t mm_getMultiConf1_Clear(uint32_t * dest);
mm_response_t mm_setMultiConf1_Clear_POS1_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS1_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS1_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS1_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS1_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS1_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS1_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS1_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS1_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS1_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS1_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS1_FANFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS2_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS2_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS2_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS2_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS2_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS2_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS2_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS2_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS2_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS2_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS2_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS2_FANFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS3_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS3_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS3_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS3_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS3_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS3_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS3_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS3_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS3_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS3_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS3_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS3_FANFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS4_Enable(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS4_Enable(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS4_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS4_Power(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS4_Power(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS4_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS4_nReset(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS4_nReset(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS4_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setMultiConf1_Clear_POS4_FAN(const mm_enabled_t val);
mm_response_t mm_getMultiConf1_Clear_POS4_FAN(mm_enabled_t * dest);
mm_response_t mm_getMultiConf1_Clear_POS4_FANFrom(mm_enabled_t * dest, const uint32_t source);

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

/*************** Get/Set functions for TE_Addr_0 register *********************************************************************/
mm_response_t mm_setTE_Addr_0(const uint32_t val);
mm_response_t mm_getTE_Addr_0(uint32_t * dest);
mm_response_t mm_setTE_Addr_0_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Detected(const bool val);
mm_response_t mm_getTE_Addr_0_Detected(bool * dest);
mm_response_t mm_getTE_Addr_0_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_0_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_0_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for TE_Addr_0_Set register *****************************************************************/
mm_response_t mm_setTE_Addr_0_Set(const uint32_t val);
mm_response_t mm_getTE_Addr_0_Set(uint32_t * dest);
mm_response_t mm_setTE_Addr_0_Set_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_Detected(const bool val);
mm_response_t mm_getTE_Addr_0_Set_Detected(bool * dest);
mm_response_t mm_getTE_Addr_0_Set_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_0_Set_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_0_Set_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Set_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Set_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Set_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for TE_Addr_0_Clear register ***************************************************************/
mm_response_t mm_setTE_Addr_0_Clear(const uint32_t val);
mm_response_t mm_getTE_Addr_0_Clear(uint32_t * dest);
mm_response_t mm_setTE_Addr_0_Clear_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_Detected(const bool val);
mm_response_t mm_getTE_Addr_0_Clear_Detected(bool * dest);
mm_response_t mm_getTE_Addr_0_Clear_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_0_Clear_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_0_Clear_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_0_Clear_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_0_Clear_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for TE_Addr_1 register *********************************************************************/
mm_response_t mm_setTE_Addr_1(const uint32_t val);
mm_response_t mm_getTE_Addr_1(uint32_t * dest);
mm_response_t mm_setTE_Addr_1_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Detected(const bool val);
mm_response_t mm_getTE_Addr_1_Detected(bool * dest);
mm_response_t mm_getTE_Addr_1_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_1_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_1_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for TE_Addr_1_Set register *****************************************************************/
mm_response_t mm_setTE_Addr_1_Set(const uint32_t val);
mm_response_t mm_getTE_Addr_1_Set(uint32_t * dest);
mm_response_t mm_setTE_Addr_1_Set_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_Detected(const bool val);
mm_response_t mm_getTE_Addr_1_Set_Detected(bool * dest);
mm_response_t mm_getTE_Addr_1_Set_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_1_Set_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_1_Set_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Set_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Set_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Set_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for TE_Addr_1_Clear register ***************************************************************/
mm_response_t mm_setTE_Addr_1_Clear(const uint32_t val);
mm_response_t mm_getTE_Addr_1_Clear(uint32_t * dest);
mm_response_t mm_setTE_Addr_1_Clear_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_Detected(const bool val);
mm_response_t mm_getTE_Addr_1_Clear_Detected(bool * dest);
mm_response_t mm_getTE_Addr_1_Clear_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_1_Clear_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_1_Clear_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_1_Clear_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_1_Clear_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for TE_Addr_2 register *********************************************************************/
mm_response_t mm_setTE_Addr_2(const uint32_t val);
mm_response_t mm_getTE_Addr_2(uint32_t * dest);
mm_response_t mm_setTE_Addr_2_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Detected(const bool val);
mm_response_t mm_getTE_Addr_2_Detected(bool * dest);
mm_response_t mm_getTE_Addr_2_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_2_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_2_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for TE_Addr_2_Set register *****************************************************************/
mm_response_t mm_setTE_Addr_2_Set(const uint32_t val);
mm_response_t mm_getTE_Addr_2_Set(uint32_t * dest);
mm_response_t mm_setTE_Addr_2_Set_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_Detected(const bool val);
mm_response_t mm_getTE_Addr_2_Set_Detected(bool * dest);
mm_response_t mm_getTE_Addr_2_Set_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_2_Set_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_2_Set_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Set_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Set_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Set_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for TE_Addr_2_Clear register ***************************************************************/
mm_response_t mm_setTE_Addr_2_Clear(const uint32_t val);
mm_response_t mm_getTE_Addr_2_Clear(uint32_t * dest);
mm_response_t mm_setTE_Addr_2_Clear_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_Detected(const bool val);
mm_response_t mm_getTE_Addr_2_Clear_Detected(bool * dest);
mm_response_t mm_getTE_Addr_2_Clear_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_2_Clear_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_2_Clear_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_2_Clear_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_2_Clear_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for TE_Addr_3 register *********************************************************************/
mm_response_t mm_setTE_Addr_3(const uint32_t val);
mm_response_t mm_getTE_Addr_3(uint32_t * dest);
mm_response_t mm_setTE_Addr_3_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Detected(const bool val);
mm_response_t mm_getTE_Addr_3_Detected(bool * dest);
mm_response_t mm_getTE_Addr_3_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_3_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_3_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for TE_Addr_3_Set register *****************************************************************/
mm_response_t mm_setTE_Addr_3_Set(const uint32_t val);
mm_response_t mm_getTE_Addr_3_Set(uint32_t * dest);
mm_response_t mm_setTE_Addr_3_Set_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_Detected(const bool val);
mm_response_t mm_getTE_Addr_3_Set_Detected(bool * dest);
mm_response_t mm_getTE_Addr_3_Set_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_3_Set_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_3_Set_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Set_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Set_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Set_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for TE_Addr_3_Clear register ***************************************************************/
mm_response_t mm_setTE_Addr_3_Clear(const uint32_t val);
mm_response_t mm_getTE_Addr_3_Clear(uint32_t * dest);
mm_response_t mm_setTE_Addr_3_Clear_ScanEnabled(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_ScanEnabled(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_ScanEnabledFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_Detected(const bool val);
mm_response_t mm_getTE_Addr_3_Clear_Detected(bool * dest);
mm_response_t mm_getTE_Addr_3_Clear_DetectedFrom(bool * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_Type(const mm_te_types_t val);
mm_response_t mm_getTE_Addr_3_Clear_Type(mm_te_types_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_TypeFrom(mm_te_types_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_SEL_CAN0(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_SEL_CAN0(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_SEL_CAN0From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_SEL_CAN1(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_SEL_CAN1(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_SEL_CAN1From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_SEL_RS485(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_SEL_RS485(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_SEL_RS485From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_SEL_I2C(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_SEL_I2C(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_SEL_I2CFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_SEL_RS422(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_SEL_RS422(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_SEL_RS422From(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_SEL_SPI(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_SEL_SPI(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_SEL_SPIFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_SEL_UART(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_SEL_UART(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_SEL_UARTFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_Power(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_Power(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_PowerFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_Enable(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_Enable(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_EnableFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_nReset(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_nReset(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_nResetFrom(mm_enabled_t * dest, const uint32_t source);
mm_response_t mm_setTE_Addr_3_Clear_COMM_TR(const mm_enabled_t val);
mm_response_t mm_getTE_Addr_3_Clear_COMM_TR(mm_enabled_t * dest);
mm_response_t mm_getTE_Addr_3_Clear_COMM_TRFrom(mm_enabled_t * dest, const uint32_t source);

/*************** Get/Set functions for RTOS_Status0 register ******************************************************************/
mm_response_t mm_setRTOS_Status0(const uint32_t val);
mm_response_t mm_getRTOS_Status0(uint32_t * dest);
mm_response_t mm_setRTOS_Status0_uartRxHBOverflow(const bool val);
mm_response_t mm_getRTOS_Status0_uartRxHBOverflow(bool * dest);
mm_response_t mm_getRTOS_Status0_uartRxHBOverflowFrom(bool * dest, const uint32_t source);
mm_response_t mm_setRTOS_Status0_uartRxSBOverflow(const bool val);
mm_response_t mm_getRTOS_Status0_uartRxSBOverflow(bool * dest);
mm_response_t mm_getRTOS_Status0_uartRxSBOverflowFrom(bool * dest, const uint32_t source);
mm_response_t mm_setRTOS_Status0_uartTxSBOverflow(const bool val);
mm_response_t mm_getRTOS_Status0_uartTxSBOverflow(bool * dest);
mm_response_t mm_getRTOS_Status0_uartTxSBOverflowFrom(bool * dest, const uint32_t source);
mm_response_t mm_setRTOS_Status0_uartTxHBOverflow(const bool val);
mm_response_t mm_getRTOS_Status0_uartTxHBOverflow(bool * dest);
mm_response_t mm_getRTOS_Status0_uartTxHBOverflowFrom(bool * dest, const uint32_t source);
mm_response_t mm_setRTOS_Status0_I2CTargetIncomingOverflow(const bool val);
mm_response_t mm_getRTOS_Status0_I2CTargetIncomingOverflow(bool * dest);
mm_response_t mm_getRTOS_Status0_I2CTargetIncomingOverflowFrom(bool * dest, const uint32_t source);
mm_response_t mm_setRTOS_Status0_I2CTargetOutgoingOverflow(const bool val);
mm_response_t mm_getRTOS_Status0_I2CTargetOutgoingOverflow(bool * dest);
mm_response_t mm_getRTOS_Status0_I2CTargetOutgoingOverflowFrom(bool * dest, const uint32_t source);
mm_response_t mm_setRTOS_Status0_CANTargetIncomingOverflow(const bool val);
mm_response_t mm_getRTOS_Status0_CANTargetIncomingOverflow(bool * dest);
mm_response_t mm_getRTOS_Status0_CANTargetIncomingOverflowFrom(bool * dest, const uint32_t source);
mm_response_t mm_setRTOS_Status0_CANInterruptBufferOverflow(const bool val);
mm_response_t mm_getRTOS_Status0_CANInterruptBufferOverflow(bool * dest);
mm_response_t mm_getRTOS_Status0_CANInterruptBufferOverflowFrom(bool * dest, const uint32_t source);
mm_response_t mm_setRTOS_Status0_CANTargetOutgoingOverflow(const bool val);
mm_response_t mm_getRTOS_Status0_CANTargetOutgoingOverflow(bool * dest);
mm_response_t mm_getRTOS_Status0_CANTargetOutgoingOverflowFrom(bool * dest, const uint32_t source);


#endif /* memory_map_h */
