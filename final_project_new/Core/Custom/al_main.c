/**
 ******************************************************************************
 * @file           : al_main.c
 * @brief          : Main business logic of audio locator
 * @author         : Constantin Wolf
 * 
 * MIT License
 *
 * Copyright (c) 2022 Constantin Wolf
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************
 */

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
void toggle_tracking_mode();
void handle_state();

// audio locator init all variables and peripherals
void al_init()
{
    ConsoleInit();
    state_init();
    al_led_init();
    al_display_init();
    direction_init();
    button_init(toggle_tracking_mode);

    display_set_tracking(direction_get());
    mics_init();
}

void al_loop()
{
    pcm_frame = mic_get_sample();
    if (pcm_frame->is_new_sample)
    {
        display_set_audio(pcm_frame);
        direction_input(pcm_frame);
        direction_update();
        al_display_update();
    }

    al_led_green_toggle();

    ConsoleProcess();
    handle_state();
}

void handle_state()
{
    if (state_changed_tracking_mode())
    {
        state_processed_tracking_mode_change();
        logging_log("Changed to tracking mode: %d", state_get_tracking_mode());
        direction_set_tracking_mode(state_get_tracking_mode());

        // Show state via LED // TODO make led code independent via al_led.h
        al_led_all_off();
        if (state_get_tracking_mode() == 1)
            BSP_LED_On(LED2);
        if (state_get_tracking_mode() == 2)
            BSP_LED_On(LED3);
    }

    if (state_changed_tracking_threshold())
    {
        state_processed_tracking_threshold_change();
        logging_log("Threshold set to %d", state_get_tracking_threshold());
        direction_set_threshold(state_get_tracking_threshold());
    }
}

void toggle_tracking_mode()
{
    state_tracking_mode_toggle();
}