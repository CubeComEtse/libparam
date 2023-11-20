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
            OBC_REG_CONFMULTI                        = 0x2b,
            OBC_REG_CONFTEMPSENSE                    = 0x2c,
            OBC_REG_XTXPINS                          = 0x30,
            OBC_REG_XTXMULTITESTER                   = 0x31,
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
        }

        public enum OBCRegisterStorageLocations{
        }

        Dictionary<OBCRegisterStorageLocations, (int index, OBCRegisterAddress)> storageLocationLookup = new Dictionary<OBCRegisterStorageLocations, (int index, OBCRegisterAddress)>{ 
        };

        [StructLayout(LayoutKind.Explicit, Pack = 1)]
        public struct RegisterData
        {
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
            public RegConfMulti RegConfMulti;
            [FieldOffset(0)]
            public RegConfTempSense RegConfTempSense;
            [FieldOffset(0)]
            public RegXTXpins RegXTXpins;
            [FieldOffset(0)]
            public RegXTXMultitester RegXTXMultitester;
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
        public struct RegConfMulti
        {
            [FieldOffset(0)]
            UInt32 data0;

            public byte MEnabled
            {
                get { return (byte)((data0 & (UInt32)0x00000001) >> 0); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000001) | (( (UInt32)(value) & 0x00000001) << 0)); }
            }

            public byte AutoCLR
            {
                get { return (byte)((data0 & (UInt32)0x00000002) >> 1); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x00000002) | (( (UInt32)(value) & 0x00000001) << 1)); }
            }

            public byte RfSwENA
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

            public byte RfSwChan
            {
                get { return (byte)((data0 & (UInt32)0x0000ff00) >> 8); } 
                set { data0 = (UInt32)((data0 & ~(UInt32)0x0000ff00) | (( (UInt32)(value) & 0x000000ff) << 8)); }
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
        public struct RegXTXpins
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

        /*************** Properties for Board_ID register ********************/
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
        
        /*************** Min and Max Properties for FW_Version types *********/
        /*************** Properties for FW_Version register ******************/
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
        
        /*************** Properties for HW_Version register ******************/
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
        
        /*************** Properties for Scratchpad register ******************/
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
        
        /*************** Properties for Supported_Boards register ************/
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
        
        /*************** Properties for Configured_Boards register ***********/
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
        
        /*************** Properties for Uptime register **********************/
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
        
        /*************** Properties for Event_ConfA register *****************/
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
        
        /*************** Properties for Event register ***********************/
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
        
        /*************** Properties for ConfPower register *******************/
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
        
        /*************** Min and Max Properties for MeasureVI_V3 types *******/
        /*************** Properties for MeasureVI_V3 register ****************/
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
        
        /*************** Min and Max Properties for MeasurePower_V3 types ****/
        /*************** Properties for MeasurePower_V3 register *************/
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
        
        /*************** Properties for MeasureVI_V5 register ****************/
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
        
        /*************** Properties for MeasurePower_V5 register *************/
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
        
        /*************** Properties for MeasureVI_VBat register **************/
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
        
        /*************** Properties for MeasurePower_VBat register ***********/
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
        
        /*************** Properties for MeasureVI_VBatAlt register ***********/
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
        
        /*************** Properties for MeasurePower_VBatAlt register ********/
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
        
        /*************** Properties for I2CConfA register ********************/
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
        
        /*************** Properties for I2CConfB register ********************/
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
        
        /*************** Properties for ConfMulti register *******************/
        private bool _ConfMulti_MEnabledIsSet;
        public bool ConfMulti_MEnabledIsSet {
            get => _ConfMulti_MEnabledIsSet;
            set => _ = Set(ref _ConfMulti_MEnabledIsSet, value); 
        }
        private Enabled _ConfMulti_MEnabled;
        public Enabled ConfMulti_MEnabled {
            get => _ConfMulti_MEnabled;
            set => _ = Set(ref _ConfMulti_MEnabled, value);
        }
        
        private bool _ConfMulti_AutoCLRIsSet;
        public bool ConfMulti_AutoCLRIsSet {
            get => _ConfMulti_AutoCLRIsSet;
            set => _ = Set(ref _ConfMulti_AutoCLRIsSet, value); 
        }
        private Enabled _ConfMulti_AutoCLR;
        public Enabled ConfMulti_AutoCLR {
            get => _ConfMulti_AutoCLR;
            set => _ = Set(ref _ConfMulti_AutoCLR, value);
        }
        
        private bool _ConfMulti_RfSwENAIsSet;
        public bool ConfMulti_RfSwENAIsSet {
            get => _ConfMulti_RfSwENAIsSet;
            set => _ = Set(ref _ConfMulti_RfSwENAIsSet, value); 
        }
        private Enabled _ConfMulti_RfSwENA;
        public Enabled ConfMulti_RfSwENA {
            get => _ConfMulti_RfSwENA;
            set => _ = Set(ref _ConfMulti_RfSwENA, value);
        }
        
        private bool _ConfMulti_FanPos1IsSet;
        public bool ConfMulti_FanPos1IsSet {
            get => _ConfMulti_FanPos1IsSet;
            set => _ = Set(ref _ConfMulti_FanPos1IsSet, value); 
        }
        private Enabled _ConfMulti_FanPos1;
        public Enabled ConfMulti_FanPos1 {
            get => _ConfMulti_FanPos1;
            set => _ = Set(ref _ConfMulti_FanPos1, value);
        }
        
        private bool _ConfMulti_FanPos2IsSet;
        public bool ConfMulti_FanPos2IsSet {
            get => _ConfMulti_FanPos2IsSet;
            set => _ = Set(ref _ConfMulti_FanPos2IsSet, value); 
        }
        private Enabled _ConfMulti_FanPos2;
        public Enabled ConfMulti_FanPos2 {
            get => _ConfMulti_FanPos2;
            set => _ = Set(ref _ConfMulti_FanPos2, value);
        }
        
        private bool _ConfMulti_FanPos3IsSet;
        public bool ConfMulti_FanPos3IsSet {
            get => _ConfMulti_FanPos3IsSet;
            set => _ = Set(ref _ConfMulti_FanPos3IsSet, value); 
        }
        private Enabled _ConfMulti_FanPos3;
        public Enabled ConfMulti_FanPos3 {
            get => _ConfMulti_FanPos3;
            set => _ = Set(ref _ConfMulti_FanPos3, value);
        }
        
        private bool _ConfMulti_FanPos4IsSet;
        public bool ConfMulti_FanPos4IsSet {
            get => _ConfMulti_FanPos4IsSet;
            set => _ = Set(ref _ConfMulti_FanPos4IsSet, value); 
        }
        private Enabled _ConfMulti_FanPos4;
        public Enabled ConfMulti_FanPos4 {
            get => _ConfMulti_FanPos4;
            set => _ = Set(ref _ConfMulti_FanPos4, value);
        }
        
        private bool _ConfMulti_RfSwChanIsSet;
        public bool ConfMulti_RfSwChanIsSet {
            get => _ConfMulti_RfSwChanIsSet;
            set => _ = Set(ref _ConfMulti_RfSwChanIsSet, value); 
        }
        private byte _ConfMulti_RfSwChan;
        public byte ConfMulti_RfSwChan {
            get => _ConfMulti_RfSwChan;
            set => _ = Set(ref _ConfMulti_RfSwChan, value);
        }
        
        /*************** Properties for ConfTempSense register ***************/
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
        
        /*************** Properties for XTXpins register *********************/
        private bool _XTXpins_ENAIsSet;
        public bool XTXpins_ENAIsSet {
            get => _XTXpins_ENAIsSet;
            set => _ = Set(ref _XTXpins_ENAIsSet, value); 
        }
        private Enabled _XTXpins_ENA;
        public Enabled XTXpins_ENA {
            get => _XTXpins_ENA;
            set => _ = Set(ref _XTXpins_ENA, value);
        }
        
        private bool _XTXpins_nRSTIsSet;
        public bool XTXpins_nRSTIsSet {
            get => _XTXpins_nRSTIsSet;
            set => _ = Set(ref _XTXpins_nRSTIsSet, value); 
        }
        private Enabled _XTXpins_nRST;
        public Enabled XTXpins_nRST {
            get => _XTXpins_nRST;
            set => _ = Set(ref _XTXpins_nRST, value);
        }
        
        private bool _XTXpins_RDYIsSet;
        public bool XTXpins_RDYIsSet {
            get => _XTXpins_RDYIsSet;
            set => _ = Set(ref _XTXpins_RDYIsSet, value); 
        }
        private Enabled _XTXpins_RDY;
        public Enabled XTXpins_RDY {
            get => _XTXpins_RDY;
            set => _ = Set(ref _XTXpins_RDY, value);
        }
        
        /*************** Properties for XTXMultitester register **************/
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
        
        /*************** Properties for XDCConfig register *******************/
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
        
        /*************** Properties for CSBoard_T0 register ******************/
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
        
        /*************** Properties for CSBoard_T1 register ******************/
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
        
        /*************** Properties for CSBoard_T2 register ******************/
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
        
        /*************** Properties for CSBoard_T3 register ******************/
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
        
        /*************** Properties for CSBoard_T4 register ******************/
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
        
        /*************** Properties for CSBoard_T5 register ******************/
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
        
        /*************** Properties for CSBoard_T6 register ******************/
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
        
        /*************** Properties for CSBoard_T7 register ******************/
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
        
        /*************** Properties for CSBoard_Current0I0 register **********/
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
        
        /*************** Properties for CSBoard_Current0I1 register **********/
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
        
        /*************** Properties for CSBoard_Current0I2 register **********/
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
        
        /*************** Properties for CSBoard_Current1I0 register **********/
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
        
        /*************** Properties for CSBoard_Current1I1 register **********/
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
        
        /*************** Properties for CSBoard_Current1I2 register **********/
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
        
        /*************** Properties for CSBoard_Current2I0 register **********/
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
        
        /*************** Properties for CSBoard_Current2I1 register **********/
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
        
        /*************** Properties for CSBoard_Current2I2 register **********/
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
        
        /*************** Properties for CSBoard_Current3I0 register **********/
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
        
        /*************** Properties for CSBoard_Current3I1 register **********/
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
        
        /*************** Properties for CSBoard_Current3I2 register **********/
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
        
        /*************** Properties for CSBoard_Current4I0 register **********/
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
        
        /*************** Properties for CSBoard_Current4I1 register **********/
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
        
        /*************** Properties for CSBoard_Current4I2 register **********/
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
        
        /*************** Properties for CSBoard_Current5I0 register **********/
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
        
        /*************** Properties for CSBoard_Current5I1 register **********/
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
        
        /*************** Properties for CSBoard_Current5I2 register **********/
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
        
        /*************** Properties for CSBoard_Current6I0 register **********/
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
        
        /*************** Properties for CSBoard_Current6I1 register **********/
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
        
        /*************** Properties for CSBoard_Current6I2 register **********/
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
        
        /*************** Properties for CSBoard_Current7I0 register **********/
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
        
        /*************** Properties for CSBoard_Current7I1 register **********/
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
        
        /*************** Properties for CSBoard_Current7I2 register **********/
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
        
        /*************** Holding Buffers for storageregs *********************/

        public void DecodeFrom(RegisterData register, OBCRegisterAddress address)
        {
            switch (address)
            {
                case OBCRegisterAddress.OBC_REG_BOARD_ID:
                    Board_ID_ccIdentifier =  register.RegBoard_ID.ccIdentifier;
                    Board_ID_id0 =  register.RegBoard_ID.id0;
                    Board_ID_id1 =  register.RegBoard_ID.id1;
                    Board_ID_id2 =  register.RegBoard_ID.id2;
                    break;

                case OBCRegisterAddress.OBC_REG_FW_VERSION:
                    FW_Version_major_version =  register.RegVersion.major_version;
                    FW_Version_minor_version =  register.RegVersion.minor_version;
                    FW_Version_patch_version =  register.RegVersion.patch_version;
                    break;

                case OBCRegisterAddress.OBC_REG_HW_VERSION:
                    HW_Version_major_version =  register.RegVersion.major_version;
                    HW_Version_minor_version =  register.RegVersion.minor_version;
                    HW_Version_patch_version =  register.RegVersion.patch_version;
                    break;

                case OBCRegisterAddress.OBC_REG_SCRATCHPAD:
                    Scratchpad =  register.RegScratchpad.value;
                    break;

                case OBCRegisterAddress.OBC_REG_SUPPORTED_BOARDS:
                    Supported_Boards =  register.RegSupported_Boards.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CONFIGURED_BOARDS:
                    Configured_Boards = (BoardIdentifier) register.RegConfigured_Boards.value;
                    break;

                case OBCRegisterAddress.OBC_REG_UPTIME:
                    Uptime =  register.RegUptime.value;
                    break;

                case OBCRegisterAddress.OBC_REG_EVENT_CONFA:
                    Event_ConfA_count =  register.RegEvent_ConfA.count;
                    break;

                case OBCRegisterAddress.OBC_REG_EVENT:
                    Event_section =  register.RegEvent.section;
                    Event_detail =  register.RegEvent.detail;
                    Event_timestamp =  register.RegEvent.timestamp;
                    break;

                case OBCRegisterAddress.OBC_REG_CONFPOWER:
                    ConfPower_voltage5Toggle = (Enabled) register.RegConfPower.voltage5Toggle;
                    ConfPower_voltage3Toggle = (Enabled) register.RegConfPower.voltage3Toggle;
                    ConfPower_voltageVBatToggle = (Enabled) register.RegConfPower.voltageVBatToggle;
                    ConfPower_voltageVBatAltToggle = (Enabled) register.RegConfPower.voltageVBatAltToggle;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_V3:
                    MeasureVI_V3_voltage =  register.RegMeasureVI.voltage;
                    MeasureVI_V3_current =  register.RegMeasureVI.current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_V3:
                    MeasurePower_V3_power =  register.RegMeasurePower.power;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_V5:
                    MeasureVI_V5_voltage =  register.RegMeasureVI.voltage;
                    MeasureVI_V5_current =  register.RegMeasureVI.current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_V5:
                    MeasurePower_V5_power =  register.RegMeasurePower.power;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_VBAT:
                    MeasureVI_VBat_voltage =  register.RegMeasureVI.voltage;
                    MeasureVI_VBat_current =  register.RegMeasureVI.current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_VBAT:
                    MeasurePower_VBat_power =  register.RegMeasurePower.power;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREVI_VBATALT:
                    MeasureVI_VBatAlt_voltage =  register.RegMeasureVI.voltage;
                    MeasureVI_VBatAlt_current =  register.RegMeasureVI.current;
                    break;

                case OBCRegisterAddress.OBC_REG_MEASUREPOWER_VBATALT:
                    MeasurePower_VBatAlt_power =  register.RegMeasurePower.power;
                    break;

                case OBCRegisterAddress.OBC_REG_I2CCONFA:
                    I2CConfA_TRDEL =  register.RegI2CConfA.TRDEL;
                    I2CConfA_WRDEL =  register.RegI2CConfA.WRDEL;
                    I2CConfA_SPD =  register.RegI2CConfA.SPD;
                    break;

                case OBCRegisterAddress.OBC_REG_I2CCONFB:
                    I2CConfB_ADDR =  register.RegI2CConfB.ADDR;
                    break;

                case OBCRegisterAddress.OBC_REG_CONFMULTI:
                    ConfMulti_MEnabled = (Enabled) register.RegConfMulti.MEnabled;
                    ConfMulti_AutoCLR = (Enabled) register.RegConfMulti.AutoCLR;
                    ConfMulti_RfSwENA = (Enabled) register.RegConfMulti.RfSwENA;
                    ConfMulti_FanPos1 = (Enabled) register.RegConfMulti.FanPos1;
                    ConfMulti_FanPos2 = (Enabled) register.RegConfMulti.FanPos2;
                    ConfMulti_FanPos3 = (Enabled) register.RegConfMulti.FanPos3;
                    ConfMulti_FanPos4 = (Enabled) register.RegConfMulti.FanPos4;
                    ConfMulti_RfSwChan =  register.RegConfMulti.RfSwChan;
                    break;

                case OBCRegisterAddress.OBC_REG_CONFTEMPSENSE:
                    ConfTempSense_EnableMeasurements = (Enabled) register.RegConfTempSense.EnableMeasurements;
                    break;

                case OBCRegisterAddress.OBC_REG_XTXPINS:
                    XTXpins_ENA = (Enabled) register.RegXTXpins.ENA;
                    XTXpins_nRST = (Enabled) register.RegXTXpins.nRST;
                    XTXpins_RDY = (Enabled) register.RegXTXpins.RDY;
                    break;

                case OBCRegisterAddress.OBC_REG_XTXMULTITESTER:
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

                case OBCRegisterAddress.OBC_REG_XDCCONFIG:
                    XDCConfig_ADDR = (Enabled) register.RegXDCConfig.ADDR;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T0:
                    CSBoard_T0 =  register.RegCSBoard_T0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T1:
                    CSBoard_T1 =  register.RegCSBoard_T1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T2:
                    CSBoard_T2 =  register.RegCSBoard_T2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T3:
                    CSBoard_T3 =  register.RegCSBoard_T3.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T4:
                    CSBoard_T4 =  register.RegCSBoard_T4.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T5:
                    CSBoard_T5 =  register.RegCSBoard_T5.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T6:
                    CSBoard_T6 =  register.RegCSBoard_T6.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_T7:
                    CSBoard_T7 =  register.RegCSBoard_T7.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT0I0:
                    CSBoard_Current0I0 =  register.RegCSBoard_Current0I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT0I1:
                    CSBoard_Current0I1 =  register.RegCSBoard_Current0I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT0I2:
                    CSBoard_Current0I2 =  register.RegCSBoard_Current0I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT1I0:
                    CSBoard_Current1I0 =  register.RegCSBoard_Current1I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT1I1:
                    CSBoard_Current1I1 =  register.RegCSBoard_Current1I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT1I2:
                    CSBoard_Current1I2 =  register.RegCSBoard_Current1I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT2I0:
                    CSBoard_Current2I0 =  register.RegCSBoard_Current2I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT2I1:
                    CSBoard_Current2I1 =  register.RegCSBoard_Current2I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT2I2:
                    CSBoard_Current2I2 =  register.RegCSBoard_Current2I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT3I0:
                    CSBoard_Current3I0 =  register.RegCSBoard_Current3I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT3I1:
                    CSBoard_Current3I1 =  register.RegCSBoard_Current3I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT3I2:
                    CSBoard_Current3I2 =  register.RegCSBoard_Current3I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT4I0:
                    CSBoard_Current4I0 =  register.RegCSBoard_Current4I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT4I1:
                    CSBoard_Current4I1 =  register.RegCSBoard_Current4I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT4I2:
                    CSBoard_Current4I2 =  register.RegCSBoard_Current4I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT5I0:
                    CSBoard_Current5I0 =  register.RegCSBoard_Current5I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT5I1:
                    CSBoard_Current5I1 =  register.RegCSBoard_Current5I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT5I2:
                    CSBoard_Current5I2 =  register.RegCSBoard_Current5I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT6I0:
                    CSBoard_Current6I0 =  register.RegCSBoard_Current6I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT6I1:
                    CSBoard_Current6I1 =  register.RegCSBoard_Current6I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT6I2:
                    CSBoard_Current6I2 =  register.RegCSBoard_Current6I2.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT7I0:
                    CSBoard_Current7I0 =  register.RegCSBoard_Current7I0.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT7I1:
                    CSBoard_Current7I1 =  register.RegCSBoard_Current7I1.value;
                    break;

                case OBCRegisterAddress.OBC_REG_CSBOARD_CURRENT7I2:
                    CSBoard_Current7I2 =  register.RegCSBoard_Current7I2.value;
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

                case OBCRegisterAddress.OBC_REG_CONFMULTI:
                    register.RegConfMulti.MEnabled = (byte) ConfMulti_MEnabled;
                    register.RegConfMulti.AutoCLR = (byte) ConfMulti_AutoCLR;
                    register.RegConfMulti.RfSwENA = (byte) ConfMulti_RfSwENA;
                    register.RegConfMulti.FanPos1 = (byte) ConfMulti_FanPos1;
                    register.RegConfMulti.FanPos2 = (byte) ConfMulti_FanPos2;
                    register.RegConfMulti.FanPos3 = (byte) ConfMulti_FanPos3;
                    register.RegConfMulti.FanPos4 = (byte) ConfMulti_FanPos4;
                    register.RegConfMulti.RfSwChan = ConfMulti_RfSwChan;
                    break;

                case OBCRegisterAddress.OBC_REG_CONFTEMPSENSE:
                    register.RegConfTempSense.EnableMeasurements = (byte) ConfTempSense_EnableMeasurements;
                    break;

                case OBCRegisterAddress.OBC_REG_XTXPINS:
                    register.RegXTXpins.ENA = (byte) XTXpins_ENA;
                    register.RegXTXpins.nRST = (byte) XTXpins_nRST;
                    register.RegXTXpins.RDY = (byte) XTXpins_RDY;
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

            }
        }

        public static byte[] GetRequiredStorageLocations(OBCRegisterAddress address)
        {
            // If this register does not have storage locations, only update it's address   
            return new byte[]{(byte) address };
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

            ConfMulti_MEnabled = 0;
            ConfMulti_MEnabledIsSet = false;
            ConfMulti_AutoCLR = 0;
            ConfMulti_AutoCLRIsSet = false;
            ConfMulti_RfSwENA = 0;
            ConfMulti_RfSwENAIsSet = false;
            ConfMulti_FanPos1 = 0;
            ConfMulti_FanPos1IsSet = false;
            ConfMulti_FanPos2 = 0;
            ConfMulti_FanPos2IsSet = false;
            ConfMulti_FanPos3 = 0;
            ConfMulti_FanPos3IsSet = false;
            ConfMulti_FanPos4 = 0;
            ConfMulti_FanPos4IsSet = false;
            ConfMulti_RfSwChan = 0;
            ConfMulti_RfSwChanIsSet = false;

            ConfTempSense_EnableMeasurements = 0;
            ConfTempSense_EnableMeasurementsIsSet = false;

            XTXpins_ENA = 0;
            XTXpins_ENAIsSet = false;
            XTXpins_nRST = 0;
            XTXpins_nRSTIsSet = false;
            XTXpins_RDY = 0;
            XTXpins_RDYIsSet = false;

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

        }

        public void DeserializeReg(OBCRegisterStorageLocations location, byte data)
        {
            if (!storageLocationLookup.ContainsKey(location))
            {
                RegisterData reg = Stream.Deserialize<OBC.RegisterData>(new byte[] { data });
                DecodeFrom(reg, (OBCRegisterAddress)location);
                return;
            }

            int index = storageLocationLookup[location].Item1;
            OBCRegisterAddress address = storageLocationLookup[location].Item2;
            
            // Take the byte we received, 
            switch (address)
            {
            }
        }

        public byte SerializeTo(OBCRegisterStorageLocations location)
        {
            int index = 0;
            OBCRegisterAddress address;
            if (!storageLocationLookup.ContainsKey(location))
            {
                index = 0;
                address = (OBCRegisterAddress) location;
            }
            else
            {
                index = storageLocationLookup[location].Item1;
                address = storageLocationLookup[location].Item2;
            }
            
            RegisterData reg = new RegisterData();
            EncodeTo(ref reg, address);
            
            byte[] data = Stream.Serialize<OBC.RegisterData>(reg);
            return data[index];
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
            if (e.PropertyName.Contains("IsSet"))
            {
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
