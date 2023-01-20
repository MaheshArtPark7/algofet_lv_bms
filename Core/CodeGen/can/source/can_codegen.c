#include "can_codegen.h"


#ifdef CAN_CODEGEN_USE_DIAG_MONITORS
// Function prototypes to be called each time CAN frame is unpacked
// FMon function may detect RC, CRC or DLC violation
#include "can_codegen-fmon.h"

#endif // CAN_CODEGEN_USE_DIAG_MONITORS


uint32_t Unpack_FCU_STATE_REQUEST_can_codegen(FCU_STATE_REQUEST_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->FCU_StateRequest = (_d[0] & (0x07U));

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < FCU_STATE_REQUEST_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_FCU_STATE_REQUEST_can_codegen(&_m->mon1, FCU_STATE_REQUEST_CANID);
#endif // CAN_CODEGEN_USE_DIAG_MONITORS

  return FCU_STATE_REQUEST_CANID;
}

#ifdef CAN_CODEGEN_USE_CANSTRUCT

uint32_t Pack_FCU_STATE_REQUEST_can_codegen(FCU_STATE_REQUEST_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < FCU_STATE_REQUEST_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->FCU_StateRequest & (0x07U));

  cframe->MsgId = FCU_STATE_REQUEST_CANID;
  cframe->DLC = FCU_STATE_REQUEST_DLC;
  cframe->IDE = FCU_STATE_REQUEST_IDE;
  return FCU_STATE_REQUEST_CANID;
}

#else

uint32_t Pack_FCU_STATE_REQUEST_can_codegen(FCU_STATE_REQUEST_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < FCU_STATE_REQUEST_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->FCU_StateRequest & (0x07U));

  *_len = FCU_STATE_REQUEST_DLC;
  *_ide = FCU_STATE_REQUEST_IDE;
  return FCU_STATE_REQUEST_CANID;
}

#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_BMS_OvrVIEW_can_codegen(BAT_BMS_OvrVIEW_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BAT_bms_StateReqSrc = (_d[0] & (0xFFU));
  _m->BAT_bms_PackState = (_d[1] & (0xFFU));

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BAT_BMS_OvrVIEW_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BAT_BMS_OvrVIEW_can_codegen(&_m->mon1, BAT_BMS_OvrVIEW_CANID);
#endif // CAN_CODEGEN_USE_DIAG_MONITORS

  return BAT_BMS_OvrVIEW_CANID;
}

#ifdef CAN_CODEGEN_USE_CANSTRUCT

uint32_t Pack_BAT_BMS_OvrVIEW_can_codegen(BAT_BMS_OvrVIEW_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BAT_BMS_OvrVIEW_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BAT_bms_StateReqSrc & (0xFFU));
  cframe->Data[1] |= (_m->BAT_bms_PackState & (0xFFU));

  cframe->MsgId = BAT_BMS_OvrVIEW_CANID;
  cframe->DLC = BAT_BMS_OvrVIEW_DLC;
  cframe->IDE = BAT_BMS_OvrVIEW_IDE;
  return BAT_BMS_OvrVIEW_CANID;
}

#else

uint32_t Pack_BAT_BMS_OvrVIEW_can_codegen(BAT_BMS_OvrVIEW_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BAT_BMS_OvrVIEW_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BAT_bms_StateReqSrc & (0xFFU));
  _d[1] |= (_m->BAT_bms_PackState & (0xFFU));

  *_len = BAT_BMS_OvrVIEW_DLC;
  *_ide = BAT_BMS_OvrVIEW_IDE;
  return BAT_BMS_OvrVIEW_CANID;
}

#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_BMS_ExtTemp_can_codegen(BAT_BMS_ExtTemp_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BAT_bms_ext_temp1 = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->BAT_bms_ext_temp2 = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BAT_BMS_ExtTemp_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BAT_BMS_ExtTemp_can_codegen(&_m->mon1, BAT_BMS_ExtTemp_CANID);
#endif // CAN_CODEGEN_USE_DIAG_MONITORS

  return BAT_BMS_ExtTemp_CANID;
}

#ifdef CAN_CODEGEN_USE_CANSTRUCT

