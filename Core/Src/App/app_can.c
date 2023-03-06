/*
 * app_can.c
 *
 *  Created on: Aug 21, 2022
 */

#include "app_can.h"
#include "can.h"


CAN_FilterTypeDef filterConfig;


__CoderDbcCanFrame_t__ canFrame;
// structure objects
extern fcuState;
extern batBmsOvr;
extern batBmsExtTemp;
extern batAfeBrickA;
extern batAfeBrickB;
extern batAfeBrickC;
extern batAfeBrickD;
extern batGaugeOvr;
extern batGaugeViT;

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

int16_t app_can_tx_header_bat_bms_ovr();
int16_t app_can_tx_header_bat_bms_ext_temp();
int16_t app_can_tx_header_bat_gauge_ovr();
int16_t app_can_tx_header_bat_gauge_Vit();
int16_t app_can_tx_header_bat_brickA_Vit();
int16_t app_can_tx_header_bat_brickB_Vit();
int16_t app_can_tx_header_bat_brickC_Vit();
int16_t app_can_tx_header_bat_brickD_Vit();
int16_t app_can_rx_header_fcu_state();
int16_t app_can_set_filter_config();

int16_t app_can_send_tx_msg(uint32_t canId);

int16_t app_can_bat_gauge_ovr_write_data(void);
int16_t app_can_bat_gauge_vit_write_data(void);
int16_t app_can_bms_ovr_write_data(void);
int16_t app_can_bms_exttemp_write_data(void);
int16_t app_can_bat_afe_brickA_write_data(void);
int16_t app_can_bat_afe_brickB_write_data(void);
int16_t app_can_bat_afe_brickC_write_data(void);
int16_t app_can_bat_afe_brickD_write_data(void);

int16_t(*func_ptrs[8])() = {app_can_bat_gauge_ovr_write_data,
                         app_can_bat_gauge_vit_write_data,
						 app_can_bms_ovr_write_data,
						 app_can_bms_exttemp_write_data,
						 app_can_bat_afe_brickA_write_data,
						 app_can_bat_afe_brickB_write_data,
						 app_can_bat_afe_brickC_write_data,
						 app_can_bat_afe_brickD_write_data};

uint32_t can_IDs[8] = {0x1ff610, 0x1ff611, 0x1ff710,
		               0x1ff711, 0x1ff712, 0x1ff713,
					   0x1ff810, 0x1ff820};

uint32_t mailbox1Hz;
uint32_t mailbox10Hz;
uint32_t mailbox100Hz;

int toggle;
int count = 0;
uint32_t id;
uint8_t state[8];

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    //HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_13);
}

int16_t app_can_tx_header_bat_bms_ovr()
{
    TxBatBmsOvr.DLC = BAT_BMS_OvrVIEW_DLC;
    TxBatBmsOvr.ExtId = 0;
    TxBatBmsOvr.IDE = CAN_ID_STD;
    TxBatBmsOvr.RTR = CAN_RTR_DATA;
    TxBatBmsOvr.StdId = BAT_BMS_OvrVIEW_CANID;
    TxBatBmsOvr.TransmitGlobalTime = DISABLE;
}

int16_t app_can_tx_header_bat_bms_ext_temp()
{
    TxBatExtTemp.DLC = BAT_BMS_ExtTemp_DLC;
    TxBatExtTemp.ExtId = 0;
    TxBatExtTemp.IDE = CAN_ID_STD;
    TxBatExtTemp.RTR = CAN_RTR_DATA;
    TxBatExtTemp.StdId = BAT_BMS_ExtTemp_CANID;
    TxBatExtTemp.TransmitGlobalTime = DISABLE;
}

int16_t app_can_tx_header_bat_gauge_ovr()
{
    TxBatGaugeOvr.DLC = BAT_GAUGE_OvrVIEW_DLC;
    TxBatGaugeOvr.ExtId = 0;
    TxBatGaugeOvr.IDE = CAN_ID_STD;
    TxBatGaugeOvr.RTR = CAN_RTR_DATA;
    TxBatGaugeOvr.StdId = BAT_GAUGE_OvrVIEW_CANID;
    TxBatGaugeOvr.TransmitGlobalTime = DISABLE;
}

int16_t app_can_tx_header_bat_gauge_Vit()
{
    TxBatGaugeVit.DLC = BAT_GAUGE_ViT_DLC;
    TxBatGaugeVit.ExtId = 0;
    TxBatGaugeVit.IDE = CAN_ID_STD;
    TxBatGaugeVit.RTR = CAN_RTR_DATA;
    TxBatGaugeVit.StdId = BAT_GAUGE_ViT_CANID;
    TxBatGaugeVit.TransmitGlobalTime = DISABLE;
}

int16_t app_can_tx_header_bat_brickA_Vit()
{
    TxBrickAViT.DLC = BAT_AFE_vBRICK_A_DLC;
    TxBrickAViT.ExtId = 0;
    TxBrickAViT.IDE = CAN_ID_STD;
    TxBrickAViT.RTR = CAN_RTR_DATA;
    TxBrickAViT.StdId = BAT_AFE_vBRICK_A_CANID;
    TxBrickAViT.TransmitGlobalTime = DISABLE;
}

