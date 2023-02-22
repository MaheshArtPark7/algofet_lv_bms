/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

CAN_FilterTypeDef filterConfig;

__CoderDbcCanFrame_t__ canFrame;

FCU_STATE_REQUEST_t fcuState;
BAT_BMS_OvrVIEW_t batBmsOvr;
BAT_BMS_ExtTemp_t batBmsExtTemp;
BAT_AFE_vBRICK_A_t batAfeBrickA;
BAT_AFE_vBRICK_B_t batAfeBrickB;
BAT_AFE_vBRICK_C_t batAfeBrickC;
BAT_AFE_vBRICK_D_t batAfeBrickD;
BAT_GAUGE_OvrVIEW_t batGaugeOvr;
BAT_GAUGE_ViT_t batGaugeViT;

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

uint32_t mailbox;
int toggle;
int count = 0;
uint32_t id;
uint8_t state[8];

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	//HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_13);
}

void TxHeaderGenerator()
{
	TxHeader.DLC = 8;
	TxHeader.ExtId = 0;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = 0x001;
	TxHeader.TransmitGlobalTime = DISABLE;
}

void RxHeaderGenerator()
{
	RxHeader.DLC = 8;
	RxHeader.ExtId = 0;
	RxHeader.IDE = CAN_ID_STD;
	RxHeader.RTR = CAN_RTR_REMOTE;
	RxHeader.StdId = 0x01;
}

/*void SetFilterConfig(int toggle)
{
	filterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	filterConfig.FilterActivation = ENABLE;
	filterConfig.FilterBank = 2;
	switch (toggle) {
		case 1: //BMS overview & Ext Temp
			filterConfig.FilterIdLow = 0xF610;
			filterConfig.FilterIdHigh = 0x001F;
			filterConfig.FilterMaskIdLow = 0xF610;
			filterConfig.FilterMaskIdHigh = 0x111F;
			break;
		case 2: //AFE v brick A-D
			filterConfig.FilterIdLow = 0xF710;
			filterConfig.FilterIdHigh = 0x001F;
			filterConfig.FilterMaskIdLow = 0xF710;
			filterConfig.FilterMaskIdHigh = 0x111F;
			break;
		case 3: //Gauge Overview & ViT
			filterConfig.FilterIdLow = 0xF810;
			filterConfig.FilterIdHigh = 0x001F;
			filterConfig.FilterMaskIdLow = 0xF801;
			filterConfig.FilterMaskIdHigh = 0x111F;
			break;
		case 4: //FCU state
			filterConfig.FilterIdLow = 0x0101;
			filterConfig.FilterIdHigh = 0x0000;
			break;
		default:
			break;
	}
	filterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	filterConfig.SlaveStartFilterBank = 3;

	HAL_CAN_ConfigFilter(&hcan1, &filterConfig);
}*/

void SetFilterConfig()
{
	filterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	filterConfig.FilterActivation = ENABLE;
	filterConfig.FilterBank = 2;
	filterConfig.FilterIdLow = 0x0101;
	filterConfig.FilterIdHigh = 0x0000;
	filterConfig.FilterMaskIdLow = 0x1101;
	filterConfig.FilterMaskIdHigh = 0x1111;
	filterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	filterConfig.SlaveStartFilterBank = 3;

	HAL_CAN_ConfigFilter(&hcan1, &filterConfig);
}
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 5;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_15TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  HAL_CAN_Start(&hcan1);
  TxHeaderGenerator();
  RxHeaderGenerator();

  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_TX_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void writeCANBatGaugeOvr()
{
	HAL_CAN_Start(&hcan1);
	id = Pack_BAT_GAUGE_OvrVIEW_can_codegen(&batGaugeOvr, &canFrame);
	if(id == 0x1ff810)
	HAL_CAN_AddTxMessage(&hcan1, &TxHeader, canFrame.Data, &mailbox);
}

void writeCANBatGaugeViT()
{
	HAL_CAN_Start(&hcan1);
	id = Pack_BAT_GAUGE_ViT_can_codegen(&batGaugeViT, &canFrame);
	if(id == 0x1ff820)
	HAL_CAN_AddTxMessage(&hcan1, &TxHeader, canFrame.Data, &mailbox);
}

void writeBMSOvr()
{
	HAL_CAN_Start(&hcan1);
	id = Pack_BAT_BMS_OvrVIEW_can_codegen(&batBmsOvr, &canFrame);
	if(id == 0x1ff610)
	HAL_CAN_AddTxMessage(&hcan1, &TxHeader, canFrame.Data, &mailbox);
}

void writeBMSExtTemp()
{
	HAL_CAN_Start(&hcan1);
	id = Pack_BAT_BMS_ExtTemp_can_codegen(&batBmsExtTemp, &canFrame);
	if(id == 0x1ff611)
	HAL_CAN_AddTxMessage(&hcan1, &TxHeader, canFrame.Data, &mailbox);
}

