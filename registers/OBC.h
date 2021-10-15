#ifndef OBC_H_
#define OBC_H_

#define OBC_REG_BOARD_ID                             0x10
#define OBC_REG_FW_VERSION                           0x11
#define OBC_REG_HW_VERSION                           0x12
#define OBC_REG_SCRATCHPAD                           0x13
#define OBC_REG_SUPPORTED_BOARDS                     0x14
#define OBC_REG_CONFIGURED_BOARDS                    0x15
#define OBC_REG_CONFPOWER                            0x20
#define OBC_REG_MEASUREVI_V3                         0x21
#define OBC_REG_MEASUREPOWER_V3                      0x22
#define OBC_REG_MEASUREVI_V5                         0x23
#define OBC_REG_MEASUREPOWER_V5                      0x24
#define OBC_REG_MEASUREVI_VBAT                       0x25
#define OBC_REG_MEASUREPOWER_VBAT                    0x26
#define OBC_REG_MEASUREVI_VBATALT                    0x27
#define OBC_REG_MEASUREPOWER_VBATALT                 0x28
#define OBC_REG_I2CCONFIG                            0x29
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

/*************** Bit definition for I2CConfig register ***********************/
#define OBC_REG_I2CCONFIG_CHK_Pos                    (8UL)
#define OBC_REG_I2CCONFIG_CHK_Msk                    (0x0001 << OBC_REG_I2CCONFIG_CHK_Pos)
#define OBC_REG_I2CCONFIG_CHK                        OBC_REG_I2CCONFIG_CHK_Msk
#define OBC_REG_I2CCONFIG_SPD_Pos                    (0UL)
#define OBC_REG_I2CCONFIG_SPD_Msk                    (0x00ff << OBC_REG_I2CCONFIG_SPD_Pos)
#define OBC_REG_I2CCONFIG_SPD                        OBC_REG_I2CCONFIG_SPD_Msk

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



struct OBC_RegisterData {
    uint32_t board_id;
    uint32_t fw_version;
    uint32_t hw_version;
    uint32_t scratchpad;
    uint32_t supported_boards;
    uint32_t configured_boards;
    uint8_t confpower;
    uint32_t measurevi_v3;
    uint32_t measurepower_v3;
    uint32_t measurevi_v5;
    uint32_t measurepower_v5;
    uint32_t measurevi_vbat;
    uint32_t measurepower_vbat;
    uint32_t measurevi_vbatalt;
    uint32_t measurepower_vbatalt;
    uint32_t i2cconfig;
    uint32_t xtxpins;
    uint32_t xdcconfig;
};
#endif /* OBC_H_ */
