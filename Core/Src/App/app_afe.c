/*
 * app_afe.c
 *
 *  Created on: Aug 21, 2022
 */

#include "app_afe.h"
#include "app_defines.h"
#include "bq76952.h"
#include "main.h"
#include "bq76952_defines.h"
#include "can_codegen.h"


TS_FETcotrol_s AFE_FETcontrol;
TS_AFEdata_s AFE_data;
TS_AFEinfo_s AFE_info;

FCU_STATE_REQUEST_t fcuState;
BAT_BMS_OvrVIEW_t batBmsOvr;
BAT_BMS_ExtTemp_t batBmsExtTemp;
BAT_AFE_vBRICK_A_t batAfeBrickA;
BAT_AFE_vBRICK_B_t batAfeBrickB;
BAT_AFE_vBRICK_C_t batAfeBrickC;
BAT_AFE_vBRICK_D_t batAfeBrickD;
BAT_GAUGE_OvrVIEW_t batGaugeOvr;
BAT_GAUGE_ViT_t batGaugeViT;

int16_t app_afe_data_read(void)
{
  uint8_t CellVoltageHolder = Cell1Voltage;
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK!= bq76952_get_device_number(AFE_data.device_number))
    {
      break;
    }
    if(SYS_OK != bq76952_dir_cmd_read(StackVoltage, AFE_data.stack_vol, 2))
    {
      break;
    }
    if(SYS_OK != bq76952_dir_cmd_read(PACKPinVoltage, AFE_data.pack_vol, 2))
    {
      break;
    }
    if(SYS_OK != bq76952_dir_cmd_read(CC2Current, AFE_data.pack_curr, 2))
    {
      break;
    }
    if(SYS_OK != bq76952_dir_cmd_read(TS1Temperature, AFE_data.temps[0], 2))
    {
      break;
    }
    if(SYS_OK != bq76952_dir_cmd_read(TS3Temperature, AFE_data.temps[1], 2))
    {
      break;
    }
    for(uint8_t i=0;i<10;i++)
    {
        if(SYS_OK == bq76952_dir_cmd_read(CellVoltageHolder, AFE_data.cellvoltages[i], 2))
          CellVoltageHolder+=2;
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}

int16_t app_afe_can_message_update(void)
{
	batGaugeViT.BAT_gauge_vPack = AFE_data.pack_vol;
	batGaugeViT.BAT_gauge_iPack = AFE_data.pack_curr;
	batGaugeViT.BAT_gauge_tPack = AFE_data.temps[0];
	batAfeBrickA.BAT_afe_vBrick01 = AFE_data.cellvoltages[0];
	batAfeBrickA.BAT_afe_vBrick02 = AFE_data.cellvoltages[1];
	batAfeBrickA.BAT_afe_vBrick03 = AFE_data.cellvoltages[2];
	batAfeBrickA.BAT_afe_vBrick04 = AFE_data.cellvoltages[3];
	batAfeBrickB.BAT_afe_vBrick05 = AFE_data.cellvoltages[4];
	batAfeBrickB.BAT_afe_vBrick06 = AFE_data.cellvoltages[5];
	batAfeBrickB.BAT_afe_vBrick07 = AFE_data.cellvoltages[6];
	batAfeBrickB.BAT_afe_vBrick08 = AFE_data.cellvoltages[7];
	batAfeBrickC.BAT_afe_vBrick09 = AFE_data.cellvoltages[8];
	batAfeBrickC.BAT_afe_vBrick10 = AFE_data.cellvoltages[9];
}

int16_t app_afe_init(void)
{
	int16_t ret_val = SYS_ERR;
	do
	{
		HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);
	  bq76952_init();
		ret_val = SYS_OK;
	}while(false);

	return ret_val;
}

int16_t app_afe_tick(void)
{
	int16_t ret_val = SYS_ERR;
	while(true)
	{

	}
	return ret_val;
}