uint32_t Pack_BAT_BMS_ExtTemp_can_codegen(BAT_BMS_ExtTemp_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BAT_BMS_ExtTemp_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BAT_bms_ext_temp1 & (0xFFU));
  cframe->Data[1] |= ((_m->BAT_bms_ext_temp1 >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->BAT_bms_ext_temp2 & (0xFFU));
  cframe->Data[3] |= ((_m->BAT_bms_ext_temp2 >> 8) & (0xFFU));

  cframe->MsgId = BAT_BMS_ExtTemp_CANID;
  cframe->DLC = BAT_BMS_ExtTemp_DLC;
  cframe->IDE = BAT_BMS_ExtTemp_IDE;
  return BAT_BMS_ExtTemp_CANID;
}

#else

uint32_t Pack_BAT_BMS_ExtTemp_can_codegen(BAT_BMS_ExtTemp_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BAT_BMS_ExtTemp_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BAT_bms_ext_temp1 & (0xFFU));
  _d[1] |= ((_m->BAT_bms_ext_temp1 >> 8) & (0xFFU));
  _d[2] |= (_m->BAT_bms_ext_temp2 & (0xFFU));
  _d[3] |= ((_m->BAT_bms_ext_temp2 >> 8) & (0xFFU));

  *_len = BAT_BMS_ExtTemp_DLC;
  *_ide = BAT_BMS_ExtTemp_IDE;
  return BAT_BMS_ExtTemp_CANID;
}

#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_AFE_vBRICK_A_can_codegen(BAT_AFE_vBRICK_A_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BAT_afe_vBrick01 = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->BAT_afe_vBrick02 = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->BAT_afe_vBrick03 = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
  _m->BAT_afe_vBrick04 = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BAT_AFE_vBRICK_A_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BAT_AFE_vBRICK_A_can_codegen(&_m->mon1, BAT_AFE_vBRICK_A_CANID);
#endif // CAN_CODEGEN_USE_DIAG_MONITORS

  return BAT_AFE_vBRICK_A_CANID;
}

#ifdef CAN_CODEGEN_USE_CANSTRUCT

uint32_t Pack_BAT_AFE_vBRICK_A_can_codegen(BAT_AFE_vBRICK_A_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BAT_AFE_vBRICK_A_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BAT_afe_vBrick01 & (0xFFU));
  cframe->Data[1] |= ((_m->BAT_afe_vBrick01 >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->BAT_afe_vBrick02 & (0xFFU));
  cframe->Data[3] |= ((_m->BAT_afe_vBrick02 >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->BAT_afe_vBrick03 & (0xFFU));
  cframe->Data[5] |= ((_m->BAT_afe_vBrick03 >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->BAT_afe_vBrick04 & (0xFFU));
  cframe->Data[7] |= ((_m->BAT_afe_vBrick04 >> 8) & (0xFFU));

  cframe->MsgId = BAT_AFE_vBRICK_A_CANID;
  cframe->DLC = BAT_AFE_vBRICK_A_DLC;
  cframe->IDE = BAT_AFE_vBRICK_A_IDE;
  return BAT_AFE_vBRICK_A_CANID;
}

#else

uint32_t Pack_BAT_AFE_vBRICK_A_can_codegen(BAT_AFE_vBRICK_A_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BAT_AFE_vBRICK_A_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BAT_afe_vBrick01 & (0xFFU));
  _d[1] |= ((_m->BAT_afe_vBrick01 >> 8) & (0xFFU));
  _d[2] |= (_m->BAT_afe_vBrick02 & (0xFFU));
  _d[3] |= ((_m->BAT_afe_vBrick02 >> 8) & (0xFFU));
  _d[4] |= (_m->BAT_afe_vBrick03 & (0xFFU));
  _d[5] |= ((_m->BAT_afe_vBrick03 >> 8) & (0xFFU));
  _d[6] |= (_m->BAT_afe_vBrick04 & (0xFFU));
  _d[7] |= ((_m->BAT_afe_vBrick04 >> 8) & (0xFFU));

  *_len = BAT_AFE_vBRICK_A_DLC;
  *_ide = BAT_AFE_vBRICK_A_IDE;
  return BAT_AFE_vBRICK_A_CANID;
}

#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_AFE_vBRICK_B_can_codegen(BAT_AFE_vBRICK_B_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BAT_afe_vBrick05 = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->BAT_afe_vBrick06 = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->BAT_afe_vBrick07 = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
  _m->BAT_afe_vBrick08 = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BAT_AFE_vBRICK_B_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BAT_AFE_vBRICK_B_can_codegen(&_m->mon1, BAT_AFE_vBRICK_B_CANID);
#endif // CAN_CODEGEN_USE_DIAG_MONITORS

  return BAT_AFE_vBRICK_B_CANID;
}

