/*
 * bq76952.c
 *
 *  Created on: 24-Aug-2022
 */

#include "bq76952.h"
#include "bq76952_defines.h"
#include "spi.h"

extern SPI_HandleTypeDef hspi1;

static TsBmsPower_cfg TsBmsPower_cfg_t;

// Global Variables for cell voltages, temperatures, Stack voltage, PACK Pin voltage, LD Pin voltage, CC2 current
uint8_t rxdata[2];
uint8_t Rx_DATA[READ_DIR_CMD_BUFF_LEN] = { 0x00, 0x00 };
uint8_t RX_32Byte[32] = { 0 };
uint16_t CellVoltage[16] = {0};
float Temperature[3] = { 0, 0, 0 };
uint16_t Stack_Voltage = 0x00;
uint16_t Pack_Voltage = 0x00;
uint16_t Load_Voltage = 0x00;
uint16_t Pack_Current = 0x00;

uint8_t FET_Status;  // FET Status register contents  - Shows states of FETs
uint16_t CB_ActiveCells;  // Cell Balancing Active Cells

uint8_t LD_ON = 0;	// Load Detect status bit
uint8_t DSG = 0;   // discharge FET state
uint8_t CHG = 0;   // charge FET state
uint8_t PCHG = 0;  // pre-charge FET state
uint8_t PDSG = 0;  // pre-discharge FET state

//------------------------------------------------------------------------------
// Static Functions declaration
static uint8_t CRC8(uint8_t *ptr, uint8_t len);
static int16_t bq76952_dir_cmd_read(uint8_t dirCmdRegAddr, uint8_t *p_data[2], uint8_t len);
static int16_t bq76952_dir_cmd_write(uint8_t dirCmdRegAddr, uint16_t dirCmd);
static int16_t bq76952_write_to_ram_register(uint8_t reg_address, uint8_t *pdata, uint8_t len);
static int16_t bq76952_write_sub_cmd(uint8_t subCmdRegAddr, uint16_t subCmd);
static int16_t bq76952_read_sub_cmd_data_buffer(uint8_t subCmdRegAddr, uint16_t *p_data, uint8_t len);

//Subcommands and Command-Only Subcommands Declaration
static int16_t bq76952_set_powercfg(TsBmsPower_cfg *pTsBmsPower_cfg_t);
static int16_t bq76952_get_device_number(uint16_t *pDev_num);
static int16_t bq76952_set_config_update(void);
extern int16_t bq76952_AFE_reset(void);
static int16_t bq76952_config(void);
static int16_t bq76952_enter_config_update(void);
static int16_t bq76952_settings_pwr_cfg(void);
static int16_t bq76952_settings_reg0_cfg(void);
static int16_t bq76952_settings_reg12_cfg(void);

//FET Control Functions Declaration
static int16_t bq76952_FETs_Control(void);
static int16_t bq76952_FETs_SleepDisable(void);
static int16_t bq76952_FETs_enable(void);
static int16_t bq76952_allFETs_on(void);
static int16_t bq76952_allFETs_off(void);
extern int16_t bq76952_FETs_ON(void);
extern int16_t bq76952_FETs_OFF(void);
static int16_t bq76952_FETs_ReadStatus(void);
extern int16_t bq76952_FETs_call(void);
static int16_t bq76952_dischargeOFF(void);
static int16_t bq76952_chargeOFF(void);
extern int16_t bq76952_Charge(void);
extern int16_t bq76952_Discharge(void);

//Direct Commands Declaration
static int16_t bq76952_alarmEnable(uint16_t command);
static int16_t bq76952_readVoltage(uint8_t cmd);
static int16_t bq76952_readAllVoltages();
static int16_t bq76952_ReadCurrent(int *Pack_Current[2]);
static float bq76952_ReadTemp(int *cmd[2]);
//------------------------------------------------------------------------------
// Static Functions definition

int16_t bq76952_init(void)
{
  int16_t ret_val = SYS_ERR;
  do
  {
    uint16_t device_number = 0; //fixme
    uint16_t pack_current[2] = {0};
    uint16_t temp[2] = {0};
    TsBmsPower_cfg_t.power_cfg_reg = PowerConfig;
    TsBmsPower_cfg_t.reg_val = 0x2D80;
    TsBmsPower_cfg_t.len = 4;

    //device_number = bq76952_get_device_number(&device_number);
    //pack_current[0] = bq76952_ReadCurrent(&pack_current);
    //temp[0] = bq76952_ReadTemp(&temp);

    //bq76952_FETs_enable();//Enables the FETs
    //HAL_Delay(100);

    //RESET #Resets the Bq769x2 Registers
    //bq76952_AFE_reset();

    //Enter config update mode
    //bq76952_set_config_update();

    //bq76952_FETs_Control(); //To disable the AFE from controlling the FETs on its own

    // TODO: Check if CFGUPDATE bit is SET

    //
    // Leave Reg1 and Reg2 mode in present state when entering deep-sleep state
    //bq76952_set_powercfg(&TsBmsPower_cfg_t);
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

    ret_val = SYS_OK;
  } while(false);

  return ret_val;
}

