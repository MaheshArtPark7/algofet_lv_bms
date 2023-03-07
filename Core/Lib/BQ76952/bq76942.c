/*
 * bq76942.c
 *
 *  Created on: 24-Aug-2022
 */

#include <bq76942.h>
#include <bq76942_defines.h>
#include "spi.h"
#include "app_afe.h"

extern SPI_HandleTypeDef hspi1;

static TsBmsPower_cfg TsBmsPower_cfg_t;
static TS_AFEramreg_s AFE_RAMwrite;

uint16_t CB_ActiveCells;  // Cell Balancing Active Cells
uint8_t LD_ON = 0;	// Load Detect status bit
uint8_t DSG = 0;   // discharge FET state
uint8_t CHG = 0;   // charge FET state
uint8_t PCHG = 0;  // pre-charge FET state
uint8_t PDSG = 0;  // pre-discharge FET state
uint8_t DCHG = 0;  // Fault state for Charging
uint8_t DDSG = 0;  // Fault state for Discharging

//------------------------------------------------------------------------------
// Static Functions declaration
static uint8_t bq76942_CRC8(uint8_t *ptr, uint8_t len);
static uint8_t bq76942_checksum(uint8_t *ptr, uint8_t len);
extern int16_t bq76942_dir_cmd_read(uint8_t dirCmdRegAddr, uint16_t *pData, uint8_t len);
static int16_t bq76942_dir_cmd_write(uint8_t dirCmdRegAddr, uint16_t dirCmd);
static int16_t bq76942_write_RAM_register(uint16_t reg_address, uint16_t cmd, uint8_t datalen);
static int16_t bq76942_read_RAM_register (uint16_t reg_address, uint16_t *pData);
static int16_t bq76942_write_sub_cmd(uint16_t subCmdRegAddr, uint16_t subCmd);
static int16_t bq76942_read_sub_cmd_data_buffer(uint8_t subCmdRegAddr, uint16_t *pData, uint8_t len);

extern int16_t bq76942_AFE_reset(void);
static int16_t bq76942_set_powercfg(TsBmsPower_cfg *pTsBmsPower_cfg_t);
extern int16_t bq76942_get_device_number(uint16_t *pDev_num);
static int16_t bq76942_set_config_update(void);
static int16_t bq76942_config(void);
static int16_t bq76942_enter_config_update(void);
static int16_t bq76942_settings_pwr_cfg(void);
static int16_t bq76942_settings_reg0_cfg(void);
static int16_t bq76942_settings_reg12_cfg(void);

//FET Control Functions Declaration
static int16_t bq76942_FETs_SleepDisable(void);
static int16_t bq76942_FETs_enable(void);
static int16_t bq76942_allFETs_on(void);
static int16_t bq76942_allFETs_off(void);
static int16_t bq76942_dischargeOFF(void);
static int16_t bq76942_chargeOFF(void);
extern int16_t bq76942_FETs_ON(void);
extern int16_t bq76942_FETs_OFF(void);
extern int16_t bq76942_Charge(void);
extern int16_t bq76942_Discharge(void);
static int16_t bq76942_FETs_ReadStatus(void);

//Direct Commands Declaration
static int16_t bq76942_alarmEnable(uint16_t command);

//RAM Register Write Commands Declaration
extern int16_t bq76942_vCellMode (void);
extern int16_t bq76942_FETs_Control(void);
extern int16_t bq76942_enabledProtectionsA (void);
extern int16_t bq76942_enabledProtectionsB (void);
extern int16_t bq76942_prechargeStartVolt(void);
extern int16_t bq76942_prechargeStopVolt(void);
extern int16_t bq76942_TS3config(void);
//------------------------------------------------------------------------------
// Static Functions definition

