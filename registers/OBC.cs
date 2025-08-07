using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

/***********************************************************************

             This class has been automatically generated. 
                         Changes will be overwritten!

 **********************************************************************/


namespace Devices.Models
{
    public class OBC : INotifyPropertyChanged, IModel
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public bool SupressUpdates = false;

        public enum OBCRegisterAddress{
            OBC_REG_BOARD_ID                         = 0x10,
            OBC_REG_FW_VERSION                       = 0x11,
            OBC_REG_HW_VERSION                       = 0x12,
            OBC_REG_SCRATCHPAD                       = 0x13,
            OBC_REG_SUPPORTED_BOARDS                 = 0x14,
            OBC_REG_CONFIGURED_BOARDS                = 0x15,
            OBC_REG_UPTIME                           = 0x16,
            OBC_REG_EVENT_CONFA                      = 0x17,
            OBC_REG_EVENT                            = 0x18,
            OBC_REG_CONFPOWER                        = 0x20,
            OBC_REG_MEASUREVI_V3                     = 0x21,
            OBC_REG_MEASUREPOWER_V3                  = 0x22,
            OBC_REG_MEASUREVI_V5                     = 0x23,
            OBC_REG_MEASUREPOWER_V5                  = 0x24,
            OBC_REG_MEASUREVI_VBAT                   = 0x25,
            OBC_REG_MEASUREPOWER_VBAT                = 0x26,
            OBC_REG_MEASUREVI_VBATALT                = 0x27,
            OBC_REG_MEASUREPOWER_VBATALT             = 0x28,
            OBC_REG_I2CCONFA                         = 0x29,
            OBC_REG_I2CCONFB                         = 0x2a,
            OBC_REG_MULTICONF0                       = 0x2b,
            OBC_REG_CONFTEMPSENSE                    = 0x2c,
            OBC_REG_CANCONFA                         = 0x2d,
            OBC_REG_CANCONFB                         = 0x2e,
            OBC_REG_SERIALCONF                       = 0x2f,
            OBC_REG_PC104PINS                        = 0x30,
            OBC_REG_XTXMULTITESTER                   = 0x31,
            OBC_REG_RFRELAYSCONF                     = 0x32,
            OBC_REG_MULTICONF1_STATUS                = 0x33,
            OBC_REG_MULTICONF1_SET                   = 0x34,
            OBC_REG_MULTICONF1_CLEAR                 = 0x35,
            OBC_REG_XDCCONFIG                        = 0x40,
            OBC_REG_CSBOARD_T0                       = 0x50,
            OBC_REG_CSBOARD_T1                       = 0x51,
            OBC_REG_CSBOARD_T2                       = 0x52,
            OBC_REG_CSBOARD_T3                       = 0x53,
            OBC_REG_CSBOARD_T4                       = 0x54,
            OBC_REG_CSBOARD_T5                       = 0x55,
            OBC_REG_CSBOARD_T6                       = 0x56,
            OBC_REG_CSBOARD_T7                       = 0x57,
            OBC_REG_CSBOARD_CURRENT0I0               = 0x58,
            OBC_REG_CSBOARD_CURRENT0I1               = 0x59,
            OBC_REG_CSBOARD_CURRENT0I2               = 0x5a,
            OBC_REG_CSBOARD_CURRENT1I0               = 0x5b,
            OBC_REG_CSBOARD_CURRENT1I1               = 0x5c,
            OBC_REG_CSBOARD_CURRENT1I2               = 0x5d,
            OBC_REG_CSBOARD_CURRENT2I0               = 0x5e,
            OBC_REG_CSBOARD_CURRENT2I1               = 0x5f,
            OBC_REG_CSBOARD_CURRENT2I2               = 0x60,
            OBC_REG_CSBOARD_CURRENT3I0               = 0x61,
            OBC_REG_CSBOARD_CURRENT3I1               = 0x62,
            OBC_REG_CSBOARD_CURRENT3I2               = 0x63,
            OBC_REG_CSBOARD_CURRENT4I0               = 0x64,
            OBC_REG_CSBOARD_CURRENT4I1               = 0x65,
            OBC_REG_CSBOARD_CURRENT4I2               = 0x66,
            OBC_REG_CSBOARD_CURRENT5I0               = 0x67,
            OBC_REG_CSBOARD_CURRENT5I1               = 0x68,
            OBC_REG_CSBOARD_CURRENT5I2               = 0x69,
            OBC_REG_CSBOARD_CURRENT6I0               = 0x6a,
            OBC_REG_CSBOARD_CURRENT6I1               = 0x6b,
            OBC_REG_CSBOARD_CURRENT6I2               = 0x6c,
            OBC_REG_CSBOARD_CURRENT7I0               = 0x6d,
            OBC_REG_CSBOARD_CURRENT7I1               = 0x6e,
            OBC_REG_CSBOARD_CURRENT7I2               = 0x6f,
            OBC_REG_TE_ADDR_0                        = 0x80,
            OBC_REG_TE_ADDR_0_SET                    = 0x81,
            OBC_REG_TE_ADDR_0_CLEAR                  = 0x82,
            OBC_REG_TE_ADDR_1                        = 0x83,
            OBC_REG_TE_ADDR_1_SET                    = 0x84,
            OBC_REG_TE_ADDR_1_CLEAR                  = 0x85,
            OBC_REG_TE_ADDR_2                        = 0x86,
            OBC_REG_TE_ADDR_2_SET                    = 0x87,
            OBC_REG_TE_ADDR_2_CLEAR                  = 0x88,
            OBC_REG_TE_ADDR_3                        = 0x89,
            OBC_REG_TE_ADDR_3_SET                    = 0x8a,
            OBC_REG_TE_ADDR_3_CLEAR                  = 0x8b,
            OBC_REG_MTC_ADDR_0                       = 0xb0,
            OBC_REG_MTC_ADDR_0_SET                   = 0xb1,
            OBC_REG_MTC_ADDR_0_CLEAR                 = 0xb2,
            OBC_REG_MTC_ADDR_1                       = 0xb3,
            OBC_REG_MTC_ADDR_1_SET                   = 0xb4,
            OBC_REG_MTC_ADDR_1_CLEAR                 = 0xb5,
            OBC_REG_MTC_ADDR_2                       = 0xb6,
            OBC_REG_MTC_ADDR_2_SET                   = 0xb7,
            OBC_REG_MTC_ADDR_2_CLEAR                 = 0xb8,
            OBC_REG_MTC_ADDR_3                       = 0xb9,
            OBC_REG_MTC_ADDR_3_SET                   = 0xba,
            OBC_REG_MTC_ADDR_3_CLEAR                 = 0xbb,
            OBC_REG_RTOS_STATUS0                     = 0x90,
            OBC_REG_UTILI2CCONFA                     = 0x98,
            OBC_REG_UTILI2CSTATUS                    = 0x99,
            OBC_REG_PREVIOUSENDPOINT                 = 0xa0,
        }

        public enum OBC_SetClearField{
            OBC_SCF_MultiConf1_Set_POS1_Enable,
            OBC_SCF_MultiConf1_Set_POS1_Power,
            OBC_SCF_MultiConf1_Set_POS1_nReset,
            OBC_SCF_MultiConf1_Set_POS1_FAN,
            OBC_SCF_MultiConf1_Set_POS2_Enable,
            OBC_SCF_MultiConf1_Set_POS2_Power,
            OBC_SCF_MultiConf1_Set_POS2_nReset,
            OBC_SCF_MultiConf1_Set_POS2_FAN,
            OBC_SCF_MultiConf1_Set_POS3_Enable,
            OBC_SCF_MultiConf1_Set_POS3_Power,
            OBC_SCF_MultiConf1_Set_POS3_nReset,
            OBC_SCF_MultiConf1_Set_POS3_FAN,
            OBC_SCF_MultiConf1_Set_POS4_Enable,
            OBC_SCF_MultiConf1_Set_POS4_Power,
            OBC_SCF_MultiConf1_Set_POS4_nReset,
            OBC_SCF_MultiConf1_Set_POS4_FAN,
            OBC_SCF_MultiConf1_Clear_POS1_Enable,
            OBC_SCF_MultiConf1_Clear_POS1_Power,
            OBC_SCF_MultiConf1_Clear_POS1_nReset,
            OBC_SCF_MultiConf1_Clear_POS1_FAN,
            OBC_SCF_MultiConf1_Clear_POS2_Enable,
            OBC_SCF_MultiConf1_Clear_POS2_Power,
            OBC_SCF_MultiConf1_Clear_POS2_nReset,
            OBC_SCF_MultiConf1_Clear_POS2_FAN,
            OBC_SCF_MultiConf1_Clear_POS3_Enable,
            OBC_SCF_MultiConf1_Clear_POS3_Power,
            OBC_SCF_MultiConf1_Clear_POS3_nReset,
            OBC_SCF_MultiConf1_Clear_POS3_FAN,
            OBC_SCF_MultiConf1_Clear_POS4_Enable,
            OBC_SCF_MultiConf1_Clear_POS4_Power,
            OBC_SCF_MultiConf1_Clear_POS4_nReset,
            OBC_SCF_MultiConf1_Clear_POS4_FAN,
            OBC_SCF_TE_Addr_0_Set_ScanEnabled,
            OBC_SCF_TE_Addr_0_Set_Detected,
            OBC_SCF_TE_Addr_0_Set_Type,
            OBC_SCF_TE_Addr_0_Set_SEL_CAN0,
            OBC_SCF_TE_Addr_0_Set_SEL_CAN1,
            OBC_SCF_TE_Addr_0_Set_SEL_RS485,
            OBC_SCF_TE_Addr_0_Set_SEL_I2C,
            OBC_SCF_TE_Addr_0_Set_SEL_RS422,
            OBC_SCF_TE_Addr_0_Set_SEL_SPI,
            OBC_SCF_TE_Addr_0_Set_SEL_UART,
            OBC_SCF_TE_Addr_0_Set_Power,
            OBC_SCF_TE_Addr_0_Set_Enable,
            OBC_SCF_TE_Addr_0_Set_nReset,
            OBC_SCF_TE_Addr_0_Set_COMM_TR,
            OBC_SCF_TE_Addr_0_Clear_ScanEnabled,
            OBC_SCF_TE_Addr_0_Clear_Detected,
            OBC_SCF_TE_Addr_0_Clear_Type,
            OBC_SCF_TE_Addr_0_Clear_SEL_CAN0,
            OBC_SCF_TE_Addr_0_Clear_SEL_CAN1,
            OBC_SCF_TE_Addr_0_Clear_SEL_RS485,
            OBC_SCF_TE_Addr_0_Clear_SEL_I2C,
            OBC_SCF_TE_Addr_0_Clear_SEL_RS422,
            OBC_SCF_TE_Addr_0_Clear_SEL_SPI,
            OBC_SCF_TE_Addr_0_Clear_SEL_UART,
            OBC_SCF_TE_Addr_0_Clear_Power,
            OBC_SCF_TE_Addr_0_Clear_Enable,
            OBC_SCF_TE_Addr_0_Clear_nReset,
            OBC_SCF_TE_Addr_0_Clear_COMM_TR,
            OBC_SCF_TE_Addr_1_Set_ScanEnabled,
            OBC_SCF_TE_Addr_1_Set_Detected,
            OBC_SCF_TE_Addr_1_Set_Type,
            OBC_SCF_TE_Addr_1_Set_SEL_CAN0,
            OBC_SCF_TE_Addr_1_Set_SEL_CAN1,
            OBC_SCF_TE_Addr_1_Set_SEL_RS485,
            OBC_SCF_TE_Addr_1_Set_SEL_I2C,
            OBC_SCF_TE_Addr_1_Set_SEL_RS422,
            OBC_SCF_TE_Addr_1_Set_SEL_SPI,
            OBC_SCF_TE_Addr_1_Set_SEL_UART,
            OBC_SCF_TE_Addr_1_Set_Power,
            OBC_SCF_TE_Addr_1_Set_Enable,
            OBC_SCF_TE_Addr_1_Set_nReset,
            OBC_SCF_TE_Addr_1_Set_COMM_TR,
            OBC_SCF_TE_Addr_1_Clear_ScanEnabled,
            OBC_SCF_TE_Addr_1_Clear_Detected,
            OBC_SCF_TE_Addr_1_Clear_Type,
            OBC_SCF_TE_Addr_1_Clear_SEL_CAN0,
            OBC_SCF_TE_Addr_1_Clear_SEL_CAN1,
            OBC_SCF_TE_Addr_1_Clear_SEL_RS485,
            OBC_SCF_TE_Addr_1_Clear_SEL_I2C,
            OBC_SCF_TE_Addr_1_Clear_SEL_RS422,
            OBC_SCF_TE_Addr_1_Clear_SEL_SPI,
            OBC_SCF_TE_Addr_1_Clear_SEL_UART,
            OBC_SCF_TE_Addr_1_Clear_Power,
            OBC_SCF_TE_Addr_1_Clear_Enable,
            OBC_SCF_TE_Addr_1_Clear_nReset,
            OBC_SCF_TE_Addr_1_Clear_COMM_TR,
            OBC_SCF_TE_Addr_2_Set_ScanEnabled,
            OBC_SCF_TE_Addr_2_Set_Detected,
            OBC_SCF_TE_Addr_2_Set_Type,
            OBC_SCF_TE_Addr_2_Set_SEL_CAN0,
            OBC_SCF_TE_Addr_2_Set_SEL_CAN1,
            OBC_SCF_TE_Addr_2_Set_SEL_RS485,
            OBC_SCF_TE_Addr_2_Set_SEL_I2C,
            OBC_SCF_TE_Addr_2_Set_SEL_RS422,
            OBC_SCF_TE_Addr_2_Set_SEL_SPI,
            OBC_SCF_TE_Addr_2_Set_SEL_UART,
            OBC_SCF_TE_Addr_2_Set_Power,
            OBC_SCF_TE_Addr_2_Set_Enable,
            OBC_SCF_TE_Addr_2_Set_nReset,
            OBC_SCF_TE_Addr_2_Set_COMM_TR,
            OBC_SCF_TE_Addr_2_Clear_ScanEnabled,
            OBC_SCF_TE_Addr_2_Clear_Detected,
            OBC_SCF_TE_Addr_2_Clear_Type,
            OBC_SCF_TE_Addr_2_Clear_SEL_CAN0,
            OBC_SCF_TE_Addr_2_Clear_SEL_CAN1,
            OBC_SCF_TE_Addr_2_Clear_SEL_RS485,
            OBC_SCF_TE_Addr_2_Clear_SEL_I2C,
            OBC_SCF_TE_Addr_2_Clear_SEL_RS422,
            OBC_SCF_TE_Addr_2_Clear_SEL_SPI,
            OBC_SCF_TE_Addr_2_Clear_SEL_UART,
            OBC_SCF_TE_Addr_2_Clear_Power,
            OBC_SCF_TE_Addr_2_Clear_Enable,
            OBC_SCF_TE_Addr_2_Clear_nReset,
            OBC_SCF_TE_Addr_2_Clear_COMM_TR,
            OBC_SCF_TE_Addr_3_Set_ScanEnabled,
            OBC_SCF_TE_Addr_3_Set_Detected,
            OBC_SCF_TE_Addr_3_Set_Type,
            OBC_SCF_TE_Addr_3_Set_SEL_CAN0,
            OBC_SCF_TE_Addr_3_Set_SEL_CAN1,
            OBC_SCF_TE_Addr_3_Set_SEL_RS485,
            OBC_SCF_TE_Addr_3_Set_SEL_I2C,
            OBC_SCF_TE_Addr_3_Set_SEL_RS422,
            OBC_SCF_TE_Addr_3_Set_SEL_SPI,
            OBC_SCF_TE_Addr_3_Set_SEL_UART,
            OBC_SCF_TE_Addr_3_Set_Power,
            OBC_SCF_TE_Addr_3_Set_Enable,
            OBC_SCF_TE_Addr_3_Set_nReset,
            OBC_SCF_TE_Addr_3_Set_COMM_TR,
            OBC_SCF_TE_Addr_3_Clear_ScanEnabled,
            OBC_SCF_TE_Addr_3_Clear_Detected,
            OBC_SCF_TE_Addr_3_Clear_Type,
            OBC_SCF_TE_Addr_3_Clear_SEL_CAN0,
            OBC_SCF_TE_Addr_3_Clear_SEL_CAN1,
            OBC_SCF_TE_Addr_3_Clear_SEL_RS485,
            OBC_SCF_TE_Addr_3_Clear_SEL_I2C,
            OBC_SCF_TE_Addr_3_Clear_SEL_RS422,
            OBC_SCF_TE_Addr_3_Clear_SEL_SPI,
            OBC_SCF_TE_Addr_3_Clear_SEL_UART,
            OBC_SCF_TE_Addr_3_Clear_Power,
            OBC_SCF_TE_Addr_3_Clear_Enable,
            OBC_SCF_TE_Addr_3_Clear_nReset,
            OBC_SCF_TE_Addr_3_Clear_COMM_TR,
            OBC_SCF_MTC_Addr_0_Set_ScanEnabled,
            OBC_SCF_MTC_Addr_0_Set_Detected,
            OBC_SCF_MTC_Addr_0_Set_Type,
            OBC_SCF_MTC_Addr_0_Set_ENABLE_1,
            OBC_SCF_MTC_Addr_0_Set_ENABLE_2,
            OBC_SCF_MTC_Addr_0_Set_SEL_I2C_1,
            OBC_SCF_MTC_Addr_0_Set_SEL_I2C_2,
            OBC_SCF_MTC_Addr_0_Set_SEL_UART_1,
            OBC_SCF_MTC_Addr_0_Set_SEL_UART_2,
            OBC_SCF_MTC_Addr_0_Set_SEL_UART_3,
            OBC_SCF_MTC_Addr_0_Set_SEL_UART_4,
            OBC_SCF_MTC_Addr_0_Set_SEL_UART_5,
            OBC_SCF_MTC_Addr_0_Set_SEL_UART_6,
            OBC_SCF_MTC_Addr_0_Set_SEL_VBAT,
            OBC_SCF_MTC_Addr_0_Set_SEL_VBAT_ALT,
            OBC_SCF_MTC_Addr_0_Set_SEL_VBAT_FPGA,
            OBC_SCF_MTC_Addr_0_Set_SEL_nRESET_1,
            OBC_SCF_MTC_Addr_0_Set_SEL_nRESET_2,
            OBC_SCF_MTC_Addr_0_Set_SEL_nRESET_3,
            OBC_SCF_MTC_Addr_0_Set_SEL_CS_1,
            OBC_SCF_MTC_Addr_0_Set_SEL_CS_2,
            OBC_SCF_MTC_Addr_0_Set_SEL_CS_3,
            OBC_SCF_MTC_Addr_0_Set_SEL_CS_4,
            OBC_SCF_MTC_Addr_0_Set_SEL_CS_5,
            OBC_SCF_MTC_Addr_0_Set_SEL_CS_6,
            OBC_SCF_MTC_Addr_0_Set_SEL_SPI_1,
            OBC_SCF_MTC_Addr_0_Set_SEL_SPI_2,
            OBC_SCF_MTC_Addr_0_Set_SEL_CAN_1,
            OBC_SCF_MTC_Addr_0_Set_SEL_CAN_2,
            OBC_SCF_MTC_Addr_0_Set_SEL_CAN_3,
            OBC_SCF_MTC_Addr_0_Set_SEL_RS422,
            OBC_SCF_MTC_Addr_0_Clear_ScanEnabled,
            OBC_SCF_MTC_Addr_0_Clear_Detected,
            OBC_SCF_MTC_Addr_0_Clear_Type,
            OBC_SCF_MTC_Addr_0_Clear_ENABLE_1,
            OBC_SCF_MTC_Addr_0_Clear_ENABLE_2,
            OBC_SCF_MTC_Addr_0_Clear_SEL_I2C_1,
            OBC_SCF_MTC_Addr_0_Clear_SEL_I2C_2,
            OBC_SCF_MTC_Addr_0_Clear_SEL_UART_1,
            OBC_SCF_MTC_Addr_0_Clear_SEL_UART_2,
            OBC_SCF_MTC_Addr_0_Clear_SEL_UART_3,
            OBC_SCF_MTC_Addr_0_Clear_SEL_UART_4,
            OBC_SCF_MTC_Addr_0_Clear_SEL_UART_5,
            OBC_SCF_MTC_Addr_0_Clear_SEL_UART_6,
            OBC_SCF_MTC_Addr_0_Clear_SEL_VBAT,
            OBC_SCF_MTC_Addr_0_Clear_SEL_VBAT_ALT,
            OBC_SCF_MTC_Addr_0_Clear_SEL_VBAT_FPGA,
            OBC_SCF_MTC_Addr_0_Clear_SEL_nRESET_1,
            OBC_SCF_MTC_Addr_0_Clear_SEL_nRESET_2,
            OBC_SCF_MTC_Addr_0_Clear_SEL_nRESET_3,
            OBC_SCF_MTC_Addr_0_Clear_SEL_CS_1,
            OBC_SCF_MTC_Addr_0_Clear_SEL_CS_2,
            OBC_SCF_MTC_Addr_0_Clear_SEL_CS_3,
            OBC_SCF_MTC_Addr_0_Clear_SEL_CS_4,
            OBC_SCF_MTC_Addr_0_Clear_SEL_CS_5,
            OBC_SCF_MTC_Addr_0_Clear_SEL_CS_6,
            OBC_SCF_MTC_Addr_0_Clear_SEL_SPI_1,
            OBC_SCF_MTC_Addr_0_Clear_SEL_SPI_2,
            OBC_SCF_MTC_Addr_0_Clear_SEL_CAN_1,
            OBC_SCF_MTC_Addr_0_Clear_SEL_CAN_2,
            OBC_SCF_MTC_Addr_0_Clear_SEL_CAN_3,
            OBC_SCF_MTC_Addr_0_Clear_SEL_RS422,
            OBC_SCF_MTC_Addr_1_Set_ScanEnabled,
            OBC_SCF_MTC_Addr_1_Set_Detected,
            OBC_SCF_MTC_Addr_1_Set_Type,
            OBC_SCF_MTC_Addr_1_Set_ENABLE_1,
            OBC_SCF_MTC_Addr_1_Set_ENABLE_2,
            OBC_SCF_MTC_Addr_1_Set_SEL_I2C_1,
            OBC_SCF_MTC_Addr_1_Set_SEL_I2C_2,
            OBC_SCF_MTC_Addr_1_Set_SEL_UART_1,
            OBC_SCF_MTC_Addr_1_Set_SEL_UART_2,
            OBC_SCF_MTC_Addr_1_Set_SEL_UART_3,
            OBC_SCF_MTC_Addr_1_Set_SEL_UART_4,
            OBC_SCF_MTC_Addr_1_Set_SEL_UART_5,
            OBC_SCF_MTC_Addr_1_Set_SEL_UART_6,
            OBC_SCF_MTC_Addr_1_Set_SEL_VBAT,
            OBC_SCF_MTC_Addr_1_Set_SEL_VBAT_ALT,
            OBC_SCF_MTC_Addr_1_Set_SEL_VBAT_FPGA,
            OBC_SCF_MTC_Addr_1_Set_SEL_nRESET_1,
            OBC_SCF_MTC_Addr_1_Set_SEL_nRESET_2,
            OBC_SCF_MTC_Addr_1_Set_SEL_nRESET_3,
            OBC_SCF_MTC_Addr_1_Set_SEL_CS_1,
            OBC_SCF_MTC_Addr_1_Set_SEL_CS_2,
            OBC_SCF_MTC_Addr_1_Set_SEL_CS_3,
            OBC_SCF_MTC_Addr_1_Set_SEL_CS_4,
            OBC_SCF_MTC_Addr_1_Set_SEL_CS_5,
            OBC_SCF_MTC_Addr_1_Set_SEL_CS_6,
            OBC_SCF_MTC_Addr_1_Set_SEL_SPI_1,
            OBC_SCF_MTC_Addr_1_Set_SEL_SPI_2,
            OBC_SCF_MTC_Addr_1_Set_SEL_CAN_1,
            OBC_SCF_MTC_Addr_1_Set_SEL_CAN_2,
            OBC_SCF_MTC_Addr_1_Set_SEL_CAN_3,
            OBC_SCF_MTC_Addr_1_Set_SEL_RS422,
            OBC_SCF_MTC_Addr_1_Clear_ScanEnabled,
            OBC_SCF_MTC_Addr_1_Clear_Detected,
            OBC_SCF_MTC_Addr_1_Clear_Type,
            OBC_SCF_MTC_Addr_1_Clear_ENABLE_1,
            OBC_SCF_MTC_Addr_1_Clear_ENABLE_2,
            OBC_SCF_MTC_Addr_1_Clear_SEL_I2C_1,
            OBC_SCF_MTC_Addr_1_Clear_SEL_I2C_2,
            OBC_SCF_MTC_Addr_1_Clear_SEL_UART_1,
            OBC_SCF_MTC_Addr_1_Clear_SEL_UART_2,
            OBC_SCF_MTC_Addr_1_Clear_SEL_UART_3,
            OBC_SCF_MTC_Addr_1_Clear_SEL_UART_4,
            OBC_SCF_MTC_Addr_1_Clear_SEL_UART_5,
            OBC_SCF_MTC_Addr_1_Clear_SEL_UART_6,
            OBC_SCF_MTC_Addr_1_Clear_SEL_VBAT,
            OBC_SCF_MTC_Addr_1_Clear_SEL_VBAT_ALT,
            OBC_SCF_MTC_Addr_1_Clear_SEL_VBAT_FPGA,
            OBC_SCF_MTC_Addr_1_Clear_SEL_nRESET_1,
            OBC_SCF_MTC_Addr_1_Clear_SEL_nRESET_2,
            OBC_SCF_MTC_Addr_1_Clear_SEL_nRESET_3,
            OBC_SCF_MTC_Addr_1_Clear_SEL_CS_1,
            OBC_SCF_MTC_Addr_1_Clear_SEL_CS_2,
            OBC_SCF_MTC_Addr_1_Clear_SEL_CS_3,
            OBC_SCF_MTC_Addr_1_Clear_SEL_CS_4,
            OBC_SCF_MTC_Addr_1_Clear_SEL_CS_5,
            OBC_SCF_MTC_Addr_1_Clear_SEL_CS_6,
            OBC_SCF_MTC_Addr_1_Clear_SEL_SPI_1,
            OBC_SCF_MTC_Addr_1_Clear_SEL_SPI_2,
            OBC_SCF_MTC_Addr_1_Clear_SEL_CAN_1,
            OBC_SCF_MTC_Addr_1_Clear_SEL_CAN_2,
            OBC_SCF_MTC_Addr_1_Clear_SEL_CAN_3,
            OBC_SCF_MTC_Addr_1_Clear_SEL_RS422,
            OBC_SCF_MTC_Addr_2_Set_ScanEnabled,
            OBC_SCF_MTC_Addr_2_Set_Detected,
            OBC_SCF_MTC_Addr_2_Set_Type,
            OBC_SCF_MTC_Addr_2_Set_ENABLE_1,
            OBC_SCF_MTC_Addr_2_Set_ENABLE_2,
            OBC_SCF_MTC_Addr_2_Set_SEL_I2C_1,
            OBC_SCF_MTC_Addr_2_Set_SEL_I2C_2,
            OBC_SCF_MTC_Addr_2_Set_SEL_UART_1,
            OBC_SCF_MTC_Addr_2_Set_SEL_UART_2,
            OBC_SCF_MTC_Addr_2_Set_SEL_UART_3,
            OBC_SCF_MTC_Addr_2_Set_SEL_UART_4,
            OBC_SCF_MTC_Addr_2_Set_SEL_UART_5,
            OBC_SCF_MTC_Addr_2_Set_SEL_UART_6,
            OBC_SCF_MTC_Addr_2_Set_SEL_VBAT,
            OBC_SCF_MTC_Addr_2_Set_SEL_VBAT_ALT,
            OBC_SCF_MTC_Addr_2_Set_SEL_VBAT_FPGA,
            OBC_SCF_MTC_Addr_2_Set_SEL_nRESET_1,
            OBC_SCF_MTC_Addr_2_Set_SEL_nRESET_2,
            OBC_SCF_MTC_Addr_2_Set_SEL_nRESET_3,
            OBC_SCF_MTC_Addr_2_Set_SEL_CS_1,
            OBC_SCF_MTC_Addr_2_Set_SEL_CS_2,
            OBC_SCF_MTC_Addr_2_Set_SEL_CS_3,
            OBC_SCF_MTC_Addr_2_Set_SEL_CS_4,
            OBC_SCF_MTC_Addr_2_Set_SEL_CS_5,
            OBC_SCF_MTC_Addr_2_Set_SEL_CS_6,
            OBC_SCF_MTC_Addr_2_Set_SEL_SPI_1,
            OBC_SCF_MTC_Addr_2_Set_SEL_SPI_2,
            OBC_SCF_MTC_Addr_2_Set_SEL_CAN_1,
            OBC_SCF_MTC_Addr_2_Set_SEL_CAN_2,
            OBC_SCF_MTC_Addr_2_Set_SEL_CAN_3,
            OBC_SCF_MTC_Addr_2_Set_SEL_RS422,
            OBC_SCF_MTC_Addr_2_Clear_ScanEnabled,
            OBC_SCF_MTC_Addr_2_Clear_Detected,
            OBC_SCF_MTC_Addr_2_Clear_Type,
            OBC_SCF_MTC_Addr_2_Clear_ENABLE_1,
            OBC_SCF_MTC_Addr_2_Clear_ENABLE_2,
            OBC_SCF_MTC_Addr_2_Clear_SEL_I2C_1,
            OBC_SCF_MTC_Addr_2_Clear_SEL_I2C_2,
            OBC_SCF_MTC_Addr_2_Clear_SEL_UART_1,
            OBC_SCF_MTC_Addr_2_Clear_SEL_UART_2,
            OBC_SCF_MTC_Addr_2_Clear_SEL_UART_3,
            OBC_SCF_MTC_Addr_2_Clear_SEL_UART_4,
            OBC_SCF_MTC_Addr_2_Clear_SEL_UART_5,
            OBC_SCF_MTC_Addr_2_Clear_SEL_UART_6,
            OBC_SCF_MTC_Addr_2_Clear_SEL_VBAT,
            OBC_SCF_MTC_Addr_2_Clear_SEL_VBAT_ALT,
            OBC_SCF_MTC_Addr_2_Clear_SEL_VBAT_FPGA,
            OBC_SCF_MTC_Addr_2_Clear_SEL_nRESET_1,
            OBC_SCF_MTC_Addr_2_Clear_SEL_nRESET_2,
            OBC_SCF_MTC_Addr_2_Clear_SEL_nRESET_3,
            OBC_SCF_MTC_Addr_2_Clear_SEL_CS_1,
            OBC_SCF_MTC_Addr_2_Clear_SEL_CS_2,
            OBC_SCF_MTC_Addr_2_Clear_SEL_CS_3,
            OBC_SCF_MTC_Addr_2_Clear_SEL_CS_4,
            OBC_SCF_MTC_Addr_2_Clear_SEL_CS_5,
            OBC_SCF_MTC_Addr_2_Clear_SEL_CS_6,
            OBC_SCF_MTC_Addr_2_Clear_SEL_SPI_1,
            OBC_SCF_MTC_Addr_2_Clear_SEL_SPI_2,
            OBC_SCF_MTC_Addr_2_Clear_SEL_CAN_1,
            OBC_SCF_MTC_Addr_2_Clear_SEL_CAN_2,
            OBC_SCF_MTC_Addr_2_Clear_SEL_CAN_3,
            OBC_SCF_MTC_Addr_2_Clear_SEL_RS422,
            OBC_SCF_MTC_Addr_3_Set_ScanEnabled,
            OBC_SCF_MTC_Addr_3_Set_Detected,
            OBC_SCF_MTC_Addr_3_Set_Type,
            OBC_SCF_MTC_Addr_3_Set_ENABLE_1,
            OBC_SCF_MTC_Addr_3_Set_ENABLE_2,
            OBC_SCF_MTC_Addr_3_Set_SEL_I2C_1,
            OBC_SCF_MTC_Addr_3_Set_SEL_I2C_2,
            OBC_SCF_MTC_Addr_3_Set_SEL_UART_1,
            OBC_SCF_MTC_Addr_3_Set_SEL_UART_2,
            OBC_SCF_MTC_Addr_3_Set_SEL_UART_3,
            OBC_SCF_MTC_Addr_3_Set_SEL_UART_4,
            OBC_SCF_MTC_Addr_3_Set_SEL_UART_5,
            OBC_SCF_MTC_Addr_3_Set_SEL_UART_6,
            OBC_SCF_MTC_Addr_3_Set_SEL_VBAT,
            OBC_SCF_MTC_Addr_3_Set_SEL_VBAT_ALT,
            OBC_SCF_MTC_Addr_3_Set_SEL_VBAT_FPGA,
            OBC_SCF_MTC_Addr_3_Set_SEL_nRESET_1,
            OBC_SCF_MTC_Addr_3_Set_SEL_nRESET_2,
            OBC_SCF_MTC_Addr_3_Set_SEL_nRESET_3,
            OBC_SCF_MTC_Addr_3_Set_SEL_CS_1,
            OBC_SCF_MTC_Addr_3_Set_SEL_CS_2,
            OBC_SCF_MTC_Addr_3_Set_SEL_CS_3,
            OBC_SCF_MTC_Addr_3_Set_SEL_CS_4,
            OBC_SCF_MTC_Addr_3_Set_SEL_CS_5,
            OBC_SCF_MTC_Addr_3_Set_SEL_CS_6,
            OBC_SCF_MTC_Addr_3_Set_SEL_SPI_1,
            OBC_SCF_MTC_Addr_3_Set_SEL_SPI_2,
            OBC_SCF_MTC_Addr_3_Set_SEL_CAN_1,
            OBC_SCF_MTC_Addr_3_Set_SEL_CAN_2,
            OBC_SCF_MTC_Addr_3_Set_SEL_CAN_3,
            OBC_SCF_MTC_Addr_3_Set_SEL_RS422,
            OBC_SCF_MTC_Addr_3_Clear_ScanEnabled,
            OBC_SCF_MTC_Addr_3_Clear_Detected,
            OBC_SCF_MTC_Addr_3_Clear_Type,
            OBC_SCF_MTC_Addr_3_Clear_ENABLE_1,
            OBC_SCF_MTC_Addr_3_Clear_ENABLE_2,
            OBC_SCF_MTC_Addr_3_Clear_SEL_I2C_1,
            OBC_SCF_MTC_Addr_3_Clear_SEL_I2C_2,
            OBC_SCF_MTC_Addr_3_Clear_SEL_UART_1,
            OBC_SCF_MTC_Addr_3_Clear_SEL_UART_2,
            OBC_SCF_MTC_Addr_3_Clear_SEL_UART_3,
            OBC_SCF_MTC_Addr_3_Clear_SEL_UART_4,
            OBC_SCF_MTC_Addr_3_Clear_SEL_UART_5,
            OBC_SCF_MTC_Addr_3_Clear_SEL_UART_6,
            OBC_SCF_MTC_Addr_3_Clear_SEL_VBAT,
            OBC_SCF_MTC_Addr_3_Clear_SEL_VBAT_ALT,
            OBC_SCF_MTC_Addr_3_Clear_SEL_VBAT_FPGA,
            OBC_SCF_MTC_Addr_3_Clear_SEL_nRESET_1,
            OBC_SCF_MTC_Addr_3_Clear_SEL_nRESET_2,
            OBC_SCF_MTC_Addr_3_Clear_SEL_nRESET_3,
            OBC_SCF_MTC_Addr_3_Clear_SEL_CS_1,
            OBC_SCF_MTC_Addr_3_Clear_SEL_CS_2,
            OBC_SCF_MTC_Addr_3_Clear_SEL_CS_3,
            OBC_SCF_MTC_Addr_3_Clear_SEL_CS_4,
            OBC_SCF_MTC_Addr_3_Clear_SEL_CS_5,
            OBC_SCF_MTC_Addr_3_Clear_SEL_CS_6,
            OBC_SCF_MTC_Addr_3_Clear_SEL_SPI_1,
            OBC_SCF_MTC_Addr_3_Clear_SEL_SPI_2,
            OBC_SCF_MTC_Addr_3_Clear_SEL_CAN_1,
            OBC_SCF_MTC_Addr_3_Clear_SEL_CAN_2,
            OBC_SCF_MTC_Addr_3_Clear_SEL_CAN_3,
            OBC_SCF_MTC_Addr_3_Clear_SEL_RS422,
        }
        [StructLayout(LayoutKind.Explicit, Pack = 1)]
        public struct RegisterData
        {
            [FieldOffset(0)]
            public UInt32 RawValue;
            [FieldOffset(0)]
            public RegBoard_ID RegBoard_ID;
            [FieldOffset(0)]
            public RegVersion RegVersion;
            [FieldOffset(0)]
            public RegScratchpad RegScratchpad;
            [FieldOffset(0)]
            public RegSupported_Boards RegSupported_Boards;
            [FieldOffset(0)]
            public RegConfigured_Boards RegConfigured_Boards;
            [FieldOffset(0)]
            public RegUptime RegUptime;
            [FieldOffset(0)]
            public RegEvent_ConfA RegEvent_ConfA;
            [FieldOffset(0)]
            public RegEvent RegEvent;
            [FieldOffset(0)]
            public RegConfPower RegConfPower;
            [FieldOffset(0)]
            public RegMeasureVI RegMeasureVI;
            [FieldOffset(0)]
            public RegMeasurePower RegMeasurePower;
            [FieldOffset(0)]
            public RegI2CConfA RegI2CConfA;
            [FieldOffset(0)]
            public RegI2CConfB RegI2CConfB;
            [FieldOffset(0)]
            public RegMultiConf0 RegMultiConf0;
            [FieldOffset(0)]
            public RegConfTempSense RegConfTempSense;
            [FieldOffset(0)]
            public RegCANConfA RegCANConfA;
            [FieldOffset(0)]
            public RegCANConfB RegCANConfB;
            [FieldOffset(0)]
            public RegSerialConf RegSerialConf;
            [FieldOffset(0)]
            public RegPC104Pins RegPC104Pins;
            [FieldOffset(0)]
            public RegXTXMultitester RegXTXMultitester;
            [FieldOffset(0)]
            public RegRFRelaysConf RegRFRelaysConf;
            [FieldOffset(0)]
            public RegMultitester RegMultitester;
            [FieldOffset(0)]
            public RegXDCConfig RegXDCConfig;
            [FieldOffset(0)]
            public RegCSBoard_T0 RegCSBoard_T0;
            [FieldOffset(0)]
            public RegCSBoard_T1 RegCSBoard_T1;
            [FieldOffset(0)]
            public RegCSBoard_T2 RegCSBoard_T2;
            [FieldOffset(0)]
            public RegCSBoard_T3 RegCSBoard_T3;
            [FieldOffset(0)]
            public RegCSBoard_T4 RegCSBoard_T4;
            [FieldOffset(0)]
            public RegCSBoard_T5 RegCSBoard_T5;
            [FieldOffset(0)]
            public RegCSBoard_T6 RegCSBoard_T6;
            [FieldOffset(0)]
            public RegCSBoard_T7 RegCSBoard_T7;
            [FieldOffset(0)]
            public RegCSBoard_Current0I0 RegCSBoard_Current0I0;
            [FieldOffset(0)]
            public RegCSBoard_Current0I1 RegCSBoard_Current0I1;
            [FieldOffset(0)]
            public RegCSBoard_Current0I2 RegCSBoard_Current0I2;
            [FieldOffset(0)]
            public RegCSBoard_Current1I0 RegCSBoard_Current1I0;
            [FieldOffset(0)]
            public RegCSBoard_Current1I1 RegCSBoard_Current1I1;
            [FieldOffset(0)]
            public RegCSBoard_Current1I2 RegCSBoard_Current1I2;
            [FieldOffset(0)]
            public RegCSBoard_Current2I0 RegCSBoard_Current2I0;
            [FieldOffset(0)]
            public RegCSBoard_Current2I1 RegCSBoard_Current2I1;
            [FieldOffset(0)]
            public RegCSBoard_Current2I2 RegCSBoard_Current2I2;
            [FieldOffset(0)]
            public RegCSBoard_Current3I0 RegCSBoard_Current3I0;
            [FieldOffset(0)]
            public RegCSBoard_Current3I1 RegCSBoard_Current3I1;
            [FieldOffset(0)]
            public RegCSBoard_Current3I2 RegCSBoard_Current3I2;
            [FieldOffset(0)]
            public RegCSBoard_Current4I0 RegCSBoard_Current4I0;
            [FieldOffset(0)]
            public RegCSBoard_Current4I1 RegCSBoard_Current4I1;
            [FieldOffset(0)]
            public RegCSBoard_Current4I2 RegCSBoard_Current4I2;
            [FieldOffset(0)]
            public RegCSBoard_Current5I0 RegCSBoard_Current5I0;
            [FieldOffset(0)]
            public RegCSBoard_Current5I1 RegCSBoard_Current5I1;
            [FieldOffset(0)]
            public RegCSBoard_Current5I2 RegCSBoard_Current5I2;
            [FieldOffset(0)]
            public RegCSBoard_Current6I0 RegCSBoard_Current6I0;
            [FieldOffset(0)]
            public RegCSBoard_Current6I1 RegCSBoard_Current6I1;
            [FieldOffset(0)]
            public RegCSBoard_Current6I2 RegCSBoard_Current6I2;
            [FieldOffset(0)]
            public RegCSBoard_Current7I0 RegCSBoard_Current7I0;
            [FieldOffset(0)]
            public RegCSBoard_Current7I1 RegCSBoard_Current7I1;
            [FieldOffset(0)]
            public RegCSBoard_Current7I2 RegCSBoard_Current7I2;
            [FieldOffset(0)]
            public RegTE_Config RegTE_Config;
            [FieldOffset(0)]
            public RegMTC_Config RegMTC_Config;
            [FieldOffset(0)]
            public RegRTOS_Status0 RegRTOS_Status0;
            [FieldOffset(0)]
            public RegUtilI2CConfA RegUtilI2CConfA;
            [FieldOffset(0)]
            public RegUtilI2CStatus RegUtilI2CStatus;
            [FieldOffset(0)]
            public RegPreviousEndpoint RegPreviousEndpoint;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegBoard_ID
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte ccIdentifier
            {
                get { return (byte)((data0 & (UInt32)0xff000000) >> 24); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0xff000000) | (( (UInt32)(value) & 0x000000ff) << 24)); }
            }

            public byte id0
            {
                get { return (byte)((data0 & (UInt32)0x00ff0000) >> 16); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00ff0000) | (( (UInt32)(value) & 0x000000ff) << 16)); }
            }

            public byte id1
            {
                get { return (byte)((data0 & (UInt32)0x0000ff00) >> 8); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000ff00) | (( (UInt32)(value) & 0x000000ff) << 8)); }
            }

            public byte id2
            {
                get { return (byte)((data0 & (UInt32)0x000000ff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x000000ff) | (( (UInt32)(value) & 0x000000ff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegVersion
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte major_version
            {
                get { return (byte)((data0 & (UInt32)0x00ff0000) >> 16); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00ff0000) | (( (UInt32)(value) & 0x000000ff) << 16)); }
            }

            public byte minor_version
            {
                get { return (byte)((data0 & (UInt32)0x0000ff00) >> 8); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000ff00) | (( (UInt32)(value) & 0x000000ff) << 8)); }
            }

            public byte patch_version
            {
                get { return (byte)((data0 & (UInt32)0x000000ff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x000000ff) | (( (UInt32)(value) & 0x000000ff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegScratchpad
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegSupported_Boards
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegConfigured_Boards
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegUptime
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegEvent_ConfA
        {
            [FieldOffset(0)]
            UInt32 data0;

            public short count
            {
                get { return (short)((data0 & (UInt32)0x0000ffff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000ffff) | (( (UInt32)(value) & 0x0000ffff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegEvent
        {
            [FieldOffset(0)]
            UInt32 data0;

            public short section
            {
                get { return (short)((data0 & (UInt32)0xff000000) >> 24); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0xff000000) | (( (UInt32)(value) & 0x000000ff) << 24)); }
            }

            public short detail
            {
                get { return (short)((data0 & (UInt32)0x00ff0000) >> 16); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00ff0000) | (( (UInt32)(value) & 0x000000ff) << 16)); }
            }

            public short timestamp
            {
                get { return (short)((data0 & (UInt32)0x0000ffff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000ffff) | (( (UInt32)(value) & 0x0000ffff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegConfPower
        {
            [FieldOffset(0)]
            byte data0;

            public byte voltage5Toggle
            {
                get { return (byte)((data0 & (byte)0x00000001) >> 0); } 
                set { data0 = (byte)((data0 & ~(byte)0x00000001) | (( (byte)(value) & 0x00000001) << 0)); }
            }

            public byte voltage3Toggle
            {
                get { return (byte)((data0 & (byte)0x00000002) >> 1); } 
                set { data0 = (byte)((data0 & ~(byte)0x00000002) | (( (byte)(value) & 0x00000001) << 1)); }
            }

            public byte voltageVBatToggle
            {
                get { return (byte)((data0 & (byte)0x00000004) >> 2); } 
                set { data0 = (byte)((data0 & ~(byte)0x00000004) | (( (byte)(value) & 0x00000001) << 2)); }
            }

            public byte voltageVBatAltToggle
            {
                get { return (byte)((data0 & (byte)0x00000008) >> 3); } 
                set { data0 = (byte)((data0 & ~(byte)0x00000008) | (( (byte)(value) & 0x00000001) << 3)); }
            }

            public byte voltage3UtilToggle
            {
                get { return (byte)((data0 & (byte)0x00000010) >> 4); } 
                set { data0 = (byte)((data0 & ~(byte)0x00000010) | (( (byte)(value) & 0x00000001) << 4)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegMeasureVI
        {
            [FieldOffset(0)]
            UInt32 data0;

            public UInt32 voltage
            {
                get { return (UInt32)((data0 & (UInt32)0xffff0000) >> 16); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0xffff0000) | (( (UInt32)(value) & 0x0000ffff) << 16)); }
            }

            public UInt32 current
            {
                get { return (UInt32)((data0 & (UInt32)0x0000ffff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000ffff) | (( (UInt32)(value) & 0x0000ffff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegMeasurePower
        {
            [FieldOffset(0)]
            UInt32 data0;

            public UInt32 power
            {
                get { return (UInt32)((data0 & (UInt32)0xffffffff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0xffffffff) | (( (UInt32)(value) & 0xffffffff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegI2CConfA
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte TRDEL
            {
                get { return (byte)((data0 & (UInt32)0x00ff0000) >> 16); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00ff0000) | (( (UInt32)(value) & 0x000000ff) << 16)); }
            }

            public byte WRDEL
            {
                get { return (byte)((data0 & (UInt32)0x0000ff00) >> 8); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000ff00) | (( (UInt32)(value) & 0x000000ff) << 8)); }
            }

            public byte SPD
            {
                get { return (byte)((data0 & (UInt32)0x000000ff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x000000ff) | (( (UInt32)(value) & 0x000000ff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegI2CConfB
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte ADDR
            {
                get { return (byte)((data0 & (UInt32)0x000000ff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x000000ff) | (( (UInt32)(value) & 0x000000ff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegMultiConf0
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte Detected
            {
                get { return (byte)((data0 & (UInt32)0x00000001) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000001) | (( (UInt32)(value) & 0x00000001) << 0)); }
            }

            public byte AutoCLR
            {
                get { return (byte)((data0 & (UInt32)0x00000002) >> 1); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000002) | (( (UInt32)(value) & 0x00000001) << 1)); }
            }

            public byte ScanEnabled
            {
                get { return (byte)((data0 & (UInt32)0x00000004) >> 2); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000004) | (( (UInt32)(value) & 0x00000001) << 2)); }
            }

            public byte FanPos1
            {
                get { return (byte)((data0 & (UInt32)0x00000010) >> 4); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000010) | (( (UInt32)(value) & 0x00000001) << 4)); }
            }

            public byte FanPos2
            {
                get { return (byte)((data0 & (UInt32)0x00000020) >> 5); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000020) | (( (UInt32)(value) & 0x00000001) << 5)); }
            }

            public byte FanPos3
            {
                get { return (byte)((data0 & (UInt32)0x00000040) >> 6); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000040) | (( (UInt32)(value) & 0x00000001) << 6)); }
            }

            public byte FanPos4
            {
                get { return (byte)((data0 & (UInt32)0x00000080) >> 7); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000080) | (( (UInt32)(value) & 0x00000001) << 7)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegConfTempSense
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte EnableMeasurements
            {
                get { return (byte)((data0 & (UInt32)0x00000001) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000001) | (( (UInt32)(value) & 0x00000001) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCANConfA
        {
            [FieldOffset(0)]
            UInt32 data0;

            public UInt32 BaudRate
            {
                get { return (UInt32)((data0 & (UInt32)0x0000ffff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000ffff) | (( (UInt32)(value) & 0x0000ffff) << 0)); }
            }

            public UInt32 EnableRetries
            {
                get { return (UInt32)((data0 & (UInt32)0x00010000) >> 16); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00010000) | (( (UInt32)(value) & 0x00000001) << 16)); }
            }

            public UInt32 FlipCanBytes
            {
                get { return (UInt32)((data0 & (UInt32)0x80000000) >> 31); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x80000000) | (( (UInt32)(value) & 0x00000001) << 31)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCANConfB
        {
            [FieldOffset(0)]
            UInt32 data0;

            public UInt32 Address
            {
                get { return (UInt32)((data0 & (UInt32)0x000000ff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x000000ff) | (( (UInt32)(value) & 0x000000ff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegSerialConf
        {
            [FieldOffset(0)]
            UInt32 data0;

            public UInt32 SerialMode
            {
                get { return (UInt32)((data0 & (UInt32)0x00000003) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000003) | (( (UInt32)(value) & 0x00000003) << 0)); }
            }

            public byte ParityEnabled
            {
                get { return (byte)((data0 & (UInt32)0x00000004) >> 2); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000004) | (( (UInt32)(value) & 0x00000001) << 2)); }
            }

            public byte ParityMode
            {
                get { return (byte)((data0 & (UInt32)0x00000008) >> 3); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000008) | (( (UInt32)(value) & 0x00000001) << 3)); }
            }

            public UInt32 BaudRates
            {
                get { return (UInt32)((data0 & (UInt32)0x00000ff0) >> 4); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000ff0) | (( (UInt32)(value) & 0x000000ff) << 4)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegPC104Pins
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte ENA
            {
                get { return (byte)((data0 & (UInt32)0x00000001) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000001) | (( (UInt32)(value) & 0x00000001) << 0)); }
            }

            public byte nRST
            {
                get { return (byte)((data0 & (UInt32)0x00000002) >> 1); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000002) | (( (UInt32)(value) & 0x00000001) << 1)); }
            }

            public byte RDY
            {
                get { return (byte)((data0 & (UInt32)0x00000004) >> 2); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000004) | (( (UInt32)(value) & 0x00000001) << 2)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegXTXMultitester
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte POS1_XTX_EN
            {
                get { return (byte)((data0 & (UInt32)0x00000001) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000001) | (( (UInt32)(value) & 0x00000001) << 0)); }
            }

            public byte POS1_XTX_Power
            {
                get { return (byte)((data0 & (UInt32)0x00000002) >> 1); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000002) | (( (UInt32)(value) & 0x00000001) << 1)); }
            }

            public byte POS1_XTX_nReset
            {
                get { return (byte)((data0 & (UInt32)0x00000004) >> 2); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000004) | (( (UInt32)(value) & 0x00000001) << 2)); }
            }

            public byte POS2_XTX_EN
            {
                get { return (byte)((data0 & (UInt32)0x00000010) >> 4); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000010) | (( (UInt32)(value) & 0x00000001) << 4)); }
            }

            public byte POS2_XTX_Power
            {
                get { return (byte)((data0 & (UInt32)0x00000020) >> 5); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000020) | (( (UInt32)(value) & 0x00000001) << 5)); }
            }

            public byte POS2_XTX_nReset
            {
                get { return (byte)((data0 & (UInt32)0x00000040) >> 6); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000040) | (( (UInt32)(value) & 0x00000001) << 6)); }
            }

            public byte POS3_XTX_EN
            {
                get { return (byte)((data0 & (UInt32)0x00000100) >> 8); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000100) | (( (UInt32)(value) & 0x00000001) << 8)); }
            }

            public byte POS3_XTX_Power
            {
                get { return (byte)((data0 & (UInt32)0x00000200) >> 9); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000200) | (( (UInt32)(value) & 0x00000001) << 9)); }
            }

            public byte POS3_XTX_nReset
            {
                get { return (byte)((data0 & (UInt32)0x00000400) >> 10); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000400) | (( (UInt32)(value) & 0x00000001) << 10)); }
            }

            public byte POS4_XTX_EN
            {
                get { return (byte)((data0 & (UInt32)0x00001000) >> 12); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00001000) | (( (UInt32)(value) & 0x00000001) << 12)); }
            }

            public byte POS4_XTX_Power
            {
                get { return (byte)((data0 & (UInt32)0x00002000) >> 13); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00002000) | (( (UInt32)(value) & 0x00000001) << 13)); }
            }

            public byte POS4_XTX_nReset
            {
                get { return (byte)((data0 & (UInt32)0x00004000) >> 14); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00004000) | (( (UInt32)(value) & 0x00000001) << 14)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegRFRelaysConf
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte RFSW1_Detected
            {
                get { return (byte)((data0 & (UInt32)0x00000001) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000001) | (( (UInt32)(value) & 0x00000001) << 0)); }
            }

            public byte RFSW2_Detected
            {
                get { return (byte)((data0 & (UInt32)0x00000002) >> 1); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000002) | (( (UInt32)(value) & 0x00000001) << 1)); }
            }

            public byte ScanEnabled
            {
                get { return (byte)((data0 & (UInt32)0x00000004) >> 2); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000004) | (( (UInt32)(value) & 0x00000001) << 2)); }
            }

            public byte RfSw1Chan
            {
                get { return (byte)((data0 & (UInt32)0x0000ff00) >> 8); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000ff00) | (( (UInt32)(value) & 0x000000ff) << 8)); }
            }

            public byte RfSw2Chan
            {
                get { return (byte)((data0 & (UInt32)0x00ff0000) >> 16); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00ff0000) | (( (UInt32)(value) & 0x000000ff) << 16)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegMultitester
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte POS1_Enable
            {
                get { return (byte)((data0 & (UInt32)0x00000001) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000001) | (( (UInt32)(value) & 0x00000001) << 0)); }
            }

            public byte POS1_Power
            {
                get { return (byte)((data0 & (UInt32)0x00000002) >> 1); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000002) | (( (UInt32)(value) & 0x00000001) << 1)); }
            }

            public byte POS1_nReset
            {
                get { return (byte)((data0 & (UInt32)0x00000004) >> 2); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000004) | (( (UInt32)(value) & 0x00000001) << 2)); }
            }

            public byte POS1_FAN
            {
                get { return (byte)((data0 & (UInt32)0x00000008) >> 3); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000008) | (( (UInt32)(value) & 0x00000001) << 3)); }
            }

            public byte POS2_Enable
            {
                get { return (byte)((data0 & (UInt32)0x00000010) >> 4); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000010) | (( (UInt32)(value) & 0x00000001) << 4)); }
            }

            public byte POS2_Power
            {
                get { return (byte)((data0 & (UInt32)0x00000020) >> 5); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000020) | (( (UInt32)(value) & 0x00000001) << 5)); }
            }

            public byte POS2_nReset
            {
                get { return (byte)((data0 & (UInt32)0x00000040) >> 6); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000040) | (( (UInt32)(value) & 0x00000001) << 6)); }
            }

            public byte POS2_FAN
            {
                get { return (byte)((data0 & (UInt32)0x00000080) >> 7); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000080) | (( (UInt32)(value) & 0x00000001) << 7)); }
            }

            public byte POS3_Enable
            {
                get { return (byte)((data0 & (UInt32)0x00000100) >> 8); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000100) | (( (UInt32)(value) & 0x00000001) << 8)); }
            }

            public byte POS3_Power
            {
                get { return (byte)((data0 & (UInt32)0x00000200) >> 9); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000200) | (( (UInt32)(value) & 0x00000001) << 9)); }
            }

            public byte POS3_nReset
            {
                get { return (byte)((data0 & (UInt32)0x00000400) >> 10); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000400) | (( (UInt32)(value) & 0x00000001) << 10)); }
            }

            public byte POS3_FAN
            {
                get { return (byte)((data0 & (UInt32)0x00000800) >> 11); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000800) | (( (UInt32)(value) & 0x00000001) << 11)); }
            }

            public byte POS4_Enable
            {
                get { return (byte)((data0 & (UInt32)0x00001000) >> 12); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00001000) | (( (UInt32)(value) & 0x00000001) << 12)); }
            }

            public byte POS4_Power
            {
                get { return (byte)((data0 & (UInt32)0x00002000) >> 13); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00002000) | (( (UInt32)(value) & 0x00000001) << 13)); }
            }

            public byte POS4_nReset
            {
                get { return (byte)((data0 & (UInt32)0x00004000) >> 14); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00004000) | (( (UInt32)(value) & 0x00000001) << 14)); }
            }

            public byte POS4_FAN
            {
                get { return (byte)((data0 & (UInt32)0x00008000) >> 15); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00008000) | (( (UInt32)(value) & 0x00000001) << 15)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegXDCConfig
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte ADDR
            {
                get { return (byte)((data0 & (UInt32)0x000000ff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x000000ff) | (( (UInt32)(value) & 0x000000ff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_T0
        {
            [FieldOffset(0)]
            public Int32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_T1
        {
            [FieldOffset(0)]
            public Int32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_T2
        {
            [FieldOffset(0)]
            public Int32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_T3
        {
            [FieldOffset(0)]
            public Int32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_T4
        {
            [FieldOffset(0)]
            public Int32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_T5
        {
            [FieldOffset(0)]
            public Int32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_T6
        {
            [FieldOffset(0)]
            public Int32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_T7
        {
            [FieldOffset(0)]
            public Int32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current0I0
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current0I1
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current0I2
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current1I0
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current1I1
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current1I2
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current2I0
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current2I1
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current2I2
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current3I0
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current3I1
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current3I2
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current4I0
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current4I1
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current4I2
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current5I0
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current5I1
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current5I2
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current6I0
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current6I1
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current6I2
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current7I0
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current7I1
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegCSBoard_Current7I2
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegTE_Config
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte ScanEnabled
            {
                get { return (byte)((data0 & (UInt32)0x00000001) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000001) | (( (UInt32)(value) & 0x00000001) << 0)); }
            }

            public byte Detected
            {
                get { return (byte)((data0 & (UInt32)0x00000002) >> 1); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000002) | (( (UInt32)(value) & 0x00000001) << 1)); }
            }

            public UInt32 Type
            {
                get { return (UInt32)((data0 & (UInt32)0x0000000c) >> 2); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000000c) | (( (UInt32)(value) & 0x00000003) << 2)); }
            }

            public byte SEL_CAN0
            {
                get { return (byte)((data0 & (UInt32)0x00010000) >> 16); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00010000) | (( (UInt32)(value) & 0x00000001) << 16)); }
            }

            public byte SEL_CAN1
            {
                get { return (byte)((data0 & (UInt32)0x00020000) >> 17); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00020000) | (( (UInt32)(value) & 0x00000001) << 17)); }
            }

            public byte SEL_RS485
            {
                get { return (byte)((data0 & (UInt32)0x00040000) >> 18); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00040000) | (( (UInt32)(value) & 0x00000001) << 18)); }
            }

            public byte SEL_I2C
            {
                get { return (byte)((data0 & (UInt32)0x00080000) >> 19); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00080000) | (( (UInt32)(value) & 0x00000001) << 19)); }
            }

            public byte SEL_RS422
            {
                get { return (byte)((data0 & (UInt32)0x00100000) >> 20); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00100000) | (( (UInt32)(value) & 0x00000001) << 20)); }
            }

            public byte SEL_SPI
            {
                get { return (byte)((data0 & (UInt32)0x00200000) >> 21); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00200000) | (( (UInt32)(value) & 0x00000001) << 21)); }
            }

            public byte SEL_UART
            {
                get { return (byte)((data0 & (UInt32)0x00400000) >> 22); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00400000) | (( (UInt32)(value) & 0x00000001) << 22)); }
            }

            public byte Power
            {
                get { return (byte)((data0 & (UInt32)0x01000000) >> 24); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x01000000) | (( (UInt32)(value) & 0x00000001) << 24)); }
            }

            public byte Enable
            {
                get { return (byte)((data0 & (UInt32)0x02000000) >> 25); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x02000000) | (( (UInt32)(value) & 0x00000001) << 25)); }
            }

            public byte nReset
            {
                get { return (byte)((data0 & (UInt32)0x04000000) >> 26); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x04000000) | (( (UInt32)(value) & 0x00000001) << 26)); }
            }

            public byte COMM_TR
            {
                get { return (byte)((data0 & (UInt32)0x08000000) >> 27); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x08000000) | (( (UInt32)(value) & 0x00000001) << 27)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegMTC_Config
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte ScanEnabled
            {
                get { return (byte)((data0 & (UInt32)0x00000001) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000001) | (( (UInt32)(value) & 0x00000001) << 0)); }
            }

            public byte Detected
            {
                get { return (byte)((data0 & (UInt32)0x00000002) >> 1); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000002) | (( (UInt32)(value) & 0x00000001) << 1)); }
            }

            public UInt32 Type
            {
                get { return (UInt32)((data0 & (UInt32)0x0000000c) >> 2); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000000c) | (( (UInt32)(value) & 0x00000003) << 2)); }
            }

            public byte ENABLE_1
            {
                get { return (byte)((data0 & (UInt32)0x00000010) >> 4); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000010) | (( (UInt32)(value) & 0x00000001) << 4)); }
            }

            public byte ENABLE_2
            {
                get { return (byte)((data0 & (UInt32)0x00000020) >> 5); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000020) | (( (UInt32)(value) & 0x00000001) << 5)); }
            }

            public byte SEL_I2C_1
            {
                get { return (byte)((data0 & (UInt32)0x00000040) >> 6); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000040) | (( (UInt32)(value) & 0x00000001) << 6)); }
            }

            public byte SEL_I2C_2
            {
                get { return (byte)((data0 & (UInt32)0x00000080) >> 7); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000080) | (( (UInt32)(value) & 0x00000001) << 7)); }
            }

            public byte SEL_UART_1
            {
                get { return (byte)((data0 & (UInt32)0x00000100) >> 8); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000100) | (( (UInt32)(value) & 0x00000001) << 8)); }
            }

            public byte SEL_UART_2
            {
                get { return (byte)((data0 & (UInt32)0x00000200) >> 9); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000200) | (( (UInt32)(value) & 0x00000001) << 9)); }
            }

            public byte SEL_UART_3
            {
                get { return (byte)((data0 & (UInt32)0x00000400) >> 10); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000400) | (( (UInt32)(value) & 0x00000001) << 10)); }
            }

            public byte SEL_UART_4
            {
                get { return (byte)((data0 & (UInt32)0x00000800) >> 11); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000800) | (( (UInt32)(value) & 0x00000001) << 11)); }
            }

            public byte SEL_UART_5
            {
                get { return (byte)((data0 & (UInt32)0x00001000) >> 12); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00001000) | (( (UInt32)(value) & 0x00000001) << 12)); }
            }

            public byte SEL_UART_6
            {
                get { return (byte)((data0 & (UInt32)0x00002000) >> 13); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00002000) | (( (UInt32)(value) & 0x00000001) << 13)); }
            }

            public byte SEL_VBAT
            {
                get { return (byte)((data0 & (UInt32)0x00004000) >> 14); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00004000) | (( (UInt32)(value) & 0x00000001) << 14)); }
            }

            public byte SEL_VBAT_ALT
            {
                get { return (byte)((data0 & (UInt32)0x00008000) >> 15); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00008000) | (( (UInt32)(value) & 0x00000001) << 15)); }
            }

            public byte SEL_VBAT_FPGA
            {
                get { return (byte)((data0 & (UInt32)0x00010000) >> 16); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00010000) | (( (UInt32)(value) & 0x00000001) << 16)); }
            }

            public byte SEL_nRESET_1
            {
                get { return (byte)((data0 & (UInt32)0x00020000) >> 17); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00020000) | (( (UInt32)(value) & 0x00000001) << 17)); }
            }

            public byte SEL_nRESET_2
            {
                get { return (byte)((data0 & (UInt32)0x00040000) >> 18); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00040000) | (( (UInt32)(value) & 0x00000001) << 18)); }
            }

            public byte SEL_nRESET_3
            {
                get { return (byte)((data0 & (UInt32)0x00080000) >> 19); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00080000) | (( (UInt32)(value) & 0x00000001) << 19)); }
            }

            public byte SEL_CS_1
            {
                get { return (byte)((data0 & (UInt32)0x00100000) >> 20); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00100000) | (( (UInt32)(value) & 0x00000001) << 20)); }
            }

            public byte SEL_CS_2
            {
                get { return (byte)((data0 & (UInt32)0x00200000) >> 21); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00200000) | (( (UInt32)(value) & 0x00000001) << 21)); }
            }

            public byte SEL_CS_3
            {
                get { return (byte)((data0 & (UInt32)0x00400000) >> 22); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00400000) | (( (UInt32)(value) & 0x00000001) << 22)); }
            }

            public byte SEL_CS_4
            {
                get { return (byte)((data0 & (UInt32)0x00800000) >> 23); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00800000) | (( (UInt32)(value) & 0x00000001) << 23)); }
            }

            public byte SEL_CS_5
            {
                get { return (byte)((data0 & (UInt32)0x01000000) >> 24); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x01000000) | (( (UInt32)(value) & 0x00000001) << 24)); }
            }

            public byte SEL_CS_6
            {
                get { return (byte)((data0 & (UInt32)0x02000000) >> 25); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x02000000) | (( (UInt32)(value) & 0x00000001) << 25)); }
            }

            public byte SEL_SPI_1
            {
                get { return (byte)((data0 & (UInt32)0x04000000) >> 26); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x04000000) | (( (UInt32)(value) & 0x00000001) << 26)); }
            }

            public byte SEL_SPI_2
            {
                get { return (byte)((data0 & (UInt32)0x08000000) >> 27); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x08000000) | (( (UInt32)(value) & 0x00000001) << 27)); }
            }

            public byte SEL_CAN_1
            {
                get { return (byte)((data0 & (UInt32)0x10000000) >> 28); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x10000000) | (( (UInt32)(value) & 0x00000001) << 28)); }
            }

            public byte SEL_CAN_2
            {
                get { return (byte)((data0 & (UInt32)0x20000000) >> 29); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x20000000) | (( (UInt32)(value) & 0x00000001) << 29)); }
            }

            public byte SEL_CAN_3
            {
                get { return (byte)((data0 & (UInt32)0x40000000) >> 30); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x40000000) | (( (UInt32)(value) & 0x00000001) << 30)); }
            }

            public byte SEL_RS422
            {
                get { return (byte)((data0 & (UInt32)0x80000000) >> 31); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x80000000) | (( (UInt32)(value) & 0x00000001) << 31)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegRTOS_Status0
        {
            [FieldOffset(0)]
            UInt32 data0;

            public bool uartRxHBOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000001) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000001) | (( Convert.ToUInt32(value) & 0x00000001) << 0)); }
            }

            public bool uartRxSBOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000002) >> 1); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000002) | (( Convert.ToUInt32(value) & 0x00000001) << 1)); }
            }

            public bool uartTxSBOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000004) >> 2); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000004) | (( Convert.ToUInt32(value) & 0x00000001) << 2)); }
            }

            public bool uartTxHBOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000008) >> 3); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000008) | (( Convert.ToUInt32(value) & 0x00000001) << 3)); }
            }

            public bool I2CTargetIncomingOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000010) >> 4); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000010) | (( Convert.ToUInt32(value) & 0x00000001) << 4)); }
            }

            public bool I2CTargetOutgoingOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000020) >> 5); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000020) | (( Convert.ToUInt32(value) & 0x00000001) << 5)); }
            }

            public bool CANTargetIncomingOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000040) >> 6); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000040) | (( Convert.ToUInt32(value) & 0x00000001) << 6)); }
            }

            public bool CANInterruptBufferOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000080) >> 7); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000080) | (( Convert.ToUInt32(value) & 0x00000001) << 7)); }
            }

            public bool CANTargetOutgoingOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000100) >> 8); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000100) | (( Convert.ToUInt32(value) & 0x00000001) << 8)); }
            }

            public bool UARTTargetIncomingOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000200) >> 9); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000200) | (( Convert.ToUInt32(value) & 0x00000001) << 9)); }
            }

            public bool UARTTargetTxHBOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000400) >> 10); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000400) | (( Convert.ToUInt32(value) & 0x00000001) << 10)); }
            }

            public bool UARTTargetRxHBOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00000800) >> 11); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000800) | (( Convert.ToUInt32(value) & 0x00000001) << 11)); }
            }

            public bool UARTTargetOutgoingOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00001000) >> 12); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00001000) | (( Convert.ToUInt32(value) & 0x00000001) << 12)); }
            }

            public bool GSETargetIncomingOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00002000) >> 13); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00002000) | (( Convert.ToUInt32(value) & 0x00000001) << 13)); }
            }

            public bool GSETargetOutgoingOverflow
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00004000) >> 14); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00004000) | (( Convert.ToUInt32(value) & 0x00000001) << 14)); }
            }

            public bool SERMUX_CRC_Error
            {
                get { return Convert.ToBoolean((data0 & (UInt32)0x00008000) >> 15); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00008000) | (( Convert.ToUInt32(value) & 0x00000001) << 15)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegUtilI2CConfA
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte Reset
            {
                get { return (byte)((data0 & (UInt32)0x80000000) >> 31); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x80000000) | (( (UInt32)(value) & 0x00000001) << 31)); }
            }

            public byte SPD
            {
                get { return (byte)((data0 & (UInt32)0x000000ff) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x000000ff) | (( (UInt32)(value) & 0x000000ff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegUtilI2CStatus
        {
            [FieldOffset(0)]
            public UInt32 value;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegPreviousEndpoint
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte Number
            {
                get { return (byte)((data0 & (UInt32)0x0000ff00) >> 8); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000ff00) | (( (UInt32)(value) & 0x000000ff) << 8)); }
            }

        }

        public enum Enabled : byte
        {
            [Description("Enabled")]
            Enabled = 1,
            [Description("Disabled")]
            Disabled = 0,
        }

        public enum BoardIdentifier : byte
        {
            [Description("Disabled")]
            None = 0,
            [Description("XTX")]
            XTX = 1,
            [Description("XSTEER")]
            XSteer = 2,
            [Description("XDC")]
            XDC = 4,
            [Description("HDRTX(DFA)")]
            HDRTX_DFA = 8,
            [Description("HDRTX")]
            HDRTX = 16,
            [Description("GEN2")]
            GEN2 = 32,
        }

        public enum TE_Types : byte
        {
            [Description("PC104 Adaptor")]
            PC104 = 0,
            [Description("uD Adaptor")]
            uD = 1,
            [Description("Gecko Adaptor")]
            Gecko = 2,
        }

        public enum SerialMode : byte
        {
            [Description("UART")]
            UART = 0,
            [Description("RS485")]
            RS485 = 1,
            [Description("RS422")]
            RS422 = 2,
        }

        public enum ParityModes : byte
        {
            [Description("Odd")]
            Odd = 0,
            [Description("Even")]
            Even = 1,
        }

        public enum USART_BaudRates : byte
        {
            [Description("115200")]
            baud_115200 = 0,
            [Description("230400")]
            baud_230400 = 1,
            [Description("460800")]
            baud_460800 = 2,
            [Description("921600")]
            baud_921600 = 3,
        }

        private UInt32 _fullRegister_Board_ID;
        public UInt32 FullRegister_Board_ID {
            get => _fullRegister_Board_ID;
            set => _ = Set(ref _fullRegister_Board_ID, value); 
        }

        private UInt32 _fullRegister_FW_Version;
        public UInt32 FullRegister_FW_Version {
            get => _fullRegister_FW_Version;
            set => _ = Set(ref _fullRegister_FW_Version, value); 
        }

        private UInt32 _fullRegister_HW_Version;
        public UInt32 FullRegister_HW_Version {
            get => _fullRegister_HW_Version;
            set => _ = Set(ref _fullRegister_HW_Version, value); 
        }

        private UInt32 _fullRegister_Scratchpad;
        public UInt32 FullRegister_Scratchpad {
            get => _fullRegister_Scratchpad;
            set => _ = Set(ref _fullRegister_Scratchpad, value); 
        }

        private UInt32 _fullRegister_Supported_Boards;
        public UInt32 FullRegister_Supported_Boards {
            get => _fullRegister_Supported_Boards;
            set => _ = Set(ref _fullRegister_Supported_Boards, value); 
        }

        private UInt32 _fullRegister_Configured_Boards;
        public UInt32 FullRegister_Configured_Boards {
            get => _fullRegister_Configured_Boards;
            set => _ = Set(ref _fullRegister_Configured_Boards, value); 
        }

        private UInt32 _fullRegister_Uptime;
        public UInt32 FullRegister_Uptime {
            get => _fullRegister_Uptime;
            set => _ = Set(ref _fullRegister_Uptime, value); 
        }

        private UInt32 _fullRegister_Event_ConfA;
        public UInt32 FullRegister_Event_ConfA {
            get => _fullRegister_Event_ConfA;
            set => _ = Set(ref _fullRegister_Event_ConfA, value); 
        }

        private UInt32 _fullRegister_Event;
        public UInt32 FullRegister_Event {
            get => _fullRegister_Event;
            set => _ = Set(ref _fullRegister_Event, value); 
        }

        private UInt32 _fullRegister_ConfPower;
        public UInt32 FullRegister_ConfPower {
            get => _fullRegister_ConfPower;
            set => _ = Set(ref _fullRegister_ConfPower, value); 
        }

        private UInt32 _fullRegister_MeasureVI_V3;
        public UInt32 FullRegister_MeasureVI_V3 {
            get => _fullRegister_MeasureVI_V3;
            set => _ = Set(ref _fullRegister_MeasureVI_V3, value); 
        }

        private UInt32 _fullRegister_MeasurePower_V3;
        public UInt32 FullRegister_MeasurePower_V3 {
            get => _fullRegister_MeasurePower_V3;
            set => _ = Set(ref _fullRegister_MeasurePower_V3, value); 
        }

        private UInt32 _fullRegister_MeasureVI_V5;
        public UInt32 FullRegister_MeasureVI_V5 {
            get => _fullRegister_MeasureVI_V5;
            set => _ = Set(ref _fullRegister_MeasureVI_V5, value); 
        }

        private UInt32 _fullRegister_MeasurePower_V5;
        public UInt32 FullRegister_MeasurePower_V5 {
            get => _fullRegister_MeasurePower_V5;
            set => _ = Set(ref _fullRegister_MeasurePower_V5, value); 
        }

        private UInt32 _fullRegister_MeasureVI_VBat;
        public UInt32 FullRegister_MeasureVI_VBat {
            get => _fullRegister_MeasureVI_VBat;
            set => _ = Set(ref _fullRegister_MeasureVI_VBat, value); 
        }

        private UInt32 _fullRegister_MeasurePower_VBat;
        public UInt32 FullRegister_MeasurePower_VBat {
            get => _fullRegister_MeasurePower_VBat;
            set => _ = Set(ref _fullRegister_MeasurePower_VBat, value); 
        }

        private UInt32 _fullRegister_MeasureVI_VBatAlt;
        public UInt32 FullRegister_MeasureVI_VBatAlt {
            get => _fullRegister_MeasureVI_VBatAlt;
            set => _ = Set(ref _fullRegister_MeasureVI_VBatAlt, value); 
        }

        private UInt32 _fullRegister_MeasurePower_VBatAlt;
        public UInt32 FullRegister_MeasurePower_VBatAlt {
            get => _fullRegister_MeasurePower_VBatAlt;
            set => _ = Set(ref _fullRegister_MeasurePower_VBatAlt, value); 
        }

        private UInt32 _fullRegister_I2CConfA;
        public UInt32 FullRegister_I2CConfA {
            get => _fullRegister_I2CConfA;
            set => _ = Set(ref _fullRegister_I2CConfA, value); 
        }

        private UInt32 _fullRegister_I2CConfB;
        public UInt32 FullRegister_I2CConfB {
            get => _fullRegister_I2CConfB;
            set => _ = Set(ref _fullRegister_I2CConfB, value); 
        }

        private UInt32 _fullRegister_MultiConf0;
        public UInt32 FullRegister_MultiConf0 {
            get => _fullRegister_MultiConf0;
            set => _ = Set(ref _fullRegister_MultiConf0, value); 
        }

        private UInt32 _fullRegister_ConfTempSense;
        public UInt32 FullRegister_ConfTempSense {
            get => _fullRegister_ConfTempSense;
            set => _ = Set(ref _fullRegister_ConfTempSense, value); 
        }

        private UInt32 _fullRegister_CANConfA;
        public UInt32 FullRegister_CANConfA {
            get => _fullRegister_CANConfA;
            set => _ = Set(ref _fullRegister_CANConfA, value); 
        }

        private UInt32 _fullRegister_CANConfB;
        public UInt32 FullRegister_CANConfB {
            get => _fullRegister_CANConfB;
            set => _ = Set(ref _fullRegister_CANConfB, value); 
        }

        private UInt32 _fullRegister_SerialConf;
        public UInt32 FullRegister_SerialConf {
            get => _fullRegister_SerialConf;
            set => _ = Set(ref _fullRegister_SerialConf, value); 
        }

        private UInt32 _fullRegister_PC104Pins;
        public UInt32 FullRegister_PC104Pins {
            get => _fullRegister_PC104Pins;
            set => _ = Set(ref _fullRegister_PC104Pins, value); 
        }

        private UInt32 _fullRegister_XTXMultitester;
        public UInt32 FullRegister_XTXMultitester {
            get => _fullRegister_XTXMultitester;
            set => _ = Set(ref _fullRegister_XTXMultitester, value); 
        }

        private UInt32 _fullRegister_RFRelaysConf;
        public UInt32 FullRegister_RFRelaysConf {
            get => _fullRegister_RFRelaysConf;
            set => _ = Set(ref _fullRegister_RFRelaysConf, value); 
        }

        private UInt32 _fullRegister_MultiConf1_Status;
        public UInt32 FullRegister_MultiConf1_Status {
            get => _fullRegister_MultiConf1_Status;
            set => _ = Set(ref _fullRegister_MultiConf1_Status, value); 
        }

        private UInt32 _fullRegister_MultiConf1_Set;
        public UInt32 FullRegister_MultiConf1_Set {
            get => _fullRegister_MultiConf1_Set;
            set => _ = Set(ref _fullRegister_MultiConf1_Set, value); 
        }

        private UInt32 _fullRegister_MultiConf1_Clear;
        public UInt32 FullRegister_MultiConf1_Clear {
            get => _fullRegister_MultiConf1_Clear;
            set => _ = Set(ref _fullRegister_MultiConf1_Clear, value); 
        }

        private UInt32 _fullRegister_XDCConfig;
        public UInt32 FullRegister_XDCConfig {
            get => _fullRegister_XDCConfig;
            set => _ = Set(ref _fullRegister_XDCConfig, value); 
        }

        private UInt32 _fullRegister_CSBoard_T0;
        public UInt32 FullRegister_CSBoard_T0 {
            get => _fullRegister_CSBoard_T0;
            set => _ = Set(ref _fullRegister_CSBoard_T0, value); 
        }

        private UInt32 _fullRegister_CSBoard_T1;
        public UInt32 FullRegister_CSBoard_T1 {
            get => _fullRegister_CSBoard_T1;
            set => _ = Set(ref _fullRegister_CSBoard_T1, value); 
        }

        private UInt32 _fullRegister_CSBoard_T2;
        public UInt32 FullRegister_CSBoard_T2 {
            get => _fullRegister_CSBoard_T2;
            set => _ = Set(ref _fullRegister_CSBoard_T2, value); 
        }

        private UInt32 _fullRegister_CSBoard_T3;
        public UInt32 FullRegister_CSBoard_T3 {
            get => _fullRegister_CSBoard_T3;
            set => _ = Set(ref _fullRegister_CSBoard_T3, value); 
        }

        private UInt32 _fullRegister_CSBoard_T4;
        public UInt32 FullRegister_CSBoard_T4 {
            get => _fullRegister_CSBoard_T4;
            set => _ = Set(ref _fullRegister_CSBoard_T4, value); 
        }

        private UInt32 _fullRegister_CSBoard_T5;
        public UInt32 FullRegister_CSBoard_T5 {
            get => _fullRegister_CSBoard_T5;
            set => _ = Set(ref _fullRegister_CSBoard_T5, value); 
        }

        private UInt32 _fullRegister_CSBoard_T6;
        public UInt32 FullRegister_CSBoard_T6 {
            get => _fullRegister_CSBoard_T6;
            set => _ = Set(ref _fullRegister_CSBoard_T6, value); 
        }

        private UInt32 _fullRegister_CSBoard_T7;
        public UInt32 FullRegister_CSBoard_T7 {
            get => _fullRegister_CSBoard_T7;
            set => _ = Set(ref _fullRegister_CSBoard_T7, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current0I0;
        public UInt32 FullRegister_CSBoard_Current0I0 {
            get => _fullRegister_CSBoard_Current0I0;
            set => _ = Set(ref _fullRegister_CSBoard_Current0I0, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current0I1;
        public UInt32 FullRegister_CSBoard_Current0I1 {
            get => _fullRegister_CSBoard_Current0I1;
            set => _ = Set(ref _fullRegister_CSBoard_Current0I1, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current0I2;
        public UInt32 FullRegister_CSBoard_Current0I2 {
            get => _fullRegister_CSBoard_Current0I2;
            set => _ = Set(ref _fullRegister_CSBoard_Current0I2, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current1I0;
        public UInt32 FullRegister_CSBoard_Current1I0 {
            get => _fullRegister_CSBoard_Current1I0;
            set => _ = Set(ref _fullRegister_CSBoard_Current1I0, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current1I1;
        public UInt32 FullRegister_CSBoard_Current1I1 {
            get => _fullRegister_CSBoard_Current1I1;
            set => _ = Set(ref _fullRegister_CSBoard_Current1I1, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current1I2;
        public UInt32 FullRegister_CSBoard_Current1I2 {
            get => _fullRegister_CSBoard_Current1I2;
            set => _ = Set(ref _fullRegister_CSBoard_Current1I2, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current2I0;
        public UInt32 FullRegister_CSBoard_Current2I0 {
            get => _fullRegister_CSBoard_Current2I0;
            set => _ = Set(ref _fullRegister_CSBoard_Current2I0, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current2I1;
        public UInt32 FullRegister_CSBoard_Current2I1 {
            get => _fullRegister_CSBoard_Current2I1;
            set => _ = Set(ref _fullRegister_CSBoard_Current2I1, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current2I2;
        public UInt32 FullRegister_CSBoard_Current2I2 {
            get => _fullRegister_CSBoard_Current2I2;
            set => _ = Set(ref _fullRegister_CSBoard_Current2I2, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current3I0;
        public UInt32 FullRegister_CSBoard_Current3I0 {
            get => _fullRegister_CSBoard_Current3I0;
            set => _ = Set(ref _fullRegister_CSBoard_Current3I0, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current3I1;
        public UInt32 FullRegister_CSBoard_Current3I1 {
            get => _fullRegister_CSBoard_Current3I1;
            set => _ = Set(ref _fullRegister_CSBoard_Current3I1, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current3I2;
        public UInt32 FullRegister_CSBoard_Current3I2 {
            get => _fullRegister_CSBoard_Current3I2;
            set => _ = Set(ref _fullRegister_CSBoard_Current3I2, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current4I0;
        public UInt32 FullRegister_CSBoard_Current4I0 {
            get => _fullRegister_CSBoard_Current4I0;
            set => _ = Set(ref _fullRegister_CSBoard_Current4I0, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current4I1;
        public UInt32 FullRegister_CSBoard_Current4I1 {
            get => _fullRegister_CSBoard_Current4I1;
            set => _ = Set(ref _fullRegister_CSBoard_Current4I1, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current4I2;
        public UInt32 FullRegister_CSBoard_Current4I2 {
            get => _fullRegister_CSBoard_Current4I2;
            set => _ = Set(ref _fullRegister_CSBoard_Current4I2, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current5I0;
        public UInt32 FullRegister_CSBoard_Current5I0 {
            get => _fullRegister_CSBoard_Current5I0;
            set => _ = Set(ref _fullRegister_CSBoard_Current5I0, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current5I1;
        public UInt32 FullRegister_CSBoard_Current5I1 {
            get => _fullRegister_CSBoard_Current5I1;
            set => _ = Set(ref _fullRegister_CSBoard_Current5I1, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current5I2;
        public UInt32 FullRegister_CSBoard_Current5I2 {
            get => _fullRegister_CSBoard_Current5I2;
            set => _ = Set(ref _fullRegister_CSBoard_Current5I2, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current6I0;
        public UInt32 FullRegister_CSBoard_Current6I0 {
            get => _fullRegister_CSBoard_Current6I0;
            set => _ = Set(ref _fullRegister_CSBoard_Current6I0, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current6I1;
        public UInt32 FullRegister_CSBoard_Current6I1 {
            get => _fullRegister_CSBoard_Current6I1;
            set => _ = Set(ref _fullRegister_CSBoard_Current6I1, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current6I2;
        public UInt32 FullRegister_CSBoard_Current6I2 {
            get => _fullRegister_CSBoard_Current6I2;
            set => _ = Set(ref _fullRegister_CSBoard_Current6I2, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current7I0;
        public UInt32 FullRegister_CSBoard_Current7I0 {
            get => _fullRegister_CSBoard_Current7I0;
            set => _ = Set(ref _fullRegister_CSBoard_Current7I0, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current7I1;
        public UInt32 FullRegister_CSBoard_Current7I1 {
            get => _fullRegister_CSBoard_Current7I1;
            set => _ = Set(ref _fullRegister_CSBoard_Current7I1, value); 
        }

        private UInt32 _fullRegister_CSBoard_Current7I2;
        public UInt32 FullRegister_CSBoard_Current7I2 {
            get => _fullRegister_CSBoard_Current7I2;
            set => _ = Set(ref _fullRegister_CSBoard_Current7I2, value); 
        }

        private UInt32 _fullRegister_TE_Addr_0;
        public UInt32 FullRegister_TE_Addr_0 {
            get => _fullRegister_TE_Addr_0;
            set => _ = Set(ref _fullRegister_TE_Addr_0, value); 
        }

        private UInt32 _fullRegister_TE_Addr_0_Set;
        public UInt32 FullRegister_TE_Addr_0_Set {
            get => _fullRegister_TE_Addr_0_Set;
            set => _ = Set(ref _fullRegister_TE_Addr_0_Set, value); 
        }

        private UInt32 _fullRegister_TE_Addr_0_Clear;
        public UInt32 FullRegister_TE_Addr_0_Clear {
            get => _fullRegister_TE_Addr_0_Clear;
            set => _ = Set(ref _fullRegister_TE_Addr_0_Clear, value); 
        }

        private UInt32 _fullRegister_TE_Addr_1;
        public UInt32 FullRegister_TE_Addr_1 {
            get => _fullRegister_TE_Addr_1;
            set => _ = Set(ref _fullRegister_TE_Addr_1, value); 
        }

        private UInt32 _fullRegister_TE_Addr_1_Set;
        public UInt32 FullRegister_TE_Addr_1_Set {
            get => _fullRegister_TE_Addr_1_Set;
            set => _ = Set(ref _fullRegister_TE_Addr_1_Set, value); 
        }

        private UInt32 _fullRegister_TE_Addr_1_Clear;
        public UInt32 FullRegister_TE_Addr_1_Clear {
            get => _fullRegister_TE_Addr_1_Clear;
            set => _ = Set(ref _fullRegister_TE_Addr_1_Clear, value); 
        }

        private UInt32 _fullRegister_TE_Addr_2;
        public UInt32 FullRegister_TE_Addr_2 {
            get => _fullRegister_TE_Addr_2;
            set => _ = Set(ref _fullRegister_TE_Addr_2, value); 
        }

        private UInt32 _fullRegister_TE_Addr_2_Set;
        public UInt32 FullRegister_TE_Addr_2_Set {
            get => _fullRegister_TE_Addr_2_Set;
            set => _ = Set(ref _fullRegister_TE_Addr_2_Set, value); 
        }

        private UInt32 _fullRegister_TE_Addr_2_Clear;
        public UInt32 FullRegister_TE_Addr_2_Clear {
            get => _fullRegister_TE_Addr_2_Clear;
            set => _ = Set(ref _fullRegister_TE_Addr_2_Clear, value); 
        }

        private UInt32 _fullRegister_TE_Addr_3;
        public UInt32 FullRegister_TE_Addr_3 {
            get => _fullRegister_TE_Addr_3;
            set => _ = Set(ref _fullRegister_TE_Addr_3, value); 
        }

        private UInt32 _fullRegister_TE_Addr_3_Set;
        public UInt32 FullRegister_TE_Addr_3_Set {
            get => _fullRegister_TE_Addr_3_Set;
            set => _ = Set(ref _fullRegister_TE_Addr_3_Set, value); 
        }

        private UInt32 _fullRegister_TE_Addr_3_Clear;
        public UInt32 FullRegister_TE_Addr_3_Clear {
            get => _fullRegister_TE_Addr_3_Clear;
            set => _ = Set(ref _fullRegister_TE_Addr_3_Clear, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_0;
        public UInt32 FullRegister_MTC_Addr_0 {
            get => _fullRegister_MTC_Addr_0;
            set => _ = Set(ref _fullRegister_MTC_Addr_0, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_0_Set;
        public UInt32 FullRegister_MTC_Addr_0_Set {
            get => _fullRegister_MTC_Addr_0_Set;
            set => _ = Set(ref _fullRegister_MTC_Addr_0_Set, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_0_Clear;
        public UInt32 FullRegister_MTC_Addr_0_Clear {
            get => _fullRegister_MTC_Addr_0_Clear;
            set => _ = Set(ref _fullRegister_MTC_Addr_0_Clear, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_1;
        public UInt32 FullRegister_MTC_Addr_1 {
            get => _fullRegister_MTC_Addr_1;
            set => _ = Set(ref _fullRegister_MTC_Addr_1, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_1_Set;
        public UInt32 FullRegister_MTC_Addr_1_Set {
            get => _fullRegister_MTC_Addr_1_Set;
            set => _ = Set(ref _fullRegister_MTC_Addr_1_Set, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_1_Clear;
        public UInt32 FullRegister_MTC_Addr_1_Clear {
            get => _fullRegister_MTC_Addr_1_Clear;
            set => _ = Set(ref _fullRegister_MTC_Addr_1_Clear, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_2;
        public UInt32 FullRegister_MTC_Addr_2 {
            get => _fullRegister_MTC_Addr_2;
            set => _ = Set(ref _fullRegister_MTC_Addr_2, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_2_Set;
        public UInt32 FullRegister_MTC_Addr_2_Set {
            get => _fullRegister_MTC_Addr_2_Set;
            set => _ = Set(ref _fullRegister_MTC_Addr_2_Set, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_2_Clear;
        public UInt32 FullRegister_MTC_Addr_2_Clear {
            get => _fullRegister_MTC_Addr_2_Clear;
            set => _ = Set(ref _fullRegister_MTC_Addr_2_Clear, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_3;
        public UInt32 FullRegister_MTC_Addr_3 {
            get => _fullRegister_MTC_Addr_3;
            set => _ = Set(ref _fullRegister_MTC_Addr_3, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_3_Set;
        public UInt32 FullRegister_MTC_Addr_3_Set {
            get => _fullRegister_MTC_Addr_3_Set;
            set => _ = Set(ref _fullRegister_MTC_Addr_3_Set, value); 
        }

        private UInt32 _fullRegister_MTC_Addr_3_Clear;
        public UInt32 FullRegister_MTC_Addr_3_Clear {
            get => _fullRegister_MTC_Addr_3_Clear;
            set => _ = Set(ref _fullRegister_MTC_Addr_3_Clear, value); 
        }

        private UInt32 _fullRegister_RTOS_Status0;
        public UInt32 FullRegister_RTOS_Status0 {
            get => _fullRegister_RTOS_Status0;
            set => _ = Set(ref _fullRegister_RTOS_Status0, value); 
        }

        private UInt32 _fullRegister_UtilI2CConfA;
        public UInt32 FullRegister_UtilI2CConfA {
            get => _fullRegister_UtilI2CConfA;
            set => _ = Set(ref _fullRegister_UtilI2CConfA, value); 
        }

        private UInt32 _fullRegister_UtilI2CStatus;
        public UInt32 FullRegister_UtilI2CStatus {
            get => _fullRegister_UtilI2CStatus;
            set => _ = Set(ref _fullRegister_UtilI2CStatus, value); 
        }

        private UInt32 _fullRegister_PreviousEndpoint;
        public UInt32 FullRegister_PreviousEndpoint {
            get => _fullRegister_PreviousEndpoint;
            set => _ = Set(ref _fullRegister_PreviousEndpoint, value); 
        }

        /*************** Properties for Board_ID register ****************************************/
        private bool _Board_ID_ccIdentifierIsSet;
        public bool Board_ID_ccIdentifierIsSet {
            get => _Board_ID_ccIdentifierIsSet;
            set => _ = Set(ref _Board_ID_ccIdentifierIsSet, value); 
        }
        private byte _Board_ID_ccIdentifier;
        public byte Board_ID_ccIdentifier {
            get => _Board_ID_ccIdentifier;
            set => _ = Set(ref _Board_ID_ccIdentifier, value);
        }
        
        private bool _Board_ID_id0IsSet;
        public bool Board_ID_id0IsSet {
            get => _Board_ID_id0IsSet;
            set => _ = Set(ref _Board_ID_id0IsSet, value); 
        }
        private byte _Board_ID_id0;
        public byte Board_ID_id0 {
            get => _Board_ID_id0;
            set => _ = Set(ref _Board_ID_id0, value);
        }
        
        private bool _Board_ID_id1IsSet;
        public bool Board_ID_id1IsSet {
            get => _Board_ID_id1IsSet;
            set => _ = Set(ref _Board_ID_id1IsSet, value); 
        }
        private byte _Board_ID_id1;
        public byte Board_ID_id1 {
            get => _Board_ID_id1;
            set => _ = Set(ref _Board_ID_id1, value);
        }
        
        private bool _Board_ID_id2IsSet;
        public bool Board_ID_id2IsSet {
            get => _Board_ID_id2IsSet;
            set => _ = Set(ref _Board_ID_id2IsSet, value); 
        }
        private byte _Board_ID_id2;
        public byte Board_ID_id2 {
            get => _Board_ID_id2;
            set => _ = Set(ref _Board_ID_id2, value);
        }
        
        /*************** Min and Max Properties for FW_Version types *****************************/
        /*************** Properties for FW_Version register **************************************/
        private bool _FW_Version_major_versionIsSet;
        public bool FW_Version_major_versionIsSet {
            get => _FW_Version_major_versionIsSet;
            set => _ = Set(ref _FW_Version_major_versionIsSet, value); 
        }
        private byte _FW_Version_major_version;
        public byte FW_Version_major_version {
            get => _FW_Version_major_version;
            set => _ = Set(ref _FW_Version_major_version, value);
        }
        
        private bool _FW_Version_minor_versionIsSet;
        public bool FW_Version_minor_versionIsSet {
            get => _FW_Version_minor_versionIsSet;
            set => _ = Set(ref _FW_Version_minor_versionIsSet, value); 
        }
        private byte _FW_Version_minor_version;
        public byte FW_Version_minor_version {
            get => _FW_Version_minor_version;
            set => _ = Set(ref _FW_Version_minor_version, value);
        }
        
        private bool _FW_Version_patch_versionIsSet;
        public bool FW_Version_patch_versionIsSet {
            get => _FW_Version_patch_versionIsSet;
            set => _ = Set(ref _FW_Version_patch_versionIsSet, value); 
        }
        private byte _FW_Version_patch_version;
        public byte FW_Version_patch_version {
            get => _FW_Version_patch_version;
            set => _ = Set(ref _FW_Version_patch_version, value);
        }
        
        /*************** Properties for HW_Version register **************************************/
        private bool _HW_Version_major_versionIsSet;
        public bool HW_Version_major_versionIsSet {
            get => _HW_Version_major_versionIsSet;
            set => _ = Set(ref _HW_Version_major_versionIsSet, value); 
        }
        private byte _HW_Version_major_version;
        public byte HW_Version_major_version {
            get => _HW_Version_major_version;
            set => _ = Set(ref _HW_Version_major_version, value);
        }
        
        private bool _HW_Version_minor_versionIsSet;
        public bool HW_Version_minor_versionIsSet {
            get => _HW_Version_minor_versionIsSet;
            set => _ = Set(ref _HW_Version_minor_versionIsSet, value); 
        }
        private byte _HW_Version_minor_version;
        public byte HW_Version_minor_version {
            get => _HW_Version_minor_version;
            set => _ = Set(ref _HW_Version_minor_version, value);
        }
        
        private bool _HW_Version_patch_versionIsSet;
        public bool HW_Version_patch_versionIsSet {
            get => _HW_Version_patch_versionIsSet;
            set => _ = Set(ref _HW_Version_patch_versionIsSet, value); 
        }
        private byte _HW_Version_patch_version;
        public byte HW_Version_patch_version {
            get => _HW_Version_patch_version;
            set => _ = Set(ref _HW_Version_patch_version, value);
        }
        
        /*************** Properties for Scratchpad register **************************************/
        private bool _ScratchpadIsSet;
        public bool ScratchpadIsSet {
            get => _ScratchpadIsSet;
            set => _ = Set(ref _ScratchpadIsSet, value); 
        }
        private UInt32 _Scratchpad;
        public UInt32 Scratchpad {
            get => _Scratchpad;
            set => _ = Set(ref _Scratchpad, value);
        }
        
        /*************** Properties for Supported_Boards register ********************************/
        private bool _Supported_BoardsIsSet;
        public bool Supported_BoardsIsSet {
            get => _Supported_BoardsIsSet;
            set => _ = Set(ref _Supported_BoardsIsSet, value); 
        }
        private UInt32 _Supported_Boards;
        public UInt32 Supported_Boards {
            get => _Supported_Boards;
            set => _ = Set(ref _Supported_Boards, value);
        }
        
        /*************** Properties for Configured_Boards register *******************************/
        private bool _Configured_BoardsIsSet;
        public bool Configured_BoardsIsSet {
            get => _Configured_BoardsIsSet;
            set => _ = Set(ref _Configured_BoardsIsSet, value); 
        }
        private BoardIdentifier _Configured_Boards;
        public BoardIdentifier Configured_Boards {
            get => _Configured_Boards;
            set => _ = Set(ref _Configured_Boards, value);
        }
        
        /*************** Properties for Uptime register ******************************************/
        private bool _UptimeIsSet;
        public bool UptimeIsSet {
            get => _UptimeIsSet;
            set => _ = Set(ref _UptimeIsSet, value); 
        }
        private UInt32 _Uptime;
        public UInt32 Uptime {
            get => _Uptime;
            set => _ = Set(ref _Uptime, value);
        }
        
        /*************** Properties for Event_ConfA register *************************************/
        private bool _Event_ConfA_countIsSet;
        public bool Event_ConfA_countIsSet {
            get => _Event_ConfA_countIsSet;
            set => _ = Set(ref _Event_ConfA_countIsSet, value); 
        }
        private short _Event_ConfA_count;
        public short Event_ConfA_count {
            get => _Event_ConfA_count;
            set => _ = Set(ref _Event_ConfA_count, value);
        }
        
        /*************** Properties for Event register *******************************************/
        private bool _Event_sectionIsSet;
        public bool Event_sectionIsSet {
            get => _Event_sectionIsSet;
            set => _ = Set(ref _Event_sectionIsSet, value); 
        }
        private short _Event_section;
        public short Event_section {
            get => _Event_section;
            set => _ = Set(ref _Event_section, value);
        }
        
        private bool _Event_detailIsSet;
        public bool Event_detailIsSet {
            get => _Event_detailIsSet;
            set => _ = Set(ref _Event_detailIsSet, value); 
        }
        private short _Event_detail;
        public short Event_detail {
            get => _Event_detail;
            set => _ = Set(ref _Event_detail, value);
        }
        
        private bool _Event_timestampIsSet;
        public bool Event_timestampIsSet {
            get => _Event_timestampIsSet;
            set => _ = Set(ref _Event_timestampIsSet, value); 
        }
        private short _Event_timestamp;
        public short Event_timestamp {
            get => _Event_timestamp;
            set => _ = Set(ref _Event_timestamp, value);
        }
        
        /*************** Properties for ConfPower register ***************************************/
        private bool _ConfPower_voltage5ToggleIsSet;
        public bool ConfPower_voltage5ToggleIsSet {
            get => _ConfPower_voltage5ToggleIsSet;
            set => _ = Set(ref _ConfPower_voltage5ToggleIsSet, value); 
        }
        private Enabled _ConfPower_voltage5Toggle;
        public Enabled ConfPower_voltage5Toggle {
            get => _ConfPower_voltage5Toggle;
            set => _ = Set(ref _ConfPower_voltage5Toggle, value);
        }
        
        private bool _ConfPower_voltage3ToggleIsSet;
        public bool ConfPower_voltage3ToggleIsSet {
            get => _ConfPower_voltage3ToggleIsSet;
            set => _ = Set(ref _ConfPower_voltage3ToggleIsSet, value); 
        }
        private Enabled _ConfPower_voltage3Toggle;
        public Enabled ConfPower_voltage3Toggle {
            get => _ConfPower_voltage3Toggle;
            set => _ = Set(ref _ConfPower_voltage3Toggle, value);
        }
        
        private bool _ConfPower_voltageVBatToggleIsSet;
        public bool ConfPower_voltageVBatToggleIsSet {
            get => _ConfPower_voltageVBatToggleIsSet;
            set => _ = Set(ref _ConfPower_voltageVBatToggleIsSet, value); 
        }
        private Enabled _ConfPower_voltageVBatToggle;
        public Enabled ConfPower_voltageVBatToggle {
            get => _ConfPower_voltageVBatToggle;
            set => _ = Set(ref _ConfPower_voltageVBatToggle, value);
        }
        
        private bool _ConfPower_voltageVBatAltToggleIsSet;
        public bool ConfPower_voltageVBatAltToggleIsSet {
            get => _ConfPower_voltageVBatAltToggleIsSet;
            set => _ = Set(ref _ConfPower_voltageVBatAltToggleIsSet, value); 
        }
        private Enabled _ConfPower_voltageVBatAltToggle;
        public Enabled ConfPower_voltageVBatAltToggle {
            get => _ConfPower_voltageVBatAltToggle;
            set => _ = Set(ref _ConfPower_voltageVBatAltToggle, value);
        }
        
        private bool _ConfPower_voltage3UtilToggleIsSet;
        public bool ConfPower_voltage3UtilToggleIsSet {
            get => _ConfPower_voltage3UtilToggleIsSet;
            set => _ = Set(ref _ConfPower_voltage3UtilToggleIsSet, value); 
        }
        private Enabled _ConfPower_voltage3UtilToggle;
        public Enabled ConfPower_voltage3UtilToggle {
            get => _ConfPower_voltage3UtilToggle;
            set => _ = Set(ref _ConfPower_voltage3UtilToggle, value);
        }
        
        /*************** Min and Max Properties for MeasureVI_V3 types ***************************/
        /*************** Properties for MeasureVI_V3 register ************************************/
        private bool _MeasureVI_V3_voltageIsSet;
        public bool MeasureVI_V3_voltageIsSet {
            get => _MeasureVI_V3_voltageIsSet;
            set => _ = Set(ref _MeasureVI_V3_voltageIsSet, value); 
        }
        private UInt32 _MeasureVI_V3_voltage;
        public UInt32 MeasureVI_V3_voltage {
            get => _MeasureVI_V3_voltage;
            set => _ = Set(ref _MeasureVI_V3_voltage, value);
        }
        
        private bool _MeasureVI_V3_currentIsSet;
        public bool MeasureVI_V3_currentIsSet {
            get => _MeasureVI_V3_currentIsSet;
            set => _ = Set(ref _MeasureVI_V3_currentIsSet, value); 
        }
        private UInt32 _MeasureVI_V3_current;
        public UInt32 MeasureVI_V3_current {
            get => _MeasureVI_V3_current;
            set => _ = Set(ref _MeasureVI_V3_current, value);
        }
        
        /*************** Min and Max Properties for MeasurePower_V3 types ************************/
        /*************** Properties for MeasurePower_V3 register *********************************/
        private bool _MeasurePower_V3_powerIsSet;
        public bool MeasurePower_V3_powerIsSet {
            get => _MeasurePower_V3_powerIsSet;
            set => _ = Set(ref _MeasurePower_V3_powerIsSet, value); 
        }
        private UInt32 _MeasurePower_V3_power;
        public UInt32 MeasurePower_V3_power {
            get => _MeasurePower_V3_power;
            set => _ = Set(ref _MeasurePower_V3_power, value);
        }
        
        /*************** Properties for MeasureVI_V5 register ************************************/
        private bool _MeasureVI_V5_voltageIsSet;
        public bool MeasureVI_V5_voltageIsSet {
            get => _MeasureVI_V5_voltageIsSet;
            set => _ = Set(ref _MeasureVI_V5_voltageIsSet, value); 
        }
        private UInt32 _MeasureVI_V5_voltage;
        public UInt32 MeasureVI_V5_voltage {
            get => _MeasureVI_V5_voltage;
            set => _ = Set(ref _MeasureVI_V5_voltage, value);
        }
        
        private bool _MeasureVI_V5_currentIsSet;
        public bool MeasureVI_V5_currentIsSet {
            get => _MeasureVI_V5_currentIsSet;
            set => _ = Set(ref _MeasureVI_V5_currentIsSet, value); 
        }
        private UInt32 _MeasureVI_V5_current;
        public UInt32 MeasureVI_V5_current {
            get => _MeasureVI_V5_current;
            set => _ = Set(ref _MeasureVI_V5_current, value);
        }
        
        /*************** Properties for MeasurePower_V5 register *********************************/
        private bool _MeasurePower_V5_powerIsSet;
        public bool MeasurePower_V5_powerIsSet {
            get => _MeasurePower_V5_powerIsSet;
            set => _ = Set(ref _MeasurePower_V5_powerIsSet, value); 
        }
        private UInt32 _MeasurePower_V5_power;
        public UInt32 MeasurePower_V5_power {
            get => _MeasurePower_V5_power;
            set => _ = Set(ref _MeasurePower_V5_power, value);
        }
        
        /*************** Properties for MeasureVI_VBat register **********************************/
        private bool _MeasureVI_VBat_voltageIsSet;
        public bool MeasureVI_VBat_voltageIsSet {
            get => _MeasureVI_VBat_voltageIsSet;
            set => _ = Set(ref _MeasureVI_VBat_voltageIsSet, value); 
        }
        private UInt32 _MeasureVI_VBat_voltage;
        public UInt32 MeasureVI_VBat_voltage {
            get => _MeasureVI_VBat_voltage;
            set => _ = Set(ref _MeasureVI_VBat_voltage, value);
        }
        
        private bool _MeasureVI_VBat_currentIsSet;
        public bool MeasureVI_VBat_currentIsSet {
            get => _MeasureVI_VBat_currentIsSet;
            set => _ = Set(ref _MeasureVI_VBat_currentIsSet, value); 
        }
        private UInt32 _MeasureVI_VBat_current;
        public UInt32 MeasureVI_VBat_current {
            get => _MeasureVI_VBat_current;
            set => _ = Set(ref _MeasureVI_VBat_current, value);
        }
        
        /*************** Properties for MeasurePower_VBat register *******************************/
        private bool _MeasurePower_VBat_powerIsSet;
        public bool MeasurePower_VBat_powerIsSet {
            get => _MeasurePower_VBat_powerIsSet;
            set => _ = Set(ref _MeasurePower_VBat_powerIsSet, value); 
        }
        private UInt32 _MeasurePower_VBat_power;
        public UInt32 MeasurePower_VBat_power {
            get => _MeasurePower_VBat_power;
            set => _ = Set(ref _MeasurePower_VBat_power, value);
        }
        
        /*************** Properties for MeasureVI_VBatAlt register *******************************/
        private bool _MeasureVI_VBatAlt_voltageIsSet;
        public bool MeasureVI_VBatAlt_voltageIsSet {
            get => _MeasureVI_VBatAlt_voltageIsSet;
            set => _ = Set(ref _MeasureVI_VBatAlt_voltageIsSet, value); 
        }
        private UInt32 _MeasureVI_VBatAlt_voltage;
        public UInt32 MeasureVI_VBatAlt_voltage {
            get => _MeasureVI_VBatAlt_voltage;
            set => _ = Set(ref _MeasureVI_VBatAlt_voltage, value);
        }
        
        private bool _MeasureVI_VBatAlt_currentIsSet;
        public bool MeasureVI_VBatAlt_currentIsSet {
            get => _MeasureVI_VBatAlt_currentIsSet;
            set => _ = Set(ref _MeasureVI_VBatAlt_currentIsSet, value); 
        }
        private UInt32 _MeasureVI_VBatAlt_current;
        public UInt32 MeasureVI_VBatAlt_current {
            get => _MeasureVI_VBatAlt_current;
            set => _ = Set(ref _MeasureVI_VBatAlt_current, value);
        }
        
        /*************** Properties for MeasurePower_VBatAlt register ****************************/
        private bool _MeasurePower_VBatAlt_powerIsSet;
        public bool MeasurePower_VBatAlt_powerIsSet {
            get => _MeasurePower_VBatAlt_powerIsSet;
            set => _ = Set(ref _MeasurePower_VBatAlt_powerIsSet, value); 
        }
        private UInt32 _MeasurePower_VBatAlt_power;
        public UInt32 MeasurePower_VBatAlt_power {
            get => _MeasurePower_VBatAlt_power;
            set => _ = Set(ref _MeasurePower_VBatAlt_power, value);
        }
        
        /*************** Properties for I2CConfA register ****************************************/
        private bool _I2CConfA_TRDELIsSet;
        public bool I2CConfA_TRDELIsSet {
            get => _I2CConfA_TRDELIsSet;
            set => _ = Set(ref _I2CConfA_TRDELIsSet, value); 
        }
        private byte _I2CConfA_TRDEL;
        public byte I2CConfA_TRDEL {
            get => _I2CConfA_TRDEL;
            set => _ = Set(ref _I2CConfA_TRDEL, value);
        }
        
        private bool _I2CConfA_WRDELIsSet;
        public bool I2CConfA_WRDELIsSet {
            get => _I2CConfA_WRDELIsSet;
            set => _ = Set(ref _I2CConfA_WRDELIsSet, value); 
        }
        private byte _I2CConfA_WRDEL;
        public byte I2CConfA_WRDEL {
            get => _I2CConfA_WRDEL;
            set => _ = Set(ref _I2CConfA_WRDEL, value);
        }
        
        public byte I2CConfA_SPDMax { get => 40; }
        public byte I2CConfA_SPDMin { get => 1; }
        private bool _I2CConfA_SPDIsSet;
        public bool I2CConfA_SPDIsSet {
            get => _I2CConfA_SPDIsSet;
            set => _ = Set(ref _I2CConfA_SPDIsSet, value); 
        }
        private byte _I2CConfA_SPD;
        public byte I2CConfA_SPD {
            get => _I2CConfA_SPD;
            set => _ = Set(ref _I2CConfA_SPD, value);
        }
        
        /*************** Properties for I2CConfB register ****************************************/
        private bool _I2CConfB_ADDRIsSet;
        public bool I2CConfB_ADDRIsSet {
            get => _I2CConfB_ADDRIsSet;
            set => _ = Set(ref _I2CConfB_ADDRIsSet, value); 
        }
        private byte _I2CConfB_ADDR;
        public byte I2CConfB_ADDR {
            get => _I2CConfB_ADDR;
            set => _ = Set(ref _I2CConfB_ADDR, value);
        }
        
        /*************** Properties for MultiConf0 register **************************************/
        private bool _MultiConf0_DetectedIsSet;
        public bool MultiConf0_DetectedIsSet {
            get => _MultiConf0_DetectedIsSet;
            set => _ = Set(ref _MultiConf0_DetectedIsSet, value); 
        }
        private Enabled _MultiConf0_Detected;
        public Enabled MultiConf0_Detected {
            get => _MultiConf0_Detected;
            set => _ = Set(ref _MultiConf0_Detected, value);
        }
        
        private bool _MultiConf0_AutoCLRIsSet;
        public bool MultiConf0_AutoCLRIsSet {
            get => _MultiConf0_AutoCLRIsSet;
            set => _ = Set(ref _MultiConf0_AutoCLRIsSet, value); 
        }
        private Enabled _MultiConf0_AutoCLR;
        public Enabled MultiConf0_AutoCLR {
            get => _MultiConf0_AutoCLR;
            set => _ = Set(ref _MultiConf0_AutoCLR, value);
        }
        
        private bool _MultiConf0_ScanEnabledIsSet;
        public bool MultiConf0_ScanEnabledIsSet {
            get => _MultiConf0_ScanEnabledIsSet;
            set => _ = Set(ref _MultiConf0_ScanEnabledIsSet, value); 
        }
        private Enabled _MultiConf0_ScanEnabled;
        public Enabled MultiConf0_ScanEnabled {
            get => _MultiConf0_ScanEnabled;
            set => _ = Set(ref _MultiConf0_ScanEnabled, value);
        }
        
        private bool _MultiConf0_FanPos1IsSet;
        public bool MultiConf0_FanPos1IsSet {
            get => _MultiConf0_FanPos1IsSet;
            set => _ = Set(ref _MultiConf0_FanPos1IsSet, value); 
        }
        private Enabled _MultiConf0_FanPos1;
        public Enabled MultiConf0_FanPos1 {
            get => _MultiConf0_FanPos1;
            set => _ = Set(ref _MultiConf0_FanPos1, value);
        }
        
        private bool _MultiConf0_FanPos2IsSet;
        public bool MultiConf0_FanPos2IsSet {
            get => _MultiConf0_FanPos2IsSet;
            set => _ = Set(ref _MultiConf0_FanPos2IsSet, value); 
        }
        private Enabled _MultiConf0_FanPos2;
        public Enabled MultiConf0_FanPos2 {
            get => _MultiConf0_FanPos2;
            set => _ = Set(ref _MultiConf0_FanPos2, value);
        }
        
        private bool _MultiConf0_FanPos3IsSet;
        public bool MultiConf0_FanPos3IsSet {
            get => _MultiConf0_FanPos3IsSet;
            set => _ = Set(ref _MultiConf0_FanPos3IsSet, value); 
        }
        private Enabled _MultiConf0_FanPos3;
        public Enabled MultiConf0_FanPos3 {
            get => _MultiConf0_FanPos3;
            set => _ = Set(ref _MultiConf0_FanPos3, value);
        }
        
        private bool _MultiConf0_FanPos4IsSet;
        public bool MultiConf0_FanPos4IsSet {
            get => _MultiConf0_FanPos4IsSet;
            set => _ = Set(ref _MultiConf0_FanPos4IsSet, value); 
        }
        private Enabled _MultiConf0_FanPos4;
        public Enabled MultiConf0_FanPos4 {
            get => _MultiConf0_FanPos4;
            set => _ = Set(ref _MultiConf0_FanPos4, value);
        }
        
        /*************** Properties for ConfTempSense register ***********************************/
        private bool _ConfTempSense_EnableMeasurementsIsSet;
        public bool ConfTempSense_EnableMeasurementsIsSet {
            get => _ConfTempSense_EnableMeasurementsIsSet;
            set => _ = Set(ref _ConfTempSense_EnableMeasurementsIsSet, value); 
        }
        private Enabled _ConfTempSense_EnableMeasurements;
        public Enabled ConfTempSense_EnableMeasurements {
            get => _ConfTempSense_EnableMeasurements;
            set => _ = Set(ref _ConfTempSense_EnableMeasurements, value);
        }
        
        /*************** Properties for CANConfA register ****************************************/
        private bool _CANConfA_BaudRateIsSet;
        public bool CANConfA_BaudRateIsSet {
            get => _CANConfA_BaudRateIsSet;
            set => _ = Set(ref _CANConfA_BaudRateIsSet, value); 
        }
        private UInt32 _CANConfA_BaudRate;
        public UInt32 CANConfA_BaudRate {
            get => _CANConfA_BaudRate;
            set => _ = Set(ref _CANConfA_BaudRate, value);
        }
        
        private bool _CANConfA_EnableRetriesIsSet;
        public bool CANConfA_EnableRetriesIsSet {
            get => _CANConfA_EnableRetriesIsSet;
            set => _ = Set(ref _CANConfA_EnableRetriesIsSet, value); 
        }
        private Enabled _CANConfA_EnableRetries;
        public Enabled CANConfA_EnableRetries {
            get => _CANConfA_EnableRetries;
            set => _ = Set(ref _CANConfA_EnableRetries, value);
        }
        
        private bool _CANConfA_FlipCanBytesIsSet;
        public bool CANConfA_FlipCanBytesIsSet {
            get => _CANConfA_FlipCanBytesIsSet;
            set => _ = Set(ref _CANConfA_FlipCanBytesIsSet, value); 
        }
        private Enabled _CANConfA_FlipCanBytes;
        public Enabled CANConfA_FlipCanBytes {
            get => _CANConfA_FlipCanBytes;
            set => _ = Set(ref _CANConfA_FlipCanBytes, value);
        }
        
        /*************** Properties for CANConfB register ****************************************/
        private bool _CANConfB_AddressIsSet;
        public bool CANConfB_AddressIsSet {
            get => _CANConfB_AddressIsSet;
            set => _ = Set(ref _CANConfB_AddressIsSet, value); 
        }
        private UInt32 _CANConfB_Address;
        public UInt32 CANConfB_Address {
            get => _CANConfB_Address;
            set => _ = Set(ref _CANConfB_Address, value);
        }
        
        /*************** Properties for SerialConf register **************************************/
        private bool _SerialConf_SerialModeIsSet;
        public bool SerialConf_SerialModeIsSet {
            get => _SerialConf_SerialModeIsSet;
            set => _ = Set(ref _SerialConf_SerialModeIsSet, value); 
        }
        private SerialMode _SerialConf_SerialMode;
        public SerialMode SerialConf_SerialMode {
            get => _SerialConf_SerialMode;
            set => _ = Set(ref _SerialConf_SerialMode, value);
        }
        
        private bool _SerialConf_ParityEnabledIsSet;
        public bool SerialConf_ParityEnabledIsSet {
            get => _SerialConf_ParityEnabledIsSet;
            set => _ = Set(ref _SerialConf_ParityEnabledIsSet, value); 
        }
        private Enabled _SerialConf_ParityEnabled;
        public Enabled SerialConf_ParityEnabled {
            get => _SerialConf_ParityEnabled;
            set => _ = Set(ref _SerialConf_ParityEnabled, value);
        }
        
        private bool _SerialConf_ParityModeIsSet;
        public bool SerialConf_ParityModeIsSet {
            get => _SerialConf_ParityModeIsSet;
            set => _ = Set(ref _SerialConf_ParityModeIsSet, value); 
        }
        private ParityModes _SerialConf_ParityMode;
        public ParityModes SerialConf_ParityMode {
            get => _SerialConf_ParityMode;
            set => _ = Set(ref _SerialConf_ParityMode, value);
        }
        
        private bool _SerialConf_BaudRatesIsSet;
        public bool SerialConf_BaudRatesIsSet {
            get => _SerialConf_BaudRatesIsSet;
            set => _ = Set(ref _SerialConf_BaudRatesIsSet, value); 
        }
        private USART_BaudRates _SerialConf_BaudRates;
        public USART_BaudRates SerialConf_BaudRates {
            get => _SerialConf_BaudRates;
            set => _ = Set(ref _SerialConf_BaudRates, value);
        }
        
        /*************** Properties for PC104Pins register ***************************************/
        private bool _PC104Pins_ENAIsSet;
        public bool PC104Pins_ENAIsSet {
            get => _PC104Pins_ENAIsSet;
            set => _ = Set(ref _PC104Pins_ENAIsSet, value); 
        }
        private Enabled _PC104Pins_ENA;
        public Enabled PC104Pins_ENA {
            get => _PC104Pins_ENA;
            set => _ = Set(ref _PC104Pins_ENA, value);
        }
        
        private bool _PC104Pins_nRSTIsSet;
        public bool PC104Pins_nRSTIsSet {
            get => _PC104Pins_nRSTIsSet;
            set => _ = Set(ref _PC104Pins_nRSTIsSet, value); 
        }
        private Enabled _PC104Pins_nRST;
        public Enabled PC104Pins_nRST {
            get => _PC104Pins_nRST;
            set => _ = Set(ref _PC104Pins_nRST, value);
        }
        
        private bool _PC104Pins_RDYIsSet;
        public bool PC104Pins_RDYIsSet {
            get => _PC104Pins_RDYIsSet;
            set => _ = Set(ref _PC104Pins_RDYIsSet, value); 
        }
        private Enabled _PC104Pins_RDY;
        public Enabled PC104Pins_RDY {
            get => _PC104Pins_RDY;
            set => _ = Set(ref _PC104Pins_RDY, value);
        }
        
        /*************** Properties for XTXMultitester register **********************************/
        private bool _XTXMultitester_POS1_XTX_ENIsSet;
        public bool XTXMultitester_POS1_XTX_ENIsSet {
            get => _XTXMultitester_POS1_XTX_ENIsSet;
            set => _ = Set(ref _XTXMultitester_POS1_XTX_ENIsSet, value); 
        }
        private Enabled _XTXMultitester_POS1_XTX_EN;
        public Enabled XTXMultitester_POS1_XTX_EN {
            get => _XTXMultitester_POS1_XTX_EN;
            set => _ = Set(ref _XTXMultitester_POS1_XTX_EN, value);
        }
        
        private bool _XTXMultitester_POS1_XTX_PowerIsSet;
        public bool XTXMultitester_POS1_XTX_PowerIsSet {
            get => _XTXMultitester_POS1_XTX_PowerIsSet;
            set => _ = Set(ref _XTXMultitester_POS1_XTX_PowerIsSet, value); 
        }
        private Enabled _XTXMultitester_POS1_XTX_Power;
        public Enabled XTXMultitester_POS1_XTX_Power {
            get => _XTXMultitester_POS1_XTX_Power;
            set => _ = Set(ref _XTXMultitester_POS1_XTX_Power, value);
        }
        
        private bool _XTXMultitester_POS1_XTX_nResetIsSet;
        public bool XTXMultitester_POS1_XTX_nResetIsSet {
            get => _XTXMultitester_POS1_XTX_nResetIsSet;
            set => _ = Set(ref _XTXMultitester_POS1_XTX_nResetIsSet, value); 
        }
        private Enabled _XTXMultitester_POS1_XTX_nReset;
        public Enabled XTXMultitester_POS1_XTX_nReset {
            get => _XTXMultitester_POS1_XTX_nReset;
            set => _ = Set(ref _XTXMultitester_POS1_XTX_nReset, value);
        }
        
        private bool _XTXMultitester_POS2_XTX_ENIsSet;
        public bool XTXMultitester_POS2_XTX_ENIsSet {
            get => _XTXMultitester_POS2_XTX_ENIsSet;
            set => _ = Set(ref _XTXMultitester_POS2_XTX_ENIsSet, value); 
        }
        private Enabled _XTXMultitester_POS2_XTX_EN;
        public Enabled XTXMultitester_POS2_XTX_EN {
            get => _XTXMultitester_POS2_XTX_EN;
            set => _ = Set(ref _XTXMultitester_POS2_XTX_EN, value);
        }
        
        private bool _XTXMultitester_POS2_XTX_PowerIsSet;
        public bool XTXMultitester_POS2_XTX_PowerIsSet {
            get => _XTXMultitester_POS2_XTX_PowerIsSet;
            set => _ = Set(ref _XTXMultitester_POS2_XTX_PowerIsSet, value); 
        }
        private Enabled _XTXMultitester_POS2_XTX_Power;
        public Enabled XTXMultitester_POS2_XTX_Power {
            get => _XTXMultitester_POS2_XTX_Power;
            set => _ = Set(ref _XTXMultitester_POS2_XTX_Power, value);
        }
        
        private bool _XTXMultitester_POS2_XTX_nResetIsSet;
        public bool XTXMultitester_POS2_XTX_nResetIsSet {
            get => _XTXMultitester_POS2_XTX_nResetIsSet;
            set => _ = Set(ref _XTXMultitester_POS2_XTX_nResetIsSet, value); 
        }
        private Enabled _XTXMultitester_POS2_XTX_nReset;
        public Enabled XTXMultitester_POS2_XTX_nReset {
            get => _XTXMultitester_POS2_XTX_nReset;
            set => _ = Set(ref _XTXMultitester_POS2_XTX_nReset, value);
        }
        
        private bool _XTXMultitester_POS3_XTX_ENIsSet;
        public bool XTXMultitester_POS3_XTX_ENIsSet {
            get => _XTXMultitester_POS3_XTX_ENIsSet;
            set => _ = Set(ref _XTXMultitester_POS3_XTX_ENIsSet, value); 
        }
        private Enabled _XTXMultitester_POS3_XTX_EN;
        public Enabled XTXMultitester_POS3_XTX_EN {
            get => _XTXMultitester_POS3_XTX_EN;
            set => _ = Set(ref _XTXMultitester_POS3_XTX_EN, value);
        }
        
        private bool _XTXMultitester_POS3_XTX_PowerIsSet;
        public bool XTXMultitester_POS3_XTX_PowerIsSet {
            get => _XTXMultitester_POS3_XTX_PowerIsSet;
            set => _ = Set(ref _XTXMultitester_POS3_XTX_PowerIsSet, value); 
        }
        private Enabled _XTXMultitester_POS3_XTX_Power;
        public Enabled XTXMultitester_POS3_XTX_Power {
            get => _XTXMultitester_POS3_XTX_Power;
            set => _ = Set(ref _XTXMultitester_POS3_XTX_Power, value);
        }
        
        private bool _XTXMultitester_POS3_XTX_nResetIsSet;
        public bool XTXMultitester_POS3_XTX_nResetIsSet {
            get => _XTXMultitester_POS3_XTX_nResetIsSet;
            set => _ = Set(ref _XTXMultitester_POS3_XTX_nResetIsSet, value); 
        }
        private Enabled _XTXMultitester_POS3_XTX_nReset;
        public Enabled XTXMultitester_POS3_XTX_nReset {
            get => _XTXMultitester_POS3_XTX_nReset;
            set => _ = Set(ref _XTXMultitester_POS3_XTX_nReset, value);
        }
        
        private bool _XTXMultitester_POS4_XTX_ENIsSet;
        public bool XTXMultitester_POS4_XTX_ENIsSet {
            get => _XTXMultitester_POS4_XTX_ENIsSet;
            set => _ = Set(ref _XTXMultitester_POS4_XTX_ENIsSet, value); 
        }
        private Enabled _XTXMultitester_POS4_XTX_EN;
        public Enabled XTXMultitester_POS4_XTX_EN {
            get => _XTXMultitester_POS4_XTX_EN;
            set => _ = Set(ref _XTXMultitester_POS4_XTX_EN, value);
        }
        
        private bool _XTXMultitester_POS4_XTX_PowerIsSet;
        public bool XTXMultitester_POS4_XTX_PowerIsSet {
            get => _XTXMultitester_POS4_XTX_PowerIsSet;
            set => _ = Set(ref _XTXMultitester_POS4_XTX_PowerIsSet, value); 
        }
        private Enabled _XTXMultitester_POS4_XTX_Power;
        public Enabled XTXMultitester_POS4_XTX_Power {
            get => _XTXMultitester_POS4_XTX_Power;
            set => _ = Set(ref _XTXMultitester_POS4_XTX_Power, value);
        }
        
        private bool _XTXMultitester_POS4_XTX_nResetIsSet;
        public bool XTXMultitester_POS4_XTX_nResetIsSet {
            get => _XTXMultitester_POS4_XTX_nResetIsSet;
            set => _ = Set(ref _XTXMultitester_POS4_XTX_nResetIsSet, value); 
        }
        private Enabled _XTXMultitester_POS4_XTX_nReset;
        public Enabled XTXMultitester_POS4_XTX_nReset {
            get => _XTXMultitester_POS4_XTX_nReset;
            set => _ = Set(ref _XTXMultitester_POS4_XTX_nReset, value);
        }
        
        /*************** Properties for RFRelaysConf register ************************************/
        private bool _RFRelaysConf_RFSW1_DetectedIsSet;
        public bool RFRelaysConf_RFSW1_DetectedIsSet {
            get => _RFRelaysConf_RFSW1_DetectedIsSet;
            set => _ = Set(ref _RFRelaysConf_RFSW1_DetectedIsSet, value); 
        }
        private Enabled _RFRelaysConf_RFSW1_Detected;
        public Enabled RFRelaysConf_RFSW1_Detected {
            get => _RFRelaysConf_RFSW1_Detected;
            set => _ = Set(ref _RFRelaysConf_RFSW1_Detected, value);
        }
        
        private bool _RFRelaysConf_RFSW2_DetectedIsSet;
        public bool RFRelaysConf_RFSW2_DetectedIsSet {
            get => _RFRelaysConf_RFSW2_DetectedIsSet;
            set => _ = Set(ref _RFRelaysConf_RFSW2_DetectedIsSet, value); 
        }
        private Enabled _RFRelaysConf_RFSW2_Detected;
        public Enabled RFRelaysConf_RFSW2_Detected {
            get => _RFRelaysConf_RFSW2_Detected;
            set => _ = Set(ref _RFRelaysConf_RFSW2_Detected, value);
        }
        
        private bool _RFRelaysConf_ScanEnabledIsSet;
        public bool RFRelaysConf_ScanEnabledIsSet {
            get => _RFRelaysConf_ScanEnabledIsSet;
            set => _ = Set(ref _RFRelaysConf_ScanEnabledIsSet, value); 
        }
        private Enabled _RFRelaysConf_ScanEnabled;
        public Enabled RFRelaysConf_ScanEnabled {
            get => _RFRelaysConf_ScanEnabled;
            set => _ = Set(ref _RFRelaysConf_ScanEnabled, value);
        }
        
        private bool _RFRelaysConf_RfSw1ChanIsSet;
        public bool RFRelaysConf_RfSw1ChanIsSet {
            get => _RFRelaysConf_RfSw1ChanIsSet;
            set => _ = Set(ref _RFRelaysConf_RfSw1ChanIsSet, value); 
        }
        private byte _RFRelaysConf_RfSw1Chan;
        public byte RFRelaysConf_RfSw1Chan {
            get => _RFRelaysConf_RfSw1Chan;
            set => _ = Set(ref _RFRelaysConf_RfSw1Chan, value);
        }
        
        private bool _RFRelaysConf_RfSw2ChanIsSet;
        public bool RFRelaysConf_RfSw2ChanIsSet {
            get => _RFRelaysConf_RfSw2ChanIsSet;
            set => _ = Set(ref _RFRelaysConf_RfSw2ChanIsSet, value); 
        }
        private byte _RFRelaysConf_RfSw2Chan;
        public byte RFRelaysConf_RfSw2Chan {
            get => _RFRelaysConf_RfSw2Chan;
            set => _ = Set(ref _RFRelaysConf_RfSw2Chan, value);
        }
        
        /*************** Min and Max Properties for MultiConf1_Status types **********************/
        /*************** Properties for MultiConf1_Status register *******************************/
        private bool _MultiConf1_Status_POS1_EnableIsSet;
        public bool MultiConf1_Status_POS1_EnableIsSet {
            get => _MultiConf1_Status_POS1_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS1_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS1_Enable;
        public Enabled MultiConf1_Status_POS1_Enable {
            get => _MultiConf1_Status_POS1_Enable;
            set => _ = Set(ref _MultiConf1_Status_POS1_Enable, value);
        }
        
        private bool _MultiConf1_Status_POS1_PowerIsSet;
        public bool MultiConf1_Status_POS1_PowerIsSet {
            get => _MultiConf1_Status_POS1_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS1_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS1_Power;
        public Enabled MultiConf1_Status_POS1_Power {
            get => _MultiConf1_Status_POS1_Power;
            set => _ = Set(ref _MultiConf1_Status_POS1_Power, value);
        }
        
        private bool _MultiConf1_Status_POS1_nResetIsSet;
        public bool MultiConf1_Status_POS1_nResetIsSet {
            get => _MultiConf1_Status_POS1_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS1_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS1_nReset;
        public Enabled MultiConf1_Status_POS1_nReset {
            get => _MultiConf1_Status_POS1_nReset;
            set => _ = Set(ref _MultiConf1_Status_POS1_nReset, value);
        }
        
        private bool _MultiConf1_Status_POS1_FANIsSet;
        public bool MultiConf1_Status_POS1_FANIsSet {
            get => _MultiConf1_Status_POS1_FANIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS1_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS1_FAN;
        public Enabled MultiConf1_Status_POS1_FAN {
            get => _MultiConf1_Status_POS1_FAN;
            set => _ = Set(ref _MultiConf1_Status_POS1_FAN, value);
        }
        
        private bool _MultiConf1_Status_POS2_EnableIsSet;
        public bool MultiConf1_Status_POS2_EnableIsSet {
            get => _MultiConf1_Status_POS2_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS2_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS2_Enable;
        public Enabled MultiConf1_Status_POS2_Enable {
            get => _MultiConf1_Status_POS2_Enable;
            set => _ = Set(ref _MultiConf1_Status_POS2_Enable, value);
        }
        
        private bool _MultiConf1_Status_POS2_PowerIsSet;
        public bool MultiConf1_Status_POS2_PowerIsSet {
            get => _MultiConf1_Status_POS2_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS2_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS2_Power;
        public Enabled MultiConf1_Status_POS2_Power {
            get => _MultiConf1_Status_POS2_Power;
            set => _ = Set(ref _MultiConf1_Status_POS2_Power, value);
        }
        
        private bool _MultiConf1_Status_POS2_nResetIsSet;
        public bool MultiConf1_Status_POS2_nResetIsSet {
            get => _MultiConf1_Status_POS2_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS2_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS2_nReset;
        public Enabled MultiConf1_Status_POS2_nReset {
            get => _MultiConf1_Status_POS2_nReset;
            set => _ = Set(ref _MultiConf1_Status_POS2_nReset, value);
        }
        
        private bool _MultiConf1_Status_POS2_FANIsSet;
        public bool MultiConf1_Status_POS2_FANIsSet {
            get => _MultiConf1_Status_POS2_FANIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS2_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS2_FAN;
        public Enabled MultiConf1_Status_POS2_FAN {
            get => _MultiConf1_Status_POS2_FAN;
            set => _ = Set(ref _MultiConf1_Status_POS2_FAN, value);
        }
        
        private bool _MultiConf1_Status_POS3_EnableIsSet;
        public bool MultiConf1_Status_POS3_EnableIsSet {
            get => _MultiConf1_Status_POS3_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS3_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS3_Enable;
        public Enabled MultiConf1_Status_POS3_Enable {
            get => _MultiConf1_Status_POS3_Enable;
            set => _ = Set(ref _MultiConf1_Status_POS3_Enable, value);
        }
        
        private bool _MultiConf1_Status_POS3_PowerIsSet;
        public bool MultiConf1_Status_POS3_PowerIsSet {
            get => _MultiConf1_Status_POS3_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS3_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS3_Power;
        public Enabled MultiConf1_Status_POS3_Power {
            get => _MultiConf1_Status_POS3_Power;
            set => _ = Set(ref _MultiConf1_Status_POS3_Power, value);
        }
        
        private bool _MultiConf1_Status_POS3_nResetIsSet;
        public bool MultiConf1_Status_POS3_nResetIsSet {
            get => _MultiConf1_Status_POS3_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS3_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS3_nReset;
        public Enabled MultiConf1_Status_POS3_nReset {
            get => _MultiConf1_Status_POS3_nReset;
            set => _ = Set(ref _MultiConf1_Status_POS3_nReset, value);
        }
        
        private bool _MultiConf1_Status_POS3_FANIsSet;
        public bool MultiConf1_Status_POS3_FANIsSet {
            get => _MultiConf1_Status_POS3_FANIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS3_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS3_FAN;
        public Enabled MultiConf1_Status_POS3_FAN {
            get => _MultiConf1_Status_POS3_FAN;
            set => _ = Set(ref _MultiConf1_Status_POS3_FAN, value);
        }
        
        private bool _MultiConf1_Status_POS4_EnableIsSet;
        public bool MultiConf1_Status_POS4_EnableIsSet {
            get => _MultiConf1_Status_POS4_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS4_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS4_Enable;
        public Enabled MultiConf1_Status_POS4_Enable {
            get => _MultiConf1_Status_POS4_Enable;
            set => _ = Set(ref _MultiConf1_Status_POS4_Enable, value);
        }
        
        private bool _MultiConf1_Status_POS4_PowerIsSet;
        public bool MultiConf1_Status_POS4_PowerIsSet {
            get => _MultiConf1_Status_POS4_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS4_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS4_Power;
        public Enabled MultiConf1_Status_POS4_Power {
            get => _MultiConf1_Status_POS4_Power;
            set => _ = Set(ref _MultiConf1_Status_POS4_Power, value);
        }
        
        private bool _MultiConf1_Status_POS4_nResetIsSet;
        public bool MultiConf1_Status_POS4_nResetIsSet {
            get => _MultiConf1_Status_POS4_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS4_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS4_nReset;
        public Enabled MultiConf1_Status_POS4_nReset {
            get => _MultiConf1_Status_POS4_nReset;
            set => _ = Set(ref _MultiConf1_Status_POS4_nReset, value);
        }
        
        private bool _MultiConf1_Status_POS4_FANIsSet;
        public bool MultiConf1_Status_POS4_FANIsSet {
            get => _MultiConf1_Status_POS4_FANIsSet;
            set => _ = Set(ref _MultiConf1_Status_POS4_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Status_POS4_FAN;
        public Enabled MultiConf1_Status_POS4_FAN {
            get => _MultiConf1_Status_POS4_FAN;
            set => _ = Set(ref _MultiConf1_Status_POS4_FAN, value);
        }
        
        /*************** Properties for MultiConf1_Set register **********************************/
        private bool _MultiConf1_Set_POS1_EnableIsSet;
        public bool MultiConf1_Set_POS1_EnableIsSet {
            get => _MultiConf1_Set_POS1_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS1_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS1_Enable;
        public Enabled MultiConf1_Set_POS1_Enable {
            get => _MultiConf1_Set_POS1_Enable;
            set => _ = Set(ref _MultiConf1_Set_POS1_Enable, value);
        }
        
        private bool _MultiConf1_Set_POS1_PowerIsSet;
        public bool MultiConf1_Set_POS1_PowerIsSet {
            get => _MultiConf1_Set_POS1_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS1_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS1_Power;
        public Enabled MultiConf1_Set_POS1_Power {
            get => _MultiConf1_Set_POS1_Power;
            set => _ = Set(ref _MultiConf1_Set_POS1_Power, value);
        }
        
        private bool _MultiConf1_Set_POS1_nResetIsSet;
        public bool MultiConf1_Set_POS1_nResetIsSet {
            get => _MultiConf1_Set_POS1_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS1_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS1_nReset;
        public Enabled MultiConf1_Set_POS1_nReset {
            get => _MultiConf1_Set_POS1_nReset;
            set => _ = Set(ref _MultiConf1_Set_POS1_nReset, value);
        }
        
        private bool _MultiConf1_Set_POS1_FANIsSet;
        public bool MultiConf1_Set_POS1_FANIsSet {
            get => _MultiConf1_Set_POS1_FANIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS1_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS1_FAN;
        public Enabled MultiConf1_Set_POS1_FAN {
            get => _MultiConf1_Set_POS1_FAN;
            set => _ = Set(ref _MultiConf1_Set_POS1_FAN, value);
        }
        
        private bool _MultiConf1_Set_POS2_EnableIsSet;
        public bool MultiConf1_Set_POS2_EnableIsSet {
            get => _MultiConf1_Set_POS2_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS2_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS2_Enable;
        public Enabled MultiConf1_Set_POS2_Enable {
            get => _MultiConf1_Set_POS2_Enable;
            set => _ = Set(ref _MultiConf1_Set_POS2_Enable, value);
        }
        
        private bool _MultiConf1_Set_POS2_PowerIsSet;
        public bool MultiConf1_Set_POS2_PowerIsSet {
            get => _MultiConf1_Set_POS2_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS2_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS2_Power;
        public Enabled MultiConf1_Set_POS2_Power {
            get => _MultiConf1_Set_POS2_Power;
            set => _ = Set(ref _MultiConf1_Set_POS2_Power, value);
        }
        
        private bool _MultiConf1_Set_POS2_nResetIsSet;
        public bool MultiConf1_Set_POS2_nResetIsSet {
            get => _MultiConf1_Set_POS2_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS2_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS2_nReset;
        public Enabled MultiConf1_Set_POS2_nReset {
            get => _MultiConf1_Set_POS2_nReset;
            set => _ = Set(ref _MultiConf1_Set_POS2_nReset, value);
        }
        
        private bool _MultiConf1_Set_POS2_FANIsSet;
        public bool MultiConf1_Set_POS2_FANIsSet {
            get => _MultiConf1_Set_POS2_FANIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS2_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS2_FAN;
        public Enabled MultiConf1_Set_POS2_FAN {
            get => _MultiConf1_Set_POS2_FAN;
            set => _ = Set(ref _MultiConf1_Set_POS2_FAN, value);
        }
        
        private bool _MultiConf1_Set_POS3_EnableIsSet;
        public bool MultiConf1_Set_POS3_EnableIsSet {
            get => _MultiConf1_Set_POS3_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS3_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS3_Enable;
        public Enabled MultiConf1_Set_POS3_Enable {
            get => _MultiConf1_Set_POS3_Enable;
            set => _ = Set(ref _MultiConf1_Set_POS3_Enable, value);
        }
        
        private bool _MultiConf1_Set_POS3_PowerIsSet;
        public bool MultiConf1_Set_POS3_PowerIsSet {
            get => _MultiConf1_Set_POS3_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS3_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS3_Power;
        public Enabled MultiConf1_Set_POS3_Power {
            get => _MultiConf1_Set_POS3_Power;
            set => _ = Set(ref _MultiConf1_Set_POS3_Power, value);
        }
        
        private bool _MultiConf1_Set_POS3_nResetIsSet;
        public bool MultiConf1_Set_POS3_nResetIsSet {
            get => _MultiConf1_Set_POS3_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS3_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS3_nReset;
        public Enabled MultiConf1_Set_POS3_nReset {
            get => _MultiConf1_Set_POS3_nReset;
            set => _ = Set(ref _MultiConf1_Set_POS3_nReset, value);
        }
        
        private bool _MultiConf1_Set_POS3_FANIsSet;
        public bool MultiConf1_Set_POS3_FANIsSet {
            get => _MultiConf1_Set_POS3_FANIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS3_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS3_FAN;
        public Enabled MultiConf1_Set_POS3_FAN {
            get => _MultiConf1_Set_POS3_FAN;
            set => _ = Set(ref _MultiConf1_Set_POS3_FAN, value);
        }
        
        private bool _MultiConf1_Set_POS4_EnableIsSet;
        public bool MultiConf1_Set_POS4_EnableIsSet {
            get => _MultiConf1_Set_POS4_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS4_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS4_Enable;
        public Enabled MultiConf1_Set_POS4_Enable {
            get => _MultiConf1_Set_POS4_Enable;
            set => _ = Set(ref _MultiConf1_Set_POS4_Enable, value);
        }
        
        private bool _MultiConf1_Set_POS4_PowerIsSet;
        public bool MultiConf1_Set_POS4_PowerIsSet {
            get => _MultiConf1_Set_POS4_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS4_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS4_Power;
        public Enabled MultiConf1_Set_POS4_Power {
            get => _MultiConf1_Set_POS4_Power;
            set => _ = Set(ref _MultiConf1_Set_POS4_Power, value);
        }
        
        private bool _MultiConf1_Set_POS4_nResetIsSet;
        public bool MultiConf1_Set_POS4_nResetIsSet {
            get => _MultiConf1_Set_POS4_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS4_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS4_nReset;
        public Enabled MultiConf1_Set_POS4_nReset {
            get => _MultiConf1_Set_POS4_nReset;
            set => _ = Set(ref _MultiConf1_Set_POS4_nReset, value);
        }
        
        private bool _MultiConf1_Set_POS4_FANIsSet;
        public bool MultiConf1_Set_POS4_FANIsSet {
            get => _MultiConf1_Set_POS4_FANIsSet;
            set => _ = Set(ref _MultiConf1_Set_POS4_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Set_POS4_FAN;
        public Enabled MultiConf1_Set_POS4_FAN {
            get => _MultiConf1_Set_POS4_FAN;
            set => _ = Set(ref _MultiConf1_Set_POS4_FAN, value);
        }
        
        /*************** Properties for MultiConf1_Clear register ********************************/
        private bool _MultiConf1_Clear_POS1_EnableIsSet;
        public bool MultiConf1_Clear_POS1_EnableIsSet {
            get => _MultiConf1_Clear_POS1_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS1_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS1_Enable;
        public Enabled MultiConf1_Clear_POS1_Enable {
            get => _MultiConf1_Clear_POS1_Enable;
            set => _ = Set(ref _MultiConf1_Clear_POS1_Enable, value);
        }
        
        private bool _MultiConf1_Clear_POS1_PowerIsSet;
        public bool MultiConf1_Clear_POS1_PowerIsSet {
            get => _MultiConf1_Clear_POS1_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS1_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS1_Power;
        public Enabled MultiConf1_Clear_POS1_Power {
            get => _MultiConf1_Clear_POS1_Power;
            set => _ = Set(ref _MultiConf1_Clear_POS1_Power, value);
        }
        
        private bool _MultiConf1_Clear_POS1_nResetIsSet;
        public bool MultiConf1_Clear_POS1_nResetIsSet {
            get => _MultiConf1_Clear_POS1_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS1_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS1_nReset;
        public Enabled MultiConf1_Clear_POS1_nReset {
            get => _MultiConf1_Clear_POS1_nReset;
            set => _ = Set(ref _MultiConf1_Clear_POS1_nReset, value);
        }
        
        private bool _MultiConf1_Clear_POS1_FANIsSet;
        public bool MultiConf1_Clear_POS1_FANIsSet {
            get => _MultiConf1_Clear_POS1_FANIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS1_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS1_FAN;
        public Enabled MultiConf1_Clear_POS1_FAN {
            get => _MultiConf1_Clear_POS1_FAN;
            set => _ = Set(ref _MultiConf1_Clear_POS1_FAN, value);
        }
        
        private bool _MultiConf1_Clear_POS2_EnableIsSet;
        public bool MultiConf1_Clear_POS2_EnableIsSet {
            get => _MultiConf1_Clear_POS2_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS2_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS2_Enable;
        public Enabled MultiConf1_Clear_POS2_Enable {
            get => _MultiConf1_Clear_POS2_Enable;
            set => _ = Set(ref _MultiConf1_Clear_POS2_Enable, value);
        }
        
        private bool _MultiConf1_Clear_POS2_PowerIsSet;
        public bool MultiConf1_Clear_POS2_PowerIsSet {
            get => _MultiConf1_Clear_POS2_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS2_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS2_Power;
        public Enabled MultiConf1_Clear_POS2_Power {
            get => _MultiConf1_Clear_POS2_Power;
            set => _ = Set(ref _MultiConf1_Clear_POS2_Power, value);
        }
        
        private bool _MultiConf1_Clear_POS2_nResetIsSet;
        public bool MultiConf1_Clear_POS2_nResetIsSet {
            get => _MultiConf1_Clear_POS2_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS2_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS2_nReset;
        public Enabled MultiConf1_Clear_POS2_nReset {
            get => _MultiConf1_Clear_POS2_nReset;
            set => _ = Set(ref _MultiConf1_Clear_POS2_nReset, value);
        }
        
        private bool _MultiConf1_Clear_POS2_FANIsSet;
        public bool MultiConf1_Clear_POS2_FANIsSet {
            get => _MultiConf1_Clear_POS2_FANIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS2_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS2_FAN;
        public Enabled MultiConf1_Clear_POS2_FAN {
            get => _MultiConf1_Clear_POS2_FAN;
            set => _ = Set(ref _MultiConf1_Clear_POS2_FAN, value);
        }
        
        private bool _MultiConf1_Clear_POS3_EnableIsSet;
        public bool MultiConf1_Clear_POS3_EnableIsSet {
            get => _MultiConf1_Clear_POS3_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS3_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS3_Enable;
        public Enabled MultiConf1_Clear_POS3_Enable {
            get => _MultiConf1_Clear_POS3_Enable;
            set => _ = Set(ref _MultiConf1_Clear_POS3_Enable, value);
        }
        
        private bool _MultiConf1_Clear_POS3_PowerIsSet;
        public bool MultiConf1_Clear_POS3_PowerIsSet {
            get => _MultiConf1_Clear_POS3_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS3_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS3_Power;
        public Enabled MultiConf1_Clear_POS3_Power {
            get => _MultiConf1_Clear_POS3_Power;
            set => _ = Set(ref _MultiConf1_Clear_POS3_Power, value);
        }
        
        private bool _MultiConf1_Clear_POS3_nResetIsSet;
        public bool MultiConf1_Clear_POS3_nResetIsSet {
            get => _MultiConf1_Clear_POS3_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS3_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS3_nReset;
        public Enabled MultiConf1_Clear_POS3_nReset {
            get => _MultiConf1_Clear_POS3_nReset;
            set => _ = Set(ref _MultiConf1_Clear_POS3_nReset, value);
        }
        
        private bool _MultiConf1_Clear_POS3_FANIsSet;
        public bool MultiConf1_Clear_POS3_FANIsSet {
            get => _MultiConf1_Clear_POS3_FANIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS3_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS3_FAN;
        public Enabled MultiConf1_Clear_POS3_FAN {
            get => _MultiConf1_Clear_POS3_FAN;
            set => _ = Set(ref _MultiConf1_Clear_POS3_FAN, value);
        }
        
        private bool _MultiConf1_Clear_POS4_EnableIsSet;
        public bool MultiConf1_Clear_POS4_EnableIsSet {
            get => _MultiConf1_Clear_POS4_EnableIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS4_EnableIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS4_Enable;
        public Enabled MultiConf1_Clear_POS4_Enable {
            get => _MultiConf1_Clear_POS4_Enable;
            set => _ = Set(ref _MultiConf1_Clear_POS4_Enable, value);
        }
        
        private bool _MultiConf1_Clear_POS4_PowerIsSet;
        public bool MultiConf1_Clear_POS4_PowerIsSet {
            get => _MultiConf1_Clear_POS4_PowerIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS4_PowerIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS4_Power;
        public Enabled MultiConf1_Clear_POS4_Power {
            get => _MultiConf1_Clear_POS4_Power;
            set => _ = Set(ref _MultiConf1_Clear_POS4_Power, value);
        }
        
        private bool _MultiConf1_Clear_POS4_nResetIsSet;
        public bool MultiConf1_Clear_POS4_nResetIsSet {
            get => _MultiConf1_Clear_POS4_nResetIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS4_nResetIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS4_nReset;
        public Enabled MultiConf1_Clear_POS4_nReset {
            get => _MultiConf1_Clear_POS4_nReset;
            set => _ = Set(ref _MultiConf1_Clear_POS4_nReset, value);
        }
        
        private bool _MultiConf1_Clear_POS4_FANIsSet;
        public bool MultiConf1_Clear_POS4_FANIsSet {
            get => _MultiConf1_Clear_POS4_FANIsSet;
            set => _ = Set(ref _MultiConf1_Clear_POS4_FANIsSet, value); 
        }
        private Enabled _MultiConf1_Clear_POS4_FAN;
        public Enabled MultiConf1_Clear_POS4_FAN {
            get => _MultiConf1_Clear_POS4_FAN;
            set => _ = Set(ref _MultiConf1_Clear_POS4_FAN, value);
        }
        
        /*************** Properties for XDCConfig register ***************************************/
        private bool _XDCConfig_ADDRIsSet;
        public bool XDCConfig_ADDRIsSet {
            get => _XDCConfig_ADDRIsSet;
            set => _ = Set(ref _XDCConfig_ADDRIsSet, value); 
        }
        private Enabled _XDCConfig_ADDR;
        public Enabled XDCConfig_ADDR {
            get => _XDCConfig_ADDR;
            set => _ = Set(ref _XDCConfig_ADDR, value);
        }
        
        /*************** Properties for CSBoard_T0 register **************************************/
        private bool _CSBoard_T0IsSet;
        public bool CSBoard_T0IsSet {
            get => _CSBoard_T0IsSet;
            set => _ = Set(ref _CSBoard_T0IsSet, value); 
        }
        private Int32 _CSBoard_T0;
        public Int32 CSBoard_T0 {
            get => _CSBoard_T0;
            set => _ = Set(ref _CSBoard_T0, value);
        }
        
        /*************** Properties for CSBoard_T1 register **************************************/
        private bool _CSBoard_T1IsSet;
        public bool CSBoard_T1IsSet {
            get => _CSBoard_T1IsSet;
            set => _ = Set(ref _CSBoard_T1IsSet, value); 
        }
        private Int32 _CSBoard_T1;
        public Int32 CSBoard_T1 {
            get => _CSBoard_T1;
            set => _ = Set(ref _CSBoard_T1, value);
        }
        
        /*************** Properties for CSBoard_T2 register **************************************/
        private bool _CSBoard_T2IsSet;
        public bool CSBoard_T2IsSet {
            get => _CSBoard_T2IsSet;
            set => _ = Set(ref _CSBoard_T2IsSet, value); 
        }
        private Int32 _CSBoard_T2;
        public Int32 CSBoard_T2 {
            get => _CSBoard_T2;
            set => _ = Set(ref _CSBoard_T2, value);
        }
        
        /*************** Properties for CSBoard_T3 register **************************************/
        private bool _CSBoard_T3IsSet;
        public bool CSBoard_T3IsSet {
            get => _CSBoard_T3IsSet;
            set => _ = Set(ref _CSBoard_T3IsSet, value); 
        }
        private Int32 _CSBoard_T3;
        public Int32 CSBoard_T3 {
            get => _CSBoard_T3;
            set => _ = Set(ref _CSBoard_T3, value);
        }
        
        /*************** Properties for CSBoard_T4 register **************************************/
        private bool _CSBoard_T4IsSet;
        public bool CSBoard_T4IsSet {
            get => _CSBoard_T4IsSet;
            set => _ = Set(ref _CSBoard_T4IsSet, value); 
        }
        private Int32 _CSBoard_T4;
        public Int32 CSBoard_T4 {
            get => _CSBoard_T4;
            set => _ = Set(ref _CSBoard_T4, value);
        }
        
        /*************** Properties for CSBoard_T5 register **************************************/
        private bool _CSBoard_T5IsSet;
        public bool CSBoard_T5IsSet {
            get => _CSBoard_T5IsSet;
            set => _ = Set(ref _CSBoard_T5IsSet, value); 
        }
        private Int32 _CSBoard_T5;
        public Int32 CSBoard_T5 {
            get => _CSBoard_T5;
            set => _ = Set(ref _CSBoard_T5, value);
        }
        
        /*************** Properties for CSBoard_T6 register **************************************/
        private bool _CSBoard_T6IsSet;
        public bool CSBoard_T6IsSet {
            get => _CSBoard_T6IsSet;
            set => _ = Set(ref _CSBoard_T6IsSet, value); 
        }
        private Int32 _CSBoard_T6;
        public Int32 CSBoard_T6 {
            get => _CSBoard_T6;
            set => _ = Set(ref _CSBoard_T6, value);
        }
        
        /*************** Properties for CSBoard_T7 register **************************************/
        private bool _CSBoard_T7IsSet;
        public bool CSBoard_T7IsSet {
            get => _CSBoard_T7IsSet;
            set => _ = Set(ref _CSBoard_T7IsSet, value); 
        }
        private Int32 _CSBoard_T7;
        public Int32 CSBoard_T7 {
            get => _CSBoard_T7;
            set => _ = Set(ref _CSBoard_T7, value);
        }
        
        /*************** Properties for CSBoard_Current0I0 register ******************************/
        private bool _CSBoard_Current0I0IsSet;
        public bool CSBoard_Current0I0IsSet {
            get => _CSBoard_Current0I0IsSet;
            set => _ = Set(ref _CSBoard_Current0I0IsSet, value); 
        }
        private UInt32 _CSBoard_Current0I0;
        public UInt32 CSBoard_Current0I0 {
            get => _CSBoard_Current0I0;
            set => _ = Set(ref _CSBoard_Current0I0, value);
        }
        
        /*************** Properties for CSBoard_Current0I1 register ******************************/
        private bool _CSBoard_Current0I1IsSet;
        public bool CSBoard_Current0I1IsSet {
            get => _CSBoard_Current0I1IsSet;
            set => _ = Set(ref _CSBoard_Current0I1IsSet, value); 
        }
        private UInt32 _CSBoard_Current0I1;
        public UInt32 CSBoard_Current0I1 {
            get => _CSBoard_Current0I1;
            set => _ = Set(ref _CSBoard_Current0I1, value);
        }
        
        /*************** Properties for CSBoard_Current0I2 register ******************************/
        private bool _CSBoard_Current0I2IsSet;
        public bool CSBoard_Current0I2IsSet {
            get => _CSBoard_Current0I2IsSet;
            set => _ = Set(ref _CSBoard_Current0I2IsSet, value); 
        }
        private UInt32 _CSBoard_Current0I2;
        public UInt32 CSBoard_Current0I2 {
            get => _CSBoard_Current0I2;
            set => _ = Set(ref _CSBoard_Current0I2, value);
        }
        
        /*************** Properties for CSBoard_Current1I0 register ******************************/
        private bool _CSBoard_Current1I0IsSet;
        public bool CSBoard_Current1I0IsSet {
            get => _CSBoard_Current1I0IsSet;
            set => _ = Set(ref _CSBoard_Current1I0IsSet, value); 
        }
        private UInt32 _CSBoard_Current1I0;
        public UInt32 CSBoard_Current1I0 {
            get => _CSBoard_Current1I0;
            set => _ = Set(ref _CSBoard_Current1I0, value);
        }
        
        /*************** Properties for CSBoard_Current1I1 register ******************************/
        private bool _CSBoard_Current1I1IsSet;
        public bool CSBoard_Current1I1IsSet {
            get => _CSBoard_Current1I1IsSet;
            set => _ = Set(ref _CSBoard_Current1I1IsSet, value); 
        }
        private UInt32 _CSBoard_Current1I1;
        public UInt32 CSBoard_Current1I1 {
            get => _CSBoard_Current1I1;
            set => _ = Set(ref _CSBoard_Current1I1, value);
        }
        
        /*************** Properties for CSBoard_Current1I2 register ******************************/
        private bool _CSBoard_Current1I2IsSet;
        public bool CSBoard_Current1I2IsSet {
            get => _CSBoard_Current1I2IsSet;
            set => _ = Set(ref _CSBoard_Current1I2IsSet, value); 
        }
        private UInt32 _CSBoard_Current1I2;
        public UInt32 CSBoard_Current1I2 {
            get => _CSBoard_Current1I2;
            set => _ = Set(ref _CSBoard_Current1I2, value);
        }
        
        /*************** Properties for CSBoard_Current2I0 register ******************************/
        private bool _CSBoard_Current2I0IsSet;
        public bool CSBoard_Current2I0IsSet {
            get => _CSBoard_Current2I0IsSet;
            set => _ = Set(ref _CSBoard_Current2I0IsSet, value); 
        }
        private UInt32 _CSBoard_Current2I0;
        public UInt32 CSBoard_Current2I0 {
            get => _CSBoard_Current2I0;
            set => _ = Set(ref _CSBoard_Current2I0, value);
        }
        
        /*************** Properties for CSBoard_Current2I1 register ******************************/
        private bool _CSBoard_Current2I1IsSet;
        public bool CSBoard_Current2I1IsSet {
            get => _CSBoard_Current2I1IsSet;
            set => _ = Set(ref _CSBoard_Current2I1IsSet, value); 
        }
        private UInt32 _CSBoard_Current2I1;
        public UInt32 CSBoard_Current2I1 {
            get => _CSBoard_Current2I1;
            set => _ = Set(ref _CSBoard_Current2I1, value);
        }
        
        /*************** Properties for CSBoard_Current2I2 register ******************************/
        private bool _CSBoard_Current2I2IsSet;
        public bool CSBoard_Current2I2IsSet {
            get => _CSBoard_Current2I2IsSet;
            set => _ = Set(ref _CSBoard_Current2I2IsSet, value); 
        }
        private UInt32 _CSBoard_Current2I2;
        public UInt32 CSBoard_Current2I2 {
            get => _CSBoard_Current2I2;
            set => _ = Set(ref _CSBoard_Current2I2, value);
        }
        
        /*************** Properties for CSBoard_Current3I0 register ******************************/
        private bool _CSBoard_Current3I0IsSet;
        public bool CSBoard_Current3I0IsSet {
            get => _CSBoard_Current3I0IsSet;
            set => _ = Set(ref _CSBoard_Current3I0IsSet, value); 
        }
        private UInt32 _CSBoard_Current3I0;
        public UInt32 CSBoard_Current3I0 {
            get => _CSBoard_Current3I0;
            set => _ = Set(ref _CSBoard_Current3I0, value);
        }
        
        /*************** Properties for CSBoard_Current3I1 register ******************************/
        private bool _CSBoard_Current3I1IsSet;
        public bool CSBoard_Current3I1IsSet {
            get => _CSBoard_Current3I1IsSet;
            set => _ = Set(ref _CSBoard_Current3I1IsSet, value); 
        }
        private UInt32 _CSBoard_Current3I1;
        public UInt32 CSBoard_Current3I1 {
            get => _CSBoard_Current3I1;
            set => _ = Set(ref _CSBoard_Current3I1, value);
        }
        
        /*************** Properties for CSBoard_Current3I2 register ******************************/
        private bool _CSBoard_Current3I2IsSet;
        public bool CSBoard_Current3I2IsSet {
            get => _CSBoard_Current3I2IsSet;
            set => _ = Set(ref _CSBoard_Current3I2IsSet, value); 
        }
        private UInt32 _CSBoard_Current3I2;
        public UInt32 CSBoard_Current3I2 {
            get => _CSBoard_Current3I2;
            set => _ = Set(ref _CSBoard_Current3I2, value);
        }
        
        /*************** Properties for CSBoard_Current4I0 register ******************************/
        private bool _CSBoard_Current4I0IsSet;
        public bool CSBoard_Current4I0IsSet {
            get => _CSBoard_Current4I0IsSet;
            set => _ = Set(ref _CSBoard_Current4I0IsSet, value); 
        }
        private UInt32 _CSBoard_Current4I0;
        public UInt32 CSBoard_Current4I0 {
            get => _CSBoard_Current4I0;
            set => _ = Set(ref _CSBoard_Current4I0, value);
        }
        
        /*************** Properties for CSBoard_Current4I1 register ******************************/
        private bool _CSBoard_Current4I1IsSet;
        public bool CSBoard_Current4I1IsSet {
            get => _CSBoard_Current4I1IsSet;
            set => _ = Set(ref _CSBoard_Current4I1IsSet, value); 
        }
        private UInt32 _CSBoard_Current4I1;
        public UInt32 CSBoard_Current4I1 {
            get => _CSBoard_Current4I1;
            set => _ = Set(ref _CSBoard_Current4I1, value);
        }
        
        /*************** Properties for CSBoard_Current4I2 register ******************************/
        private bool _CSBoard_Current4I2IsSet;
        public bool CSBoard_Current4I2IsSet {
            get => _CSBoard_Current4I2IsSet;
            set => _ = Set(ref _CSBoard_Current4I2IsSet, value); 
        }
        private UInt32 _CSBoard_Current4I2;
        public UInt32 CSBoard_Current4I2 {
            get => _CSBoard_Current4I2;
            set => _ = Set(ref _CSBoard_Current4I2, value);
        }
        
        /*************** Properties for CSBoard_Current5I0 register ******************************/
        private bool _CSBoard_Current5I0IsSet;
        public bool CSBoard_Current5I0IsSet {
            get => _CSBoard_Current5I0IsSet;
            set => _ = Set(ref _CSBoard_Current5I0IsSet, value); 
        }
        private UInt32 _CSBoard_Current5I0;
        public UInt32 CSBoard_Current5I0 {
            get => _CSBoard_Current5I0;
            set => _ = Set(ref _CSBoard_Current5I0, value);
        }
        
        /*************** Properties for CSBoard_Current5I1 register ******************************/
        private bool _CSBoard_Current5I1IsSet;
        public bool CSBoard_Current5I1IsSet {
            get => _CSBoard_Current5I1IsSet;
            set => _ = Set(ref _CSBoard_Current5I1IsSet, value); 
        }
        private UInt32 _CSBoard_Current5I1;
        public UInt32 CSBoard_Current5I1 {
            get => _CSBoard_Current5I1;
            set => _ = Set(ref _CSBoard_Current5I1, value);
        }
        
        /*************** Properties for CSBoard_Current5I2 register ******************************/
        private bool _CSBoard_Current5I2IsSet;
        public bool CSBoard_Current5I2IsSet {
            get => _CSBoard_Current5I2IsSet;
            set => _ = Set(ref _CSBoard_Current5I2IsSet, value); 
        }
        private UInt32 _CSBoard_Current5I2;
        public UInt32 CSBoard_Current5I2 {
            get => _CSBoard_Current5I2;
            set => _ = Set(ref _CSBoard_Current5I2, value);
        }
        
        /*************** Properties for CSBoard_Current6I0 register ******************************/
        private bool _CSBoard_Current6I0IsSet;
        public bool CSBoard_Current6I0IsSet {
            get => _CSBoard_Current6I0IsSet;
            set => _ = Set(ref _CSBoard_Current6I0IsSet, value); 
        }
        private UInt32 _CSBoard_Current6I0;
        public UInt32 CSBoard_Current6I0 {
            get => _CSBoard_Current6I0;
            set => _ = Set(ref _CSBoard_Current6I0, value);
        }
        
        /*************** Properties for CSBoard_Current6I1 register ******************************/
        private bool _CSBoard_Current6I1IsSet;
        public bool CSBoard_Current6I1IsSet {
            get => _CSBoard_Current6I1IsSet;
            set => _ = Set(ref _CSBoard_Current6I1IsSet, value); 
        }
        private UInt32 _CSBoard_Current6I1;
        public UInt32 CSBoard_Current6I1 {
            get => _CSBoard_Current6I1;
            set => _ = Set(ref _CSBoard_Current6I1, value);
        }
        
        /*************** Properties for CSBoard_Current6I2 register ******************************/
        private bool _CSBoard_Current6I2IsSet;
        public bool CSBoard_Current6I2IsSet {
            get => _CSBoard_Current6I2IsSet;
            set => _ = Set(ref _CSBoard_Current6I2IsSet, value); 
        }
        private UInt32 _CSBoard_Current6I2;
        public UInt32 CSBoard_Current6I2 {
            get => _CSBoard_Current6I2;
            set => _ = Set(ref _CSBoard_Current6I2, value);
        }
        
        /*************** Properties for CSBoard_Current7I0 register ******************************/
        private bool _CSBoard_Current7I0IsSet;
        public bool CSBoard_Current7I0IsSet {
            get => _CSBoard_Current7I0IsSet;
            set => _ = Set(ref _CSBoard_Current7I0IsSet, value); 
        }
        private UInt32 _CSBoard_Current7I0;
        public UInt32 CSBoard_Current7I0 {
            get => _CSBoard_Current7I0;
            set => _ = Set(ref _CSBoard_Current7I0, value);
        }
        
        /*************** Properties for CSBoard_Current7I1 register ******************************/
        private bool _CSBoard_Current7I1IsSet;
        public bool CSBoard_Current7I1IsSet {
            get => _CSBoard_Current7I1IsSet;
            set => _ = Set(ref _CSBoard_Current7I1IsSet, value); 
        }
        private UInt32 _CSBoard_Current7I1;
        public UInt32 CSBoard_Current7I1 {
            get => _CSBoard_Current7I1;
            set => _ = Set(ref _CSBoard_Current7I1, value);
        }
        
        /*************** Properties for CSBoard_Current7I2 register ******************************/
        private bool _CSBoard_Current7I2IsSet;
        public bool CSBoard_Current7I2IsSet {
            get => _CSBoard_Current7I2IsSet;
            set => _ = Set(ref _CSBoard_Current7I2IsSet, value); 
        }
        private UInt32 _CSBoard_Current7I2;
        public UInt32 CSBoard_Current7I2 {
            get => _CSBoard_Current7I2;
            set => _ = Set(ref _CSBoard_Current7I2, value);
        }
        
        /*************** Min and Max Properties for TE_Addr_0 types ******************************/
        /*************** Properties for TE_Addr_0 register ***************************************/
        private bool _TE_Addr_0_ScanEnabledIsSet;
        public bool TE_Addr_0_ScanEnabledIsSet {
            get => _TE_Addr_0_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_0_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_0_ScanEnabled;
        public Enabled TE_Addr_0_ScanEnabled {
            get => _TE_Addr_0_ScanEnabled;
            set => _ = Set(ref _TE_Addr_0_ScanEnabled, value);
        }
        
        private bool _TE_Addr_0_DetectedIsSet;
        public bool TE_Addr_0_DetectedIsSet {
            get => _TE_Addr_0_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_0_DetectedIsSet, value); 
        }
        private byte _TE_Addr_0_Detected;
        public byte TE_Addr_0_Detected {
            get => _TE_Addr_0_Detected;
            set => _ = Set(ref _TE_Addr_0_Detected, value);
        }
        
        private bool _TE_Addr_0_TypeIsSet;
        public bool TE_Addr_0_TypeIsSet {
            get => _TE_Addr_0_TypeIsSet;
            set => _ = Set(ref _TE_Addr_0_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_0_Type;
        public TE_Types TE_Addr_0_Type {
            get => _TE_Addr_0_Type;
            set => _ = Set(ref _TE_Addr_0_Type, value);
        }
        
        private bool _TE_Addr_0_SEL_CAN0IsSet;
        public bool TE_Addr_0_SEL_CAN0IsSet {
            get => _TE_Addr_0_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_0_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_0_SEL_CAN0;
        public Enabled TE_Addr_0_SEL_CAN0 {
            get => _TE_Addr_0_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_0_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_0_SEL_CAN1IsSet;
        public bool TE_Addr_0_SEL_CAN1IsSet {
            get => _TE_Addr_0_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_0_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_0_SEL_CAN1;
        public Enabled TE_Addr_0_SEL_CAN1 {
            get => _TE_Addr_0_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_0_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_0_SEL_RS485IsSet;
        public bool TE_Addr_0_SEL_RS485IsSet {
            get => _TE_Addr_0_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_0_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_0_SEL_RS485;
        public Enabled TE_Addr_0_SEL_RS485 {
            get => _TE_Addr_0_SEL_RS485;
            set => _ = Set(ref _TE_Addr_0_SEL_RS485, value);
        }
        
        private bool _TE_Addr_0_SEL_I2CIsSet;
        public bool TE_Addr_0_SEL_I2CIsSet {
            get => _TE_Addr_0_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_0_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_0_SEL_I2C;
        public Enabled TE_Addr_0_SEL_I2C {
            get => _TE_Addr_0_SEL_I2C;
            set => _ = Set(ref _TE_Addr_0_SEL_I2C, value);
        }
        
        private bool _TE_Addr_0_SEL_RS422IsSet;
        public bool TE_Addr_0_SEL_RS422IsSet {
            get => _TE_Addr_0_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_0_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_0_SEL_RS422;
        public Enabled TE_Addr_0_SEL_RS422 {
            get => _TE_Addr_0_SEL_RS422;
            set => _ = Set(ref _TE_Addr_0_SEL_RS422, value);
        }
        
        private bool _TE_Addr_0_SEL_SPIIsSet;
        public bool TE_Addr_0_SEL_SPIIsSet {
            get => _TE_Addr_0_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_0_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_0_SEL_SPI;
        public Enabled TE_Addr_0_SEL_SPI {
            get => _TE_Addr_0_SEL_SPI;
            set => _ = Set(ref _TE_Addr_0_SEL_SPI, value);
        }
        
        private bool _TE_Addr_0_SEL_UARTIsSet;
        public bool TE_Addr_0_SEL_UARTIsSet {
            get => _TE_Addr_0_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_0_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_0_SEL_UART;
        public Enabled TE_Addr_0_SEL_UART {
            get => _TE_Addr_0_SEL_UART;
            set => _ = Set(ref _TE_Addr_0_SEL_UART, value);
        }
        
        private bool _TE_Addr_0_PowerIsSet;
        public bool TE_Addr_0_PowerIsSet {
            get => _TE_Addr_0_PowerIsSet;
            set => _ = Set(ref _TE_Addr_0_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_0_Power;
        public Enabled TE_Addr_0_Power {
            get => _TE_Addr_0_Power;
            set => _ = Set(ref _TE_Addr_0_Power, value);
        }
        
        private bool _TE_Addr_0_EnableIsSet;
        public bool TE_Addr_0_EnableIsSet {
            get => _TE_Addr_0_EnableIsSet;
            set => _ = Set(ref _TE_Addr_0_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_0_Enable;
        public Enabled TE_Addr_0_Enable {
            get => _TE_Addr_0_Enable;
            set => _ = Set(ref _TE_Addr_0_Enable, value);
        }
        
        private bool _TE_Addr_0_nResetIsSet;
        public bool TE_Addr_0_nResetIsSet {
            get => _TE_Addr_0_nResetIsSet;
            set => _ = Set(ref _TE_Addr_0_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_0_nReset;
        public Enabled TE_Addr_0_nReset {
            get => _TE_Addr_0_nReset;
            set => _ = Set(ref _TE_Addr_0_nReset, value);
        }
        
        private bool _TE_Addr_0_COMM_TRIsSet;
        public bool TE_Addr_0_COMM_TRIsSet {
            get => _TE_Addr_0_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_0_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_0_COMM_TR;
        public Enabled TE_Addr_0_COMM_TR {
            get => _TE_Addr_0_COMM_TR;
            set => _ = Set(ref _TE_Addr_0_COMM_TR, value);
        }
        
        /*************** Properties for TE_Addr_0_Set register ***********************************/
        private bool _TE_Addr_0_Set_ScanEnabledIsSet;
        public bool TE_Addr_0_Set_ScanEnabledIsSet {
            get => _TE_Addr_0_Set_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_0_Set_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_ScanEnabled;
        public Enabled TE_Addr_0_Set_ScanEnabled {
            get => _TE_Addr_0_Set_ScanEnabled;
            set => _ = Set(ref _TE_Addr_0_Set_ScanEnabled, value);
        }
        
        private bool _TE_Addr_0_Set_DetectedIsSet;
        public bool TE_Addr_0_Set_DetectedIsSet {
            get => _TE_Addr_0_Set_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_0_Set_DetectedIsSet, value); 
        }
        private byte _TE_Addr_0_Set_Detected;
        public byte TE_Addr_0_Set_Detected {
            get => _TE_Addr_0_Set_Detected;
            set => _ = Set(ref _TE_Addr_0_Set_Detected, value);
        }
        
        private bool _TE_Addr_0_Set_TypeIsSet;
        public bool TE_Addr_0_Set_TypeIsSet {
            get => _TE_Addr_0_Set_TypeIsSet;
            set => _ = Set(ref _TE_Addr_0_Set_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_0_Set_Type;
        public TE_Types TE_Addr_0_Set_Type {
            get => _TE_Addr_0_Set_Type;
            set => _ = Set(ref _TE_Addr_0_Set_Type, value);
        }
        
        private bool _TE_Addr_0_Set_SEL_CAN0IsSet;
        public bool TE_Addr_0_Set_SEL_CAN0IsSet {
            get => _TE_Addr_0_Set_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_SEL_CAN0;
        public Enabled TE_Addr_0_Set_SEL_CAN0 {
            get => _TE_Addr_0_Set_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_0_Set_SEL_CAN1IsSet;
        public bool TE_Addr_0_Set_SEL_CAN1IsSet {
            get => _TE_Addr_0_Set_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_SEL_CAN1;
        public Enabled TE_Addr_0_Set_SEL_CAN1 {
            get => _TE_Addr_0_Set_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_0_Set_SEL_RS485IsSet;
        public bool TE_Addr_0_Set_SEL_RS485IsSet {
            get => _TE_Addr_0_Set_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_SEL_RS485;
        public Enabled TE_Addr_0_Set_SEL_RS485 {
            get => _TE_Addr_0_Set_SEL_RS485;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_RS485, value);
        }
        
        private bool _TE_Addr_0_Set_SEL_I2CIsSet;
        public bool TE_Addr_0_Set_SEL_I2CIsSet {
            get => _TE_Addr_0_Set_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_SEL_I2C;
        public Enabled TE_Addr_0_Set_SEL_I2C {
            get => _TE_Addr_0_Set_SEL_I2C;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_I2C, value);
        }
        
        private bool _TE_Addr_0_Set_SEL_RS422IsSet;
        public bool TE_Addr_0_Set_SEL_RS422IsSet {
            get => _TE_Addr_0_Set_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_SEL_RS422;
        public Enabled TE_Addr_0_Set_SEL_RS422 {
            get => _TE_Addr_0_Set_SEL_RS422;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_RS422, value);
        }
        
        private bool _TE_Addr_0_Set_SEL_SPIIsSet;
        public bool TE_Addr_0_Set_SEL_SPIIsSet {
            get => _TE_Addr_0_Set_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_SEL_SPI;
        public Enabled TE_Addr_0_Set_SEL_SPI {
            get => _TE_Addr_0_Set_SEL_SPI;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_SPI, value);
        }
        
        private bool _TE_Addr_0_Set_SEL_UARTIsSet;
        public bool TE_Addr_0_Set_SEL_UARTIsSet {
            get => _TE_Addr_0_Set_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_SEL_UART;
        public Enabled TE_Addr_0_Set_SEL_UART {
            get => _TE_Addr_0_Set_SEL_UART;
            set => _ = Set(ref _TE_Addr_0_Set_SEL_UART, value);
        }
        
        private bool _TE_Addr_0_Set_PowerIsSet;
        public bool TE_Addr_0_Set_PowerIsSet {
            get => _TE_Addr_0_Set_PowerIsSet;
            set => _ = Set(ref _TE_Addr_0_Set_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_Power;
        public Enabled TE_Addr_0_Set_Power {
            get => _TE_Addr_0_Set_Power;
            set => _ = Set(ref _TE_Addr_0_Set_Power, value);
        }
        
        private bool _TE_Addr_0_Set_EnableIsSet;
        public bool TE_Addr_0_Set_EnableIsSet {
            get => _TE_Addr_0_Set_EnableIsSet;
            set => _ = Set(ref _TE_Addr_0_Set_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_Enable;
        public Enabled TE_Addr_0_Set_Enable {
            get => _TE_Addr_0_Set_Enable;
            set => _ = Set(ref _TE_Addr_0_Set_Enable, value);
        }
        
        private bool _TE_Addr_0_Set_nResetIsSet;
        public bool TE_Addr_0_Set_nResetIsSet {
            get => _TE_Addr_0_Set_nResetIsSet;
            set => _ = Set(ref _TE_Addr_0_Set_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_nReset;
        public Enabled TE_Addr_0_Set_nReset {
            get => _TE_Addr_0_Set_nReset;
            set => _ = Set(ref _TE_Addr_0_Set_nReset, value);
        }
        
        private bool _TE_Addr_0_Set_COMM_TRIsSet;
        public bool TE_Addr_0_Set_COMM_TRIsSet {
            get => _TE_Addr_0_Set_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_0_Set_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_0_Set_COMM_TR;
        public Enabled TE_Addr_0_Set_COMM_TR {
            get => _TE_Addr_0_Set_COMM_TR;
            set => _ = Set(ref _TE_Addr_0_Set_COMM_TR, value);
        }
        
        /*************** Properties for TE_Addr_0_Clear register *********************************/
        private bool _TE_Addr_0_Clear_ScanEnabledIsSet;
        public bool TE_Addr_0_Clear_ScanEnabledIsSet {
            get => _TE_Addr_0_Clear_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_ScanEnabled;
        public Enabled TE_Addr_0_Clear_ScanEnabled {
            get => _TE_Addr_0_Clear_ScanEnabled;
            set => _ = Set(ref _TE_Addr_0_Clear_ScanEnabled, value);
        }
        
        private bool _TE_Addr_0_Clear_DetectedIsSet;
        public bool TE_Addr_0_Clear_DetectedIsSet {
            get => _TE_Addr_0_Clear_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_DetectedIsSet, value); 
        }
        private byte _TE_Addr_0_Clear_Detected;
        public byte TE_Addr_0_Clear_Detected {
            get => _TE_Addr_0_Clear_Detected;
            set => _ = Set(ref _TE_Addr_0_Clear_Detected, value);
        }
        
        private bool _TE_Addr_0_Clear_TypeIsSet;
        public bool TE_Addr_0_Clear_TypeIsSet {
            get => _TE_Addr_0_Clear_TypeIsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_0_Clear_Type;
        public TE_Types TE_Addr_0_Clear_Type {
            get => _TE_Addr_0_Clear_Type;
            set => _ = Set(ref _TE_Addr_0_Clear_Type, value);
        }
        
        private bool _TE_Addr_0_Clear_SEL_CAN0IsSet;
        public bool TE_Addr_0_Clear_SEL_CAN0IsSet {
            get => _TE_Addr_0_Clear_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_SEL_CAN0;
        public Enabled TE_Addr_0_Clear_SEL_CAN0 {
            get => _TE_Addr_0_Clear_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_0_Clear_SEL_CAN1IsSet;
        public bool TE_Addr_0_Clear_SEL_CAN1IsSet {
            get => _TE_Addr_0_Clear_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_SEL_CAN1;
        public Enabled TE_Addr_0_Clear_SEL_CAN1 {
            get => _TE_Addr_0_Clear_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_0_Clear_SEL_RS485IsSet;
        public bool TE_Addr_0_Clear_SEL_RS485IsSet {
            get => _TE_Addr_0_Clear_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_SEL_RS485;
        public Enabled TE_Addr_0_Clear_SEL_RS485 {
            get => _TE_Addr_0_Clear_SEL_RS485;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_RS485, value);
        }
        
        private bool _TE_Addr_0_Clear_SEL_I2CIsSet;
        public bool TE_Addr_0_Clear_SEL_I2CIsSet {
            get => _TE_Addr_0_Clear_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_SEL_I2C;
        public Enabled TE_Addr_0_Clear_SEL_I2C {
            get => _TE_Addr_0_Clear_SEL_I2C;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_I2C, value);
        }
        
        private bool _TE_Addr_0_Clear_SEL_RS422IsSet;
        public bool TE_Addr_0_Clear_SEL_RS422IsSet {
            get => _TE_Addr_0_Clear_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_SEL_RS422;
        public Enabled TE_Addr_0_Clear_SEL_RS422 {
            get => _TE_Addr_0_Clear_SEL_RS422;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_RS422, value);
        }
        
        private bool _TE_Addr_0_Clear_SEL_SPIIsSet;
        public bool TE_Addr_0_Clear_SEL_SPIIsSet {
            get => _TE_Addr_0_Clear_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_SEL_SPI;
        public Enabled TE_Addr_0_Clear_SEL_SPI {
            get => _TE_Addr_0_Clear_SEL_SPI;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_SPI, value);
        }
        
        private bool _TE_Addr_0_Clear_SEL_UARTIsSet;
        public bool TE_Addr_0_Clear_SEL_UARTIsSet {
            get => _TE_Addr_0_Clear_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_SEL_UART;
        public Enabled TE_Addr_0_Clear_SEL_UART {
            get => _TE_Addr_0_Clear_SEL_UART;
            set => _ = Set(ref _TE_Addr_0_Clear_SEL_UART, value);
        }
        
        private bool _TE_Addr_0_Clear_PowerIsSet;
        public bool TE_Addr_0_Clear_PowerIsSet {
            get => _TE_Addr_0_Clear_PowerIsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_Power;
        public Enabled TE_Addr_0_Clear_Power {
            get => _TE_Addr_0_Clear_Power;
            set => _ = Set(ref _TE_Addr_0_Clear_Power, value);
        }
        
        private bool _TE_Addr_0_Clear_EnableIsSet;
        public bool TE_Addr_0_Clear_EnableIsSet {
            get => _TE_Addr_0_Clear_EnableIsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_Enable;
        public Enabled TE_Addr_0_Clear_Enable {
            get => _TE_Addr_0_Clear_Enable;
            set => _ = Set(ref _TE_Addr_0_Clear_Enable, value);
        }
        
        private bool _TE_Addr_0_Clear_nResetIsSet;
        public bool TE_Addr_0_Clear_nResetIsSet {
            get => _TE_Addr_0_Clear_nResetIsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_nReset;
        public Enabled TE_Addr_0_Clear_nReset {
            get => _TE_Addr_0_Clear_nReset;
            set => _ = Set(ref _TE_Addr_0_Clear_nReset, value);
        }
        
        private bool _TE_Addr_0_Clear_COMM_TRIsSet;
        public bool TE_Addr_0_Clear_COMM_TRIsSet {
            get => _TE_Addr_0_Clear_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_0_Clear_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_0_Clear_COMM_TR;
        public Enabled TE_Addr_0_Clear_COMM_TR {
            get => _TE_Addr_0_Clear_COMM_TR;
            set => _ = Set(ref _TE_Addr_0_Clear_COMM_TR, value);
        }
        
        /*************** Properties for TE_Addr_1 register ***************************************/
        private bool _TE_Addr_1_ScanEnabledIsSet;
        public bool TE_Addr_1_ScanEnabledIsSet {
            get => _TE_Addr_1_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_1_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_1_ScanEnabled;
        public Enabled TE_Addr_1_ScanEnabled {
            get => _TE_Addr_1_ScanEnabled;
            set => _ = Set(ref _TE_Addr_1_ScanEnabled, value);
        }
        
        private bool _TE_Addr_1_DetectedIsSet;
        public bool TE_Addr_1_DetectedIsSet {
            get => _TE_Addr_1_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_1_DetectedIsSet, value); 
        }
        private byte _TE_Addr_1_Detected;
        public byte TE_Addr_1_Detected {
            get => _TE_Addr_1_Detected;
            set => _ = Set(ref _TE_Addr_1_Detected, value);
        }
        
        private bool _TE_Addr_1_TypeIsSet;
        public bool TE_Addr_1_TypeIsSet {
            get => _TE_Addr_1_TypeIsSet;
            set => _ = Set(ref _TE_Addr_1_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_1_Type;
        public TE_Types TE_Addr_1_Type {
            get => _TE_Addr_1_Type;
            set => _ = Set(ref _TE_Addr_1_Type, value);
        }
        
        private bool _TE_Addr_1_SEL_CAN0IsSet;
        public bool TE_Addr_1_SEL_CAN0IsSet {
            get => _TE_Addr_1_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_1_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_1_SEL_CAN0;
        public Enabled TE_Addr_1_SEL_CAN0 {
            get => _TE_Addr_1_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_1_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_1_SEL_CAN1IsSet;
        public bool TE_Addr_1_SEL_CAN1IsSet {
            get => _TE_Addr_1_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_1_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_1_SEL_CAN1;
        public Enabled TE_Addr_1_SEL_CAN1 {
            get => _TE_Addr_1_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_1_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_1_SEL_RS485IsSet;
        public bool TE_Addr_1_SEL_RS485IsSet {
            get => _TE_Addr_1_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_1_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_1_SEL_RS485;
        public Enabled TE_Addr_1_SEL_RS485 {
            get => _TE_Addr_1_SEL_RS485;
            set => _ = Set(ref _TE_Addr_1_SEL_RS485, value);
        }
        
        private bool _TE_Addr_1_SEL_I2CIsSet;
        public bool TE_Addr_1_SEL_I2CIsSet {
            get => _TE_Addr_1_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_1_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_1_SEL_I2C;
        public Enabled TE_Addr_1_SEL_I2C {
            get => _TE_Addr_1_SEL_I2C;
            set => _ = Set(ref _TE_Addr_1_SEL_I2C, value);
        }
        
        private bool _TE_Addr_1_SEL_RS422IsSet;
        public bool TE_Addr_1_SEL_RS422IsSet {
            get => _TE_Addr_1_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_1_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_1_SEL_RS422;
        public Enabled TE_Addr_1_SEL_RS422 {
            get => _TE_Addr_1_SEL_RS422;
            set => _ = Set(ref _TE_Addr_1_SEL_RS422, value);
        }
        
        private bool _TE_Addr_1_SEL_SPIIsSet;
        public bool TE_Addr_1_SEL_SPIIsSet {
            get => _TE_Addr_1_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_1_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_1_SEL_SPI;
        public Enabled TE_Addr_1_SEL_SPI {
            get => _TE_Addr_1_SEL_SPI;
            set => _ = Set(ref _TE_Addr_1_SEL_SPI, value);
        }
        
        private bool _TE_Addr_1_SEL_UARTIsSet;
        public bool TE_Addr_1_SEL_UARTIsSet {
            get => _TE_Addr_1_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_1_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_1_SEL_UART;
        public Enabled TE_Addr_1_SEL_UART {
            get => _TE_Addr_1_SEL_UART;
            set => _ = Set(ref _TE_Addr_1_SEL_UART, value);
        }
        
        private bool _TE_Addr_1_PowerIsSet;
        public bool TE_Addr_1_PowerIsSet {
            get => _TE_Addr_1_PowerIsSet;
            set => _ = Set(ref _TE_Addr_1_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_1_Power;
        public Enabled TE_Addr_1_Power {
            get => _TE_Addr_1_Power;
            set => _ = Set(ref _TE_Addr_1_Power, value);
        }
        
        private bool _TE_Addr_1_EnableIsSet;
        public bool TE_Addr_1_EnableIsSet {
            get => _TE_Addr_1_EnableIsSet;
            set => _ = Set(ref _TE_Addr_1_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_1_Enable;
        public Enabled TE_Addr_1_Enable {
            get => _TE_Addr_1_Enable;
            set => _ = Set(ref _TE_Addr_1_Enable, value);
        }
        
        private bool _TE_Addr_1_nResetIsSet;
        public bool TE_Addr_1_nResetIsSet {
            get => _TE_Addr_1_nResetIsSet;
            set => _ = Set(ref _TE_Addr_1_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_1_nReset;
        public Enabled TE_Addr_1_nReset {
            get => _TE_Addr_1_nReset;
            set => _ = Set(ref _TE_Addr_1_nReset, value);
        }
        
        private bool _TE_Addr_1_COMM_TRIsSet;
        public bool TE_Addr_1_COMM_TRIsSet {
            get => _TE_Addr_1_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_1_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_1_COMM_TR;
        public Enabled TE_Addr_1_COMM_TR {
            get => _TE_Addr_1_COMM_TR;
            set => _ = Set(ref _TE_Addr_1_COMM_TR, value);
        }
        
        /*************** Properties for TE_Addr_1_Set register ***********************************/
        private bool _TE_Addr_1_Set_ScanEnabledIsSet;
        public bool TE_Addr_1_Set_ScanEnabledIsSet {
            get => _TE_Addr_1_Set_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_1_Set_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_ScanEnabled;
        public Enabled TE_Addr_1_Set_ScanEnabled {
            get => _TE_Addr_1_Set_ScanEnabled;
            set => _ = Set(ref _TE_Addr_1_Set_ScanEnabled, value);
        }
        
        private bool _TE_Addr_1_Set_DetectedIsSet;
        public bool TE_Addr_1_Set_DetectedIsSet {
            get => _TE_Addr_1_Set_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_1_Set_DetectedIsSet, value); 
        }
        private byte _TE_Addr_1_Set_Detected;
        public byte TE_Addr_1_Set_Detected {
            get => _TE_Addr_1_Set_Detected;
            set => _ = Set(ref _TE_Addr_1_Set_Detected, value);
        }
        
        private bool _TE_Addr_1_Set_TypeIsSet;
        public bool TE_Addr_1_Set_TypeIsSet {
            get => _TE_Addr_1_Set_TypeIsSet;
            set => _ = Set(ref _TE_Addr_1_Set_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_1_Set_Type;
        public TE_Types TE_Addr_1_Set_Type {
            get => _TE_Addr_1_Set_Type;
            set => _ = Set(ref _TE_Addr_1_Set_Type, value);
        }
        
        private bool _TE_Addr_1_Set_SEL_CAN0IsSet;
        public bool TE_Addr_1_Set_SEL_CAN0IsSet {
            get => _TE_Addr_1_Set_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_SEL_CAN0;
        public Enabled TE_Addr_1_Set_SEL_CAN0 {
            get => _TE_Addr_1_Set_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_1_Set_SEL_CAN1IsSet;
        public bool TE_Addr_1_Set_SEL_CAN1IsSet {
            get => _TE_Addr_1_Set_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_SEL_CAN1;
        public Enabled TE_Addr_1_Set_SEL_CAN1 {
            get => _TE_Addr_1_Set_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_1_Set_SEL_RS485IsSet;
        public bool TE_Addr_1_Set_SEL_RS485IsSet {
            get => _TE_Addr_1_Set_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_SEL_RS485;
        public Enabled TE_Addr_1_Set_SEL_RS485 {
            get => _TE_Addr_1_Set_SEL_RS485;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_RS485, value);
        }
        
        private bool _TE_Addr_1_Set_SEL_I2CIsSet;
        public bool TE_Addr_1_Set_SEL_I2CIsSet {
            get => _TE_Addr_1_Set_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_SEL_I2C;
        public Enabled TE_Addr_1_Set_SEL_I2C {
            get => _TE_Addr_1_Set_SEL_I2C;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_I2C, value);
        }
        
        private bool _TE_Addr_1_Set_SEL_RS422IsSet;
        public bool TE_Addr_1_Set_SEL_RS422IsSet {
            get => _TE_Addr_1_Set_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_SEL_RS422;
        public Enabled TE_Addr_1_Set_SEL_RS422 {
            get => _TE_Addr_1_Set_SEL_RS422;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_RS422, value);
        }
        
        private bool _TE_Addr_1_Set_SEL_SPIIsSet;
        public bool TE_Addr_1_Set_SEL_SPIIsSet {
            get => _TE_Addr_1_Set_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_SEL_SPI;
        public Enabled TE_Addr_1_Set_SEL_SPI {
            get => _TE_Addr_1_Set_SEL_SPI;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_SPI, value);
        }
        
        private bool _TE_Addr_1_Set_SEL_UARTIsSet;
        public bool TE_Addr_1_Set_SEL_UARTIsSet {
            get => _TE_Addr_1_Set_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_SEL_UART;
        public Enabled TE_Addr_1_Set_SEL_UART {
            get => _TE_Addr_1_Set_SEL_UART;
            set => _ = Set(ref _TE_Addr_1_Set_SEL_UART, value);
        }
        
        private bool _TE_Addr_1_Set_PowerIsSet;
        public bool TE_Addr_1_Set_PowerIsSet {
            get => _TE_Addr_1_Set_PowerIsSet;
            set => _ = Set(ref _TE_Addr_1_Set_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_Power;
        public Enabled TE_Addr_1_Set_Power {
            get => _TE_Addr_1_Set_Power;
            set => _ = Set(ref _TE_Addr_1_Set_Power, value);
        }
        
        private bool _TE_Addr_1_Set_EnableIsSet;
        public bool TE_Addr_1_Set_EnableIsSet {
            get => _TE_Addr_1_Set_EnableIsSet;
            set => _ = Set(ref _TE_Addr_1_Set_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_Enable;
        public Enabled TE_Addr_1_Set_Enable {
            get => _TE_Addr_1_Set_Enable;
            set => _ = Set(ref _TE_Addr_1_Set_Enable, value);
        }
        
        private bool _TE_Addr_1_Set_nResetIsSet;
        public bool TE_Addr_1_Set_nResetIsSet {
            get => _TE_Addr_1_Set_nResetIsSet;
            set => _ = Set(ref _TE_Addr_1_Set_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_nReset;
        public Enabled TE_Addr_1_Set_nReset {
            get => _TE_Addr_1_Set_nReset;
            set => _ = Set(ref _TE_Addr_1_Set_nReset, value);
        }
        
        private bool _TE_Addr_1_Set_COMM_TRIsSet;
        public bool TE_Addr_1_Set_COMM_TRIsSet {
            get => _TE_Addr_1_Set_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_1_Set_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_1_Set_COMM_TR;
        public Enabled TE_Addr_1_Set_COMM_TR {
            get => _TE_Addr_1_Set_COMM_TR;
            set => _ = Set(ref _TE_Addr_1_Set_COMM_TR, value);
        }
        
        /*************** Properties for TE_Addr_1_Clear register *********************************/
        private bool _TE_Addr_1_Clear_ScanEnabledIsSet;
        public bool TE_Addr_1_Clear_ScanEnabledIsSet {
            get => _TE_Addr_1_Clear_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_ScanEnabled;
        public Enabled TE_Addr_1_Clear_ScanEnabled {
            get => _TE_Addr_1_Clear_ScanEnabled;
            set => _ = Set(ref _TE_Addr_1_Clear_ScanEnabled, value);
        }
        
        private bool _TE_Addr_1_Clear_DetectedIsSet;
        public bool TE_Addr_1_Clear_DetectedIsSet {
            get => _TE_Addr_1_Clear_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_DetectedIsSet, value); 
        }
        private byte _TE_Addr_1_Clear_Detected;
        public byte TE_Addr_1_Clear_Detected {
            get => _TE_Addr_1_Clear_Detected;
            set => _ = Set(ref _TE_Addr_1_Clear_Detected, value);
        }
        
        private bool _TE_Addr_1_Clear_TypeIsSet;
        public bool TE_Addr_1_Clear_TypeIsSet {
            get => _TE_Addr_1_Clear_TypeIsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_1_Clear_Type;
        public TE_Types TE_Addr_1_Clear_Type {
            get => _TE_Addr_1_Clear_Type;
            set => _ = Set(ref _TE_Addr_1_Clear_Type, value);
        }
        
        private bool _TE_Addr_1_Clear_SEL_CAN0IsSet;
        public bool TE_Addr_1_Clear_SEL_CAN0IsSet {
            get => _TE_Addr_1_Clear_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_SEL_CAN0;
        public Enabled TE_Addr_1_Clear_SEL_CAN0 {
            get => _TE_Addr_1_Clear_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_1_Clear_SEL_CAN1IsSet;
        public bool TE_Addr_1_Clear_SEL_CAN1IsSet {
            get => _TE_Addr_1_Clear_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_SEL_CAN1;
        public Enabled TE_Addr_1_Clear_SEL_CAN1 {
            get => _TE_Addr_1_Clear_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_1_Clear_SEL_RS485IsSet;
        public bool TE_Addr_1_Clear_SEL_RS485IsSet {
            get => _TE_Addr_1_Clear_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_SEL_RS485;
        public Enabled TE_Addr_1_Clear_SEL_RS485 {
            get => _TE_Addr_1_Clear_SEL_RS485;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_RS485, value);
        }
        
        private bool _TE_Addr_1_Clear_SEL_I2CIsSet;
        public bool TE_Addr_1_Clear_SEL_I2CIsSet {
            get => _TE_Addr_1_Clear_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_SEL_I2C;
        public Enabled TE_Addr_1_Clear_SEL_I2C {
            get => _TE_Addr_1_Clear_SEL_I2C;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_I2C, value);
        }
        
        private bool _TE_Addr_1_Clear_SEL_RS422IsSet;
        public bool TE_Addr_1_Clear_SEL_RS422IsSet {
            get => _TE_Addr_1_Clear_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_SEL_RS422;
        public Enabled TE_Addr_1_Clear_SEL_RS422 {
            get => _TE_Addr_1_Clear_SEL_RS422;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_RS422, value);
        }
        
        private bool _TE_Addr_1_Clear_SEL_SPIIsSet;
        public bool TE_Addr_1_Clear_SEL_SPIIsSet {
            get => _TE_Addr_1_Clear_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_SEL_SPI;
        public Enabled TE_Addr_1_Clear_SEL_SPI {
            get => _TE_Addr_1_Clear_SEL_SPI;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_SPI, value);
        }
        
        private bool _TE_Addr_1_Clear_SEL_UARTIsSet;
        public bool TE_Addr_1_Clear_SEL_UARTIsSet {
            get => _TE_Addr_1_Clear_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_SEL_UART;
        public Enabled TE_Addr_1_Clear_SEL_UART {
            get => _TE_Addr_1_Clear_SEL_UART;
            set => _ = Set(ref _TE_Addr_1_Clear_SEL_UART, value);
        }
        
        private bool _TE_Addr_1_Clear_PowerIsSet;
        public bool TE_Addr_1_Clear_PowerIsSet {
            get => _TE_Addr_1_Clear_PowerIsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_Power;
        public Enabled TE_Addr_1_Clear_Power {
            get => _TE_Addr_1_Clear_Power;
            set => _ = Set(ref _TE_Addr_1_Clear_Power, value);
        }
        
        private bool _TE_Addr_1_Clear_EnableIsSet;
        public bool TE_Addr_1_Clear_EnableIsSet {
            get => _TE_Addr_1_Clear_EnableIsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_Enable;
        public Enabled TE_Addr_1_Clear_Enable {
            get => _TE_Addr_1_Clear_Enable;
            set => _ = Set(ref _TE_Addr_1_Clear_Enable, value);
        }
        
        private bool _TE_Addr_1_Clear_nResetIsSet;
        public bool TE_Addr_1_Clear_nResetIsSet {
            get => _TE_Addr_1_Clear_nResetIsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_nReset;
        public Enabled TE_Addr_1_Clear_nReset {
            get => _TE_Addr_1_Clear_nReset;
            set => _ = Set(ref _TE_Addr_1_Clear_nReset, value);
        }
        
        private bool _TE_Addr_1_Clear_COMM_TRIsSet;
        public bool TE_Addr_1_Clear_COMM_TRIsSet {
            get => _TE_Addr_1_Clear_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_1_Clear_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_1_Clear_COMM_TR;
        public Enabled TE_Addr_1_Clear_COMM_TR {
            get => _TE_Addr_1_Clear_COMM_TR;
            set => _ = Set(ref _TE_Addr_1_Clear_COMM_TR, value);
        }
        
        /*************** Properties for TE_Addr_2 register ***************************************/
        private bool _TE_Addr_2_ScanEnabledIsSet;
        public bool TE_Addr_2_ScanEnabledIsSet {
            get => _TE_Addr_2_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_2_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_2_ScanEnabled;
        public Enabled TE_Addr_2_ScanEnabled {
            get => _TE_Addr_2_ScanEnabled;
            set => _ = Set(ref _TE_Addr_2_ScanEnabled, value);
        }
        
        private bool _TE_Addr_2_DetectedIsSet;
        public bool TE_Addr_2_DetectedIsSet {
            get => _TE_Addr_2_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_2_DetectedIsSet, value); 
        }
        private byte _TE_Addr_2_Detected;
        public byte TE_Addr_2_Detected {
            get => _TE_Addr_2_Detected;
            set => _ = Set(ref _TE_Addr_2_Detected, value);
        }
        
        private bool _TE_Addr_2_TypeIsSet;
        public bool TE_Addr_2_TypeIsSet {
            get => _TE_Addr_2_TypeIsSet;
            set => _ = Set(ref _TE_Addr_2_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_2_Type;
        public TE_Types TE_Addr_2_Type {
            get => _TE_Addr_2_Type;
            set => _ = Set(ref _TE_Addr_2_Type, value);
        }
        
        private bool _TE_Addr_2_SEL_CAN0IsSet;
        public bool TE_Addr_2_SEL_CAN0IsSet {
            get => _TE_Addr_2_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_2_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_2_SEL_CAN0;
        public Enabled TE_Addr_2_SEL_CAN0 {
            get => _TE_Addr_2_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_2_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_2_SEL_CAN1IsSet;
        public bool TE_Addr_2_SEL_CAN1IsSet {
            get => _TE_Addr_2_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_2_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_2_SEL_CAN1;
        public Enabled TE_Addr_2_SEL_CAN1 {
            get => _TE_Addr_2_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_2_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_2_SEL_RS485IsSet;
        public bool TE_Addr_2_SEL_RS485IsSet {
            get => _TE_Addr_2_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_2_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_2_SEL_RS485;
        public Enabled TE_Addr_2_SEL_RS485 {
            get => _TE_Addr_2_SEL_RS485;
            set => _ = Set(ref _TE_Addr_2_SEL_RS485, value);
        }
        
        private bool _TE_Addr_2_SEL_I2CIsSet;
        public bool TE_Addr_2_SEL_I2CIsSet {
            get => _TE_Addr_2_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_2_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_2_SEL_I2C;
        public Enabled TE_Addr_2_SEL_I2C {
            get => _TE_Addr_2_SEL_I2C;
            set => _ = Set(ref _TE_Addr_2_SEL_I2C, value);
        }
        
        private bool _TE_Addr_2_SEL_RS422IsSet;
        public bool TE_Addr_2_SEL_RS422IsSet {
            get => _TE_Addr_2_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_2_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_2_SEL_RS422;
        public Enabled TE_Addr_2_SEL_RS422 {
            get => _TE_Addr_2_SEL_RS422;
            set => _ = Set(ref _TE_Addr_2_SEL_RS422, value);
        }
        
        private bool _TE_Addr_2_SEL_SPIIsSet;
        public bool TE_Addr_2_SEL_SPIIsSet {
            get => _TE_Addr_2_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_2_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_2_SEL_SPI;
        public Enabled TE_Addr_2_SEL_SPI {
            get => _TE_Addr_2_SEL_SPI;
            set => _ = Set(ref _TE_Addr_2_SEL_SPI, value);
        }
        
        private bool _TE_Addr_2_SEL_UARTIsSet;
        public bool TE_Addr_2_SEL_UARTIsSet {
            get => _TE_Addr_2_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_2_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_2_SEL_UART;
        public Enabled TE_Addr_2_SEL_UART {
            get => _TE_Addr_2_SEL_UART;
            set => _ = Set(ref _TE_Addr_2_SEL_UART, value);
        }
        
        private bool _TE_Addr_2_PowerIsSet;
        public bool TE_Addr_2_PowerIsSet {
            get => _TE_Addr_2_PowerIsSet;
            set => _ = Set(ref _TE_Addr_2_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_2_Power;
        public Enabled TE_Addr_2_Power {
            get => _TE_Addr_2_Power;
            set => _ = Set(ref _TE_Addr_2_Power, value);
        }
        
        private bool _TE_Addr_2_EnableIsSet;
        public bool TE_Addr_2_EnableIsSet {
            get => _TE_Addr_2_EnableIsSet;
            set => _ = Set(ref _TE_Addr_2_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_2_Enable;
        public Enabled TE_Addr_2_Enable {
            get => _TE_Addr_2_Enable;
            set => _ = Set(ref _TE_Addr_2_Enable, value);
        }
        
        private bool _TE_Addr_2_nResetIsSet;
        public bool TE_Addr_2_nResetIsSet {
            get => _TE_Addr_2_nResetIsSet;
            set => _ = Set(ref _TE_Addr_2_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_2_nReset;
        public Enabled TE_Addr_2_nReset {
            get => _TE_Addr_2_nReset;
            set => _ = Set(ref _TE_Addr_2_nReset, value);
        }
        
        private bool _TE_Addr_2_COMM_TRIsSet;
        public bool TE_Addr_2_COMM_TRIsSet {
            get => _TE_Addr_2_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_2_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_2_COMM_TR;
        public Enabled TE_Addr_2_COMM_TR {
            get => _TE_Addr_2_COMM_TR;
            set => _ = Set(ref _TE_Addr_2_COMM_TR, value);
        }
        
        /*************** Properties for TE_Addr_2_Set register ***********************************/
        private bool _TE_Addr_2_Set_ScanEnabledIsSet;
        public bool TE_Addr_2_Set_ScanEnabledIsSet {
            get => _TE_Addr_2_Set_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_2_Set_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_ScanEnabled;
        public Enabled TE_Addr_2_Set_ScanEnabled {
            get => _TE_Addr_2_Set_ScanEnabled;
            set => _ = Set(ref _TE_Addr_2_Set_ScanEnabled, value);
        }
        
        private bool _TE_Addr_2_Set_DetectedIsSet;
        public bool TE_Addr_2_Set_DetectedIsSet {
            get => _TE_Addr_2_Set_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_2_Set_DetectedIsSet, value); 
        }
        private byte _TE_Addr_2_Set_Detected;
        public byte TE_Addr_2_Set_Detected {
            get => _TE_Addr_2_Set_Detected;
            set => _ = Set(ref _TE_Addr_2_Set_Detected, value);
        }
        
        private bool _TE_Addr_2_Set_TypeIsSet;
        public bool TE_Addr_2_Set_TypeIsSet {
            get => _TE_Addr_2_Set_TypeIsSet;
            set => _ = Set(ref _TE_Addr_2_Set_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_2_Set_Type;
        public TE_Types TE_Addr_2_Set_Type {
            get => _TE_Addr_2_Set_Type;
            set => _ = Set(ref _TE_Addr_2_Set_Type, value);
        }
        
        private bool _TE_Addr_2_Set_SEL_CAN0IsSet;
        public bool TE_Addr_2_Set_SEL_CAN0IsSet {
            get => _TE_Addr_2_Set_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_SEL_CAN0;
        public Enabled TE_Addr_2_Set_SEL_CAN0 {
            get => _TE_Addr_2_Set_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_2_Set_SEL_CAN1IsSet;
        public bool TE_Addr_2_Set_SEL_CAN1IsSet {
            get => _TE_Addr_2_Set_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_SEL_CAN1;
        public Enabled TE_Addr_2_Set_SEL_CAN1 {
            get => _TE_Addr_2_Set_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_2_Set_SEL_RS485IsSet;
        public bool TE_Addr_2_Set_SEL_RS485IsSet {
            get => _TE_Addr_2_Set_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_SEL_RS485;
        public Enabled TE_Addr_2_Set_SEL_RS485 {
            get => _TE_Addr_2_Set_SEL_RS485;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_RS485, value);
        }
        
        private bool _TE_Addr_2_Set_SEL_I2CIsSet;
        public bool TE_Addr_2_Set_SEL_I2CIsSet {
            get => _TE_Addr_2_Set_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_SEL_I2C;
        public Enabled TE_Addr_2_Set_SEL_I2C {
            get => _TE_Addr_2_Set_SEL_I2C;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_I2C, value);
        }
        
        private bool _TE_Addr_2_Set_SEL_RS422IsSet;
        public bool TE_Addr_2_Set_SEL_RS422IsSet {
            get => _TE_Addr_2_Set_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_SEL_RS422;
        public Enabled TE_Addr_2_Set_SEL_RS422 {
            get => _TE_Addr_2_Set_SEL_RS422;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_RS422, value);
        }
        
        private bool _TE_Addr_2_Set_SEL_SPIIsSet;
        public bool TE_Addr_2_Set_SEL_SPIIsSet {
            get => _TE_Addr_2_Set_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_SEL_SPI;
        public Enabled TE_Addr_2_Set_SEL_SPI {
            get => _TE_Addr_2_Set_SEL_SPI;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_SPI, value);
        }
        
        private bool _TE_Addr_2_Set_SEL_UARTIsSet;
        public bool TE_Addr_2_Set_SEL_UARTIsSet {
            get => _TE_Addr_2_Set_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_SEL_UART;
        public Enabled TE_Addr_2_Set_SEL_UART {
            get => _TE_Addr_2_Set_SEL_UART;
            set => _ = Set(ref _TE_Addr_2_Set_SEL_UART, value);
        }
        
        private bool _TE_Addr_2_Set_PowerIsSet;
        public bool TE_Addr_2_Set_PowerIsSet {
            get => _TE_Addr_2_Set_PowerIsSet;
            set => _ = Set(ref _TE_Addr_2_Set_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_Power;
        public Enabled TE_Addr_2_Set_Power {
            get => _TE_Addr_2_Set_Power;
            set => _ = Set(ref _TE_Addr_2_Set_Power, value);
        }
        
        private bool _TE_Addr_2_Set_EnableIsSet;
        public bool TE_Addr_2_Set_EnableIsSet {
            get => _TE_Addr_2_Set_EnableIsSet;
            set => _ = Set(ref _TE_Addr_2_Set_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_Enable;
        public Enabled TE_Addr_2_Set_Enable {
            get => _TE_Addr_2_Set_Enable;
            set => _ = Set(ref _TE_Addr_2_Set_Enable, value);
        }
        
        private bool _TE_Addr_2_Set_nResetIsSet;
        public bool TE_Addr_2_Set_nResetIsSet {
            get => _TE_Addr_2_Set_nResetIsSet;
            set => _ = Set(ref _TE_Addr_2_Set_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_nReset;
        public Enabled TE_Addr_2_Set_nReset {
            get => _TE_Addr_2_Set_nReset;
            set => _ = Set(ref _TE_Addr_2_Set_nReset, value);
        }
        
        private bool _TE_Addr_2_Set_COMM_TRIsSet;
        public bool TE_Addr_2_Set_COMM_TRIsSet {
            get => _TE_Addr_2_Set_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_2_Set_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_2_Set_COMM_TR;
        public Enabled TE_Addr_2_Set_COMM_TR {
            get => _TE_Addr_2_Set_COMM_TR;
            set => _ = Set(ref _TE_Addr_2_Set_COMM_TR, value);
        }
        
        /*************** Properties for TE_Addr_2_Clear register *********************************/
        private bool _TE_Addr_2_Clear_ScanEnabledIsSet;
        public bool TE_Addr_2_Clear_ScanEnabledIsSet {
            get => _TE_Addr_2_Clear_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_ScanEnabled;
        public Enabled TE_Addr_2_Clear_ScanEnabled {
            get => _TE_Addr_2_Clear_ScanEnabled;
            set => _ = Set(ref _TE_Addr_2_Clear_ScanEnabled, value);
        }
        
        private bool _TE_Addr_2_Clear_DetectedIsSet;
        public bool TE_Addr_2_Clear_DetectedIsSet {
            get => _TE_Addr_2_Clear_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_DetectedIsSet, value); 
        }
        private byte _TE_Addr_2_Clear_Detected;
        public byte TE_Addr_2_Clear_Detected {
            get => _TE_Addr_2_Clear_Detected;
            set => _ = Set(ref _TE_Addr_2_Clear_Detected, value);
        }
        
        private bool _TE_Addr_2_Clear_TypeIsSet;
        public bool TE_Addr_2_Clear_TypeIsSet {
            get => _TE_Addr_2_Clear_TypeIsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_2_Clear_Type;
        public TE_Types TE_Addr_2_Clear_Type {
            get => _TE_Addr_2_Clear_Type;
            set => _ = Set(ref _TE_Addr_2_Clear_Type, value);
        }
        
        private bool _TE_Addr_2_Clear_SEL_CAN0IsSet;
        public bool TE_Addr_2_Clear_SEL_CAN0IsSet {
            get => _TE_Addr_2_Clear_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_SEL_CAN0;
        public Enabled TE_Addr_2_Clear_SEL_CAN0 {
            get => _TE_Addr_2_Clear_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_2_Clear_SEL_CAN1IsSet;
        public bool TE_Addr_2_Clear_SEL_CAN1IsSet {
            get => _TE_Addr_2_Clear_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_SEL_CAN1;
        public Enabled TE_Addr_2_Clear_SEL_CAN1 {
            get => _TE_Addr_2_Clear_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_2_Clear_SEL_RS485IsSet;
        public bool TE_Addr_2_Clear_SEL_RS485IsSet {
            get => _TE_Addr_2_Clear_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_SEL_RS485;
        public Enabled TE_Addr_2_Clear_SEL_RS485 {
            get => _TE_Addr_2_Clear_SEL_RS485;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_RS485, value);
        }
        
        private bool _TE_Addr_2_Clear_SEL_I2CIsSet;
        public bool TE_Addr_2_Clear_SEL_I2CIsSet {
            get => _TE_Addr_2_Clear_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_SEL_I2C;
        public Enabled TE_Addr_2_Clear_SEL_I2C {
            get => _TE_Addr_2_Clear_SEL_I2C;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_I2C, value);
        }
        
        private bool _TE_Addr_2_Clear_SEL_RS422IsSet;
        public bool TE_Addr_2_Clear_SEL_RS422IsSet {
            get => _TE_Addr_2_Clear_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_SEL_RS422;
        public Enabled TE_Addr_2_Clear_SEL_RS422 {
            get => _TE_Addr_2_Clear_SEL_RS422;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_RS422, value);
        }
        
        private bool _TE_Addr_2_Clear_SEL_SPIIsSet;
        public bool TE_Addr_2_Clear_SEL_SPIIsSet {
            get => _TE_Addr_2_Clear_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_SEL_SPI;
        public Enabled TE_Addr_2_Clear_SEL_SPI {
            get => _TE_Addr_2_Clear_SEL_SPI;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_SPI, value);
        }
        
        private bool _TE_Addr_2_Clear_SEL_UARTIsSet;
        public bool TE_Addr_2_Clear_SEL_UARTIsSet {
            get => _TE_Addr_2_Clear_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_SEL_UART;
        public Enabled TE_Addr_2_Clear_SEL_UART {
            get => _TE_Addr_2_Clear_SEL_UART;
            set => _ = Set(ref _TE_Addr_2_Clear_SEL_UART, value);
        }
        
        private bool _TE_Addr_2_Clear_PowerIsSet;
        public bool TE_Addr_2_Clear_PowerIsSet {
            get => _TE_Addr_2_Clear_PowerIsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_Power;
        public Enabled TE_Addr_2_Clear_Power {
            get => _TE_Addr_2_Clear_Power;
            set => _ = Set(ref _TE_Addr_2_Clear_Power, value);
        }
        
        private bool _TE_Addr_2_Clear_EnableIsSet;
        public bool TE_Addr_2_Clear_EnableIsSet {
            get => _TE_Addr_2_Clear_EnableIsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_Enable;
        public Enabled TE_Addr_2_Clear_Enable {
            get => _TE_Addr_2_Clear_Enable;
            set => _ = Set(ref _TE_Addr_2_Clear_Enable, value);
        }
        
        private bool _TE_Addr_2_Clear_nResetIsSet;
        public bool TE_Addr_2_Clear_nResetIsSet {
            get => _TE_Addr_2_Clear_nResetIsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_nReset;
        public Enabled TE_Addr_2_Clear_nReset {
            get => _TE_Addr_2_Clear_nReset;
            set => _ = Set(ref _TE_Addr_2_Clear_nReset, value);
        }
        
        private bool _TE_Addr_2_Clear_COMM_TRIsSet;
        public bool TE_Addr_2_Clear_COMM_TRIsSet {
            get => _TE_Addr_2_Clear_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_2_Clear_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_2_Clear_COMM_TR;
        public Enabled TE_Addr_2_Clear_COMM_TR {
            get => _TE_Addr_2_Clear_COMM_TR;
            set => _ = Set(ref _TE_Addr_2_Clear_COMM_TR, value);
        }
        
        /*************** Properties for TE_Addr_3 register ***************************************/
        private bool _TE_Addr_3_ScanEnabledIsSet;
        public bool TE_Addr_3_ScanEnabledIsSet {
            get => _TE_Addr_3_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_3_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_3_ScanEnabled;
        public Enabled TE_Addr_3_ScanEnabled {
            get => _TE_Addr_3_ScanEnabled;
            set => _ = Set(ref _TE_Addr_3_ScanEnabled, value);
        }
        
        private bool _TE_Addr_3_DetectedIsSet;
        public bool TE_Addr_3_DetectedIsSet {
            get => _TE_Addr_3_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_3_DetectedIsSet, value); 
        }
        private byte _TE_Addr_3_Detected;
        public byte TE_Addr_3_Detected {
            get => _TE_Addr_3_Detected;
            set => _ = Set(ref _TE_Addr_3_Detected, value);
        }
        
        private bool _TE_Addr_3_TypeIsSet;
        public bool TE_Addr_3_TypeIsSet {
            get => _TE_Addr_3_TypeIsSet;
            set => _ = Set(ref _TE_Addr_3_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_3_Type;
        public TE_Types TE_Addr_3_Type {
            get => _TE_Addr_3_Type;
            set => _ = Set(ref _TE_Addr_3_Type, value);
        }
        
        private bool _TE_Addr_3_SEL_CAN0IsSet;
        public bool TE_Addr_3_SEL_CAN0IsSet {
            get => _TE_Addr_3_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_3_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_3_SEL_CAN0;
        public Enabled TE_Addr_3_SEL_CAN0 {
            get => _TE_Addr_3_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_3_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_3_SEL_CAN1IsSet;
        public bool TE_Addr_3_SEL_CAN1IsSet {
            get => _TE_Addr_3_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_3_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_3_SEL_CAN1;
        public Enabled TE_Addr_3_SEL_CAN1 {
            get => _TE_Addr_3_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_3_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_3_SEL_RS485IsSet;
        public bool TE_Addr_3_SEL_RS485IsSet {
            get => _TE_Addr_3_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_3_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_3_SEL_RS485;
        public Enabled TE_Addr_3_SEL_RS485 {
            get => _TE_Addr_3_SEL_RS485;
            set => _ = Set(ref _TE_Addr_3_SEL_RS485, value);
        }
        
        private bool _TE_Addr_3_SEL_I2CIsSet;
        public bool TE_Addr_3_SEL_I2CIsSet {
            get => _TE_Addr_3_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_3_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_3_SEL_I2C;
        public Enabled TE_Addr_3_SEL_I2C {
            get => _TE_Addr_3_SEL_I2C;
            set => _ = Set(ref _TE_Addr_3_SEL_I2C, value);
        }
        
        private bool _TE_Addr_3_SEL_RS422IsSet;
        public bool TE_Addr_3_SEL_RS422IsSet {
            get => _TE_Addr_3_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_3_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_3_SEL_RS422;
        public Enabled TE_Addr_3_SEL_RS422 {
            get => _TE_Addr_3_SEL_RS422;
            set => _ = Set(ref _TE_Addr_3_SEL_RS422, value);
        }
        
        private bool _TE_Addr_3_SEL_SPIIsSet;
        public bool TE_Addr_3_SEL_SPIIsSet {
            get => _TE_Addr_3_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_3_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_3_SEL_SPI;
        public Enabled TE_Addr_3_SEL_SPI {
            get => _TE_Addr_3_SEL_SPI;
            set => _ = Set(ref _TE_Addr_3_SEL_SPI, value);
        }
        
        private bool _TE_Addr_3_SEL_UARTIsSet;
        public bool TE_Addr_3_SEL_UARTIsSet {
            get => _TE_Addr_3_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_3_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_3_SEL_UART;
        public Enabled TE_Addr_3_SEL_UART {
            get => _TE_Addr_3_SEL_UART;
            set => _ = Set(ref _TE_Addr_3_SEL_UART, value);
        }
        
        private bool _TE_Addr_3_PowerIsSet;
        public bool TE_Addr_3_PowerIsSet {
            get => _TE_Addr_3_PowerIsSet;
            set => _ = Set(ref _TE_Addr_3_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_3_Power;
        public Enabled TE_Addr_3_Power {
            get => _TE_Addr_3_Power;
            set => _ = Set(ref _TE_Addr_3_Power, value);
        }
        
        private bool _TE_Addr_3_EnableIsSet;
        public bool TE_Addr_3_EnableIsSet {
            get => _TE_Addr_3_EnableIsSet;
            set => _ = Set(ref _TE_Addr_3_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_3_Enable;
        public Enabled TE_Addr_3_Enable {
            get => _TE_Addr_3_Enable;
            set => _ = Set(ref _TE_Addr_3_Enable, value);
        }
        
        private bool _TE_Addr_3_nResetIsSet;
        public bool TE_Addr_3_nResetIsSet {
            get => _TE_Addr_3_nResetIsSet;
            set => _ = Set(ref _TE_Addr_3_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_3_nReset;
        public Enabled TE_Addr_3_nReset {
            get => _TE_Addr_3_nReset;
            set => _ = Set(ref _TE_Addr_3_nReset, value);
        }
        
        private bool _TE_Addr_3_COMM_TRIsSet;
        public bool TE_Addr_3_COMM_TRIsSet {
            get => _TE_Addr_3_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_3_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_3_COMM_TR;
        public Enabled TE_Addr_3_COMM_TR {
            get => _TE_Addr_3_COMM_TR;
            set => _ = Set(ref _TE_Addr_3_COMM_TR, value);
        }
        
        /*************** Properties for TE_Addr_3_Set register ***********************************/
        private bool _TE_Addr_3_Set_ScanEnabledIsSet;
        public bool TE_Addr_3_Set_ScanEnabledIsSet {
            get => _TE_Addr_3_Set_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_3_Set_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_ScanEnabled;
        public Enabled TE_Addr_3_Set_ScanEnabled {
            get => _TE_Addr_3_Set_ScanEnabled;
            set => _ = Set(ref _TE_Addr_3_Set_ScanEnabled, value);
        }
        
        private bool _TE_Addr_3_Set_DetectedIsSet;
        public bool TE_Addr_3_Set_DetectedIsSet {
            get => _TE_Addr_3_Set_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_3_Set_DetectedIsSet, value); 
        }
        private byte _TE_Addr_3_Set_Detected;
        public byte TE_Addr_3_Set_Detected {
            get => _TE_Addr_3_Set_Detected;
            set => _ = Set(ref _TE_Addr_3_Set_Detected, value);
        }
        
        private bool _TE_Addr_3_Set_TypeIsSet;
        public bool TE_Addr_3_Set_TypeIsSet {
            get => _TE_Addr_3_Set_TypeIsSet;
            set => _ = Set(ref _TE_Addr_3_Set_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_3_Set_Type;
        public TE_Types TE_Addr_3_Set_Type {
            get => _TE_Addr_3_Set_Type;
            set => _ = Set(ref _TE_Addr_3_Set_Type, value);
        }
        
        private bool _TE_Addr_3_Set_SEL_CAN0IsSet;
        public bool TE_Addr_3_Set_SEL_CAN0IsSet {
            get => _TE_Addr_3_Set_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_SEL_CAN0;
        public Enabled TE_Addr_3_Set_SEL_CAN0 {
            get => _TE_Addr_3_Set_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_3_Set_SEL_CAN1IsSet;
        public bool TE_Addr_3_Set_SEL_CAN1IsSet {
            get => _TE_Addr_3_Set_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_SEL_CAN1;
        public Enabled TE_Addr_3_Set_SEL_CAN1 {
            get => _TE_Addr_3_Set_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_3_Set_SEL_RS485IsSet;
        public bool TE_Addr_3_Set_SEL_RS485IsSet {
            get => _TE_Addr_3_Set_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_SEL_RS485;
        public Enabled TE_Addr_3_Set_SEL_RS485 {
            get => _TE_Addr_3_Set_SEL_RS485;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_RS485, value);
        }
        
        private bool _TE_Addr_3_Set_SEL_I2CIsSet;
        public bool TE_Addr_3_Set_SEL_I2CIsSet {
            get => _TE_Addr_3_Set_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_SEL_I2C;
        public Enabled TE_Addr_3_Set_SEL_I2C {
            get => _TE_Addr_3_Set_SEL_I2C;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_I2C, value);
        }
        
        private bool _TE_Addr_3_Set_SEL_RS422IsSet;
        public bool TE_Addr_3_Set_SEL_RS422IsSet {
            get => _TE_Addr_3_Set_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_SEL_RS422;
        public Enabled TE_Addr_3_Set_SEL_RS422 {
            get => _TE_Addr_3_Set_SEL_RS422;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_RS422, value);
        }
        
        private bool _TE_Addr_3_Set_SEL_SPIIsSet;
        public bool TE_Addr_3_Set_SEL_SPIIsSet {
            get => _TE_Addr_3_Set_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_SEL_SPI;
        public Enabled TE_Addr_3_Set_SEL_SPI {
            get => _TE_Addr_3_Set_SEL_SPI;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_SPI, value);
        }
        
        private bool _TE_Addr_3_Set_SEL_UARTIsSet;
        public bool TE_Addr_3_Set_SEL_UARTIsSet {
            get => _TE_Addr_3_Set_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_SEL_UART;
        public Enabled TE_Addr_3_Set_SEL_UART {
            get => _TE_Addr_3_Set_SEL_UART;
            set => _ = Set(ref _TE_Addr_3_Set_SEL_UART, value);
        }
        
        private bool _TE_Addr_3_Set_PowerIsSet;
        public bool TE_Addr_3_Set_PowerIsSet {
            get => _TE_Addr_3_Set_PowerIsSet;
            set => _ = Set(ref _TE_Addr_3_Set_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_Power;
        public Enabled TE_Addr_3_Set_Power {
            get => _TE_Addr_3_Set_Power;
            set => _ = Set(ref _TE_Addr_3_Set_Power, value);
        }
        
        private bool _TE_Addr_3_Set_EnableIsSet;
        public bool TE_Addr_3_Set_EnableIsSet {
            get => _TE_Addr_3_Set_EnableIsSet;
            set => _ = Set(ref _TE_Addr_3_Set_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_Enable;
        public Enabled TE_Addr_3_Set_Enable {
            get => _TE_Addr_3_Set_Enable;
            set => _ = Set(ref _TE_Addr_3_Set_Enable, value);
        }
        
        private bool _TE_Addr_3_Set_nResetIsSet;
        public bool TE_Addr_3_Set_nResetIsSet {
            get => _TE_Addr_3_Set_nResetIsSet;
            set => _ = Set(ref _TE_Addr_3_Set_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_nReset;
        public Enabled TE_Addr_3_Set_nReset {
            get => _TE_Addr_3_Set_nReset;
            set => _ = Set(ref _TE_Addr_3_Set_nReset, value);
        }
        
        private bool _TE_Addr_3_Set_COMM_TRIsSet;
        public bool TE_Addr_3_Set_COMM_TRIsSet {
            get => _TE_Addr_3_Set_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_3_Set_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_3_Set_COMM_TR;
        public Enabled TE_Addr_3_Set_COMM_TR {
            get => _TE_Addr_3_Set_COMM_TR;
            set => _ = Set(ref _TE_Addr_3_Set_COMM_TR, value);
        }
        
        /*************** Properties for TE_Addr_3_Clear register *********************************/
        private bool _TE_Addr_3_Clear_ScanEnabledIsSet;
        public bool TE_Addr_3_Clear_ScanEnabledIsSet {
            get => _TE_Addr_3_Clear_ScanEnabledIsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_ScanEnabledIsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_ScanEnabled;
        public Enabled TE_Addr_3_Clear_ScanEnabled {
            get => _TE_Addr_3_Clear_ScanEnabled;
            set => _ = Set(ref _TE_Addr_3_Clear_ScanEnabled, value);
        }
        
        private bool _TE_Addr_3_Clear_DetectedIsSet;
        public bool TE_Addr_3_Clear_DetectedIsSet {
            get => _TE_Addr_3_Clear_DetectedIsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_DetectedIsSet, value); 
        }
        private byte _TE_Addr_3_Clear_Detected;
        public byte TE_Addr_3_Clear_Detected {
            get => _TE_Addr_3_Clear_Detected;
            set => _ = Set(ref _TE_Addr_3_Clear_Detected, value);
        }
        
        private bool _TE_Addr_3_Clear_TypeIsSet;
        public bool TE_Addr_3_Clear_TypeIsSet {
            get => _TE_Addr_3_Clear_TypeIsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_TypeIsSet, value); 
        }
        private TE_Types _TE_Addr_3_Clear_Type;
        public TE_Types TE_Addr_3_Clear_Type {
            get => _TE_Addr_3_Clear_Type;
            set => _ = Set(ref _TE_Addr_3_Clear_Type, value);
        }
        
        private bool _TE_Addr_3_Clear_SEL_CAN0IsSet;
        public bool TE_Addr_3_Clear_SEL_CAN0IsSet {
            get => _TE_Addr_3_Clear_SEL_CAN0IsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_CAN0IsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_SEL_CAN0;
        public Enabled TE_Addr_3_Clear_SEL_CAN0 {
            get => _TE_Addr_3_Clear_SEL_CAN0;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_CAN0, value);
        }
        
        private bool _TE_Addr_3_Clear_SEL_CAN1IsSet;
        public bool TE_Addr_3_Clear_SEL_CAN1IsSet {
            get => _TE_Addr_3_Clear_SEL_CAN1IsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_CAN1IsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_SEL_CAN1;
        public Enabled TE_Addr_3_Clear_SEL_CAN1 {
            get => _TE_Addr_3_Clear_SEL_CAN1;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_CAN1, value);
        }
        
        private bool _TE_Addr_3_Clear_SEL_RS485IsSet;
        public bool TE_Addr_3_Clear_SEL_RS485IsSet {
            get => _TE_Addr_3_Clear_SEL_RS485IsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_RS485IsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_SEL_RS485;
        public Enabled TE_Addr_3_Clear_SEL_RS485 {
            get => _TE_Addr_3_Clear_SEL_RS485;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_RS485, value);
        }
        
        private bool _TE_Addr_3_Clear_SEL_I2CIsSet;
        public bool TE_Addr_3_Clear_SEL_I2CIsSet {
            get => _TE_Addr_3_Clear_SEL_I2CIsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_I2CIsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_SEL_I2C;
        public Enabled TE_Addr_3_Clear_SEL_I2C {
            get => _TE_Addr_3_Clear_SEL_I2C;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_I2C, value);
        }
        
        private bool _TE_Addr_3_Clear_SEL_RS422IsSet;
        public bool TE_Addr_3_Clear_SEL_RS422IsSet {
            get => _TE_Addr_3_Clear_SEL_RS422IsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_RS422IsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_SEL_RS422;
        public Enabled TE_Addr_3_Clear_SEL_RS422 {
            get => _TE_Addr_3_Clear_SEL_RS422;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_RS422, value);
        }
        
        private bool _TE_Addr_3_Clear_SEL_SPIIsSet;
        public bool TE_Addr_3_Clear_SEL_SPIIsSet {
            get => _TE_Addr_3_Clear_SEL_SPIIsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_SPIIsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_SEL_SPI;
        public Enabled TE_Addr_3_Clear_SEL_SPI {
            get => _TE_Addr_3_Clear_SEL_SPI;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_SPI, value);
        }
        
        private bool _TE_Addr_3_Clear_SEL_UARTIsSet;
        public bool TE_Addr_3_Clear_SEL_UARTIsSet {
            get => _TE_Addr_3_Clear_SEL_UARTIsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_UARTIsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_SEL_UART;
        public Enabled TE_Addr_3_Clear_SEL_UART {
            get => _TE_Addr_3_Clear_SEL_UART;
            set => _ = Set(ref _TE_Addr_3_Clear_SEL_UART, value);
        }
        
        private bool _TE_Addr_3_Clear_PowerIsSet;
        public bool TE_Addr_3_Clear_PowerIsSet {
            get => _TE_Addr_3_Clear_PowerIsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_PowerIsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_Power;
        public Enabled TE_Addr_3_Clear_Power {
            get => _TE_Addr_3_Clear_Power;
            set => _ = Set(ref _TE_Addr_3_Clear_Power, value);
        }
        
        private bool _TE_Addr_3_Clear_EnableIsSet;
        public bool TE_Addr_3_Clear_EnableIsSet {
            get => _TE_Addr_3_Clear_EnableIsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_EnableIsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_Enable;
        public Enabled TE_Addr_3_Clear_Enable {
            get => _TE_Addr_3_Clear_Enable;
            set => _ = Set(ref _TE_Addr_3_Clear_Enable, value);
        }
        
        private bool _TE_Addr_3_Clear_nResetIsSet;
        public bool TE_Addr_3_Clear_nResetIsSet {
            get => _TE_Addr_3_Clear_nResetIsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_nResetIsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_nReset;
        public Enabled TE_Addr_3_Clear_nReset {
            get => _TE_Addr_3_Clear_nReset;
            set => _ = Set(ref _TE_Addr_3_Clear_nReset, value);
        }
        
        private bool _TE_Addr_3_Clear_COMM_TRIsSet;
        public bool TE_Addr_3_Clear_COMM_TRIsSet {
            get => _TE_Addr_3_Clear_COMM_TRIsSet;
            set => _ = Set(ref _TE_Addr_3_Clear_COMM_TRIsSet, value); 
        }
        private Enabled _TE_Addr_3_Clear_COMM_TR;
        public Enabled TE_Addr_3_Clear_COMM_TR {
            get => _TE_Addr_3_Clear_COMM_TR;
            set => _ = Set(ref _TE_Addr_3_Clear_COMM_TR, value);
        }
        
        /*************** Min and Max Properties for MTC_Addr_0 types *****************************/
        /*************** Properties for MTC_Addr_0 register **************************************/
        private bool _MTC_Addr_0_ScanEnabledIsSet;
        public bool MTC_Addr_0_ScanEnabledIsSet {
            get => _MTC_Addr_0_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_0_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_0_ScanEnabled;
        public Enabled MTC_Addr_0_ScanEnabled {
            get => _MTC_Addr_0_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_0_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_0_DetectedIsSet;
        public bool MTC_Addr_0_DetectedIsSet {
            get => _MTC_Addr_0_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_0_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_0_Detected;
        public byte MTC_Addr_0_Detected {
            get => _MTC_Addr_0_Detected;
            set => _ = Set(ref _MTC_Addr_0_Detected, value);
        }
        
        private bool _MTC_Addr_0_TypeIsSet;
        public bool MTC_Addr_0_TypeIsSet {
            get => _MTC_Addr_0_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_0_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_0_Type;
        public UInt32 MTC_Addr_0_Type {
            get => _MTC_Addr_0_Type;
            set => _ = Set(ref _MTC_Addr_0_Type, value);
        }
        
        private bool _MTC_Addr_0_ENABLE_1IsSet;
        public bool MTC_Addr_0_ENABLE_1IsSet {
            get => _MTC_Addr_0_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_ENABLE_1;
        public Enabled MTC_Addr_0_ENABLE_1 {
            get => _MTC_Addr_0_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_0_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_0_ENABLE_2IsSet;
        public bool MTC_Addr_0_ENABLE_2IsSet {
            get => _MTC_Addr_0_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_ENABLE_2;
        public Enabled MTC_Addr_0_ENABLE_2 {
            get => _MTC_Addr_0_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_0_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_0_SEL_I2C_1IsSet;
        public bool MTC_Addr_0_SEL_I2C_1IsSet {
            get => _MTC_Addr_0_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_I2C_1;
        public Enabled MTC_Addr_0_SEL_I2C_1 {
            get => _MTC_Addr_0_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_0_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_0_SEL_I2C_2IsSet;
        public bool MTC_Addr_0_SEL_I2C_2IsSet {
            get => _MTC_Addr_0_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_I2C_2;
        public Enabled MTC_Addr_0_SEL_I2C_2 {
            get => _MTC_Addr_0_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_0_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_0_SEL_UART_1IsSet;
        public bool MTC_Addr_0_SEL_UART_1IsSet {
            get => _MTC_Addr_0_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_UART_1;
        public Enabled MTC_Addr_0_SEL_UART_1 {
            get => _MTC_Addr_0_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_0_SEL_UART_2IsSet;
        public bool MTC_Addr_0_SEL_UART_2IsSet {
            get => _MTC_Addr_0_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_UART_2;
        public Enabled MTC_Addr_0_SEL_UART_2 {
            get => _MTC_Addr_0_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_0_SEL_UART_3IsSet;
        public bool MTC_Addr_0_SEL_UART_3IsSet {
            get => _MTC_Addr_0_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_UART_3;
        public Enabled MTC_Addr_0_SEL_UART_3 {
            get => _MTC_Addr_0_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_0_SEL_UART_4IsSet;
        public bool MTC_Addr_0_SEL_UART_4IsSet {
            get => _MTC_Addr_0_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_UART_4;
        public Enabled MTC_Addr_0_SEL_UART_4 {
            get => _MTC_Addr_0_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_0_SEL_UART_5IsSet;
        public bool MTC_Addr_0_SEL_UART_5IsSet {
            get => _MTC_Addr_0_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_UART_5;
        public Enabled MTC_Addr_0_SEL_UART_5 {
            get => _MTC_Addr_0_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_0_SEL_UART_6IsSet;
        public bool MTC_Addr_0_SEL_UART_6IsSet {
            get => _MTC_Addr_0_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_UART_6;
        public Enabled MTC_Addr_0_SEL_UART_6 {
            get => _MTC_Addr_0_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_0_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_0_SEL_VBATIsSet;
        public bool MTC_Addr_0_SEL_VBATIsSet {
            get => _MTC_Addr_0_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_VBAT;
        public Enabled MTC_Addr_0_SEL_VBAT {
            get => _MTC_Addr_0_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_0_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_0_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_0_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_0_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_VBAT_ALT;
        public Enabled MTC_Addr_0_SEL_VBAT_ALT {
            get => _MTC_Addr_0_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_0_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_0_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_0_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_0_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_0_SEL_VBAT_FPGA {
            get => _MTC_Addr_0_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_0_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_0_SEL_nRESET_1IsSet;
        public bool MTC_Addr_0_SEL_nRESET_1IsSet {
            get => _MTC_Addr_0_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_nRESET_1;
        public Enabled MTC_Addr_0_SEL_nRESET_1 {
            get => _MTC_Addr_0_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_0_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_0_SEL_nRESET_2IsSet;
        public bool MTC_Addr_0_SEL_nRESET_2IsSet {
            get => _MTC_Addr_0_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_nRESET_2;
        public Enabled MTC_Addr_0_SEL_nRESET_2 {
            get => _MTC_Addr_0_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_0_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_0_SEL_nRESET_3IsSet;
        public bool MTC_Addr_0_SEL_nRESET_3IsSet {
            get => _MTC_Addr_0_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_nRESET_3;
        public Enabled MTC_Addr_0_SEL_nRESET_3 {
            get => _MTC_Addr_0_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_0_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_0_SEL_CS_1IsSet;
        public bool MTC_Addr_0_SEL_CS_1IsSet {
            get => _MTC_Addr_0_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_CS_1;
        public Enabled MTC_Addr_0_SEL_CS_1 {
            get => _MTC_Addr_0_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_0_SEL_CS_2IsSet;
        public bool MTC_Addr_0_SEL_CS_2IsSet {
            get => _MTC_Addr_0_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_CS_2;
        public Enabled MTC_Addr_0_SEL_CS_2 {
            get => _MTC_Addr_0_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_0_SEL_CS_3IsSet;
        public bool MTC_Addr_0_SEL_CS_3IsSet {
            get => _MTC_Addr_0_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_CS_3;
        public Enabled MTC_Addr_0_SEL_CS_3 {
            get => _MTC_Addr_0_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_0_SEL_CS_4IsSet;
        public bool MTC_Addr_0_SEL_CS_4IsSet {
            get => _MTC_Addr_0_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_CS_4;
        public Enabled MTC_Addr_0_SEL_CS_4 {
            get => _MTC_Addr_0_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_0_SEL_CS_5IsSet;
        public bool MTC_Addr_0_SEL_CS_5IsSet {
            get => _MTC_Addr_0_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_CS_5;
        public Enabled MTC_Addr_0_SEL_CS_5 {
            get => _MTC_Addr_0_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_0_SEL_CS_6IsSet;
        public bool MTC_Addr_0_SEL_CS_6IsSet {
            get => _MTC_Addr_0_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_CS_6;
        public Enabled MTC_Addr_0_SEL_CS_6 {
            get => _MTC_Addr_0_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_0_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_0_SEL_SPI_1IsSet;
        public bool MTC_Addr_0_SEL_SPI_1IsSet {
            get => _MTC_Addr_0_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_SPI_1;
        public Enabled MTC_Addr_0_SEL_SPI_1 {
            get => _MTC_Addr_0_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_0_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_0_SEL_SPI_2IsSet;
        public bool MTC_Addr_0_SEL_SPI_2IsSet {
            get => _MTC_Addr_0_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_SPI_2;
        public Enabled MTC_Addr_0_SEL_SPI_2 {
            get => _MTC_Addr_0_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_0_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_0_SEL_CAN_1IsSet;
        public bool MTC_Addr_0_SEL_CAN_1IsSet {
            get => _MTC_Addr_0_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_CAN_1;
        public Enabled MTC_Addr_0_SEL_CAN_1 {
            get => _MTC_Addr_0_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_0_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_0_SEL_CAN_2IsSet;
        public bool MTC_Addr_0_SEL_CAN_2IsSet {
            get => _MTC_Addr_0_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_CAN_2;
        public Enabled MTC_Addr_0_SEL_CAN_2 {
            get => _MTC_Addr_0_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_0_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_0_SEL_CAN_3IsSet;
        public bool MTC_Addr_0_SEL_CAN_3IsSet {
            get => _MTC_Addr_0_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_CAN_3;
        public Enabled MTC_Addr_0_SEL_CAN_3 {
            get => _MTC_Addr_0_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_0_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_0_SEL_RS422IsSet;
        public bool MTC_Addr_0_SEL_RS422IsSet {
            get => _MTC_Addr_0_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_0_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_0_SEL_RS422;
        public Enabled MTC_Addr_0_SEL_RS422 {
            get => _MTC_Addr_0_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_0_SEL_RS422, value);
        }
        
        /*************** Properties for MTC_Addr_0_Set register **********************************/
        private bool _MTC_Addr_0_Set_ScanEnabledIsSet;
        public bool MTC_Addr_0_Set_ScanEnabledIsSet {
            get => _MTC_Addr_0_Set_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_ScanEnabled;
        public Enabled MTC_Addr_0_Set_ScanEnabled {
            get => _MTC_Addr_0_Set_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_0_Set_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_0_Set_DetectedIsSet;
        public bool MTC_Addr_0_Set_DetectedIsSet {
            get => _MTC_Addr_0_Set_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_0_Set_Detected;
        public byte MTC_Addr_0_Set_Detected {
            get => _MTC_Addr_0_Set_Detected;
            set => _ = Set(ref _MTC_Addr_0_Set_Detected, value);
        }
        
        private bool _MTC_Addr_0_Set_TypeIsSet;
        public bool MTC_Addr_0_Set_TypeIsSet {
            get => _MTC_Addr_0_Set_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_0_Set_Type;
        public UInt32 MTC_Addr_0_Set_Type {
            get => _MTC_Addr_0_Set_Type;
            set => _ = Set(ref _MTC_Addr_0_Set_Type, value);
        }
        
        private bool _MTC_Addr_0_Set_ENABLE_1IsSet;
        public bool MTC_Addr_0_Set_ENABLE_1IsSet {
            get => _MTC_Addr_0_Set_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_ENABLE_1;
        public Enabled MTC_Addr_0_Set_ENABLE_1 {
            get => _MTC_Addr_0_Set_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_0_Set_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_0_Set_ENABLE_2IsSet;
        public bool MTC_Addr_0_Set_ENABLE_2IsSet {
            get => _MTC_Addr_0_Set_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_ENABLE_2;
        public Enabled MTC_Addr_0_Set_ENABLE_2 {
            get => _MTC_Addr_0_Set_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_0_Set_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_I2C_1IsSet;
        public bool MTC_Addr_0_Set_SEL_I2C_1IsSet {
            get => _MTC_Addr_0_Set_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_I2C_1;
        public Enabled MTC_Addr_0_Set_SEL_I2C_1 {
            get => _MTC_Addr_0_Set_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_I2C_2IsSet;
        public bool MTC_Addr_0_Set_SEL_I2C_2IsSet {
            get => _MTC_Addr_0_Set_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_I2C_2;
        public Enabled MTC_Addr_0_Set_SEL_I2C_2 {
            get => _MTC_Addr_0_Set_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_UART_1IsSet;
        public bool MTC_Addr_0_Set_SEL_UART_1IsSet {
            get => _MTC_Addr_0_Set_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_UART_1;
        public Enabled MTC_Addr_0_Set_SEL_UART_1 {
            get => _MTC_Addr_0_Set_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_UART_2IsSet;
        public bool MTC_Addr_0_Set_SEL_UART_2IsSet {
            get => _MTC_Addr_0_Set_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_UART_2;
        public Enabled MTC_Addr_0_Set_SEL_UART_2 {
            get => _MTC_Addr_0_Set_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_UART_3IsSet;
        public bool MTC_Addr_0_Set_SEL_UART_3IsSet {
            get => _MTC_Addr_0_Set_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_UART_3;
        public Enabled MTC_Addr_0_Set_SEL_UART_3 {
            get => _MTC_Addr_0_Set_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_UART_4IsSet;
        public bool MTC_Addr_0_Set_SEL_UART_4IsSet {
            get => _MTC_Addr_0_Set_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_UART_4;
        public Enabled MTC_Addr_0_Set_SEL_UART_4 {
            get => _MTC_Addr_0_Set_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_UART_5IsSet;
        public bool MTC_Addr_0_Set_SEL_UART_5IsSet {
            get => _MTC_Addr_0_Set_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_UART_5;
        public Enabled MTC_Addr_0_Set_SEL_UART_5 {
            get => _MTC_Addr_0_Set_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_UART_6IsSet;
        public bool MTC_Addr_0_Set_SEL_UART_6IsSet {
            get => _MTC_Addr_0_Set_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_UART_6;
        public Enabled MTC_Addr_0_Set_SEL_UART_6 {
            get => _MTC_Addr_0_Set_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_VBATIsSet;
        public bool MTC_Addr_0_Set_SEL_VBATIsSet {
            get => _MTC_Addr_0_Set_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_VBAT;
        public Enabled MTC_Addr_0_Set_SEL_VBAT {
            get => _MTC_Addr_0_Set_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_0_Set_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_0_Set_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_VBAT_ALT;
        public Enabled MTC_Addr_0_Set_SEL_VBAT_ALT {
            get => _MTC_Addr_0_Set_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_0_Set_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_0_Set_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_0_Set_SEL_VBAT_FPGA {
            get => _MTC_Addr_0_Set_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_nRESET_1IsSet;
        public bool MTC_Addr_0_Set_SEL_nRESET_1IsSet {
            get => _MTC_Addr_0_Set_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_nRESET_1;
        public Enabled MTC_Addr_0_Set_SEL_nRESET_1 {
            get => _MTC_Addr_0_Set_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_nRESET_2IsSet;
        public bool MTC_Addr_0_Set_SEL_nRESET_2IsSet {
            get => _MTC_Addr_0_Set_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_nRESET_2;
        public Enabled MTC_Addr_0_Set_SEL_nRESET_2 {
            get => _MTC_Addr_0_Set_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_nRESET_3IsSet;
        public bool MTC_Addr_0_Set_SEL_nRESET_3IsSet {
            get => _MTC_Addr_0_Set_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_nRESET_3;
        public Enabled MTC_Addr_0_Set_SEL_nRESET_3 {
            get => _MTC_Addr_0_Set_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_CS_1IsSet;
        public bool MTC_Addr_0_Set_SEL_CS_1IsSet {
            get => _MTC_Addr_0_Set_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_CS_1;
        public Enabled MTC_Addr_0_Set_SEL_CS_1 {
            get => _MTC_Addr_0_Set_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_CS_2IsSet;
        public bool MTC_Addr_0_Set_SEL_CS_2IsSet {
            get => _MTC_Addr_0_Set_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_CS_2;
        public Enabled MTC_Addr_0_Set_SEL_CS_2 {
            get => _MTC_Addr_0_Set_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_CS_3IsSet;
        public bool MTC_Addr_0_Set_SEL_CS_3IsSet {
            get => _MTC_Addr_0_Set_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_CS_3;
        public Enabled MTC_Addr_0_Set_SEL_CS_3 {
            get => _MTC_Addr_0_Set_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_CS_4IsSet;
        public bool MTC_Addr_0_Set_SEL_CS_4IsSet {
            get => _MTC_Addr_0_Set_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_CS_4;
        public Enabled MTC_Addr_0_Set_SEL_CS_4 {
            get => _MTC_Addr_0_Set_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_CS_5IsSet;
        public bool MTC_Addr_0_Set_SEL_CS_5IsSet {
            get => _MTC_Addr_0_Set_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_CS_5;
        public Enabled MTC_Addr_0_Set_SEL_CS_5 {
            get => _MTC_Addr_0_Set_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_CS_6IsSet;
        public bool MTC_Addr_0_Set_SEL_CS_6IsSet {
            get => _MTC_Addr_0_Set_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_CS_6;
        public Enabled MTC_Addr_0_Set_SEL_CS_6 {
            get => _MTC_Addr_0_Set_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_SPI_1IsSet;
        public bool MTC_Addr_0_Set_SEL_SPI_1IsSet {
            get => _MTC_Addr_0_Set_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_SPI_1;
        public Enabled MTC_Addr_0_Set_SEL_SPI_1 {
            get => _MTC_Addr_0_Set_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_SPI_2IsSet;
        public bool MTC_Addr_0_Set_SEL_SPI_2IsSet {
            get => _MTC_Addr_0_Set_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_SPI_2;
        public Enabled MTC_Addr_0_Set_SEL_SPI_2 {
            get => _MTC_Addr_0_Set_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_CAN_1IsSet;
        public bool MTC_Addr_0_Set_SEL_CAN_1IsSet {
            get => _MTC_Addr_0_Set_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_CAN_1;
        public Enabled MTC_Addr_0_Set_SEL_CAN_1 {
            get => _MTC_Addr_0_Set_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_CAN_2IsSet;
        public bool MTC_Addr_0_Set_SEL_CAN_2IsSet {
            get => _MTC_Addr_0_Set_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_CAN_2;
        public Enabled MTC_Addr_0_Set_SEL_CAN_2 {
            get => _MTC_Addr_0_Set_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_CAN_3IsSet;
        public bool MTC_Addr_0_Set_SEL_CAN_3IsSet {
            get => _MTC_Addr_0_Set_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_CAN_3;
        public Enabled MTC_Addr_0_Set_SEL_CAN_3 {
            get => _MTC_Addr_0_Set_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_0_Set_SEL_RS422IsSet;
        public bool MTC_Addr_0_Set_SEL_RS422IsSet {
            get => _MTC_Addr_0_Set_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Set_SEL_RS422;
        public Enabled MTC_Addr_0_Set_SEL_RS422 {
            get => _MTC_Addr_0_Set_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_0_Set_SEL_RS422, value);
        }
        
        /*************** Properties for MTC_Addr_0_Clear register ********************************/
        private bool _MTC_Addr_0_Clear_ScanEnabledIsSet;
        public bool MTC_Addr_0_Clear_ScanEnabledIsSet {
            get => _MTC_Addr_0_Clear_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_ScanEnabled;
        public Enabled MTC_Addr_0_Clear_ScanEnabled {
            get => _MTC_Addr_0_Clear_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_0_Clear_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_0_Clear_DetectedIsSet;
        public bool MTC_Addr_0_Clear_DetectedIsSet {
            get => _MTC_Addr_0_Clear_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_0_Clear_Detected;
        public byte MTC_Addr_0_Clear_Detected {
            get => _MTC_Addr_0_Clear_Detected;
            set => _ = Set(ref _MTC_Addr_0_Clear_Detected, value);
        }
        
        private bool _MTC_Addr_0_Clear_TypeIsSet;
        public bool MTC_Addr_0_Clear_TypeIsSet {
            get => _MTC_Addr_0_Clear_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_0_Clear_Type;
        public UInt32 MTC_Addr_0_Clear_Type {
            get => _MTC_Addr_0_Clear_Type;
            set => _ = Set(ref _MTC_Addr_0_Clear_Type, value);
        }
        
        private bool _MTC_Addr_0_Clear_ENABLE_1IsSet;
        public bool MTC_Addr_0_Clear_ENABLE_1IsSet {
            get => _MTC_Addr_0_Clear_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_ENABLE_1;
        public Enabled MTC_Addr_0_Clear_ENABLE_1 {
            get => _MTC_Addr_0_Clear_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_0_Clear_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_0_Clear_ENABLE_2IsSet;
        public bool MTC_Addr_0_Clear_ENABLE_2IsSet {
            get => _MTC_Addr_0_Clear_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_ENABLE_2;
        public Enabled MTC_Addr_0_Clear_ENABLE_2 {
            get => _MTC_Addr_0_Clear_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_0_Clear_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_I2C_1IsSet;
        public bool MTC_Addr_0_Clear_SEL_I2C_1IsSet {
            get => _MTC_Addr_0_Clear_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_I2C_1;
        public Enabled MTC_Addr_0_Clear_SEL_I2C_1 {
            get => _MTC_Addr_0_Clear_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_I2C_2IsSet;
        public bool MTC_Addr_0_Clear_SEL_I2C_2IsSet {
            get => _MTC_Addr_0_Clear_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_I2C_2;
        public Enabled MTC_Addr_0_Clear_SEL_I2C_2 {
            get => _MTC_Addr_0_Clear_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_UART_1IsSet;
        public bool MTC_Addr_0_Clear_SEL_UART_1IsSet {
            get => _MTC_Addr_0_Clear_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_UART_1;
        public Enabled MTC_Addr_0_Clear_SEL_UART_1 {
            get => _MTC_Addr_0_Clear_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_UART_2IsSet;
        public bool MTC_Addr_0_Clear_SEL_UART_2IsSet {
            get => _MTC_Addr_0_Clear_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_UART_2;
        public Enabled MTC_Addr_0_Clear_SEL_UART_2 {
            get => _MTC_Addr_0_Clear_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_UART_3IsSet;
        public bool MTC_Addr_0_Clear_SEL_UART_3IsSet {
            get => _MTC_Addr_0_Clear_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_UART_3;
        public Enabled MTC_Addr_0_Clear_SEL_UART_3 {
            get => _MTC_Addr_0_Clear_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_UART_4IsSet;
        public bool MTC_Addr_0_Clear_SEL_UART_4IsSet {
            get => _MTC_Addr_0_Clear_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_UART_4;
        public Enabled MTC_Addr_0_Clear_SEL_UART_4 {
            get => _MTC_Addr_0_Clear_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_UART_5IsSet;
        public bool MTC_Addr_0_Clear_SEL_UART_5IsSet {
            get => _MTC_Addr_0_Clear_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_UART_5;
        public Enabled MTC_Addr_0_Clear_SEL_UART_5 {
            get => _MTC_Addr_0_Clear_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_UART_6IsSet;
        public bool MTC_Addr_0_Clear_SEL_UART_6IsSet {
            get => _MTC_Addr_0_Clear_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_UART_6;
        public Enabled MTC_Addr_0_Clear_SEL_UART_6 {
            get => _MTC_Addr_0_Clear_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_VBATIsSet;
        public bool MTC_Addr_0_Clear_SEL_VBATIsSet {
            get => _MTC_Addr_0_Clear_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_VBAT;
        public Enabled MTC_Addr_0_Clear_SEL_VBAT {
            get => _MTC_Addr_0_Clear_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_0_Clear_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_0_Clear_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_VBAT_ALT;
        public Enabled MTC_Addr_0_Clear_SEL_VBAT_ALT {
            get => _MTC_Addr_0_Clear_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_0_Clear_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_0_Clear_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_0_Clear_SEL_VBAT_FPGA {
            get => _MTC_Addr_0_Clear_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_nRESET_1IsSet;
        public bool MTC_Addr_0_Clear_SEL_nRESET_1IsSet {
            get => _MTC_Addr_0_Clear_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_nRESET_1;
        public Enabled MTC_Addr_0_Clear_SEL_nRESET_1 {
            get => _MTC_Addr_0_Clear_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_nRESET_2IsSet;
        public bool MTC_Addr_0_Clear_SEL_nRESET_2IsSet {
            get => _MTC_Addr_0_Clear_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_nRESET_2;
        public Enabled MTC_Addr_0_Clear_SEL_nRESET_2 {
            get => _MTC_Addr_0_Clear_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_nRESET_3IsSet;
        public bool MTC_Addr_0_Clear_SEL_nRESET_3IsSet {
            get => _MTC_Addr_0_Clear_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_nRESET_3;
        public Enabled MTC_Addr_0_Clear_SEL_nRESET_3 {
            get => _MTC_Addr_0_Clear_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_CS_1IsSet;
        public bool MTC_Addr_0_Clear_SEL_CS_1IsSet {
            get => _MTC_Addr_0_Clear_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_CS_1;
        public Enabled MTC_Addr_0_Clear_SEL_CS_1 {
            get => _MTC_Addr_0_Clear_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_CS_2IsSet;
        public bool MTC_Addr_0_Clear_SEL_CS_2IsSet {
            get => _MTC_Addr_0_Clear_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_CS_2;
        public Enabled MTC_Addr_0_Clear_SEL_CS_2 {
            get => _MTC_Addr_0_Clear_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_CS_3IsSet;
        public bool MTC_Addr_0_Clear_SEL_CS_3IsSet {
            get => _MTC_Addr_0_Clear_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_CS_3;
        public Enabled MTC_Addr_0_Clear_SEL_CS_3 {
            get => _MTC_Addr_0_Clear_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_CS_4IsSet;
        public bool MTC_Addr_0_Clear_SEL_CS_4IsSet {
            get => _MTC_Addr_0_Clear_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_CS_4;
        public Enabled MTC_Addr_0_Clear_SEL_CS_4 {
            get => _MTC_Addr_0_Clear_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_CS_5IsSet;
        public bool MTC_Addr_0_Clear_SEL_CS_5IsSet {
            get => _MTC_Addr_0_Clear_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_CS_5;
        public Enabled MTC_Addr_0_Clear_SEL_CS_5 {
            get => _MTC_Addr_0_Clear_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_CS_6IsSet;
        public bool MTC_Addr_0_Clear_SEL_CS_6IsSet {
            get => _MTC_Addr_0_Clear_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_CS_6;
        public Enabled MTC_Addr_0_Clear_SEL_CS_6 {
            get => _MTC_Addr_0_Clear_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_SPI_1IsSet;
        public bool MTC_Addr_0_Clear_SEL_SPI_1IsSet {
            get => _MTC_Addr_0_Clear_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_SPI_1;
        public Enabled MTC_Addr_0_Clear_SEL_SPI_1 {
            get => _MTC_Addr_0_Clear_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_SPI_2IsSet;
        public bool MTC_Addr_0_Clear_SEL_SPI_2IsSet {
            get => _MTC_Addr_0_Clear_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_SPI_2;
        public Enabled MTC_Addr_0_Clear_SEL_SPI_2 {
            get => _MTC_Addr_0_Clear_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_CAN_1IsSet;
        public bool MTC_Addr_0_Clear_SEL_CAN_1IsSet {
            get => _MTC_Addr_0_Clear_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_CAN_1;
        public Enabled MTC_Addr_0_Clear_SEL_CAN_1 {
            get => _MTC_Addr_0_Clear_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_CAN_2IsSet;
        public bool MTC_Addr_0_Clear_SEL_CAN_2IsSet {
            get => _MTC_Addr_0_Clear_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_CAN_2;
        public Enabled MTC_Addr_0_Clear_SEL_CAN_2 {
            get => _MTC_Addr_0_Clear_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_CAN_3IsSet;
        public bool MTC_Addr_0_Clear_SEL_CAN_3IsSet {
            get => _MTC_Addr_0_Clear_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_CAN_3;
        public Enabled MTC_Addr_0_Clear_SEL_CAN_3 {
            get => _MTC_Addr_0_Clear_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_0_Clear_SEL_RS422IsSet;
        public bool MTC_Addr_0_Clear_SEL_RS422IsSet {
            get => _MTC_Addr_0_Clear_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_0_Clear_SEL_RS422;
        public Enabled MTC_Addr_0_Clear_SEL_RS422 {
            get => _MTC_Addr_0_Clear_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_0_Clear_SEL_RS422, value);
        }
        
        /*************** Properties for MTC_Addr_1 register **************************************/
        private bool _MTC_Addr_1_ScanEnabledIsSet;
        public bool MTC_Addr_1_ScanEnabledIsSet {
            get => _MTC_Addr_1_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_1_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_1_ScanEnabled;
        public Enabled MTC_Addr_1_ScanEnabled {
            get => _MTC_Addr_1_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_1_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_1_DetectedIsSet;
        public bool MTC_Addr_1_DetectedIsSet {
            get => _MTC_Addr_1_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_1_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_1_Detected;
        public byte MTC_Addr_1_Detected {
            get => _MTC_Addr_1_Detected;
            set => _ = Set(ref _MTC_Addr_1_Detected, value);
        }
        
        private bool _MTC_Addr_1_TypeIsSet;
        public bool MTC_Addr_1_TypeIsSet {
            get => _MTC_Addr_1_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_1_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_1_Type;
        public UInt32 MTC_Addr_1_Type {
            get => _MTC_Addr_1_Type;
            set => _ = Set(ref _MTC_Addr_1_Type, value);
        }
        
        private bool _MTC_Addr_1_ENABLE_1IsSet;
        public bool MTC_Addr_1_ENABLE_1IsSet {
            get => _MTC_Addr_1_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_ENABLE_1;
        public Enabled MTC_Addr_1_ENABLE_1 {
            get => _MTC_Addr_1_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_1_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_1_ENABLE_2IsSet;
        public bool MTC_Addr_1_ENABLE_2IsSet {
            get => _MTC_Addr_1_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_ENABLE_2;
        public Enabled MTC_Addr_1_ENABLE_2 {
            get => _MTC_Addr_1_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_1_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_1_SEL_I2C_1IsSet;
        public bool MTC_Addr_1_SEL_I2C_1IsSet {
            get => _MTC_Addr_1_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_I2C_1;
        public Enabled MTC_Addr_1_SEL_I2C_1 {
            get => _MTC_Addr_1_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_1_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_1_SEL_I2C_2IsSet;
        public bool MTC_Addr_1_SEL_I2C_2IsSet {
            get => _MTC_Addr_1_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_I2C_2;
        public Enabled MTC_Addr_1_SEL_I2C_2 {
            get => _MTC_Addr_1_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_1_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_1_SEL_UART_1IsSet;
        public bool MTC_Addr_1_SEL_UART_1IsSet {
            get => _MTC_Addr_1_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_UART_1;
        public Enabled MTC_Addr_1_SEL_UART_1 {
            get => _MTC_Addr_1_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_1_SEL_UART_2IsSet;
        public bool MTC_Addr_1_SEL_UART_2IsSet {
            get => _MTC_Addr_1_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_UART_2;
        public Enabled MTC_Addr_1_SEL_UART_2 {
            get => _MTC_Addr_1_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_1_SEL_UART_3IsSet;
        public bool MTC_Addr_1_SEL_UART_3IsSet {
            get => _MTC_Addr_1_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_UART_3;
        public Enabled MTC_Addr_1_SEL_UART_3 {
            get => _MTC_Addr_1_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_1_SEL_UART_4IsSet;
        public bool MTC_Addr_1_SEL_UART_4IsSet {
            get => _MTC_Addr_1_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_UART_4;
        public Enabled MTC_Addr_1_SEL_UART_4 {
            get => _MTC_Addr_1_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_1_SEL_UART_5IsSet;
        public bool MTC_Addr_1_SEL_UART_5IsSet {
            get => _MTC_Addr_1_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_UART_5;
        public Enabled MTC_Addr_1_SEL_UART_5 {
            get => _MTC_Addr_1_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_1_SEL_UART_6IsSet;
        public bool MTC_Addr_1_SEL_UART_6IsSet {
            get => _MTC_Addr_1_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_UART_6;
        public Enabled MTC_Addr_1_SEL_UART_6 {
            get => _MTC_Addr_1_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_1_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_1_SEL_VBATIsSet;
        public bool MTC_Addr_1_SEL_VBATIsSet {
            get => _MTC_Addr_1_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_VBAT;
        public Enabled MTC_Addr_1_SEL_VBAT {
            get => _MTC_Addr_1_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_1_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_1_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_1_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_1_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_VBAT_ALT;
        public Enabled MTC_Addr_1_SEL_VBAT_ALT {
            get => _MTC_Addr_1_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_1_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_1_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_1_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_1_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_1_SEL_VBAT_FPGA {
            get => _MTC_Addr_1_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_1_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_1_SEL_nRESET_1IsSet;
        public bool MTC_Addr_1_SEL_nRESET_1IsSet {
            get => _MTC_Addr_1_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_nRESET_1;
        public Enabled MTC_Addr_1_SEL_nRESET_1 {
            get => _MTC_Addr_1_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_1_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_1_SEL_nRESET_2IsSet;
        public bool MTC_Addr_1_SEL_nRESET_2IsSet {
            get => _MTC_Addr_1_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_nRESET_2;
        public Enabled MTC_Addr_1_SEL_nRESET_2 {
            get => _MTC_Addr_1_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_1_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_1_SEL_nRESET_3IsSet;
        public bool MTC_Addr_1_SEL_nRESET_3IsSet {
            get => _MTC_Addr_1_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_nRESET_3;
        public Enabled MTC_Addr_1_SEL_nRESET_3 {
            get => _MTC_Addr_1_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_1_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_1_SEL_CS_1IsSet;
        public bool MTC_Addr_1_SEL_CS_1IsSet {
            get => _MTC_Addr_1_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_CS_1;
        public Enabled MTC_Addr_1_SEL_CS_1 {
            get => _MTC_Addr_1_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_1_SEL_CS_2IsSet;
        public bool MTC_Addr_1_SEL_CS_2IsSet {
            get => _MTC_Addr_1_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_CS_2;
        public Enabled MTC_Addr_1_SEL_CS_2 {
            get => _MTC_Addr_1_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_1_SEL_CS_3IsSet;
        public bool MTC_Addr_1_SEL_CS_3IsSet {
            get => _MTC_Addr_1_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_CS_3;
        public Enabled MTC_Addr_1_SEL_CS_3 {
            get => _MTC_Addr_1_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_1_SEL_CS_4IsSet;
        public bool MTC_Addr_1_SEL_CS_4IsSet {
            get => _MTC_Addr_1_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_CS_4;
        public Enabled MTC_Addr_1_SEL_CS_4 {
            get => _MTC_Addr_1_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_1_SEL_CS_5IsSet;
        public bool MTC_Addr_1_SEL_CS_5IsSet {
            get => _MTC_Addr_1_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_CS_5;
        public Enabled MTC_Addr_1_SEL_CS_5 {
            get => _MTC_Addr_1_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_1_SEL_CS_6IsSet;
        public bool MTC_Addr_1_SEL_CS_6IsSet {
            get => _MTC_Addr_1_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_CS_6;
        public Enabled MTC_Addr_1_SEL_CS_6 {
            get => _MTC_Addr_1_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_1_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_1_SEL_SPI_1IsSet;
        public bool MTC_Addr_1_SEL_SPI_1IsSet {
            get => _MTC_Addr_1_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_SPI_1;
        public Enabled MTC_Addr_1_SEL_SPI_1 {
            get => _MTC_Addr_1_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_1_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_1_SEL_SPI_2IsSet;
        public bool MTC_Addr_1_SEL_SPI_2IsSet {
            get => _MTC_Addr_1_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_SPI_2;
        public Enabled MTC_Addr_1_SEL_SPI_2 {
            get => _MTC_Addr_1_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_1_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_1_SEL_CAN_1IsSet;
        public bool MTC_Addr_1_SEL_CAN_1IsSet {
            get => _MTC_Addr_1_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_CAN_1;
        public Enabled MTC_Addr_1_SEL_CAN_1 {
            get => _MTC_Addr_1_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_1_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_1_SEL_CAN_2IsSet;
        public bool MTC_Addr_1_SEL_CAN_2IsSet {
            get => _MTC_Addr_1_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_CAN_2;
        public Enabled MTC_Addr_1_SEL_CAN_2 {
            get => _MTC_Addr_1_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_1_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_1_SEL_CAN_3IsSet;
        public bool MTC_Addr_1_SEL_CAN_3IsSet {
            get => _MTC_Addr_1_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_CAN_3;
        public Enabled MTC_Addr_1_SEL_CAN_3 {
            get => _MTC_Addr_1_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_1_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_1_SEL_RS422IsSet;
        public bool MTC_Addr_1_SEL_RS422IsSet {
            get => _MTC_Addr_1_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_1_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_1_SEL_RS422;
        public Enabled MTC_Addr_1_SEL_RS422 {
            get => _MTC_Addr_1_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_1_SEL_RS422, value);
        }
        
        /*************** Properties for MTC_Addr_1_Set register **********************************/
        private bool _MTC_Addr_1_Set_ScanEnabledIsSet;
        public bool MTC_Addr_1_Set_ScanEnabledIsSet {
            get => _MTC_Addr_1_Set_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_ScanEnabled;
        public Enabled MTC_Addr_1_Set_ScanEnabled {
            get => _MTC_Addr_1_Set_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_1_Set_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_1_Set_DetectedIsSet;
        public bool MTC_Addr_1_Set_DetectedIsSet {
            get => _MTC_Addr_1_Set_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_1_Set_Detected;
        public byte MTC_Addr_1_Set_Detected {
            get => _MTC_Addr_1_Set_Detected;
            set => _ = Set(ref _MTC_Addr_1_Set_Detected, value);
        }
        
        private bool _MTC_Addr_1_Set_TypeIsSet;
        public bool MTC_Addr_1_Set_TypeIsSet {
            get => _MTC_Addr_1_Set_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_1_Set_Type;
        public UInt32 MTC_Addr_1_Set_Type {
            get => _MTC_Addr_1_Set_Type;
            set => _ = Set(ref _MTC_Addr_1_Set_Type, value);
        }
        
        private bool _MTC_Addr_1_Set_ENABLE_1IsSet;
        public bool MTC_Addr_1_Set_ENABLE_1IsSet {
            get => _MTC_Addr_1_Set_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_ENABLE_1;
        public Enabled MTC_Addr_1_Set_ENABLE_1 {
            get => _MTC_Addr_1_Set_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_1_Set_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_1_Set_ENABLE_2IsSet;
        public bool MTC_Addr_1_Set_ENABLE_2IsSet {
            get => _MTC_Addr_1_Set_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_ENABLE_2;
        public Enabled MTC_Addr_1_Set_ENABLE_2 {
            get => _MTC_Addr_1_Set_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_1_Set_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_I2C_1IsSet;
        public bool MTC_Addr_1_Set_SEL_I2C_1IsSet {
            get => _MTC_Addr_1_Set_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_I2C_1;
        public Enabled MTC_Addr_1_Set_SEL_I2C_1 {
            get => _MTC_Addr_1_Set_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_I2C_2IsSet;
        public bool MTC_Addr_1_Set_SEL_I2C_2IsSet {
            get => _MTC_Addr_1_Set_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_I2C_2;
        public Enabled MTC_Addr_1_Set_SEL_I2C_2 {
            get => _MTC_Addr_1_Set_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_UART_1IsSet;
        public bool MTC_Addr_1_Set_SEL_UART_1IsSet {
            get => _MTC_Addr_1_Set_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_UART_1;
        public Enabled MTC_Addr_1_Set_SEL_UART_1 {
            get => _MTC_Addr_1_Set_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_UART_2IsSet;
        public bool MTC_Addr_1_Set_SEL_UART_2IsSet {
            get => _MTC_Addr_1_Set_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_UART_2;
        public Enabled MTC_Addr_1_Set_SEL_UART_2 {
            get => _MTC_Addr_1_Set_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_UART_3IsSet;
        public bool MTC_Addr_1_Set_SEL_UART_3IsSet {
            get => _MTC_Addr_1_Set_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_UART_3;
        public Enabled MTC_Addr_1_Set_SEL_UART_3 {
            get => _MTC_Addr_1_Set_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_UART_4IsSet;
        public bool MTC_Addr_1_Set_SEL_UART_4IsSet {
            get => _MTC_Addr_1_Set_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_UART_4;
        public Enabled MTC_Addr_1_Set_SEL_UART_4 {
            get => _MTC_Addr_1_Set_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_UART_5IsSet;
        public bool MTC_Addr_1_Set_SEL_UART_5IsSet {
            get => _MTC_Addr_1_Set_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_UART_5;
        public Enabled MTC_Addr_1_Set_SEL_UART_5 {
            get => _MTC_Addr_1_Set_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_UART_6IsSet;
        public bool MTC_Addr_1_Set_SEL_UART_6IsSet {
            get => _MTC_Addr_1_Set_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_UART_6;
        public Enabled MTC_Addr_1_Set_SEL_UART_6 {
            get => _MTC_Addr_1_Set_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_VBATIsSet;
        public bool MTC_Addr_1_Set_SEL_VBATIsSet {
            get => _MTC_Addr_1_Set_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_VBAT;
        public Enabled MTC_Addr_1_Set_SEL_VBAT {
            get => _MTC_Addr_1_Set_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_1_Set_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_1_Set_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_VBAT_ALT;
        public Enabled MTC_Addr_1_Set_SEL_VBAT_ALT {
            get => _MTC_Addr_1_Set_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_1_Set_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_1_Set_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_1_Set_SEL_VBAT_FPGA {
            get => _MTC_Addr_1_Set_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_nRESET_1IsSet;
        public bool MTC_Addr_1_Set_SEL_nRESET_1IsSet {
            get => _MTC_Addr_1_Set_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_nRESET_1;
        public Enabled MTC_Addr_1_Set_SEL_nRESET_1 {
            get => _MTC_Addr_1_Set_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_nRESET_2IsSet;
        public bool MTC_Addr_1_Set_SEL_nRESET_2IsSet {
            get => _MTC_Addr_1_Set_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_nRESET_2;
        public Enabled MTC_Addr_1_Set_SEL_nRESET_2 {
            get => _MTC_Addr_1_Set_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_nRESET_3IsSet;
        public bool MTC_Addr_1_Set_SEL_nRESET_3IsSet {
            get => _MTC_Addr_1_Set_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_nRESET_3;
        public Enabled MTC_Addr_1_Set_SEL_nRESET_3 {
            get => _MTC_Addr_1_Set_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_CS_1IsSet;
        public bool MTC_Addr_1_Set_SEL_CS_1IsSet {
            get => _MTC_Addr_1_Set_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_CS_1;
        public Enabled MTC_Addr_1_Set_SEL_CS_1 {
            get => _MTC_Addr_1_Set_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_CS_2IsSet;
        public bool MTC_Addr_1_Set_SEL_CS_2IsSet {
            get => _MTC_Addr_1_Set_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_CS_2;
        public Enabled MTC_Addr_1_Set_SEL_CS_2 {
            get => _MTC_Addr_1_Set_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_CS_3IsSet;
        public bool MTC_Addr_1_Set_SEL_CS_3IsSet {
            get => _MTC_Addr_1_Set_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_CS_3;
        public Enabled MTC_Addr_1_Set_SEL_CS_3 {
            get => _MTC_Addr_1_Set_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_CS_4IsSet;
        public bool MTC_Addr_1_Set_SEL_CS_4IsSet {
            get => _MTC_Addr_1_Set_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_CS_4;
        public Enabled MTC_Addr_1_Set_SEL_CS_4 {
            get => _MTC_Addr_1_Set_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_CS_5IsSet;
        public bool MTC_Addr_1_Set_SEL_CS_5IsSet {
            get => _MTC_Addr_1_Set_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_CS_5;
        public Enabled MTC_Addr_1_Set_SEL_CS_5 {
            get => _MTC_Addr_1_Set_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_CS_6IsSet;
        public bool MTC_Addr_1_Set_SEL_CS_6IsSet {
            get => _MTC_Addr_1_Set_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_CS_6;
        public Enabled MTC_Addr_1_Set_SEL_CS_6 {
            get => _MTC_Addr_1_Set_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_SPI_1IsSet;
        public bool MTC_Addr_1_Set_SEL_SPI_1IsSet {
            get => _MTC_Addr_1_Set_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_SPI_1;
        public Enabled MTC_Addr_1_Set_SEL_SPI_1 {
            get => _MTC_Addr_1_Set_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_SPI_2IsSet;
        public bool MTC_Addr_1_Set_SEL_SPI_2IsSet {
            get => _MTC_Addr_1_Set_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_SPI_2;
        public Enabled MTC_Addr_1_Set_SEL_SPI_2 {
            get => _MTC_Addr_1_Set_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_CAN_1IsSet;
        public bool MTC_Addr_1_Set_SEL_CAN_1IsSet {
            get => _MTC_Addr_1_Set_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_CAN_1;
        public Enabled MTC_Addr_1_Set_SEL_CAN_1 {
            get => _MTC_Addr_1_Set_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_CAN_2IsSet;
        public bool MTC_Addr_1_Set_SEL_CAN_2IsSet {
            get => _MTC_Addr_1_Set_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_CAN_2;
        public Enabled MTC_Addr_1_Set_SEL_CAN_2 {
            get => _MTC_Addr_1_Set_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_CAN_3IsSet;
        public bool MTC_Addr_1_Set_SEL_CAN_3IsSet {
            get => _MTC_Addr_1_Set_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_CAN_3;
        public Enabled MTC_Addr_1_Set_SEL_CAN_3 {
            get => _MTC_Addr_1_Set_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_1_Set_SEL_RS422IsSet;
        public bool MTC_Addr_1_Set_SEL_RS422IsSet {
            get => _MTC_Addr_1_Set_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Set_SEL_RS422;
        public Enabled MTC_Addr_1_Set_SEL_RS422 {
            get => _MTC_Addr_1_Set_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_1_Set_SEL_RS422, value);
        }
        
        /*************** Properties for MTC_Addr_1_Clear register ********************************/
        private bool _MTC_Addr_1_Clear_ScanEnabledIsSet;
        public bool MTC_Addr_1_Clear_ScanEnabledIsSet {
            get => _MTC_Addr_1_Clear_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_ScanEnabled;
        public Enabled MTC_Addr_1_Clear_ScanEnabled {
            get => _MTC_Addr_1_Clear_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_1_Clear_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_1_Clear_DetectedIsSet;
        public bool MTC_Addr_1_Clear_DetectedIsSet {
            get => _MTC_Addr_1_Clear_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_1_Clear_Detected;
        public byte MTC_Addr_1_Clear_Detected {
            get => _MTC_Addr_1_Clear_Detected;
            set => _ = Set(ref _MTC_Addr_1_Clear_Detected, value);
        }
        
        private bool _MTC_Addr_1_Clear_TypeIsSet;
        public bool MTC_Addr_1_Clear_TypeIsSet {
            get => _MTC_Addr_1_Clear_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_1_Clear_Type;
        public UInt32 MTC_Addr_1_Clear_Type {
            get => _MTC_Addr_1_Clear_Type;
            set => _ = Set(ref _MTC_Addr_1_Clear_Type, value);
        }
        
        private bool _MTC_Addr_1_Clear_ENABLE_1IsSet;
        public bool MTC_Addr_1_Clear_ENABLE_1IsSet {
            get => _MTC_Addr_1_Clear_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_ENABLE_1;
        public Enabled MTC_Addr_1_Clear_ENABLE_1 {
            get => _MTC_Addr_1_Clear_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_1_Clear_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_1_Clear_ENABLE_2IsSet;
        public bool MTC_Addr_1_Clear_ENABLE_2IsSet {
            get => _MTC_Addr_1_Clear_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_ENABLE_2;
        public Enabled MTC_Addr_1_Clear_ENABLE_2 {
            get => _MTC_Addr_1_Clear_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_1_Clear_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_I2C_1IsSet;
        public bool MTC_Addr_1_Clear_SEL_I2C_1IsSet {
            get => _MTC_Addr_1_Clear_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_I2C_1;
        public Enabled MTC_Addr_1_Clear_SEL_I2C_1 {
            get => _MTC_Addr_1_Clear_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_I2C_2IsSet;
        public bool MTC_Addr_1_Clear_SEL_I2C_2IsSet {
            get => _MTC_Addr_1_Clear_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_I2C_2;
        public Enabled MTC_Addr_1_Clear_SEL_I2C_2 {
            get => _MTC_Addr_1_Clear_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_UART_1IsSet;
        public bool MTC_Addr_1_Clear_SEL_UART_1IsSet {
            get => _MTC_Addr_1_Clear_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_UART_1;
        public Enabled MTC_Addr_1_Clear_SEL_UART_1 {
            get => _MTC_Addr_1_Clear_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_UART_2IsSet;
        public bool MTC_Addr_1_Clear_SEL_UART_2IsSet {
            get => _MTC_Addr_1_Clear_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_UART_2;
        public Enabled MTC_Addr_1_Clear_SEL_UART_2 {
            get => _MTC_Addr_1_Clear_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_UART_3IsSet;
        public bool MTC_Addr_1_Clear_SEL_UART_3IsSet {
            get => _MTC_Addr_1_Clear_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_UART_3;
        public Enabled MTC_Addr_1_Clear_SEL_UART_3 {
            get => _MTC_Addr_1_Clear_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_UART_4IsSet;
        public bool MTC_Addr_1_Clear_SEL_UART_4IsSet {
            get => _MTC_Addr_1_Clear_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_UART_4;
        public Enabled MTC_Addr_1_Clear_SEL_UART_4 {
            get => _MTC_Addr_1_Clear_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_UART_5IsSet;
        public bool MTC_Addr_1_Clear_SEL_UART_5IsSet {
            get => _MTC_Addr_1_Clear_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_UART_5;
        public Enabled MTC_Addr_1_Clear_SEL_UART_5 {
            get => _MTC_Addr_1_Clear_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_UART_6IsSet;
        public bool MTC_Addr_1_Clear_SEL_UART_6IsSet {
            get => _MTC_Addr_1_Clear_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_UART_6;
        public Enabled MTC_Addr_1_Clear_SEL_UART_6 {
            get => _MTC_Addr_1_Clear_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_VBATIsSet;
        public bool MTC_Addr_1_Clear_SEL_VBATIsSet {
            get => _MTC_Addr_1_Clear_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_VBAT;
        public Enabled MTC_Addr_1_Clear_SEL_VBAT {
            get => _MTC_Addr_1_Clear_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_1_Clear_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_1_Clear_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_VBAT_ALT;
        public Enabled MTC_Addr_1_Clear_SEL_VBAT_ALT {
            get => _MTC_Addr_1_Clear_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_1_Clear_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_1_Clear_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_1_Clear_SEL_VBAT_FPGA {
            get => _MTC_Addr_1_Clear_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_nRESET_1IsSet;
        public bool MTC_Addr_1_Clear_SEL_nRESET_1IsSet {
            get => _MTC_Addr_1_Clear_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_nRESET_1;
        public Enabled MTC_Addr_1_Clear_SEL_nRESET_1 {
            get => _MTC_Addr_1_Clear_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_nRESET_2IsSet;
        public bool MTC_Addr_1_Clear_SEL_nRESET_2IsSet {
            get => _MTC_Addr_1_Clear_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_nRESET_2;
        public Enabled MTC_Addr_1_Clear_SEL_nRESET_2 {
            get => _MTC_Addr_1_Clear_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_nRESET_3IsSet;
        public bool MTC_Addr_1_Clear_SEL_nRESET_3IsSet {
            get => _MTC_Addr_1_Clear_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_nRESET_3;
        public Enabled MTC_Addr_1_Clear_SEL_nRESET_3 {
            get => _MTC_Addr_1_Clear_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_CS_1IsSet;
        public bool MTC_Addr_1_Clear_SEL_CS_1IsSet {
            get => _MTC_Addr_1_Clear_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_CS_1;
        public Enabled MTC_Addr_1_Clear_SEL_CS_1 {
            get => _MTC_Addr_1_Clear_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_CS_2IsSet;
        public bool MTC_Addr_1_Clear_SEL_CS_2IsSet {
            get => _MTC_Addr_1_Clear_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_CS_2;
        public Enabled MTC_Addr_1_Clear_SEL_CS_2 {
            get => _MTC_Addr_1_Clear_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_CS_3IsSet;
        public bool MTC_Addr_1_Clear_SEL_CS_3IsSet {
            get => _MTC_Addr_1_Clear_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_CS_3;
        public Enabled MTC_Addr_1_Clear_SEL_CS_3 {
            get => _MTC_Addr_1_Clear_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_CS_4IsSet;
        public bool MTC_Addr_1_Clear_SEL_CS_4IsSet {
            get => _MTC_Addr_1_Clear_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_CS_4;
        public Enabled MTC_Addr_1_Clear_SEL_CS_4 {
            get => _MTC_Addr_1_Clear_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_CS_5IsSet;
        public bool MTC_Addr_1_Clear_SEL_CS_5IsSet {
            get => _MTC_Addr_1_Clear_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_CS_5;
        public Enabled MTC_Addr_1_Clear_SEL_CS_5 {
            get => _MTC_Addr_1_Clear_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_CS_6IsSet;
        public bool MTC_Addr_1_Clear_SEL_CS_6IsSet {
            get => _MTC_Addr_1_Clear_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_CS_6;
        public Enabled MTC_Addr_1_Clear_SEL_CS_6 {
            get => _MTC_Addr_1_Clear_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_SPI_1IsSet;
        public bool MTC_Addr_1_Clear_SEL_SPI_1IsSet {
            get => _MTC_Addr_1_Clear_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_SPI_1;
        public Enabled MTC_Addr_1_Clear_SEL_SPI_1 {
            get => _MTC_Addr_1_Clear_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_SPI_2IsSet;
        public bool MTC_Addr_1_Clear_SEL_SPI_2IsSet {
            get => _MTC_Addr_1_Clear_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_SPI_2;
        public Enabled MTC_Addr_1_Clear_SEL_SPI_2 {
            get => _MTC_Addr_1_Clear_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_CAN_1IsSet;
        public bool MTC_Addr_1_Clear_SEL_CAN_1IsSet {
            get => _MTC_Addr_1_Clear_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_CAN_1;
        public Enabled MTC_Addr_1_Clear_SEL_CAN_1 {
            get => _MTC_Addr_1_Clear_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_CAN_2IsSet;
        public bool MTC_Addr_1_Clear_SEL_CAN_2IsSet {
            get => _MTC_Addr_1_Clear_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_CAN_2;
        public Enabled MTC_Addr_1_Clear_SEL_CAN_2 {
            get => _MTC_Addr_1_Clear_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_CAN_3IsSet;
        public bool MTC_Addr_1_Clear_SEL_CAN_3IsSet {
            get => _MTC_Addr_1_Clear_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_CAN_3;
        public Enabled MTC_Addr_1_Clear_SEL_CAN_3 {
            get => _MTC_Addr_1_Clear_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_1_Clear_SEL_RS422IsSet;
        public bool MTC_Addr_1_Clear_SEL_RS422IsSet {
            get => _MTC_Addr_1_Clear_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_1_Clear_SEL_RS422;
        public Enabled MTC_Addr_1_Clear_SEL_RS422 {
            get => _MTC_Addr_1_Clear_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_1_Clear_SEL_RS422, value);
        }
        
        /*************** Properties for MTC_Addr_2 register **************************************/
        private bool _MTC_Addr_2_ScanEnabledIsSet;
        public bool MTC_Addr_2_ScanEnabledIsSet {
            get => _MTC_Addr_2_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_2_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_2_ScanEnabled;
        public Enabled MTC_Addr_2_ScanEnabled {
            get => _MTC_Addr_2_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_2_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_2_DetectedIsSet;
        public bool MTC_Addr_2_DetectedIsSet {
            get => _MTC_Addr_2_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_2_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_2_Detected;
        public byte MTC_Addr_2_Detected {
            get => _MTC_Addr_2_Detected;
            set => _ = Set(ref _MTC_Addr_2_Detected, value);
        }
        
        private bool _MTC_Addr_2_TypeIsSet;
        public bool MTC_Addr_2_TypeIsSet {
            get => _MTC_Addr_2_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_2_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_2_Type;
        public UInt32 MTC_Addr_2_Type {
            get => _MTC_Addr_2_Type;
            set => _ = Set(ref _MTC_Addr_2_Type, value);
        }
        
        private bool _MTC_Addr_2_ENABLE_1IsSet;
        public bool MTC_Addr_2_ENABLE_1IsSet {
            get => _MTC_Addr_2_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_ENABLE_1;
        public Enabled MTC_Addr_2_ENABLE_1 {
            get => _MTC_Addr_2_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_2_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_2_ENABLE_2IsSet;
        public bool MTC_Addr_2_ENABLE_2IsSet {
            get => _MTC_Addr_2_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_ENABLE_2;
        public Enabled MTC_Addr_2_ENABLE_2 {
            get => _MTC_Addr_2_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_2_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_2_SEL_I2C_1IsSet;
        public bool MTC_Addr_2_SEL_I2C_1IsSet {
            get => _MTC_Addr_2_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_I2C_1;
        public Enabled MTC_Addr_2_SEL_I2C_1 {
            get => _MTC_Addr_2_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_2_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_2_SEL_I2C_2IsSet;
        public bool MTC_Addr_2_SEL_I2C_2IsSet {
            get => _MTC_Addr_2_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_I2C_2;
        public Enabled MTC_Addr_2_SEL_I2C_2 {
            get => _MTC_Addr_2_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_2_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_2_SEL_UART_1IsSet;
        public bool MTC_Addr_2_SEL_UART_1IsSet {
            get => _MTC_Addr_2_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_UART_1;
        public Enabled MTC_Addr_2_SEL_UART_1 {
            get => _MTC_Addr_2_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_2_SEL_UART_2IsSet;
        public bool MTC_Addr_2_SEL_UART_2IsSet {
            get => _MTC_Addr_2_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_UART_2;
        public Enabled MTC_Addr_2_SEL_UART_2 {
            get => _MTC_Addr_2_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_2_SEL_UART_3IsSet;
        public bool MTC_Addr_2_SEL_UART_3IsSet {
            get => _MTC_Addr_2_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_UART_3;
        public Enabled MTC_Addr_2_SEL_UART_3 {
            get => _MTC_Addr_2_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_2_SEL_UART_4IsSet;
        public bool MTC_Addr_2_SEL_UART_4IsSet {
            get => _MTC_Addr_2_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_UART_4;
        public Enabled MTC_Addr_2_SEL_UART_4 {
            get => _MTC_Addr_2_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_2_SEL_UART_5IsSet;
        public bool MTC_Addr_2_SEL_UART_5IsSet {
            get => _MTC_Addr_2_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_UART_5;
        public Enabled MTC_Addr_2_SEL_UART_5 {
            get => _MTC_Addr_2_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_2_SEL_UART_6IsSet;
        public bool MTC_Addr_2_SEL_UART_6IsSet {
            get => _MTC_Addr_2_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_UART_6;
        public Enabled MTC_Addr_2_SEL_UART_6 {
            get => _MTC_Addr_2_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_2_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_2_SEL_VBATIsSet;
        public bool MTC_Addr_2_SEL_VBATIsSet {
            get => _MTC_Addr_2_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_VBAT;
        public Enabled MTC_Addr_2_SEL_VBAT {
            get => _MTC_Addr_2_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_2_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_2_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_2_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_2_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_VBAT_ALT;
        public Enabled MTC_Addr_2_SEL_VBAT_ALT {
            get => _MTC_Addr_2_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_2_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_2_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_2_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_2_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_2_SEL_VBAT_FPGA {
            get => _MTC_Addr_2_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_2_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_2_SEL_nRESET_1IsSet;
        public bool MTC_Addr_2_SEL_nRESET_1IsSet {
            get => _MTC_Addr_2_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_nRESET_1;
        public Enabled MTC_Addr_2_SEL_nRESET_1 {
            get => _MTC_Addr_2_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_2_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_2_SEL_nRESET_2IsSet;
        public bool MTC_Addr_2_SEL_nRESET_2IsSet {
            get => _MTC_Addr_2_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_nRESET_2;
        public Enabled MTC_Addr_2_SEL_nRESET_2 {
            get => _MTC_Addr_2_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_2_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_2_SEL_nRESET_3IsSet;
        public bool MTC_Addr_2_SEL_nRESET_3IsSet {
            get => _MTC_Addr_2_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_nRESET_3;
        public Enabled MTC_Addr_2_SEL_nRESET_3 {
            get => _MTC_Addr_2_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_2_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_2_SEL_CS_1IsSet;
        public bool MTC_Addr_2_SEL_CS_1IsSet {
            get => _MTC_Addr_2_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_CS_1;
        public Enabled MTC_Addr_2_SEL_CS_1 {
            get => _MTC_Addr_2_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_2_SEL_CS_2IsSet;
        public bool MTC_Addr_2_SEL_CS_2IsSet {
            get => _MTC_Addr_2_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_CS_2;
        public Enabled MTC_Addr_2_SEL_CS_2 {
            get => _MTC_Addr_2_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_2_SEL_CS_3IsSet;
        public bool MTC_Addr_2_SEL_CS_3IsSet {
            get => _MTC_Addr_2_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_CS_3;
        public Enabled MTC_Addr_2_SEL_CS_3 {
            get => _MTC_Addr_2_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_2_SEL_CS_4IsSet;
        public bool MTC_Addr_2_SEL_CS_4IsSet {
            get => _MTC_Addr_2_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_CS_4;
        public Enabled MTC_Addr_2_SEL_CS_4 {
            get => _MTC_Addr_2_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_2_SEL_CS_5IsSet;
        public bool MTC_Addr_2_SEL_CS_5IsSet {
            get => _MTC_Addr_2_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_CS_5;
        public Enabled MTC_Addr_2_SEL_CS_5 {
            get => _MTC_Addr_2_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_2_SEL_CS_6IsSet;
        public bool MTC_Addr_2_SEL_CS_6IsSet {
            get => _MTC_Addr_2_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_CS_6;
        public Enabled MTC_Addr_2_SEL_CS_6 {
            get => _MTC_Addr_2_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_2_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_2_SEL_SPI_1IsSet;
        public bool MTC_Addr_2_SEL_SPI_1IsSet {
            get => _MTC_Addr_2_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_SPI_1;
        public Enabled MTC_Addr_2_SEL_SPI_1 {
            get => _MTC_Addr_2_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_2_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_2_SEL_SPI_2IsSet;
        public bool MTC_Addr_2_SEL_SPI_2IsSet {
            get => _MTC_Addr_2_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_SPI_2;
        public Enabled MTC_Addr_2_SEL_SPI_2 {
            get => _MTC_Addr_2_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_2_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_2_SEL_CAN_1IsSet;
        public bool MTC_Addr_2_SEL_CAN_1IsSet {
            get => _MTC_Addr_2_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_CAN_1;
        public Enabled MTC_Addr_2_SEL_CAN_1 {
            get => _MTC_Addr_2_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_2_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_2_SEL_CAN_2IsSet;
        public bool MTC_Addr_2_SEL_CAN_2IsSet {
            get => _MTC_Addr_2_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_CAN_2;
        public Enabled MTC_Addr_2_SEL_CAN_2 {
            get => _MTC_Addr_2_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_2_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_2_SEL_CAN_3IsSet;
        public bool MTC_Addr_2_SEL_CAN_3IsSet {
            get => _MTC_Addr_2_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_CAN_3;
        public Enabled MTC_Addr_2_SEL_CAN_3 {
            get => _MTC_Addr_2_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_2_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_2_SEL_RS422IsSet;
        public bool MTC_Addr_2_SEL_RS422IsSet {
            get => _MTC_Addr_2_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_2_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_2_SEL_RS422;
        public Enabled MTC_Addr_2_SEL_RS422 {
            get => _MTC_Addr_2_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_2_SEL_RS422, value);
        }
        
        /*************** Properties for MTC_Addr_2_Set register **********************************/
        private bool _MTC_Addr_2_Set_ScanEnabledIsSet;
        public bool MTC_Addr_2_Set_ScanEnabledIsSet {
            get => _MTC_Addr_2_Set_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_ScanEnabled;
        public Enabled MTC_Addr_2_Set_ScanEnabled {
            get => _MTC_Addr_2_Set_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_2_Set_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_2_Set_DetectedIsSet;
        public bool MTC_Addr_2_Set_DetectedIsSet {
            get => _MTC_Addr_2_Set_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_2_Set_Detected;
        public byte MTC_Addr_2_Set_Detected {
            get => _MTC_Addr_2_Set_Detected;
            set => _ = Set(ref _MTC_Addr_2_Set_Detected, value);
        }
        
        private bool _MTC_Addr_2_Set_TypeIsSet;
        public bool MTC_Addr_2_Set_TypeIsSet {
            get => _MTC_Addr_2_Set_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_2_Set_Type;
        public UInt32 MTC_Addr_2_Set_Type {
            get => _MTC_Addr_2_Set_Type;
            set => _ = Set(ref _MTC_Addr_2_Set_Type, value);
        }
        
        private bool _MTC_Addr_2_Set_ENABLE_1IsSet;
        public bool MTC_Addr_2_Set_ENABLE_1IsSet {
            get => _MTC_Addr_2_Set_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_ENABLE_1;
        public Enabled MTC_Addr_2_Set_ENABLE_1 {
            get => _MTC_Addr_2_Set_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_2_Set_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_2_Set_ENABLE_2IsSet;
        public bool MTC_Addr_2_Set_ENABLE_2IsSet {
            get => _MTC_Addr_2_Set_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_ENABLE_2;
        public Enabled MTC_Addr_2_Set_ENABLE_2 {
            get => _MTC_Addr_2_Set_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_2_Set_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_I2C_1IsSet;
        public bool MTC_Addr_2_Set_SEL_I2C_1IsSet {
            get => _MTC_Addr_2_Set_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_I2C_1;
        public Enabled MTC_Addr_2_Set_SEL_I2C_1 {
            get => _MTC_Addr_2_Set_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_I2C_2IsSet;
        public bool MTC_Addr_2_Set_SEL_I2C_2IsSet {
            get => _MTC_Addr_2_Set_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_I2C_2;
        public Enabled MTC_Addr_2_Set_SEL_I2C_2 {
            get => _MTC_Addr_2_Set_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_UART_1IsSet;
        public bool MTC_Addr_2_Set_SEL_UART_1IsSet {
            get => _MTC_Addr_2_Set_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_UART_1;
        public Enabled MTC_Addr_2_Set_SEL_UART_1 {
            get => _MTC_Addr_2_Set_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_UART_2IsSet;
        public bool MTC_Addr_2_Set_SEL_UART_2IsSet {
            get => _MTC_Addr_2_Set_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_UART_2;
        public Enabled MTC_Addr_2_Set_SEL_UART_2 {
            get => _MTC_Addr_2_Set_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_UART_3IsSet;
        public bool MTC_Addr_2_Set_SEL_UART_3IsSet {
            get => _MTC_Addr_2_Set_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_UART_3;
        public Enabled MTC_Addr_2_Set_SEL_UART_3 {
            get => _MTC_Addr_2_Set_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_UART_4IsSet;
        public bool MTC_Addr_2_Set_SEL_UART_4IsSet {
            get => _MTC_Addr_2_Set_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_UART_4;
        public Enabled MTC_Addr_2_Set_SEL_UART_4 {
            get => _MTC_Addr_2_Set_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_UART_5IsSet;
        public bool MTC_Addr_2_Set_SEL_UART_5IsSet {
            get => _MTC_Addr_2_Set_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_UART_5;
        public Enabled MTC_Addr_2_Set_SEL_UART_5 {
            get => _MTC_Addr_2_Set_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_UART_6IsSet;
        public bool MTC_Addr_2_Set_SEL_UART_6IsSet {
            get => _MTC_Addr_2_Set_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_UART_6;
        public Enabled MTC_Addr_2_Set_SEL_UART_6 {
            get => _MTC_Addr_2_Set_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_VBATIsSet;
        public bool MTC_Addr_2_Set_SEL_VBATIsSet {
            get => _MTC_Addr_2_Set_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_VBAT;
        public Enabled MTC_Addr_2_Set_SEL_VBAT {
            get => _MTC_Addr_2_Set_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_2_Set_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_2_Set_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_VBAT_ALT;
        public Enabled MTC_Addr_2_Set_SEL_VBAT_ALT {
            get => _MTC_Addr_2_Set_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_2_Set_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_2_Set_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_2_Set_SEL_VBAT_FPGA {
            get => _MTC_Addr_2_Set_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_nRESET_1IsSet;
        public bool MTC_Addr_2_Set_SEL_nRESET_1IsSet {
            get => _MTC_Addr_2_Set_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_nRESET_1;
        public Enabled MTC_Addr_2_Set_SEL_nRESET_1 {
            get => _MTC_Addr_2_Set_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_nRESET_2IsSet;
        public bool MTC_Addr_2_Set_SEL_nRESET_2IsSet {
            get => _MTC_Addr_2_Set_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_nRESET_2;
        public Enabled MTC_Addr_2_Set_SEL_nRESET_2 {
            get => _MTC_Addr_2_Set_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_nRESET_3IsSet;
        public bool MTC_Addr_2_Set_SEL_nRESET_3IsSet {
            get => _MTC_Addr_2_Set_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_nRESET_3;
        public Enabled MTC_Addr_2_Set_SEL_nRESET_3 {
            get => _MTC_Addr_2_Set_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_CS_1IsSet;
        public bool MTC_Addr_2_Set_SEL_CS_1IsSet {
            get => _MTC_Addr_2_Set_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_CS_1;
        public Enabled MTC_Addr_2_Set_SEL_CS_1 {
            get => _MTC_Addr_2_Set_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_CS_2IsSet;
        public bool MTC_Addr_2_Set_SEL_CS_2IsSet {
            get => _MTC_Addr_2_Set_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_CS_2;
        public Enabled MTC_Addr_2_Set_SEL_CS_2 {
            get => _MTC_Addr_2_Set_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_CS_3IsSet;
        public bool MTC_Addr_2_Set_SEL_CS_3IsSet {
            get => _MTC_Addr_2_Set_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_CS_3;
        public Enabled MTC_Addr_2_Set_SEL_CS_3 {
            get => _MTC_Addr_2_Set_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_CS_4IsSet;
        public bool MTC_Addr_2_Set_SEL_CS_4IsSet {
            get => _MTC_Addr_2_Set_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_CS_4;
        public Enabled MTC_Addr_2_Set_SEL_CS_4 {
            get => _MTC_Addr_2_Set_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_CS_5IsSet;
        public bool MTC_Addr_2_Set_SEL_CS_5IsSet {
            get => _MTC_Addr_2_Set_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_CS_5;
        public Enabled MTC_Addr_2_Set_SEL_CS_5 {
            get => _MTC_Addr_2_Set_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_CS_6IsSet;
        public bool MTC_Addr_2_Set_SEL_CS_6IsSet {
            get => _MTC_Addr_2_Set_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_CS_6;
        public Enabled MTC_Addr_2_Set_SEL_CS_6 {
            get => _MTC_Addr_2_Set_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_SPI_1IsSet;
        public bool MTC_Addr_2_Set_SEL_SPI_1IsSet {
            get => _MTC_Addr_2_Set_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_SPI_1;
        public Enabled MTC_Addr_2_Set_SEL_SPI_1 {
            get => _MTC_Addr_2_Set_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_SPI_2IsSet;
        public bool MTC_Addr_2_Set_SEL_SPI_2IsSet {
            get => _MTC_Addr_2_Set_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_SPI_2;
        public Enabled MTC_Addr_2_Set_SEL_SPI_2 {
            get => _MTC_Addr_2_Set_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_CAN_1IsSet;
        public bool MTC_Addr_2_Set_SEL_CAN_1IsSet {
            get => _MTC_Addr_2_Set_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_CAN_1;
        public Enabled MTC_Addr_2_Set_SEL_CAN_1 {
            get => _MTC_Addr_2_Set_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_CAN_2IsSet;
        public bool MTC_Addr_2_Set_SEL_CAN_2IsSet {
            get => _MTC_Addr_2_Set_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_CAN_2;
        public Enabled MTC_Addr_2_Set_SEL_CAN_2 {
            get => _MTC_Addr_2_Set_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_CAN_3IsSet;
        public bool MTC_Addr_2_Set_SEL_CAN_3IsSet {
            get => _MTC_Addr_2_Set_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_CAN_3;
        public Enabled MTC_Addr_2_Set_SEL_CAN_3 {
            get => _MTC_Addr_2_Set_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_2_Set_SEL_RS422IsSet;
        public bool MTC_Addr_2_Set_SEL_RS422IsSet {
            get => _MTC_Addr_2_Set_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Set_SEL_RS422;
        public Enabled MTC_Addr_2_Set_SEL_RS422 {
            get => _MTC_Addr_2_Set_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_2_Set_SEL_RS422, value);
        }
        
        /*************** Properties for MTC_Addr_2_Clear register ********************************/
        private bool _MTC_Addr_2_Clear_ScanEnabledIsSet;
        public bool MTC_Addr_2_Clear_ScanEnabledIsSet {
            get => _MTC_Addr_2_Clear_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_ScanEnabled;
        public Enabled MTC_Addr_2_Clear_ScanEnabled {
            get => _MTC_Addr_2_Clear_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_2_Clear_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_2_Clear_DetectedIsSet;
        public bool MTC_Addr_2_Clear_DetectedIsSet {
            get => _MTC_Addr_2_Clear_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_2_Clear_Detected;
        public byte MTC_Addr_2_Clear_Detected {
            get => _MTC_Addr_2_Clear_Detected;
            set => _ = Set(ref _MTC_Addr_2_Clear_Detected, value);
        }
        
        private bool _MTC_Addr_2_Clear_TypeIsSet;
        public bool MTC_Addr_2_Clear_TypeIsSet {
            get => _MTC_Addr_2_Clear_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_2_Clear_Type;
        public UInt32 MTC_Addr_2_Clear_Type {
            get => _MTC_Addr_2_Clear_Type;
            set => _ = Set(ref _MTC_Addr_2_Clear_Type, value);
        }
        
        private bool _MTC_Addr_2_Clear_ENABLE_1IsSet;
        public bool MTC_Addr_2_Clear_ENABLE_1IsSet {
            get => _MTC_Addr_2_Clear_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_ENABLE_1;
        public Enabled MTC_Addr_2_Clear_ENABLE_1 {
            get => _MTC_Addr_2_Clear_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_2_Clear_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_2_Clear_ENABLE_2IsSet;
        public bool MTC_Addr_2_Clear_ENABLE_2IsSet {
            get => _MTC_Addr_2_Clear_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_ENABLE_2;
        public Enabled MTC_Addr_2_Clear_ENABLE_2 {
            get => _MTC_Addr_2_Clear_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_2_Clear_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_I2C_1IsSet;
        public bool MTC_Addr_2_Clear_SEL_I2C_1IsSet {
            get => _MTC_Addr_2_Clear_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_I2C_1;
        public Enabled MTC_Addr_2_Clear_SEL_I2C_1 {
            get => _MTC_Addr_2_Clear_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_I2C_2IsSet;
        public bool MTC_Addr_2_Clear_SEL_I2C_2IsSet {
            get => _MTC_Addr_2_Clear_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_I2C_2;
        public Enabled MTC_Addr_2_Clear_SEL_I2C_2 {
            get => _MTC_Addr_2_Clear_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_UART_1IsSet;
        public bool MTC_Addr_2_Clear_SEL_UART_1IsSet {
            get => _MTC_Addr_2_Clear_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_UART_1;
        public Enabled MTC_Addr_2_Clear_SEL_UART_1 {
            get => _MTC_Addr_2_Clear_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_UART_2IsSet;
        public bool MTC_Addr_2_Clear_SEL_UART_2IsSet {
            get => _MTC_Addr_2_Clear_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_UART_2;
        public Enabled MTC_Addr_2_Clear_SEL_UART_2 {
            get => _MTC_Addr_2_Clear_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_UART_3IsSet;
        public bool MTC_Addr_2_Clear_SEL_UART_3IsSet {
            get => _MTC_Addr_2_Clear_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_UART_3;
        public Enabled MTC_Addr_2_Clear_SEL_UART_3 {
            get => _MTC_Addr_2_Clear_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_UART_4IsSet;
        public bool MTC_Addr_2_Clear_SEL_UART_4IsSet {
            get => _MTC_Addr_2_Clear_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_UART_4;
        public Enabled MTC_Addr_2_Clear_SEL_UART_4 {
            get => _MTC_Addr_2_Clear_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_UART_5IsSet;
        public bool MTC_Addr_2_Clear_SEL_UART_5IsSet {
            get => _MTC_Addr_2_Clear_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_UART_5;
        public Enabled MTC_Addr_2_Clear_SEL_UART_5 {
            get => _MTC_Addr_2_Clear_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_UART_6IsSet;
        public bool MTC_Addr_2_Clear_SEL_UART_6IsSet {
            get => _MTC_Addr_2_Clear_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_UART_6;
        public Enabled MTC_Addr_2_Clear_SEL_UART_6 {
            get => _MTC_Addr_2_Clear_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_VBATIsSet;
        public bool MTC_Addr_2_Clear_SEL_VBATIsSet {
            get => _MTC_Addr_2_Clear_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_VBAT;
        public Enabled MTC_Addr_2_Clear_SEL_VBAT {
            get => _MTC_Addr_2_Clear_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_2_Clear_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_2_Clear_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_VBAT_ALT;
        public Enabled MTC_Addr_2_Clear_SEL_VBAT_ALT {
            get => _MTC_Addr_2_Clear_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_2_Clear_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_2_Clear_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_2_Clear_SEL_VBAT_FPGA {
            get => _MTC_Addr_2_Clear_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_nRESET_1IsSet;
        public bool MTC_Addr_2_Clear_SEL_nRESET_1IsSet {
            get => _MTC_Addr_2_Clear_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_nRESET_1;
        public Enabled MTC_Addr_2_Clear_SEL_nRESET_1 {
            get => _MTC_Addr_2_Clear_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_nRESET_2IsSet;
        public bool MTC_Addr_2_Clear_SEL_nRESET_2IsSet {
            get => _MTC_Addr_2_Clear_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_nRESET_2;
        public Enabled MTC_Addr_2_Clear_SEL_nRESET_2 {
            get => _MTC_Addr_2_Clear_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_nRESET_3IsSet;
        public bool MTC_Addr_2_Clear_SEL_nRESET_3IsSet {
            get => _MTC_Addr_2_Clear_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_nRESET_3;
        public Enabled MTC_Addr_2_Clear_SEL_nRESET_3 {
            get => _MTC_Addr_2_Clear_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_CS_1IsSet;
        public bool MTC_Addr_2_Clear_SEL_CS_1IsSet {
            get => _MTC_Addr_2_Clear_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_CS_1;
        public Enabled MTC_Addr_2_Clear_SEL_CS_1 {
            get => _MTC_Addr_2_Clear_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_CS_2IsSet;
        public bool MTC_Addr_2_Clear_SEL_CS_2IsSet {
            get => _MTC_Addr_2_Clear_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_CS_2;
        public Enabled MTC_Addr_2_Clear_SEL_CS_2 {
            get => _MTC_Addr_2_Clear_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_CS_3IsSet;
        public bool MTC_Addr_2_Clear_SEL_CS_3IsSet {
            get => _MTC_Addr_2_Clear_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_CS_3;
        public Enabled MTC_Addr_2_Clear_SEL_CS_3 {
            get => _MTC_Addr_2_Clear_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_CS_4IsSet;
        public bool MTC_Addr_2_Clear_SEL_CS_4IsSet {
            get => _MTC_Addr_2_Clear_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_CS_4;
        public Enabled MTC_Addr_2_Clear_SEL_CS_4 {
            get => _MTC_Addr_2_Clear_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_CS_5IsSet;
        public bool MTC_Addr_2_Clear_SEL_CS_5IsSet {
            get => _MTC_Addr_2_Clear_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_CS_5;
        public Enabled MTC_Addr_2_Clear_SEL_CS_5 {
            get => _MTC_Addr_2_Clear_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_CS_6IsSet;
        public bool MTC_Addr_2_Clear_SEL_CS_6IsSet {
            get => _MTC_Addr_2_Clear_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_CS_6;
        public Enabled MTC_Addr_2_Clear_SEL_CS_6 {
            get => _MTC_Addr_2_Clear_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_SPI_1IsSet;
        public bool MTC_Addr_2_Clear_SEL_SPI_1IsSet {
            get => _MTC_Addr_2_Clear_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_SPI_1;
        public Enabled MTC_Addr_2_Clear_SEL_SPI_1 {
            get => _MTC_Addr_2_Clear_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_SPI_2IsSet;
        public bool MTC_Addr_2_Clear_SEL_SPI_2IsSet {
            get => _MTC_Addr_2_Clear_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_SPI_2;
        public Enabled MTC_Addr_2_Clear_SEL_SPI_2 {
            get => _MTC_Addr_2_Clear_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_CAN_1IsSet;
        public bool MTC_Addr_2_Clear_SEL_CAN_1IsSet {
            get => _MTC_Addr_2_Clear_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_CAN_1;
        public Enabled MTC_Addr_2_Clear_SEL_CAN_1 {
            get => _MTC_Addr_2_Clear_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_CAN_2IsSet;
        public bool MTC_Addr_2_Clear_SEL_CAN_2IsSet {
            get => _MTC_Addr_2_Clear_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_CAN_2;
        public Enabled MTC_Addr_2_Clear_SEL_CAN_2 {
            get => _MTC_Addr_2_Clear_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_CAN_3IsSet;
        public bool MTC_Addr_2_Clear_SEL_CAN_3IsSet {
            get => _MTC_Addr_2_Clear_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_CAN_3;
        public Enabled MTC_Addr_2_Clear_SEL_CAN_3 {
            get => _MTC_Addr_2_Clear_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_2_Clear_SEL_RS422IsSet;
        public bool MTC_Addr_2_Clear_SEL_RS422IsSet {
            get => _MTC_Addr_2_Clear_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_2_Clear_SEL_RS422;
        public Enabled MTC_Addr_2_Clear_SEL_RS422 {
            get => _MTC_Addr_2_Clear_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_2_Clear_SEL_RS422, value);
        }
        
        /*************** Properties for MTC_Addr_3 register **************************************/
        private bool _MTC_Addr_3_ScanEnabledIsSet;
        public bool MTC_Addr_3_ScanEnabledIsSet {
            get => _MTC_Addr_3_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_3_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_3_ScanEnabled;
        public Enabled MTC_Addr_3_ScanEnabled {
            get => _MTC_Addr_3_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_3_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_3_DetectedIsSet;
        public bool MTC_Addr_3_DetectedIsSet {
            get => _MTC_Addr_3_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_3_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_3_Detected;
        public byte MTC_Addr_3_Detected {
            get => _MTC_Addr_3_Detected;
            set => _ = Set(ref _MTC_Addr_3_Detected, value);
        }
        
        private bool _MTC_Addr_3_TypeIsSet;
        public bool MTC_Addr_3_TypeIsSet {
            get => _MTC_Addr_3_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_3_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_3_Type;
        public UInt32 MTC_Addr_3_Type {
            get => _MTC_Addr_3_Type;
            set => _ = Set(ref _MTC_Addr_3_Type, value);
        }
        
        private bool _MTC_Addr_3_ENABLE_1IsSet;
        public bool MTC_Addr_3_ENABLE_1IsSet {
            get => _MTC_Addr_3_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_ENABLE_1;
        public Enabled MTC_Addr_3_ENABLE_1 {
            get => _MTC_Addr_3_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_3_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_3_ENABLE_2IsSet;
        public bool MTC_Addr_3_ENABLE_2IsSet {
            get => _MTC_Addr_3_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_ENABLE_2;
        public Enabled MTC_Addr_3_ENABLE_2 {
            get => _MTC_Addr_3_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_3_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_3_SEL_I2C_1IsSet;
        public bool MTC_Addr_3_SEL_I2C_1IsSet {
            get => _MTC_Addr_3_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_I2C_1;
        public Enabled MTC_Addr_3_SEL_I2C_1 {
            get => _MTC_Addr_3_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_3_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_3_SEL_I2C_2IsSet;
        public bool MTC_Addr_3_SEL_I2C_2IsSet {
            get => _MTC_Addr_3_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_I2C_2;
        public Enabled MTC_Addr_3_SEL_I2C_2 {
            get => _MTC_Addr_3_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_3_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_3_SEL_UART_1IsSet;
        public bool MTC_Addr_3_SEL_UART_1IsSet {
            get => _MTC_Addr_3_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_UART_1;
        public Enabled MTC_Addr_3_SEL_UART_1 {
            get => _MTC_Addr_3_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_3_SEL_UART_2IsSet;
        public bool MTC_Addr_3_SEL_UART_2IsSet {
            get => _MTC_Addr_3_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_UART_2;
        public Enabled MTC_Addr_3_SEL_UART_2 {
            get => _MTC_Addr_3_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_3_SEL_UART_3IsSet;
        public bool MTC_Addr_3_SEL_UART_3IsSet {
            get => _MTC_Addr_3_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_UART_3;
        public Enabled MTC_Addr_3_SEL_UART_3 {
            get => _MTC_Addr_3_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_3_SEL_UART_4IsSet;
        public bool MTC_Addr_3_SEL_UART_4IsSet {
            get => _MTC_Addr_3_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_UART_4;
        public Enabled MTC_Addr_3_SEL_UART_4 {
            get => _MTC_Addr_3_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_3_SEL_UART_5IsSet;
        public bool MTC_Addr_3_SEL_UART_5IsSet {
            get => _MTC_Addr_3_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_UART_5;
        public Enabled MTC_Addr_3_SEL_UART_5 {
            get => _MTC_Addr_3_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_3_SEL_UART_6IsSet;
        public bool MTC_Addr_3_SEL_UART_6IsSet {
            get => _MTC_Addr_3_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_UART_6;
        public Enabled MTC_Addr_3_SEL_UART_6 {
            get => _MTC_Addr_3_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_3_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_3_SEL_VBATIsSet;
        public bool MTC_Addr_3_SEL_VBATIsSet {
            get => _MTC_Addr_3_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_VBAT;
        public Enabled MTC_Addr_3_SEL_VBAT {
            get => _MTC_Addr_3_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_3_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_3_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_3_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_3_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_VBAT_ALT;
        public Enabled MTC_Addr_3_SEL_VBAT_ALT {
            get => _MTC_Addr_3_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_3_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_3_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_3_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_3_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_3_SEL_VBAT_FPGA {
            get => _MTC_Addr_3_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_3_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_3_SEL_nRESET_1IsSet;
        public bool MTC_Addr_3_SEL_nRESET_1IsSet {
            get => _MTC_Addr_3_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_nRESET_1;
        public Enabled MTC_Addr_3_SEL_nRESET_1 {
            get => _MTC_Addr_3_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_3_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_3_SEL_nRESET_2IsSet;
        public bool MTC_Addr_3_SEL_nRESET_2IsSet {
            get => _MTC_Addr_3_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_nRESET_2;
        public Enabled MTC_Addr_3_SEL_nRESET_2 {
            get => _MTC_Addr_3_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_3_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_3_SEL_nRESET_3IsSet;
        public bool MTC_Addr_3_SEL_nRESET_3IsSet {
            get => _MTC_Addr_3_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_nRESET_3;
        public Enabled MTC_Addr_3_SEL_nRESET_3 {
            get => _MTC_Addr_3_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_3_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_3_SEL_CS_1IsSet;
        public bool MTC_Addr_3_SEL_CS_1IsSet {
            get => _MTC_Addr_3_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_CS_1;
        public Enabled MTC_Addr_3_SEL_CS_1 {
            get => _MTC_Addr_3_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_3_SEL_CS_2IsSet;
        public bool MTC_Addr_3_SEL_CS_2IsSet {
            get => _MTC_Addr_3_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_CS_2;
        public Enabled MTC_Addr_3_SEL_CS_2 {
            get => _MTC_Addr_3_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_3_SEL_CS_3IsSet;
        public bool MTC_Addr_3_SEL_CS_3IsSet {
            get => _MTC_Addr_3_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_CS_3;
        public Enabled MTC_Addr_3_SEL_CS_3 {
            get => _MTC_Addr_3_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_3_SEL_CS_4IsSet;
        public bool MTC_Addr_3_SEL_CS_4IsSet {
            get => _MTC_Addr_3_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_CS_4;
        public Enabled MTC_Addr_3_SEL_CS_4 {
            get => _MTC_Addr_3_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_3_SEL_CS_5IsSet;
        public bool MTC_Addr_3_SEL_CS_5IsSet {
            get => _MTC_Addr_3_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_CS_5;
        public Enabled MTC_Addr_3_SEL_CS_5 {
            get => _MTC_Addr_3_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_3_SEL_CS_6IsSet;
        public bool MTC_Addr_3_SEL_CS_6IsSet {
            get => _MTC_Addr_3_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_CS_6;
        public Enabled MTC_Addr_3_SEL_CS_6 {
            get => _MTC_Addr_3_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_3_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_3_SEL_SPI_1IsSet;
        public bool MTC_Addr_3_SEL_SPI_1IsSet {
            get => _MTC_Addr_3_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_SPI_1;
        public Enabled MTC_Addr_3_SEL_SPI_1 {
            get => _MTC_Addr_3_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_3_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_3_SEL_SPI_2IsSet;
        public bool MTC_Addr_3_SEL_SPI_2IsSet {
            get => _MTC_Addr_3_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_SPI_2;
        public Enabled MTC_Addr_3_SEL_SPI_2 {
            get => _MTC_Addr_3_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_3_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_3_SEL_CAN_1IsSet;
        public bool MTC_Addr_3_SEL_CAN_1IsSet {
            get => _MTC_Addr_3_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_CAN_1;
        public Enabled MTC_Addr_3_SEL_CAN_1 {
            get => _MTC_Addr_3_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_3_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_3_SEL_CAN_2IsSet;
        public bool MTC_Addr_3_SEL_CAN_2IsSet {
            get => _MTC_Addr_3_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_CAN_2;
        public Enabled MTC_Addr_3_SEL_CAN_2 {
            get => _MTC_Addr_3_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_3_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_3_SEL_CAN_3IsSet;
        public bool MTC_Addr_3_SEL_CAN_3IsSet {
            get => _MTC_Addr_3_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_CAN_3;
        public Enabled MTC_Addr_3_SEL_CAN_3 {
            get => _MTC_Addr_3_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_3_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_3_SEL_RS422IsSet;
        public bool MTC_Addr_3_SEL_RS422IsSet {
            get => _MTC_Addr_3_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_3_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_3_SEL_RS422;
        public Enabled MTC_Addr_3_SEL_RS422 {
            get => _MTC_Addr_3_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_3_SEL_RS422, value);
        }
        
        /*************** Properties for MTC_Addr_3_Set register **********************************/
        private bool _MTC_Addr_3_Set_ScanEnabledIsSet;
        public bool MTC_Addr_3_Set_ScanEnabledIsSet {
            get => _MTC_Addr_3_Set_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_ScanEnabled;
        public Enabled MTC_Addr_3_Set_ScanEnabled {
            get => _MTC_Addr_3_Set_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_3_Set_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_3_Set_DetectedIsSet;
        public bool MTC_Addr_3_Set_DetectedIsSet {
            get => _MTC_Addr_3_Set_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_3_Set_Detected;
        public byte MTC_Addr_3_Set_Detected {
            get => _MTC_Addr_3_Set_Detected;
            set => _ = Set(ref _MTC_Addr_3_Set_Detected, value);
        }
        
        private bool _MTC_Addr_3_Set_TypeIsSet;
        public bool MTC_Addr_3_Set_TypeIsSet {
            get => _MTC_Addr_3_Set_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_3_Set_Type;
        public UInt32 MTC_Addr_3_Set_Type {
            get => _MTC_Addr_3_Set_Type;
            set => _ = Set(ref _MTC_Addr_3_Set_Type, value);
        }
        
        private bool _MTC_Addr_3_Set_ENABLE_1IsSet;
        public bool MTC_Addr_3_Set_ENABLE_1IsSet {
            get => _MTC_Addr_3_Set_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_ENABLE_1;
        public Enabled MTC_Addr_3_Set_ENABLE_1 {
            get => _MTC_Addr_3_Set_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_3_Set_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_3_Set_ENABLE_2IsSet;
        public bool MTC_Addr_3_Set_ENABLE_2IsSet {
            get => _MTC_Addr_3_Set_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_ENABLE_2;
        public Enabled MTC_Addr_3_Set_ENABLE_2 {
            get => _MTC_Addr_3_Set_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_3_Set_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_I2C_1IsSet;
        public bool MTC_Addr_3_Set_SEL_I2C_1IsSet {
            get => _MTC_Addr_3_Set_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_I2C_1;
        public Enabled MTC_Addr_3_Set_SEL_I2C_1 {
            get => _MTC_Addr_3_Set_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_I2C_2IsSet;
        public bool MTC_Addr_3_Set_SEL_I2C_2IsSet {
            get => _MTC_Addr_3_Set_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_I2C_2;
        public Enabled MTC_Addr_3_Set_SEL_I2C_2 {
            get => _MTC_Addr_3_Set_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_UART_1IsSet;
        public bool MTC_Addr_3_Set_SEL_UART_1IsSet {
            get => _MTC_Addr_3_Set_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_UART_1;
        public Enabled MTC_Addr_3_Set_SEL_UART_1 {
            get => _MTC_Addr_3_Set_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_UART_2IsSet;
        public bool MTC_Addr_3_Set_SEL_UART_2IsSet {
            get => _MTC_Addr_3_Set_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_UART_2;
        public Enabled MTC_Addr_3_Set_SEL_UART_2 {
            get => _MTC_Addr_3_Set_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_UART_3IsSet;
        public bool MTC_Addr_3_Set_SEL_UART_3IsSet {
            get => _MTC_Addr_3_Set_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_UART_3;
        public Enabled MTC_Addr_3_Set_SEL_UART_3 {
            get => _MTC_Addr_3_Set_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_UART_4IsSet;
        public bool MTC_Addr_3_Set_SEL_UART_4IsSet {
            get => _MTC_Addr_3_Set_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_UART_4;
        public Enabled MTC_Addr_3_Set_SEL_UART_4 {
            get => _MTC_Addr_3_Set_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_UART_5IsSet;
        public bool MTC_Addr_3_Set_SEL_UART_5IsSet {
            get => _MTC_Addr_3_Set_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_UART_5;
        public Enabled MTC_Addr_3_Set_SEL_UART_5 {
            get => _MTC_Addr_3_Set_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_UART_6IsSet;
        public bool MTC_Addr_3_Set_SEL_UART_6IsSet {
            get => _MTC_Addr_3_Set_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_UART_6;
        public Enabled MTC_Addr_3_Set_SEL_UART_6 {
            get => _MTC_Addr_3_Set_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_VBATIsSet;
        public bool MTC_Addr_3_Set_SEL_VBATIsSet {
            get => _MTC_Addr_3_Set_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_VBAT;
        public Enabled MTC_Addr_3_Set_SEL_VBAT {
            get => _MTC_Addr_3_Set_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_3_Set_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_3_Set_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_VBAT_ALT;
        public Enabled MTC_Addr_3_Set_SEL_VBAT_ALT {
            get => _MTC_Addr_3_Set_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_3_Set_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_3_Set_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_3_Set_SEL_VBAT_FPGA {
            get => _MTC_Addr_3_Set_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_nRESET_1IsSet;
        public bool MTC_Addr_3_Set_SEL_nRESET_1IsSet {
            get => _MTC_Addr_3_Set_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_nRESET_1;
        public Enabled MTC_Addr_3_Set_SEL_nRESET_1 {
            get => _MTC_Addr_3_Set_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_nRESET_2IsSet;
        public bool MTC_Addr_3_Set_SEL_nRESET_2IsSet {
            get => _MTC_Addr_3_Set_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_nRESET_2;
        public Enabled MTC_Addr_3_Set_SEL_nRESET_2 {
            get => _MTC_Addr_3_Set_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_nRESET_3IsSet;
        public bool MTC_Addr_3_Set_SEL_nRESET_3IsSet {
            get => _MTC_Addr_3_Set_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_nRESET_3;
        public Enabled MTC_Addr_3_Set_SEL_nRESET_3 {
            get => _MTC_Addr_3_Set_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_CS_1IsSet;
        public bool MTC_Addr_3_Set_SEL_CS_1IsSet {
            get => _MTC_Addr_3_Set_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_CS_1;
        public Enabled MTC_Addr_3_Set_SEL_CS_1 {
            get => _MTC_Addr_3_Set_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_CS_2IsSet;
        public bool MTC_Addr_3_Set_SEL_CS_2IsSet {
            get => _MTC_Addr_3_Set_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_CS_2;
        public Enabled MTC_Addr_3_Set_SEL_CS_2 {
            get => _MTC_Addr_3_Set_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_CS_3IsSet;
        public bool MTC_Addr_3_Set_SEL_CS_3IsSet {
            get => _MTC_Addr_3_Set_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_CS_3;
        public Enabled MTC_Addr_3_Set_SEL_CS_3 {
            get => _MTC_Addr_3_Set_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_CS_4IsSet;
        public bool MTC_Addr_3_Set_SEL_CS_4IsSet {
            get => _MTC_Addr_3_Set_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_CS_4;
        public Enabled MTC_Addr_3_Set_SEL_CS_4 {
            get => _MTC_Addr_3_Set_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_CS_5IsSet;
        public bool MTC_Addr_3_Set_SEL_CS_5IsSet {
            get => _MTC_Addr_3_Set_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_CS_5;
        public Enabled MTC_Addr_3_Set_SEL_CS_5 {
            get => _MTC_Addr_3_Set_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_CS_6IsSet;
        public bool MTC_Addr_3_Set_SEL_CS_6IsSet {
            get => _MTC_Addr_3_Set_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_CS_6;
        public Enabled MTC_Addr_3_Set_SEL_CS_6 {
            get => _MTC_Addr_3_Set_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_SPI_1IsSet;
        public bool MTC_Addr_3_Set_SEL_SPI_1IsSet {
            get => _MTC_Addr_3_Set_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_SPI_1;
        public Enabled MTC_Addr_3_Set_SEL_SPI_1 {
            get => _MTC_Addr_3_Set_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_SPI_2IsSet;
        public bool MTC_Addr_3_Set_SEL_SPI_2IsSet {
            get => _MTC_Addr_3_Set_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_SPI_2;
        public Enabled MTC_Addr_3_Set_SEL_SPI_2 {
            get => _MTC_Addr_3_Set_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_CAN_1IsSet;
        public bool MTC_Addr_3_Set_SEL_CAN_1IsSet {
            get => _MTC_Addr_3_Set_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_CAN_1;
        public Enabled MTC_Addr_3_Set_SEL_CAN_1 {
            get => _MTC_Addr_3_Set_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_CAN_2IsSet;
        public bool MTC_Addr_3_Set_SEL_CAN_2IsSet {
            get => _MTC_Addr_3_Set_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_CAN_2;
        public Enabled MTC_Addr_3_Set_SEL_CAN_2 {
            get => _MTC_Addr_3_Set_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_CAN_3IsSet;
        public bool MTC_Addr_3_Set_SEL_CAN_3IsSet {
            get => _MTC_Addr_3_Set_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_CAN_3;
        public Enabled MTC_Addr_3_Set_SEL_CAN_3 {
            get => _MTC_Addr_3_Set_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_3_Set_SEL_RS422IsSet;
        public bool MTC_Addr_3_Set_SEL_RS422IsSet {
            get => _MTC_Addr_3_Set_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Set_SEL_RS422;
        public Enabled MTC_Addr_3_Set_SEL_RS422 {
            get => _MTC_Addr_3_Set_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_3_Set_SEL_RS422, value);
        }
        
        /*************** Properties for MTC_Addr_3_Clear register ********************************/
        private bool _MTC_Addr_3_Clear_ScanEnabledIsSet;
        public bool MTC_Addr_3_Clear_ScanEnabledIsSet {
            get => _MTC_Addr_3_Clear_ScanEnabledIsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_ScanEnabledIsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_ScanEnabled;
        public Enabled MTC_Addr_3_Clear_ScanEnabled {
            get => _MTC_Addr_3_Clear_ScanEnabled;
            set => _ = Set(ref _MTC_Addr_3_Clear_ScanEnabled, value);
        }
        
        private bool _MTC_Addr_3_Clear_DetectedIsSet;
        public bool MTC_Addr_3_Clear_DetectedIsSet {
            get => _MTC_Addr_3_Clear_DetectedIsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_DetectedIsSet, value); 
        }
        private byte _MTC_Addr_3_Clear_Detected;
        public byte MTC_Addr_3_Clear_Detected {
            get => _MTC_Addr_3_Clear_Detected;
            set => _ = Set(ref _MTC_Addr_3_Clear_Detected, value);
        }
        
        private bool _MTC_Addr_3_Clear_TypeIsSet;
        public bool MTC_Addr_3_Clear_TypeIsSet {
            get => _MTC_Addr_3_Clear_TypeIsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_TypeIsSet, value); 
        }
        private UInt32 _MTC_Addr_3_Clear_Type;
        public UInt32 MTC_Addr_3_Clear_Type {
            get => _MTC_Addr_3_Clear_Type;
            set => _ = Set(ref _MTC_Addr_3_Clear_Type, value);
        }
        
        private bool _MTC_Addr_3_Clear_ENABLE_1IsSet;
        public bool MTC_Addr_3_Clear_ENABLE_1IsSet {
            get => _MTC_Addr_3_Clear_ENABLE_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_ENABLE_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_ENABLE_1;
        public Enabled MTC_Addr_3_Clear_ENABLE_1 {
            get => _MTC_Addr_3_Clear_ENABLE_1;
            set => _ = Set(ref _MTC_Addr_3_Clear_ENABLE_1, value);
        }
        
        private bool _MTC_Addr_3_Clear_ENABLE_2IsSet;
        public bool MTC_Addr_3_Clear_ENABLE_2IsSet {
            get => _MTC_Addr_3_Clear_ENABLE_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_ENABLE_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_ENABLE_2;
        public Enabled MTC_Addr_3_Clear_ENABLE_2 {
            get => _MTC_Addr_3_Clear_ENABLE_2;
            set => _ = Set(ref _MTC_Addr_3_Clear_ENABLE_2, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_I2C_1IsSet;
        public bool MTC_Addr_3_Clear_SEL_I2C_1IsSet {
            get => _MTC_Addr_3_Clear_SEL_I2C_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_I2C_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_I2C_1;
        public Enabled MTC_Addr_3_Clear_SEL_I2C_1 {
            get => _MTC_Addr_3_Clear_SEL_I2C_1;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_I2C_1, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_I2C_2IsSet;
        public bool MTC_Addr_3_Clear_SEL_I2C_2IsSet {
            get => _MTC_Addr_3_Clear_SEL_I2C_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_I2C_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_I2C_2;
        public Enabled MTC_Addr_3_Clear_SEL_I2C_2 {
            get => _MTC_Addr_3_Clear_SEL_I2C_2;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_I2C_2, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_UART_1IsSet;
        public bool MTC_Addr_3_Clear_SEL_UART_1IsSet {
            get => _MTC_Addr_3_Clear_SEL_UART_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_UART_1;
        public Enabled MTC_Addr_3_Clear_SEL_UART_1 {
            get => _MTC_Addr_3_Clear_SEL_UART_1;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_1, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_UART_2IsSet;
        public bool MTC_Addr_3_Clear_SEL_UART_2IsSet {
            get => _MTC_Addr_3_Clear_SEL_UART_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_UART_2;
        public Enabled MTC_Addr_3_Clear_SEL_UART_2 {
            get => _MTC_Addr_3_Clear_SEL_UART_2;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_2, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_UART_3IsSet;
        public bool MTC_Addr_3_Clear_SEL_UART_3IsSet {
            get => _MTC_Addr_3_Clear_SEL_UART_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_UART_3;
        public Enabled MTC_Addr_3_Clear_SEL_UART_3 {
            get => _MTC_Addr_3_Clear_SEL_UART_3;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_3, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_UART_4IsSet;
        public bool MTC_Addr_3_Clear_SEL_UART_4IsSet {
            get => _MTC_Addr_3_Clear_SEL_UART_4IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_4IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_UART_4;
        public Enabled MTC_Addr_3_Clear_SEL_UART_4 {
            get => _MTC_Addr_3_Clear_SEL_UART_4;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_4, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_UART_5IsSet;
        public bool MTC_Addr_3_Clear_SEL_UART_5IsSet {
            get => _MTC_Addr_3_Clear_SEL_UART_5IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_5IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_UART_5;
        public Enabled MTC_Addr_3_Clear_SEL_UART_5 {
            get => _MTC_Addr_3_Clear_SEL_UART_5;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_5, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_UART_6IsSet;
        public bool MTC_Addr_3_Clear_SEL_UART_6IsSet {
            get => _MTC_Addr_3_Clear_SEL_UART_6IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_6IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_UART_6;
        public Enabled MTC_Addr_3_Clear_SEL_UART_6 {
            get => _MTC_Addr_3_Clear_SEL_UART_6;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_UART_6, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_VBATIsSet;
        public bool MTC_Addr_3_Clear_SEL_VBATIsSet {
            get => _MTC_Addr_3_Clear_SEL_VBATIsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_VBATIsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_VBAT;
        public Enabled MTC_Addr_3_Clear_SEL_VBAT {
            get => _MTC_Addr_3_Clear_SEL_VBAT;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_VBAT, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_VBAT_ALTIsSet;
        public bool MTC_Addr_3_Clear_SEL_VBAT_ALTIsSet {
            get => _MTC_Addr_3_Clear_SEL_VBAT_ALTIsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_VBAT_ALTIsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_VBAT_ALT;
        public Enabled MTC_Addr_3_Clear_SEL_VBAT_ALT {
            get => _MTC_Addr_3_Clear_SEL_VBAT_ALT;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_VBAT_ALT, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_VBAT_FPGAIsSet;
        public bool MTC_Addr_3_Clear_SEL_VBAT_FPGAIsSet {
            get => _MTC_Addr_3_Clear_SEL_VBAT_FPGAIsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_VBAT_FPGAIsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_VBAT_FPGA;
        public Enabled MTC_Addr_3_Clear_SEL_VBAT_FPGA {
            get => _MTC_Addr_3_Clear_SEL_VBAT_FPGA;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_VBAT_FPGA, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_nRESET_1IsSet;
        public bool MTC_Addr_3_Clear_SEL_nRESET_1IsSet {
            get => _MTC_Addr_3_Clear_SEL_nRESET_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_nRESET_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_nRESET_1;
        public Enabled MTC_Addr_3_Clear_SEL_nRESET_1 {
            get => _MTC_Addr_3_Clear_SEL_nRESET_1;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_nRESET_1, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_nRESET_2IsSet;
        public bool MTC_Addr_3_Clear_SEL_nRESET_2IsSet {
            get => _MTC_Addr_3_Clear_SEL_nRESET_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_nRESET_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_nRESET_2;
        public Enabled MTC_Addr_3_Clear_SEL_nRESET_2 {
            get => _MTC_Addr_3_Clear_SEL_nRESET_2;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_nRESET_2, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_nRESET_3IsSet;
        public bool MTC_Addr_3_Clear_SEL_nRESET_3IsSet {
            get => _MTC_Addr_3_Clear_SEL_nRESET_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_nRESET_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_nRESET_3;
        public Enabled MTC_Addr_3_Clear_SEL_nRESET_3 {
            get => _MTC_Addr_3_Clear_SEL_nRESET_3;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_nRESET_3, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_CS_1IsSet;
        public bool MTC_Addr_3_Clear_SEL_CS_1IsSet {
            get => _MTC_Addr_3_Clear_SEL_CS_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_CS_1;
        public Enabled MTC_Addr_3_Clear_SEL_CS_1 {
            get => _MTC_Addr_3_Clear_SEL_CS_1;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_1, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_CS_2IsSet;
        public bool MTC_Addr_3_Clear_SEL_CS_2IsSet {
            get => _MTC_Addr_3_Clear_SEL_CS_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_CS_2;
        public Enabled MTC_Addr_3_Clear_SEL_CS_2 {
            get => _MTC_Addr_3_Clear_SEL_CS_2;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_2, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_CS_3IsSet;
        public bool MTC_Addr_3_Clear_SEL_CS_3IsSet {
            get => _MTC_Addr_3_Clear_SEL_CS_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_CS_3;
        public Enabled MTC_Addr_3_Clear_SEL_CS_3 {
            get => _MTC_Addr_3_Clear_SEL_CS_3;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_3, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_CS_4IsSet;
        public bool MTC_Addr_3_Clear_SEL_CS_4IsSet {
            get => _MTC_Addr_3_Clear_SEL_CS_4IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_4IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_CS_4;
        public Enabled MTC_Addr_3_Clear_SEL_CS_4 {
            get => _MTC_Addr_3_Clear_SEL_CS_4;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_4, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_CS_5IsSet;
        public bool MTC_Addr_3_Clear_SEL_CS_5IsSet {
            get => _MTC_Addr_3_Clear_SEL_CS_5IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_5IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_CS_5;
        public Enabled MTC_Addr_3_Clear_SEL_CS_5 {
            get => _MTC_Addr_3_Clear_SEL_CS_5;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_5, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_CS_6IsSet;
        public bool MTC_Addr_3_Clear_SEL_CS_6IsSet {
            get => _MTC_Addr_3_Clear_SEL_CS_6IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_6IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_CS_6;
        public Enabled MTC_Addr_3_Clear_SEL_CS_6 {
            get => _MTC_Addr_3_Clear_SEL_CS_6;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CS_6, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_SPI_1IsSet;
        public bool MTC_Addr_3_Clear_SEL_SPI_1IsSet {
            get => _MTC_Addr_3_Clear_SEL_SPI_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_SPI_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_SPI_1;
        public Enabled MTC_Addr_3_Clear_SEL_SPI_1 {
            get => _MTC_Addr_3_Clear_SEL_SPI_1;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_SPI_1, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_SPI_2IsSet;
        public bool MTC_Addr_3_Clear_SEL_SPI_2IsSet {
            get => _MTC_Addr_3_Clear_SEL_SPI_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_SPI_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_SPI_2;
        public Enabled MTC_Addr_3_Clear_SEL_SPI_2 {
            get => _MTC_Addr_3_Clear_SEL_SPI_2;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_SPI_2, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_CAN_1IsSet;
        public bool MTC_Addr_3_Clear_SEL_CAN_1IsSet {
            get => _MTC_Addr_3_Clear_SEL_CAN_1IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CAN_1IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_CAN_1;
        public Enabled MTC_Addr_3_Clear_SEL_CAN_1 {
            get => _MTC_Addr_3_Clear_SEL_CAN_1;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CAN_1, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_CAN_2IsSet;
        public bool MTC_Addr_3_Clear_SEL_CAN_2IsSet {
            get => _MTC_Addr_3_Clear_SEL_CAN_2IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CAN_2IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_CAN_2;
        public Enabled MTC_Addr_3_Clear_SEL_CAN_2 {
            get => _MTC_Addr_3_Clear_SEL_CAN_2;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CAN_2, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_CAN_3IsSet;
        public bool MTC_Addr_3_Clear_SEL_CAN_3IsSet {
            get => _MTC_Addr_3_Clear_SEL_CAN_3IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CAN_3IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_CAN_3;
        public Enabled MTC_Addr_3_Clear_SEL_CAN_3 {
            get => _MTC_Addr_3_Clear_SEL_CAN_3;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_CAN_3, value);
        }
        
        private bool _MTC_Addr_3_Clear_SEL_RS422IsSet;
        public bool MTC_Addr_3_Clear_SEL_RS422IsSet {
            get => _MTC_Addr_3_Clear_SEL_RS422IsSet;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_RS422IsSet, value); 
        }
        private Enabled _MTC_Addr_3_Clear_SEL_RS422;
        public Enabled MTC_Addr_3_Clear_SEL_RS422 {
            get => _MTC_Addr_3_Clear_SEL_RS422;
            set => _ = Set(ref _MTC_Addr_3_Clear_SEL_RS422, value);
        }
        
        /*************** Properties for RTOS_Status0 register ************************************/
        private bool _RTOS_Status0_uartRxHBOverflowIsSet;
        public bool RTOS_Status0_uartRxHBOverflowIsSet {
            get => _RTOS_Status0_uartRxHBOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_uartRxHBOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_uartRxHBOverflow;
        public bool RTOS_Status0_uartRxHBOverflow {
            get => _RTOS_Status0_uartRxHBOverflow;
            set => _ = Set(ref _RTOS_Status0_uartRxHBOverflow, value);
        }
        
        private bool _RTOS_Status0_uartRxSBOverflowIsSet;
        public bool RTOS_Status0_uartRxSBOverflowIsSet {
            get => _RTOS_Status0_uartRxSBOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_uartRxSBOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_uartRxSBOverflow;
        public bool RTOS_Status0_uartRxSBOverflow {
            get => _RTOS_Status0_uartRxSBOverflow;
            set => _ = Set(ref _RTOS_Status0_uartRxSBOverflow, value);
        }
        
        private bool _RTOS_Status0_uartTxSBOverflowIsSet;
        public bool RTOS_Status0_uartTxSBOverflowIsSet {
            get => _RTOS_Status0_uartTxSBOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_uartTxSBOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_uartTxSBOverflow;
        public bool RTOS_Status0_uartTxSBOverflow {
            get => _RTOS_Status0_uartTxSBOverflow;
            set => _ = Set(ref _RTOS_Status0_uartTxSBOverflow, value);
        }
        
        private bool _RTOS_Status0_uartTxHBOverflowIsSet;
        public bool RTOS_Status0_uartTxHBOverflowIsSet {
            get => _RTOS_Status0_uartTxHBOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_uartTxHBOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_uartTxHBOverflow;
        public bool RTOS_Status0_uartTxHBOverflow {
            get => _RTOS_Status0_uartTxHBOverflow;
            set => _ = Set(ref _RTOS_Status0_uartTxHBOverflow, value);
        }
        
        private bool _RTOS_Status0_I2CTargetIncomingOverflowIsSet;
        public bool RTOS_Status0_I2CTargetIncomingOverflowIsSet {
            get => _RTOS_Status0_I2CTargetIncomingOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_I2CTargetIncomingOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_I2CTargetIncomingOverflow;
        public bool RTOS_Status0_I2CTargetIncomingOverflow {
            get => _RTOS_Status0_I2CTargetIncomingOverflow;
            set => _ = Set(ref _RTOS_Status0_I2CTargetIncomingOverflow, value);
        }
        
        private bool _RTOS_Status0_I2CTargetOutgoingOverflowIsSet;
        public bool RTOS_Status0_I2CTargetOutgoingOverflowIsSet {
            get => _RTOS_Status0_I2CTargetOutgoingOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_I2CTargetOutgoingOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_I2CTargetOutgoingOverflow;
        public bool RTOS_Status0_I2CTargetOutgoingOverflow {
            get => _RTOS_Status0_I2CTargetOutgoingOverflow;
            set => _ = Set(ref _RTOS_Status0_I2CTargetOutgoingOverflow, value);
        }
        
        private bool _RTOS_Status0_CANTargetIncomingOverflowIsSet;
        public bool RTOS_Status0_CANTargetIncomingOverflowIsSet {
            get => _RTOS_Status0_CANTargetIncomingOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_CANTargetIncomingOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_CANTargetIncomingOverflow;
        public bool RTOS_Status0_CANTargetIncomingOverflow {
            get => _RTOS_Status0_CANTargetIncomingOverflow;
            set => _ = Set(ref _RTOS_Status0_CANTargetIncomingOverflow, value);
        }
        
        private bool _RTOS_Status0_CANInterruptBufferOverflowIsSet;
        public bool RTOS_Status0_CANInterruptBufferOverflowIsSet {
            get => _RTOS_Status0_CANInterruptBufferOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_CANInterruptBufferOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_CANInterruptBufferOverflow;
        public bool RTOS_Status0_CANInterruptBufferOverflow {
            get => _RTOS_Status0_CANInterruptBufferOverflow;
            set => _ = Set(ref _RTOS_Status0_CANInterruptBufferOverflow, value);
        }
        
        private bool _RTOS_Status0_CANTargetOutgoingOverflowIsSet;
        public bool RTOS_Status0_CANTargetOutgoingOverflowIsSet {
            get => _RTOS_Status0_CANTargetOutgoingOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_CANTargetOutgoingOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_CANTargetOutgoingOverflow;
        public bool RTOS_Status0_CANTargetOutgoingOverflow {
            get => _RTOS_Status0_CANTargetOutgoingOverflow;
            set => _ = Set(ref _RTOS_Status0_CANTargetOutgoingOverflow, value);
        }
        
        private bool _RTOS_Status0_UARTTargetIncomingOverflowIsSet;
        public bool RTOS_Status0_UARTTargetIncomingOverflowIsSet {
            get => _RTOS_Status0_UARTTargetIncomingOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_UARTTargetIncomingOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_UARTTargetIncomingOverflow;
        public bool RTOS_Status0_UARTTargetIncomingOverflow {
            get => _RTOS_Status0_UARTTargetIncomingOverflow;
            set => _ = Set(ref _RTOS_Status0_UARTTargetIncomingOverflow, value);
        }
        
        private bool _RTOS_Status0_UARTTargetTxHBOverflowIsSet;
        public bool RTOS_Status0_UARTTargetTxHBOverflowIsSet {
            get => _RTOS_Status0_UARTTargetTxHBOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_UARTTargetTxHBOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_UARTTargetTxHBOverflow;
        public bool RTOS_Status0_UARTTargetTxHBOverflow {
            get => _RTOS_Status0_UARTTargetTxHBOverflow;
            set => _ = Set(ref _RTOS_Status0_UARTTargetTxHBOverflow, value);
        }
        
        private bool _RTOS_Status0_UARTTargetRxHBOverflowIsSet;
        public bool RTOS_Status0_UARTTargetRxHBOverflowIsSet {
            get => _RTOS_Status0_UARTTargetRxHBOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_UARTTargetRxHBOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_UARTTargetRxHBOverflow;
        public bool RTOS_Status0_UARTTargetRxHBOverflow {
            get => _RTOS_Status0_UARTTargetRxHBOverflow;
            set => _ = Set(ref _RTOS_Status0_UARTTargetRxHBOverflow, value);
        }
        
        private bool _RTOS_Status0_UARTTargetOutgoingOverflowIsSet;
        public bool RTOS_Status0_UARTTargetOutgoingOverflowIsSet {
            get => _RTOS_Status0_UARTTargetOutgoingOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_UARTTargetOutgoingOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_UARTTargetOutgoingOverflow;
        public bool RTOS_Status0_UARTTargetOutgoingOverflow {
            get => _RTOS_Status0_UARTTargetOutgoingOverflow;
            set => _ = Set(ref _RTOS_Status0_UARTTargetOutgoingOverflow, value);
        }
        
        private bool _RTOS_Status0_GSETargetIncomingOverflowIsSet;
        public bool RTOS_Status0_GSETargetIncomingOverflowIsSet {
            get => _RTOS_Status0_GSETargetIncomingOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_GSETargetIncomingOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_GSETargetIncomingOverflow;
        public bool RTOS_Status0_GSETargetIncomingOverflow {
            get => _RTOS_Status0_GSETargetIncomingOverflow;
            set => _ = Set(ref _RTOS_Status0_GSETargetIncomingOverflow, value);
        }
        
        private bool _RTOS_Status0_GSETargetOutgoingOverflowIsSet;
        public bool RTOS_Status0_GSETargetOutgoingOverflowIsSet {
            get => _RTOS_Status0_GSETargetOutgoingOverflowIsSet;
            set => _ = Set(ref _RTOS_Status0_GSETargetOutgoingOverflowIsSet, value); 
        }
        private bool _RTOS_Status0_GSETargetOutgoingOverflow;
        public bool RTOS_Status0_GSETargetOutgoingOverflow {
            get => _RTOS_Status0_GSETargetOutgoingOverflow;
            set => _ = Set(ref _RTOS_Status0_GSETargetOutgoingOverflow, value);
        }
        
        private bool _RTOS_Status0_SERMUX_CRC_ErrorIsSet;
        public bool RTOS_Status0_SERMUX_CRC_ErrorIsSet {
            get => _RTOS_Status0_SERMUX_CRC_ErrorIsSet;
            set => _ = Set(ref _RTOS_Status0_SERMUX_CRC_ErrorIsSet, value); 
        }
        private bool _RTOS_Status0_SERMUX_CRC_Error;
        public bool RTOS_Status0_SERMUX_CRC_Error {
            get => _RTOS_Status0_SERMUX_CRC_Error;
            set => _ = Set(ref _RTOS_Status0_SERMUX_CRC_Error, value);
        }
        
        /*************** Properties for UtilI2CConfA register ************************************/
        private bool _UtilI2CConfA_ResetIsSet;
        public bool UtilI2CConfA_ResetIsSet {
            get => _UtilI2CConfA_ResetIsSet;
            set => _ = Set(ref _UtilI2CConfA_ResetIsSet, value); 
        }
        private byte _UtilI2CConfA_Reset;
        public byte UtilI2CConfA_Reset {
            get => _UtilI2CConfA_Reset;
            set => _ = Set(ref _UtilI2CConfA_Reset, value);
        }
        
        public byte UtilI2CConfA_SPDMax { get => 40; }
        public byte UtilI2CConfA_SPDMin { get => 1; }
        private bool _UtilI2CConfA_SPDIsSet;
        public bool UtilI2CConfA_SPDIsSet {
            get => _UtilI2CConfA_SPDIsSet;
            set => _ = Set(ref _UtilI2CConfA_SPDIsSet, value); 
        }
        private byte _UtilI2CConfA_SPD;
        public byte UtilI2CConfA_SPD {
            get => _UtilI2CConfA_SPD;
            set => _ = Set(ref _UtilI2CConfA_SPD, value);
        }
        
        /*************** Properties for UtilI2CStatus register ***********************************/
        private bool _UtilI2CStatusIsSet;
        public bool UtilI2CStatusIsSet {
            get => _UtilI2CStatusIsSet;
            set => _ = Set(ref _UtilI2CStatusIsSet, value); 
        }
        private UInt32 _UtilI2CStatus;
        public UInt32 UtilI2CStatus {
            get => _UtilI2CStatus;
            set => _ = Set(ref _UtilI2CStatus, value);
        }
        
        /*************** Properties for PreviousEndpoint register ********************************/
        private bool _PreviousEndpoint_NumberIsSet;
        public bool PreviousEndpoint_NumberIsSet {
            get => _PreviousEndpoint_NumberIsSet;
            set => _ = Set(ref _PreviousEndpoint_NumberIsSet, value); 
        }
        private byte _PreviousEndpoint_Number;
        public byte PreviousEndpoint_Number {
            get => _PreviousEndpoint_Number;
            set => _ = Set(ref _PreviousEndpoint_Number, value);
        }
        
        public void DecodeFrom(RegisterData register, OBCRegisterAddress address)
        {
            switch (address)
            {
                case OBCRegisterAddress.OBC_REG_BOARD_ID:
                    FullRegister_Board_ID  = register.RawValue; 
                    Board_ID_ccIdentifier =  register.RegBoard_ID.ccIdentifier;
                    Board_ID_id0 =  register.RegBoard_ID.id0;
                    Board_ID_id1 =  register.RegBoard_ID.id1;
                    Board_ID_id2 =  register.RegBoard_ID.id2;
                    break;

                case OBCRegisterAddress.OBC_REG_FW_VERSION:
                    FullRegister_FW_Version  = register.RawValue; 
                    FW_Version_major_version =  register.RegVersion.major_version;
                    FW_Version_minor_version =  register.RegVersion.minor_version;
                    FW_Version_patch_version =  register.RegVersion.patch_version;
                    break;

                case OBCRegisterAddress.OBC_REG_HW_VERSION:
                    FullRegister_HW_Version  = register.RawValue; 
                    HW_Version_major_version =  register.RegVersion.major_version;
                    HW_Version_minor_version =  register.RegVersion.minor_version;
                    HW_Version_patch_version =  register.RegVersion.patch_version;
                    break;

                case OBCRegisterAddress.OBC_REG_SCRATCHPAD:
                    FullRegister_Scratchpad  = register.RawValue; 
                    Scratchpad =  register.RegScratchpad.value;
                    break;

                case OBCRegisterAddress.OBC_REG_SUPPORTED_BOARDS:
                    FullRegister_Supported_Boards  = register.RawValue; 
                    Supported_Boards =  register.RegSupported_Boards.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CONFIGURED_BOARDS:
                    FullRegister_Configured_Boards  = register.RawValue; 
                    Configured_Boards = (BoardIdentifier) register.RegConfigured_Boards.value;
                    break;

                case OBCRegisterAddress.OBC_REG_UPTIME:
                    FullRegister_Uptime  = register.RawValue; 
                    Uptime =  register.RegUptime.value;
                    break;

                case OBCRegisterAddress.OBC_REG_EVENT_CONFA:
                    FullRegister_Event_ConfA  = register.RawValue; 
                    Event_ConfA_count =  register.RegEvent_ConfA.count;
                    break;

                case OBCRegisterAddress.OBC_REG_EVENT:
                    FullRegister_Event  = register.RawValue; 
                    Event_section =  register.RegEvent.section;
                    Event_detail =  register.RegEvent.detail;
                    Event_timestamp =  register.RegEvent.timestamp;
                    break;

                case OBCRegisterAddress.OBC_REG_CONFPOWER:
                    FullRegister_ConfPower  = register.RawValue; 
                    ConfPower_voltage5Toggle = (Enabled) register.RegConfPower.voltage5Toggle;
                    ConfPower_voltage3Toggle = (Enabled) register.RegConfPower.voltage3Toggle;
                    ConfPower_voltageVBatToggle = (Enabled) register.RegConfPower.voltageVBatToggle;
                    ConfPower_voltageVBatAltToggle = (Enabled) register.RegConfPower.voltageVBatAltToggle;
                    ConfPower_voltage3UtilToggle = (Enabled) register.RegConfPower.voltage3UtilToggle;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_V3:
                    FullRegister_MeasureVI_V3  = register.RawValue; 
                    MeasureVI_V3_voltage =  register.RegMeasureVI.voltage;
                    MeasureVI_V3_current =  register.RegMeasureVI.current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_V3:
                    FullRegister_MeasurePower_V3  = register.RawValue; 
                    MeasurePower_V3_power =  register.RegMeasurePower.power;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_V5:
                    FullRegister_MeasureVI_V5  = register.RawValue; 
                    MeasureVI_V5_voltage =  register.RegMeasureVI.voltage;
                    MeasureVI_V5_current =  register.RegMeasureVI.current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_V5:
                    FullRegister_MeasurePower_V5  = register.RawValue; 
                    MeasurePower_V5_power =  register.RegMeasurePower.power;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_VBAT:
                    FullRegister_MeasureVI_VBat  = register.RawValue; 
                    MeasureVI_VBat_voltage =  register.RegMeasureVI.voltage;
                    MeasureVI_VBat_current =  register.RegMeasureVI.current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_VBAT:
                    FullRegister_MeasurePower_VBat  = register.RawValue; 
                    MeasurePower_VBat_power =  register.RegMeasurePower.power;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_VBATALT:
                    FullRegister_MeasureVI_VBatAlt  = register.RawValue; 
                    MeasureVI_VBatAlt_voltage =  register.RegMeasureVI.voltage;
                    MeasureVI_VBatAlt_current =  register.RegMeasureVI.current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_VBATALT:
                    FullRegister_MeasurePower_VBatAlt  = register.RawValue; 
                    MeasurePower_VBatAlt_power =  register.RegMeasurePower.power;
                    break;

                case OBCRegisterAddress.OBC_REG_I2CCONFA:
                    FullRegister_I2CConfA  = register.RawValue; 
                    I2CConfA_TRDEL =  register.RegI2CConfA.TRDEL;
                    I2CConfA_WRDEL =  register.RegI2CConfA.WRDEL;
                    I2CConfA_SPD =  register.RegI2CConfA.SPD;
                    break;

                case OBCRegisterAddress.OBC_REG_I2CCONFB:
                    FullRegister_I2CConfB  = register.RawValue; 
                    I2CConfB_ADDR =  register.RegI2CConfB.ADDR;
                    break;

                case OBCRegisterAddress.OBC_REG_MULTICONF0:
                    FullRegister_MultiConf0  = register.RawValue; 
                    MultiConf0_Detected = (Enabled) register.RegMultiConf0.Detected;
                    MultiConf0_AutoCLR = (Enabled) register.RegMultiConf0.AutoCLR;
                    MultiConf0_ScanEnabled = (Enabled) register.RegMultiConf0.ScanEnabled;
                    MultiConf0_FanPos1 = (Enabled) register.RegMultiConf0.FanPos1;
                    MultiConf0_FanPos2 = (Enabled) register.RegMultiConf0.FanPos2;
                    MultiConf0_FanPos3 = (Enabled) register.RegMultiConf0.FanPos3;
                    MultiConf0_FanPos4 = (Enabled) register.RegMultiConf0.FanPos4;
                    break;

                case OBCRegisterAddress.OBC_REG_CONFTEMPSENSE:
                    FullRegister_ConfTempSense  = register.RawValue; 
                    ConfTempSense_EnableMeasurements = (Enabled) register.RegConfTempSense.EnableMeasurements;
                    break;

                case OBCRegisterAddress.OBC_REG_CANCONFA:
                    FullRegister_CANConfA  = register.RawValue; 
                    CANConfA_BaudRate =  register.RegCANConfA.BaudRate;
                    CANConfA_EnableRetries = (Enabled) register.RegCANConfA.EnableRetries;
                    CANConfA_FlipCanBytes = (Enabled) register.RegCANConfA.FlipCanBytes;
                    break;

                case OBCRegisterAddress.OBC_REG_CANCONFB:
                    FullRegister_CANConfB  = register.RawValue; 
                    CANConfB_Address =  register.RegCANConfB.Address;
                    break;

                case OBCRegisterAddress.OBC_REG_SERIALCONF:
                    FullRegister_SerialConf  = register.RawValue; 
                    SerialConf_SerialMode = (SerialMode) register.RegSerialConf.SerialMode;
                    SerialConf_ParityEnabled = (Enabled) register.RegSerialConf.ParityEnabled;
                    SerialConf_ParityMode = (ParityModes) register.RegSerialConf.ParityMode;
                    SerialConf_BaudRates = (USART_BaudRates) register.RegSerialConf.BaudRates;
                    break;

                case OBCRegisterAddress.OBC_REG_PC104PINS:
                    FullRegister_PC104Pins  = register.RawValue; 
                    PC104Pins_ENA = (Enabled) register.RegPC104Pins.ENA;
                    PC104Pins_nRST = (Enabled) register.RegPC104Pins.nRST;
                    PC104Pins_RDY = (Enabled) register.RegPC104Pins.RDY;
                    break;

                case OBCRegisterAddress.OBC_REG_XTXMULTITESTER:
                    FullRegister_XTXMultitester  = register.RawValue; 
                    XTXMultitester_POS1_XTX_EN = (Enabled) register.RegXTXMultitester.POS1_XTX_EN;
                    XTXMultitester_POS1_XTX_Power = (Enabled) register.RegXTXMultitester.POS1_XTX_Power;
                    XTXMultitester_POS1_XTX_nReset = (Enabled) register.RegXTXMultitester.POS1_XTX_nReset;
                    XTXMultitester_POS2_XTX_EN = (Enabled) register.RegXTXMultitester.POS2_XTX_EN;
                    XTXMultitester_POS2_XTX_Power = (Enabled) register.RegXTXMultitester.POS2_XTX_Power;
                    XTXMultitester_POS2_XTX_nReset = (Enabled) register.RegXTXMultitester.POS2_XTX_nReset;
                    XTXMultitester_POS3_XTX_EN = (Enabled) register.RegXTXMultitester.POS3_XTX_EN;
                    XTXMultitester_POS3_XTX_Power = (Enabled) register.RegXTXMultitester.POS3_XTX_Power;
                    XTXMultitester_POS3_XTX_nReset = (Enabled) register.RegXTXMultitester.POS3_XTX_nReset;
                    XTXMultitester_POS4_XTX_EN = (Enabled) register.RegXTXMultitester.POS4_XTX_EN;
                    XTXMultitester_POS4_XTX_Power = (Enabled) register.RegXTXMultitester.POS4_XTX_Power;
                    XTXMultitester_POS4_XTX_nReset = (Enabled) register.RegXTXMultitester.POS4_XTX_nReset;
                    break;

                case OBCRegisterAddress.OBC_REG_RFRELAYSCONF:
                    FullRegister_RFRelaysConf  = register.RawValue; 
                    RFRelaysConf_RFSW1_Detected = (Enabled) register.RegRFRelaysConf.RFSW1_Detected;
                    RFRelaysConf_RFSW2_Detected = (Enabled) register.RegRFRelaysConf.RFSW2_Detected;
                    RFRelaysConf_ScanEnabled = (Enabled) register.RegRFRelaysConf.ScanEnabled;
                    RFRelaysConf_RfSw1Chan =  register.RegRFRelaysConf.RfSw1Chan;
                    RFRelaysConf_RfSw2Chan =  register.RegRFRelaysConf.RfSw2Chan;
                    break;

                case OBCRegisterAddress.OBC_REG_MULTICONF1_STATUS:
                    FullRegister_MultiConf1_Status  = register.RawValue; 
                    MultiConf1_Status_POS1_Enable = (Enabled) register.RegMultitester.POS1_Enable;
                    MultiConf1_Status_POS1_Power = (Enabled) register.RegMultitester.POS1_Power;
                    MultiConf1_Status_POS1_nReset = (Enabled) register.RegMultitester.POS1_nReset;
                    MultiConf1_Status_POS1_FAN = (Enabled) register.RegMultitester.POS1_FAN;
                    MultiConf1_Status_POS2_Enable = (Enabled) register.RegMultitester.POS2_Enable;
                    MultiConf1_Status_POS2_Power = (Enabled) register.RegMultitester.POS2_Power;
                    MultiConf1_Status_POS2_nReset = (Enabled) register.RegMultitester.POS2_nReset;
                    MultiConf1_Status_POS2_FAN = (Enabled) register.RegMultitester.POS2_FAN;
                    MultiConf1_Status_POS3_Enable = (Enabled) register.RegMultitester.POS3_Enable;
                    MultiConf1_Status_POS3_Power = (Enabled) register.RegMultitester.POS3_Power;
                    MultiConf1_Status_POS3_nReset = (Enabled) register.RegMultitester.POS3_nReset;
                    MultiConf1_Status_POS3_FAN = (Enabled) register.RegMultitester.POS3_FAN;
                    MultiConf1_Status_POS4_Enable = (Enabled) register.RegMultitester.POS4_Enable;
                    MultiConf1_Status_POS4_Power = (Enabled) register.RegMultitester.POS4_Power;
                    MultiConf1_Status_POS4_nReset = (Enabled) register.RegMultitester.POS4_nReset;
                    MultiConf1_Status_POS4_FAN = (Enabled) register.RegMultitester.POS4_FAN;
                    break;

                case OBCRegisterAddress.OBC_REG_MULTICONF1_SET:
                    FullRegister_MultiConf1_Set  = register.RawValue; 
                    MultiConf1_Set_POS1_Enable = (Enabled) register.RegMultitester.POS1_Enable;
                    MultiConf1_Set_POS1_Power = (Enabled) register.RegMultitester.POS1_Power;
                    MultiConf1_Set_POS1_nReset = (Enabled) register.RegMultitester.POS1_nReset;
                    MultiConf1_Set_POS1_FAN = (Enabled) register.RegMultitester.POS1_FAN;
                    MultiConf1_Set_POS2_Enable = (Enabled) register.RegMultitester.POS2_Enable;
                    MultiConf1_Set_POS2_Power = (Enabled) register.RegMultitester.POS2_Power;
                    MultiConf1_Set_POS2_nReset = (Enabled) register.RegMultitester.POS2_nReset;
                    MultiConf1_Set_POS2_FAN = (Enabled) register.RegMultitester.POS2_FAN;
                    MultiConf1_Set_POS3_Enable = (Enabled) register.RegMultitester.POS3_Enable;
                    MultiConf1_Set_POS3_Power = (Enabled) register.RegMultitester.POS3_Power;
                    MultiConf1_Set_POS3_nReset = (Enabled) register.RegMultitester.POS3_nReset;
                    MultiConf1_Set_POS3_FAN = (Enabled) register.RegMultitester.POS3_FAN;
                    MultiConf1_Set_POS4_Enable = (Enabled) register.RegMultitester.POS4_Enable;
                    MultiConf1_Set_POS4_Power = (Enabled) register.RegMultitester.POS4_Power;
                    MultiConf1_Set_POS4_nReset = (Enabled) register.RegMultitester.POS4_nReset;
                    MultiConf1_Set_POS4_FAN = (Enabled) register.RegMultitester.POS4_FAN;
                    break;

                case OBCRegisterAddress.OBC_REG_MULTICONF1_CLEAR:
                    FullRegister_MultiConf1_Clear  = register.RawValue; 
                    MultiConf1_Clear_POS1_Enable = (Enabled) register.RegMultitester.POS1_Enable;
                    MultiConf1_Clear_POS1_Power = (Enabled) register.RegMultitester.POS1_Power;
                    MultiConf1_Clear_POS1_nReset = (Enabled) register.RegMultitester.POS1_nReset;
                    MultiConf1_Clear_POS1_FAN = (Enabled) register.RegMultitester.POS1_FAN;
                    MultiConf1_Clear_POS2_Enable = (Enabled) register.RegMultitester.POS2_Enable;
                    MultiConf1_Clear_POS2_Power = (Enabled) register.RegMultitester.POS2_Power;
                    MultiConf1_Clear_POS2_nReset = (Enabled) register.RegMultitester.POS2_nReset;
                    MultiConf1_Clear_POS2_FAN = (Enabled) register.RegMultitester.POS2_FAN;
                    MultiConf1_Clear_POS3_Enable = (Enabled) register.RegMultitester.POS3_Enable;
                    MultiConf1_Clear_POS3_Power = (Enabled) register.RegMultitester.POS3_Power;
                    MultiConf1_Clear_POS3_nReset = (Enabled) register.RegMultitester.POS3_nReset;
                    MultiConf1_Clear_POS3_FAN = (Enabled) register.RegMultitester.POS3_FAN;
                    MultiConf1_Clear_POS4_Enable = (Enabled) register.RegMultitester.POS4_Enable;
                    MultiConf1_Clear_POS4_Power = (Enabled) register.RegMultitester.POS4_Power;
                    MultiConf1_Clear_POS4_nReset = (Enabled) register.RegMultitester.POS4_nReset;
                    MultiConf1_Clear_POS4_FAN = (Enabled) register.RegMultitester.POS4_FAN;
                    break;

                case OBCRegisterAddress.OBC_REG_XDCCONFIG:
                    FullRegister_XDCConfig  = register.RawValue; 
                    XDCConfig_ADDR = (Enabled) register.RegXDCConfig.ADDR;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T0:
                    FullRegister_CSBoard_T0  = register.RawValue; 
                    CSBoard_T0 =  register.RegCSBoard_T0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T1:
                    FullRegister_CSBoard_T1  = register.RawValue; 
                    CSBoard_T1 =  register.RegCSBoard_T1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T2:
                    FullRegister_CSBoard_T2  = register.RawValue; 
                    CSBoard_T2 =  register.RegCSBoard_T2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T3:
                    FullRegister_CSBoard_T3  = register.RawValue; 
                    CSBoard_T3 =  register.RegCSBoard_T3.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T4:
                    FullRegister_CSBoard_T4  = register.RawValue; 
                    CSBoard_T4 =  register.RegCSBoard_T4.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T5:
                    FullRegister_CSBoard_T5  = register.RawValue; 
                    CSBoard_T5 =  register.RegCSBoard_T5.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T6:
                    FullRegister_CSBoard_T6  = register.RawValue; 
                    CSBoard_T6 =  register.RegCSBoard_T6.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T7:
                    FullRegister_CSBoard_T7  = register.RawValue; 
                    CSBoard_T7 =  register.RegCSBoard_T7.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT0I0:
                    FullRegister_CSBoard_Current0I0  = register.RawValue; 
                    CSBoard_Current0I0 =  register.RegCSBoard_Current0I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT0I1:
                    FullRegister_CSBoard_Current0I1  = register.RawValue; 
                    CSBoard_Current0I1 =  register.RegCSBoard_Current0I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT0I2:
                    FullRegister_CSBoard_Current0I2  = register.RawValue; 
                    CSBoard_Current0I2 =  register.RegCSBoard_Current0I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT1I0:
                    FullRegister_CSBoard_Current1I0  = register.RawValue; 
                    CSBoard_Current1I0 =  register.RegCSBoard_Current1I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT1I1:
                    FullRegister_CSBoard_Current1I1  = register.RawValue; 
                    CSBoard_Current1I1 =  register.RegCSBoard_Current1I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT1I2:
                    FullRegister_CSBoard_Current1I2  = register.RawValue; 
                    CSBoard_Current1I2 =  register.RegCSBoard_Current1I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT2I0:
                    FullRegister_CSBoard_Current2I0  = register.RawValue; 
                    CSBoard_Current2I0 =  register.RegCSBoard_Current2I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT2I1:
                    FullRegister_CSBoard_Current2I1  = register.RawValue; 
                    CSBoard_Current2I1 =  register.RegCSBoard_Current2I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT2I2:
                    FullRegister_CSBoard_Current2I2  = register.RawValue; 
                    CSBoard_Current2I2 =  register.RegCSBoard_Current2I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT3I0:
                    FullRegister_CSBoard_Current3I0  = register.RawValue; 
                    CSBoard_Current3I0 =  register.RegCSBoard_Current3I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT3I1:
                    FullRegister_CSBoard_Current3I1  = register.RawValue; 
                    CSBoard_Current3I1 =  register.RegCSBoard_Current3I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT3I2:
                    FullRegister_CSBoard_Current3I2  = register.RawValue; 
                    CSBoard_Current3I2 =  register.RegCSBoard_Current3I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT4I0:
                    FullRegister_CSBoard_Current4I0  = register.RawValue; 
                    CSBoard_Current4I0 =  register.RegCSBoard_Current4I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT4I1:
                    FullRegister_CSBoard_Current4I1  = register.RawValue; 
                    CSBoard_Current4I1 =  register.RegCSBoard_Current4I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT4I2:
                    FullRegister_CSBoard_Current4I2  = register.RawValue; 
                    CSBoard_Current4I2 =  register.RegCSBoard_Current4I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT5I0:
                    FullRegister_CSBoard_Current5I0  = register.RawValue; 
                    CSBoard_Current5I0 =  register.RegCSBoard_Current5I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT5I1:
                    FullRegister_CSBoard_Current5I1  = register.RawValue; 
                    CSBoard_Current5I1 =  register.RegCSBoard_Current5I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT5I2:
                    FullRegister_CSBoard_Current5I2  = register.RawValue; 
                    CSBoard_Current5I2 =  register.RegCSBoard_Current5I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT6I0:
                    FullRegister_CSBoard_Current6I0  = register.RawValue; 
                    CSBoard_Current6I0 =  register.RegCSBoard_Current6I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT6I1:
                    FullRegister_CSBoard_Current6I1  = register.RawValue; 
                    CSBoard_Current6I1 =  register.RegCSBoard_Current6I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT6I2:
                    FullRegister_CSBoard_Current6I2  = register.RawValue; 
                    CSBoard_Current6I2 =  register.RegCSBoard_Current6I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT7I0:
                    FullRegister_CSBoard_Current7I0  = register.RawValue; 
                    CSBoard_Current7I0 =  register.RegCSBoard_Current7I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT7I1:
                    FullRegister_CSBoard_Current7I1  = register.RawValue; 
                    CSBoard_Current7I1 =  register.RegCSBoard_Current7I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT7I2:
                    FullRegister_CSBoard_Current7I2  = register.RawValue; 
                    CSBoard_Current7I2 =  register.RegCSBoard_Current7I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_0:
                    FullRegister_TE_Addr_0  = register.RawValue; 
                    TE_Addr_0_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_0_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_0_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_0_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_0_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_0_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_0_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_0_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_0_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_0_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_0_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_0_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_0_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_0_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_0_SET:
                    FullRegister_TE_Addr_0_Set  = register.RawValue; 
                    TE_Addr_0_Set_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_0_Set_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_0_Set_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_0_Set_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_0_Set_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_0_Set_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_0_Set_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_0_Set_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_0_Set_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_0_Set_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_0_Set_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_0_Set_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_0_Set_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_0_Set_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_0_CLEAR:
                    FullRegister_TE_Addr_0_Clear  = register.RawValue; 
                    TE_Addr_0_Clear_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_0_Clear_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_0_Clear_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_0_Clear_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_0_Clear_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_0_Clear_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_0_Clear_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_0_Clear_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_0_Clear_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_0_Clear_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_0_Clear_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_0_Clear_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_0_Clear_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_0_Clear_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_1:
                    FullRegister_TE_Addr_1  = register.RawValue; 
                    TE_Addr_1_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_1_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_1_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_1_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_1_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_1_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_1_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_1_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_1_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_1_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_1_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_1_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_1_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_1_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_1_SET:
                    FullRegister_TE_Addr_1_Set  = register.RawValue; 
                    TE_Addr_1_Set_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_1_Set_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_1_Set_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_1_Set_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_1_Set_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_1_Set_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_1_Set_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_1_Set_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_1_Set_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_1_Set_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_1_Set_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_1_Set_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_1_Set_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_1_Set_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_1_CLEAR:
                    FullRegister_TE_Addr_1_Clear  = register.RawValue; 
                    TE_Addr_1_Clear_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_1_Clear_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_1_Clear_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_1_Clear_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_1_Clear_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_1_Clear_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_1_Clear_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_1_Clear_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_1_Clear_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_1_Clear_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_1_Clear_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_1_Clear_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_1_Clear_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_1_Clear_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_2:
                    FullRegister_TE_Addr_2  = register.RawValue; 
                    TE_Addr_2_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_2_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_2_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_2_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_2_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_2_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_2_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_2_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_2_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_2_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_2_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_2_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_2_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_2_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_2_SET:
                    FullRegister_TE_Addr_2_Set  = register.RawValue; 
                    TE_Addr_2_Set_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_2_Set_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_2_Set_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_2_Set_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_2_Set_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_2_Set_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_2_Set_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_2_Set_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_2_Set_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_2_Set_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_2_Set_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_2_Set_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_2_Set_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_2_Set_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_2_CLEAR:
                    FullRegister_TE_Addr_2_Clear  = register.RawValue; 
                    TE_Addr_2_Clear_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_2_Clear_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_2_Clear_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_2_Clear_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_2_Clear_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_2_Clear_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_2_Clear_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_2_Clear_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_2_Clear_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_2_Clear_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_2_Clear_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_2_Clear_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_2_Clear_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_2_Clear_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_3:
                    FullRegister_TE_Addr_3  = register.RawValue; 
                    TE_Addr_3_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_3_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_3_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_3_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_3_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_3_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_3_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_3_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_3_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_3_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_3_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_3_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_3_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_3_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_3_SET:
                    FullRegister_TE_Addr_3_Set  = register.RawValue; 
                    TE_Addr_3_Set_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_3_Set_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_3_Set_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_3_Set_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_3_Set_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_3_Set_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_3_Set_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_3_Set_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_3_Set_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_3_Set_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_3_Set_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_3_Set_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_3_Set_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_3_Set_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_3_CLEAR:
                    FullRegister_TE_Addr_3_Clear  = register.RawValue; 
                    TE_Addr_3_Clear_ScanEnabled = (Enabled) register.RegTE_Config.ScanEnabled;
                    TE_Addr_3_Clear_Detected =  register.RegTE_Config.Detected;
                    TE_Addr_3_Clear_Type = (TE_Types) register.RegTE_Config.Type;
                    TE_Addr_3_Clear_SEL_CAN0 = (Enabled) register.RegTE_Config.SEL_CAN0;
                    TE_Addr_3_Clear_SEL_CAN1 = (Enabled) register.RegTE_Config.SEL_CAN1;
                    TE_Addr_3_Clear_SEL_RS485 = (Enabled) register.RegTE_Config.SEL_RS485;
                    TE_Addr_3_Clear_SEL_I2C = (Enabled) register.RegTE_Config.SEL_I2C;
                    TE_Addr_3_Clear_SEL_RS422 = (Enabled) register.RegTE_Config.SEL_RS422;
                    TE_Addr_3_Clear_SEL_SPI = (Enabled) register.RegTE_Config.SEL_SPI;
                    TE_Addr_3_Clear_SEL_UART = (Enabled) register.RegTE_Config.SEL_UART;
                    TE_Addr_3_Clear_Power = (Enabled) register.RegTE_Config.Power;
                    TE_Addr_3_Clear_Enable = (Enabled) register.RegTE_Config.Enable;
                    TE_Addr_3_Clear_nReset = (Enabled) register.RegTE_Config.nReset;
                    TE_Addr_3_Clear_COMM_TR = (Enabled) register.RegTE_Config.COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_0:
                    FullRegister_MTC_Addr_0  = register.RawValue; 
                    MTC_Addr_0_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_0_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_0_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_0_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_0_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_0_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_0_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_0_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_0_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_0_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_0_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_0_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_0_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_0_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_0_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_0_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_0_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_0_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_0_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_0_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_0_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_0_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_0_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_0_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_0_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_0_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_0_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_0_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_0_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_0_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_0_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_0_SET:
                    FullRegister_MTC_Addr_0_Set  = register.RawValue; 
                    MTC_Addr_0_Set_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_0_Set_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_0_Set_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_0_Set_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_0_Set_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_0_Set_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_0_Set_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_0_Set_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_0_Set_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_0_Set_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_0_Set_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_0_Set_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_0_Set_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_0_Set_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_0_Set_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_0_Set_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_0_Set_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_0_Set_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_0_Set_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_0_Set_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_0_Set_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_0_Set_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_0_Set_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_0_Set_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_0_Set_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_0_Set_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_0_Set_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_0_Set_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_0_Set_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_0_Set_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_0_Set_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_0_CLEAR:
                    FullRegister_MTC_Addr_0_Clear  = register.RawValue; 
                    MTC_Addr_0_Clear_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_0_Clear_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_0_Clear_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_0_Clear_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_0_Clear_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_0_Clear_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_0_Clear_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_0_Clear_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_0_Clear_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_0_Clear_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_0_Clear_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_0_Clear_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_0_Clear_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_0_Clear_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_0_Clear_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_0_Clear_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_0_Clear_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_0_Clear_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_0_Clear_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_0_Clear_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_0_Clear_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_0_Clear_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_0_Clear_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_0_Clear_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_0_Clear_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_0_Clear_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_0_Clear_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_0_Clear_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_0_Clear_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_0_Clear_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_0_Clear_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_1:
                    FullRegister_MTC_Addr_1  = register.RawValue; 
                    MTC_Addr_1_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_1_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_1_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_1_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_1_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_1_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_1_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_1_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_1_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_1_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_1_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_1_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_1_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_1_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_1_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_1_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_1_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_1_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_1_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_1_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_1_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_1_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_1_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_1_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_1_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_1_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_1_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_1_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_1_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_1_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_1_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_1_SET:
                    FullRegister_MTC_Addr_1_Set  = register.RawValue; 
                    MTC_Addr_1_Set_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_1_Set_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_1_Set_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_1_Set_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_1_Set_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_1_Set_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_1_Set_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_1_Set_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_1_Set_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_1_Set_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_1_Set_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_1_Set_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_1_Set_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_1_Set_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_1_Set_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_1_Set_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_1_Set_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_1_Set_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_1_Set_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_1_Set_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_1_Set_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_1_Set_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_1_Set_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_1_Set_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_1_Set_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_1_Set_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_1_Set_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_1_Set_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_1_Set_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_1_Set_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_1_Set_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_1_CLEAR:
                    FullRegister_MTC_Addr_1_Clear  = register.RawValue; 
                    MTC_Addr_1_Clear_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_1_Clear_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_1_Clear_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_1_Clear_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_1_Clear_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_1_Clear_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_1_Clear_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_1_Clear_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_1_Clear_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_1_Clear_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_1_Clear_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_1_Clear_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_1_Clear_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_1_Clear_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_1_Clear_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_1_Clear_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_1_Clear_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_1_Clear_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_1_Clear_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_1_Clear_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_1_Clear_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_1_Clear_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_1_Clear_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_1_Clear_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_1_Clear_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_1_Clear_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_1_Clear_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_1_Clear_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_1_Clear_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_1_Clear_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_1_Clear_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_2:
                    FullRegister_MTC_Addr_2  = register.RawValue; 
                    MTC_Addr_2_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_2_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_2_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_2_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_2_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_2_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_2_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_2_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_2_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_2_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_2_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_2_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_2_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_2_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_2_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_2_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_2_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_2_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_2_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_2_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_2_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_2_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_2_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_2_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_2_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_2_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_2_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_2_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_2_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_2_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_2_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_2_SET:
                    FullRegister_MTC_Addr_2_Set  = register.RawValue; 
                    MTC_Addr_2_Set_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_2_Set_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_2_Set_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_2_Set_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_2_Set_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_2_Set_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_2_Set_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_2_Set_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_2_Set_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_2_Set_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_2_Set_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_2_Set_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_2_Set_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_2_Set_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_2_Set_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_2_Set_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_2_Set_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_2_Set_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_2_Set_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_2_Set_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_2_Set_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_2_Set_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_2_Set_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_2_Set_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_2_Set_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_2_Set_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_2_Set_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_2_Set_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_2_Set_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_2_Set_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_2_Set_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_2_CLEAR:
                    FullRegister_MTC_Addr_2_Clear  = register.RawValue; 
                    MTC_Addr_2_Clear_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_2_Clear_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_2_Clear_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_2_Clear_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_2_Clear_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_2_Clear_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_2_Clear_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_2_Clear_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_2_Clear_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_2_Clear_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_2_Clear_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_2_Clear_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_2_Clear_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_2_Clear_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_2_Clear_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_2_Clear_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_2_Clear_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_2_Clear_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_2_Clear_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_2_Clear_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_2_Clear_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_2_Clear_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_2_Clear_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_2_Clear_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_2_Clear_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_2_Clear_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_2_Clear_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_2_Clear_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_2_Clear_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_2_Clear_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_2_Clear_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_3:
                    FullRegister_MTC_Addr_3  = register.RawValue; 
                    MTC_Addr_3_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_3_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_3_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_3_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_3_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_3_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_3_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_3_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_3_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_3_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_3_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_3_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_3_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_3_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_3_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_3_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_3_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_3_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_3_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_3_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_3_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_3_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_3_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_3_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_3_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_3_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_3_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_3_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_3_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_3_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_3_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_3_SET:
                    FullRegister_MTC_Addr_3_Set  = register.RawValue; 
                    MTC_Addr_3_Set_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_3_Set_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_3_Set_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_3_Set_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_3_Set_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_3_Set_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_3_Set_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_3_Set_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_3_Set_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_3_Set_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_3_Set_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_3_Set_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_3_Set_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_3_Set_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_3_Set_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_3_Set_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_3_Set_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_3_Set_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_3_Set_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_3_Set_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_3_Set_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_3_Set_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_3_Set_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_3_Set_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_3_Set_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_3_Set_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_3_Set_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_3_Set_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_3_Set_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_3_Set_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_3_Set_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_3_CLEAR:
                    FullRegister_MTC_Addr_3_Clear  = register.RawValue; 
                    MTC_Addr_3_Clear_ScanEnabled = (Enabled) register.RegMTC_Config.ScanEnabled;
                    MTC_Addr_3_Clear_Detected =  register.RegMTC_Config.Detected;
                    MTC_Addr_3_Clear_Type =  register.RegMTC_Config.Type;
                    MTC_Addr_3_Clear_ENABLE_1 = (Enabled) register.RegMTC_Config.ENABLE_1;
                    MTC_Addr_3_Clear_ENABLE_2 = (Enabled) register.RegMTC_Config.ENABLE_2;
                    MTC_Addr_3_Clear_SEL_I2C_1 = (Enabled) register.RegMTC_Config.SEL_I2C_1;
                    MTC_Addr_3_Clear_SEL_I2C_2 = (Enabled) register.RegMTC_Config.SEL_I2C_2;
                    MTC_Addr_3_Clear_SEL_UART_1 = (Enabled) register.RegMTC_Config.SEL_UART_1;
                    MTC_Addr_3_Clear_SEL_UART_2 = (Enabled) register.RegMTC_Config.SEL_UART_2;
                    MTC_Addr_3_Clear_SEL_UART_3 = (Enabled) register.RegMTC_Config.SEL_UART_3;
                    MTC_Addr_3_Clear_SEL_UART_4 = (Enabled) register.RegMTC_Config.SEL_UART_4;
                    MTC_Addr_3_Clear_SEL_UART_5 = (Enabled) register.RegMTC_Config.SEL_UART_5;
                    MTC_Addr_3_Clear_SEL_UART_6 = (Enabled) register.RegMTC_Config.SEL_UART_6;
                    MTC_Addr_3_Clear_SEL_VBAT = (Enabled) register.RegMTC_Config.SEL_VBAT;
                    MTC_Addr_3_Clear_SEL_VBAT_ALT = (Enabled) register.RegMTC_Config.SEL_VBAT_ALT;
                    MTC_Addr_3_Clear_SEL_VBAT_FPGA = (Enabled) register.RegMTC_Config.SEL_VBAT_FPGA;
                    MTC_Addr_3_Clear_SEL_nRESET_1 = (Enabled) register.RegMTC_Config.SEL_nRESET_1;
                    MTC_Addr_3_Clear_SEL_nRESET_2 = (Enabled) register.RegMTC_Config.SEL_nRESET_2;
                    MTC_Addr_3_Clear_SEL_nRESET_3 = (Enabled) register.RegMTC_Config.SEL_nRESET_3;
                    MTC_Addr_3_Clear_SEL_CS_1 = (Enabled) register.RegMTC_Config.SEL_CS_1;
                    MTC_Addr_3_Clear_SEL_CS_2 = (Enabled) register.RegMTC_Config.SEL_CS_2;
                    MTC_Addr_3_Clear_SEL_CS_3 = (Enabled) register.RegMTC_Config.SEL_CS_3;
                    MTC_Addr_3_Clear_SEL_CS_4 = (Enabled) register.RegMTC_Config.SEL_CS_4;
                    MTC_Addr_3_Clear_SEL_CS_5 = (Enabled) register.RegMTC_Config.SEL_CS_5;
                    MTC_Addr_3_Clear_SEL_CS_6 = (Enabled) register.RegMTC_Config.SEL_CS_6;
                    MTC_Addr_3_Clear_SEL_SPI_1 = (Enabled) register.RegMTC_Config.SEL_SPI_1;
                    MTC_Addr_3_Clear_SEL_SPI_2 = (Enabled) register.RegMTC_Config.SEL_SPI_2;
                    MTC_Addr_3_Clear_SEL_CAN_1 = (Enabled) register.RegMTC_Config.SEL_CAN_1;
                    MTC_Addr_3_Clear_SEL_CAN_2 = (Enabled) register.RegMTC_Config.SEL_CAN_2;
                    MTC_Addr_3_Clear_SEL_CAN_3 = (Enabled) register.RegMTC_Config.SEL_CAN_3;
                    MTC_Addr_3_Clear_SEL_RS422 = (Enabled) register.RegMTC_Config.SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_RTOS_STATUS0:
                    FullRegister_RTOS_Status0  = register.RawValue; 
                    RTOS_Status0_uartRxHBOverflow =  register.RegRTOS_Status0.uartRxHBOverflow;
                    RTOS_Status0_uartRxSBOverflow =  register.RegRTOS_Status0.uartRxSBOverflow;
                    RTOS_Status0_uartTxSBOverflow =  register.RegRTOS_Status0.uartTxSBOverflow;
                    RTOS_Status0_uartTxHBOverflow =  register.RegRTOS_Status0.uartTxHBOverflow;
                    RTOS_Status0_I2CTargetIncomingOverflow =  register.RegRTOS_Status0.I2CTargetIncomingOverflow;
                    RTOS_Status0_I2CTargetOutgoingOverflow =  register.RegRTOS_Status0.I2CTargetOutgoingOverflow;
                    RTOS_Status0_CANTargetIncomingOverflow =  register.RegRTOS_Status0.CANTargetIncomingOverflow;
                    RTOS_Status0_CANInterruptBufferOverflow =  register.RegRTOS_Status0.CANInterruptBufferOverflow;
                    RTOS_Status0_CANTargetOutgoingOverflow =  register.RegRTOS_Status0.CANTargetOutgoingOverflow;
                    RTOS_Status0_UARTTargetIncomingOverflow =  register.RegRTOS_Status0.UARTTargetIncomingOverflow;
                    RTOS_Status0_UARTTargetTxHBOverflow =  register.RegRTOS_Status0.UARTTargetTxHBOverflow;
                    RTOS_Status0_UARTTargetRxHBOverflow =  register.RegRTOS_Status0.UARTTargetRxHBOverflow;
                    RTOS_Status0_UARTTargetOutgoingOverflow =  register.RegRTOS_Status0.UARTTargetOutgoingOverflow;
                    RTOS_Status0_GSETargetIncomingOverflow =  register.RegRTOS_Status0.GSETargetIncomingOverflow;
                    RTOS_Status0_GSETargetOutgoingOverflow =  register.RegRTOS_Status0.GSETargetOutgoingOverflow;
                    RTOS_Status0_SERMUX_CRC_Error =  register.RegRTOS_Status0.SERMUX_CRC_Error;
                    break;

                case OBCRegisterAddress.OBC_REG_UTILI2CCONFA:
                    FullRegister_UtilI2CConfA  = register.RawValue; 
                    UtilI2CConfA_Reset =  register.RegUtilI2CConfA.Reset;
                    UtilI2CConfA_SPD =  register.RegUtilI2CConfA.SPD;
                    break;

                case OBCRegisterAddress.OBC_REG_UTILI2CSTATUS:
                    FullRegister_UtilI2CStatus  = register.RawValue; 
                    UtilI2CStatus =  register.RegUtilI2CStatus.value;
                    break;

                case OBCRegisterAddress.OBC_REG_PREVIOUSENDPOINT:
                    FullRegister_PreviousEndpoint  = register.RawValue; 
                    PreviousEndpoint_Number =  register.RegPreviousEndpoint.Number;
                    break;

            }
        }

        public void EncodeTo(ref RegisterData register, OBCRegisterAddress address)
        {
            switch (address)
            {
                case OBCRegisterAddress.OBC_REG_BOARD_ID:
                    register.RegBoard_ID.ccIdentifier = Board_ID_ccIdentifier;
                    register.RegBoard_ID.id0 = Board_ID_id0;
                    register.RegBoard_ID.id1 = Board_ID_id1;
                    register.RegBoard_ID.id2 = Board_ID_id2;
                    break;

                case OBCRegisterAddress.OBC_REG_FW_VERSION:
                    register.RegVersion.major_version = FW_Version_major_version;
                    register.RegVersion.minor_version = FW_Version_minor_version;
                    register.RegVersion.patch_version = FW_Version_patch_version;
                    break;

                case OBCRegisterAddress.OBC_REG_HW_VERSION:
                    register.RegVersion.major_version = HW_Version_major_version;
                    register.RegVersion.minor_version = HW_Version_minor_version;
                    register.RegVersion.patch_version = HW_Version_patch_version;
                    break;

                case OBCRegisterAddress.OBC_REG_SCRATCHPAD:
                    register.RegScratchpad.value = Scratchpad;
                    break;

                case OBCRegisterAddress.OBC_REG_SUPPORTED_BOARDS:
                    register.RegSupported_Boards.value = Supported_Boards;
                    break;

                case OBCRegisterAddress.OBC_REG_CONFIGURED_BOARDS:
                    register.RegConfigured_Boards.value = (byte) Configured_Boards;
                    break;

                case OBCRegisterAddress.OBC_REG_UPTIME:
                    register.RegUptime.value = Uptime;
                    break;

                case OBCRegisterAddress.OBC_REG_EVENT_CONFA:
                    register.RegEvent_ConfA.count = Event_ConfA_count;
                    break;

                case OBCRegisterAddress.OBC_REG_EVENT:
                    register.RegEvent.section = Event_section;
                    register.RegEvent.detail = Event_detail;
                    register.RegEvent.timestamp = Event_timestamp;
                    break;

                case OBCRegisterAddress.OBC_REG_CONFPOWER:
                    register.RegConfPower.voltage5Toggle = (byte) ConfPower_voltage5Toggle;
                    register.RegConfPower.voltage3Toggle = (byte) ConfPower_voltage3Toggle;
                    register.RegConfPower.voltageVBatToggle = (byte) ConfPower_voltageVBatToggle;
                    register.RegConfPower.voltageVBatAltToggle = (byte) ConfPower_voltageVBatAltToggle;
                    register.RegConfPower.voltage3UtilToggle = (byte) ConfPower_voltage3UtilToggle;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_V3:
                    register.RegMeasureVI.voltage = MeasureVI_V3_voltage;
                    register.RegMeasureVI.current = MeasureVI_V3_current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_V3:
                    register.RegMeasurePower.power = MeasurePower_V3_power;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_V5:
                    register.RegMeasureVI.voltage = MeasureVI_V5_voltage;
                    register.RegMeasureVI.current = MeasureVI_V5_current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_V5:
                    register.RegMeasurePower.power = MeasurePower_V5_power;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_VBAT:
                    register.RegMeasureVI.voltage = MeasureVI_VBat_voltage;
                    register.RegMeasureVI.current = MeasureVI_VBat_current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_VBAT:
                    register.RegMeasurePower.power = MeasurePower_VBat_power;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_VBATALT:
                    register.RegMeasureVI.voltage = MeasureVI_VBatAlt_voltage;
                    register.RegMeasureVI.current = MeasureVI_VBatAlt_current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_VBATALT:
                    register.RegMeasurePower.power = MeasurePower_VBatAlt_power;
                    break;

                case OBCRegisterAddress.OBC_REG_I2CCONFA:
                    register.RegI2CConfA.TRDEL = I2CConfA_TRDEL;
                    register.RegI2CConfA.WRDEL = I2CConfA_WRDEL;
                    register.RegI2CConfA.SPD = I2CConfA_SPD;
                    break;

                case OBCRegisterAddress.OBC_REG_I2CCONFB:
                    register.RegI2CConfB.ADDR = I2CConfB_ADDR;
                    break;

                case OBCRegisterAddress.OBC_REG_MULTICONF0:
                    register.RegMultiConf0.Detected = (byte) MultiConf0_Detected;
                    register.RegMultiConf0.AutoCLR = (byte) MultiConf0_AutoCLR;
                    register.RegMultiConf0.ScanEnabled = (byte) MultiConf0_ScanEnabled;
                    register.RegMultiConf0.FanPos1 = (byte) MultiConf0_FanPos1;
                    register.RegMultiConf0.FanPos2 = (byte) MultiConf0_FanPos2;
                    register.RegMultiConf0.FanPos3 = (byte) MultiConf0_FanPos3;
                    register.RegMultiConf0.FanPos4 = (byte) MultiConf0_FanPos4;
                    break;

                case OBCRegisterAddress.OBC_REG_CONFTEMPSENSE:
                    register.RegConfTempSense.EnableMeasurements = (byte) ConfTempSense_EnableMeasurements;
                    break;

                case OBCRegisterAddress.OBC_REG_CANCONFA:
                    register.RegCANConfA.BaudRate = CANConfA_BaudRate;
                    register.RegCANConfA.EnableRetries = (byte) CANConfA_EnableRetries;
                    register.RegCANConfA.FlipCanBytes = (byte) CANConfA_FlipCanBytes;
                    break;

                case OBCRegisterAddress.OBC_REG_CANCONFB:
                    register.RegCANConfB.Address = CANConfB_Address;
                    break;

                case OBCRegisterAddress.OBC_REG_SERIALCONF:
                    register.RegSerialConf.SerialMode = (byte) SerialConf_SerialMode;
                    register.RegSerialConf.ParityEnabled = (byte) SerialConf_ParityEnabled;
                    register.RegSerialConf.ParityMode = (byte) SerialConf_ParityMode;
                    register.RegSerialConf.BaudRates = (byte) SerialConf_BaudRates;
                    break;

                case OBCRegisterAddress.OBC_REG_PC104PINS:
                    register.RegPC104Pins.ENA = (byte) PC104Pins_ENA;
                    register.RegPC104Pins.nRST = (byte) PC104Pins_nRST;
                    register.RegPC104Pins.RDY = (byte) PC104Pins_RDY;
                    break;

                case OBCRegisterAddress.OBC_REG_XTXMULTITESTER:
                    register.RegXTXMultitester.POS1_XTX_EN = (byte) XTXMultitester_POS1_XTX_EN;
                    register.RegXTXMultitester.POS1_XTX_Power = (byte) XTXMultitester_POS1_XTX_Power;
                    register.RegXTXMultitester.POS1_XTX_nReset = (byte) XTXMultitester_POS1_XTX_nReset;
                    register.RegXTXMultitester.POS2_XTX_EN = (byte) XTXMultitester_POS2_XTX_EN;
                    register.RegXTXMultitester.POS2_XTX_Power = (byte) XTXMultitester_POS2_XTX_Power;
                    register.RegXTXMultitester.POS2_XTX_nReset = (byte) XTXMultitester_POS2_XTX_nReset;
                    register.RegXTXMultitester.POS3_XTX_EN = (byte) XTXMultitester_POS3_XTX_EN;
                    register.RegXTXMultitester.POS3_XTX_Power = (byte) XTXMultitester_POS3_XTX_Power;
                    register.RegXTXMultitester.POS3_XTX_nReset = (byte) XTXMultitester_POS3_XTX_nReset;
                    register.RegXTXMultitester.POS4_XTX_EN = (byte) XTXMultitester_POS4_XTX_EN;
                    register.RegXTXMultitester.POS4_XTX_Power = (byte) XTXMultitester_POS4_XTX_Power;
                    register.RegXTXMultitester.POS4_XTX_nReset = (byte) XTXMultitester_POS4_XTX_nReset;
                    break;

                case OBCRegisterAddress.OBC_REG_RFRELAYSCONF:
                    register.RegRFRelaysConf.RFSW1_Detected = (byte) RFRelaysConf_RFSW1_Detected;
                    register.RegRFRelaysConf.RFSW2_Detected = (byte) RFRelaysConf_RFSW2_Detected;
                    register.RegRFRelaysConf.ScanEnabled = (byte) RFRelaysConf_ScanEnabled;
                    register.RegRFRelaysConf.RfSw1Chan = RFRelaysConf_RfSw1Chan;
                    register.RegRFRelaysConf.RfSw2Chan = RFRelaysConf_RfSw2Chan;
                    break;

                case OBCRegisterAddress.OBC_REG_MULTICONF1_STATUS:
                    register.RegMultitester.POS1_Enable = (byte) MultiConf1_Status_POS1_Enable;
                    register.RegMultitester.POS1_Power = (byte) MultiConf1_Status_POS1_Power;
                    register.RegMultitester.POS1_nReset = (byte) MultiConf1_Status_POS1_nReset;
                    register.RegMultitester.POS1_FAN = (byte) MultiConf1_Status_POS1_FAN;
                    register.RegMultitester.POS2_Enable = (byte) MultiConf1_Status_POS2_Enable;
                    register.RegMultitester.POS2_Power = (byte) MultiConf1_Status_POS2_Power;
                    register.RegMultitester.POS2_nReset = (byte) MultiConf1_Status_POS2_nReset;
                    register.RegMultitester.POS2_FAN = (byte) MultiConf1_Status_POS2_FAN;
                    register.RegMultitester.POS3_Enable = (byte) MultiConf1_Status_POS3_Enable;
                    register.RegMultitester.POS3_Power = (byte) MultiConf1_Status_POS3_Power;
                    register.RegMultitester.POS3_nReset = (byte) MultiConf1_Status_POS3_nReset;
                    register.RegMultitester.POS3_FAN = (byte) MultiConf1_Status_POS3_FAN;
                    register.RegMultitester.POS4_Enable = (byte) MultiConf1_Status_POS4_Enable;
                    register.RegMultitester.POS4_Power = (byte) MultiConf1_Status_POS4_Power;
                    register.RegMultitester.POS4_nReset = (byte) MultiConf1_Status_POS4_nReset;
                    register.RegMultitester.POS4_FAN = (byte) MultiConf1_Status_POS4_FAN;
                    break;

                case OBCRegisterAddress.OBC_REG_MULTICONF1_SET:
                    register.RegMultitester.POS1_Enable = (byte) MultiConf1_Set_POS1_Enable;
                    register.RegMultitester.POS1_Power = (byte) MultiConf1_Set_POS1_Power;
                    register.RegMultitester.POS1_nReset = (byte) MultiConf1_Set_POS1_nReset;
                    register.RegMultitester.POS1_FAN = (byte) MultiConf1_Set_POS1_FAN;
                    register.RegMultitester.POS2_Enable = (byte) MultiConf1_Set_POS2_Enable;
                    register.RegMultitester.POS2_Power = (byte) MultiConf1_Set_POS2_Power;
                    register.RegMultitester.POS2_nReset = (byte) MultiConf1_Set_POS2_nReset;
                    register.RegMultitester.POS2_FAN = (byte) MultiConf1_Set_POS2_FAN;
                    register.RegMultitester.POS3_Enable = (byte) MultiConf1_Set_POS3_Enable;
                    register.RegMultitester.POS3_Power = (byte) MultiConf1_Set_POS3_Power;
                    register.RegMultitester.POS3_nReset = (byte) MultiConf1_Set_POS3_nReset;
                    register.RegMultitester.POS3_FAN = (byte) MultiConf1_Set_POS3_FAN;
                    register.RegMultitester.POS4_Enable = (byte) MultiConf1_Set_POS4_Enable;
                    register.RegMultitester.POS4_Power = (byte) MultiConf1_Set_POS4_Power;
                    register.RegMultitester.POS4_nReset = (byte) MultiConf1_Set_POS4_nReset;
                    register.RegMultitester.POS4_FAN = (byte) MultiConf1_Set_POS4_FAN;
                    break;

                case OBCRegisterAddress.OBC_REG_MULTICONF1_CLEAR:
                    register.RegMultitester.POS1_Enable = (byte) MultiConf1_Clear_POS1_Enable;
                    register.RegMultitester.POS1_Power = (byte) MultiConf1_Clear_POS1_Power;
                    register.RegMultitester.POS1_nReset = (byte) MultiConf1_Clear_POS1_nReset;
                    register.RegMultitester.POS1_FAN = (byte) MultiConf1_Clear_POS1_FAN;
                    register.RegMultitester.POS2_Enable = (byte) MultiConf1_Clear_POS2_Enable;
                    register.RegMultitester.POS2_Power = (byte) MultiConf1_Clear_POS2_Power;
                    register.RegMultitester.POS2_nReset = (byte) MultiConf1_Clear_POS2_nReset;
                    register.RegMultitester.POS2_FAN = (byte) MultiConf1_Clear_POS2_FAN;
                    register.RegMultitester.POS3_Enable = (byte) MultiConf1_Clear_POS3_Enable;
                    register.RegMultitester.POS3_Power = (byte) MultiConf1_Clear_POS3_Power;
                    register.RegMultitester.POS3_nReset = (byte) MultiConf1_Clear_POS3_nReset;
                    register.RegMultitester.POS3_FAN = (byte) MultiConf1_Clear_POS3_FAN;
                    register.RegMultitester.POS4_Enable = (byte) MultiConf1_Clear_POS4_Enable;
                    register.RegMultitester.POS4_Power = (byte) MultiConf1_Clear_POS4_Power;
                    register.RegMultitester.POS4_nReset = (byte) MultiConf1_Clear_POS4_nReset;
                    register.RegMultitester.POS4_FAN = (byte) MultiConf1_Clear_POS4_FAN;
                    break;

                case OBCRegisterAddress.OBC_REG_XDCCONFIG:
                    register.RegXDCConfig.ADDR = (byte) XDCConfig_ADDR;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T0:
                    register.RegCSBoard_T0.value = CSBoard_T0;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T1:
                    register.RegCSBoard_T1.value = CSBoard_T1;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T2:
                    register.RegCSBoard_T2.value = CSBoard_T2;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T3:
                    register.RegCSBoard_T3.value = CSBoard_T3;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T4:
                    register.RegCSBoard_T4.value = CSBoard_T4;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T5:
                    register.RegCSBoard_T5.value = CSBoard_T5;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T6:
                    register.RegCSBoard_T6.value = CSBoard_T6;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T7:
                    register.RegCSBoard_T7.value = CSBoard_T7;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT0I0:
                    register.RegCSBoard_Current0I0.value = CSBoard_Current0I0;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT0I1:
                    register.RegCSBoard_Current0I1.value = CSBoard_Current0I1;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT0I2:
                    register.RegCSBoard_Current0I2.value = CSBoard_Current0I2;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT1I0:
                    register.RegCSBoard_Current1I0.value = CSBoard_Current1I0;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT1I1:
                    register.RegCSBoard_Current1I1.value = CSBoard_Current1I1;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT1I2:
                    register.RegCSBoard_Current1I2.value = CSBoard_Current1I2;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT2I0:
                    register.RegCSBoard_Current2I0.value = CSBoard_Current2I0;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT2I1:
                    register.RegCSBoard_Current2I1.value = CSBoard_Current2I1;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT2I2:
                    register.RegCSBoard_Current2I2.value = CSBoard_Current2I2;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT3I0:
                    register.RegCSBoard_Current3I0.value = CSBoard_Current3I0;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT3I1:
                    register.RegCSBoard_Current3I1.value = CSBoard_Current3I1;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT3I2:
                    register.RegCSBoard_Current3I2.value = CSBoard_Current3I2;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT4I0:
                    register.RegCSBoard_Current4I0.value = CSBoard_Current4I0;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT4I1:
                    register.RegCSBoard_Current4I1.value = CSBoard_Current4I1;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT4I2:
                    register.RegCSBoard_Current4I2.value = CSBoard_Current4I2;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT5I0:
                    register.RegCSBoard_Current5I0.value = CSBoard_Current5I0;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT5I1:
                    register.RegCSBoard_Current5I1.value = CSBoard_Current5I1;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT5I2:
                    register.RegCSBoard_Current5I2.value = CSBoard_Current5I2;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT6I0:
                    register.RegCSBoard_Current6I0.value = CSBoard_Current6I0;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT6I1:
                    register.RegCSBoard_Current6I1.value = CSBoard_Current6I1;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT6I2:
                    register.RegCSBoard_Current6I2.value = CSBoard_Current6I2;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT7I0:
                    register.RegCSBoard_Current7I0.value = CSBoard_Current7I0;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT7I1:
                    register.RegCSBoard_Current7I1.value = CSBoard_Current7I1;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT7I2:
                    register.RegCSBoard_Current7I2.value = CSBoard_Current7I2;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_0:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_0_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_0_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_0_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_0_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_0_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_0_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_0_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_0_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_0_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_0_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_0_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_0_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_0_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_0_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_0_SET:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_0_Set_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_0_Set_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_0_Set_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_0_Set_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_0_Set_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_0_Set_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_0_Set_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_0_Set_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_0_Set_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_0_Set_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_0_Set_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_0_Set_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_0_Set_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_0_Set_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_0_CLEAR:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_0_Clear_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_0_Clear_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_0_Clear_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_0_Clear_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_0_Clear_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_0_Clear_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_0_Clear_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_0_Clear_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_0_Clear_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_0_Clear_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_0_Clear_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_0_Clear_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_0_Clear_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_0_Clear_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_1:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_1_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_1_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_1_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_1_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_1_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_1_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_1_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_1_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_1_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_1_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_1_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_1_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_1_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_1_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_1_SET:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_1_Set_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_1_Set_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_1_Set_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_1_Set_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_1_Set_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_1_Set_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_1_Set_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_1_Set_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_1_Set_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_1_Set_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_1_Set_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_1_Set_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_1_Set_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_1_Set_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_1_CLEAR:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_1_Clear_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_1_Clear_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_1_Clear_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_1_Clear_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_1_Clear_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_1_Clear_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_1_Clear_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_1_Clear_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_1_Clear_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_1_Clear_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_1_Clear_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_1_Clear_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_1_Clear_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_1_Clear_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_2:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_2_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_2_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_2_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_2_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_2_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_2_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_2_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_2_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_2_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_2_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_2_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_2_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_2_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_2_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_2_SET:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_2_Set_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_2_Set_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_2_Set_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_2_Set_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_2_Set_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_2_Set_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_2_Set_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_2_Set_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_2_Set_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_2_Set_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_2_Set_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_2_Set_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_2_Set_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_2_Set_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_2_CLEAR:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_2_Clear_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_2_Clear_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_2_Clear_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_2_Clear_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_2_Clear_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_2_Clear_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_2_Clear_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_2_Clear_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_2_Clear_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_2_Clear_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_2_Clear_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_2_Clear_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_2_Clear_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_2_Clear_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_3:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_3_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_3_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_3_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_3_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_3_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_3_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_3_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_3_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_3_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_3_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_3_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_3_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_3_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_3_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_3_SET:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_3_Set_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_3_Set_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_3_Set_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_3_Set_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_3_Set_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_3_Set_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_3_Set_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_3_Set_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_3_Set_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_3_Set_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_3_Set_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_3_Set_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_3_Set_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_3_Set_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_TE_ADDR_3_CLEAR:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_3_Clear_ScanEnabled;
                    register.RegTE_Config.Detected = TE_Addr_3_Clear_Detected;
                    register.RegTE_Config.Type = (byte) TE_Addr_3_Clear_Type;
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_3_Clear_SEL_CAN0;
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_3_Clear_SEL_CAN1;
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_3_Clear_SEL_RS485;
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_3_Clear_SEL_I2C;
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_3_Clear_SEL_RS422;
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_3_Clear_SEL_SPI;
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_3_Clear_SEL_UART;
                    register.RegTE_Config.Power = (byte) TE_Addr_3_Clear_Power;
                    register.RegTE_Config.Enable = (byte) TE_Addr_3_Clear_Enable;
                    register.RegTE_Config.nReset = (byte) TE_Addr_3_Clear_nReset;
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_3_Clear_COMM_TR;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_0:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_0_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_0_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_0_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_0_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_0_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_0_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_0_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_0_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_0_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_0_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_0_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_0_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_0_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_0_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_0_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_0_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_0_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_0_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_0_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_0_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_0_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_0_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_0_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_0_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_0_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_0_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_0_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_0_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_0_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_0_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_0_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_0_SET:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_0_Set_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_0_Set_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_0_Set_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_0_Set_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_0_Set_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_0_Set_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_0_Set_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_0_Set_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_0_Set_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_0_Set_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_0_Set_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_0_Set_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_0_Set_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_0_Set_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_0_Set_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_0_Set_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_0_Set_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_0_Set_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_0_Set_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_0_Set_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_0_Set_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_0_Set_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_0_Set_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_0_Set_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_0_Set_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_0_Set_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_0_Set_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_0_Set_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_0_Set_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_0_Set_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_0_Set_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_0_CLEAR:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_0_Clear_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_0_Clear_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_0_Clear_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_0_Clear_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_0_Clear_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_0_Clear_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_0_Clear_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_0_Clear_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_0_Clear_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_0_Clear_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_0_Clear_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_0_Clear_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_0_Clear_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_0_Clear_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_0_Clear_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_0_Clear_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_0_Clear_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_0_Clear_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_0_Clear_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_0_Clear_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_0_Clear_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_0_Clear_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_0_Clear_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_0_Clear_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_0_Clear_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_0_Clear_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_0_Clear_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_0_Clear_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_0_Clear_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_0_Clear_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_0_Clear_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_1:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_1_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_1_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_1_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_1_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_1_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_1_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_1_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_1_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_1_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_1_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_1_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_1_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_1_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_1_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_1_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_1_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_1_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_1_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_1_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_1_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_1_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_1_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_1_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_1_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_1_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_1_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_1_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_1_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_1_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_1_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_1_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_1_SET:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_1_Set_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_1_Set_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_1_Set_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_1_Set_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_1_Set_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_1_Set_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_1_Set_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_1_Set_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_1_Set_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_1_Set_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_1_Set_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_1_Set_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_1_Set_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_1_Set_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_1_Set_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_1_Set_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_1_Set_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_1_Set_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_1_Set_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_1_Set_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_1_Set_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_1_Set_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_1_Set_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_1_Set_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_1_Set_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_1_Set_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_1_Set_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_1_Set_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_1_Set_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_1_Set_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_1_Set_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_1_CLEAR:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_1_Clear_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_1_Clear_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_1_Clear_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_1_Clear_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_1_Clear_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_1_Clear_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_1_Clear_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_1_Clear_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_1_Clear_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_1_Clear_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_1_Clear_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_1_Clear_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_1_Clear_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_1_Clear_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_1_Clear_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_1_Clear_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_1_Clear_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_1_Clear_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_1_Clear_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_1_Clear_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_1_Clear_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_1_Clear_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_1_Clear_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_1_Clear_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_1_Clear_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_1_Clear_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_1_Clear_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_1_Clear_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_1_Clear_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_1_Clear_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_1_Clear_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_2:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_2_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_2_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_2_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_2_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_2_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_2_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_2_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_2_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_2_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_2_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_2_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_2_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_2_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_2_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_2_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_2_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_2_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_2_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_2_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_2_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_2_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_2_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_2_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_2_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_2_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_2_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_2_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_2_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_2_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_2_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_2_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_2_SET:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_2_Set_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_2_Set_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_2_Set_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_2_Set_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_2_Set_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_2_Set_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_2_Set_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_2_Set_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_2_Set_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_2_Set_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_2_Set_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_2_Set_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_2_Set_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_2_Set_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_2_Set_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_2_Set_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_2_Set_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_2_Set_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_2_Set_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_2_Set_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_2_Set_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_2_Set_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_2_Set_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_2_Set_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_2_Set_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_2_Set_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_2_Set_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_2_Set_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_2_Set_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_2_Set_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_2_Set_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_2_CLEAR:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_2_Clear_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_2_Clear_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_2_Clear_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_2_Clear_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_2_Clear_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_2_Clear_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_2_Clear_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_2_Clear_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_2_Clear_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_2_Clear_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_2_Clear_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_2_Clear_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_2_Clear_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_2_Clear_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_2_Clear_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_2_Clear_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_2_Clear_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_2_Clear_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_2_Clear_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_2_Clear_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_2_Clear_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_2_Clear_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_2_Clear_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_2_Clear_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_2_Clear_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_2_Clear_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_2_Clear_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_2_Clear_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_2_Clear_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_2_Clear_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_2_Clear_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_3:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_3_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_3_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_3_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_3_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_3_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_3_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_3_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_3_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_3_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_3_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_3_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_3_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_3_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_3_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_3_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_3_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_3_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_3_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_3_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_3_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_3_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_3_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_3_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_3_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_3_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_3_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_3_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_3_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_3_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_3_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_3_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_3_SET:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_3_Set_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_3_Set_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_3_Set_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_3_Set_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_3_Set_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_3_Set_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_3_Set_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_3_Set_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_3_Set_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_3_Set_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_3_Set_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_3_Set_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_3_Set_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_3_Set_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_3_Set_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_3_Set_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_3_Set_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_3_Set_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_3_Set_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_3_Set_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_3_Set_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_3_Set_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_3_Set_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_3_Set_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_3_Set_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_3_Set_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_3_Set_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_3_Set_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_3_Set_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_3_Set_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_3_Set_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_MTC_ADDR_3_CLEAR:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_3_Clear_ScanEnabled;
                    register.RegMTC_Config.Detected = MTC_Addr_3_Clear_Detected;
                    register.RegMTC_Config.Type = MTC_Addr_3_Clear_Type;
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_3_Clear_ENABLE_1;
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_3_Clear_ENABLE_2;
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_3_Clear_SEL_I2C_1;
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_3_Clear_SEL_I2C_2;
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_3_Clear_SEL_UART_1;
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_3_Clear_SEL_UART_2;
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_3_Clear_SEL_UART_3;
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_3_Clear_SEL_UART_4;
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_3_Clear_SEL_UART_5;
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_3_Clear_SEL_UART_6;
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_3_Clear_SEL_VBAT;
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_3_Clear_SEL_VBAT_ALT;
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_3_Clear_SEL_VBAT_FPGA;
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_3_Clear_SEL_nRESET_1;
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_3_Clear_SEL_nRESET_2;
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_3_Clear_SEL_nRESET_3;
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_3_Clear_SEL_CS_1;
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_3_Clear_SEL_CS_2;
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_3_Clear_SEL_CS_3;
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_3_Clear_SEL_CS_4;
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_3_Clear_SEL_CS_5;
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_3_Clear_SEL_CS_6;
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_3_Clear_SEL_SPI_1;
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_3_Clear_SEL_SPI_2;
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_3_Clear_SEL_CAN_1;
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_3_Clear_SEL_CAN_2;
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_3_Clear_SEL_CAN_3;
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_3_Clear_SEL_RS422;
                    break;

                case OBCRegisterAddress.OBC_REG_RTOS_STATUS0:
                    register.RegRTOS_Status0.uartRxHBOverflow = RTOS_Status0_uartRxHBOverflow;
                    register.RegRTOS_Status0.uartRxSBOverflow = RTOS_Status0_uartRxSBOverflow;
                    register.RegRTOS_Status0.uartTxSBOverflow = RTOS_Status0_uartTxSBOverflow;
                    register.RegRTOS_Status0.uartTxHBOverflow = RTOS_Status0_uartTxHBOverflow;
                    register.RegRTOS_Status0.I2CTargetIncomingOverflow = RTOS_Status0_I2CTargetIncomingOverflow;
                    register.RegRTOS_Status0.I2CTargetOutgoingOverflow = RTOS_Status0_I2CTargetOutgoingOverflow;
                    register.RegRTOS_Status0.CANTargetIncomingOverflow = RTOS_Status0_CANTargetIncomingOverflow;
                    register.RegRTOS_Status0.CANInterruptBufferOverflow = RTOS_Status0_CANInterruptBufferOverflow;
                    register.RegRTOS_Status0.CANTargetOutgoingOverflow = RTOS_Status0_CANTargetOutgoingOverflow;
                    register.RegRTOS_Status0.UARTTargetIncomingOverflow = RTOS_Status0_UARTTargetIncomingOverflow;
                    register.RegRTOS_Status0.UARTTargetTxHBOverflow = RTOS_Status0_UARTTargetTxHBOverflow;
                    register.RegRTOS_Status0.UARTTargetRxHBOverflow = RTOS_Status0_UARTTargetRxHBOverflow;
                    register.RegRTOS_Status0.UARTTargetOutgoingOverflow = RTOS_Status0_UARTTargetOutgoingOverflow;
                    register.RegRTOS_Status0.GSETargetIncomingOverflow = RTOS_Status0_GSETargetIncomingOverflow;
                    register.RegRTOS_Status0.GSETargetOutgoingOverflow = RTOS_Status0_GSETargetOutgoingOverflow;
                    register.RegRTOS_Status0.SERMUX_CRC_Error = RTOS_Status0_SERMUX_CRC_Error;
                    break;

                case OBCRegisterAddress.OBC_REG_UTILI2CCONFA:
                    register.RegUtilI2CConfA.Reset = UtilI2CConfA_Reset;
                    register.RegUtilI2CConfA.SPD = UtilI2CConfA_SPD;
                    break;

                case OBCRegisterAddress.OBC_REG_UTILI2CSTATUS:
                    register.RegUtilI2CStatus.value = UtilI2CStatus;
                    break;

                case OBCRegisterAddress.OBC_REG_PREVIOUSENDPOINT:
                    register.RegPreviousEndpoint.Number = PreviousEndpoint_Number;
                    break;

            }
        }

        public void EncodeSetClearFieldTo(ref RegisterData register, OBC_SetClearField fieldIdentifier)
        {
            switch (fieldIdentifier)
            {
                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS1_Enable:
                    register.RegMultitester.POS1_Enable = (byte) MultiConf1_Set_POS1_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS1_Power:
                    register.RegMultitester.POS1_Power = (byte) MultiConf1_Set_POS1_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS1_nReset:
                    register.RegMultitester.POS1_nReset = (byte) MultiConf1_Set_POS1_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS1_FAN:
                    register.RegMultitester.POS1_FAN = (byte) MultiConf1_Set_POS1_FAN;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS2_Enable:
                    register.RegMultitester.POS2_Enable = (byte) MultiConf1_Set_POS2_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS2_Power:
                    register.RegMultitester.POS2_Power = (byte) MultiConf1_Set_POS2_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS2_nReset:
                    register.RegMultitester.POS2_nReset = (byte) MultiConf1_Set_POS2_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS2_FAN:
                    register.RegMultitester.POS2_FAN = (byte) MultiConf1_Set_POS2_FAN;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS3_Enable:
                    register.RegMultitester.POS3_Enable = (byte) MultiConf1_Set_POS3_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS3_Power:
                    register.RegMultitester.POS3_Power = (byte) MultiConf1_Set_POS3_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS3_nReset:
                    register.RegMultitester.POS3_nReset = (byte) MultiConf1_Set_POS3_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS3_FAN:
                    register.RegMultitester.POS3_FAN = (byte) MultiConf1_Set_POS3_FAN;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS4_Enable:
                    register.RegMultitester.POS4_Enable = (byte) MultiConf1_Set_POS4_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS4_Power:
                    register.RegMultitester.POS4_Power = (byte) MultiConf1_Set_POS4_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS4_nReset:
                    register.RegMultitester.POS4_nReset = (byte) MultiConf1_Set_POS4_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Set_POS4_FAN:
                    register.RegMultitester.POS4_FAN = (byte) MultiConf1_Set_POS4_FAN;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS1_Enable:
                    register.RegMultitester.POS1_Enable = (byte) MultiConf1_Clear_POS1_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS1_Power:
                    register.RegMultitester.POS1_Power = (byte) MultiConf1_Clear_POS1_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS1_nReset:
                    register.RegMultitester.POS1_nReset = (byte) MultiConf1_Clear_POS1_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS1_FAN:
                    register.RegMultitester.POS1_FAN = (byte) MultiConf1_Clear_POS1_FAN;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS2_Enable:
                    register.RegMultitester.POS2_Enable = (byte) MultiConf1_Clear_POS2_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS2_Power:
                    register.RegMultitester.POS2_Power = (byte) MultiConf1_Clear_POS2_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS2_nReset:
                    register.RegMultitester.POS2_nReset = (byte) MultiConf1_Clear_POS2_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS2_FAN:
                    register.RegMultitester.POS2_FAN = (byte) MultiConf1_Clear_POS2_FAN;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS3_Enable:
                    register.RegMultitester.POS3_Enable = (byte) MultiConf1_Clear_POS3_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS3_Power:
                    register.RegMultitester.POS3_Power = (byte) MultiConf1_Clear_POS3_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS3_nReset:
                    register.RegMultitester.POS3_nReset = (byte) MultiConf1_Clear_POS3_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS3_FAN:
                    register.RegMultitester.POS3_FAN = (byte) MultiConf1_Clear_POS3_FAN;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS4_Enable:
                    register.RegMultitester.POS4_Enable = (byte) MultiConf1_Clear_POS4_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS4_Power:
                    register.RegMultitester.POS4_Power = (byte) MultiConf1_Clear_POS4_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS4_nReset:
                    register.RegMultitester.POS4_nReset = (byte) MultiConf1_Clear_POS4_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_MultiConf1_Clear_POS4_FAN:
                    register.RegMultitester.POS4_FAN = (byte) MultiConf1_Clear_POS4_FAN;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_ScanEnabled:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_0_Set_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_Detected:
                    register.RegTE_Config.Detected = TE_Addr_0_Set_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_Type:
                    register.RegTE_Config.Type = (byte) TE_Addr_0_Set_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_SEL_CAN0:
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_0_Set_SEL_CAN0;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_SEL_CAN1:
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_0_Set_SEL_CAN1;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_SEL_RS485:
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_0_Set_SEL_RS485;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_SEL_I2C:
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_0_Set_SEL_I2C;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_SEL_RS422:
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_0_Set_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_SEL_SPI:
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_0_Set_SEL_SPI;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_SEL_UART:
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_0_Set_SEL_UART;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_Power:
                    register.RegTE_Config.Power = (byte) TE_Addr_0_Set_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_Enable:
                    register.RegTE_Config.Enable = (byte) TE_Addr_0_Set_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_nReset:
                    register.RegTE_Config.nReset = (byte) TE_Addr_0_Set_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Set_COMM_TR:
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_0_Set_COMM_TR;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_ScanEnabled:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_0_Clear_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_Detected:
                    register.RegTE_Config.Detected = TE_Addr_0_Clear_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_Type:
                    register.RegTE_Config.Type = (byte) TE_Addr_0_Clear_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_SEL_CAN0:
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_0_Clear_SEL_CAN0;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_SEL_CAN1:
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_0_Clear_SEL_CAN1;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_SEL_RS485:
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_0_Clear_SEL_RS485;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_SEL_I2C:
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_0_Clear_SEL_I2C;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_SEL_RS422:
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_0_Clear_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_SEL_SPI:
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_0_Clear_SEL_SPI;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_SEL_UART:
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_0_Clear_SEL_UART;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_Power:
                    register.RegTE_Config.Power = (byte) TE_Addr_0_Clear_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_Enable:
                    register.RegTE_Config.Enable = (byte) TE_Addr_0_Clear_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_nReset:
                    register.RegTE_Config.nReset = (byte) TE_Addr_0_Clear_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_0_Clear_COMM_TR:
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_0_Clear_COMM_TR;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_ScanEnabled:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_1_Set_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_Detected:
                    register.RegTE_Config.Detected = TE_Addr_1_Set_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_Type:
                    register.RegTE_Config.Type = (byte) TE_Addr_1_Set_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_SEL_CAN0:
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_1_Set_SEL_CAN0;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_SEL_CAN1:
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_1_Set_SEL_CAN1;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_SEL_RS485:
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_1_Set_SEL_RS485;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_SEL_I2C:
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_1_Set_SEL_I2C;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_SEL_RS422:
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_1_Set_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_SEL_SPI:
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_1_Set_SEL_SPI;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_SEL_UART:
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_1_Set_SEL_UART;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_Power:
                    register.RegTE_Config.Power = (byte) TE_Addr_1_Set_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_Enable:
                    register.RegTE_Config.Enable = (byte) TE_Addr_1_Set_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_nReset:
                    register.RegTE_Config.nReset = (byte) TE_Addr_1_Set_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Set_COMM_TR:
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_1_Set_COMM_TR;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_ScanEnabled:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_1_Clear_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_Detected:
                    register.RegTE_Config.Detected = TE_Addr_1_Clear_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_Type:
                    register.RegTE_Config.Type = (byte) TE_Addr_1_Clear_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_SEL_CAN0:
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_1_Clear_SEL_CAN0;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_SEL_CAN1:
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_1_Clear_SEL_CAN1;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_SEL_RS485:
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_1_Clear_SEL_RS485;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_SEL_I2C:
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_1_Clear_SEL_I2C;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_SEL_RS422:
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_1_Clear_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_SEL_SPI:
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_1_Clear_SEL_SPI;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_SEL_UART:
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_1_Clear_SEL_UART;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_Power:
                    register.RegTE_Config.Power = (byte) TE_Addr_1_Clear_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_Enable:
                    register.RegTE_Config.Enable = (byte) TE_Addr_1_Clear_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_nReset:
                    register.RegTE_Config.nReset = (byte) TE_Addr_1_Clear_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_1_Clear_COMM_TR:
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_1_Clear_COMM_TR;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_ScanEnabled:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_2_Set_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_Detected:
                    register.RegTE_Config.Detected = TE_Addr_2_Set_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_Type:
                    register.RegTE_Config.Type = (byte) TE_Addr_2_Set_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_SEL_CAN0:
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_2_Set_SEL_CAN0;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_SEL_CAN1:
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_2_Set_SEL_CAN1;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_SEL_RS485:
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_2_Set_SEL_RS485;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_SEL_I2C:
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_2_Set_SEL_I2C;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_SEL_RS422:
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_2_Set_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_SEL_SPI:
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_2_Set_SEL_SPI;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_SEL_UART:
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_2_Set_SEL_UART;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_Power:
                    register.RegTE_Config.Power = (byte) TE_Addr_2_Set_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_Enable:
                    register.RegTE_Config.Enable = (byte) TE_Addr_2_Set_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_nReset:
                    register.RegTE_Config.nReset = (byte) TE_Addr_2_Set_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Set_COMM_TR:
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_2_Set_COMM_TR;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_ScanEnabled:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_2_Clear_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_Detected:
                    register.RegTE_Config.Detected = TE_Addr_2_Clear_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_Type:
                    register.RegTE_Config.Type = (byte) TE_Addr_2_Clear_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_SEL_CAN0:
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_2_Clear_SEL_CAN0;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_SEL_CAN1:
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_2_Clear_SEL_CAN1;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_SEL_RS485:
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_2_Clear_SEL_RS485;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_SEL_I2C:
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_2_Clear_SEL_I2C;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_SEL_RS422:
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_2_Clear_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_SEL_SPI:
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_2_Clear_SEL_SPI;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_SEL_UART:
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_2_Clear_SEL_UART;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_Power:
                    register.RegTE_Config.Power = (byte) TE_Addr_2_Clear_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_Enable:
                    register.RegTE_Config.Enable = (byte) TE_Addr_2_Clear_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_nReset:
                    register.RegTE_Config.nReset = (byte) TE_Addr_2_Clear_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_2_Clear_COMM_TR:
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_2_Clear_COMM_TR;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_ScanEnabled:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_3_Set_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_Detected:
                    register.RegTE_Config.Detected = TE_Addr_3_Set_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_Type:
                    register.RegTE_Config.Type = (byte) TE_Addr_3_Set_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_SEL_CAN0:
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_3_Set_SEL_CAN0;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_SEL_CAN1:
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_3_Set_SEL_CAN1;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_SEL_RS485:
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_3_Set_SEL_RS485;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_SEL_I2C:
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_3_Set_SEL_I2C;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_SEL_RS422:
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_3_Set_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_SEL_SPI:
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_3_Set_SEL_SPI;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_SEL_UART:
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_3_Set_SEL_UART;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_Power:
                    register.RegTE_Config.Power = (byte) TE_Addr_3_Set_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_Enable:
                    register.RegTE_Config.Enable = (byte) TE_Addr_3_Set_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_nReset:
                    register.RegTE_Config.nReset = (byte) TE_Addr_3_Set_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Set_COMM_TR:
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_3_Set_COMM_TR;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_ScanEnabled:
                    register.RegTE_Config.ScanEnabled = (byte) TE_Addr_3_Clear_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_Detected:
                    register.RegTE_Config.Detected = TE_Addr_3_Clear_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_Type:
                    register.RegTE_Config.Type = (byte) TE_Addr_3_Clear_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_SEL_CAN0:
                    register.RegTE_Config.SEL_CAN0 = (byte) TE_Addr_3_Clear_SEL_CAN0;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_SEL_CAN1:
                    register.RegTE_Config.SEL_CAN1 = (byte) TE_Addr_3_Clear_SEL_CAN1;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_SEL_RS485:
                    register.RegTE_Config.SEL_RS485 = (byte) TE_Addr_3_Clear_SEL_RS485;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_SEL_I2C:
                    register.RegTE_Config.SEL_I2C = (byte) TE_Addr_3_Clear_SEL_I2C;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_SEL_RS422:
                    register.RegTE_Config.SEL_RS422 = (byte) TE_Addr_3_Clear_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_SEL_SPI:
                    register.RegTE_Config.SEL_SPI = (byte) TE_Addr_3_Clear_SEL_SPI;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_SEL_UART:
                    register.RegTE_Config.SEL_UART = (byte) TE_Addr_3_Clear_SEL_UART;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_Power:
                    register.RegTE_Config.Power = (byte) TE_Addr_3_Clear_Power;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_Enable:
                    register.RegTE_Config.Enable = (byte) TE_Addr_3_Clear_Enable;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_nReset:
                    register.RegTE_Config.nReset = (byte) TE_Addr_3_Clear_nReset;
                    break;

                case OBC_SetClearField.OBC_SCF_TE_Addr_3_Clear_COMM_TR:
                    register.RegTE_Config.COMM_TR = (byte) TE_Addr_3_Clear_COMM_TR;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_ScanEnabled:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_0_Set_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_Detected:
                    register.RegMTC_Config.Detected = MTC_Addr_0_Set_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_Type:
                    register.RegMTC_Config.Type = MTC_Addr_0_Set_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_ENABLE_1:
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_0_Set_ENABLE_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_ENABLE_2:
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_0_Set_ENABLE_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_I2C_1:
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_0_Set_SEL_I2C_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_I2C_2:
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_0_Set_SEL_I2C_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_UART_1:
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_0_Set_SEL_UART_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_UART_2:
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_0_Set_SEL_UART_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_UART_3:
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_0_Set_SEL_UART_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_UART_4:
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_0_Set_SEL_UART_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_UART_5:
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_0_Set_SEL_UART_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_UART_6:
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_0_Set_SEL_UART_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_VBAT:
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_0_Set_SEL_VBAT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_VBAT_ALT:
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_0_Set_SEL_VBAT_ALT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_VBAT_FPGA:
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_0_Set_SEL_VBAT_FPGA;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_nRESET_1:
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_0_Set_SEL_nRESET_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_nRESET_2:
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_0_Set_SEL_nRESET_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_nRESET_3:
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_0_Set_SEL_nRESET_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_CS_1:
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_0_Set_SEL_CS_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_CS_2:
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_0_Set_SEL_CS_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_CS_3:
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_0_Set_SEL_CS_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_CS_4:
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_0_Set_SEL_CS_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_CS_5:
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_0_Set_SEL_CS_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_CS_6:
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_0_Set_SEL_CS_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_SPI_1:
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_0_Set_SEL_SPI_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_SPI_2:
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_0_Set_SEL_SPI_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_CAN_1:
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_0_Set_SEL_CAN_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_CAN_2:
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_0_Set_SEL_CAN_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_CAN_3:
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_0_Set_SEL_CAN_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Set_SEL_RS422:
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_0_Set_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_ScanEnabled:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_0_Clear_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_Detected:
                    register.RegMTC_Config.Detected = MTC_Addr_0_Clear_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_Type:
                    register.RegMTC_Config.Type = MTC_Addr_0_Clear_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_ENABLE_1:
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_0_Clear_ENABLE_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_ENABLE_2:
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_0_Clear_ENABLE_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_I2C_1:
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_0_Clear_SEL_I2C_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_I2C_2:
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_0_Clear_SEL_I2C_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_UART_1:
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_0_Clear_SEL_UART_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_UART_2:
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_0_Clear_SEL_UART_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_UART_3:
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_0_Clear_SEL_UART_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_UART_4:
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_0_Clear_SEL_UART_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_UART_5:
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_0_Clear_SEL_UART_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_UART_6:
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_0_Clear_SEL_UART_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_VBAT:
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_0_Clear_SEL_VBAT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_VBAT_ALT:
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_0_Clear_SEL_VBAT_ALT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_VBAT_FPGA:
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_0_Clear_SEL_VBAT_FPGA;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_nRESET_1:
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_0_Clear_SEL_nRESET_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_nRESET_2:
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_0_Clear_SEL_nRESET_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_nRESET_3:
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_0_Clear_SEL_nRESET_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_CS_1:
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_0_Clear_SEL_CS_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_CS_2:
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_0_Clear_SEL_CS_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_CS_3:
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_0_Clear_SEL_CS_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_CS_4:
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_0_Clear_SEL_CS_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_CS_5:
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_0_Clear_SEL_CS_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_CS_6:
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_0_Clear_SEL_CS_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_SPI_1:
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_0_Clear_SEL_SPI_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_SPI_2:
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_0_Clear_SEL_SPI_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_CAN_1:
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_0_Clear_SEL_CAN_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_CAN_2:
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_0_Clear_SEL_CAN_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_CAN_3:
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_0_Clear_SEL_CAN_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_0_Clear_SEL_RS422:
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_0_Clear_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_ScanEnabled:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_1_Set_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_Detected:
                    register.RegMTC_Config.Detected = MTC_Addr_1_Set_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_Type:
                    register.RegMTC_Config.Type = MTC_Addr_1_Set_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_ENABLE_1:
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_1_Set_ENABLE_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_ENABLE_2:
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_1_Set_ENABLE_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_I2C_1:
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_1_Set_SEL_I2C_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_I2C_2:
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_1_Set_SEL_I2C_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_UART_1:
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_1_Set_SEL_UART_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_UART_2:
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_1_Set_SEL_UART_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_UART_3:
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_1_Set_SEL_UART_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_UART_4:
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_1_Set_SEL_UART_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_UART_5:
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_1_Set_SEL_UART_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_UART_6:
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_1_Set_SEL_UART_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_VBAT:
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_1_Set_SEL_VBAT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_VBAT_ALT:
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_1_Set_SEL_VBAT_ALT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_VBAT_FPGA:
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_1_Set_SEL_VBAT_FPGA;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_nRESET_1:
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_1_Set_SEL_nRESET_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_nRESET_2:
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_1_Set_SEL_nRESET_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_nRESET_3:
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_1_Set_SEL_nRESET_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_CS_1:
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_1_Set_SEL_CS_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_CS_2:
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_1_Set_SEL_CS_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_CS_3:
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_1_Set_SEL_CS_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_CS_4:
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_1_Set_SEL_CS_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_CS_5:
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_1_Set_SEL_CS_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_CS_6:
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_1_Set_SEL_CS_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_SPI_1:
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_1_Set_SEL_SPI_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_SPI_2:
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_1_Set_SEL_SPI_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_CAN_1:
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_1_Set_SEL_CAN_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_CAN_2:
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_1_Set_SEL_CAN_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_CAN_3:
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_1_Set_SEL_CAN_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Set_SEL_RS422:
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_1_Set_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_ScanEnabled:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_1_Clear_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_Detected:
                    register.RegMTC_Config.Detected = MTC_Addr_1_Clear_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_Type:
                    register.RegMTC_Config.Type = MTC_Addr_1_Clear_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_ENABLE_1:
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_1_Clear_ENABLE_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_ENABLE_2:
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_1_Clear_ENABLE_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_I2C_1:
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_1_Clear_SEL_I2C_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_I2C_2:
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_1_Clear_SEL_I2C_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_UART_1:
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_1_Clear_SEL_UART_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_UART_2:
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_1_Clear_SEL_UART_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_UART_3:
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_1_Clear_SEL_UART_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_UART_4:
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_1_Clear_SEL_UART_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_UART_5:
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_1_Clear_SEL_UART_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_UART_6:
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_1_Clear_SEL_UART_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_VBAT:
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_1_Clear_SEL_VBAT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_VBAT_ALT:
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_1_Clear_SEL_VBAT_ALT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_VBAT_FPGA:
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_1_Clear_SEL_VBAT_FPGA;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_nRESET_1:
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_1_Clear_SEL_nRESET_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_nRESET_2:
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_1_Clear_SEL_nRESET_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_nRESET_3:
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_1_Clear_SEL_nRESET_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_CS_1:
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_1_Clear_SEL_CS_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_CS_2:
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_1_Clear_SEL_CS_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_CS_3:
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_1_Clear_SEL_CS_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_CS_4:
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_1_Clear_SEL_CS_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_CS_5:
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_1_Clear_SEL_CS_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_CS_6:
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_1_Clear_SEL_CS_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_SPI_1:
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_1_Clear_SEL_SPI_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_SPI_2:
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_1_Clear_SEL_SPI_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_CAN_1:
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_1_Clear_SEL_CAN_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_CAN_2:
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_1_Clear_SEL_CAN_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_CAN_3:
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_1_Clear_SEL_CAN_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_1_Clear_SEL_RS422:
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_1_Clear_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_ScanEnabled:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_2_Set_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_Detected:
                    register.RegMTC_Config.Detected = MTC_Addr_2_Set_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_Type:
                    register.RegMTC_Config.Type = MTC_Addr_2_Set_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_ENABLE_1:
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_2_Set_ENABLE_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_ENABLE_2:
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_2_Set_ENABLE_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_I2C_1:
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_2_Set_SEL_I2C_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_I2C_2:
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_2_Set_SEL_I2C_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_UART_1:
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_2_Set_SEL_UART_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_UART_2:
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_2_Set_SEL_UART_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_UART_3:
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_2_Set_SEL_UART_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_UART_4:
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_2_Set_SEL_UART_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_UART_5:
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_2_Set_SEL_UART_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_UART_6:
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_2_Set_SEL_UART_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_VBAT:
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_2_Set_SEL_VBAT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_VBAT_ALT:
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_2_Set_SEL_VBAT_ALT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_VBAT_FPGA:
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_2_Set_SEL_VBAT_FPGA;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_nRESET_1:
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_2_Set_SEL_nRESET_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_nRESET_2:
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_2_Set_SEL_nRESET_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_nRESET_3:
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_2_Set_SEL_nRESET_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_CS_1:
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_2_Set_SEL_CS_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_CS_2:
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_2_Set_SEL_CS_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_CS_3:
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_2_Set_SEL_CS_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_CS_4:
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_2_Set_SEL_CS_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_CS_5:
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_2_Set_SEL_CS_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_CS_6:
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_2_Set_SEL_CS_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_SPI_1:
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_2_Set_SEL_SPI_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_SPI_2:
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_2_Set_SEL_SPI_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_CAN_1:
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_2_Set_SEL_CAN_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_CAN_2:
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_2_Set_SEL_CAN_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_CAN_3:
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_2_Set_SEL_CAN_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Set_SEL_RS422:
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_2_Set_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_ScanEnabled:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_2_Clear_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_Detected:
                    register.RegMTC_Config.Detected = MTC_Addr_2_Clear_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_Type:
                    register.RegMTC_Config.Type = MTC_Addr_2_Clear_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_ENABLE_1:
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_2_Clear_ENABLE_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_ENABLE_2:
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_2_Clear_ENABLE_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_I2C_1:
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_2_Clear_SEL_I2C_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_I2C_2:
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_2_Clear_SEL_I2C_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_UART_1:
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_2_Clear_SEL_UART_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_UART_2:
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_2_Clear_SEL_UART_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_UART_3:
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_2_Clear_SEL_UART_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_UART_4:
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_2_Clear_SEL_UART_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_UART_5:
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_2_Clear_SEL_UART_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_UART_6:
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_2_Clear_SEL_UART_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_VBAT:
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_2_Clear_SEL_VBAT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_VBAT_ALT:
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_2_Clear_SEL_VBAT_ALT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_VBAT_FPGA:
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_2_Clear_SEL_VBAT_FPGA;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_nRESET_1:
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_2_Clear_SEL_nRESET_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_nRESET_2:
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_2_Clear_SEL_nRESET_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_nRESET_3:
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_2_Clear_SEL_nRESET_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_CS_1:
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_2_Clear_SEL_CS_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_CS_2:
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_2_Clear_SEL_CS_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_CS_3:
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_2_Clear_SEL_CS_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_CS_4:
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_2_Clear_SEL_CS_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_CS_5:
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_2_Clear_SEL_CS_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_CS_6:
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_2_Clear_SEL_CS_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_SPI_1:
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_2_Clear_SEL_SPI_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_SPI_2:
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_2_Clear_SEL_SPI_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_CAN_1:
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_2_Clear_SEL_CAN_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_CAN_2:
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_2_Clear_SEL_CAN_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_CAN_3:
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_2_Clear_SEL_CAN_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_2_Clear_SEL_RS422:
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_2_Clear_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_ScanEnabled:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_3_Set_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_Detected:
                    register.RegMTC_Config.Detected = MTC_Addr_3_Set_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_Type:
                    register.RegMTC_Config.Type = MTC_Addr_3_Set_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_ENABLE_1:
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_3_Set_ENABLE_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_ENABLE_2:
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_3_Set_ENABLE_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_I2C_1:
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_3_Set_SEL_I2C_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_I2C_2:
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_3_Set_SEL_I2C_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_UART_1:
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_3_Set_SEL_UART_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_UART_2:
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_3_Set_SEL_UART_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_UART_3:
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_3_Set_SEL_UART_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_UART_4:
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_3_Set_SEL_UART_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_UART_5:
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_3_Set_SEL_UART_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_UART_6:
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_3_Set_SEL_UART_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_VBAT:
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_3_Set_SEL_VBAT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_VBAT_ALT:
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_3_Set_SEL_VBAT_ALT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_VBAT_FPGA:
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_3_Set_SEL_VBAT_FPGA;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_nRESET_1:
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_3_Set_SEL_nRESET_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_nRESET_2:
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_3_Set_SEL_nRESET_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_nRESET_3:
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_3_Set_SEL_nRESET_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_CS_1:
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_3_Set_SEL_CS_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_CS_2:
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_3_Set_SEL_CS_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_CS_3:
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_3_Set_SEL_CS_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_CS_4:
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_3_Set_SEL_CS_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_CS_5:
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_3_Set_SEL_CS_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_CS_6:
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_3_Set_SEL_CS_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_SPI_1:
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_3_Set_SEL_SPI_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_SPI_2:
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_3_Set_SEL_SPI_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_CAN_1:
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_3_Set_SEL_CAN_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_CAN_2:
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_3_Set_SEL_CAN_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_CAN_3:
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_3_Set_SEL_CAN_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Set_SEL_RS422:
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_3_Set_SEL_RS422;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_ScanEnabled:
                    register.RegMTC_Config.ScanEnabled = (byte) MTC_Addr_3_Clear_ScanEnabled;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_Detected:
                    register.RegMTC_Config.Detected = MTC_Addr_3_Clear_Detected;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_Type:
                    register.RegMTC_Config.Type = MTC_Addr_3_Clear_Type;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_ENABLE_1:
                    register.RegMTC_Config.ENABLE_1 = (byte) MTC_Addr_3_Clear_ENABLE_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_ENABLE_2:
                    register.RegMTC_Config.ENABLE_2 = (byte) MTC_Addr_3_Clear_ENABLE_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_I2C_1:
                    register.RegMTC_Config.SEL_I2C_1 = (byte) MTC_Addr_3_Clear_SEL_I2C_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_I2C_2:
                    register.RegMTC_Config.SEL_I2C_2 = (byte) MTC_Addr_3_Clear_SEL_I2C_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_UART_1:
                    register.RegMTC_Config.SEL_UART_1 = (byte) MTC_Addr_3_Clear_SEL_UART_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_UART_2:
                    register.RegMTC_Config.SEL_UART_2 = (byte) MTC_Addr_3_Clear_SEL_UART_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_UART_3:
                    register.RegMTC_Config.SEL_UART_3 = (byte) MTC_Addr_3_Clear_SEL_UART_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_UART_4:
                    register.RegMTC_Config.SEL_UART_4 = (byte) MTC_Addr_3_Clear_SEL_UART_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_UART_5:
                    register.RegMTC_Config.SEL_UART_5 = (byte) MTC_Addr_3_Clear_SEL_UART_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_UART_6:
                    register.RegMTC_Config.SEL_UART_6 = (byte) MTC_Addr_3_Clear_SEL_UART_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_VBAT:
                    register.RegMTC_Config.SEL_VBAT = (byte) MTC_Addr_3_Clear_SEL_VBAT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_VBAT_ALT:
                    register.RegMTC_Config.SEL_VBAT_ALT = (byte) MTC_Addr_3_Clear_SEL_VBAT_ALT;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_VBAT_FPGA:
                    register.RegMTC_Config.SEL_VBAT_FPGA = (byte) MTC_Addr_3_Clear_SEL_VBAT_FPGA;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_nRESET_1:
                    register.RegMTC_Config.SEL_nRESET_1 = (byte) MTC_Addr_3_Clear_SEL_nRESET_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_nRESET_2:
                    register.RegMTC_Config.SEL_nRESET_2 = (byte) MTC_Addr_3_Clear_SEL_nRESET_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_nRESET_3:
                    register.RegMTC_Config.SEL_nRESET_3 = (byte) MTC_Addr_3_Clear_SEL_nRESET_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_CS_1:
                    register.RegMTC_Config.SEL_CS_1 = (byte) MTC_Addr_3_Clear_SEL_CS_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_CS_2:
                    register.RegMTC_Config.SEL_CS_2 = (byte) MTC_Addr_3_Clear_SEL_CS_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_CS_3:
                    register.RegMTC_Config.SEL_CS_3 = (byte) MTC_Addr_3_Clear_SEL_CS_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_CS_4:
                    register.RegMTC_Config.SEL_CS_4 = (byte) MTC_Addr_3_Clear_SEL_CS_4;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_CS_5:
                    register.RegMTC_Config.SEL_CS_5 = (byte) MTC_Addr_3_Clear_SEL_CS_5;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_CS_6:
                    register.RegMTC_Config.SEL_CS_6 = (byte) MTC_Addr_3_Clear_SEL_CS_6;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_SPI_1:
                    register.RegMTC_Config.SEL_SPI_1 = (byte) MTC_Addr_3_Clear_SEL_SPI_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_SPI_2:
                    register.RegMTC_Config.SEL_SPI_2 = (byte) MTC_Addr_3_Clear_SEL_SPI_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_CAN_1:
                    register.RegMTC_Config.SEL_CAN_1 = (byte) MTC_Addr_3_Clear_SEL_CAN_1;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_CAN_2:
                    register.RegMTC_Config.SEL_CAN_2 = (byte) MTC_Addr_3_Clear_SEL_CAN_2;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_CAN_3:
                    register.RegMTC_Config.SEL_CAN_3 = (byte) MTC_Addr_3_Clear_SEL_CAN_3;
                    break;

                case OBC_SetClearField.OBC_SCF_MTC_Addr_3_Clear_SEL_RS422:
                    register.RegMTC_Config.SEL_RS422 = (byte) MTC_Addr_3_Clear_SEL_RS422;
                    break;

            }
        }

        public void ResetValues()
        {
            // First clear the value
            // Then clear the IsSet
            Board_ID_ccIdentifier = 0;
            Board_ID_ccIdentifierIsSet = false;
            Board_ID_id0 = 0;
            Board_ID_id0IsSet = false;
            Board_ID_id1 = 0;
            Board_ID_id1IsSet = false;
            Board_ID_id2 = 0;
            Board_ID_id2IsSet = false;

            FW_Version_major_version = 0;
            FW_Version_major_versionIsSet = false;
            FW_Version_minor_version = 0;
            FW_Version_minor_versionIsSet = false;
            FW_Version_patch_version = 0;
            FW_Version_patch_versionIsSet = false;

            HW_Version_major_version = 0;
            HW_Version_major_versionIsSet = false;
            HW_Version_minor_version = 0;
            HW_Version_minor_versionIsSet = false;
            HW_Version_patch_version = 0;
            HW_Version_patch_versionIsSet = false;

            Scratchpad = 0;
            ScratchpadIsSet = false;

            Supported_Boards = 0;
            Supported_BoardsIsSet = false;

            Configured_Boards = 0;
            Configured_BoardsIsSet = false;

            Uptime = 0;
            UptimeIsSet = false;

            Event_ConfA_count = 0;
            Event_ConfA_countIsSet = false;

            Event_section = 0;
            Event_sectionIsSet = false;
            Event_detail = 0;
            Event_detailIsSet = false;
            Event_timestamp = 0;
            Event_timestampIsSet = false;

            ConfPower_voltage5Toggle = 0;
            ConfPower_voltage5ToggleIsSet = false;
            ConfPower_voltage3Toggle = 0;
            ConfPower_voltage3ToggleIsSet = false;
            ConfPower_voltageVBatToggle = 0;
            ConfPower_voltageVBatToggleIsSet = false;
            ConfPower_voltageVBatAltToggle = 0;
            ConfPower_voltageVBatAltToggleIsSet = false;
            ConfPower_voltage3UtilToggle = 0;
            ConfPower_voltage3UtilToggleIsSet = false;

            MeasureVI_V3_voltage = 0;
            MeasureVI_V3_voltageIsSet = false;
            MeasureVI_V3_current = 0;
            MeasureVI_V3_currentIsSet = false;

            MeasurePower_V3_power = 0;
            MeasurePower_V3_powerIsSet = false;

            MeasureVI_V5_voltage = 0;
            MeasureVI_V5_voltageIsSet = false;
            MeasureVI_V5_current = 0;
            MeasureVI_V5_currentIsSet = false;

            MeasurePower_V5_power = 0;
            MeasurePower_V5_powerIsSet = false;

            MeasureVI_VBat_voltage = 0;
            MeasureVI_VBat_voltageIsSet = false;
            MeasureVI_VBat_current = 0;
            MeasureVI_VBat_currentIsSet = false;

            MeasurePower_VBat_power = 0;
            MeasurePower_VBat_powerIsSet = false;

            MeasureVI_VBatAlt_voltage = 0;
            MeasureVI_VBatAlt_voltageIsSet = false;
            MeasureVI_VBatAlt_current = 0;
            MeasureVI_VBatAlt_currentIsSet = false;

            MeasurePower_VBatAlt_power = 0;
            MeasurePower_VBatAlt_powerIsSet = false;

            I2CConfA_TRDEL = 0;
            I2CConfA_TRDELIsSet = false;
            I2CConfA_WRDEL = 0;
            I2CConfA_WRDELIsSet = false;
            I2CConfA_SPD = 0;
            I2CConfA_SPDIsSet = false;

            I2CConfB_ADDR = 0;
            I2CConfB_ADDRIsSet = false;

            MultiConf0_Detected = 0;
            MultiConf0_DetectedIsSet = false;
            MultiConf0_AutoCLR = 0;
            MultiConf0_AutoCLRIsSet = false;
            MultiConf0_ScanEnabled = 0;
            MultiConf0_ScanEnabledIsSet = false;
            MultiConf0_FanPos1 = 0;
            MultiConf0_FanPos1IsSet = false;
            MultiConf0_FanPos2 = 0;
            MultiConf0_FanPos2IsSet = false;
            MultiConf0_FanPos3 = 0;
            MultiConf0_FanPos3IsSet = false;
            MultiConf0_FanPos4 = 0;
            MultiConf0_FanPos4IsSet = false;

            ConfTempSense_EnableMeasurements = 0;
            ConfTempSense_EnableMeasurementsIsSet = false;

            CANConfA_BaudRate = 0;
            CANConfA_BaudRateIsSet = false;
            CANConfA_EnableRetries = 0;
            CANConfA_EnableRetriesIsSet = false;
            CANConfA_FlipCanBytes = 0;
            CANConfA_FlipCanBytesIsSet = false;

            CANConfB_Address = 0;
            CANConfB_AddressIsSet = false;

            SerialConf_SerialMode = 0;
            SerialConf_SerialModeIsSet = false;
            SerialConf_ParityEnabled = 0;
            SerialConf_ParityEnabledIsSet = false;
            SerialConf_ParityMode = 0;
            SerialConf_ParityModeIsSet = false;
            SerialConf_BaudRates = 0;
            SerialConf_BaudRatesIsSet = false;

            PC104Pins_ENA = 0;
            PC104Pins_ENAIsSet = false;
            PC104Pins_nRST = 0;
            PC104Pins_nRSTIsSet = false;
            PC104Pins_RDY = 0;
            PC104Pins_RDYIsSet = false;

            XTXMultitester_POS1_XTX_EN = 0;
            XTXMultitester_POS1_XTX_ENIsSet = false;
            XTXMultitester_POS1_XTX_Power = 0;
            XTXMultitester_POS1_XTX_PowerIsSet = false;
            XTXMultitester_POS1_XTX_nReset = 0;
            XTXMultitester_POS1_XTX_nResetIsSet = false;
            XTXMultitester_POS2_XTX_EN = 0;
            XTXMultitester_POS2_XTX_ENIsSet = false;
            XTXMultitester_POS2_XTX_Power = 0;
            XTXMultitester_POS2_XTX_PowerIsSet = false;
            XTXMultitester_POS2_XTX_nReset = 0;
            XTXMultitester_POS2_XTX_nResetIsSet = false;
            XTXMultitester_POS3_XTX_EN = 0;
            XTXMultitester_POS3_XTX_ENIsSet = false;
            XTXMultitester_POS3_XTX_Power = 0;
            XTXMultitester_POS3_XTX_PowerIsSet = false;
            XTXMultitester_POS3_XTX_nReset = 0;
            XTXMultitester_POS3_XTX_nResetIsSet = false;
            XTXMultitester_POS4_XTX_EN = 0;
            XTXMultitester_POS4_XTX_ENIsSet = false;
            XTXMultitester_POS4_XTX_Power = 0;
            XTXMultitester_POS4_XTX_PowerIsSet = false;
            XTXMultitester_POS4_XTX_nReset = 0;
            XTXMultitester_POS4_XTX_nResetIsSet = false;

            RFRelaysConf_RFSW1_Detected = 0;
            RFRelaysConf_RFSW1_DetectedIsSet = false;
            RFRelaysConf_RFSW2_Detected = 0;
            RFRelaysConf_RFSW2_DetectedIsSet = false;
            RFRelaysConf_ScanEnabled = 0;
            RFRelaysConf_ScanEnabledIsSet = false;
            RFRelaysConf_RfSw1Chan = 0;
            RFRelaysConf_RfSw1ChanIsSet = false;
            RFRelaysConf_RfSw2Chan = 0;
            RFRelaysConf_RfSw2ChanIsSet = false;

            MultiConf1_Status_POS1_Enable = 0;
            MultiConf1_Status_POS1_EnableIsSet = false;
            MultiConf1_Status_POS1_Power = 0;
            MultiConf1_Status_POS1_PowerIsSet = false;
            MultiConf1_Status_POS1_nReset = 0;
            MultiConf1_Status_POS1_nResetIsSet = false;
            MultiConf1_Status_POS1_FAN = 0;
            MultiConf1_Status_POS1_FANIsSet = false;
            MultiConf1_Status_POS2_Enable = 0;
            MultiConf1_Status_POS2_EnableIsSet = false;
            MultiConf1_Status_POS2_Power = 0;
            MultiConf1_Status_POS2_PowerIsSet = false;
            MultiConf1_Status_POS2_nReset = 0;
            MultiConf1_Status_POS2_nResetIsSet = false;
            MultiConf1_Status_POS2_FAN = 0;
            MultiConf1_Status_POS2_FANIsSet = false;
            MultiConf1_Status_POS3_Enable = 0;
            MultiConf1_Status_POS3_EnableIsSet = false;
            MultiConf1_Status_POS3_Power = 0;
            MultiConf1_Status_POS3_PowerIsSet = false;
            MultiConf1_Status_POS3_nReset = 0;
            MultiConf1_Status_POS3_nResetIsSet = false;
            MultiConf1_Status_POS3_FAN = 0;
            MultiConf1_Status_POS3_FANIsSet = false;
            MultiConf1_Status_POS4_Enable = 0;
            MultiConf1_Status_POS4_EnableIsSet = false;
            MultiConf1_Status_POS4_Power = 0;
            MultiConf1_Status_POS4_PowerIsSet = false;
            MultiConf1_Status_POS4_nReset = 0;
            MultiConf1_Status_POS4_nResetIsSet = false;
            MultiConf1_Status_POS4_FAN = 0;
            MultiConf1_Status_POS4_FANIsSet = false;

            MultiConf1_Set_POS1_Enable = 0;
            MultiConf1_Set_POS1_EnableIsSet = false;
            MultiConf1_Set_POS1_Power = 0;
            MultiConf1_Set_POS1_PowerIsSet = false;
            MultiConf1_Set_POS1_nReset = 0;
            MultiConf1_Set_POS1_nResetIsSet = false;
            MultiConf1_Set_POS1_FAN = 0;
            MultiConf1_Set_POS1_FANIsSet = false;
            MultiConf1_Set_POS2_Enable = 0;
            MultiConf1_Set_POS2_EnableIsSet = false;
            MultiConf1_Set_POS2_Power = 0;
            MultiConf1_Set_POS2_PowerIsSet = false;
            MultiConf1_Set_POS2_nReset = 0;
            MultiConf1_Set_POS2_nResetIsSet = false;
            MultiConf1_Set_POS2_FAN = 0;
            MultiConf1_Set_POS2_FANIsSet = false;
            MultiConf1_Set_POS3_Enable = 0;
            MultiConf1_Set_POS3_EnableIsSet = false;
            MultiConf1_Set_POS3_Power = 0;
            MultiConf1_Set_POS3_PowerIsSet = false;
            MultiConf1_Set_POS3_nReset = 0;
            MultiConf1_Set_POS3_nResetIsSet = false;
            MultiConf1_Set_POS3_FAN = 0;
            MultiConf1_Set_POS3_FANIsSet = false;
            MultiConf1_Set_POS4_Enable = 0;
            MultiConf1_Set_POS4_EnableIsSet = false;
            MultiConf1_Set_POS4_Power = 0;
            MultiConf1_Set_POS4_PowerIsSet = false;
            MultiConf1_Set_POS4_nReset = 0;
            MultiConf1_Set_POS4_nResetIsSet = false;
            MultiConf1_Set_POS4_FAN = 0;
            MultiConf1_Set_POS4_FANIsSet = false;

            MultiConf1_Clear_POS1_Enable = 0;
            MultiConf1_Clear_POS1_EnableIsSet = false;
            MultiConf1_Clear_POS1_Power = 0;
            MultiConf1_Clear_POS1_PowerIsSet = false;
            MultiConf1_Clear_POS1_nReset = 0;
            MultiConf1_Clear_POS1_nResetIsSet = false;
            MultiConf1_Clear_POS1_FAN = 0;
            MultiConf1_Clear_POS1_FANIsSet = false;
            MultiConf1_Clear_POS2_Enable = 0;
            MultiConf1_Clear_POS2_EnableIsSet = false;
            MultiConf1_Clear_POS2_Power = 0;
            MultiConf1_Clear_POS2_PowerIsSet = false;
            MultiConf1_Clear_POS2_nReset = 0;
            MultiConf1_Clear_POS2_nResetIsSet = false;
            MultiConf1_Clear_POS2_FAN = 0;
            MultiConf1_Clear_POS2_FANIsSet = false;
            MultiConf1_Clear_POS3_Enable = 0;
            MultiConf1_Clear_POS3_EnableIsSet = false;
            MultiConf1_Clear_POS3_Power = 0;
            MultiConf1_Clear_POS3_PowerIsSet = false;
            MultiConf1_Clear_POS3_nReset = 0;
            MultiConf1_Clear_POS3_nResetIsSet = false;
            MultiConf1_Clear_POS3_FAN = 0;
            MultiConf1_Clear_POS3_FANIsSet = false;
            MultiConf1_Clear_POS4_Enable = 0;
            MultiConf1_Clear_POS4_EnableIsSet = false;
            MultiConf1_Clear_POS4_Power = 0;
            MultiConf1_Clear_POS4_PowerIsSet = false;
            MultiConf1_Clear_POS4_nReset = 0;
            MultiConf1_Clear_POS4_nResetIsSet = false;
            MultiConf1_Clear_POS4_FAN = 0;
            MultiConf1_Clear_POS4_FANIsSet = false;

            XDCConfig_ADDR = 0;
            XDCConfig_ADDRIsSet = false;

            CSBoard_T0 = 0;
            CSBoard_T0IsSet = false;

            CSBoard_T1 = 0;
            CSBoard_T1IsSet = false;

            CSBoard_T2 = 0;
            CSBoard_T2IsSet = false;

            CSBoard_T3 = 0;
            CSBoard_T3IsSet = false;

            CSBoard_T4 = 0;
            CSBoard_T4IsSet = false;

            CSBoard_T5 = 0;
            CSBoard_T5IsSet = false;

            CSBoard_T6 = 0;
            CSBoard_T6IsSet = false;

            CSBoard_T7 = 0;
            CSBoard_T7IsSet = false;

            CSBoard_Current0I0 = 0;
            CSBoard_Current0I0IsSet = false;

            CSBoard_Current0I1 = 0;
            CSBoard_Current0I1IsSet = false;

            CSBoard_Current0I2 = 0;
            CSBoard_Current0I2IsSet = false;

            CSBoard_Current1I0 = 0;
            CSBoard_Current1I0IsSet = false;

            CSBoard_Current1I1 = 0;
            CSBoard_Current1I1IsSet = false;

            CSBoard_Current1I2 = 0;
            CSBoard_Current1I2IsSet = false;

            CSBoard_Current2I0 = 0;
            CSBoard_Current2I0IsSet = false;

            CSBoard_Current2I1 = 0;
            CSBoard_Current2I1IsSet = false;

            CSBoard_Current2I2 = 0;
            CSBoard_Current2I2IsSet = false;

            CSBoard_Current3I0 = 0;
            CSBoard_Current3I0IsSet = false;

            CSBoard_Current3I1 = 0;
            CSBoard_Current3I1IsSet = false;

            CSBoard_Current3I2 = 0;
            CSBoard_Current3I2IsSet = false;

            CSBoard_Current4I0 = 0;
            CSBoard_Current4I0IsSet = false;

            CSBoard_Current4I1 = 0;
            CSBoard_Current4I1IsSet = false;

            CSBoard_Current4I2 = 0;
            CSBoard_Current4I2IsSet = false;

            CSBoard_Current5I0 = 0;
            CSBoard_Current5I0IsSet = false;

            CSBoard_Current5I1 = 0;
            CSBoard_Current5I1IsSet = false;

            CSBoard_Current5I2 = 0;
            CSBoard_Current5I2IsSet = false;

            CSBoard_Current6I0 = 0;
            CSBoard_Current6I0IsSet = false;

            CSBoard_Current6I1 = 0;
            CSBoard_Current6I1IsSet = false;

            CSBoard_Current6I2 = 0;
            CSBoard_Current6I2IsSet = false;

            CSBoard_Current7I0 = 0;
            CSBoard_Current7I0IsSet = false;

            CSBoard_Current7I1 = 0;
            CSBoard_Current7I1IsSet = false;

            CSBoard_Current7I2 = 0;
            CSBoard_Current7I2IsSet = false;

            TE_Addr_0_ScanEnabled = 0;
            TE_Addr_0_ScanEnabledIsSet = false;
            TE_Addr_0_Detected = 0;
            TE_Addr_0_DetectedIsSet = false;
            TE_Addr_0_Type = 0;
            TE_Addr_0_TypeIsSet = false;
            TE_Addr_0_SEL_CAN0 = 0;
            TE_Addr_0_SEL_CAN0IsSet = false;
            TE_Addr_0_SEL_CAN1 = 0;
            TE_Addr_0_SEL_CAN1IsSet = false;
            TE_Addr_0_SEL_RS485 = 0;
            TE_Addr_0_SEL_RS485IsSet = false;
            TE_Addr_0_SEL_I2C = 0;
            TE_Addr_0_SEL_I2CIsSet = false;
            TE_Addr_0_SEL_RS422 = 0;
            TE_Addr_0_SEL_RS422IsSet = false;
            TE_Addr_0_SEL_SPI = 0;
            TE_Addr_0_SEL_SPIIsSet = false;
            TE_Addr_0_SEL_UART = 0;
            TE_Addr_0_SEL_UARTIsSet = false;
            TE_Addr_0_Power = 0;
            TE_Addr_0_PowerIsSet = false;
            TE_Addr_0_Enable = 0;
            TE_Addr_0_EnableIsSet = false;
            TE_Addr_0_nReset = 0;
            TE_Addr_0_nResetIsSet = false;
            TE_Addr_0_COMM_TR = 0;
            TE_Addr_0_COMM_TRIsSet = false;

            TE_Addr_0_Set_ScanEnabled = 0;
            TE_Addr_0_Set_ScanEnabledIsSet = false;
            TE_Addr_0_Set_Detected = 0;
            TE_Addr_0_Set_DetectedIsSet = false;
            TE_Addr_0_Set_Type = 0;
            TE_Addr_0_Set_TypeIsSet = false;
            TE_Addr_0_Set_SEL_CAN0 = 0;
            TE_Addr_0_Set_SEL_CAN0IsSet = false;
            TE_Addr_0_Set_SEL_CAN1 = 0;
            TE_Addr_0_Set_SEL_CAN1IsSet = false;
            TE_Addr_0_Set_SEL_RS485 = 0;
            TE_Addr_0_Set_SEL_RS485IsSet = false;
            TE_Addr_0_Set_SEL_I2C = 0;
            TE_Addr_0_Set_SEL_I2CIsSet = false;
            TE_Addr_0_Set_SEL_RS422 = 0;
            TE_Addr_0_Set_SEL_RS422IsSet = false;
            TE_Addr_0_Set_SEL_SPI = 0;
            TE_Addr_0_Set_SEL_SPIIsSet = false;
            TE_Addr_0_Set_SEL_UART = 0;
            TE_Addr_0_Set_SEL_UARTIsSet = false;
            TE_Addr_0_Set_Power = 0;
            TE_Addr_0_Set_PowerIsSet = false;
            TE_Addr_0_Set_Enable = 0;
            TE_Addr_0_Set_EnableIsSet = false;
            TE_Addr_0_Set_nReset = 0;
            TE_Addr_0_Set_nResetIsSet = false;
            TE_Addr_0_Set_COMM_TR = 0;
            TE_Addr_0_Set_COMM_TRIsSet = false;

            TE_Addr_0_Clear_ScanEnabled = 0;
            TE_Addr_0_Clear_ScanEnabledIsSet = false;
            TE_Addr_0_Clear_Detected = 0;
            TE_Addr_0_Clear_DetectedIsSet = false;
            TE_Addr_0_Clear_Type = 0;
            TE_Addr_0_Clear_TypeIsSet = false;
            TE_Addr_0_Clear_SEL_CAN0 = 0;
            TE_Addr_0_Clear_SEL_CAN0IsSet = false;
            TE_Addr_0_Clear_SEL_CAN1 = 0;
            TE_Addr_0_Clear_SEL_CAN1IsSet = false;
            TE_Addr_0_Clear_SEL_RS485 = 0;
            TE_Addr_0_Clear_SEL_RS485IsSet = false;
            TE_Addr_0_Clear_SEL_I2C = 0;
            TE_Addr_0_Clear_SEL_I2CIsSet = false;
            TE_Addr_0_Clear_SEL_RS422 = 0;
            TE_Addr_0_Clear_SEL_RS422IsSet = false;
            TE_Addr_0_Clear_SEL_SPI = 0;
            TE_Addr_0_Clear_SEL_SPIIsSet = false;
            TE_Addr_0_Clear_SEL_UART = 0;
            TE_Addr_0_Clear_SEL_UARTIsSet = false;
            TE_Addr_0_Clear_Power = 0;
            TE_Addr_0_Clear_PowerIsSet = false;
            TE_Addr_0_Clear_Enable = 0;
            TE_Addr_0_Clear_EnableIsSet = false;
            TE_Addr_0_Clear_nReset = 0;
            TE_Addr_0_Clear_nResetIsSet = false;
            TE_Addr_0_Clear_COMM_TR = 0;
            TE_Addr_0_Clear_COMM_TRIsSet = false;

            TE_Addr_1_ScanEnabled = 0;
            TE_Addr_1_ScanEnabledIsSet = false;
            TE_Addr_1_Detected = 0;
            TE_Addr_1_DetectedIsSet = false;
            TE_Addr_1_Type = 0;
            TE_Addr_1_TypeIsSet = false;
            TE_Addr_1_SEL_CAN0 = 0;
            TE_Addr_1_SEL_CAN0IsSet = false;
            TE_Addr_1_SEL_CAN1 = 0;
            TE_Addr_1_SEL_CAN1IsSet = false;
            TE_Addr_1_SEL_RS485 = 0;
            TE_Addr_1_SEL_RS485IsSet = false;
            TE_Addr_1_SEL_I2C = 0;
            TE_Addr_1_SEL_I2CIsSet = false;
            TE_Addr_1_SEL_RS422 = 0;
            TE_Addr_1_SEL_RS422IsSet = false;
            TE_Addr_1_SEL_SPI = 0;
            TE_Addr_1_SEL_SPIIsSet = false;
            TE_Addr_1_SEL_UART = 0;
            TE_Addr_1_SEL_UARTIsSet = false;
            TE_Addr_1_Power = 0;
            TE_Addr_1_PowerIsSet = false;
            TE_Addr_1_Enable = 0;
            TE_Addr_1_EnableIsSet = false;
            TE_Addr_1_nReset = 0;
            TE_Addr_1_nResetIsSet = false;
            TE_Addr_1_COMM_TR = 0;
            TE_Addr_1_COMM_TRIsSet = false;

            TE_Addr_1_Set_ScanEnabled = 0;
            TE_Addr_1_Set_ScanEnabledIsSet = false;
            TE_Addr_1_Set_Detected = 0;
            TE_Addr_1_Set_DetectedIsSet = false;
            TE_Addr_1_Set_Type = 0;
            TE_Addr_1_Set_TypeIsSet = false;
            TE_Addr_1_Set_SEL_CAN0 = 0;
            TE_Addr_1_Set_SEL_CAN0IsSet = false;
            TE_Addr_1_Set_SEL_CAN1 = 0;
            TE_Addr_1_Set_SEL_CAN1IsSet = false;
            TE_Addr_1_Set_SEL_RS485 = 0;
            TE_Addr_1_Set_SEL_RS485IsSet = false;
            TE_Addr_1_Set_SEL_I2C = 0;
            TE_Addr_1_Set_SEL_I2CIsSet = false;
            TE_Addr_1_Set_SEL_RS422 = 0;
            TE_Addr_1_Set_SEL_RS422IsSet = false;
            TE_Addr_1_Set_SEL_SPI = 0;
            TE_Addr_1_Set_SEL_SPIIsSet = false;
            TE_Addr_1_Set_SEL_UART = 0;
            TE_Addr_1_Set_SEL_UARTIsSet = false;
            TE_Addr_1_Set_Power = 0;
            TE_Addr_1_Set_PowerIsSet = false;
            TE_Addr_1_Set_Enable = 0;
            TE_Addr_1_Set_EnableIsSet = false;
            TE_Addr_1_Set_nReset = 0;
            TE_Addr_1_Set_nResetIsSet = false;
            TE_Addr_1_Set_COMM_TR = 0;
            TE_Addr_1_Set_COMM_TRIsSet = false;

            TE_Addr_1_Clear_ScanEnabled = 0;
            TE_Addr_1_Clear_ScanEnabledIsSet = false;
            TE_Addr_1_Clear_Detected = 0;
            TE_Addr_1_Clear_DetectedIsSet = false;
            TE_Addr_1_Clear_Type = 0;
            TE_Addr_1_Clear_TypeIsSet = false;
            TE_Addr_1_Clear_SEL_CAN0 = 0;
            TE_Addr_1_Clear_SEL_CAN0IsSet = false;
            TE_Addr_1_Clear_SEL_CAN1 = 0;
            TE_Addr_1_Clear_SEL_CAN1IsSet = false;
            TE_Addr_1_Clear_SEL_RS485 = 0;
            TE_Addr_1_Clear_SEL_RS485IsSet = false;
            TE_Addr_1_Clear_SEL_I2C = 0;
            TE_Addr_1_Clear_SEL_I2CIsSet = false;
            TE_Addr_1_Clear_SEL_RS422 = 0;
            TE_Addr_1_Clear_SEL_RS422IsSet = false;
            TE_Addr_1_Clear_SEL_SPI = 0;
            TE_Addr_1_Clear_SEL_SPIIsSet = false;
            TE_Addr_1_Clear_SEL_UART = 0;
            TE_Addr_1_Clear_SEL_UARTIsSet = false;
            TE_Addr_1_Clear_Power = 0;
            TE_Addr_1_Clear_PowerIsSet = false;
            TE_Addr_1_Clear_Enable = 0;
            TE_Addr_1_Clear_EnableIsSet = false;
            TE_Addr_1_Clear_nReset = 0;
            TE_Addr_1_Clear_nResetIsSet = false;
            TE_Addr_1_Clear_COMM_TR = 0;
            TE_Addr_1_Clear_COMM_TRIsSet = false;

            TE_Addr_2_ScanEnabled = 0;
            TE_Addr_2_ScanEnabledIsSet = false;
            TE_Addr_2_Detected = 0;
            TE_Addr_2_DetectedIsSet = false;
            TE_Addr_2_Type = 0;
            TE_Addr_2_TypeIsSet = false;
            TE_Addr_2_SEL_CAN0 = 0;
            TE_Addr_2_SEL_CAN0IsSet = false;
            TE_Addr_2_SEL_CAN1 = 0;
            TE_Addr_2_SEL_CAN1IsSet = false;
            TE_Addr_2_SEL_RS485 = 0;
            TE_Addr_2_SEL_RS485IsSet = false;
            TE_Addr_2_SEL_I2C = 0;
            TE_Addr_2_SEL_I2CIsSet = false;
            TE_Addr_2_SEL_RS422 = 0;
            TE_Addr_2_SEL_RS422IsSet = false;
            TE_Addr_2_SEL_SPI = 0;
            TE_Addr_2_SEL_SPIIsSet = false;
            TE_Addr_2_SEL_UART = 0;
            TE_Addr_2_SEL_UARTIsSet = false;
            TE_Addr_2_Power = 0;
            TE_Addr_2_PowerIsSet = false;
            TE_Addr_2_Enable = 0;
            TE_Addr_2_EnableIsSet = false;
            TE_Addr_2_nReset = 0;
            TE_Addr_2_nResetIsSet = false;
            TE_Addr_2_COMM_TR = 0;
            TE_Addr_2_COMM_TRIsSet = false;

            TE_Addr_2_Set_ScanEnabled = 0;
            TE_Addr_2_Set_ScanEnabledIsSet = false;
            TE_Addr_2_Set_Detected = 0;
            TE_Addr_2_Set_DetectedIsSet = false;
            TE_Addr_2_Set_Type = 0;
            TE_Addr_2_Set_TypeIsSet = false;
            TE_Addr_2_Set_SEL_CAN0 = 0;
            TE_Addr_2_Set_SEL_CAN0IsSet = false;
            TE_Addr_2_Set_SEL_CAN1 = 0;
            TE_Addr_2_Set_SEL_CAN1IsSet = false;
            TE_Addr_2_Set_SEL_RS485 = 0;
            TE_Addr_2_Set_SEL_RS485IsSet = false;
            TE_Addr_2_Set_SEL_I2C = 0;
            TE_Addr_2_Set_SEL_I2CIsSet = false;
            TE_Addr_2_Set_SEL_RS422 = 0;
            TE_Addr_2_Set_SEL_RS422IsSet = false;
            TE_Addr_2_Set_SEL_SPI = 0;
            TE_Addr_2_Set_SEL_SPIIsSet = false;
            TE_Addr_2_Set_SEL_UART = 0;
            TE_Addr_2_Set_SEL_UARTIsSet = false;
            TE_Addr_2_Set_Power = 0;
            TE_Addr_2_Set_PowerIsSet = false;
            TE_Addr_2_Set_Enable = 0;
            TE_Addr_2_Set_EnableIsSet = false;
            TE_Addr_2_Set_nReset = 0;
            TE_Addr_2_Set_nResetIsSet = false;
            TE_Addr_2_Set_COMM_TR = 0;
            TE_Addr_2_Set_COMM_TRIsSet = false;

            TE_Addr_2_Clear_ScanEnabled = 0;
            TE_Addr_2_Clear_ScanEnabledIsSet = false;
            TE_Addr_2_Clear_Detected = 0;
            TE_Addr_2_Clear_DetectedIsSet = false;
            TE_Addr_2_Clear_Type = 0;
            TE_Addr_2_Clear_TypeIsSet = false;
            TE_Addr_2_Clear_SEL_CAN0 = 0;
            TE_Addr_2_Clear_SEL_CAN0IsSet = false;
            TE_Addr_2_Clear_SEL_CAN1 = 0;
            TE_Addr_2_Clear_SEL_CAN1IsSet = false;
            TE_Addr_2_Clear_SEL_RS485 = 0;
            TE_Addr_2_Clear_SEL_RS485IsSet = false;
            TE_Addr_2_Clear_SEL_I2C = 0;
            TE_Addr_2_Clear_SEL_I2CIsSet = false;
            TE_Addr_2_Clear_SEL_RS422 = 0;
            TE_Addr_2_Clear_SEL_RS422IsSet = false;
            TE_Addr_2_Clear_SEL_SPI = 0;
            TE_Addr_2_Clear_SEL_SPIIsSet = false;
            TE_Addr_2_Clear_SEL_UART = 0;
            TE_Addr_2_Clear_SEL_UARTIsSet = false;
            TE_Addr_2_Clear_Power = 0;
            TE_Addr_2_Clear_PowerIsSet = false;
            TE_Addr_2_Clear_Enable = 0;
            TE_Addr_2_Clear_EnableIsSet = false;
            TE_Addr_2_Clear_nReset = 0;
            TE_Addr_2_Clear_nResetIsSet = false;
            TE_Addr_2_Clear_COMM_TR = 0;
            TE_Addr_2_Clear_COMM_TRIsSet = false;

            TE_Addr_3_ScanEnabled = 0;
            TE_Addr_3_ScanEnabledIsSet = false;
            TE_Addr_3_Detected = 0;
            TE_Addr_3_DetectedIsSet = false;
            TE_Addr_3_Type = 0;
            TE_Addr_3_TypeIsSet = false;
            TE_Addr_3_SEL_CAN0 = 0;
            TE_Addr_3_SEL_CAN0IsSet = false;
            TE_Addr_3_SEL_CAN1 = 0;
            TE_Addr_3_SEL_CAN1IsSet = false;
            TE_Addr_3_SEL_RS485 = 0;
            TE_Addr_3_SEL_RS485IsSet = false;
            TE_Addr_3_SEL_I2C = 0;
            TE_Addr_3_SEL_I2CIsSet = false;
            TE_Addr_3_SEL_RS422 = 0;
            TE_Addr_3_SEL_RS422IsSet = false;
            TE_Addr_3_SEL_SPI = 0;
            TE_Addr_3_SEL_SPIIsSet = false;
            TE_Addr_3_SEL_UART = 0;
            TE_Addr_3_SEL_UARTIsSet = false;
            TE_Addr_3_Power = 0;
            TE_Addr_3_PowerIsSet = false;
            TE_Addr_3_Enable = 0;
            TE_Addr_3_EnableIsSet = false;
            TE_Addr_3_nReset = 0;
            TE_Addr_3_nResetIsSet = false;
            TE_Addr_3_COMM_TR = 0;
            TE_Addr_3_COMM_TRIsSet = false;

            TE_Addr_3_Set_ScanEnabled = 0;
            TE_Addr_3_Set_ScanEnabledIsSet = false;
            TE_Addr_3_Set_Detected = 0;
            TE_Addr_3_Set_DetectedIsSet = false;
            TE_Addr_3_Set_Type = 0;
            TE_Addr_3_Set_TypeIsSet = false;
            TE_Addr_3_Set_SEL_CAN0 = 0;
            TE_Addr_3_Set_SEL_CAN0IsSet = false;
            TE_Addr_3_Set_SEL_CAN1 = 0;
            TE_Addr_3_Set_SEL_CAN1IsSet = false;
            TE_Addr_3_Set_SEL_RS485 = 0;
            TE_Addr_3_Set_SEL_RS485IsSet = false;
            TE_Addr_3_Set_SEL_I2C = 0;
            TE_Addr_3_Set_SEL_I2CIsSet = false;
            TE_Addr_3_Set_SEL_RS422 = 0;
            TE_Addr_3_Set_SEL_RS422IsSet = false;
            TE_Addr_3_Set_SEL_SPI = 0;
            TE_Addr_3_Set_SEL_SPIIsSet = false;
            TE_Addr_3_Set_SEL_UART = 0;
            TE_Addr_3_Set_SEL_UARTIsSet = false;
            TE_Addr_3_Set_Power = 0;
            TE_Addr_3_Set_PowerIsSet = false;
            TE_Addr_3_Set_Enable = 0;
            TE_Addr_3_Set_EnableIsSet = false;
            TE_Addr_3_Set_nReset = 0;
            TE_Addr_3_Set_nResetIsSet = false;
            TE_Addr_3_Set_COMM_TR = 0;
            TE_Addr_3_Set_COMM_TRIsSet = false;

            TE_Addr_3_Clear_ScanEnabled = 0;
            TE_Addr_3_Clear_ScanEnabledIsSet = false;
            TE_Addr_3_Clear_Detected = 0;
            TE_Addr_3_Clear_DetectedIsSet = false;
            TE_Addr_3_Clear_Type = 0;
            TE_Addr_3_Clear_TypeIsSet = false;
            TE_Addr_3_Clear_SEL_CAN0 = 0;
            TE_Addr_3_Clear_SEL_CAN0IsSet = false;
            TE_Addr_3_Clear_SEL_CAN1 = 0;
            TE_Addr_3_Clear_SEL_CAN1IsSet = false;
            TE_Addr_3_Clear_SEL_RS485 = 0;
            TE_Addr_3_Clear_SEL_RS485IsSet = false;
            TE_Addr_3_Clear_SEL_I2C = 0;
            TE_Addr_3_Clear_SEL_I2CIsSet = false;
            TE_Addr_3_Clear_SEL_RS422 = 0;
            TE_Addr_3_Clear_SEL_RS422IsSet = false;
            TE_Addr_3_Clear_SEL_SPI = 0;
            TE_Addr_3_Clear_SEL_SPIIsSet = false;
            TE_Addr_3_Clear_SEL_UART = 0;
            TE_Addr_3_Clear_SEL_UARTIsSet = false;
            TE_Addr_3_Clear_Power = 0;
            TE_Addr_3_Clear_PowerIsSet = false;
            TE_Addr_3_Clear_Enable = 0;
            TE_Addr_3_Clear_EnableIsSet = false;
            TE_Addr_3_Clear_nReset = 0;
            TE_Addr_3_Clear_nResetIsSet = false;
            TE_Addr_3_Clear_COMM_TR = 0;
            TE_Addr_3_Clear_COMM_TRIsSet = false;

            MTC_Addr_0_ScanEnabled = 0;
            MTC_Addr_0_ScanEnabledIsSet = false;
            MTC_Addr_0_Detected = 0;
            MTC_Addr_0_DetectedIsSet = false;
            MTC_Addr_0_Type = 0;
            MTC_Addr_0_TypeIsSet = false;
            MTC_Addr_0_ENABLE_1 = 0;
            MTC_Addr_0_ENABLE_1IsSet = false;
            MTC_Addr_0_ENABLE_2 = 0;
            MTC_Addr_0_ENABLE_2IsSet = false;
            MTC_Addr_0_SEL_I2C_1 = 0;
            MTC_Addr_0_SEL_I2C_1IsSet = false;
            MTC_Addr_0_SEL_I2C_2 = 0;
            MTC_Addr_0_SEL_I2C_2IsSet = false;
            MTC_Addr_0_SEL_UART_1 = 0;
            MTC_Addr_0_SEL_UART_1IsSet = false;
            MTC_Addr_0_SEL_UART_2 = 0;
            MTC_Addr_0_SEL_UART_2IsSet = false;
            MTC_Addr_0_SEL_UART_3 = 0;
            MTC_Addr_0_SEL_UART_3IsSet = false;
            MTC_Addr_0_SEL_UART_4 = 0;
            MTC_Addr_0_SEL_UART_4IsSet = false;
            MTC_Addr_0_SEL_UART_5 = 0;
            MTC_Addr_0_SEL_UART_5IsSet = false;
            MTC_Addr_0_SEL_UART_6 = 0;
            MTC_Addr_0_SEL_UART_6IsSet = false;
            MTC_Addr_0_SEL_VBAT = 0;
            MTC_Addr_0_SEL_VBATIsSet = false;
            MTC_Addr_0_SEL_VBAT_ALT = 0;
            MTC_Addr_0_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_0_SEL_VBAT_FPGA = 0;
            MTC_Addr_0_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_0_SEL_nRESET_1 = 0;
            MTC_Addr_0_SEL_nRESET_1IsSet = false;
            MTC_Addr_0_SEL_nRESET_2 = 0;
            MTC_Addr_0_SEL_nRESET_2IsSet = false;
            MTC_Addr_0_SEL_nRESET_3 = 0;
            MTC_Addr_0_SEL_nRESET_3IsSet = false;
            MTC_Addr_0_SEL_CS_1 = 0;
            MTC_Addr_0_SEL_CS_1IsSet = false;
            MTC_Addr_0_SEL_CS_2 = 0;
            MTC_Addr_0_SEL_CS_2IsSet = false;
            MTC_Addr_0_SEL_CS_3 = 0;
            MTC_Addr_0_SEL_CS_3IsSet = false;
            MTC_Addr_0_SEL_CS_4 = 0;
            MTC_Addr_0_SEL_CS_4IsSet = false;
            MTC_Addr_0_SEL_CS_5 = 0;
            MTC_Addr_0_SEL_CS_5IsSet = false;
            MTC_Addr_0_SEL_CS_6 = 0;
            MTC_Addr_0_SEL_CS_6IsSet = false;
            MTC_Addr_0_SEL_SPI_1 = 0;
            MTC_Addr_0_SEL_SPI_1IsSet = false;
            MTC_Addr_0_SEL_SPI_2 = 0;
            MTC_Addr_0_SEL_SPI_2IsSet = false;
            MTC_Addr_0_SEL_CAN_1 = 0;
            MTC_Addr_0_SEL_CAN_1IsSet = false;
            MTC_Addr_0_SEL_CAN_2 = 0;
            MTC_Addr_0_SEL_CAN_2IsSet = false;
            MTC_Addr_0_SEL_CAN_3 = 0;
            MTC_Addr_0_SEL_CAN_3IsSet = false;
            MTC_Addr_0_SEL_RS422 = 0;
            MTC_Addr_0_SEL_RS422IsSet = false;

            MTC_Addr_0_Set_ScanEnabled = 0;
            MTC_Addr_0_Set_ScanEnabledIsSet = false;
            MTC_Addr_0_Set_Detected = 0;
            MTC_Addr_0_Set_DetectedIsSet = false;
            MTC_Addr_0_Set_Type = 0;
            MTC_Addr_0_Set_TypeIsSet = false;
            MTC_Addr_0_Set_ENABLE_1 = 0;
            MTC_Addr_0_Set_ENABLE_1IsSet = false;
            MTC_Addr_0_Set_ENABLE_2 = 0;
            MTC_Addr_0_Set_ENABLE_2IsSet = false;
            MTC_Addr_0_Set_SEL_I2C_1 = 0;
            MTC_Addr_0_Set_SEL_I2C_1IsSet = false;
            MTC_Addr_0_Set_SEL_I2C_2 = 0;
            MTC_Addr_0_Set_SEL_I2C_2IsSet = false;
            MTC_Addr_0_Set_SEL_UART_1 = 0;
            MTC_Addr_0_Set_SEL_UART_1IsSet = false;
            MTC_Addr_0_Set_SEL_UART_2 = 0;
            MTC_Addr_0_Set_SEL_UART_2IsSet = false;
            MTC_Addr_0_Set_SEL_UART_3 = 0;
            MTC_Addr_0_Set_SEL_UART_3IsSet = false;
            MTC_Addr_0_Set_SEL_UART_4 = 0;
            MTC_Addr_0_Set_SEL_UART_4IsSet = false;
            MTC_Addr_0_Set_SEL_UART_5 = 0;
            MTC_Addr_0_Set_SEL_UART_5IsSet = false;
            MTC_Addr_0_Set_SEL_UART_6 = 0;
            MTC_Addr_0_Set_SEL_UART_6IsSet = false;
            MTC_Addr_0_Set_SEL_VBAT = 0;
            MTC_Addr_0_Set_SEL_VBATIsSet = false;
            MTC_Addr_0_Set_SEL_VBAT_ALT = 0;
            MTC_Addr_0_Set_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_0_Set_SEL_VBAT_FPGA = 0;
            MTC_Addr_0_Set_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_0_Set_SEL_nRESET_1 = 0;
            MTC_Addr_0_Set_SEL_nRESET_1IsSet = false;
            MTC_Addr_0_Set_SEL_nRESET_2 = 0;
            MTC_Addr_0_Set_SEL_nRESET_2IsSet = false;
            MTC_Addr_0_Set_SEL_nRESET_3 = 0;
            MTC_Addr_0_Set_SEL_nRESET_3IsSet = false;
            MTC_Addr_0_Set_SEL_CS_1 = 0;
            MTC_Addr_0_Set_SEL_CS_1IsSet = false;
            MTC_Addr_0_Set_SEL_CS_2 = 0;
            MTC_Addr_0_Set_SEL_CS_2IsSet = false;
            MTC_Addr_0_Set_SEL_CS_3 = 0;
            MTC_Addr_0_Set_SEL_CS_3IsSet = false;
            MTC_Addr_0_Set_SEL_CS_4 = 0;
            MTC_Addr_0_Set_SEL_CS_4IsSet = false;
            MTC_Addr_0_Set_SEL_CS_5 = 0;
            MTC_Addr_0_Set_SEL_CS_5IsSet = false;
            MTC_Addr_0_Set_SEL_CS_6 = 0;
            MTC_Addr_0_Set_SEL_CS_6IsSet = false;
            MTC_Addr_0_Set_SEL_SPI_1 = 0;
            MTC_Addr_0_Set_SEL_SPI_1IsSet = false;
            MTC_Addr_0_Set_SEL_SPI_2 = 0;
            MTC_Addr_0_Set_SEL_SPI_2IsSet = false;
            MTC_Addr_0_Set_SEL_CAN_1 = 0;
            MTC_Addr_0_Set_SEL_CAN_1IsSet = false;
            MTC_Addr_0_Set_SEL_CAN_2 = 0;
            MTC_Addr_0_Set_SEL_CAN_2IsSet = false;
            MTC_Addr_0_Set_SEL_CAN_3 = 0;
            MTC_Addr_0_Set_SEL_CAN_3IsSet = false;
            MTC_Addr_0_Set_SEL_RS422 = 0;
            MTC_Addr_0_Set_SEL_RS422IsSet = false;

            MTC_Addr_0_Clear_ScanEnabled = 0;
            MTC_Addr_0_Clear_ScanEnabledIsSet = false;
            MTC_Addr_0_Clear_Detected = 0;
            MTC_Addr_0_Clear_DetectedIsSet = false;
            MTC_Addr_0_Clear_Type = 0;
            MTC_Addr_0_Clear_TypeIsSet = false;
            MTC_Addr_0_Clear_ENABLE_1 = 0;
            MTC_Addr_0_Clear_ENABLE_1IsSet = false;
            MTC_Addr_0_Clear_ENABLE_2 = 0;
            MTC_Addr_0_Clear_ENABLE_2IsSet = false;
            MTC_Addr_0_Clear_SEL_I2C_1 = 0;
            MTC_Addr_0_Clear_SEL_I2C_1IsSet = false;
            MTC_Addr_0_Clear_SEL_I2C_2 = 0;
            MTC_Addr_0_Clear_SEL_I2C_2IsSet = false;
            MTC_Addr_0_Clear_SEL_UART_1 = 0;
            MTC_Addr_0_Clear_SEL_UART_1IsSet = false;
            MTC_Addr_0_Clear_SEL_UART_2 = 0;
            MTC_Addr_0_Clear_SEL_UART_2IsSet = false;
            MTC_Addr_0_Clear_SEL_UART_3 = 0;
            MTC_Addr_0_Clear_SEL_UART_3IsSet = false;
            MTC_Addr_0_Clear_SEL_UART_4 = 0;
            MTC_Addr_0_Clear_SEL_UART_4IsSet = false;
            MTC_Addr_0_Clear_SEL_UART_5 = 0;
            MTC_Addr_0_Clear_SEL_UART_5IsSet = false;
            MTC_Addr_0_Clear_SEL_UART_6 = 0;
            MTC_Addr_0_Clear_SEL_UART_6IsSet = false;
            MTC_Addr_0_Clear_SEL_VBAT = 0;
            MTC_Addr_0_Clear_SEL_VBATIsSet = false;
            MTC_Addr_0_Clear_SEL_VBAT_ALT = 0;
            MTC_Addr_0_Clear_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_0_Clear_SEL_VBAT_FPGA = 0;
            MTC_Addr_0_Clear_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_0_Clear_SEL_nRESET_1 = 0;
            MTC_Addr_0_Clear_SEL_nRESET_1IsSet = false;
            MTC_Addr_0_Clear_SEL_nRESET_2 = 0;
            MTC_Addr_0_Clear_SEL_nRESET_2IsSet = false;
            MTC_Addr_0_Clear_SEL_nRESET_3 = 0;
            MTC_Addr_0_Clear_SEL_nRESET_3IsSet = false;
            MTC_Addr_0_Clear_SEL_CS_1 = 0;
            MTC_Addr_0_Clear_SEL_CS_1IsSet = false;
            MTC_Addr_0_Clear_SEL_CS_2 = 0;
            MTC_Addr_0_Clear_SEL_CS_2IsSet = false;
            MTC_Addr_0_Clear_SEL_CS_3 = 0;
            MTC_Addr_0_Clear_SEL_CS_3IsSet = false;
            MTC_Addr_0_Clear_SEL_CS_4 = 0;
            MTC_Addr_0_Clear_SEL_CS_4IsSet = false;
            MTC_Addr_0_Clear_SEL_CS_5 = 0;
            MTC_Addr_0_Clear_SEL_CS_5IsSet = false;
            MTC_Addr_0_Clear_SEL_CS_6 = 0;
            MTC_Addr_0_Clear_SEL_CS_6IsSet = false;
            MTC_Addr_0_Clear_SEL_SPI_1 = 0;
            MTC_Addr_0_Clear_SEL_SPI_1IsSet = false;
            MTC_Addr_0_Clear_SEL_SPI_2 = 0;
            MTC_Addr_0_Clear_SEL_SPI_2IsSet = false;
            MTC_Addr_0_Clear_SEL_CAN_1 = 0;
            MTC_Addr_0_Clear_SEL_CAN_1IsSet = false;
            MTC_Addr_0_Clear_SEL_CAN_2 = 0;
            MTC_Addr_0_Clear_SEL_CAN_2IsSet = false;
            MTC_Addr_0_Clear_SEL_CAN_3 = 0;
            MTC_Addr_0_Clear_SEL_CAN_3IsSet = false;
            MTC_Addr_0_Clear_SEL_RS422 = 0;
            MTC_Addr_0_Clear_SEL_RS422IsSet = false;

            MTC_Addr_1_ScanEnabled = 0;
            MTC_Addr_1_ScanEnabledIsSet = false;
            MTC_Addr_1_Detected = 0;
            MTC_Addr_1_DetectedIsSet = false;
            MTC_Addr_1_Type = 0;
            MTC_Addr_1_TypeIsSet = false;
            MTC_Addr_1_ENABLE_1 = 0;
            MTC_Addr_1_ENABLE_1IsSet = false;
            MTC_Addr_1_ENABLE_2 = 0;
            MTC_Addr_1_ENABLE_2IsSet = false;
            MTC_Addr_1_SEL_I2C_1 = 0;
            MTC_Addr_1_SEL_I2C_1IsSet = false;
            MTC_Addr_1_SEL_I2C_2 = 0;
            MTC_Addr_1_SEL_I2C_2IsSet = false;
            MTC_Addr_1_SEL_UART_1 = 0;
            MTC_Addr_1_SEL_UART_1IsSet = false;
            MTC_Addr_1_SEL_UART_2 = 0;
            MTC_Addr_1_SEL_UART_2IsSet = false;
            MTC_Addr_1_SEL_UART_3 = 0;
            MTC_Addr_1_SEL_UART_3IsSet = false;
            MTC_Addr_1_SEL_UART_4 = 0;
            MTC_Addr_1_SEL_UART_4IsSet = false;
            MTC_Addr_1_SEL_UART_5 = 0;
            MTC_Addr_1_SEL_UART_5IsSet = false;
            MTC_Addr_1_SEL_UART_6 = 0;
            MTC_Addr_1_SEL_UART_6IsSet = false;
            MTC_Addr_1_SEL_VBAT = 0;
            MTC_Addr_1_SEL_VBATIsSet = false;
            MTC_Addr_1_SEL_VBAT_ALT = 0;
            MTC_Addr_1_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_1_SEL_VBAT_FPGA = 0;
            MTC_Addr_1_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_1_SEL_nRESET_1 = 0;
            MTC_Addr_1_SEL_nRESET_1IsSet = false;
            MTC_Addr_1_SEL_nRESET_2 = 0;
            MTC_Addr_1_SEL_nRESET_2IsSet = false;
            MTC_Addr_1_SEL_nRESET_3 = 0;
            MTC_Addr_1_SEL_nRESET_3IsSet = false;
            MTC_Addr_1_SEL_CS_1 = 0;
            MTC_Addr_1_SEL_CS_1IsSet = false;
            MTC_Addr_1_SEL_CS_2 = 0;
            MTC_Addr_1_SEL_CS_2IsSet = false;
            MTC_Addr_1_SEL_CS_3 = 0;
            MTC_Addr_1_SEL_CS_3IsSet = false;
            MTC_Addr_1_SEL_CS_4 = 0;
            MTC_Addr_1_SEL_CS_4IsSet = false;
            MTC_Addr_1_SEL_CS_5 = 0;
            MTC_Addr_1_SEL_CS_5IsSet = false;
            MTC_Addr_1_SEL_CS_6 = 0;
            MTC_Addr_1_SEL_CS_6IsSet = false;
            MTC_Addr_1_SEL_SPI_1 = 0;
            MTC_Addr_1_SEL_SPI_1IsSet = false;
            MTC_Addr_1_SEL_SPI_2 = 0;
            MTC_Addr_1_SEL_SPI_2IsSet = false;
            MTC_Addr_1_SEL_CAN_1 = 0;
            MTC_Addr_1_SEL_CAN_1IsSet = false;
            MTC_Addr_1_SEL_CAN_2 = 0;
            MTC_Addr_1_SEL_CAN_2IsSet = false;
            MTC_Addr_1_SEL_CAN_3 = 0;
            MTC_Addr_1_SEL_CAN_3IsSet = false;
            MTC_Addr_1_SEL_RS422 = 0;
            MTC_Addr_1_SEL_RS422IsSet = false;

            MTC_Addr_1_Set_ScanEnabled = 0;
            MTC_Addr_1_Set_ScanEnabledIsSet = false;
            MTC_Addr_1_Set_Detected = 0;
            MTC_Addr_1_Set_DetectedIsSet = false;
            MTC_Addr_1_Set_Type = 0;
            MTC_Addr_1_Set_TypeIsSet = false;
            MTC_Addr_1_Set_ENABLE_1 = 0;
            MTC_Addr_1_Set_ENABLE_1IsSet = false;
            MTC_Addr_1_Set_ENABLE_2 = 0;
            MTC_Addr_1_Set_ENABLE_2IsSet = false;
            MTC_Addr_1_Set_SEL_I2C_1 = 0;
            MTC_Addr_1_Set_SEL_I2C_1IsSet = false;
            MTC_Addr_1_Set_SEL_I2C_2 = 0;
            MTC_Addr_1_Set_SEL_I2C_2IsSet = false;
            MTC_Addr_1_Set_SEL_UART_1 = 0;
            MTC_Addr_1_Set_SEL_UART_1IsSet = false;
            MTC_Addr_1_Set_SEL_UART_2 = 0;
            MTC_Addr_1_Set_SEL_UART_2IsSet = false;
            MTC_Addr_1_Set_SEL_UART_3 = 0;
            MTC_Addr_1_Set_SEL_UART_3IsSet = false;
            MTC_Addr_1_Set_SEL_UART_4 = 0;
            MTC_Addr_1_Set_SEL_UART_4IsSet = false;
            MTC_Addr_1_Set_SEL_UART_5 = 0;
            MTC_Addr_1_Set_SEL_UART_5IsSet = false;
            MTC_Addr_1_Set_SEL_UART_6 = 0;
            MTC_Addr_1_Set_SEL_UART_6IsSet = false;
            MTC_Addr_1_Set_SEL_VBAT = 0;
            MTC_Addr_1_Set_SEL_VBATIsSet = false;
            MTC_Addr_1_Set_SEL_VBAT_ALT = 0;
            MTC_Addr_1_Set_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_1_Set_SEL_VBAT_FPGA = 0;
            MTC_Addr_1_Set_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_1_Set_SEL_nRESET_1 = 0;
            MTC_Addr_1_Set_SEL_nRESET_1IsSet = false;
            MTC_Addr_1_Set_SEL_nRESET_2 = 0;
            MTC_Addr_1_Set_SEL_nRESET_2IsSet = false;
            MTC_Addr_1_Set_SEL_nRESET_3 = 0;
            MTC_Addr_1_Set_SEL_nRESET_3IsSet = false;
            MTC_Addr_1_Set_SEL_CS_1 = 0;
            MTC_Addr_1_Set_SEL_CS_1IsSet = false;
            MTC_Addr_1_Set_SEL_CS_2 = 0;
            MTC_Addr_1_Set_SEL_CS_2IsSet = false;
            MTC_Addr_1_Set_SEL_CS_3 = 0;
            MTC_Addr_1_Set_SEL_CS_3IsSet = false;
            MTC_Addr_1_Set_SEL_CS_4 = 0;
            MTC_Addr_1_Set_SEL_CS_4IsSet = false;
            MTC_Addr_1_Set_SEL_CS_5 = 0;
            MTC_Addr_1_Set_SEL_CS_5IsSet = false;
            MTC_Addr_1_Set_SEL_CS_6 = 0;
            MTC_Addr_1_Set_SEL_CS_6IsSet = false;
            MTC_Addr_1_Set_SEL_SPI_1 = 0;
            MTC_Addr_1_Set_SEL_SPI_1IsSet = false;
            MTC_Addr_1_Set_SEL_SPI_2 = 0;
            MTC_Addr_1_Set_SEL_SPI_2IsSet = false;
            MTC_Addr_1_Set_SEL_CAN_1 = 0;
            MTC_Addr_1_Set_SEL_CAN_1IsSet = false;
            MTC_Addr_1_Set_SEL_CAN_2 = 0;
            MTC_Addr_1_Set_SEL_CAN_2IsSet = false;
            MTC_Addr_1_Set_SEL_CAN_3 = 0;
            MTC_Addr_1_Set_SEL_CAN_3IsSet = false;
            MTC_Addr_1_Set_SEL_RS422 = 0;
            MTC_Addr_1_Set_SEL_RS422IsSet = false;

            MTC_Addr_1_Clear_ScanEnabled = 0;
            MTC_Addr_1_Clear_ScanEnabledIsSet = false;
            MTC_Addr_1_Clear_Detected = 0;
            MTC_Addr_1_Clear_DetectedIsSet = false;
            MTC_Addr_1_Clear_Type = 0;
            MTC_Addr_1_Clear_TypeIsSet = false;
            MTC_Addr_1_Clear_ENABLE_1 = 0;
            MTC_Addr_1_Clear_ENABLE_1IsSet = false;
            MTC_Addr_1_Clear_ENABLE_2 = 0;
            MTC_Addr_1_Clear_ENABLE_2IsSet = false;
            MTC_Addr_1_Clear_SEL_I2C_1 = 0;
            MTC_Addr_1_Clear_SEL_I2C_1IsSet = false;
            MTC_Addr_1_Clear_SEL_I2C_2 = 0;
            MTC_Addr_1_Clear_SEL_I2C_2IsSet = false;
            MTC_Addr_1_Clear_SEL_UART_1 = 0;
            MTC_Addr_1_Clear_SEL_UART_1IsSet = false;
            MTC_Addr_1_Clear_SEL_UART_2 = 0;
            MTC_Addr_1_Clear_SEL_UART_2IsSet = false;
            MTC_Addr_1_Clear_SEL_UART_3 = 0;
            MTC_Addr_1_Clear_SEL_UART_3IsSet = false;
            MTC_Addr_1_Clear_SEL_UART_4 = 0;
            MTC_Addr_1_Clear_SEL_UART_4IsSet = false;
            MTC_Addr_1_Clear_SEL_UART_5 = 0;
            MTC_Addr_1_Clear_SEL_UART_5IsSet = false;
            MTC_Addr_1_Clear_SEL_UART_6 = 0;
            MTC_Addr_1_Clear_SEL_UART_6IsSet = false;
            MTC_Addr_1_Clear_SEL_VBAT = 0;
            MTC_Addr_1_Clear_SEL_VBATIsSet = false;
            MTC_Addr_1_Clear_SEL_VBAT_ALT = 0;
            MTC_Addr_1_Clear_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_1_Clear_SEL_VBAT_FPGA = 0;
            MTC_Addr_1_Clear_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_1_Clear_SEL_nRESET_1 = 0;
            MTC_Addr_1_Clear_SEL_nRESET_1IsSet = false;
            MTC_Addr_1_Clear_SEL_nRESET_2 = 0;
            MTC_Addr_1_Clear_SEL_nRESET_2IsSet = false;
            MTC_Addr_1_Clear_SEL_nRESET_3 = 0;
            MTC_Addr_1_Clear_SEL_nRESET_3IsSet = false;
            MTC_Addr_1_Clear_SEL_CS_1 = 0;
            MTC_Addr_1_Clear_SEL_CS_1IsSet = false;
            MTC_Addr_1_Clear_SEL_CS_2 = 0;
            MTC_Addr_1_Clear_SEL_CS_2IsSet = false;
            MTC_Addr_1_Clear_SEL_CS_3 = 0;
            MTC_Addr_1_Clear_SEL_CS_3IsSet = false;
            MTC_Addr_1_Clear_SEL_CS_4 = 0;
            MTC_Addr_1_Clear_SEL_CS_4IsSet = false;
            MTC_Addr_1_Clear_SEL_CS_5 = 0;
            MTC_Addr_1_Clear_SEL_CS_5IsSet = false;
            MTC_Addr_1_Clear_SEL_CS_6 = 0;
            MTC_Addr_1_Clear_SEL_CS_6IsSet = false;
            MTC_Addr_1_Clear_SEL_SPI_1 = 0;
            MTC_Addr_1_Clear_SEL_SPI_1IsSet = false;
            MTC_Addr_1_Clear_SEL_SPI_2 = 0;
            MTC_Addr_1_Clear_SEL_SPI_2IsSet = false;
            MTC_Addr_1_Clear_SEL_CAN_1 = 0;
            MTC_Addr_1_Clear_SEL_CAN_1IsSet = false;
            MTC_Addr_1_Clear_SEL_CAN_2 = 0;
            MTC_Addr_1_Clear_SEL_CAN_2IsSet = false;
            MTC_Addr_1_Clear_SEL_CAN_3 = 0;
            MTC_Addr_1_Clear_SEL_CAN_3IsSet = false;
            MTC_Addr_1_Clear_SEL_RS422 = 0;
            MTC_Addr_1_Clear_SEL_RS422IsSet = false;

            MTC_Addr_2_ScanEnabled = 0;
            MTC_Addr_2_ScanEnabledIsSet = false;
            MTC_Addr_2_Detected = 0;
            MTC_Addr_2_DetectedIsSet = false;
            MTC_Addr_2_Type = 0;
            MTC_Addr_2_TypeIsSet = false;
            MTC_Addr_2_ENABLE_1 = 0;
            MTC_Addr_2_ENABLE_1IsSet = false;
            MTC_Addr_2_ENABLE_2 = 0;
            MTC_Addr_2_ENABLE_2IsSet = false;
            MTC_Addr_2_SEL_I2C_1 = 0;
            MTC_Addr_2_SEL_I2C_1IsSet = false;
            MTC_Addr_2_SEL_I2C_2 = 0;
            MTC_Addr_2_SEL_I2C_2IsSet = false;
            MTC_Addr_2_SEL_UART_1 = 0;
            MTC_Addr_2_SEL_UART_1IsSet = false;
            MTC_Addr_2_SEL_UART_2 = 0;
            MTC_Addr_2_SEL_UART_2IsSet = false;
            MTC_Addr_2_SEL_UART_3 = 0;
            MTC_Addr_2_SEL_UART_3IsSet = false;
            MTC_Addr_2_SEL_UART_4 = 0;
            MTC_Addr_2_SEL_UART_4IsSet = false;
            MTC_Addr_2_SEL_UART_5 = 0;
            MTC_Addr_2_SEL_UART_5IsSet = false;
            MTC_Addr_2_SEL_UART_6 = 0;
            MTC_Addr_2_SEL_UART_6IsSet = false;
            MTC_Addr_2_SEL_VBAT = 0;
            MTC_Addr_2_SEL_VBATIsSet = false;
            MTC_Addr_2_SEL_VBAT_ALT = 0;
            MTC_Addr_2_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_2_SEL_VBAT_FPGA = 0;
            MTC_Addr_2_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_2_SEL_nRESET_1 = 0;
            MTC_Addr_2_SEL_nRESET_1IsSet = false;
            MTC_Addr_2_SEL_nRESET_2 = 0;
            MTC_Addr_2_SEL_nRESET_2IsSet = false;
            MTC_Addr_2_SEL_nRESET_3 = 0;
            MTC_Addr_2_SEL_nRESET_3IsSet = false;
            MTC_Addr_2_SEL_CS_1 = 0;
            MTC_Addr_2_SEL_CS_1IsSet = false;
            MTC_Addr_2_SEL_CS_2 = 0;
            MTC_Addr_2_SEL_CS_2IsSet = false;
            MTC_Addr_2_SEL_CS_3 = 0;
            MTC_Addr_2_SEL_CS_3IsSet = false;
            MTC_Addr_2_SEL_CS_4 = 0;
            MTC_Addr_2_SEL_CS_4IsSet = false;
            MTC_Addr_2_SEL_CS_5 = 0;
            MTC_Addr_2_SEL_CS_5IsSet = false;
            MTC_Addr_2_SEL_CS_6 = 0;
            MTC_Addr_2_SEL_CS_6IsSet = false;
            MTC_Addr_2_SEL_SPI_1 = 0;
            MTC_Addr_2_SEL_SPI_1IsSet = false;
            MTC_Addr_2_SEL_SPI_2 = 0;
            MTC_Addr_2_SEL_SPI_2IsSet = false;
            MTC_Addr_2_SEL_CAN_1 = 0;
            MTC_Addr_2_SEL_CAN_1IsSet = false;
            MTC_Addr_2_SEL_CAN_2 = 0;
            MTC_Addr_2_SEL_CAN_2IsSet = false;
            MTC_Addr_2_SEL_CAN_3 = 0;
            MTC_Addr_2_SEL_CAN_3IsSet = false;
            MTC_Addr_2_SEL_RS422 = 0;
            MTC_Addr_2_SEL_RS422IsSet = false;

            MTC_Addr_2_Set_ScanEnabled = 0;
            MTC_Addr_2_Set_ScanEnabledIsSet = false;
            MTC_Addr_2_Set_Detected = 0;
            MTC_Addr_2_Set_DetectedIsSet = false;
            MTC_Addr_2_Set_Type = 0;
            MTC_Addr_2_Set_TypeIsSet = false;
            MTC_Addr_2_Set_ENABLE_1 = 0;
            MTC_Addr_2_Set_ENABLE_1IsSet = false;
            MTC_Addr_2_Set_ENABLE_2 = 0;
            MTC_Addr_2_Set_ENABLE_2IsSet = false;
            MTC_Addr_2_Set_SEL_I2C_1 = 0;
            MTC_Addr_2_Set_SEL_I2C_1IsSet = false;
            MTC_Addr_2_Set_SEL_I2C_2 = 0;
            MTC_Addr_2_Set_SEL_I2C_2IsSet = false;
            MTC_Addr_2_Set_SEL_UART_1 = 0;
            MTC_Addr_2_Set_SEL_UART_1IsSet = false;
            MTC_Addr_2_Set_SEL_UART_2 = 0;
            MTC_Addr_2_Set_SEL_UART_2IsSet = false;
            MTC_Addr_2_Set_SEL_UART_3 = 0;
            MTC_Addr_2_Set_SEL_UART_3IsSet = false;
            MTC_Addr_2_Set_SEL_UART_4 = 0;
            MTC_Addr_2_Set_SEL_UART_4IsSet = false;
            MTC_Addr_2_Set_SEL_UART_5 = 0;
            MTC_Addr_2_Set_SEL_UART_5IsSet = false;
            MTC_Addr_2_Set_SEL_UART_6 = 0;
            MTC_Addr_2_Set_SEL_UART_6IsSet = false;
            MTC_Addr_2_Set_SEL_VBAT = 0;
            MTC_Addr_2_Set_SEL_VBATIsSet = false;
            MTC_Addr_2_Set_SEL_VBAT_ALT = 0;
            MTC_Addr_2_Set_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_2_Set_SEL_VBAT_FPGA = 0;
            MTC_Addr_2_Set_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_2_Set_SEL_nRESET_1 = 0;
            MTC_Addr_2_Set_SEL_nRESET_1IsSet = false;
            MTC_Addr_2_Set_SEL_nRESET_2 = 0;
            MTC_Addr_2_Set_SEL_nRESET_2IsSet = false;
            MTC_Addr_2_Set_SEL_nRESET_3 = 0;
            MTC_Addr_2_Set_SEL_nRESET_3IsSet = false;
            MTC_Addr_2_Set_SEL_CS_1 = 0;
            MTC_Addr_2_Set_SEL_CS_1IsSet = false;
            MTC_Addr_2_Set_SEL_CS_2 = 0;
            MTC_Addr_2_Set_SEL_CS_2IsSet = false;
            MTC_Addr_2_Set_SEL_CS_3 = 0;
            MTC_Addr_2_Set_SEL_CS_3IsSet = false;
            MTC_Addr_2_Set_SEL_CS_4 = 0;
            MTC_Addr_2_Set_SEL_CS_4IsSet = false;
            MTC_Addr_2_Set_SEL_CS_5 = 0;
            MTC_Addr_2_Set_SEL_CS_5IsSet = false;
            MTC_Addr_2_Set_SEL_CS_6 = 0;
            MTC_Addr_2_Set_SEL_CS_6IsSet = false;
            MTC_Addr_2_Set_SEL_SPI_1 = 0;
            MTC_Addr_2_Set_SEL_SPI_1IsSet = false;
            MTC_Addr_2_Set_SEL_SPI_2 = 0;
            MTC_Addr_2_Set_SEL_SPI_2IsSet = false;
            MTC_Addr_2_Set_SEL_CAN_1 = 0;
            MTC_Addr_2_Set_SEL_CAN_1IsSet = false;
            MTC_Addr_2_Set_SEL_CAN_2 = 0;
            MTC_Addr_2_Set_SEL_CAN_2IsSet = false;
            MTC_Addr_2_Set_SEL_CAN_3 = 0;
            MTC_Addr_2_Set_SEL_CAN_3IsSet = false;
            MTC_Addr_2_Set_SEL_RS422 = 0;
            MTC_Addr_2_Set_SEL_RS422IsSet = false;

            MTC_Addr_2_Clear_ScanEnabled = 0;
            MTC_Addr_2_Clear_ScanEnabledIsSet = false;
            MTC_Addr_2_Clear_Detected = 0;
            MTC_Addr_2_Clear_DetectedIsSet = false;
            MTC_Addr_2_Clear_Type = 0;
            MTC_Addr_2_Clear_TypeIsSet = false;
            MTC_Addr_2_Clear_ENABLE_1 = 0;
            MTC_Addr_2_Clear_ENABLE_1IsSet = false;
            MTC_Addr_2_Clear_ENABLE_2 = 0;
            MTC_Addr_2_Clear_ENABLE_2IsSet = false;
            MTC_Addr_2_Clear_SEL_I2C_1 = 0;
            MTC_Addr_2_Clear_SEL_I2C_1IsSet = false;
            MTC_Addr_2_Clear_SEL_I2C_2 = 0;
            MTC_Addr_2_Clear_SEL_I2C_2IsSet = false;
            MTC_Addr_2_Clear_SEL_UART_1 = 0;
            MTC_Addr_2_Clear_SEL_UART_1IsSet = false;
            MTC_Addr_2_Clear_SEL_UART_2 = 0;
            MTC_Addr_2_Clear_SEL_UART_2IsSet = false;
            MTC_Addr_2_Clear_SEL_UART_3 = 0;
            MTC_Addr_2_Clear_SEL_UART_3IsSet = false;
            MTC_Addr_2_Clear_SEL_UART_4 = 0;
            MTC_Addr_2_Clear_SEL_UART_4IsSet = false;
            MTC_Addr_2_Clear_SEL_UART_5 = 0;
            MTC_Addr_2_Clear_SEL_UART_5IsSet = false;
            MTC_Addr_2_Clear_SEL_UART_6 = 0;
            MTC_Addr_2_Clear_SEL_UART_6IsSet = false;
            MTC_Addr_2_Clear_SEL_VBAT = 0;
            MTC_Addr_2_Clear_SEL_VBATIsSet = false;
            MTC_Addr_2_Clear_SEL_VBAT_ALT = 0;
            MTC_Addr_2_Clear_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_2_Clear_SEL_VBAT_FPGA = 0;
            MTC_Addr_2_Clear_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_2_Clear_SEL_nRESET_1 = 0;
            MTC_Addr_2_Clear_SEL_nRESET_1IsSet = false;
            MTC_Addr_2_Clear_SEL_nRESET_2 = 0;
            MTC_Addr_2_Clear_SEL_nRESET_2IsSet = false;
            MTC_Addr_2_Clear_SEL_nRESET_3 = 0;
            MTC_Addr_2_Clear_SEL_nRESET_3IsSet = false;
            MTC_Addr_2_Clear_SEL_CS_1 = 0;
            MTC_Addr_2_Clear_SEL_CS_1IsSet = false;
            MTC_Addr_2_Clear_SEL_CS_2 = 0;
            MTC_Addr_2_Clear_SEL_CS_2IsSet = false;
            MTC_Addr_2_Clear_SEL_CS_3 = 0;
            MTC_Addr_2_Clear_SEL_CS_3IsSet = false;
            MTC_Addr_2_Clear_SEL_CS_4 = 0;
            MTC_Addr_2_Clear_SEL_CS_4IsSet = false;
            MTC_Addr_2_Clear_SEL_CS_5 = 0;
            MTC_Addr_2_Clear_SEL_CS_5IsSet = false;
            MTC_Addr_2_Clear_SEL_CS_6 = 0;
            MTC_Addr_2_Clear_SEL_CS_6IsSet = false;
            MTC_Addr_2_Clear_SEL_SPI_1 = 0;
            MTC_Addr_2_Clear_SEL_SPI_1IsSet = false;
            MTC_Addr_2_Clear_SEL_SPI_2 = 0;
            MTC_Addr_2_Clear_SEL_SPI_2IsSet = false;
            MTC_Addr_2_Clear_SEL_CAN_1 = 0;
            MTC_Addr_2_Clear_SEL_CAN_1IsSet = false;
            MTC_Addr_2_Clear_SEL_CAN_2 = 0;
            MTC_Addr_2_Clear_SEL_CAN_2IsSet = false;
            MTC_Addr_2_Clear_SEL_CAN_3 = 0;
            MTC_Addr_2_Clear_SEL_CAN_3IsSet = false;
            MTC_Addr_2_Clear_SEL_RS422 = 0;
            MTC_Addr_2_Clear_SEL_RS422IsSet = false;

            MTC_Addr_3_ScanEnabled = 0;
            MTC_Addr_3_ScanEnabledIsSet = false;
            MTC_Addr_3_Detected = 0;
            MTC_Addr_3_DetectedIsSet = false;
            MTC_Addr_3_Type = 0;
            MTC_Addr_3_TypeIsSet = false;
            MTC_Addr_3_ENABLE_1 = 0;
            MTC_Addr_3_ENABLE_1IsSet = false;
            MTC_Addr_3_ENABLE_2 = 0;
            MTC_Addr_3_ENABLE_2IsSet = false;
            MTC_Addr_3_SEL_I2C_1 = 0;
            MTC_Addr_3_SEL_I2C_1IsSet = false;
            MTC_Addr_3_SEL_I2C_2 = 0;
            MTC_Addr_3_SEL_I2C_2IsSet = false;
            MTC_Addr_3_SEL_UART_1 = 0;
            MTC_Addr_3_SEL_UART_1IsSet = false;
            MTC_Addr_3_SEL_UART_2 = 0;
            MTC_Addr_3_SEL_UART_2IsSet = false;
            MTC_Addr_3_SEL_UART_3 = 0;
            MTC_Addr_3_SEL_UART_3IsSet = false;
            MTC_Addr_3_SEL_UART_4 = 0;
            MTC_Addr_3_SEL_UART_4IsSet = false;
            MTC_Addr_3_SEL_UART_5 = 0;
            MTC_Addr_3_SEL_UART_5IsSet = false;
            MTC_Addr_3_SEL_UART_6 = 0;
            MTC_Addr_3_SEL_UART_6IsSet = false;
            MTC_Addr_3_SEL_VBAT = 0;
            MTC_Addr_3_SEL_VBATIsSet = false;
            MTC_Addr_3_SEL_VBAT_ALT = 0;
            MTC_Addr_3_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_3_SEL_VBAT_FPGA = 0;
            MTC_Addr_3_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_3_SEL_nRESET_1 = 0;
            MTC_Addr_3_SEL_nRESET_1IsSet = false;
            MTC_Addr_3_SEL_nRESET_2 = 0;
            MTC_Addr_3_SEL_nRESET_2IsSet = false;
            MTC_Addr_3_SEL_nRESET_3 = 0;
            MTC_Addr_3_SEL_nRESET_3IsSet = false;
            MTC_Addr_3_SEL_CS_1 = 0;
            MTC_Addr_3_SEL_CS_1IsSet = false;
            MTC_Addr_3_SEL_CS_2 = 0;
            MTC_Addr_3_SEL_CS_2IsSet = false;
            MTC_Addr_3_SEL_CS_3 = 0;
            MTC_Addr_3_SEL_CS_3IsSet = false;
            MTC_Addr_3_SEL_CS_4 = 0;
            MTC_Addr_3_SEL_CS_4IsSet = false;
            MTC_Addr_3_SEL_CS_5 = 0;
            MTC_Addr_3_SEL_CS_5IsSet = false;
            MTC_Addr_3_SEL_CS_6 = 0;
            MTC_Addr_3_SEL_CS_6IsSet = false;
            MTC_Addr_3_SEL_SPI_1 = 0;
            MTC_Addr_3_SEL_SPI_1IsSet = false;
            MTC_Addr_3_SEL_SPI_2 = 0;
            MTC_Addr_3_SEL_SPI_2IsSet = false;
            MTC_Addr_3_SEL_CAN_1 = 0;
            MTC_Addr_3_SEL_CAN_1IsSet = false;
            MTC_Addr_3_SEL_CAN_2 = 0;
            MTC_Addr_3_SEL_CAN_2IsSet = false;
            MTC_Addr_3_SEL_CAN_3 = 0;
            MTC_Addr_3_SEL_CAN_3IsSet = false;
            MTC_Addr_3_SEL_RS422 = 0;
            MTC_Addr_3_SEL_RS422IsSet = false;

            MTC_Addr_3_Set_ScanEnabled = 0;
            MTC_Addr_3_Set_ScanEnabledIsSet = false;
            MTC_Addr_3_Set_Detected = 0;
            MTC_Addr_3_Set_DetectedIsSet = false;
            MTC_Addr_3_Set_Type = 0;
            MTC_Addr_3_Set_TypeIsSet = false;
            MTC_Addr_3_Set_ENABLE_1 = 0;
            MTC_Addr_3_Set_ENABLE_1IsSet = false;
            MTC_Addr_3_Set_ENABLE_2 = 0;
            MTC_Addr_3_Set_ENABLE_2IsSet = false;
            MTC_Addr_3_Set_SEL_I2C_1 = 0;
            MTC_Addr_3_Set_SEL_I2C_1IsSet = false;
            MTC_Addr_3_Set_SEL_I2C_2 = 0;
            MTC_Addr_3_Set_SEL_I2C_2IsSet = false;
            MTC_Addr_3_Set_SEL_UART_1 = 0;
            MTC_Addr_3_Set_SEL_UART_1IsSet = false;
            MTC_Addr_3_Set_SEL_UART_2 = 0;
            MTC_Addr_3_Set_SEL_UART_2IsSet = false;
            MTC_Addr_3_Set_SEL_UART_3 = 0;
            MTC_Addr_3_Set_SEL_UART_3IsSet = false;
            MTC_Addr_3_Set_SEL_UART_4 = 0;
            MTC_Addr_3_Set_SEL_UART_4IsSet = false;
            MTC_Addr_3_Set_SEL_UART_5 = 0;
            MTC_Addr_3_Set_SEL_UART_5IsSet = false;
            MTC_Addr_3_Set_SEL_UART_6 = 0;
            MTC_Addr_3_Set_SEL_UART_6IsSet = false;
            MTC_Addr_3_Set_SEL_VBAT = 0;
            MTC_Addr_3_Set_SEL_VBATIsSet = false;
            MTC_Addr_3_Set_SEL_VBAT_ALT = 0;
            MTC_Addr_3_Set_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_3_Set_SEL_VBAT_FPGA = 0;
            MTC_Addr_3_Set_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_3_Set_SEL_nRESET_1 = 0;
            MTC_Addr_3_Set_SEL_nRESET_1IsSet = false;
            MTC_Addr_3_Set_SEL_nRESET_2 = 0;
            MTC_Addr_3_Set_SEL_nRESET_2IsSet = false;
            MTC_Addr_3_Set_SEL_nRESET_3 = 0;
            MTC_Addr_3_Set_SEL_nRESET_3IsSet = false;
            MTC_Addr_3_Set_SEL_CS_1 = 0;
            MTC_Addr_3_Set_SEL_CS_1IsSet = false;
            MTC_Addr_3_Set_SEL_CS_2 = 0;
            MTC_Addr_3_Set_SEL_CS_2IsSet = false;
            MTC_Addr_3_Set_SEL_CS_3 = 0;
            MTC_Addr_3_Set_SEL_CS_3IsSet = false;
            MTC_Addr_3_Set_SEL_CS_4 = 0;
            MTC_Addr_3_Set_SEL_CS_4IsSet = false;
            MTC_Addr_3_Set_SEL_CS_5 = 0;
            MTC_Addr_3_Set_SEL_CS_5IsSet = false;
            MTC_Addr_3_Set_SEL_CS_6 = 0;
            MTC_Addr_3_Set_SEL_CS_6IsSet = false;
            MTC_Addr_3_Set_SEL_SPI_1 = 0;
            MTC_Addr_3_Set_SEL_SPI_1IsSet = false;
            MTC_Addr_3_Set_SEL_SPI_2 = 0;
            MTC_Addr_3_Set_SEL_SPI_2IsSet = false;
            MTC_Addr_3_Set_SEL_CAN_1 = 0;
            MTC_Addr_3_Set_SEL_CAN_1IsSet = false;
            MTC_Addr_3_Set_SEL_CAN_2 = 0;
            MTC_Addr_3_Set_SEL_CAN_2IsSet = false;
            MTC_Addr_3_Set_SEL_CAN_3 = 0;
            MTC_Addr_3_Set_SEL_CAN_3IsSet = false;
            MTC_Addr_3_Set_SEL_RS422 = 0;
            MTC_Addr_3_Set_SEL_RS422IsSet = false;

            MTC_Addr_3_Clear_ScanEnabled = 0;
            MTC_Addr_3_Clear_ScanEnabledIsSet = false;
            MTC_Addr_3_Clear_Detected = 0;
            MTC_Addr_3_Clear_DetectedIsSet = false;
            MTC_Addr_3_Clear_Type = 0;
            MTC_Addr_3_Clear_TypeIsSet = false;
            MTC_Addr_3_Clear_ENABLE_1 = 0;
            MTC_Addr_3_Clear_ENABLE_1IsSet = false;
            MTC_Addr_3_Clear_ENABLE_2 = 0;
            MTC_Addr_3_Clear_ENABLE_2IsSet = false;
            MTC_Addr_3_Clear_SEL_I2C_1 = 0;
            MTC_Addr_3_Clear_SEL_I2C_1IsSet = false;
            MTC_Addr_3_Clear_SEL_I2C_2 = 0;
            MTC_Addr_3_Clear_SEL_I2C_2IsSet = false;
            MTC_Addr_3_Clear_SEL_UART_1 = 0;
            MTC_Addr_3_Clear_SEL_UART_1IsSet = false;
            MTC_Addr_3_Clear_SEL_UART_2 = 0;
            MTC_Addr_3_Clear_SEL_UART_2IsSet = false;
            MTC_Addr_3_Clear_SEL_UART_3 = 0;
            MTC_Addr_3_Clear_SEL_UART_3IsSet = false;
            MTC_Addr_3_Clear_SEL_UART_4 = 0;
            MTC_Addr_3_Clear_SEL_UART_4IsSet = false;
            MTC_Addr_3_Clear_SEL_UART_5 = 0;
            MTC_Addr_3_Clear_SEL_UART_5IsSet = false;
            MTC_Addr_3_Clear_SEL_UART_6 = 0;
            MTC_Addr_3_Clear_SEL_UART_6IsSet = false;
            MTC_Addr_3_Clear_SEL_VBAT = 0;
            MTC_Addr_3_Clear_SEL_VBATIsSet = false;
            MTC_Addr_3_Clear_SEL_VBAT_ALT = 0;
            MTC_Addr_3_Clear_SEL_VBAT_ALTIsSet = false;
            MTC_Addr_3_Clear_SEL_VBAT_FPGA = 0;
            MTC_Addr_3_Clear_SEL_VBAT_FPGAIsSet = false;
            MTC_Addr_3_Clear_SEL_nRESET_1 = 0;
            MTC_Addr_3_Clear_SEL_nRESET_1IsSet = false;
            MTC_Addr_3_Clear_SEL_nRESET_2 = 0;
            MTC_Addr_3_Clear_SEL_nRESET_2IsSet = false;
            MTC_Addr_3_Clear_SEL_nRESET_3 = 0;
            MTC_Addr_3_Clear_SEL_nRESET_3IsSet = false;
            MTC_Addr_3_Clear_SEL_CS_1 = 0;
            MTC_Addr_3_Clear_SEL_CS_1IsSet = false;
            MTC_Addr_3_Clear_SEL_CS_2 = 0;
            MTC_Addr_3_Clear_SEL_CS_2IsSet = false;
            MTC_Addr_3_Clear_SEL_CS_3 = 0;
            MTC_Addr_3_Clear_SEL_CS_3IsSet = false;
            MTC_Addr_3_Clear_SEL_CS_4 = 0;
            MTC_Addr_3_Clear_SEL_CS_4IsSet = false;
            MTC_Addr_3_Clear_SEL_CS_5 = 0;
            MTC_Addr_3_Clear_SEL_CS_5IsSet = false;
            MTC_Addr_3_Clear_SEL_CS_6 = 0;
            MTC_Addr_3_Clear_SEL_CS_6IsSet = false;
            MTC_Addr_3_Clear_SEL_SPI_1 = 0;
            MTC_Addr_3_Clear_SEL_SPI_1IsSet = false;
            MTC_Addr_3_Clear_SEL_SPI_2 = 0;
            MTC_Addr_3_Clear_SEL_SPI_2IsSet = false;
            MTC_Addr_3_Clear_SEL_CAN_1 = 0;
            MTC_Addr_3_Clear_SEL_CAN_1IsSet = false;
            MTC_Addr_3_Clear_SEL_CAN_2 = 0;
            MTC_Addr_3_Clear_SEL_CAN_2IsSet = false;
            MTC_Addr_3_Clear_SEL_CAN_3 = 0;
            MTC_Addr_3_Clear_SEL_CAN_3IsSet = false;
            MTC_Addr_3_Clear_SEL_RS422 = 0;
            MTC_Addr_3_Clear_SEL_RS422IsSet = false;

            RTOS_Status0_uartRxHBOverflow = false;
            RTOS_Status0_uartRxHBOverflowIsSet = false;
            RTOS_Status0_uartRxSBOverflow = false;
            RTOS_Status0_uartRxSBOverflowIsSet = false;
            RTOS_Status0_uartTxSBOverflow = false;
            RTOS_Status0_uartTxSBOverflowIsSet = false;
            RTOS_Status0_uartTxHBOverflow = false;
            RTOS_Status0_uartTxHBOverflowIsSet = false;
            RTOS_Status0_I2CTargetIncomingOverflow = false;
            RTOS_Status0_I2CTargetIncomingOverflowIsSet = false;
            RTOS_Status0_I2CTargetOutgoingOverflow = false;
            RTOS_Status0_I2CTargetOutgoingOverflowIsSet = false;
            RTOS_Status0_CANTargetIncomingOverflow = false;
            RTOS_Status0_CANTargetIncomingOverflowIsSet = false;
            RTOS_Status0_CANInterruptBufferOverflow = false;
            RTOS_Status0_CANInterruptBufferOverflowIsSet = false;
            RTOS_Status0_CANTargetOutgoingOverflow = false;
            RTOS_Status0_CANTargetOutgoingOverflowIsSet = false;
            RTOS_Status0_UARTTargetIncomingOverflow = false;
            RTOS_Status0_UARTTargetIncomingOverflowIsSet = false;
            RTOS_Status0_UARTTargetTxHBOverflow = false;
            RTOS_Status0_UARTTargetTxHBOverflowIsSet = false;
            RTOS_Status0_UARTTargetRxHBOverflow = false;
            RTOS_Status0_UARTTargetRxHBOverflowIsSet = false;
            RTOS_Status0_UARTTargetOutgoingOverflow = false;
            RTOS_Status0_UARTTargetOutgoingOverflowIsSet = false;
            RTOS_Status0_GSETargetIncomingOverflow = false;
            RTOS_Status0_GSETargetIncomingOverflowIsSet = false;
            RTOS_Status0_GSETargetOutgoingOverflow = false;
            RTOS_Status0_GSETargetOutgoingOverflowIsSet = false;
            RTOS_Status0_SERMUX_CRC_Error = false;
            RTOS_Status0_SERMUX_CRC_ErrorIsSet = false;

            UtilI2CConfA_Reset = 0;
            UtilI2CConfA_ResetIsSet = false;
            UtilI2CConfA_SPD = 0;
            UtilI2CConfA_SPDIsSet = false;

            UtilI2CStatus = 0;
            UtilI2CStatusIsSet = false;

            PreviousEndpoint_Number = 0;
            PreviousEndpoint_NumberIsSet = false;

        }

        /*
        * Wrapper for Setters
        */
        protected bool Set<T>(ref T backingField, T value, [CallerMemberName] string propertyname = null)
        {
            // Check if the value and backing field are actualy different
            /*if (EqualityComparer<T>.Default.Equals(backingField, value))
            {
                return false;
            }*/
            
            // Setting the backing field and the RaisePropertyChanged
            backingField = value;
            if (!SupressUpdates)
            {
                OnPropertyChanged(propertyname);
            }
            return true;
        }
        protected virtual void OnPropertyChanged(string propertyname)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyname));
        }

        /*
         * Register on another XTX model. When a value is received for the
         * first time, set this instance's value
         */
        public void RegisterListener(IModel other)
        {
            other.PropertyChanged += OtherHandler;
        }
        
        /*
         * Listener to other instance of the XTX
         */
        public void OtherHandler(object sender, PropertyChangedEventArgs e)
        {
            // We don't need to update when the RXModel's FullRegister updates
            if (e.PropertyName.Contains("FullRegister")){
                return;
            }
        
            // Get has_field for this value
            string propertyString = e.PropertyName;
            string flagPropertyString = e.PropertyName + "IsSet";
        
            // If not set before
            if (!(bool)GetType().GetProperty(flagPropertyString).GetValue(this, null))
            {
                // First set the value
                GetType().GetProperty(propertyString).SetValue(this, sender.GetType().GetProperty(propertyString).GetValue(sender, null));
        
                // Then set the flag
                GetType().GetProperty(flagPropertyString).SetValue(this, true);
        
            }
        }
        
        /*
         * Force an update event to a specific property. This is used when the value is not changed
         * according to us, but the device did not accept a previous value.
         */
        public void ForceUpdate(string propertyname)
        {
            OnPropertyChanged(propertyname);
        }

    }
}
