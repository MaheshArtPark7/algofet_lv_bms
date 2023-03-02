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


TS_FETcotrol_s AFE_FETcontrol;
TS_AFEdata_s AFE_data;
TS_AFEinfo_s AFE_info;

int16_t afe_data_read(void)
{
  uint16_t data=0;
  uint8_t CellVoltageHolder = Cell1Voltage;
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK == bq76952_get_device_number(&data))
      AFE_data.device_number = data;
    if(SYS_OK == bq76952_dir_cmd_read(StackVoltage, &data, 2))
      AFE_data.stack_vol = data;
    if(SYS_OK == bq76952_dir_cmd_read(PACKPinVoltage, &data, 2))
      AFE_data.pack_vol = data;
    if(SYS_OK == bq76952_dir_cmd_read(CC2Current, &data, 2))
      AFE_data.pack_curr = data;
    if(SYS_OK == bq76952_dir_cmd_read(TS1Temperature, &data, 2))
      AFE_data.temps[0] = data;
    if(SYS_OK == bq76952_dir_cmd_read(TS3Temperature, &data, 2))
      AFE_data.temps[1] = data;
    for(uint8_t i=0;i<10;i++)
    {
      do
      {
        if(SYS_OK == bq76952_dir_cmd_read(CellVoltageHolder, &data, 2))
        {
          AFE_data.cellvoltages[i] = data;
          CellVoltageHolder+=2;
        }
      }while(false);
    }

    AFE_info.Device_Number = AFE_data.device_number;
    AFE_info.Stack_Voltage = 0.01*(AFE_data.stack_vol);                     //Returns Stack Voltage in Volts (V)
    AFE_info.Pack_Voltage = 0.01*(AFE_data.pack_vol);                       //Returns Pack Voltage in Volts (V)
    AFE_info.Pack_Current = (AFE_data.pack_curr);                      //Returns Pack Current in Amperes (A)
    AFE_info.Temperatures[0] = (0.1*(AFE_data.temps[0]))-273.15;     //Returns TS1 in  Degree Celcius (C)
    AFE_info.Temperatures[1] = (0.1*(AFE_data.temps[1]))-273.15;     //Returns TS1 in Degree Celcius (C)
    for(uint8_t i=0;i<10;i++)
    {
      AFE_info.CellVoltages[i] = 0.001*(AFE_data.cellvoltages[i]);          //Returns Cell Voltages in Volts (V)
    }
    ret_val = SYS_OK;
  }while(false);

  return ret_val;
}

int16_t app_afe_init(void)
{
	int16_t ret_val = SYS_ERR;
	do
	{
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