int16_t bq76942_init(void)
{
  int16_t ret_val = SYS_ERR;
  do
  {
    TsBmsPower_cfg_t.power_cfg_reg = PowerConfig;
    TsBmsPower_cfg_t.reg_val = 0x2D80;
    TsBmsPower_cfg_t.len = 4;
    AFE_RAMwrite.vCellModecmd = 0x03C3;           //0x03C3 for 6S | 0x0303 for 4S
    AFE_RAMwrite.FETs_CONTROL = 0x0;
    AFE_RAMwrite.enabledProtectionsA = 0xBC;
    AFE_RAMwrite.enabledProtectionsB = 0xF7;      //(Also sets OTC, OTD and OTF as 1)
    AFE_RAMwrite.prechargeStartVoltage = 0x0A8C;  //2700mV
    AFE_RAMwrite.prechargeStopVoltage = 0x0AF0;   //2800mV
    AFE_RAMwrite.TS3config = 0x07;                //Default for TS3: 0X07 | Default for TS1: 0x07

    //bq76942_vCellMode();
    //bq76942_FETs_Control();
    //bq76942_TS3config();

        //RESET #Resets the Bq769x2 Registers
        bq76942_AFE_reset();

        // Enter config update mode
        //bq76942_set_config_update();

        // TODO: Check if CFGUPDATE bit is SET

        // Leave Reg1 and Reg2 mode in present state when entering deep-sleep state
        //bq76942_set_powercfg(&TsBmsPower_cfg_t);
        //REG0Config --> 0x01
        //DFETOFFPinConfig --> 0x42  #Set DFETOFF pin to control both CHG and DSG FET
        //TS1Config --> 0xB3  #ADC raw data reported
        //TS3Config --> 0xB3  #ADC raw data reported
        //DCHGPinConfig --> 0x25
        //DDSGPinConfig --> 0x25
        //VCellMode --> 0x03C3 for 6S | 0x0303 for 4S
        //EnabledProtectionsA --> 0xBC
        //EnabledProtectionsB --> 0xF7
        //CHGFETProtectionsA --> 0x00
        //CHGFETProtectionsB --> 0x00
        //CHGFETProtectionsC --> 0x00
        //DSGFETProtectionsA --> 0x00
        //DSGFETProtectionsB --> 0x00
        //DSGFETProtectionsC --> 0x00
        //DefaultAlarmMask --> 0xF882
        //FETOptions --> 0x3D               # AFE should wait for the host command before turning FETs On. PDSG FET is turned ON before DSG.
        //PrechargeStartVoltage --> 0x0A8C  # 2700mV
        //PrechargeStopVoltage --> 0x0AF0   # 2800mV
        //PredischargeTimeout --> 0x00      # No Timeout
        //PredischargeStopDelta --> 0x05    #500mV
        //BalancingConfiguration --> 0x03	#Autonomous balancing On in Relax and Charging mode
        //CUVThreshold --> 0x31   			#2479mV, unit is 50.6mV. Refer to TRM page 166
        //COVThreshold --> 0x55				#4310mV, unit is 50.6mV
        //OCCThreshold --> 0x05				#Rsense is 1mohm. Unit is 2mV, so 10mV means a threshold of 10A
        //OCD1Threshold --> 0x0A			#Rsense is 1mohm. Unit is 2mV, so 20mV means a threshold of 20A
        //SCDThreshold --> 0x02				#40mV across 1mohm, i.e, 40A. Refer to TRM page 168
        //SCDDelay --> 0x03					#30us. Enabled with a delay of (value - 1) * 15 us; min value of 1
        //SCDLLatchLimit --> 0x01			#Only with load removal. Refer to TRM page 170

    // Leave Reg1 and Reg2 mode in present state when entering deep-sleep state
    //bq76942_set_powercfg(&TsBmsPower_cfg_t);
    //REG0Config --> 0x01
    //DFETOFFPinConfig --> 0x42  #Set DFETOFF pin to control both CHG and DSG FET
    //TS1Config --> 0x07  #ADC raw data reported (Updated)
    //TS3Config --> 0x07  #ADC raw data reported (Updated)
    //DCHGPinConfig --> 0x25
    //DDSGPinConfig --> 0x25
    //VCellMode --> 0x03C3 for 6S | 0x0303 for 4S
    //EnabledProtectionsA --> 0xBC
    //EnabledProtectionsB --> 0xF7 (Also sets OTC, OTD and OTF as 1)
    //CHGFETProtectionsA --> 0x00
    //CHGFETProtectionsB --> 0x00
    //CHGFETProtectionsC --> 0x00
    //DSGFETProtectionsA --> 0x00
    //DSGFETProtectionsB --> 0x00
    //DSGFETProtectionsC --> 0x00
    //DefaultAlarmMask --> 0xF882
    //FETOptions --> 0x3D               # AFE should wait for the host command before turning FETs On. PDSG FET is turned ON before DSG.
    //PrechargeStartVoltage --> 0x0A8C  # 2700mV
    //PrechargeStopVoltage --> 0x0AF0   # 2800mV
    //PredischargeTimeout --> 0x00      # No Timeout
    //PredischargeStopDelta --> 0x05    #500mV
    //BalancingConfiguration --> 0x03	#Autonomous balancing On in Relax and Charging mode
    //CUVThreshold --> 0x31   			#2479mV, unit is 50.6mV. Refer to TRM page 166
    //COVThreshold --> 0x55				#4310mV, unit is 50.6mV
    //OCCThreshold --> 0x05				#Rsense is 1mohm. Unit is 2mV, so 10mV means a threshold of 10A
    //OCD1Threshold --> 0x0A			#Rsense is 1mohm. Unit is 2mV, so 20mV means a threshold of 20A
    //SCDThreshold --> 0x02				#40mV across 1mohm, i.e, 40A. Refer to TRM page 168
    //SCDDelay --> 0x03					#30us. Enabled with a delay of (value - 1) * 15 us; min value of 1
    //SCDLLatchLimit --> 0x01			#Only with load removal. Refer to TRM page 170
    ret_val = SYS_OK;
  } while(false);

  return ret_val;
}

