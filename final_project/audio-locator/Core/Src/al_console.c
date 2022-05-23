#include "al_console.h"
#include <stm32f4xx_hal.h>

extern UART_HandleTypeDef huart3;

void al_console_print()
{
    char *str = "hoi!";
    char recv = ".";
    HAL_UART_Transmit(&huart3, str, strlen(str), 1000);

    while (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == SET)
    {
        auto ret = HAL_UART_Receive(&huart3, &recv, 100, 100);
        if (HAL_OK != ret)
            break;

        HAL_UART_Transmit(&huart3, &recv, 1, 1000);

        // volatile int a = ;
    }
}