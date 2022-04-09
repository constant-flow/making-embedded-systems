#if !defined(HEADER_LED)
#define HEADER_LED

// LED
#define LED_PIN GPIO_PIN_13
#define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOG_CLK_ENABLE();
#define LED_GPIO_PORT GPIOG

void LED_Init()
{
    LED_GPIO_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {
        .Pin = LED_PIN,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_PULLUP,
        .Speed = GPIO_SPEED_FREQ_HIGH};

    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}
void LED_Toggle()
{
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
}

#endif // HEADER_LED