//------------------------------------------------------------------------------
// FET CONTROL COMMANDS
static int16_t bq76942_FETs_SleepDisable(void)
{
  // Puts the FETs in performance mode
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76942_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, SLEEP_DISABLE))
    {
      break;
    }
    ret_val = SYS_OK;
  } while(false);
  return ret_val;
}
static int16_t bq76942_FETs_enable(void)
{
  // Enables all the FETs to be controlled
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76942_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, FET_ENABLE))
    {
      break;
    }
    ret_val = SYS_OK;
  } while(false);
  return ret_val;
}
static int16_t bq76942_allFETs_on(void)
{
  // Switches on all the FETs
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76942_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, ALL_FETS_ON))
    {
      break;
    }
    ret_val = SYS_OK;
  } while(false);
  return ret_val;
}
static int16_t bq76942_allFETs_off(void)
{
  // Switches off all the FETs
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76942_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, ALL_FETS_OFF))
    {
      break;
    }
    ret_val = SYS_OK;
  } while(false);
  return ret_val;
}
static int16_t bq76942_dischargeOFF(void)
{
  //Disable DSG and PDSG FET drivers
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76942_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, DSG_PDSG_OFF))
    {
      break;
    }
    ret_val = SYS_OK;
  } while(false);
  return ret_val;
}
static int16_t bq76942_chargeOFF(void)
{
  //Disable CHG and PCHG FET drivers
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76942_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, CHG_PCHG_OFF))
    {
      break;
    }
    ret_val = SYS_OK;
  } while(false);
  return ret_val;
}


