#include "al_main.h"

#include "al_button.h"
#include "al_direction.h"
#include "al_display.h"
#include "al_led.h"
#include "al_mics.h"
#include "al_state.h"
#include "al_logging.h"
#include "console.h"

// vars
mics_pcm_frame *pcm_frame = NULL;

// pre-defs
void bsp_test_screen();
void led_toggle();

// audio locator init all variables and peripherals
void al_init()
{
    bsp_test_screen();
    ConsoleInit();
    state_init();
    al_led_init();
    al_display_init();
    button_init(led_toggle);

    direction_reset();
    display_set_tracking(direction_get());
    mics_init();
}

void al_loop()
{
    mics_update();
    pcm_frame = mic_get_sample();
    display_set_audio(pcm_frame);

    direction_update();
    al_led_green_toggle();
    al_display_update();

    ConsoleProcess();

    if (state_changed_tracking_mode())
    {
      state_processed_tracking_mode_change();
      char buffer[32];
      logging_log("Changed to %dD mode", state_get_tracking_mode());      

      // Show state via LED // TODO make led code independent via al_led.h
      al_led_all_off();
      if (state_get_tracking_mode() == 2)
        BSP_LED_On(LED2);
      if (state_get_tracking_mode() == 3)
        BSP_LED_On(LED3);
    }

    if (state_changed_tracking_threshold())
    {
      state_processed_tracking_threshold_change();
      char buffer[32];
      logging_log("Threshold set to %d", state_get_tracking_threshold());      
    }
}

void bsp_test_screen()
{
    if (BSP_LCD_Init() == LCD_ERROR)
    {
        /* Initialization Error */
        Error_Handler();
    }

    BSP_LCD_SelectLayer(0);
    BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);

    uint32_t screen_width = BSP_LCD_GetXSize();
    uint32_t screen_height = BSP_LCD_GetYSize();

    BSP_LCD_SetTextColor(0xff000000);
    BSP_LCD_FillRect(0, 0, screen_width, screen_height);

    BSP_LCD_DisplayStringAt(0, 240 - 65, (uint8_t *)"Audio Locator", CENTER_MODE);
}

void led_toggle()
{
  state_tracking_mode_toggle();
}