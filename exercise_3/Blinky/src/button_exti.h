#if !defined(HEADER_USER_BUTTON_EXTI)
#define HEADER_USER_BUTTON_EXTI

#define USER_BUTTON_PIN GPIO_PIN_0
#define USER_BUTTON_GPIO_PORT GPIOA
#define BUTTON_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE();

void (*button_callback)(void) = 0;

void Button_Init_EXTI(void (*callback)(void))
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

#endif // HEADER_USER_BUTTON_EXTI