#ifdef CAN_CODEGEN_USE_CANSTRUCT

uint32_t Pack_BAT_AFE_vBRICK_B_can_codegen(BAT_AFE_vBRICK_B_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BAT_AFE_vBRICK_B_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BAT_afe_vBrick05 & (0xFFU));
  cframe->Data[1] |= ((_m->BAT_afe_vBrick05 >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->BAT_afe_vBrick06 & (0xFFU));
  cframe->Data[3] |= ((_m->BAT_afe_vBrick06 >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->BAT_afe_vBrick07 & (0xFFU));
  cframe->Data[5] |= ((_m->BAT_afe_vBrick07 >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->BAT_afe_vBrick08 & (0xFFU));
  cframe->Data[7] |= ((_m->BAT_afe_vBrick08 >> 8) & (0xFFU));

  cframe->MsgId = BAT_AFE_vBRICK_B_CANID;
  cframe->DLC = BAT_AFE_vBRICK_B_DLC;
  cframe->IDE = BAT_AFE_vBRICK_B_IDE;
  return BAT_AFE_vBRICK_B_CANID;
}

#else

uint32_t Pack_BAT_AFE_vBRICK_B_can_codegen(BAT_AFE_vBRICK_B_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BAT_AFE_vBRICK_B_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BAT_afe_vBrick05 & (0xFFU));
  _d[1] |= ((_m->BAT_afe_vBrick05 >> 8) & (0xFFU));
  _d[2] |= (_m->BAT_afe_vBrick06 & (0xFFU));
  _d[3] |= ((_m->BAT_afe_vBrick06 >> 8) & (0xFFU));
  _d[4] |= (_m->BAT_afe_vBrick07 & (0xFFU));
  _d[5] |= ((_m->BAT_afe_vBrick07 >> 8) & (0xFFU));
  _d[6] |= (_m->BAT_afe_vBrick08 & (0xFFU));
  _d[7] |= ((_m->BAT_afe_vBrick08 >> 8) & (0xFFU));

  *_len = BAT_AFE_vBRICK_B_DLC;
  *_ide = BAT_AFE_vBRICK_B_IDE;
  return BAT_AFE_vBRICK_B_CANID;
}

#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_AFE_vBRICK_C_can_codegen(BAT_AFE_vBRICK_C_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BAT_afe_vBrick09 = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->BAT_afe_vBrick10 = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->BAT_afe_vBrick11 = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
  _m->BAT_afe_vBrick12 = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BAT_AFE_vBRICK_C_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BAT_AFE_vBRICK_C_can_codegen(&_m->mon1, BAT_AFE_vBRICK_C_CANID);
#endif // CAN_CODEGEN_USE_DIAG_MONITORS

  return BAT_AFE_vBRICK_C_CANID;
}

#ifdef CAN_CODEGEN_USE_CANSTRUCT