extern int16_t bq76942_FETs_ON(void)
{
  //To switch on the FETs whenever required
  int8_t ret_val = SYS_OK;
  do
  {
    if(SYS_OK!= bq76942_FETs_enable())
    {
      break;
    }
    HAL_Delay(50);
    if(SYS_OK!= bq76942_FETs_SleepDisable())
    {
      break;
    }
    HAL_Delay(50);
    if(SYS_OK!= bq76942_allFETs_on())
    {
      break;
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}
extern int16_t bq76942_FETs_OFF(void)
{
  //To switch off the FETs whenever required
  int8_t ret_val = SYS_OK;
  do
  {
    if(SYS_OK!= bq76942_FETs_enable())
    {
      break;
    }
    HAL_Delay(50);
    if(SYS_OK!= bq76942_allFETs_off())
    {
      break;
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}

extern int16_t bq76942_Charge(void)
{
  //Takes the BMS to Charging mode
  uint8_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK!= bq76942_FETs_enable())
    {
      break;
    }
    if(SYS_OK!= bq76942_allFETs_on())
    {
      break;
    }
    if(SYS_OK!= bq76942_dischargeOFF())
    {
      break;
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}
extern int16_t bq76942_Discharge(void)
{
  //Takes the BMS to Discharging mode
  uint8_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK!= bq76942_FETs_enable())
    {
      break;
    }
    if(SYS_OK!= bq76942_allFETs_on())
    {
      break;
    }
    if(SYS_OK!= bq76942_chargeOFF())
    {
      break;
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}

static int16_t bq76942_FETs_ReadStatus(void)
{
  // Reads FET Status to see which FETs are enabled
  uint8_t ret_val = SYS_ERR;
  uint16_t data=0;
  do
  {
    bq76942_dir_cmd_read(FETStatus, &data, 1);
    HAL_Delay(50);
    CHG = (0x1 & data);                // charge FET state
    PCHG = ((0x2 & data) >> 1);        // pre-charge FET state
    DSG = ((0x4 & data) >> 2);         // discharge FET state
    PDSG = ((0x8 & data) >> 3);        // pre-discharge FET state
    DCHG = ((0X10 & data) >> 4);       //Fault State for Charging
    DDSG = ((0x20 & data) >> 5);       //Fault State for Discharging
    //Bit Number 7 is for Alert Pin, add later if required
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}
//------------------------------------------------------------------------------------------------------------
//AFE Functions
extern int16_t bq76942_AFE_reset(void)
{
  // Resets all the registers of the AFE
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76942_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, RESET))
    {
      break;
    }
    ret_val = SYS_OK;
  } while(false);
  return ret_val;
}

static int16_t bq76942_set_powercfg(TsBmsPower_cfg *pTsBmsPower_cfg_t)
{
    //PowerConfig --> 0x2D80   #DPSLP_LDO bit -> 1

    int16_t ret_val = SYS_ERR;
    do
    {
        //if(SYS_OK != bq76942_write_to_register(SUB_CMD_REG_LSB_ADDR, pTsBmsPower_cfg_t->buffer, pTsBmsPower_cfg_t->len))
        {
            break;
        }
    } while (false);
    ret_val = SYS_OK;
    return ret_val;
}

extern int16_t bq76942_get_device_number(uint16_t *pDev_num)
{
    int16_t ret_val = SYS_ERR;
    do
    {
      if(SYS_OK != bq76942_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, DEVICE_NUMBER))
      {
        break;
      }
    if(SYS_OK != bq76942_read_sub_cmd_data_buffer(SUB_CMD_DATA_BUFF_ADDR, pDev_num, 2))
    {
      break;
    }
    ret_val = SYS_OK;
  } while(false);
  return ret_val;
}

//----------------------------------------------DIRECT COMMANDS-------------------------------------------------------------------

static int16_t bq76942_alarmEnable(uint16_t command)
{
  //To set a value to the Alarm Enable Register
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76942_dir_cmd_write(AlarmEnable, command))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}

static int16_t bq76942_set_config_update(void)
{
    int16_t ret_val = SYS_ERR;
    do
    {
        if (SYS_OK != bq76942_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, SET_CFGUPDATE))
        {
            break;
        }
    } while (false);
    ret_val = SYS_OK;
    return ret_val;
}

