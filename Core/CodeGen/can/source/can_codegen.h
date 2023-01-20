#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// DBC file version
#define VER_CAN_CODEGEN_MAJ (0U)
#define VER_CAN_CODEGEN_MIN (0U)

// include current dbc-driver compilation config
#include "can_codegen-config.h"

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS
// This file must define:
// base monitor struct
// function signature for HASH calculation: (@GetFrameHash)
// function signature for getting system tick value: (@GetSystemTick)
#include "canmonitorutil.h"

#endif // CAN_CODEGEN_USE_DIAG_MONITORS


// def @FCU_STATE_REQUEST CAN Message (257  0x101)
#define FCU_STATE_REQUEST_IDE (0U)
#define FCU_STATE_REQUEST_DLC (1U)
#define FCU_STATE_REQUEST_CANID (0x101)

typedef struct
{
#ifdef CAN_CODEGEN_USE_BITS_SIGNAL

  // Pack State
  // 
  uint8_t FCU_StateRequest : 3;              //      Bits= 3

#else

  // Pack State
  // 
  uint8_t FCU_StateRequest;                  //      Bits= 3

#endif // CAN_CODEGEN_USE_BITS_SIGNAL

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // CAN_CODEGEN_USE_DIAG_MONITORS

} FCU_STATE_REQUEST_t;

// def @BAT_BMS_OvrVIEW CAN Message (2094608 0x1ff610)
#define BAT_BMS_OvrVIEW_IDE (1U)
#define BAT_BMS_OvrVIEW_DLC (2U)
#define BAT_BMS_OvrVIEW_CANID (0x1ff610)

typedef struct
{
#ifdef CAN_CODEGEN_USE_BITS_SIGNAL

  // BMS State Control Source
  // 
  // 
  // 
  uint8_t BAT_bms_StateReqSrc;               //      Bits= 8

  // Pack State
  // 
  uint8_t BAT_bms_PackState;                 //      Bits= 8

#else

  // BMS State Control Source
  // 
  // 
  // 
  uint8_t BAT_bms_StateReqSrc;               //      Bits= 8

  // Pack State
  // 
  uint8_t BAT_bms_PackState;                 //      Bits= 8

#endif // CAN_CODEGEN_USE_BITS_SIGNAL

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // CAN_CODEGEN_USE_DIAG_MONITORS

} BAT_BMS_OvrVIEW_t;

// def @BAT_BMS_ExtTemp CAN Message (2094609 0x1ff611)
#define BAT_BMS_ExtTemp_IDE (1U)
#define BAT_BMS_ExtTemp_DLC (4U)
#define BAT_BMS_ExtTemp_CANID (0x1ff611)

typedef struct
{
#ifdef CAN_CODEGEN_USE_BITS_SIGNAL

  // External Temperature Sensor 1
  // 
  uint16_t BAT_bms_ext_temp1;                //      Bits=16 Unit:'*C'

  // External Temperature Sensor 2
  uint16_t BAT_bms_ext_temp2;                //      Bits=16 Unit:'*C'

#else

  // External Temperature Sensor 1
  // 
  uint16_t BAT_bms_ext_temp1;                //      Bits=16 Unit:'*C'

  // External Temperature Sensor 2
  uint16_t BAT_bms_ext_temp2;                //      Bits=16 Unit:'*C'

#endif // CAN_CODEGEN_USE_BITS_SIGNAL

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // CAN_CODEGEN_USE_DIAG_MONITORS

} BAT_BMS_ExtTemp_t;

// This is a message for not used signals, created by Vector CANdb++ DBC OLE DB Provider.
// def @BAT_AFE_vBRICK_A CAN Message (2094864 0x1ff710)
#define BAT_AFE_vBRICK_A_IDE (1U)
#define BAT_AFE_vBRICK_A_DLC (8U)
#define BAT_AFE_vBRICK_A_CANID (0x1ff710)

typedef struct
{
#ifdef CAN_CODEGEN_USE_BITS_SIGNAL

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick01;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick02;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick03;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick04;                 //      Bits=16 Unit:'Volts'

#else

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick01;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick02;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick03;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick04;                 //      Bits=16 Unit:'Volts'

#endif // CAN_CODEGEN_USE_BITS_SIGNAL

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // CAN_CODEGEN_USE_DIAG_MONITORS

} BAT_AFE_vBRICK_A_t;

