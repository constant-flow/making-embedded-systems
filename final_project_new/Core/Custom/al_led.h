/**
 ******************************************************************************
 * @file           : al_led.c
 * @brief          : Handles the onboard LEDs
 * @author         : Constantin Wolf
 ******************************************************************************
 */

#if !defined(HEADER_AL_LED)
#define HEADER_AL_LED

void al_led_init();
void al_led_all_off();
void al_led_green_toggle();

#endif // HEADER_AL_LED
