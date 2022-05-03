// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include <string.h>

#include <stm32f4xx_hal.h>
#include <stm32f469xx.h>

// use the windows conio.h for kbhit, or a POSIX reproduction
// #ifdef _WIN32
// #include <conio.h>
// #else
// #include "conioCompat.h"
// #endif

#define NO_CHAR_AVAILABLE -1

UART_HandleTypeDef uartCli;

void debugPrintln(UART_HandleTypeDef *huart, char _out[])
{
    HAL_UART_Transmit(huart, (uint8_t *)_out, strlen(_out), 10);
    char newline[2] = "\r\n";
    HAL_UART_Transmit(huart, (uint8_t *)newline, 2, 10);
}

// void Error_Handler(void)
// {
//     /* USER CODE BEGIN Error_Handler_Debug */
//     /* User can add his own implementation to report the HAL error return state */
//     __disable_irq();
//     while (1)
//     {
//     }
//     /* USER CODE END Error_Handler_Debug */
// }

eConsoleError ConsoleIoInit(void)
{
    __USART3_CLK_ENABLE();

    // uartCli.Instance = USART3;
    // uartCli.Init.BaudRate = 115200;
    // uartCli.Init.WordLength = UART_WORDLENGTH_8B;
    // uartCli.Init.StopBits = UART_STOPBITS_1;
    // uartCli.Init.Parity = UART_PARITY_NONE;
    // uartCli.Init.Mode = UART_MODE_TX_RX;
    // uartCli.Init.HwFlowCtl = UART_HWCONTROL_NONE;

    uartCli.Instance = USART3;
    uartCli.Init.BaudRate = 115200;
    uartCli.Init.WordLength = UART_WORDLENGTH_8B;
    uartCli.Init.StopBits = UART_STOPBITS_1;
    uartCli.Init.Parity = UART_PARITY_NONE;
    uartCli.Init.Mode = UART_MODE_TX_RX;
    uartCli.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uartCli.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_StatusTypeDef ret = HAL_UART_Init(&uartCli);

    if (HAL_UART_Init(&uartCli) != HAL_OK)
    {
        // Error_Handler();
        return HAL_ERROR;
    }

    debugPrintln(&uartCli, "hello2");

    return ret;
}

static int getch_noblock()
{
    uint8_t one_char_buffer;
    HAL_StatusTypeDef ret = HAL_UART_Receive(&uartCli, &one_char_buffer, 1, 1000);

    if (ret == HAL_ERROR)
    {
        ConsoleIoSendString("asd");
        return NO_CHAR_AVAILABLE;
    }
    return one_char_buffer;
}

uint8_t UART1_rxBuffer[12] = {0};

eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{
    // uint32_t i = 0;
    // char ch;

    // ch = getch_noblock();
    // while ((ch != NO_CHAR_AVAILABLE) && (i < bufferLength))
    // {
    //     buffer[i] = (uint8_t)ch;
    //     i++;
    //     ch = getch_noblock();
    // }
    // *readLength = i;
    // return CONSOLE_SUCCESS;

    uint32_t i = 0;
    u_int8_t ch;

    while (__HAL_UART_GET_FLAG(&uartCli, UART_FLAG_RXNE) == SET)
    {
        HAL_UART_Receive(&uartCli, &ch, 1, 0);
        // HAL_UART_Transmit(&uartCli, &ch, 1, 10);
        buffer[i] = ch;
        i++;
    }

    *readLength = i;
    return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
    int len = strlen(buffer);
    // HAL_UART_Transmit_IT(&uartCli, (unsigned char *)buffer, len);
    HAL_UART_Transmit(&uartCli, (unsigned char *)buffer, len, 1000);
    return CONSOLE_SUCCESS;
}