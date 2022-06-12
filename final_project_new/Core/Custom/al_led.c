/**
 ******************************************************************************
 * @file           : al_led.h
 * @brief          : Handles the onboard LEDs
 * @author         : Constantin Wolf
 ******************************************************************************
 */

#include "al_led.h"
#include "stm32469i_discovery.h"

void al_led_init()
{
    al_led_all_off();
}

void al_led_all_off()
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