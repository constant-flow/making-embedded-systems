#include "stm32f4xx_hal.h"
#include "stm32f429xx.h"
#include <stdbool.h>

// Custom functionalities
#include "led.h"
#include "button.h"
#include "fault_handling.h"

int main(void)
{
    bool blinking_active = false;

    HAL_Init();

    // Initialize peripherals
    LED_Init();
    Button_Init();

    while (1)
    {
        if (blinking_active)
        {
            LED_Toggle();
            HAL_Delay(100);
        }

        if (Button_Pressed())
        {
            blinking_active = !blinking_active;
            HAL_Delay(100); // lazy debounce
        }
    }
}