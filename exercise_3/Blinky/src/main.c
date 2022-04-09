#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f429xx.h"
#include <stdbool.h>

// Custom functionalities
#include "led.h"
#include "button_exti.h"
#include "fault_handling.h"

volatile uint32_t led_direct_read_val;
volatile uint32_t btn_direct_read_val;

int main(void)
{
    HAL_Init();

    // Initialize peripherals
    LED_Init();
    Button_Init_EXTI(LED_Toggle);

    while (1)
    {
        // reading the LED value directly from register (debug here to see)
        led_direct_read_val = ((*(uint32_t *)0x40021814) >> 13) & 0x1;

        // reading the BTN value directly from register (debug here to see)
        btn_direct_read_val = ((*(uint32_t *)0x40020010) >> 0) & 0x1;

        // Loop 4 ever ... so the program never ends
    }
}