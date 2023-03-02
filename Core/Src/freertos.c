/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can.h"
#include "can_codegen.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

extern void(*func_ptrs[8])();

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

uint32_t can_IDs[8] = {0x1ff610, 0x1ff611, 0x1ff710, 0x1ff711, 0x1ff712, 0x1ff713, 0x1ff810, 0x1ff820};

/* USER CODE END Variables */
osThreadId APP_1HZ_TASKHandle;
osThreadId APP_10HZ_TASKHandle;
osThreadId APP_100HZ_TASKHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
QueueHandle_t can_tx_queue,can_rx_queue;
/* USER CODE END FunctionPrototypes */

void app_task_1Hz(void const * argument);
void app_task_10hz(void const * argument);
void app_task_100hz(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

	can_tx_queue = xQueueCreate(10, sizeof(uint32_t)); //to be used to queue the messages being sent on CAN line
													//only 3 messages can be transmitted at once at the hardware level.
	can_rx_queue = xQueueCreate(10, sizeof(uint32_t));


	if(can_tx_queue != NULL)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	}

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of mutex_can_tx_queue */
  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of APP_1HZ_TASK */
  osThreadDef(APP_1HZ_TASK, app_task_1Hz, osPriorityNormal, 0, 128);
  APP_1HZ_TASKHandle = osThreadCreate(osThread(APP_1HZ_TASK), NULL);

  /* definition and creation of APP_10HZ_TASK */
  osThreadDef(APP_10HZ_TASK, app_task_10hz, osPriorityNormal, 0, 128);
  APP_10HZ_TASKHandle = osThreadCreate(osThread(APP_10HZ_TASK), NULL);

  /* definition and creation of APP_100HZ_TASK */
  osThreadDef(APP_100HZ_TASK, app_task_100hz, osPriorityNormal, 0, 128);
  APP_100HZ_TASKHandle = osThreadCreate(osThread(APP_100HZ_TASK), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_app_task_1Hz */
/**
 * @brief  Function implementing the APP_1HZ_TASK thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_app_task_1Hz */
void app_task_1Hz(void const * argument)
{
  /* USER CODE BEGIN app_task_1Hz */
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 1000;
    xLastWakeTime = xTaskGetTickCount();
    /* Infinite loop */
    for (;;)
    {
    	//xSemaphoreTake(can_task_semaphore_handle, 10);
    	for(int i = 1;i<7;i++)
    	{
    		xQueueSend(can_tx_queue, &can_IDs[i], (TickType_t)10);
    	}
    	vTaskDelayUntil(&xLastWakeTime, xFrequency);
    	//xSemaphoreGive(can_task_semaphore_handle);
    }

  /* USER CODE END app_task_1Hz */
}

/* USER CODE BEGIN Header_app_task_10hz */
/**
 * @brief Function implementing the APP_10HZ_TASK thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_app_task_10hz */
void app_task_10hz(void const * argument)
{
  /* USER CODE BEGIN app_task_10hz */
    TickType_t xLastWakeTime;
    uint16_t counter = 0;
    const TickType_t xFrequency = 100;
    xLastWakeTime = xTaskGetTickCount();
    /* Infinite loop */
    for (;;)
    {
    //xSemaphoreTake(can_task_semaphore_handle, 1000);
    if(counter%5==0)
    	can_fcu_read_data();
    counter++;
    xQueueSend(can_tx_queue, &can_IDs[0],(TickType_t)10); //GaugeVit
    xQueueSend(can_tx_queue, &can_IDs[7],(TickType_t)10); //BMS Ovr
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    //xSemaphoreGive(can_task_semaphore_handle);
    }


  /* USER CODE END app_task_10hz */
}

/* USER CODE BEGIN Header_app_task_100hz */
/**
 * @brief Function implementing the APP_100HZ_TASK thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_app_task_100hz */
void app_task_100hz(void const * argument)
{
  /* USER CODE BEGIN app_task_100hz */
    TickType_t xLastWakeTime;
    uint32_t* pReceive;
    const TickType_t xFrequency = 10;
    xLastWakeTime = xTaskGetTickCount();
    /* Infinite loop */
    for (;;)
    {
    		if(uxQueueMessagesWaiting(can_tx_queue) > 0)
    		{
    		//xSemaphoreTake(can_task_semaphore_handle, 10);
    		if(xQueueReceive(can_tx_queue, &pReceive, 100) == pdPASS)
    		{
    		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    		for(int i=0;i<9;i++)
    			{
    				if(pReceive == can_IDs[i])
    				{
    					(func_ptrs[i])();
    					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
    				}
    			}
    		}
    		}
    	vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
  /* USER CODE END app_task_100hz */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
