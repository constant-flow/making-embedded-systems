/**
 ******************************************************************************
 * @file           : al_direction.h
 * @brief          : Processes PCM stream into direction of the loudest sound
 *                   above a definable threshold
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

#if !defined(HEADER_AL_DIRECTION)
#define HEADER_AL_DIRECTION

#include "al_mics.h"

// available tracking modes
enum al_tracking_mode
{
    MODE_UNINITIALIZED = 0,
    MODE_PCB_PLANE = 1,
    MODE_SCREEN_FRONT = 2
};

typedef enum al_tracking_mode tracking_mode;

// direction struct containing coordinates (x,y,z) and the used tracking mode (mode) e.g. 2D, 3D
// use type tracking_dir
struct al_tracking_direction
{
    float x;
    float y;
    float z;
    tracking_mode mode;
};

typedef struct al_tracking_direction tracking_dir;

// returns last calculated direction towards a loud noise
tracking_dir *direction_get();

// calculate (possibly) new direction
void direction_update();

// initializes parameters, resets the tracking dir and tracking mode
void direction_init();

void direction_input(mics_pcm_frame *input);

// sets the threshold how loud sounds needs to be to be detected (small = faster detected)
void direction_set_threshold(uint8_t threshold);

// sets the tracking plane
void direction_set_tracking_mode(enum al_tracking_mode mode);

#endif // HEADER_AL_DIRECTION