static int16_t bq76942_settings_pwr_cfg(void)
{
    int16_t ret_val = SYS_ERR;
    uint16_t settings = 0x1D00;
    // Settings:Power Config
//    bq76942_sub_cmd_access((uint16_t)PowerConfig, SPI_WR_BLOCKING, sizeof(settings) + SUB_CMD_LEN, &settings);
    ret_val = SYS_OK;
    return ret_val;
}

static int16_t bq76942_settings_reg0_cfg(void)
{
    int16_t ret_val = SYS_ERR;
    uint8_t settings = 0x01;
    // Settings:REG0 Config
//    bq76942_sub_cmd_access((uint16_t)REG0Config, SPI_WR_BLOCKING, sizeof(settings) + SUB_CMD_LEN, &settings);
    ret_val = SYS_OK;
    return ret_val;
}

static int16_t bq76942_settings_reg12_cfg(void)
{
    int16_t ret_val = SYS_ERR;
    uint8_t settings = 0x0D;
    // Settings:REG12 Config
//    bq76942_sub_cmd_access((uint16_t)REG12Config, SPI_WR_BLOCKING, sizeof(settings) + SUB_CMD_LEN, &settings);
  ret_val = SYS_OK;
  return ret_val;
}

/*------------------RAM Register Commands-----------------------------*/
extern int16_t bq76942_FETs_Control(void)
{
  //To control the FETs with MCU only
  uint16_t data=0;
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76942_write_RAM_register(FET_CONTROL, AFE_RAMwrite.FETs_CONTROL, 1))
    {
      break;
    }
    if(SYS_OK != bq76942_read_RAM_register(FET_CONTROL, &data))
    {
      break;
    }
    if(data!= AFE_RAMwrite.FETs_CONTROL)
    {
      break;
    }
    ret_val = SYS_OK;
  } while(false);

  return ret_val;
}
extern int16_t bq76942_vCellMode (void)
{
  int16_t ret_val = SYS_ERR;
  uint16_t data=0;
  do
  {
    if(SYS_OK!= bq76942_write_RAM_register(VCellMode, AFE_RAMwrite.vCellModecmd, 2))
    {
      break;
    }
    if(SYS_OK!= bq76942_read_RAM_register(VCellMode, &data))
    {
      break;
    }
    if(data!= AFE_RAMwrite.vCellModecmd)
    {
      break;
    }
      ret_val = SYS_OK;
  }while(false);
  return ret_val;
}
extern int16_t bq76942_enabledProtectionsA (void)
{
  int16_t ret_val = SYS_ERR;
  uint16_t data=0;
  do
  {
    if(SYS_OK!= bq76942_write_RAM_register(EnabledProtectionsA, AFE_RAMwrite.enabledProtectionsA, 1))
    {
      break;
    }
    if(SYS_OK!= bq76942_read_RAM_register(EnabledProtectionsA, &data))
    {
      break;
    }
    if(data!= AFE_RAMwrite.enabledProtectionsA)
    {
      break;
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}
extern int16_t bq76942_enabledProtectionsB (void)
{
  int16_t ret_val = SYS_ERR;
  uint16_t data=0;
  do
  {
    if(SYS_OK!= bq76942_write_RAM_register(EnabledProtectionsB, AFE_RAMwrite.enabledProtectionsB, 1))
    {
      break;
    }
    if(SYS_OK!= bq76942_read_RAM_register(EnabledProtectionsB, &data))
    {
      break;
    }
    if(data!= AFE_RAMwrite.enabledProtectionsB)
    {
      break;
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}
extern int16_t bq76942_prechargeStartVolt(void)
{
  int16_t ret_val = SYS_ERR;
  uint16_t data=0;
  do
  {
    if(SYS_OK!= bq76942_write_RAM_register(PrechargeStartVoltage, AFE_RAMwrite.prechargeStartVoltage, 2))
    {
      break;
    }
    if(SYS_OK!= bq76942_read_RAM_register(PrechargeStartVoltage, &data))
    {
      break;
    }
    if(data!= AFE_RAMwrite.prechargeStartVoltage)
    {
      break;
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}
extern int16_t bq76942_prechargeStopVolt(void)
{
  int16_t ret_val = SYS_ERR;
  uint16_t data=0;
  do
  {
    if(SYS_OK!= bq76942_write_RAM_register(PrechargeStopVoltage, AFE_RAMwrite.prechargeStopVoltage, 2))
    {
      break;
    }
    if(SYS_OK!= bq76942_read_RAM_register(PrechargeStopVoltage, &data))
    {
      break;
    }
    if(data!= AFE_RAMwrite.prechargeStopVoltage)
    {
      break;
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}
extern int16_t bq76942_TS3config(void)
{
  int16_t ret_val = SYS_ERR;
  uint16_t data=0;
  do
  {
    if(SYS_OK!= bq76942_write_RAM_register(PrechargeStopVoltage, AFE_RAMwrite.TS3config, 1))
    {
      break;
    }
    if(SYS_OK!= bq76942_read_RAM_register(PrechargeStopVoltage, &data))
    {
      break;
    }
    if(data!= AFE_RAMwrite.TS3config)
    {
      break;
    }ret_val = SYS_OK;
  }while(false);
  return ret_val;
}
static int16_t bq76942_write_RAM_register (uint16_t reg_address, uint16_t cmd, uint8_t datalen)
{
  //Writes to RAM Register
  uint16_t TX_Buffer;
  uint16_t ret_val = SYS_ERR;
  uint8_t TX_Buff[2] = {0x00, 0x00};
  uint8_t TX_RegData[4] = {0x00, 0x00, 0x00, 0x00};
  TX_RegData[0] = reg_address & 0xff;
  TX_RegData[1] = (reg_address >> 8) & 0xff;
  TX_RegData[2] = cmd & 0xff; //1st byte of data
  TX_RegData[3] = (cmd>>8) & 0xff;

  TX_Buff[0] = bq76942_checksum(TX_RegData, SUB_CMD_LEN+datalen);
  TX_Buff[1] = SUB_CMD_LEN + CHECKSUM_LEN + datalen;
  TX_Buffer = (TX_Buff[1]<<8)| TX_Buff[0];

  do
  {
    if(SYS_OK != bq76942_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, reg_address)) //Writes register address to Subcommand Memory 0x3E
    {
      break;
    }
    if(SYS_OK != bq76942_write_sub_cmd(SUB_CMD_DATA_BUFF_ADDR, cmd)) //Writes Command to Buffer Memory 0x40
    {
      break;
    }
    if(SYS_OK != bq76942_write_sub_cmd(RAM_REG_LSB_ADDR, TX_Buffer))  //Writes Checksum and Datalength to 0x60 and 0x61
    {
      break;
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}

static int16_t bq76942_read_RAM_register (uint16_t reg_address, uint16_t *pData)
{
  //Reads from the RAM Register
  uint16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76942_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, reg_address))
    {
      break;
    }
    if(SYS_OK != bq76942_read_sub_cmd_data_buffer(SUB_CMD_DATA_BUFF_ADDR, &pData, 2))
    {
      break;
    }
    ret_val = SYS_OK;
  }while(false);
  return ret_val;
}

static uint8_t bq76942_checksum(uint8_t *pData, uint8_t len)
// Calculates the checksum when writing to a RAM register. The checksum is the inverse of the sum of the bytes.
{
  uint8_t i;
  uint8_t checksum = 0;

  for(i=0; i<len; i++)
    checksum += pData[i];

  checksum = 0xff & ~checksum;

  return(checksum);
}


static uint8_t bq76942_CRC8(uint8_t *pData, uint8_t len)
//Calculates CRC8 for passed bytes.
{
  uint8_t i;
  uint8_t crc = 0;
  while(len-- != 0)
  {
    for (i = 0x80; i != 0; i /= 2)
    {
      if((crc & 0x80) != 0)
      {
        crc *= 2;
        crc ^= 0x107;
      }
      else
        crc *= 2;

      if((*pData & i) != 0)
        crc ^= 0x107;
    }
    pData++;
  }
  return (crc);
}

//-----------------------------------------------------------------------------------------------------------------------------
// READ/WRITE FUNCTIONS FOR DIRECT COMMANDS and SUBCOMMANDS

static int16_t bq76942_write_sub_cmd(uint16_t subCmdRegAddr, uint16_t subCmd)
{
  //To write data to subcommand address register (0x3E)
  uint8_t subCmdRegAddrWRITE = subCmdRegAddr | 0x80u; //Changes the leftmost bit to 1 since W Operation
  int16_t ret_val = SYS_ERR;
  uint8_t pTxData[SPI_SUB_CMD_FRAME_LEN] = { 0 };
  uint8_t pRxData[SPI_SUB_CMD_FRAME_LEN] = { 0 };
  uint8_t retry_cnt = 0;
  uint16_t TxByte, RxByte = 0;
  for (uint8_t i = 0; i < SUB_CMD_LEN; i++)
  {
    pTxData[0] = subCmdRegAddrWRITE + i;
    pTxData[1] = subCmd >> (i * 8); //To retrieve the lower byte and then the higher byte subsequently
    pTxData[2] = bq76942_CRC8(pTxData, SUB_CMD_LEN);
    TxByte = pTxData[0] | (pTxData[1] << 8);
    do
    {
      HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);                                          // Enable CS
      HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, SPI_SUB_CMD_FRAME_LEN, SPI_WR_TIMEOUT_MS); // Rx & Tx simultaneously (Full Duplex)
      HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);                                          // Disable CS
      HAL_Delay(2);
      RxByte = pRxData[0] | (pRxData[1] << 8);
      retry_cnt++;
    } while((TxByte != RxByte) && (retry_cnt < 4));
    if(TxByte == RxByte)
    {
      retry_cnt=0;
      ret_val = SYS_OK;
    }
    else
    {
      ret_val = SYS_ERR;
      break;
    }
  }
  return ret_val;
}

static int16_t bq76942_read_sub_cmd_data_buffer(uint8_t subCmdRegAddr, uint16_t *pData, uint8_t len)
{
  //To read data from the Subcommand Buffer register(0x40)
  uint8_t RX_DATA[SUB_CMD_DATA_BUFF_LEN_MAX] = {0};  //To store the initial data from the Buffer
  int16_t ret_val = SYS_ERR;
  do
  {
    if((len > SUB_CMD_DATA_BUFF_LEN_MAX) || (len == 0))
    {
      break;
    }
//    if(pData == NULL)
//    {
//      break;
//    }
    uint8_t pTxData[SPI_SUB_CMD_FRAME_LEN] = { 0 };
    uint8_t pRxData[SPI_SUB_CMD_FRAME_LEN] = { 0 };
    uint8_t retry_cnt = 0;
    uint8_t TxByte, RxByte;
    for (uint8_t i = 0; i < len; i++)
    {
      pTxData[0] = subCmdRegAddr + i;
      pTxData[1] = 0xFF;
      pTxData[2] = bq76942_CRC8(pTxData, SUB_CMD_LEN);
      TxByte = pTxData[0];
      retry_cnt = 0;
      do
      {
        HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);                                          // Enable CS
        HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, SPI_SUB_CMD_FRAME_LEN, SPI_WR_TIMEOUT_MS); // Rx & Tx simultaneously (Full Duplex)
        HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);                                          // Disable CS
        HAL_Delay(2);
        RxByte = pRxData[0];
        retry_cnt++;
      } while((TxByte != RxByte) && (retry_cnt < 4));
      if(TxByte == RxByte)
      {
        retry_cnt=0;
        RX_DATA[i] = pRxData[1];
        ret_val = SYS_OK;
      }
      else
      {
        ret_val = SYS_ERR;
        break;
      }
    }
    if(ret_val == SYS_OK)
      *pData= (RX_DATA[1] << 8) | RX_DATA[0];
  } while(false);
  return ret_val;
}

