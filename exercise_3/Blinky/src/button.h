#if !defined(HEADER_USER_BUTTON)
#define HEADER_USER_BUTTON

#define USER_BUTTON_PIN GPIO_PIN_0
#define USER_BUTTON_GPIO_PORT GPIOA
#define BUTTON_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE();

// interrupt: EXTI0

void Button_Init()
{
    BUTTON_GPIO_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {
        .Pin = USER_BUTTON_PIN,
        .Mode = GPIO_MODE_INPUT,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_HIGH};

    HAL_GPIO_Init(USER_BUTTON_GPIO_PORT, &GPIO_InitStruct);
}

int Button_Pressed()
{
    int val = HAL_GPIO_ReadPin(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN);
    return val;
}

#endif // HEADER_USER_BUTTON
