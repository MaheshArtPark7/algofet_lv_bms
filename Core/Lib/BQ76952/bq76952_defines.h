/*
 * bq76952_defines.h
 *
 *  Created on: 24-Aug-2022
 */

#ifndef __BQ76952_DEFINES_H_
#define __BQ76952_DEFINES_H_

#include "stdint.h"
#include "stdbool.h"

//------------------------------------------------------------------------------
// SPI Commands
#define SPI_RD_DMA 0
#define SPI_WR_DMA 1
#define SPI_RD_BLOCKING 2
#define SPI_WR_BLOCKING 3
#define SPI_WR_TIMEOUT_MS 10
#define SPI_SUB_CMD_FRAME_LEN 3
#define SPI_DIR_CMD_FRAME_LEN 3
#define READ_DIR_CMD_BUFF_LEN 2


#define SUB_CMD_REG_LSB_ADDR (uint8_t)0x3Eu       // 0x3E + R/W bit(1: write)
#define SUB_CMD_REG_MSB_ADDR (uint8_t)0x3Fu       // 0x3F + R/W bit(1: write)
#define SUB_CMD_DATA_BUFF_ADDR (uint8_t)0x40u     // 0x40 + R/W bit(0: read)
#define SUB_CMD_WR_CHKSUM_LSB_ADDR (uint8_t)0xC0u // 0x60 + R/W bit(1: write)
#define SUB_CMD_Wr_CHKSUM_MSB_ADDR (uint8_t)0xC1u // 0x61 + R/W bit(1: write)

#define SUB_CMD_DATA_BUFF_LEN_MAX 32 // 32 Bytes

//------------------------------------------------------------------------------
// Direct Commands
#define ControlStatus 0x00
#define SafetyAlertA 0x02
#define SafetyStatusA 0x03
#define SafetyAlertB 0x04
#define SafetyStatusB 0x05
#define SafetyAlertC 0x06
#define SafetyStatusC 0x07
#define PFAlertA 0x0A
#define PFStatusA 0x0B
#define PFAlertB 0x0C
#define PFStatusB 0x0D
#define PFAlertC 0x0E
#define PFStatusC 0x0F
#define PFAlertD 0x10
#define PFStatusD 0x11
#define BatteryStatus 0x12
#define Cell1Voltage 0x14
#define Cell2Voltage 0x16
#define Cell3Voltage 0x18
#define Cell4Voltage 0x1A
#define Cell5Voltage 0x1C
#define Cell6Voltage 0x1E
#define Cell7Voltage 0x20
#define Cell8Voltage 0x22
#define Cell9Voltage 0x24
#define Cell10Voltage 0x26
#define Cell11Voltage 0x28
#define Cell12Voltage 0x2A
#define Cell13Voltage 0x2C
#define Cell14Voltage 0x2E
#define Cell15Voltage 0x30
#define Cell16Voltage 0x32
#define StackVoltage 0x34
#define PACKPinVoltage 0x36
#define LDPinVoltage 0x38
#define CC2Current 0x3A
#define AlarmStatus 0x62
#define AlarmRawStatus 0x64
#define AlarmEnable 0x66
#define IntTemperature 0x68
#define CFETOFFTemperature 0x6A
#define DFETOFFTemperature 0x6C
#define ALERTTemperature 0x6E
#define TS1Temperature 0x70
#define TS2Temperature 0x72
#define TS3Temperature 0x74
#define HDQTemperature 0x76
#define DCHGTemperature 0x78
#define DDSGTemperature 0x7A
#define FETStatus 0x7F

