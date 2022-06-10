// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include <string.h>

#include <stm32f4xx_hal.h>
#include <stm32f469xx.h>
#include <stdbool.h>

extern UART_HandleTypeDef huart3;

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX_BUFFER_LEN 10

uint8_t receivedChar = 0;
uint8_t receivedIndex = 0;
uint8_t receivedString[MAX_BUFFER_LEN];
const uint8_t *recvStr = receivedString;

bool dataAvailable = false;

void debugPrintln(UART_HandleTypeDef *huart, char _out[])
{
    HAL_UART_Transmit(huart, (uint8_t *)_out, strlen(_out), 10);
    char newline[2] = "\r\n";
    HAL_UART_Transmit(huart, (uint8_t *)newline, 2, 10);
}

eConsoleError ConsoleIoInit(void)
{
    NVIC_EnableIRQ(USART3_IRQn);
    HAL_UART_Receive_IT(&huart3, &receivedChar, 1);
    return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{
    if (dataAvailable)
    {
        uint8_t lengthOfBuffer = MIN(bufferLength, receivedIndex);
        memcpy(buffer, receivedString, lengthOfBuffer);
        *readLength = lengthOfBuffer;

        // Reset string capturing vars
        receivedIndex = 0;
        dataAvailable = false;
        receivedChar = '\0';
        for (int i = 0; i < MAX_BUFFER_LEN; i++)
            receivedString[i] = '-';
    }
    else
    {
        *readLength = 0;
    }
    return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
    HAL_UART_Transmit(&huart3, (uint8_t *)buffer, strlen(buffer), 1000);
    return CONSOLE_SUCCESS;
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