// def @BAT_AFE_vBRICK_B CAN Message (2094865 0x1ff711)
#define BAT_AFE_vBRICK_B_IDE (1U)
#define BAT_AFE_vBRICK_B_DLC (8U)
#define BAT_AFE_vBRICK_B_CANID (0x1ff711)

typedef struct
{
#ifdef CAN_CODEGEN_USE_BITS_SIGNAL

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick05;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick06;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick07;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick08;                 //      Bits=16 Unit:'Volts'

#else

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick05;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick06;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick07;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick08;                 //      Bits=16 Unit:'Volts'

#endif // CAN_CODEGEN_USE_BITS_SIGNAL

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // CAN_CODEGEN_USE_DIAG_MONITORS

} BAT_AFE_vBRICK_B_t;

// def @BAT_AFE_vBRICK_C CAN Message (2094866 0x1ff712)
#define BAT_AFE_vBRICK_C_IDE (1U)
#define BAT_AFE_vBRICK_C_DLC (8U)
#define BAT_AFE_vBRICK_C_CANID (0x1ff712)

typedef struct
{
#ifdef CAN_CODEGEN_USE_BITS_SIGNAL

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick09;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick10;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick11;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick12;                 //      Bits=16 Unit:'Volts'

#else

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick09;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick10;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick11;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick12;                 //      Bits=16 Unit:'Volts'

#endif // CAN_CODEGEN_USE_BITS_SIGNAL

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // CAN_CODEGEN_USE_DIAG_MONITORS

} BAT_AFE_vBRICK_C_t;

// def @BAT_AFE_vBRICK_D CAN Message (2094867 0x1ff713)
#define BAT_AFE_vBRICK_D_IDE (1U)
#define BAT_AFE_vBRICK_D_DLC (4U)
#define BAT_AFE_vBRICK_D_CANID (0x1ff713)

typedef struct
{
#ifdef CAN_CODEGEN_USE_BITS_SIGNAL

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick13;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick14;                 //      Bits=16 Unit:'Volts'

#else

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick13;                 //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  uint16_t BAT_afe_vBrick14;                 //      Bits=16 Unit:'Volts'

#endif // CAN_CODEGEN_USE_BITS_SIGNAL

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // CAN_CODEGEN_USE_DIAG_MONITORS

} BAT_AFE_vBRICK_D_t;

// def @BAT_GAUGE_OvrVIEW CAN Message (2095120 0x1ff810)
#define BAT_GAUGE_OvrVIEW_IDE (1U)
#define BAT_GAUGE_OvrVIEW_DLC (4U)
#define BAT_GAUGE_OvrVIEW_CANID (0x1ff810)

typedef struct
{
#ifdef CAN_CODEGEN_USE_BITS_SIGNAL

  // Voltage of brick 1
  uint8_t BAT_gauge_SoC;                     //      Bits= 8 Unit:'%'

  // Voltage of brick 1
  uint8_t BAT_gauge_SoH;                     //      Bits= 8 Unit:'%'

  // Voltage of brick 1
  uint16_t BAT_gauge_cycleCount;             //      Bits=16 Unit:'Cycles'

#else

  // Voltage of brick 1
  uint8_t BAT_gauge_SoC;                     //      Bits= 8 Unit:'%'

  // Voltage of brick 1
  uint8_t BAT_gauge_SoH;                     //      Bits= 8 Unit:'%'

  // Voltage of brick 1
  uint16_t BAT_gauge_cycleCount;             //      Bits=16 Unit:'Cycles'

#endif // CAN_CODEGEN_USE_BITS_SIGNAL

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // CAN_CODEGEN_USE_DIAG_MONITORS

} BAT_GAUGE_OvrVIEW_t;

// def @BAT_GAUGE_ViT CAN Message (2095136 0x1ff820)
#define BAT_GAUGE_ViT_IDE (1U)
#define BAT_GAUGE_ViT_DLC (6U)
#define BAT_GAUGE_ViT_CANID (0x1ff820)