uint32_t Pack_BAT_AFE_vBRICK_C_can_codegen(BAT_AFE_vBRICK_C_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BAT_AFE_vBRICK_C_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BAT_afe_vBrick09 & (0xFFU));
  cframe->Data[1] |= ((_m->BAT_afe_vBrick09 >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->BAT_afe_vBrick10 & (0xFFU));
  cframe->Data[3] |= ((_m->BAT_afe_vBrick10 >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->BAT_afe_vBrick11 & (0xFFU));
  cframe->Data[5] |= ((_m->BAT_afe_vBrick11 >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->BAT_afe_vBrick12 & (0xFFU));
  cframe->Data[7] |= ((_m->BAT_afe_vBrick12 >> 8) & (0xFFU));

  cframe->MsgId = BAT_AFE_vBRICK_C_CANID;
  cframe->DLC = BAT_AFE_vBRICK_C_DLC;
  cframe->IDE = BAT_AFE_vBRICK_C_IDE;
  return BAT_AFE_vBRICK_C_CANID;
}

#else

uint32_t Pack_BAT_AFE_vBRICK_C_can_codegen(BAT_AFE_vBRICK_C_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BAT_AFE_vBRICK_C_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BAT_afe_vBrick09 & (0xFFU));
  _d[1] |= ((_m->BAT_afe_vBrick09 >> 8) & (0xFFU));
  _d[2] |= (_m->BAT_afe_vBrick10 & (0xFFU));
  _d[3] |= ((_m->BAT_afe_vBrick10 >> 8) & (0xFFU));
  _d[4] |= (_m->BAT_afe_vBrick11 & (0xFFU));
  _d[5] |= ((_m->BAT_afe_vBrick11 >> 8) & (0xFFU));
  _d[6] |= (_m->BAT_afe_vBrick12 & (0xFFU));
  _d[7] |= ((_m->BAT_afe_vBrick12 >> 8) & (0xFFU));

  *_len = BAT_AFE_vBRICK_C_DLC;
  *_ide = BAT_AFE_vBRICK_C_IDE;
  return BAT_AFE_vBRICK_C_CANID;
}

#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_AFE_vBRICK_D_can_codegen(BAT_AFE_vBRICK_D_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BAT_afe_vBrick13 = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->BAT_afe_vBrick14 = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BAT_AFE_vBRICK_D_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BAT_AFE_vBRICK_D_can_codegen(&_m->mon1, BAT_AFE_vBRICK_D_CANID);
#endif // CAN_CODEGEN_USE_DIAG_MONITORS

  return BAT_AFE_vBRICK_D_CANID;
}

#ifdef CAN_CODEGEN_USE_CANSTRUCT

uint32_t Pack_BAT_AFE_vBRICK_D_can_codegen(BAT_AFE_vBRICK_D_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BAT_AFE_vBRICK_D_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BAT_afe_vBrick13 & (0xFFU));
  cframe->Data[1] |= ((_m->BAT_afe_vBrick13 >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->BAT_afe_vBrick14 & (0xFFU));
  cframe->Data[3] |= ((_m->BAT_afe_vBrick14 >> 8) & (0xFFU));

  cframe->MsgId = BAT_AFE_vBRICK_D_CANID;
  cframe->DLC = BAT_AFE_vBRICK_D_DLC;
  cframe->IDE = BAT_AFE_vBRICK_D_IDE;
  return BAT_AFE_vBRICK_D_CANID;
}

#else

uint32_t Pack_BAT_AFE_vBRICK_D_can_codegen(BAT_AFE_vBRICK_D_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BAT_AFE_vBRICK_D_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BAT_afe_vBrick13 & (0xFFU));
  _d[1] |= ((_m->BAT_afe_vBrick13 >> 8) & (0xFFU));
  _d[2] |= (_m->BAT_afe_vBrick14 & (0xFFU));
  _d[3] |= ((_m->BAT_afe_vBrick14 >> 8) & (0xFFU));

  *_len = BAT_AFE_vBRICK_D_DLC;
  *_ide = BAT_AFE_vBRICK_D_IDE;
  return BAT_AFE_vBRICK_D_CANID;
}

#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_GAUGE_OvrVIEW_can_codegen(BAT_GAUGE_OvrVIEW_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BAT_gauge_SoC = (_d[0] & (0xFFU));
  _m->BAT_gauge_SoH = (_d[1] & (0xFFU));
  _m->BAT_gauge_cycleCount = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BAT_GAUGE_OvrVIEW_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BAT_GAUGE_OvrVIEW_can_codegen(&_m->mon1, BAT_GAUGE_OvrVIEW_CANID);
