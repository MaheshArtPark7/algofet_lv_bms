/*
 * app_fuel_gauge.c
 *
 *  Created on: Aug 21, 2022
 */

#include "app_fuel_gauge.h"
#include "stm32f4xx_hal_i2c.h"
#include "i2c.h"

TsGaugeData_t BQ34_GaugeInfo;
TsAppGaugeData_t App_GaugeData;

static TsDataBlockConfig_t block_read_cfg[BQ_NUM_BURST_RD_BLOCKS];
static uint8_t gauge_read_buffer[BQ_RD_BUFFER_LEN];

static int16_t app_gauge_burst_read(TsDataBlockConfig_t *pDataBlockCfg);
static int16_t app_gauge_map_read_data(uint8_t *pBuff, uint8_t blockIdx);

static inline uint16_t byte_map(uint8_t lsb, uint8_t msb)
{
	return (msb << 8 | lsb);
}

static int16_t app_gauge_burst_read(TsDataBlockConfig_t *pDataBlockCfg)
{
	int16_t ret_val = SYS_ERR;
	do
	{
		if(NULL == pDataBlockCfg)
		{
			break;
		}
		if (pDataBlockCfg->Len > BQ_RD_BUFFER_LEN)
		{
			break;
		}
		if(HAL_OK != HAL_I2C_Master_Transmit(&hi2c1, BQ_WR_ADDR, &pDataBlockCfg->Addr, sizeof(pDataBlockCfg->Addr), 500))
		{
			break;
		}

		/* Master request Slave for data */
		if (HAL_OK != HAL_I2C_Master_Receive (&hi2c1, BQ_RD_ADDR, gauge_read_buffer, pDataBlockCfg->Len, 500))
		{
			break;
		}

		ret_val = SYS_OK;

	}while(false);

	return ret_val;
}

static int16_t app_gauge_map_read_data(uint8_t *pBuff, uint8_t blockIdx)
{
	int16_t ret_val = SYS_ERR;
	do
	{
		if(NULL == pBuff)
		{
			break;
		}
		if(blockIdx > BQ_NUM_BURST_RD_BLOCKS)
		{
			break;
		}
		switch(blockIdx)
		{
		case eAlgoFet_BLOCK0:
			BQ34_GaugeInfo.StateOfCharge = pBuff[0];
			BQ34_GaugeInfo.vStack = byte_map(pBuff[6], pBuff[7]);
			BQ34_GaugeInfo.Current = byte_map(pBuff[14], pBuff[15]);
			BQ34_GaugeInfo.Temperature = byte_map(pBuff[10], pBuff[11]);

			App_GaugeData.SoC = BQ34_GaugeInfo.StateOfCharge;
			App_GaugeData.vStack = (float)BQ34_GaugeInfo.vStack/1000;
			App_GaugeData.BatTemp = (float)(BQ34_GaugeInfo.Temperature / 10) - 273.15f;
			App_GaugeData.InstCurrent = (float)BQ34_GaugeInfo.Current/1000;
			break;
		default:
			break;
		}

		ret_val = SYS_OK;
	}while(false);

	return ret_val;
}

int16_t app_gauge_init(void)
{
    int16_t ret_val = SYS_ERR;

    // Config block reads
    block_read_cfg[eAlgoFet_BLOCK0].Addr = 0x02u;
    block_read_cfg[eAlgoFet_BLOCK0].Len = 18u;

    ret_val = SYS_OK;

    return ret_val;
}

int16_t app_gauge_tick(void)
{
    int16_t ret_val = SYS_ERR;
    do
    {
    	// Read SoC
    	if(SYS_OK != app_gauge_burst_read(&block_read_cfg[eAlgoFet_BLOCK0]))
    	{
    		break;
    	}
    	if(SYS_OK != app_gauge_map_read_data(gauge_read_buffer, eAlgoFet_BLOCK0))
    	{
    	    break;
    	}
    	ret_val = SYS_OK;
    }while(false);
    return ret_val;
}
