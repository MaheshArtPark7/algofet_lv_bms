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
#include "queue.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "dbccodeconf.h"
#include "can.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
struct CanFrame recievedData;

/* USER CODE END Variables */
osThreadId APP_1HZ_TASKHandle;
osThreadId APP_10HZ_TASKHandle;
osThreadId APP_100HZ_TASKHandle;
osMessageQId can_tx_queueHandle;
osMessageQId can_rx_queueHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

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

	/* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of can_tx_queue */
  osMessageQDef(can_tx_queue, 512, uint8_t);
  can_tx_queueHandle = osMessageCreate(osMessageQ(can_tx_queue), NULL);

  /* definition and creation of can_rx_queue */
  osMessageQDef(can_rx_queue, 512, uint8_t);
  can_rx_queueHandle = osMessageCreate(osMessageQ(can_rx_queue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of APP_1HZ_TASK */
  osThreadDef(APP_1HZ_TASK, app_task_1Hz, osPriorityNormal, 0, 128);
  APP_1HZ_TASKHandle = osThreadCreate(osThread(APP_1HZ_TASK), NULL);

  /* definition and creation of APP_10HZ_TASK */
  osThreadDef(APP_10HZ_TASK, app_task_10hz, osPriorityAboveNormal, 0, 128);
  APP_10HZ_TASKHandle = osThreadCreate(osThread(APP_10HZ_TASK), NULL);

  /* definition and creation of APP_100HZ_TASK */
  osThreadDef(APP_100HZ_TASK, app_task_100hz, osPriorityHigh, 0, 128);
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
    	writeAfeBrickAVt();
    	writeAfeBrickBVt();
    	writeAfeBrickCVt();
    	writeAfeBrickDVt();
		writeBMSExtTemp();
		writeCANBatGaugeOvr();
    	vTaskDelayUntil(&xLastWakeTime, xFrequency);
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
    if(counter%5==0)
    	readFCU_state();
    counter++;
    writeCANBatGaugeViT();
    writeBMSOvr();
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
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
    const TickType_t xFrequency = 10;
    xLastWakeTime = xTaskGetTickCount();
    /* Infinite loop */
    for (;;)
    {
    	QueueEmpty();
    	vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
  /* USER CODE END app_task_100hz */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
