/*
 * bq76952.c
 *
 *  Created on: 24-Aug-2022
 */

#include "bq76952.h"
#include "bq76952_defines.h"
#include "spi.h"

extern SPI_HandleTypeDef hspi1;

//------------------------------------------------------------------------------
// Static Functions declaration

static int16_t bq76952_dir_cmd_access(uint8_t dir_cmd, bool read_write, uint8_t data_len, uint8_t *p_data);
static int16_t bq76952_write_sub_cmd(uint8_t subCmdRegAddr, uint8_t subCmd);
static int16_t bq76952_read_sub_cmd_data_buffer(uint8_t subCmdRegAddr, uint8_t *p_data, uint8_t len);
static int16_t bq76952_get_device_number(uint16_t *pDev_num);
static int16_t bq76952_set_config_update(void);
static int16_t bq76952_config(void);
static int16_t bq76952_enter_config_update(void);
static int16_t bq76952_settings_pwr_cfg(void);
static int16_t bq76952_settings_reg0_cfg(void);
static int16_t bq76952_settings_reg12_cfg(void);

//------------------------------------------------------------------------------
// Static Functions definition

int16_t bq76952_init(void)
{
    int16_t ret_val = SYS_ERR;
    do
    {
        uint16_t device_number = 0;
        bq76952_get_device_number(&device_number);
        //RESET #Resets the Bq769x2 Registers
        //        bq76952_set_config_update();
        // TODO: Check if CFGUPDATE bit is SET

        //PowerConfig --> 0x2D80   #DPSLP_LDO bit -> 1 To leave Reg1 and Reg2 mode in present state when entering Deepsleep
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
    } while (false);

    return ret_val;
}

static int16_t bq76952_get_device_number(uint16_t *pDev_num)
{
    int16_t ret_val = SYS_ERR;
    do
    {
        if (SYS_OK != bq76952_write_sub_cmd(SUB_CMD_REG_LSB_ADDR, DEVICE_NUMBER))
        {
            break;
        }
        if (SYS_OK != bq76952_read_sub_cmd_data_buffer(SUB_CMD_DATA_BUFF_ADDR, (uint8_t*)pDev_num, 2))
        {
            break;
        }
    } while (false);
    ret_val = SYS_OK;
    return ret_val;
}

static int16_t bq76952_set_config_update(void)
{
    int16_t ret_val = SYS_ERR;
    // Enter CONFIG_UPDATE mode
//    bq76952_sub_cmd_access((uint16_t)SET_CFGUPDATE, SPI_WR_BLOCKING, SUB_CMD_LEN, NULL);
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

static uint8_t get_crc8(uint8_t *pData, uint8_t len)
{
    uint8_t crc = 0xff;
    size_t i, j;
    for (i = 0; i < len; i++)
    {
        crc ^= pData[i];
        for (j = 0; j < 8; j++)
        {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ 0x31);
            else
                crc <<= 1;
        }
    }
    return crc;
}

static int16_t bq76952_write_sub_cmd(uint8_t subCmdRegAddr, uint8_t subCmd)
{
    int16_t ret_val = SYS_ERR;
    uint8_t pTxData[SPI_SUB_CMD_FRAME_LEN] = {0};
    uint8_t pRxData[SPI_SUB_CMD_FRAME_LEN] = {0};
    uint8_t retry_cnt = 0;
    uint16_t TxByte, RxByte;
    for (uint8_t i = 0; i < SUB_CMD_LEN; i++)
    {
        pTxData[0] = subCmdRegAddr + i;
        pTxData[1] = subCmd;
        pTxData[2] = get_crc8(pTxData, SUB_CMD_LEN);
        TxByte = pTxData[0] | (pTxData[1] << 8);
        do
        {
            HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);                                          // Enable CS
            HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, SPI_SUB_CMD_FRAME_LEN, SPI_WR_TIMEOUT_MS); // Rx & Tx simultaneously (Full Duplex)
            HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);                                          // Disable CS
            HAL_Delay(2);
            RxByte = pRxData[0] | (pRxData[1] << 8);
            retry_cnt++;
        } while ((TxByte != RxByte) && (retry_cnt > 3));
        if ((TxByte == RxByte) && (retry_cnt < 4))
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

static int16_t bq76952_read_sub_cmd_data_buffer(uint8_t subCmdRegAddr, uint8_t *p_data, uint8_t len)
{
    int16_t ret_val = SYS_ERR;
    do
    {
        if ((len > SUB_CMD_DATA_BUFF_LEN_MAX) || (len == 0))
        {
            break;
        }
        if (p_data == NULL)
        {
            break;
        }
        uint8_t pTxData[SPI_SUB_CMD_FRAME_LEN] = {0};
        uint8_t pRxData[SPI_SUB_CMD_FRAME_LEN] = {0};
        uint8_t retry_cnt = 0;
        uint8_t TxByte, RxByte;
        for (uint8_t i = 0; i > len; i++)
        {
            pTxData[0] = subCmdRegAddr + i;
            pTxData[1] = 0xFF;
            pTxData[2] = get_crc8(pTxData, SUB_CMD_LEN);
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
            } while ((TxByte != RxByte) && (retry_cnt > 3));
            if ((TxByte == RxByte) && (retry_cnt < 4))
            {
                p_data[i] = RxByte;
                ret_val = SYS_OK;
            }
            else
            {
                ret_val = SYS_ERR;
                break;
            }
        }
    } while (false);
    return ret_val;
}
