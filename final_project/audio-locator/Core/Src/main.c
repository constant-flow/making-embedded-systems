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

/// BSP Documentation: https://documentation.help/STM32F469I-Discovery-BSP-Drivers

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

/* Custom non-generated functions --------------------------------------------*/
#include "console.h"
#include "state.h"
#include "al_display.h"
#include "al_led.h"
#include "al_stm_init.h"

/**
 * @brief  The application entry point.
 * @retval int
 */

int main(void)
{
  al_board_init();

  /* Init custom components */
  ConsoleInit();
  init_state();
  al_led_init();
  al_display_init();

  while (1)
  {
    al_led_green_toggle();
    al_display_update();

    ConsoleProcess();
    MX_USB_HOST_Process();

    if (changed_tracking_mode())
    {
      processed_tracking_mode_change();
      char buffer[32];
      sprintf(buffer, "Changed to %dD mode", get_tracking_mode());
      debugPrintlnUsart(buffer);
    }

    if (changed_tracking_threshold())
    {
      processed_tracking_threshold_change();
      char buffer[32];
      sprintf(buffer, "Threshold set to %d", get_tracking_threshold());
      debugPrintlnUsart(buffer);
    }

    HAL_Delay(1900);
  }
}