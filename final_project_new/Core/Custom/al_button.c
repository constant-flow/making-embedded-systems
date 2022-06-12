/**
 ******************************************************************************
 * @file           : al_button.c
 * @brief          : Handles user button via Interrupt, calls registered 
 *                   callback
 * @author         : Constantin Wolf
 * 
 * MIT License
 *
 * Copyright (c) 2022 Constantin Wolf
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 ******************************************************************************
 */

#include "al_button.h"
#include "stm32f4xx_hal.h"
#include "stm32469i_discovery.h"

static void (*button_callback)(void) = 0;

void button_init(void (*callback)(void))
{
    button_callback = callback;
    BUTTON_GPIO_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {
        .Pin = USER_BUTTON_PIN,
        .Mode = GPIO_MODE_IT_RISING,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_HIGH};

    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    HAL_GPIO_Init(USER_BUTTON_GPIO_PORT, &GPIO_InitStruct);
}

void EXTI0_IRQHandler()
{
    if (button_callback)
    {
        button_callback();
    }

    // clear interrupt flag
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}