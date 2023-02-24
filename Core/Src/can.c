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
#include "FreeRTOS.h"
#include "queue.h"

/* USER CODE BEGIN 0 */

#define uxQueueLength 10
#define uxItemSize sizeof(struct CanFrame*)

CAN_FilterTypeDef filterConfig;
QueueHandle_t xQueue1;
__CoderDbcCanFrame_t__ canFrame;
struct CanFrame *ReceivedFrame;

// structure objects
FCU_STATE_REQUEST_t fcuState;
BAT_BMS_OvrVIEW_t batBmsOvr;
BAT_BMS_ExtTemp_t batBmsExtTemp;
BAT_AFE_vBRICK_A_t batAfeBrickA;
BAT_AFE_vBRICK_B_t batAfeBrickB;
BAT_AFE_vBRICK_C_t batAfeBrickC;
BAT_AFE_vBRICK_D_t batAfeBrickD;
BAT_GAUGE_OvrVIEW_t batGaugeOvr;
BAT_GAUGE_ViT_t batGaugeViT;

// CAN TxHeaders
CAN_TxHeaderTypeDef TxBatBmsOvr;
CAN_TxHeaderTypeDef TxBatExtTemp;
CAN_TxHeaderTypeDef TxBatGaugeOvr;
CAN_TxHeaderTypeDef TxBatGaugeVit;
CAN_TxHeaderTypeDef TxBrickAViT;
CAN_TxHeaderTypeDef TxBrickBViT;
CAN_TxHeaderTypeDef TxBrickCViT;
CAN_TxHeaderTypeDef TxBrickDViT;

CAN_RxHeaderTypeDef RxHeader;

uint32_t mailboxAFE;
uint32_t mailboxFuelGauge;
uint32_t mailboxBMS;

int toggle;
int count = 0;
uint32_t id;
uint8_t state[8];

void CreateQueue()
{
xQueue1 = xQueueCreate(uxQueueLength, uxItemSize);
if(xQueue1 == NULL)
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
}
}

void QueueEmpty()
{
	if( xQueueReceive( xQueue1, &ReceivedFrame, 0 ) == pdPASS )
	{
		HAL_CAN_AddTxMessage(&hcan1, &TxBrickAViT, ReceivedFrame->Data, &mailboxAFE);
		HAL_CAN_AddTxMessage(&hcan1, &TxBrickBViT, ReceivedFrame->Data, &mailboxAFE);
		HAL_CAN_AddTxMessage(&hcan1, &TxBrickCViT, ReceivedFrame->Data, &mailboxAFE);
		HAL_CAN_AddTxMessage(&hcan1, &TxBrickDViT, ReceivedFrame->Data, &mailboxAFE);
	}
	else
	{

	}
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	//HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_13);
}

void TxHeaderGeneratorBatBmsOvr()
{
	TxBatBmsOvr.DLC = BAT_BMS_OvrVIEW_DLC;
	TxBatBmsOvr.ExtId = 0;
	TxBatBmsOvr.IDE = CAN_ID_STD;
	TxBatBmsOvr.RTR = CAN_RTR_DATA;
	TxBatBmsOvr.StdId = BAT_BMS_OvrVIEW_CANID;
	TxBatBmsOvr.TransmitGlobalTime = DISABLE;
}

void TxHeaderGeneratorBatBmsExtTemp()
{
	TxBatExtTemp.DLC = BAT_BMS_ExtTemp_DLC;
	TxBatExtTemp.ExtId = 0;
	TxBatExtTemp.IDE = CAN_ID_STD;
	TxBatExtTemp.RTR = CAN_RTR_DATA;
	TxBatExtTemp.StdId = BAT_BMS_ExtTemp_CANID;
	TxBatExtTemp.TransmitGlobalTime = DISABLE;
}

void TxHeaderGeneratorBatGaugeOvr()
{
	TxBatGaugeOvr.DLC = BAT_GAUGE_OvrVIEW_DLC;
	TxBatGaugeOvr.ExtId = 0;
	TxBatGaugeOvr.IDE = CAN_ID_STD;
	TxBatGaugeOvr.RTR = CAN_RTR_DATA;
	TxBatGaugeOvr.StdId = BAT_GAUGE_OvrVIEW_CANID;
	TxBatGaugeOvr.TransmitGlobalTime = DISABLE;
}

void TxHeaderGeneratorBatGaugeViT()
{
	TxBatGaugeVit.DLC = BAT_GAUGE_ViT_DLC;
	TxBatGaugeVit.ExtId = 0;
	TxBatGaugeVit.IDE = CAN_ID_STD;
	TxBatGaugeVit.RTR = CAN_RTR_DATA;
	TxBatGaugeVit.StdId = BAT_GAUGE_ViT_CANID;
	TxBatGaugeVit.TransmitGlobalTime = DISABLE;
}

void TxHeaderGeneratorBatBrickAVit()
{
	TxBrickAViT.DLC = BAT_AFE_vBRICK_A_DLC;
	TxBrickAViT.ExtId = 0;
	TxBrickAViT.IDE = CAN_ID_STD;
	TxBrickAViT.RTR = CAN_RTR_DATA;
	TxBrickAViT.StdId = BAT_AFE_vBRICK_A_CANID;
	TxBrickAViT.TransmitGlobalTime = DISABLE;
}

