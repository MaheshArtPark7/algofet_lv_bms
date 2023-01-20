#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dbccodeconf.h"

#include "can_codegen.h"

// This version definition comes from main driver version and
// can be compared in user code space for strict compatibility test
#define VER_CAN_CODEGEN_MAJ (0U)
#define VER_CAN_CODEGEN_MIN (0U)

typedef struct
{
  FCU_STATE_REQUEST_t FCU_STATE_REQUEST;
  BAT_BMS_OvrVIEW_t BAT_BMS_OvrVIEW;
  BAT_BMS_ExtTemp_t BAT_BMS_ExtTemp;
  BAT_AFE_vBRICK_A_t BAT_AFE_vBRICK_A;
  BAT_AFE_vBRICK_B_t BAT_AFE_vBRICK_B;
  BAT_AFE_vBRICK_C_t BAT_AFE_vBRICK_C;
  BAT_AFE_vBRICK_D_t BAT_AFE_vBRICK_D;
  BAT_GAUGE_OvrVIEW_t BAT_GAUGE_OvrVIEW;
  BAT_GAUGE_ViT_t BAT_GAUGE_ViT;
} can_codegen_rx_t;

// There is no any TX mapped massage.

uint32_t can_codegen_Receive(can_codegen_rx_t* m, const uint8_t* d, uint32_t msgid, uint8_t dlc);

#ifdef __DEF_CAN_CODEGEN__

extern can_codegen_rx_t can_codegen_rx;

#endif // __DEF_CAN_CODEGEN__

#ifdef __cplusplus
}
#endif
