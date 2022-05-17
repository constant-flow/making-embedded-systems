#include "al_led.h"
#include "stm32469i_discovery.h"

void al_led_init()
{
    BSP_LED_Off(LED1);
    BSP_LED_Off(LED2);
    BSP_LED_Off(LED3);
    BSP_LED_Off(LED4);
}

void al_led_green_toggle()
{
    BSP_LED_Toggle(LED1);
}