//------------------------------------------------------------------------------
// Command-Only Subcommands
#define SUB_CMD_LEN 0x02
#define EXIT_DEEPSLEEP 0x000E
#define DEEPSLEEP 0x000F
#define SHUTDOWN 0x0010
#define RESET 0x0012
#define PDSGTEST 0x001C
#define FUSE_TOGGLE 0x001D
#define PCHGTEST 0x001E
#define CHGTEST 0x001F
#define DSGTEST 0x0020
#define FET_ENABLE 0x0022
#define PF_ENABLE 0x0024
#define PF_RESET 0x0029
#define SEAL 0x0030
#define RESET_PASSQ 0x0082
#define PTO_RECOVER 0x008A
#define SET_CFGUPDATE 0x0090
#define EXIT_CFGUPDATE 0x0092
#define DSG_PDSG_OFF 0x0093
#define CHG_PCHG_OFF 0x0094
#define ALL_FETS_OFF 0x0095
#define ALL_FETS_ON 0x0096
#define SLEEP_ENABLE 0x0099
#define SLEEP_DISABLE 0x009A
#define OCDL_RECOVER 0x009B
#define SCDL_RECOVER 0x009C
#define LOAD_DETECT_RESTART 0x009D
#define LOAD_DETECT_ON 0x009E
#define LOAD_DETECT_OFF 0x009F
#define CFETOFF_LO 0x2800
#define DFETOFF_LO 0x2801
#define ALERT_LO 0x2802
#define HDQ_LO 0x2806
#define DCHG_LO 0x2807
#define DDSG_LO 0x2808
#define CFETOFF_HI 0x2810
#define DFETOFF_HI 0x2811
#define ALERT_HI 0x2812
#define HDQ_HI 0x2816
#define DCHG_HI 0x2817
#define DDSG_HI 0x2818
#define PF_FORCE_A 0x2857
#define PF_FORCE_B 0x29A3
#define SWAP_COMM_MODE 0x29BC
#define SWAP_TO_I2C 0x29E7
#define SWAP_TO_SPI 0x7C35
#define SWAP_TO_HDQ 0x7C40

//------------------------------------------------------------------------------
// Subcommands with Data
#define DEVICE_NUMBER 0x0001
#define FW_VERSION 0x0002
#define HW_VERSION 0x0003
#define IROM_SIG 0x0004
#define STATIC_CFG_SIG 0x0005
#define PREV_MACWRITE 0x0007
#define DROM_SIG 0x0009
#define SECURITY_KEYS 0x0035
#define SAVED_PF_STATUS 0x0053
#define MANUFACTURINGSTATUS 0x0057
#define MANU_DATA 0x0070
#define DASTATUS1 0x0071
#define DASTATUS2 0x0072
#define DASTATUS3 0x0073
#define DASTATUS4 0x0074
#define DASTATUS5 0x0075
#define DASTATUS6 0x0076
#define DASTATUS7 0x0077
#define CUV_SNAPSHOT 0x0080
#define COV_SNAPSHOT 0x0081
#define CB_ACTIVE_CELLS 0x0083
#define CB_SET_LVL 0x0084
#define CBSTATUS1 0x0085
#define CBSTATUS2 0x0086
#define CBSTATUS3 0x0087
#define FET_CONTROL 0x0097
#define REG12_CONTROL 0x0098
#define OTP_WR_CHECK 0x00A0
#define OTP_WRITE 0x00A1
#define READ_CAL1 0xF081
#define CAL_CUV 0xF090
#define CAL_COV 0xF091

