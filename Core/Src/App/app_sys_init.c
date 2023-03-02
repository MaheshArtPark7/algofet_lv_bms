/*
 * app_sys_init.c
 *
 *  Created on: 29-Nov-2022
 */

#include "app_sys_init.h"
//#include "stm32f4xx_hal_def.h"
#include "gpio.h"
#include "spi.h"
#include "i2c.h"
#include "can.h"
#include "dma.h"
#include "adc.h"

#include "app_afe.h"
#include "app_fuel_gauge.h"

int16_t app_sys_init(void)
{
	int16_t ret_val = SYS_ERR;
	do
	{
		// TODO:
		// IO Init
		(void) MX_GPIO_Init();
		// I2C Init
		(void) MX_I2C1_Init();
		// SPI Init
		(void) MX_SPI1_Init();
		// CAN Init
		(void) MX_CAN1_Init();
		// PWM Init
		(void) MX_DMA_Init();
		// ADC Init
		(void) MX_ADC1_Init();

	}while(false);

	return ret_val;
}

int16_t app_sys_peripheral_init(void)
{
	int16_t ret_val = SYS_ERR;
	do
	{
		// TODO:
		// AFE Init
		if(SYS_OK != app_afe_init())
		{
			break;
		}
		// Fuel Gauge Init
		if(SYS_OK != app_gauge_init())
		{
			break;
		}
		//State Machine Init
		if(SYS_OK != app_bms_sm_init())
		{
		    break;
		}
		// CAN NW Init

		ret_val = SYS_OK;
	}while(false);

	return ret_val;
}