static int16_t bq76942_dir_cmd_write(uint8_t dirCmdRegAddr, uint16_t dirCmd)
{
  //To write data to the Direct Commands registers
  uint8_t dirCmdRegAddrWRITE = dirCmdRegAddr | 0x80; //Changes leftmost bit to 1 since Write Command
  int16_t ret_val = SYS_ERR;
  uint8_t pTxData[SPI_DIR_CMD_FRAME_LEN] = { 0 };
  uint8_t pRxData[SPI_DIR_CMD_FRAME_LEN] = { 0 };
  uint8_t retry_cnt = 0;
  uint16_t TxByte, RxByte;
  for (uint8_t i = 0; i < SUB_CMD_LEN; i++)
  {
    pTxData[0] = dirCmdRegAddrWRITE + i;
    pTxData[1] = dirCmd >> (i * 8);
    pTxData[2] = bq76942_CRC8(pTxData, SUB_CMD_LEN);
    TxByte = pTxData[0] | (pTxData[1] << 8);
    do
    {
      HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);                                          // Enable CS
      HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, SPI_DIR_CMD_FRAME_LEN, SPI_WR_TIMEOUT_MS); // Rx & Tx simultaneously (Full Duplex)
      HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);                                          // Disable CS
      HAL_Delay(2);
      RxByte = pRxData[0] | (pRxData[1] << 8);
      retry_cnt++;
    } while((TxByte != RxByte) && (retry_cnt < 4));
    if(TxByte == RxByte)
    {
      retry_cnt = 0;
      ret_val = SYS_OK;
    }
    else
    {
      ret_val = SYS_ERR;
      break;
    }
  }
  return ret_val;
}

