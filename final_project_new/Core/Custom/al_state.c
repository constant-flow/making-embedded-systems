/**
 ******************************************************************************
 * @file           : al_state.c
 * @brief          : Statemachine to toggle between tracking modes
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

#include "al_state.h"

struct audio_locator_state
{
    // 2D or 3D
    int16_t tracking_mode;
    // signals a change in tracking mode
    int16_t state_changed_tracking_mode;

    // how much do signals need to correlate to trigger a detection
    int16_t detector_level;
    int16_t detector_level_changed;
};

struct audio_locator_state state;

void state_init()
{
    state.tracking_mode = 1;
    state.state_changed_tracking_mode = 1;

    state.detector_level = 128;
    state.detector_level_changed = 1;
}

void state_set_tracking_mode(int16_t newMode)
{
    if (state.tracking_mode == newMode)
        return;
    if (newMode == 1 || newMode == 2)
    {
        state.state_changed_tracking_mode = 1;
        state.tracking_mode = newMode;
    }
}

uint16_t state_get_tracking_mode()
{
    return state.tracking_mode;
}

int state_changed_tracking_mode()
{
    return state.state_changed_tracking_mode;
}

void state_processed_tracking_mode_change()
{
    state.state_changed_tracking_mode = 0;
}

int state_set_tracking_threshold(int16_t newLevel)
{
    if (newLevel > 255 || newLevel < 0)
        return 0; // out of expected bounds

    state.detector_level = newLevel;
    state.detector_level_changed = 1;
    return 1;
}

int state_changed_tracking_threshold()
{
    return state.detector_level_changed;
}

void state_processed_tracking_threshold_change()
{
    state.detector_level_changed = 0;
}

int16_t state_get_tracking_threshold()
{
    return state.detector_level;
}

void state_tracking_mode_toggle()
{
    if (state_get_tracking_mode() == 2)
    {
        state_set_tracking_mode(1);
    }
    else
    {
        state_set_tracking_mode(2);
    }
}
