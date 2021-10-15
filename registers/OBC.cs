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


namespace ControllerDemo.Components.Models
{
    public class OBC : INotifyPropertyChanged, IModel
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public enum OBCRegisterAddress{
            OBC_REG_BOARD_ID                         = 0x10,
            OBC_REG_FW_VERSION                       = 0x11,
            OBC_REG_HW_VERSION                       = 0x12,
            OBC_REG_SCRATCHPAD                       = 0x13,
            OBC_REG_SUPPORTED_BOARDS                 = 0x14,
            OBC_REG_CONFIGURED_BOARDS                = 0x15,
            OBC_REG_CONFPOWER                        = 0x20,
            OBC_REG_MEASUREVI_V3                     = 0x21,
            OBC_REG_MEASUREPOWER_V3                  = 0x22,
            OBC_REG_MEASUREVI_V5                     = 0x23,
            OBC_REG_MEASUREPOWER_V5                  = 0x24,
            OBC_REG_MEASUREVI_VBAT                   = 0x25,
            OBC_REG_MEASUREPOWER_VBAT                = 0x26,
            OBC_REG_MEASUREVI_VBATALT                = 0x27,
            OBC_REG_MEASUREPOWER_VBATALT             = 0x28,
            OBC_REG_I2CCONFIG                        = 0x29,
            OBC_REG_XTXPINS                          = 0x30,
            OBC_REG_XDCCONFIG                        = 0x40,
        }

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
            public RegConfPower RegConfPower;
            [FieldOffset(0)]
            public RegMeasureVI RegMeasureVI;
            [FieldOffset(0)]
            public RegMeasurePower RegMeasurePower;
            [FieldOffset(0)]
            public RegI2CConfig RegI2CConfig;
            [FieldOffset(0)]
            public RegXTXpins RegXTXpins;
            [FieldOffset(0)]
            public RegXDCConfig RegXDCConfig;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegBoard_ID
        {
            [FieldOffset(0)]
            UInt32 data;

            public byte ccIdentifier
            {
                get { return (byte)((data & (UInt32)0xff000000) >> 24); } 
                set { data = (UInt32)((data & ~(UInt32)0xff000000) | (( (UInt32)(value) & 0x000000ff) << 24)); }
            }

            public byte id0
            {
                get { return (byte)((data & (UInt32)0x00ff0000) >> 16); } 
                set { data = (UInt32)((data & ~(UInt32)0x00ff0000) | (( (UInt32)(value) & 0x000000ff) << 16)); }
            }

            public byte id1
            {
                get { return (byte)((data & (UInt32)0x0000ff00) >> 8); } 
                set { data = (UInt32)((data & ~(UInt32)0x0000ff00) | (( (UInt32)(value) & 0x000000ff) << 8)); }
            }

            public byte id2
            {
                get { return (byte)((data & (UInt32)0x000000ff) >> 0); } 
                set { data = (UInt32)((data & ~(UInt32)0x000000ff) | (( (UInt32)(value) & 0x000000ff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegVersion
        {
            [FieldOffset(0)]
            UInt32 data;

            public byte major_version
            {
                get { return (byte)((data & (UInt32)0x00ff0000) >> 16); } 
                set { data = (UInt32)((data & ~(UInt32)0x00ff0000) | (( (UInt32)(value) & 0x000000ff) << 16)); }
            }

            public byte minor_version
            {
                get { return (byte)((data & (UInt32)0x0000ff00) >> 8); } 
                set { data = (UInt32)((data & ~(UInt32)0x0000ff00) | (( (UInt32)(value) & 0x000000ff) << 8)); }
            }

            public byte patch_version
            {
                get { return (byte)((data & (UInt32)0x000000ff) >> 0); } 
                set { data = (UInt32)((data & ~(UInt32)0x000000ff) | (( (UInt32)(value) & 0x000000ff) << 0)); }
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
        public struct RegConfPower
        {
            [FieldOffset(0)]
            byte data;

            public byte voltage5Toggle
            {
                get { return (byte)((data & (byte)0x00000001) >> 0); } 
                set { data = (byte)((data & ~(byte)0x00000001) | (( (byte)(value) & 0x00000001) << 0)); }
            }

            public byte voltage3Toggle
            {
                get { return (byte)((data & (byte)0x00000002) >> 1); } 
                set { data = (byte)((data & ~(byte)0x00000002) | (( (byte)(value) & 0x00000001) << 1)); }
            }

            public byte voltageVBatToggle
            {
                get { return (byte)((data & (byte)0x00000004) >> 2); } 
                set { data = (byte)((data & ~(byte)0x00000004) | (( (byte)(value) & 0x00000001) << 2)); }
            }

            public byte voltageVBatAltToggle
            {
                get { return (byte)((data & (byte)0x00000008) >> 3); } 
                set { data = (byte)((data & ~(byte)0x00000008) | (( (byte)(value) & 0x00000001) << 3)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegMeasureVI
        {
            [FieldOffset(0)]
            UInt32 data;

            public UInt32 voltage
            {
                get { return (UInt32)((data & (UInt32)0xffff0000) >> 16); } 
                set { data = (UInt32)((data & ~(UInt32)0xffff0000) | (( (UInt32)(value) & 0x0000ffff) << 16)); }
            }

            public UInt32 current
            {
                get { return (UInt32)((data & (UInt32)0x0000ffff) >> 0); } 
                set { data = (UInt32)((data & ~(UInt32)0x0000ffff) | (( (UInt32)(value) & 0x0000ffff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegMeasurePower
        {
            [FieldOffset(0)]
            UInt32 data;

            public UInt32 power
            {
                get { return (UInt32)((data & (UInt32)0xffffffff) >> 0); } 
                set { data = (UInt32)((data & ~(UInt32)0xffffffff) | (( (UInt32)(value) & 0xffffffff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegI2CConfig
        {
            [FieldOffset(0)]
            UInt32 data;

            public byte CHK
            {
                get { return (byte)((data & (UInt32)0x00000100) >> 8); } 
                set { data = (UInt32)((data & ~(UInt32)0x00000100) | (( (UInt32)(value) & 0x00000001) << 8)); }
            }

            public byte SPD
            {
                get { return (byte)((data & (UInt32)0x000000ff) >> 0); } 
                set { data = (UInt32)((data & ~(UInt32)0x000000ff) | (( (UInt32)(value) & 0x000000ff) << 0)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegXTXpins
        {
            [FieldOffset(0)]
            UInt32 data;

            public byte ENA
            {
                get { return (byte)((data & (UInt32)0x00000001) >> 0); } 
                set { data = (UInt32)((data & ~(UInt32)0x00000001) | (( (UInt32)(value) & 0x00000001) << 0)); }
            }

            public byte nRST
            {
                get { return (byte)((data & (UInt32)0x00000002) >> 1); } 
                set { data = (UInt32)((data & ~(UInt32)0x00000002) | (( (UInt32)(value) & 0x00000001) << 1)); }
            }

            public byte RDY
            {
                get { return (byte)((data & (UInt32)0x00000004) >> 2); } 
                set { data = (UInt32)((data & ~(UInt32)0x00000004) | (( (UInt32)(value) & 0x00000001) << 2)); }
            }

        }

        [StructLayout(LayoutKind.Explicit, Pack = 0)]
        public struct RegXDCConfig
        {
            [FieldOffset(0)]
            UInt32 data;

            public byte ADDR
            {
                get { return (byte)((data & (UInt32)0x000000ff) >> 0); } 
                set { data = (UInt32)((data & ~(UInt32)0x000000ff) | (( (UInt32)(value) & 0x000000ff) << 0)); }
            }

        }

        public enum Enabled : byte
        {
            Enabled = 1,
            Disabled = 0,
        }

        public enum BoardIdentifier : byte
        {
            None = 0,
            XTX = 1,
            XSteer = 2,
            XDC = 4,
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
        
        /*************** Properties for I2CConfig register *******************/
        private bool _I2CConfig_CHKIsSet;
        public bool I2CConfig_CHKIsSet {
            get => _I2CConfig_CHKIsSet;
            set => _ = Set(ref _I2CConfig_CHKIsSet, value); 
        }
        private Enabled _I2CConfig_CHK;
        public Enabled I2CConfig_CHK {
            get => _I2CConfig_CHK;
            set => _ = Set(ref _I2CConfig_CHK, value);
        }
        
        private bool _I2CConfig_SPDIsSet;
        public bool I2CConfig_SPDIsSet {
            get => _I2CConfig_SPDIsSet;
            set => _ = Set(ref _I2CConfig_SPDIsSet, value); 
        }
        private byte _I2CConfig_SPD;
        public byte I2CConfig_SPD {
            get => _I2CConfig_SPD;
            set => _ = Set(ref _I2CConfig_SPD, value);
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

                case OBCRegisterAddress.OBC_REG_I2CCONFIG:
                    I2CConfig_CHK = (Enabled) register.RegI2CConfig.CHK;
                    I2CConfig_SPD =  register.RegI2CConfig.SPD;
                    break;

                case OBCRegisterAddress.OBC_REG_XTXPINS:
                    XTXpins_ENA = (Enabled) register.RegXTXpins.ENA;
                    XTXpins_nRST = (Enabled) register.RegXTXpins.nRST;
                    XTXpins_RDY = (Enabled) register.RegXTXpins.RDY;
                    break;

                case OBCRegisterAddress.OBC_REG_XDCCONFIG:
                    XDCConfig_ADDR = (Enabled) register.RegXDCConfig.ADDR;
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

                case OBCRegisterAddress.OBC_REG_I2CCONFIG:
                    register.RegI2CConfig.CHK = (byte) I2CConfig_CHK;
                    register.RegI2CConfig.SPD = I2CConfig_SPD;
                    break;

                case OBCRegisterAddress.OBC_REG_XTXPINS:
                    register.RegXTXpins.ENA = (byte) XTXpins_ENA;
                    register.RegXTXpins.nRST = (byte) XTXpins_nRST;
                    register.RegXTXpins.RDY = (byte) XTXpins_RDY;
                    break;

                case OBCRegisterAddress.OBC_REG_XDCCONFIG:
                    register.RegXDCConfig.ADDR = (byte) XDCConfig_ADDR;
                    break;

            }
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
            OnPropertyChanged(propertyname);
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
