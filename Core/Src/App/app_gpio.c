/*
 * app_gpio.c
 *
 *  Created on: Aug 21, 2022
 */

#include "app_gpio.h"

void app_gpio_set_dfet(bool pinState)
{
    HAL_GPIO_WritePin(DFETOFF_OUT_GPIO_Port, DFETOFF_OUT_Pin, pinState);
}

void app_gpio_set_pwr5v(GPIO_PinState pinState)
{
    HAL_GPIO_WritePin(PWR5V_OUT_GPIO_Port, PWR5V_OUT_Pin, pinState);
}

void app_gpio_set_led1(GPIO_PinState pinState)
{
    HAL_GPIO_WritePin(LED1_OUT_GPIO_Port, LED1_OUT_Pin, pinState);
}

void app_gpio_set_led2(GPIO_PinState pinState)
{
    HAL_GPIO_WritePin(LED2_OUT_GPIO_Port, LED2_OUT_Pin, pinState);
}

void app_gpio_set_led3(GPIO_PinState pinState)
{
    HAL_GPIO_WritePin(LED3_OUT_GPIO_Port, LED3_OUT_Pin, pinState);
}

void app_gpio_set_led4(GPIO_PinState pinState)
{
    HAL_GPIO_WritePin(LED4_OUT_GPIO_Port, LED4_OUT_Pin, pinState);
}

GPIO_PinState app_gpio_get_btn_in(void)
{
    GPIO_PinState pinState;
    pinState = HAL_GPIO_ReadPin(BTN_IN_GPIO_Port, BTN_IN_Pin);
    return pinState;
}

GPIO_PinState app_gpio_get_afe_alert_in(void)
{
    GPIO_PinState pinState;
    pinState = HAL_GPIO_ReadPin(AFE_ALERT_IN_GPIO_Port, AFE_ALERT_IN_Pin);
    return pinState;
}