extern int16_t bq76942_dir_cmd_read(uint8_t dirCmdRegAddr, uint16_t *pData, uint8_t len)
{
  //To read data from the direct command registers
  uint8_t RX_DATA[READ_DIR_CMD_BUFF_LEN] = {0};
  int16_t ret_val = SYS_ERR;
  do
  {
    if((len > DIR_CMD_DATA_BUFF_LEN_MAX) || (len == 0))
    {
      break;
    }
    if(pData == NULL)
    {
      break;
    }
    uint8_t pTxData[SPI_DIR_CMD_FRAME_LEN] = { 0 };
    uint8_t pRxData[SPI_DIR_CMD_FRAME_LEN] = { 0 };
    uint8_t retry_cnt = 0;
    uint16_t TxByte, RxByte;
    for (uint8_t i = 0; i < SUB_CMD_LEN; i++)
    {
      pTxData[0] = dirCmdRegAddr + i;
      pTxData[1] = 0xFF;
      pTxData[2] = bq76942_CRC8(pTxData, SUB_CMD_LEN);
      TxByte = pTxData[0];
      retry_cnt = 0;
      do
      {
        HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);                                          // Enable CS
        HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, SPI_DIR_CMD_FRAME_LEN, SPI_WR_TIMEOUT_MS); // Rx & Tx simultaneously (Full Duplex)
        HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);                                          // Disable CS
        HAL_Delay(2);
        RxByte = pRxData[0];
        retry_cnt++;
      } while((TxByte != RxByte) && (retry_cnt < 4));
      if(TxByte == RxByte)
      {
        retry_cnt=0;
        RX_DATA[i] = pRxData[1];
        ret_val = SYS_OK;
      }
      else
      {
        ret_val = SYS_ERR;
        break;
      }
    }
    if(ret_val == SYS_OK)
      *pData= (RX_DATA[1] << 8) | RX_DATA[0];
  } while(false);
  return ret_val;
}