//------------------------------------------------------------------------------
// Data Memory
#define Cell1Gain 0x9180                    // Cal:Voltage:Cell 1 Gain
#define Cell2Gain 0x9182                    // Cal:Voltage:Cell 2 Gain
#define Cell3Gain 0x9184                    // Cal:Voltage:Cell 3 Gain
#define Cell4Gain 0x9186                    // Cal:Voltage:Cell 4 Gain
#define Cell5Gain 0x9188                    // Cal:Voltage:Cell 5 Gain
#define Cell6Gain 0x918A                    // Cal:Voltage:Cell 6 Gain
#define Cell7Gain 0x918C                    // Cal:Voltage:Cell 7 Gain
#define Cell8Gain 0x918E                    // Cal:Voltage:Cell 8 Gain
#define Cell9Gain 0x9190                    // Cal:Voltage:Cell 9 Gain
#define Cell10Gain 0x9192                   // Cal:Voltage:Cell 10 Gain
#define Cell11Gain 0x9194                   // Cal:Voltage:Cell 11 Gain
#define Cell12Gain 0x9196                   // Cal:Voltage:Cell 12 Gain
#define Cell13Gain 0x9198                   // Cal:Voltage:Cell 13 Gain
#define Cell14Gain 0x919A                   // Cal:Voltage:Cell 14 Gain
#define Cell15Gain 0x919C                   // Cal:Voltage:Cell 15 Gain
#define Cell16Gain 0x919E                   // Cal:Voltage:Cell 16 Gain
#define PackGain 0x91A0                     // Cal:Voltage:Pack Gain
#define TOSGain 0x91                        // Cal:Voltage:TOS Gain
#define LDGain 0x91A4                       // Cal:Voltage:LD Gain
#define ADCGain 0x91A6                      // Cal:Voltage:ADC Gain
#define CCGain 0x91A8                       // Cal:Current:CC Gain
#define CapacityGain 0x91AC                 // Cal:Current:Capacity Gain
#define VcellOffset 0x91B0                  // Cal:Vcell Offset:Vcell Offset
#define VdivOffset 0x91B2                   // Cal:V Divider Offset:Vdiv Offset
#define CoulombCounterOffsetSamples 0x91C6  // Cal:Current Offset:Coulomb Counter Offset Samples
#define BoardOffset 0x91C8                  // Cal:Current Offset:Board Offset
#define InternalTempOffset 0x91CA           // Cal:Temperature:Internal Temp Offset
#define CFETOFFTempOffset 0x91CB            // Cal:Temperature:CFETOFF Temp Offset
#define DFETOFFTempOffset 0x91CC            // Cal:Temperature:DFETOFF Temp Offset
#define ALERTTempOffset 0x91CD              // Cal:Temperature:ALERT Temp Offset
#define TS1TempOffset 0x91CE                // Cal:Temperature:TS1 Temp Offset
#define TS2TempOffset 0x91CF                // Cal:Temperature:TS2 Temp Offset
#define TS3TempOffset 0x91D0                // Cal:Temperature:TS3 Temp Offset
#define HDQTempOffset 0x91D1                // Cal:Temperature:HDQ Temp Offset
#define DCHGTempOffset 0x91D2               // Cal:Temperature:DCHG Temp Offset
#define DDSGTempOffset 0x91D3               // Cal:Temperature:DDSG Temp Offset
#define IntGain 0x91E2                      // Cal:Internal Temp Model:Int Gain
#define Intbaseoffset 0x91E4                // Cal:Internal Temp Model:Int base offset
#define IntMaximumAD 0x91E6                 // Cal:Internal Temp Model:Int Maximum AD
#define IntMaximumTemp 0x91E8               // Cal:Internal Temp Model:Int Maximum Temp
#define T18kCoeffa1 0x91EA                  // Cal:18K Temperature Model:Coeff a1
#define T18kCoeffa2 0x91EC                  // Cal:18K Temperature Model:Coeff a2
#define T18kCoeffa3 0x91EE                  // Cal:18K Temperature Model:Coeff a3
#define T18kCoeffa4 0x91F0                  // Cal:18K Temperature Model:Coeff a4
#define T18kCoeffa5 0x91F2                  // Cal:18K Temperature Model:Coeff a5
#define T18kCoeffb1 0x91F4                  // Cal:18K Temperature Model:Coeff b1
#define T18kCoeffb2 0x91F6                  // Cal:18K Temperature Model:Coeff b2
#define T18kCoeffb3 0x91F8                  // Cal:18K Temperature Model:Coeff b3
#define T18kCoeffb4 0x91FA                  // Cal:18K Temperature Model:Coeff b4
#define T18kAdc0 0x91FE                     // Cal:18K Temperature Model:Adc0
#define T180kCoeffa1 0x9200                 // Cal:180K Temperature Model:Coeff a1
#define T180kCoeffa2 0x9202                 // Cal:180K Temperature Model:Coeff a2
#define T180kCoeffa3 0x9204                 // Cal:180K Temperature Model:Coeff a3
#define T180kCoeffa4 0x9206                 // Cal:180K Temperature Model:Coeff a4
#define T180kCoeffa5 0x9208                 // Cal:180K Temperature Model:Coeff a5
#define T180kCoeffb1 0x920A                 // Cal:180K Temperature Model:Coeff b1
#define T180kCoeffb2 0x920C                 // Cal:180K Temperature Model:Coeff b2
#define T180kCoeffb3 0x920E                 // Cal:180K Temperature Model:Coeff b3
#define T180kCoeffb4 0x9210                 // Cal:180K Temperature Model:Coeff b4
#define T180kAdc0 0x9214                    // Cal:180K Temperature Model:Adc0
#define CustomCoeffa1 0x9216                // Cal:Custom Temperature Model:Coeff a1
#define CustomCoeffa2 0x9218                // Cal:Custom Temperature Model:Coeff a2
#define CustomCoeffa3 0x921A                // Cal:Custom Temperature Model:Coeff a3
#define CustomCoeffa4 0x921C                // Cal:Custom Temperature Model:Coeff a4
#define CustomCoeffa5 0x921E                // Cal:Custom Temperature Model:Coeff a5
#define CustomCoeffb1 0x9220                // Cal:Custom Temperature Model:Coeff b1
#define CustomCoeffb2 0x9222                // Cal:Custom Temperature Model:Coeff b2
#define CustomCoeffb3 0x9224                // Cal:Custom Temperature Model:Coeff b3
#define CustomCoeffb4 0x9226                // Cal:Custom Temperature Model:Coeff b4
#define CustomRc0 0x9228                    // Cal:Custom Temperature Model:Rc0
#define CustomAdc0 0x922A                   // Cal:Custom Temperature Model:Adc0
#define CoulombCounterDeadband 0x922D       // Cal:Current Deadband:Coulomb Counter Deadband
#define CUVThresholdOverride 0x91D4         // Cal:CUV:CUV Threshold Override
#define COVThresholdOverride 0x91D6         // Cal:COV:COV Threshold Override
#define MinBlowFuseVoltage 0x9231           // Settings:Fuse:Min Blow Fuse Voltage
#define FuseBlowTimeout 0x9233              // Settings:Fuse:Fuse Blow Timeout
#define PowerConfig 0x9234                  // Settings:Configuration:Power Config
#define REG12Config 0x9236                  // Settings:Configuration:REG12 Config
#define REG0Config 0x9237                   // Settings:Configuration:REG0 Config
#define HWDRegulatorOptions 0x9238          // Settings:Configuration:HWD Regulator Options
#define CommType 0x9239                     // Settings:Configuration:Comm Type
#define I2CAddress 0x923A                   // Settings:Configuration:I2C Address
#define SPIConfiguration 0x923C             // Settings:Configuration:SPI Configuration
#define CommIdleTime 0x923D                 // Settings:Configuration:Comm Idle Time
#define CFETOFFPinConfig 0x92FA             // Settings:Configuration:CFETOFF Pin Config
#define DFETOFFPinConfig 0x92FB             // Settings:Configuration:DFETOFF Pin Config
#define ALERTPinConfig 0x92FC               // Settings:Configuration:ALERT Pin Config
#define TS1Config 0x92FD                    // Settings:Configuration:TS1 Config
#define TS2Config 0x92FE                    // Settings:Configuration:TS2 Config
#define TS3Config 0x92FF                    // Settings:Configuration:TS3 Config
#define HDQPinConfig 0x9300                 // Settings:Configuration:HDQ Pin Config
#define DCHGPinConfig 0x9301                // Settings:Configuration:DCHG Pin Config
#define DDSGPinConfig 0x9302                // Settings:Configuration:DDSG Pin Config
#define DAConfiguration 0x9303              // Settings:Configuration:DA Configuration
#define VCellMode 0x9304                    // Settings:Configuration:Vcell Mode
#define CC3Samples 0x9307                   // Settings:Configuration:CC3 Samples
#define ProtectionConfiguration 0x925F      // Settings:Protection:Protection Configuration
#define EnabledProtectionsA 0x9261          // Settings:Protection:Enabled Protections A
#define EnabledProtectionsB 0x9262          // Settings:Protection:Enabled Protections B
#define EnabledProtectionsC 0x9263          // Settings:Protection:Enabled Protections C
#define CHGFETProtectionsA 0x9265           // Settings:Protection:CHG FET Protections A
#define CHGFETProtectionsB 0x9266           // Settings:Protection:CHG FET Protections B
#define CHGFETProtectionsC 0x9267           // Settings:Protection:CHG FET Protections C
#define DSGFETProtectionsA 0x9269           // Settings:Protection:DSG FET Protections A
#define DSGFETProtectionsB 0x926A           // Settings:Protection:DSG FET Protections B
#define DSGFETProtectionsC 0x926B           // Settings:Protection:DSG FET Protections C
#define BodyDiodeThreshold 0x9273           // Settings:Protection:Body Diode Threshold
#define DefaultAlarmMask 0x926D             // Settings:Alarm:Default Alarm Mask
#define SFAlertMaskA 0x926F                 // Settings:Alarm:SF Alert Mask A
#define SFAlertMaskB 0x9270                 // Settings:Alarm:SF Alert Mask B
#define SFAlertMaskC 0x9271                 // Settings:Alarm:SF Alert Mask C
#define PFAlertMaskA 0x92C4                 // Settings:Alarm:PF Alert Mask A
#define PFAlertMaskB 0x92C5                 // Settings:Alarm:PF Alert Mask B
#define PFAlertMaskC 0x92C6                 // Settings:Alarm:PF Alert Mask C
#define PFAlertMaskD 0x92C7                 // Settings:Alarm:PF Alert Mask D
#define EnabledPFA 0x92C0                   // Settings:Permanent Failure:Enabled PF A
#define EnabledPFB 0x92C1                   // Settings:Permanent Failure:Enabled PF B
#define EnabledPFC 0x92C2                   // Settings:Permanent Failure:Enabled PF C
#define EnabledPFD 0x92C3                   // Settings:Permanent Failure:Enabled PF D
#define FETOptions 0x9308                   // Settings:FET:FET Options
#define ChgPumpControl 0x9309               // Settings:FET:Chg Pump Control
#define PrechargeStartVoltage 0x930A        // Settings:FET:Precharge Start Voltage
#define PrechargeStopVoltage 0x930C         // Settings:FET:Precharge Stop Voltage
#define PredischargeTimeout 0x930E          // Settings:FET:Predischarge Timeout
#define PredischargeStopDelta 0x930F        // Settings:FET:Predischarge Stop Delta
#define DsgCurrentThreshold 0x9310          // Settings:Current Thresholds:Dsg Current Threshold
#define ChgCurrentThreshold 0x9312          // Settings:Current Thresholds:Chg Current Threshold
#define CheckTime 0x9314                    // Settings:Cell Open-Wire:Check Time
#define Cell1Interconnect 0x9315            // Settings:Interconnect Resistances:Cell 1 Interconnect
#define Cell2Interconnect 0x9317            // Settings:Interconnect Resistances:Cell 2 Interconnect
#define Cell3Interconnect 0x9319            // Settings:Interconnect Resistances:Cell 3 Interconnect
#define Cell4Interconnect 0x931B            // Settings:Interconnect Resistances:Cell 4 Interconnect
#define Cell5Interconnect 0x931D            // Settings:Interconnect Resistances:Cell 5 Interconnect
#define Cell6Interconnect 0x931F            // Settings:Interconnect Resistances:Cell 6 Interconnect
#define Cell7Interconnect 0x9321            // Settings:Interconnect Resistances:Cell 7 Interconnect
#define Cell8Interconnect 0x9323            // Settings:Interconnect Resistances:Cell 8 Interconnect
#define Cell9Interconnect 0x9325            // Settings:Interconnect Resistances:Cell 9 Interconnect
#define Cell10Interconnect 0x9327           // Settings:Interconnect Resistances:Cell 10 Interconnect
#define Cell11Interconnect 0x9329           // Settings:Interconnect Resistances:Cell 11 Interconnect
#define Cell12Interconnect 0x932B           // Settings:Interconnect Resistances:Cell 12 Interconnect
#define Cell13Interconnect 0x932D           // Settings:Interconnect Resistances:Cell 13 Interconnect
#define Cell14Interconnect 0x932F           // Settings:Interconnect Resistances:Cell 14 Interconnect
#define Cell15Interconnect 0x9331           // Settings:Interconnect Resistances:Cell 15 Interconnect
#define Cell16Interconnect 0x9333           // Settings:Interconnect Resistances:Cell 16 Interconnect
#define MfgStatusInit 0x9343                // Settings:Manufacturing:Mfg Status Init
#define BalancingConfiguration 0x9335       // Settings:Cell Balancing Config:Balancing Configuration
#define MinCellTemp 0x9336                  // Settings:Cell Balancing Config:Min Cell Temp
#define MaxCellTemp 0x9337                  // Settings:Cell Balancing Config:Max Cell Temp
#define MaxInternalTemp 0x9338              // Settings:Cell Balancing Config:Max Internal Temp
#define CellBalanceInterval 0x9339          // Settings:Cell Balancing Config:Cell Balance Interval
#define CellBalanceMaxCells 0x933A          // Settings:Cell Balancing Config:Cell Balance Max Cells
#define CellBalanceMinCellVCharge 0x933B    // Settings:Cell Balancing Config:Cell Balance Min Cell V (Charge)
#define CellBalanceMinDeltaCharge 0x933D    // Settings:Cell Balancing Config:Cell Balance Min Delta (Charge)
#define CellBalanceStopDeltaCharge 0x933E   // Settings:Cell Balancing Config:Cell Balance Stop Delta (Charge)
#define CellBalanceMinCellVRelax 0x933F     // Settings:Cell Balancing Config:Cell Balance Min Cell V (Relax)
#define CellBalanceMinDeltaRelax 0x9341     // Settings:Cell Balancing Config:Cell Balance Min Delta (Relax)
#define CellBalanceStopDeltaRelax 0x9342    // Settings:Cell Balancing Config:Cell Balance Stop Delta (Relax)
#define ShutdownCellVoltage 0x923F          // Power:Shutdown:Shutdown Cell Voltage
#define ShutdownStackVoltage 0x9241         // Power:Shutdown:Shutdown Stack Voltage
#define LowVShutdownDelay 0x9243            // Power:Shutdown:Low V Shutdown Delay
#define ShutdownTemperature 0x9244          // Power:Shutdown:Shutdown Temperature
#define ShutdownTemperatureDelay 0x9245     // Power:Shutdown:Shutdown Temperature Delay
#define FETOffDelay 0x9252                  // Power:Shutdown:FET Off Delay
#define ShutdownCommandDelay 0x9253         // Power:Shutdown:Shutdown Command Delay
#define AutoShutdownTime 0x9254             // Power:Shutdown:Auto Shutdown Time
#define RAMFailShutdownTime 0x9255          // Power:Shutdown:RAM Fail Shutdown Time
#define SleepCurrent 0x9248                 // Power:Sleep:Sleep Current
#define VoltageTime 0x924A                  // Power:Sleep:Voltage Time
#define WakeComparatorCurrent 0x924B        // Power:Sleep:Wake Comparator Current
#define SleepHysteresisTime 0x924D          // Power:Sleep:Sleep Hysteresis Time
#define SleepChargerVoltageThreshold 0x924E // Power:Sleep:Sleep Charger Voltage Threshold
#define SleepChargerPACKTOSDelta 0x9250     // Power:Sleep:Sleep Charger PACK-TOS Delta
#define ConfigRAMSignature 0x91E0           // System Data:Integrity:Config RAM Signature
#define CUVThreshold 0x9275                 // Protections:CUV:Threshold
#define CUVDelay 0x9276                     // Protections:CUV:Delay
#define CUVRecoveryHysteresis 0x927B        // Protections:CUV:Recovery Hysteresis
#define COVThreshold 0x9278                 // Protections:COV:Threshold
#define COVDelay 0x9279                     // Protections:COV:Delay
#define COVRecoveryHysteresis 0x927C        // Protections:COV:Recovery Hysteresis
#define COVLLatchLimit 0x927D               // Protections:COVL:Latch Limit
#define COVLCounterDecDelay 0x927E          // Protections:COVL:Counter Dec Delay
#define COVLRecoveryTime 0x927F             // Protections:COVL:Recovery Time
#define OCCThreshold 0x9280                 // Protections:OCC:Threshold
#define OCCDelay 0x9281                     // Protections:OCC:Delay
#define OCCRecoveryThreshold 0x9288         // Protections:OCC:Recovery Threshold
#define OCCPACKTOSDelta 0x92B0              // Protections:OCC:PACK-TOS Delta
#define OCD1Threshold 0x9282                // Protections:OCD1:Threshold
#define OCD1Delay 0x9283                    // Protections:OCD1:Delay
#define OCD2Threshold 0x9284                // Protections:OCD2:Threshold
#define OCD2Delay 0x9285                    // Protections:OCD2:Delay
#define SCDThreshold 0x9286                 // Protections:SCD:Threshold
#define SCDDelay 0x9287                     // Protections:SCD:Delay
#define SCDRecoveryTime 0x9294              // Protections:SCD:Recovery Time
#define OCD3Threshold 0x928A                // Protections:OCD3:Threshold
#define OCD3Delay 0x928C                    // Protections:OCD3:Delay
#define OCDRecoveryThreshold 0x928D         // Protections:OCD:Recovery Threshold
#define OCDLLatchLimit 0x928F               // Protections:OCDL:Latch Limit
#define OCDLCounterDecDelay 0x9290          // Protections:OCDL:Counter Dec Delay
#define OCDLRecoveryTime 0x9291             // Protections:OCDL:Recovery Time
#define OCDLRecoveryThreshold 0x9292        // Protections:OCDL:Recovery Threshold
#define SCDLLatchLimit 0x9295               // Protections:SCDL:Latch Limit
#define SCDLCounterDecDelay 0x9296          // Protections:SCDL:Counter Dec Delay
#define SCDLRecoveryTime 0x9297             // Protections:SCDL:Recovery Time
#define SCDLRecoveryThreshold 0x9298        // Protections:SCDL:Recovery Threshold
#define OTCThreshold 0x929A                 // Protections:OTC:Threshold
#define OTCDelay 0x920B                     // Protections:OTC:Delay
#define OTCRecovery 0x929C                  // Protections:OTC:Recovery
#define OTDThreshold 0x929D                 // Protections:OTD:Threshold
#define OTDDelay 0x929E                     // Protections:OTD:Delay
#define OTDRecovery 0x929F                  // Protections:OTD:Recovery
#define OTFThreshold 0x92A0                 // Protections:OTF:Threshold
#define OTFDelay 0x92A1                     // Protections:OTF:Delay
#define OTFRecovery 0x92A2                  // Protections:OTF:Recovery
#define OTINTThreshold 0x92A3               // Protections:OTINT:Threshold
#define OTINTDelay 0x92A4                   // Protections:OTINT:Delay
#define OTINTRecovery 0x92A5                // Protections:OTINT:Recovery
#define UTCThreshold 0x92A6                 // Protections:UTC:Threshold
#define UTCDelay 0x92A7                     // Protections:UTC:Delay
#define UTCRecovery 0x92A8                  // Protections:UTC:Recovery
#define UTDThreshold 0x92A9                 // Protections:UTD:Threshold
#define UTDDelay 0x92AA                     // Protections:UTD:Delay
#define UTDRecovery 0x92AB                  // Protections:UTD:Recovery
#define UTINTThreshold 0x92AC               // Protections:UTINT:Threshold
#define UTINTDelay 0x92AD                   // Protections:UTINT:Delay
#define UTINTRecovery 0x92AE                // Protections:UTINT:Recovery
#define ProtectionsRecoveryTime 0x92AF      // Protections:Recovery:Time
#define HWDDelay 0x92B2                     // Protections:HWD:Delay
#define LoadDetectActiveTime 0x92B4         // Protections:Load Detect:Active Time
#define LoadDetectRetryDelay 0x92B5         // Protections:Load Detect:Retry Delay
#define LoadDetectTimeout 0x92B6            // Protections:Load Detect:Timeout
#define PTOChargeThreshold 0x92BA           // Protections:PTO:Charge Threshold
#define PTODelay 0x92BC                     // Protections:PTO:Delay
#define PTOReset 0x92BE                     // Protections:PTO:Reset
#define CUDEPThreshold 0x92C8               // Permanent Fail:CUDEP:Threshold
#define CUDEPDelay 0x92CA                   // Permanent Fail:CUDEP:Delay
#define SUVThreshold 0x92CB                 // Permanent Fail:SUV:Threshold
#define SUVDelay 0x92CD                     // Permanent Fail:SUV:Delay
#define SOVThreshold 0x92CE                 // Permanent Fail:SOV:Threshold
#define SOVDelay 0x92D0                     // Permanent Fail:SOV:Delay
#define TOSSThreshold 0x92D1                // Permanent Fail:TOS:Threshold
#define TOSSDelay 0x92D3                    // Permanent Fail:TOS:Delay
#define SOCCThreshold 0x92D4                // Permanent Fail:SOCC:Threshold
#define SOCCDelay 0x92D6                    // Permanent Fail:SOCC:Delay
#define SOCDThreshold 0x92D7                // Permanent Fail:SOCD:Threshold
#define SOCDDelay 0x92D9                    // Permanent Fail:SOCD:Delay
#define SOTThreshold 0x92DA                 // Permanent Fail:SOT:Threshold
#define SOTDelay 0x92DB                     // Permanent Fail:SOT:Delay
#define SOTFThreshold 0x92DC                // Permanent Fail:SOTF:Threshold
#define SOTFDelay 0x92DD                    // Permanent Fail:SOTF:Delay
#define VIMRCheckVoltage 0x92DE             // Permanent Fail:VIMR:Check Voltage
#define VIMRMaxRelaxCurrent 0x92E0          // Permanent Fail:VIMR:Max Relax Current
#define VIMRThreshold 0x92E2                // Permanent Fail:VIMR:Threshold
#define VIMRDelay 0x92E4                    // Permanent Fail:VIMR:Delay
#define VIMRRelaxMinDuration 0x92E5         // Permanent Fail:VIMR:Relax Min Duration
#define VIMACheckVoltage 0x92E7             // Permanent Fail:VIMA:Check Voltage
#define VIMAMinActiveCurrent 0x92E9         // Permanent Fail:VIMA:Min Active Current
#define VIMAThreshold 0x92EB                // Permanent Fail:VIMA:Threshold
#define VIMADelay 0x92ED                    // Permanent Fail:VIMA:Delay
#define CFETFOFFThreshold 0x92EE            // Permanent Fail:CFETF:OFF Threshold
#define CFETFOFFDelay 0x92F0                // Permanent Fail:CFETF:OFF Delay
#define DFETFOFFThreshold 0x92F1            // Permanent Fail:DFETF:OFF Threshold
#define DFETFOFFDelay 0x92F3                // Permanent Fail:DFETF:OFF Delay
#define VSSFFailThreshold 0x92F4            // Permanent Fail:VSSF:Fail Threshold
#define VSSFDelay 0x92F6                    // Permanent Fail:VSSF:Delay
#define PF2LVLDelay 0x92F7                  // Permanent Fail:2LVL:Delay
#define LFOFDelay 0x92F8                    // Permanent Fail:LFOF:Delay
#define HWMXDelay 0x92F9                    // Permanent Fail:HWMX:Delay
#define SecuritySettings 0x9256             // Security:Settings:Security Settings
#define UnsealKeyStep1 0x9257               // Security:Keys:Unseal Key Step 1
#define UnsealKeyStep2 0x9259               // Security:Keys:Unseal Key Step 2
#define FullAccessKeyStep1 0x925B           // Security:Keys:Full Access Key Step 1
#define FullAccessKeyStep2 0x925D           // Security:Keys:Full Access Key Step 2

#endif /* __BQ76952_DEFINES_H_ */