typedef struct
{
#ifdef CAN_CODEGEN_USE_BITS_SIGNAL

  // Voltage of brick 1
  uint16_t BAT_gauge_vPack;                  //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  int16_t BAT_gauge_iPack;                   //  [-] Bits=16 Unit:'A'

  // Voltage of brick 1
  uint16_t BAT_gauge_tPack;                  //      Bits=16 Unit:'*C'

#else

  // Voltage of brick 1
  uint16_t BAT_gauge_vPack;                  //      Bits=16 Unit:'Volts'

  // Voltage of brick 1
  int16_t BAT_gauge_iPack;                   //  [-] Bits=16 Unit:'A'

  // Voltage of brick 1
  uint16_t BAT_gauge_tPack;                  //      Bits=16 Unit:'*C'

#endif // CAN_CODEGEN_USE_BITS_SIGNAL

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // CAN_CODEGEN_USE_DIAG_MONITORS

} BAT_GAUGE_ViT_t;

// Function signatures

uint32_t Unpack_FCU_STATE_REQUEST_can_codegen(FCU_STATE_REQUEST_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef CAN_CODEGEN_USE_CANSTRUCT
uint32_t Pack_FCU_STATE_REQUEST_can_codegen(FCU_STATE_REQUEST_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_FCU_STATE_REQUEST_can_codegen(FCU_STATE_REQUEST_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_BMS_OvrVIEW_can_codegen(BAT_BMS_OvrVIEW_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef CAN_CODEGEN_USE_CANSTRUCT
uint32_t Pack_BAT_BMS_OvrVIEW_can_codegen(BAT_BMS_OvrVIEW_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BAT_BMS_OvrVIEW_can_codegen(BAT_BMS_OvrVIEW_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_BMS_ExtTemp_can_codegen(BAT_BMS_ExtTemp_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef CAN_CODEGEN_USE_CANSTRUCT
uint32_t Pack_BAT_BMS_ExtTemp_can_codegen(BAT_BMS_ExtTemp_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BAT_BMS_ExtTemp_can_codegen(BAT_BMS_ExtTemp_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_AFE_vBRICK_A_can_codegen(BAT_AFE_vBRICK_A_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef CAN_CODEGEN_USE_CANSTRUCT
uint32_t Pack_BAT_AFE_vBRICK_A_can_codegen(BAT_AFE_vBRICK_A_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BAT_AFE_vBRICK_A_can_codegen(BAT_AFE_vBRICK_A_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_AFE_vBRICK_B_can_codegen(BAT_AFE_vBRICK_B_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef CAN_CODEGEN_USE_CANSTRUCT
uint32_t Pack_BAT_AFE_vBRICK_B_can_codegen(BAT_AFE_vBRICK_B_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BAT_AFE_vBRICK_B_can_codegen(BAT_AFE_vBRICK_B_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_AFE_vBRICK_C_can_codegen(BAT_AFE_vBRICK_C_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef CAN_CODEGEN_USE_CANSTRUCT
uint32_t Pack_BAT_AFE_vBRICK_C_can_codegen(BAT_AFE_vBRICK_C_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BAT_AFE_vBRICK_C_can_codegen(BAT_AFE_vBRICK_C_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_AFE_vBRICK_D_can_codegen(BAT_AFE_vBRICK_D_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef CAN_CODEGEN_USE_CANSTRUCT
uint32_t Pack_BAT_AFE_vBRICK_D_can_codegen(BAT_AFE_vBRICK_D_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BAT_AFE_vBRICK_D_can_codegen(BAT_AFE_vBRICK_D_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_GAUGE_OvrVIEW_can_codegen(BAT_GAUGE_OvrVIEW_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef CAN_CODEGEN_USE_CANSTRUCT
uint32_t Pack_BAT_GAUGE_OvrVIEW_can_codegen(BAT_GAUGE_OvrVIEW_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BAT_GAUGE_OvrVIEW_can_codegen(BAT_GAUGE_OvrVIEW_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_GAUGE_ViT_can_codegen(BAT_GAUGE_ViT_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef CAN_CODEGEN_USE_CANSTRUCT
uint32_t Pack_BAT_GAUGE_ViT_can_codegen(BAT_GAUGE_ViT_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BAT_GAUGE_ViT_can_codegen(BAT_GAUGE_ViT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // CAN_CODEGEN_USE_CANSTRUCT

#ifdef __cplusplus
}
#endif
