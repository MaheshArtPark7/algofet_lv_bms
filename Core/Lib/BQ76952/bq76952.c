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

static int16_t bq76952_sub_cmd_access(uint16_t sub_cmd, bool read_write, uint8_t data_len, uint8_t *p_data);
static int16_t bq76952_dir_cmd_access(uint8_t dir_cmd, bool read_write, uint8_t data_len, uint8_t *p_data);
static int16_t bq76952_wr_cmd(uint8_t subCmdRegAddr, uint8_t subCmd);
static int16_t bq76952_get_device_number(void);
static int16_t bq76952_set_config_update(void);
static int16_t bq76952_config(void);
static int16_t bq76952_enter_config_update(void);
static int16_t bq76952_settings_pwr_cfg(void);
static int16_t bq76952_settings_reg0_cfg(void);
static int16_t bq76952_settings_reg12_cfg(void);

//------------------------------------------------------------------------------
// Static Functions definition
static int16_t bq76952_sub_cmd_access(uint16_t sub_cmd, bool read_write, uint8_t data_len, uint8_t *p_data)
{
    int16_t ret_val = SYS_ERR;
    do
    {
        if (data_len == 0)
        {
            break;
        }
        if ((data_len != SUB_CMD_LEN) && (p_data == NULL))
        {
            break;
        }

        if (SYS_OK != bq76952_wr_cmd(SUB_CMD_WR_REG_LSB_ADDR, (uint8_t)sub_cmd))
        {
            break;
        }
        if (SYS_OK != bq76952_wr_cmd(SUB_CMD_WR_REG_MSB_ADDR, (uint8_t)sub_cmd >> 8))
        {
            break;
        }

        //		while(pRxData[0] != pTxData[0])
        //		{
        //		    HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);
        //		    HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, SPI_SUB_CMD_FRAME_LEN, SPI_WR_TIMEOUT_MS);
        //		    HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);
        //		    HAL_Delay(10);
        //		}
        //
        //		pTxData[0] = 0xBF; // Constant
        //		pTxData[1] = (uint8_t)sub_cmd >> 8;
        //		pTxData[2] = 0x8C;
        //		while(pRxData[0] != pTxData[0])
        //		{
        //		    HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);
        //		    HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, 3, SPI_WR_TIMEOUT_MS);
        //		    HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);
        //		    HAL_Delay(10);
        //		}
        //
        //		pTxData[0] = 0x40; // constant
        //		pTxData[1] = 0xFF;
        //		pTxData[2] = 0xA8;
        //		while(pRxData[0] != pTxData[0])
        //		{
        //		    HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);
        //		    HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, 3, SPI_WR_TIMEOUT_MS);
        //		    HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);
        //		    HAL_Delay(10);
        //		}
        //
        //		pTxData[0] = 0x41; // constant
        //		pTxData[1] = 0xFF;
        //		pTxData[2] = 0xBD;
        //		while(pRxData[0] != pTxData[0])
        //		{
        //		    HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);
        //		    HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, 3, SPI_WR_TIMEOUT_MS);
        //		    HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);
        //		    HAL_Delay(10);
        //		}

        ret_val = SYS_OK;
    } while (false);

    return ret_val;
}

int16_t bq76952_init(void)
{
    int16_t ret_val = SYS_ERR;
    do
    {
        bq76952_get_device_number();
        //        bq76952_set_config_update();
        // TODO: Check if CFGUPDATE bit is SET
        //        bq76952_settings_pwr_cfg();

        ret_val = SYS_OK;
    } while (false);

    return ret_val;
}

static int16_t bq76952_get_device_number(void)
{
    int16_t ret_val = SYS_ERR;
    bq76952_sub_cmd_access(DEVICE_NUMBER, SPI_WR_BLOCKING, SUB_CMD_LEN, NULL);
    ret_val = SYS_OK;
    return ret_val;
}
static int16_t bq76952_set_config_update(void)
{
    int16_t ret_val = SYS_ERR;
    // Enter CONFIG_UPDATE mode
    bq76952_sub_cmd_access((uint16_t)SET_CFGUPDATE, SPI_WR_BLOCKING, SUB_CMD_LEN, NULL);
    ret_val = SYS_OK;
    return ret_val;
}

static int16_t bq76952_settings_pwr_cfg(void)
{
    int16_t ret_val = SYS_ERR;
    uint16_t settings = 0x1D00;
    // Settings:Power Config
    bq76952_sub_cmd_access((uint16_t)PowerConfig, SPI_WR_BLOCKING, sizeof(settings) + SUB_CMD_LEN, &settings);
    ret_val = SYS_OK;
    return ret_val;
}

static int16_t bq76952_settings_reg0_cfg(void)
{
    int16_t ret_val = SYS_ERR;
    uint8_t settings = 0x01;
    // Settings:REG0 Config
    bq76952_sub_cmd_access((uint16_t)REG0Config, SPI_WR_BLOCKING, sizeof(settings) + SUB_CMD_LEN, &settings);
    ret_val = SYS_OK;
    return ret_val;
}

static int16_t bq76952_settings_reg12_cfg(void)
{
    int16_t ret_val = SYS_ERR;
    uint8_t settings = 0x0D;
    // Settings:REG12 Config
    bq76952_sub_cmd_access((uint16_t)REG12Config, SPI_WR_BLOCKING, sizeof(settings) + SUB_CMD_LEN, &settings);
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

static int16_t bq76952_wr_cmd(uint8_t subCmdRegAddr, uint8_t subCmd)
{
    int16_t ret_val = SYS_ERR;
    uint8_t pTxData[SPI_SUB_CMD_FRAME_LEN] = {0};
    uint8_t pRxData[SPI_SUB_CMD_FRAME_LEN] = {0};
    uint8_t retry_cnt = 0;
    uint16_t TxByte, RxByte;

    pTxData[0] = subCmdRegAddr;
    pTxData[1] = subCmd;
    pTxData[2] = get_crc8(pTxData, SUB_CMD_LEN);

    TxByte = pTxData[0] | (pTxData[1] << 8);
    RxByte = 0;
    while ((TxByte != RxByte) && (retry_cnt > 3))
    {
        HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 0);                                          // Enable CS
        HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, SPI_SUB_CMD_FRAME_LEN, SPI_WR_TIMEOUT_MS); // Rx & Tx simultaneously (Full Duplex)
        HAL_GPIO_WritePin(SP1_CS_GPIO_Port, SP1_CS_Pin, 1);                                          // Disable CS
        // TODO: Change SPI baud to 1Mbps and minimise the delay(1ms)
        HAL_Delay(10);
        RxByte = pRxData[0] | (pRxData[1] << 8);
        retry_cnt++;
    }
    ret_val = (TxByte == RxByte) ? SYS_OK : SYS_ERR;
    return ret_val;
}