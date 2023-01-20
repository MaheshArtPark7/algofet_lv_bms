#include "can_codegen-binutil.h"

#ifdef __DEF_CAN_CODEGEN__

can_codegen_rx_t can_codegen_rx;

#endif // __DEF_CAN_CODEGEN__

uint32_t can_codegen_Receive(can_codegen_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if ((_id >= 0x101U) && (_id < 0x1FF711U)) {
  if ((_id >= 0x101U) && (_id < 0x1FF611U)) {
   if (_id == 0x101U) {
    recid = Unpack_FCU_STATE_REQUEST_can_codegen(&(_m->FCU_STATE_REQUEST), _d, dlc_);
   } else if (_id == 0x1FF610U) {
    recid = Unpack_BAT_BMS_OvrVIEW_can_codegen(&(_m->BAT_BMS_OvrVIEW), _d, dlc_);
   }
  } else {
   if (_id == 0x1FF611U) {
    recid = Unpack_BAT_BMS_ExtTemp_can_codegen(&(_m->BAT_BMS_ExtTemp), _d, dlc_);
   } else if (_id == 0x1FF710U) {
    recid = Unpack_BAT_AFE_vBRICK_A_can_codegen(&(_m->BAT_AFE_vBRICK_A), _d, dlc_);
   }
  }
 } else {
  if ((_id >= 0x1FF711U) && (_id < 0x1FF713U)) {
   if (_id == 0x1FF711U) {
    recid = Unpack_BAT_AFE_vBRICK_B_can_codegen(&(_m->BAT_AFE_vBRICK_B), _d, dlc_);
   } else if (_id == 0x1FF712U) {
    recid = Unpack_BAT_AFE_vBRICK_C_can_codegen(&(_m->BAT_AFE_vBRICK_C), _d, dlc_);
   }
  } else {
   if (_id == 0x1FF713U) {
    recid = Unpack_BAT_AFE_vBRICK_D_can_codegen(&(_m->BAT_AFE_vBRICK_D), _d, dlc_);
   } else {
    if (_id == 0x1FF810U) {
     recid = Unpack_BAT_GAUGE_OvrVIEW_can_codegen(&(_m->BAT_GAUGE_OvrVIEW), _d, dlc_);
    } else if (_id == 0x1FF820U) {
     recid = Unpack_BAT_GAUGE_ViT_can_codegen(&(_m->BAT_GAUGE_ViT), _d, dlc_);
    }
   }
  }
 }

 return recid;
}