void writeAfeBrickAVt()
{
	HAL_CAN_Start(&hcan1);
	id = Pack_BAT_AFE_vBRICK_A_can_codegen(&batAfeBrickA, &canFrame);
	if(id == 0x1ff710)
	HAL_CAN_AddTxMessage(&hcan1, &TxHeader, canFrame.Data, &mailbox);
}

void writeAfeBrickBVt()
{
	HAL_CAN_Start(&hcan1);
	id = Pack_BAT_AFE_vBRICK_B_can_codegen(&batAfeBrickB, &canFrame);
	if(id == 0x1ff711)
	HAL_CAN_AddTxMessage(&hcan1, &TxHeader, canFrame.Data, &mailbox);
}

void writeAfeBrickCVt()
{
	HAL_CAN_Start(&hcan1);
	id = Pack_BAT_AFE_vBRICK_C_can_codegen(&batAfeBrickC, &canFrame);
	if(id == 0x1ff712)
	HAL_CAN_AddTxMessage(&hcan1, &TxHeader, canFrame.Data, &mailbox);
}

void writeAfeBrickDVt()
{
	HAL_CAN_Start(&hcan1);
	id = Pack_BAT_AFE_vBRICK_D_can_codegen(&batAfeBrickD, &canFrame);
	if(id == 0x1ff713)
	HAL_CAN_AddTxMessage(&hcan1, &TxHeader, canFrame.Data, &mailbox);
}

//reading Fuel Gauge Data over CAN

/*void readCANBatGaugeOvr()
{
	toggle = 3;
	SetFilterConfig(toggle);

	if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, state) == HAL_OK)
	{
		id = Unpack_BAT_GAUGE_OvrVIEW_can_codegen(&batGaugeOvr, &state, 4);
	}
}

void readCANBatGaugeVit()
{
	toggle = 3;
	SetFilterConfig(toggle);

	if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, state) == HAL_OK)
	{
		id  = Unpack_BAT_GAUGE_ViT_can_codegen(&batGaugeViT, &state, 6);
	}
}*/

// Reading BMS related info on CAN

/*void readBMSOvr()
{
	toggle = 1;
	SetFilterConfig(toggle);

	if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, state) == HAL_OK);
	{
		id = Unpack_BAT_BMS_OvrVIEW_can_codegen(&batBmsOvr, &state, 2);
	}
}

void readBMSExtTemp()
{
	toggle = 1;
	SetFilterConfig(toggle);

	if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, state) == HAL_OK)
	{
		id = Unpack_BAT_BMS_ExtTemp_can_codegen(&batBmsExtTemp, &state, 4);
	}
}*/

// reading AFE brick voltages over CAN

/*void readAfeBrickAVt()
{
	toggle = 2;
	SetFilterConfig(toggle);

	if(HAL_CAN_GetRxMessage(&hcan1,  CAN_RX_FIFO0, &RxHeader, state)== HAL_OK)
	{
		id = Unpack_BAT_AFE_vBRICK_A_can_codegen(&batAfeBrickA, &state, 8);
	}
}

void readAfeBrickBVt()
{
	toggle = 2;
	SetFilterConfig(toggle);

	if(HAL_CAN_GetRxMessage(&hcan1,  CAN_RX_FIFO0, &RxHeader, state)== HAL_OK)
	{
		id = Unpack_BAT_AFE_vBRICK_B_can_codegen(&batAfeBrickB, &state, 8);
	}
}

void readAfeBrickCVt()
{
	toggle = 2;
	SetFilterConfig(toggle);

	if(HAL_CAN_GetRxMessage(&hcan1,  CAN_RX_FIFO0, &RxHeader, state)== HAL_OK)
	{
		id = Unpack_BAT_AFE_vBRICK_C_can_codegen(&batAfeBrickC, &state, 8);
	}
}

void readAfeBrickDVt()
{
	toggle = 2;
	SetFilterConfig(toggle);

	if(HAL_CAN_GetRxMessage(&hcan1,  CAN_RX_FIFO0, &RxHeader, state)== HAL_OK)
	{
		id = Unpack_BAT_AFE_vBRICK_D_can_codegen(&batAfeBrickD, &state, 8);
	}
}*/

void readFCU_state()
{
	//toggle = 4;
	//SetFilterConfig(toggle); //to be uncommented if reading other data as well apart from FCU State
	SetFilterConfig(); //to be commented out if reading other data as well apart from FCU state.
	if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, state) == HAL_OK)
		{
		id = Unpack_FCU_STATE_REQUEST_can_codegen(&fcuState, &state, 1);
		switch (state[0]) {
			case 0:
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);  // replace with all fets on function call
				break;
			case 1:
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);  //replace with all fets off function call
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);  // replace with afe reset function call
				break;
			case 3:
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
				break;
			default:
				break;
		}
		}
}


/* USER CODE END 1 */
