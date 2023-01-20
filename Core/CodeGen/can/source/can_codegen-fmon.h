#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// DBC file version
#define VER_CAN_CODEGEN_MAJ_FMON (0U)
#define VER_CAN_CODEGEN_MIN_FMON (0U)

#include "can_codegen-config.h"

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS

#include "canmonitorutil.h"
/*
This file contains the prototypes of all the functions that will be called
from each Unpack_*name* function to detect DBC related errors
It is the user responsibility to defined these functions in the
separated .c file. If it won't be done the linkage error will happen
*/

void FMon_FCU_STATE_REQUEST_can_codegen(FrameMonitor_t* _mon, uint32_t msgid);
void FMon_BAT_BMS_OvrVIEW_can_codegen(FrameMonitor_t* _mon, uint32_t msgid);
void FMon_BAT_BMS_ExtTemp_can_codegen(FrameMonitor_t* _mon, uint32_t msgid);
void FMon_BAT_AFE_vBRICK_A_can_codegen(FrameMonitor_t* _mon, uint32_t msgid);
void FMon_BAT_AFE_vBRICK_B_can_codegen(FrameMonitor_t* _mon, uint32_t msgid);
void FMon_BAT_AFE_vBRICK_C_can_codegen(FrameMonitor_t* _mon, uint32_t msgid);
void FMon_BAT_AFE_vBRICK_D_can_codegen(FrameMonitor_t* _mon, uint32_t msgid);
void FMon_BAT_GAUGE_OvrVIEW_can_codegen(FrameMonitor_t* _mon, uint32_t msgid);
void FMon_BAT_GAUGE_ViT_can_codegen(FrameMonitor_t* _mon, uint32_t msgid);

#endif // CAN_CODEGEN_USE_DIAG_MONITORS

#ifdef __cplusplus
}
#endif
