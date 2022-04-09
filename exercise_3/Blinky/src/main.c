#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f429xx.h"
#include <stdbool.h>

// Custom functionalities
#include "led.h"
#include "button_exti.h"
#include "fault_handling.h"

int main(void)
{
    HAL_Init();

    // Initialize peripherals
    LED_Init();
    Button_Init_EXTI(LED_Toggle);

    while (1)
    {
        // Loop 4 ever ... so the program never ends
    }
}