void TxHeaderGeneratorBatBrickBVit()
{
	TxBrickBViT.DLC = BAT_AFE_vBRICK_B_DLC;
	TxBrickBViT.ExtId = 0;
	TxBrickBViT.IDE = CAN_ID_STD;
	TxBrickBViT.RTR = CAN_RTR_DATA;
	TxBrickBViT.StdId = BAT_AFE_vBRICK_B_CANID;
	TxBrickBViT.TransmitGlobalTime = DISABLE;
}

void TxHeaderGeneratorBatBrickCVit()
{
	TxBrickCViT.DLC = BAT_AFE_vBRICK_C_DLC;
	TxBrickCViT.ExtId = 0;
	TxBrickCViT.IDE = CAN_ID_STD;
	TxBrickCViT.RTR = CAN_RTR_DATA;
	TxBrickCViT.StdId = BAT_AFE_vBRICK_C_CANID;
	TxBrickCViT.TransmitGlobalTime = DISABLE;
}

void TxHeaderGeneratorBatBrickDVit()
{
	TxBrickDViT.DLC = BAT_AFE_vBRICK_D_DLC;
	TxBrickDViT.ExtId = 0;
	TxBrickDViT.IDE = CAN_ID_STD;
	TxBrickDViT.RTR = CAN_RTR_DATA;
	TxBrickDViT.StdId = BAT_AFE_vBRICK_D_CANID;
	TxBrickDViT.TransmitGlobalTime = DISABLE;
}

void RxHeaderGenerator()
{
	RxHeader.DLC = 8;
	RxHeader.ExtId = 0;
	RxHeader.IDE = CAN_ID_STD;
	RxHeader.RTR = CAN_RTR_REMOTE;
	RxHeader.StdId = 0x00;
}

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

struct CanFrame *msgPointer;

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
  RxHeaderGenerator();
  TxHeaderGeneratorBatGaugeOvr();
  TxHeaderGeneratorBatGaugeViT();
  TxHeaderGeneratorBatBmsOvr();
  TxHeaderGeneratorBatBmsExtTemp();
  TxHeaderGeneratorBatBrickAVit();
  TxHeaderGeneratorBatBrickBVit();
  TxHeaderGeneratorBatBrickCVit();
  TxHeaderGeneratorBatBrickDVit();

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
	TxHeaderGeneratorBatGaugeOvr();
	id = Pack_BAT_GAUGE_OvrVIEW_can_codegen(&batGaugeOvr, &canFrame);
	if(id == 0x1ff810)
	HAL_CAN_AddTxMessage(&hcan1, &TxBatGaugeOvr, canFrame.Data, &mailboxFuelGauge);
}

void writeCANBatGaugeViT()
{
	TxHeaderGeneratorBatGaugeViT();
	id = Pack_BAT_GAUGE_ViT_can_codegen(&batGaugeViT, &canFrame);
	if(id == 0x1ff820)
	HAL_CAN_AddTxMessage(&hcan1, &TxBatGaugeVit, canFrame.Data, &mailboxFuelGauge);
}

void writeBMSOvr()
{
	TxHeaderGeneratorBatBmsOvr();
	id = Pack_BAT_BMS_OvrVIEW_can_codegen(&batBmsOvr, &canFrame);
	if(id == 0x1ff610)
	HAL_CAN_AddTxMessage(&hcan1, &TxBatBmsOvr, canFrame.Data, &mailboxBMS);
}

void writeBMSExtTemp()
{
	TxHeaderGeneratorBatBmsExtTemp();
	id = Pack_BAT_BMS_ExtTemp_can_codegen(&batBmsExtTemp, &canFrame);
	if(id == 0x1ff611)
	HAL_CAN_AddTxMessage(&hcan1, &TxBatExtTemp, canFrame.Data, &mailboxBMS);
}

void writeAfeBrickAVt()
{
	TxHeaderGeneratorBatBrickAVit();
	id = Pack_BAT_AFE_vBRICK_A_can_codegen(&batAfeBrickA, &canFrame);
	if(id == 0x1ff710)
		xQueueSend(xQueue1,(void *)&msgPointer, (TickType_t)0);
}

void writeAfeBrickBVt()
{
	TxHeaderGeneratorBatBrickBVit();
	id = Pack_BAT_AFE_vBRICK_B_can_codegen(&batAfeBrickB, &canFrame);
	if(id == 0x1ff711)
		xQueueSend(xQueue1,(void *)&msgPointer, (TickType_t)0);
}

void writeAfeBrickCVt()
{
	TxHeaderGeneratorBatBrickCVit();
	id = Pack_BAT_AFE_vBRICK_C_can_codegen(&batAfeBrickC, &canFrame);
	if(id == 0x1ff712)
		xQueueSend(xQueue1,(void *)&msgPointer, (TickType_t)0);
}

void writeAfeBrickDVt()
{
	TxHeaderGeneratorBatBrickDVit();
	id = Pack_BAT_AFE_vBRICK_D_can_codegen(&batAfeBrickD, &canFrame);
	if(id == 0x1ff713)
		xQueueSend(xQueue1,(void *)&msgPointer, (TickType_t)0);
}

void readFCU_state()
{
	SetFilterConfig();
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
