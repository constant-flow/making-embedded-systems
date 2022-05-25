/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/// BSP Documentation: https://documentation.help/STM32F469I-Discovery-BSP-Drivers/

#include "main.h"
#include "crc.h"
#include "dma2d.h"
#include "dsihost.h"
#include "fatfs.h"
#include "i2c.h"
#include "libjpeg.h"
#include "ltdc.h"
#include "pdm2pcm.h"
#include "quadspi.h"
#include "sai.h"
#include "sdio.h"
#include "tim.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"
#include "fmc.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "stm32469i_discovery.h"

/* Custom non-generated functions --------------------------------------------*/
#include "console.h"
#include "al_state.h"
#include "al_display.h"
#include "al_led.h"
#include "al_stm_init.h"
#include "al_button.h"
#include "al_direction.h"

int global_init = 1;
int global_uninit;

// ============================================================================
// Tests/Section macros to enable for debugging and other applications
// ----------------------------------------------------------------------------
//
// #define AL_TEST_VAR_LOCATIONS
// ============================================================================

#ifdef AL_TEST_VAR_LOCATIONS
void mem_test()
{
  static int static_var_in_function = 2;
  int var_in_function_1 = 3;
  int var_in_function_2 = 3;

  volatile int adr_global_init = &global_init;
  volatile int adr_global_uninit = &global_uninit;
  volatile int adr_static_var = &static_var_in_function;
  volatile int adr_local_var_1 = &var_in_function_1;
  volatile int adr_local_var_2 = &var_in_function_2;
  volatile int adr_heap_1 = malloc(1);
  volatile int adr_heap_2 = malloc(1);
  volatile int adr_stack_1 = adr_local_var_1;
  volatile int adr_stack_2 = adr_local_var_2;
}
#endif

/**
 * @brief  The application entry point.
 * @retval int
 */

void led_toooogle()
{
  state_tracking_mode_toggle();
}

int main(void)
{
  al_board_init();

#ifdef AL_TEST_VAR_LOCATIONS
  mem_test();
#endif

  /* Init custom components */
  ConsoleInit();
  state_init();
  al_led_init();
  al_display_init();
  button_init(led_toooogle);
  direction_reset();
  display_set_tracking(direction_get());

  while (1)
  {
    direction_update();
    al_led_green_toggle();
    al_display_update();

    ConsoleProcess();
    MX_USB_HOST_Process();

    if (state_changed_tracking_mode())
    {
      state_processed_tracking_mode_change();
      char buffer[32];
      sprintf(buffer, "Changed to %dD mode", state_get_tracking_mode());
      debugPrintlnUsart(buffer);

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
      sprintf(buffer, "Threshold set to %d", state_get_tracking_threshold());
      debugPrintlnUsart(buffer);
    }

    HAL_Delay(10);
  }
}