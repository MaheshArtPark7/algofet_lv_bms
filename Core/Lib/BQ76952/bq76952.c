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
        //        bq76952_set_config_update();
        // TODO: Check if CFGUPDATE bit is SET
        //        bq76952_settings_pwr_cfg();

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
