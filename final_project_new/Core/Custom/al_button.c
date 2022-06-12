/**
 ******************************************************************************
 * @file           : al_button.c
 * @brief          : Handles user button via Interrupt, calls registered 
 *                   callback
 * @author         : Constantin Wolf
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