//------------------------------------------------------------------------------
// FET CONTROL COMMANDS

static int16_t bq76952_FETs_Control(void)
{
  //To control the FETs with MCU only
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76952_write_to_ram_register(FET_CONTROL, FETs_CONTROL, 2))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}


static int16_t bq76952_FETs_SleepDisable(void)
{
  // Puts the FETs in performance mode
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76952_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, SLEEP_DISABLE))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}

static int16_t bq76952_FETs_enable(void)
{
  // Enables all the FETs to be controlled
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76952_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, FET_ENABLE))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}

static int16_t bq76952_allFETs_on(void)
{
  // Switches on all the FETs
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76952_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, ALL_FETS_ON))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}

static int16_t bq76952_allFETs_off(void)
{
  // Switches off all the FETs
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76952_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, ALL_FETS_OFF))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}

extern int16_t bq76952_FETs_ON(void)
{
  //To switch on the FETs whenever required
  bq76952_FETs_enable();
  bq76952_allFETs_on();
}

extern int16_t bq76952_FETs_OFF(void)
{
  //To switch off the FETs
  bq76952_FETs_enable();
  bq76952_allFETs_off();
}

static int16_t bq76952_dischargeOFF(void)
{
  //Disable DSG and PDSG FET drivers
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76952_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, DSG_PDSG_OFF))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}

static int16_t bq76952_chargeOFF(void)
{
  //Disable CHG and PCHG FET drivers
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76952_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, CHG_PCHG_OFF))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}

extern int16_t bq76952_Charge(void)
{
  //to take the BMS to charging mode
  bq76952_FETs_enable();
  bq76952_allFETs_on();
  HAL_Delay(50);
  bq76952_dischargeOFF();
}

extern int16_t bq76952_Discharge(void)
{
  //to take the BMS to charging mode
  bq76952_FETs_enable();
  bq76952_allFETs_on();
  HAL_Delay(50);
  bq76952_chargeOFF();
}

static int16_t bq76952_FETs_ReadStatus(void)
{
  // Reads FET Status to see which FETs are enabled
  bq76952_dir_cmd_read(FETStatus, 0x00, R);
  FET_Status = (Rx_DATA[1] * 256 + Rx_DATA[0]);
  DSG = ((0x4 & Rx_DATA[0]) >> 2);        // discharge FET state
  CHG = (0x1 & Rx_DATA[0]);        // charge FET state
  PCHG = ((0x2 & Rx_DATA[0]) >> 1);        // pre-charge FET state
  PDSG = ((0x8 & Rx_DATA[0]) >> 3);        // pre-discharge FET state
}

//FET Control call
extern int16_t bq76952_FETs_call(void)
{
  //For calling all FET Commands
  bq76952_AFE_reset();
  HAL_Delay(100);
  //bq76952_FETs_SleepDisable();
  //HAL_Delay(100);
  //bq76952_init();
  //HAL_Delay(100);
  bq76952_FETs_enable();
  HAL_Delay(100);
  //bq76952_FETs_Control();
  //HAL_Delay(100);
  //bq76952_FETs_on();
  //HAL_Delay(100);
  //bq76952_FETs_off();
  //HAL_Delay(100);
  //bq76952_dischargeOFF();
  //HAL_Delay(100);
  //bq76952_chargeOFF();
  //HAL_Delay(100);
}

//------------------------------------------------------------------------------------------------------------
//AFE Functions
extern int16_t bq76952_AFE_reset(void)
{
  // Resets all the registers of the AFE
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76952_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, RESET))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}

static int16_t bq76952_set_powercfg(TsBmsPower_cfg *pTsBmsPower_cfg_t)
{
  //PowerConfig --> 0x2D80   #DPSLP_LDO bit -> 1

  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76952_write_to_ram_register(SUB_CMD_REG_LSB_ADDR, pTsBmsPower_cfg_t->buffer, pTsBmsPower_cfg_t->len))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}

