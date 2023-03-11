/*
 * app_user.c
 *
 */

#include "app_afe.h"
#include "app_defines.h"
#include "main.h"
#include "can_codegen.h"
#include "bq76942.h"
#include "bq76942_defines.h"
#include "app_fuel_gauge.h"

TsAppGaugeData_t App_Gaugedata;
//Static functions definitions
int16_t app_user_SOC_LED_indic (void);
int16_t app_user_BMS_state_LED_indic (void);
int16_t app_user_ERROR_LED_indic (void);



int16_t app_user_SOC_LED_indic (void) //LED Indication for State of Charge (SOC)
{
  int ret_val = SYS_ERR;
  do
  {
    if(App_Gaugedata.SoC < 15)//SOC<15%
    {
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 1);
      HAL_Delay(100);
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED2_OUT_GPIO_Port, LED2_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, 0);
    }
    else if(App_Gaugedata.SoC>=15 && App_Gaugedata.SoC<50)//15%<=SOC<50%
    {
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED2_OUT_GPIO_Port, LED2_OUT_Pin, 1);
      HAL_Delay(100);
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, 0);
    }
    else if(App_Gaugedata.SoC>=50 && App_Gaugedata.SoC<75)//50%<=SOC<=75%
    {
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED2_OUT_GPIO_Port, LED2_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, 1);
      HAL_Delay(100);
      HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, 0);
    }
    else if(App_Gaugedata.SoC>=75 && App_Gaugedata.SoC<98)//75%<=SOC<=98%
    {
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED2_OUT_GPIO_Port, LED2_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, 1);
      HAL_Delay(100);
      HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, 0);

    }
    else if(App_Gaugedata.SoC>=98 && App_Gaugedata.SoC<100)//98%<=SOC<=100%
    {
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED2_OUT_GPIO_Port, LED2_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, 1);
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}

int16_t app_user_BMS_state_LED_indic (void) //LED Indication for BMS State
{
  int16_t ret_val = SYS_ERR;
  do
  {
    if(1)//IDLE (To be updated)
    {
      HAL_GPIO_WritePin(LED5_OUT_BLUE_GPIO_Port, LED5_OUT_BLUE_Pin, 1);
      HAL_GPIO_WritePin(LED5_OUT_GREEN_GPIO_Port, LED5_OUT_GREEN_Pin, 0);
      HAL_GPIO_WritePin(LED5_OUT_GREEN_GPIO_Port, LED5_OUT_RED_Pin, 0);
    }
    else if(2)//CHARGE or DISCHARGE (To be updated)
    {
      HAL_GPIO_WritePin(LED5_OUT_BLUE_GPIO_Port, LED5_OUT_BLUE_Pin, 0);
      HAL_GPIO_WritePin(LED5_OUT_GREEN_GPIO_Port, LED5_OUT_GREEN_Pin, 1);
      HAL_GPIO_WritePin(LED5_OUT_GREEN_GPIO_Port, LED5_OUT_RED_Pin, 0);
    }
    else if(3)//ERROR (To be updated)
    {
      HAL_GPIO_WritePin(LED5_OUT_BLUE_GPIO_Port, LED5_OUT_BLUE_Pin, 0);
      HAL_GPIO_WritePin(LED5_OUT_GREEN_GPIO_Port, LED5_OUT_GREEN_Pin, 0);
      HAL_GPIO_WritePin(LED5_OUT_GREEN_GPIO_Port, LED5_OUT_RED_Pin, 1);
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}

int16_t app_user_ERROR_LED_indic (void) //LED Indication for Errors
{
  uint8_t SafetyAlertA_CUV,SafetyAlertA_COV,SafetyAlertA_OCC,SafetyAlertA_OCD1,SafetyAlertA_OCD2,SafetyAlertA_SCD,SafetyStatusA_CUV,SafetyStatusA_COV,SafetyStatusA_OCC,SafetyStatusA_OCD1,SafetyStatusA_OCD2,SafetyStatusA_SCD;
    uint8_t SafetyAlertB_OTF,SafetyAlertB_OTINT,SafetyAlertB_OTD,SafetyAlertB_OTC,SafetyAlertB_UTINT,SafetyAlertB_UTD,SafetyAlertB_UTC,SafetyStatusB_OTF,SafetyStatusB_OTINT,SafetyStatusB_OTD,SafetyStatusB_OTC,SafetyStatusB_UTINT,SafetyStatusB_UTD,SafetyStatusB_UTC;
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SafetyAlertA_COV==0 && SafetyStatusA_COV==1)  //OVERVOLTAGE ERROR
    {
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED2_OUT_GPIO_Port, LED2_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, 1);
    }
    if(SafetyAlertA_CUV==0 && SafetyStatusA_CUV==1)  //UNDERVOLTAGE ERROR
    {
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED2_OUT_GPIO_Port, LED2_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, 1);
    }
    if(SafetyAlertA_OCC==0 && SafetyStatusA_OCC==1)   //OVERCURRENT ERROR
    {
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED2_OUT_GPIO_Port, LED2_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, 0);
    }
    if(1)//HIGH TEMPERATURE ERROR (To be updated)
    {
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED2_OUT_GPIO_Port, LED2_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, 0);
    }
    if(1)//LOW TEMPERATURE ERROR (To be updated)
    {
      HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED2_OUT_GPIO_Port, LED2_OUT_Pin, 1);
      HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, 0);
      HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, 1);
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}
