int16_t app_can_tx_header_bat_brickB_Vit()
{
    TxBrickBViT.DLC = BAT_AFE_vBRICK_B_DLC;
    TxBrickBViT.ExtId = 0;
    TxBrickBViT.IDE = CAN_ID_STD;
    TxBrickBViT.RTR = CAN_RTR_DATA;
    TxBrickBViT.StdId = BAT_AFE_vBRICK_B_CANID;
    TxBrickBViT.TransmitGlobalTime = DISABLE;
}

int16_t app_can_tx_header_bat_brickC_Vit()
{
    TxBrickCViT.DLC = BAT_AFE_vBRICK_C_DLC;
    TxBrickCViT.ExtId = 0;
    TxBrickCViT.IDE = CAN_ID_STD;
    TxBrickCViT.RTR = CAN_RTR_DATA;
    TxBrickCViT.StdId = BAT_AFE_vBRICK_C_CANID;
    TxBrickCViT.TransmitGlobalTime = DISABLE;
}

int16_t tx_header_bat_brickD_vit()
{
    TxBrickDViT.DLC = BAT_AFE_vBRICK_D_DLC;
    TxBrickDViT.ExtId = 0;
    TxBrickDViT.IDE = CAN_ID_STD;
    TxBrickDViT.RTR = CAN_RTR_DATA;
    TxBrickDViT.StdId = BAT_AFE_vBRICK_D_CANID;
    TxBrickDViT.TransmitGlobalTime = DISABLE;
}

int16_t app_can_rx_header_fcu_state()
{
    RxHeader.DLC = 8;
    RxHeader.ExtId = 0;
    RxHeader.IDE = CAN_ID_STD;
    RxHeader.RTR = CAN_RTR_REMOTE;
    RxHeader.StdId = 0x00;
}

int16_t app_can_set_filter_config()
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

int16_t app_can_send_tx_msg(uint32_t canId)
{
	for(int i=0; i<9; i++)
	{
		if(canId == can_IDs[i])
		{
			(func_ptrs[i])();
		}
	}
}
int16_t app_can_bat_gauge_ovr_write_data(void)
{
    app_can_tx_header_bat_gauge_ovr();
    Pack_BAT_GAUGE_OvrVIEW_can_codegen(&batGaugeOvr, &canFrame);
    HAL_CAN_AddTxMessage(&hcan1, &TxBatGaugeOvr, canFrame.Data, &mailbox1Hz);
}

int16_t app_can_bat_gauge_vit_write_data(void)
{
    app_can_tx_header_bat_gauge_Vit();
    Pack_BAT_GAUGE_ViT_can_codegen(&batGaugeViT, &canFrame);
    HAL_CAN_AddTxMessage(&hcan1, &TxBatGaugeVit, canFrame.Data, &mailbox10Hz);
}

int16_t app_can_bms_ovr_write_data(void)
{
    app_can_tx_header_bat_bms_ovr();
    Pack_BAT_BMS_OvrVIEW_can_codegen(&batBmsOvr, &canFrame);
    HAL_CAN_AddTxMessage(&hcan1, &TxBatBmsOvr, canFrame.Data, &mailbox10Hz);
}

int16_t app_can_bms_exttemp_write_data(void)
{
    app_can_tx_header_bat_bms_ext_temp();
    Pack_BAT_BMS_ExtTemp_can_codegen(&batBmsExtTemp, &canFrame);
    HAL_CAN_AddTxMessage(&hcan1, &TxBatExtTemp, canFrame.Data, &mailbox1Hz);
}

int16_t app_can_bat_afe_brickA_write_data(void)
{
    app_can_tx_header_bat_brickA_Vit();
    Pack_BAT_AFE_vBRICK_A_can_codegen(&batAfeBrickA, &canFrame);
    HAL_CAN_AddTxMessage(&hcan1, &TxBrickAViT, canFrame.Data, &mailbox1Hz);
}

int16_t app_can_bat_afe_brickB_write_data(void)
{
    app_can_tx_header_bat_brickB_Vit();
    Pack_BAT_AFE_vBRICK_B_can_codegen(&batAfeBrickB, &canFrame);
    HAL_CAN_AddTxMessage(&hcan1, &TxBrickBViT, canFrame.Data, &mailbox1Hz);
}

int16_t app_can_bat_afe_brickC_write_data(void)
{
    app_can_tx_header_bat_brickC_Vit();
    Pack_BAT_AFE_vBRICK_C_can_codegen(&batAfeBrickC, &canFrame);
    HAL_CAN_AddTxMessage(&hcan1, &TxBrickCViT, canFrame.Data, &mailbox1Hz);
}

int16_t app_can_bat_afe_brickD_write_data(void)
{
    tx_header_bat_brickD_vit();
    Pack_BAT_AFE_vBRICK_D_can_codegen(&batAfeBrickD, &canFrame);
    HAL_CAN_AddTxMessage(&hcan1, &TxBrickDViT, canFrame.Data, &mailbox1Hz);
}

int16_t app_can_fcu_read_data()
{
    app_can_set_filter_config();
    if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, state) == HAL_OK)
    {
        id = Unpack_FCU_STATE_REQUEST_can_codegen(&fcuState, &state, 1);
	    switch (state[0])
	    {
			case 0:
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
				bq76952_FETs_OFF(); // replace with all fets off function call
				break;
			case 1:
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
				bq76952_FETs_ON(); //replace with all fets on function call
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
				bq76952_AFE_reset();// replace with afe reset function call
				break;
			case 3:
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
				bq76952_Charge();
				break;
			case 4:
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
				bq76952_Discharge();
				break;
			default:
				break;
		}
    }
}