#endif // CAN_CODEGEN_USE_DIAG_MONITORS

  return BAT_GAUGE_OvrVIEW_CANID;
}

#ifdef CAN_CODEGEN_USE_CANSTRUCT

uint32_t Pack_BAT_GAUGE_OvrVIEW_can_codegen(BAT_GAUGE_OvrVIEW_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BAT_GAUGE_OvrVIEW_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BAT_gauge_SoC & (0xFFU));
  cframe->Data[1] |= (_m->BAT_gauge_SoH & (0xFFU));
  cframe->Data[2] |= (_m->BAT_gauge_cycleCount & (0xFFU));
  cframe->Data[3] |= ((_m->BAT_gauge_cycleCount >> 8) & (0xFFU));

  cframe->MsgId = BAT_GAUGE_OvrVIEW_CANID;
  cframe->DLC = BAT_GAUGE_OvrVIEW_DLC;
  cframe->IDE = BAT_GAUGE_OvrVIEW_IDE;
  return BAT_GAUGE_OvrVIEW_CANID;
}

#else

uint32_t Pack_BAT_GAUGE_OvrVIEW_can_codegen(BAT_GAUGE_OvrVIEW_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BAT_GAUGE_OvrVIEW_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BAT_gauge_SoC & (0xFFU));
  _d[1] |= (_m->BAT_gauge_SoH & (0xFFU));
  _d[2] |= (_m->BAT_gauge_cycleCount & (0xFFU));
  _d[3] |= ((_m->BAT_gauge_cycleCount >> 8) & (0xFFU));

  *_len = BAT_GAUGE_OvrVIEW_DLC;
  *_ide = BAT_GAUGE_OvrVIEW_IDE;
  return BAT_GAUGE_OvrVIEW_CANID;
}

#endif // CAN_CODEGEN_USE_CANSTRUCT

uint32_t Unpack_BAT_GAUGE_ViT_can_codegen(BAT_GAUGE_ViT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BAT_gauge_vPack = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->BAT_gauge_iPack = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->BAT_gauge_tPack = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));

#ifdef CAN_CODEGEN_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BAT_GAUGE_ViT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BAT_GAUGE_ViT_can_codegen(&_m->mon1, BAT_GAUGE_ViT_CANID);
#endif // CAN_CODEGEN_USE_DIAG_MONITORS

  return BAT_GAUGE_ViT_CANID;
}

#ifdef CAN_CODEGEN_USE_CANSTRUCT

uint32_t Pack_BAT_GAUGE_ViT_can_codegen(BAT_GAUGE_ViT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BAT_GAUGE_ViT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BAT_gauge_vPack & (0xFFU));
  cframe->Data[1] |= ((_m->BAT_gauge_vPack >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->BAT_gauge_iPack & (0xFFU));
  cframe->Data[3] |= ((_m->BAT_gauge_iPack >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->BAT_gauge_tPack & (0xFFU));
  cframe->Data[5] |= ((_m->BAT_gauge_tPack >> 8) & (0xFFU));

  cframe->MsgId = BAT_GAUGE_ViT_CANID;
  cframe->DLC = BAT_GAUGE_ViT_DLC;
  cframe->IDE = BAT_GAUGE_ViT_IDE;
  return BAT_GAUGE_ViT_CANID;
}

#else

uint32_t Pack_BAT_GAUGE_ViT_can_codegen(BAT_GAUGE_ViT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BAT_GAUGE_ViT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BAT_gauge_vPack & (0xFFU));
  _d[1] |= ((_m->BAT_gauge_vPack >> 8) & (0xFFU));
  _d[2] |= (_m->BAT_gauge_iPack & (0xFFU));
  _d[3] |= ((_m->BAT_gauge_iPack >> 8) & (0xFFU));
  _d[4] |= (_m->BAT_gauge_tPack & (0xFFU));
  _d[5] |= ((_m->BAT_gauge_tPack >> 8) & (0xFFU));

  *_len = BAT_GAUGE_ViT_DLC;
  *_ide = BAT_GAUGE_ViT_IDE;
  return BAT_GAUGE_ViT_CANID;
}

#endif // CAN_CODEGEN_USE_CANSTRUCT

