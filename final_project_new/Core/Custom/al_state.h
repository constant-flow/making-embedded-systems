/**
 ******************************************************************************
 * @file           : al_state.h
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

#if !defined(HEADER_AL_STATE)
#define HEADER_AL_STATE

#include "stdint.h"

// set all states to default
void state_init();

// Tracking
void state_set_tracking_mode(int16_t newMode);
uint16_t state_get_tracking_mode();
void state_processed_tracking_mode_change();
int state_changed_tracking_mode();

// Sound detection
int state_set_tracking_threshold(int16_t newLevel);
int state_changed_tracking_threshold();
int16_t state_get_tracking_threshold();
void state_processed_tracking_threshold_change();
void state_tracking_mode_toggle();

#endif // HEADER_AL_STATE
