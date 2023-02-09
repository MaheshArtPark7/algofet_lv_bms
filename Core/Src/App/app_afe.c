/*
 * app_afe.c
 *
 *  Created on: Aug 21, 2022
 */

#include "app_afe.h"
#include "app_defines.h"
#include "bq76952.h"
#include "main.h"

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
