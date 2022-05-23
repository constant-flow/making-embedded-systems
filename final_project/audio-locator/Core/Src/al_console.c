#include "al_console.h"
#include <stm32f4xx_hal.h>
#include <stdbool.h>

extern UART_HandleTypeDef huart3;

#define MAX_BUFFER_LEN 10

uint8_t receivedChar = 0;
uint8_t receivedIndex = 0;
uint8_t receivedString[MAX_BUFFER_LEN];
const uint8_t *recvStr = receivedString;

bool dataAvailable = false;

void al_console_init()
{
    NVIC_EnableIRQ(USART3_IRQn);
    HAL_UART_Receive_IT(&huart3, &receivedChar, 1);
}

void al_console_print()
{
    if (dataAvailable)
    {
        HAL_UART_Transmit(&huart3, recvStr, receivedIndex, 1000);
        receivedIndex = 0;
        dataAvailable = false;
        receivedChar = '\0';
        for (int i = 0; i < MAX_BUFFER_LEN; i++)
            receivedString[i] = '-';
    }
}

void USART3_IRQHandler()
{
    dataAvailable = true;
    HAL_UART_IRQHandler(&huart3);

    receivedString[receivedIndex] = receivedChar;
    receivedIndex++;

    if (receivedChar == '\n')
        dataAvailable = true;
    if (receivedIndex >= MAX_BUFFER_LEN - 1)
        dataAvailable = true;
    HAL_UART_Receive_IT(&huart3, &receivedChar, 1);
}
