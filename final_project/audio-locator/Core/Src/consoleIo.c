// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include <string.h>

#include <stm32f4xx_hal.h>
#include <stm32f469xx.h>

extern UART_HandleTypeDef huart3;

void debugPrintln(UART_HandleTypeDef *huart, char _out[])
{
    HAL_UART_Transmit(huart, (uint8_t *)_out, strlen(_out), 10);
    char newline[2] = "\r\n";
    HAL_UART_Transmit(huart, (uint8_t *)newline, 2, 10);
}

eConsoleError ConsoleIoInit(void)
{
    // Enable the USART RX Interrupt
    // NVIC_EnableIRQ(USART3_IRQn);
    return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{
    // uint32_t i = 0;
    // char ch;

    // ch = getch_noblock();
    // while ((EOF != ch) && (i < bufferLength))
    // {
    //     buffer[i] = (uint8_t)ch;
    //     i++;
    //     ch = getch_noblock();
    // }
    // *readLength = i;

    *readLength = 0;
    return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
    // HAL_UART_Transmit(&huart3, &receivedChar, 1, 1000);
    return CONSOLE_SUCCESS;
}