static int16_t bq76952_get_device_number(uint16_t *pDev_num)
{
  //Reads the device number of the AFE
  int16_t ret_val = SYS_ERR;
  uint8_t device_number;
  do
  {
    if(SYS_OK != bq76952_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, DEVICE_NUMBER))
    {
      break;
    }
    if(SYS_OK != bq76952_read_sub_cmd_data_buffer(SUB_CMD_DATA_BUFF_ADDR, &pDev_num, 2))
    {
      pDev_num= *pDev_num;
      break;
    }
  } while(false);
  ret_val = SYS_OK;

  return pDev_num;
}

extern int16_t led_blink(void)
{
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
  HAL_Delay(100);
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
  HAL_Delay(200);
}
//----------------------------------------------DIRECT COMMANDS-------------------------------------------------------------------

static int16_t bq76952_alarmEnable(uint16_t command)
{
  //To set a value to the Alarm Enable Register
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76952_dir_cmd_write(AlarmEnable, command))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}

static int16_t bq76952_readVoltage(uint8_t cmd)
{
  int16_t ret_val = SYS_ERR;
  do
  {
    bq76952_dir_cmd_read(cmd, 0x00, 2);
    if(cmd >= Cell1Voltage && cmd <= Cell16Voltage)
    {	//Cells 1 through 16 (0x14 to 0x32)
      return (Rx_DATA[1] * 256 + Rx_DATA[0]); //voltage is reported in mV
    }
    else
    { //stack, Pack, LD
      return 10 * (Rx_DATA[1] * 256 + Rx_DATA[0]); //voltage is reported in 0.01V units
    }
  } while(false);
  return ret_val;
}

static int16_t bq76952_readAllVoltages()
{
  int cellvoltageholder = Cell1Voltage; //Cell1Voltage is 0x14
  for (int x = 0; x < 16; x++)
  { //Reads all cell voltages
    CellVoltage[x] = bq76952_readVoltage(cellvoltageholder);
    cellvoltageholder = cellvoltageholder + 2;
  }
  Stack_Voltage = bq76952_readVoltage(StackVoltage);
  Pack_Voltage = bq76952_readVoltage(PACKPinVoltage);
  Load_Voltage = bq76952_readVoltage(LDPinVoltage);
}

static int16_t bq76952_ReadCurrent(int *Pack_Current[2])
// Reads PACK current
{
  bq76952_dir_cmd_read(CC2Current, &Pack_Current, 2);
  return ((int)Pack_Current[1] * 256 + (int)Pack_Current[0]);  // current is reported in mA
}

static float bq76952_ReadTemp(int *cmd[2])
{
  //Reads the temperature of the AFE
  bq76952_dir_cmd_read(IntTemperature ,&cmd , 2);
  return (0.1 * (float) ((int)cmd[1] * 256 + (int)cmd[0])) - 273.15;
}

static int16_t bq76952_set_config_update(void)
{
  int16_t ret_val = SYS_ERR;
  do
  {
    if(SYS_OK != bq76952_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, SET_CFGUPDATE))
    {
      break;
    }
  } while(false);
  ret_val = SYS_OK;
  return ret_val;
}

static int16_t bq76952_settings_pwr_cfg(void)
{
  int16_t ret_val = SYS_ERR;
  uint16_t settings = 0x1D00;
  // Settings:Power Config
//    bq76952_sub_cmd_access((uint16_t)PowerConfig, SPI_WR_BLOCKING, sizeof(settings) + SUB_CMD_LEN, &settings);
  ret_val = SYS_OK;
  return ret_val;
}

static int16_t bq76952_settings_reg0_cfg(void)
{
  int16_t ret_val = SYS_ERR;
  uint8_t settings = 0x01;
  // Settings:REG0 Config
//    bq76952_sub_cmd_access((uint16_t)REG0Config, SPI_WR_BLOCKING, sizeof(settings) + SUB_CMD_LEN, &settings);
  ret_val = SYS_OK;
  return ret_val;
}

static int16_t bq76952_settings_reg12_cfg(void)
{
  int16_t ret_val = SYS_ERR;
  uint8_t settings = 0x0D;
  // Settings:REG12 Config
//    bq76952_sub_cmd_access((uint16_t)REG12Config, SPI_WR_BLOCKING, sizeof(settings) + SUB_CMD_LEN, &settings);
  ret_val = SYS_OK;
  return ret_val;
}
static int16_t bq76952_write_to_ram_register(uint8_t reg_address, uint8_t *pdata, uint8_t len)
{
  //Writes data to the RAM Register
  int16_t ret_val = SYS_ERR;
  do
  {
    if(pdata == NULL)
    {
      break;
    }
    for (uint8_t i = 0; i < len; i++)
    {
      if(SYS_OK != bq76952_write_sub_cmd(reg_address + i, pdata[i]))
      {
        break;
      }
    }
    ret_val = SYS_OK;
  } while(false);
  return ret_val;
}

static uint8_t get_crc8(uint8_t *pData, uint8_t len)
{
  uint8_t crc = 0xff;
  size_t i, j;
  for (i = 0; i < len; i++)
  {
    crc ^= pData[i];
    for (j = 0; j < 8; j++)
    {
      if((crc & 0x80) != 0)
        crc = (uint8_t) ((crc << 1) ^ 0x31);
      else
        crc <<= 1;
    }
  }
  return crc;
}
static uint8_t CRC8(uint8_t *ptr, uint8_t len)
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

      if((*ptr & i) != 0)
        crc ^= 0x107;
    }
    ptr++;
  }
  return (crc);
}

//-----------------------------------------------------------------------------------------------------------------------------
// READ/WRITE FUNCTIONS FOR DIRECT COMMANDS and SUBCOMMANDS

static int16_t bq76952_write_sub_cmd(uint8_t subCmdRegAddr, uint16_t subCmd)
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
    pTxData[2] = CRC8(pTxData, SUB_CMD_LEN);
    TxByte = pTxData[0] | (pTxData[1] << 8);
    do
    {
      HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);                                          // Enable CS
      HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, SPI_SUB_CMD_FRAME_LEN, SPI_WR_TIMEOUT_MS); // Rx & Tx simultaneously (Full Duplex)
      HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);                                          // Disable CS
      HAL_Delay(2);
      RxByte = pRxData[0] | (pRxData[1] << 8);
      retry_cnt++;
    } while((TxByte != RxByte) && (retry_cnt < 3));
    if((TxByte == RxByte) && (retry_cnt < 4))
    {
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

static int16_t bq76952_read_sub_cmd_data_buffer(uint8_t subCmdRegAddr, uint16_t *p_data, uint8_t len)
{
  //To read data from the Subcommand Buffer register(0x40)
  uint8_t RX_DATA[READ_DIR_CMD_BUFF_LEN] = {0};  //To store the initial data from the Buffer
  int16_t ret_val = SYS_ERR;
  do
  {
    if((len > SUB_CMD_DATA_BUFF_LEN_MAX) || (len == 0))
    {
      break;
    }
    if(p_data == NULL)
    {
      break;
    }
    uint8_t pTxData[SPI_SUB_CMD_FRAME_LEN] = { 0 };
    uint8_t pRxData[SPI_SUB_CMD_FRAME_LEN] = { 0 };
    uint8_t retry_cnt = 0;
    uint8_t TxByte, RxByte;
    for (uint8_t i = 0; i < len; i++)
    {
      pTxData[0] = subCmdRegAddr + i;
      pTxData[1] = 0xFF;
      pTxData[2] = CRC8(pTxData, SUB_CMD_LEN);
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
      } while((TxByte != RxByte) && (retry_cnt < 3));
      if((TxByte == RxByte) && (retry_cnt < 4))
      {
        RX_DATA[i] = pRxData[1];
      }
      else
      {
        ret_val = SYS_ERR;
        break;
      }
    }
    p_data= (RX_DATA[1] << 8) | RX_DATA[0];
  } while(false);
  return p_data;
}

static int16_t bq76952_dir_cmd_write(uint8_t dirCmdRegAddr, uint16_t dirCmd)
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
    pTxData[2] = CRC8(pTxData, SUB_CMD_LEN);
    TxByte = pTxData[0] | (pTxData[1] << 8);
    do
    {
      HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);                                          // Enable CS
      HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, SPI_DIR_CMD_FRAME_LEN, SPI_WR_TIMEOUT_MS); // Rx & Tx simultaneously (Full Duplex)
      HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);                                          // Disable CS
      HAL_Delay(2);
      RxByte = pRxData[0] | (pRxData[1] << 8);
      retry_cnt++;
    } while((TxByte != RxByte) && (retry_cnt < 3));
    if((TxByte == RxByte) && (retry_cnt < 4))
    {
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

static int16_t bq76952_dir_cmd_read(uint8_t dirCmdRegAddr, uint8_t *p_data[2], uint8_t len)
{
  //To read data from the direct command registers
  int16_t ret_val = SYS_ERR;
  do
  {
    if((len > DIR_CMD_DATA_BUFF_LEN_MAX) || (len == 0))
    {
      break;
    }
    if(p_data == NULL)
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
      pTxData[2] = CRC8(pTxData, SUB_CMD_LEN);
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
      } while((TxByte != RxByte) && (retry_cnt < 3));
      if((TxByte == RxByte) && (retry_cnt < 4))
      {
        p_data[i] = pRxData[1];
        ret_val = SYS_OK;
      }
      else
      {
        ret_val = SYS_ERR;
        break;
      }
    }
  } while(false);
  return p_data;
}

