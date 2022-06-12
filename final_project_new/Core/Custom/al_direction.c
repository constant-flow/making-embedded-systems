/**
 ******************************************************************************
 * @file           : al_direction.c
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

#include "al_direction.h"
#include "al_logging.h"

#include "arm_math.h"
#include "main.h"

/*****************************************************************************/
// Debugging parameters
/*****************************************************************************/
// test output without audio processing for debugging the visual output
// #define USE_GENERATED_SINE_INPUT

// halts the process after first correlation, to enable complex console prints
// #define HALT_AFTER_FIRST_SAMPLE
/*****************************************************************************/

// correlation threshold
#define MIN_DETECTION_THRESHOLD 0.1f
#define MAX_DETECTION_THRESHOLD 5.0f


static tracking_dir tracking_result = {0.0f, 0.0f, 0.0f, MODE_UNINITIALIZED};

// Incoming pcm data of both microphones
static mics_pcm_frame *microphones_pcm_data;

// Currently set threshold to overcome to be detected
static float detection_threshold = MIN_DETECTION_THRESHOLD;

// Last angle towards signal
static float angle_target = 0;
// Smoothed angle towards signal
static float angle_smoothed = 0;
// Smoothening factor to reduce jitter
static float angle_target_smoothing = 0.99f;

// distance between microphones in cm
#define MICS_DISTANCE 12.4f
#define MICS_BASELINE_TO_SCREEN_ANGLE (tan(1.8f / 11.7f) - PI / 2)

// in cm/s
#define SPEED_OF_SOUND 34300

// how far (in cm) did a soundwave travel one sample later ()
#define DIST_BETWEEN_SAMPLES ((float)SPEED_OF_SOUND / DEFAULT_AUDIO_IN_FREQ)

// buffer for the correlation results
#define CORR_BUF_SIZE (PCM_BUF_SIZE_HALF * 2 - 1)

// holds multiple infos about the correlation: 
//  - phase shift between signals
//  - max correlation between signals
//  - mid of the buffer 
typedef struct pcm_correlation
{
    int16_t max_shift_samples; // how many samples were the the two signals phase shifted
    uint16_t max_val;          // how much did they correlate
    uint16_t mid_id;           // which sample id in the correlation means
                               //`phase shift` = 0 (both signals came at the same time)
} pcm_correlation;

static pcm_correlation corr;
static float32_t channel_right[PCM_BUF_SIZE_HALF];
static float32_t channel_left[PCM_BUF_SIZE_HALF];
static float32_t result_corr[CORR_BUF_SIZE];

// returns the tracking result
tracking_dir *direction_get()
{
    return &tracking_result;
}

inline float toFloat(uint16_t val)
{
    return ((float32_t)val) / ((float32_t)UINT16_MAX) - 0.5f;
}

// splits input audio from interleaved uint16_t signal into two float buffers
void calc_float_channels(mics_pcm_frame *input)
{
    for (int i = 0; i < PCM_BUF_SIZE_HALF; i++)
    {
        channel_left[i] = toFloat(input->samples[i * 2]);
        channel_right[i] = toFloat(input->samples[i * 2 + 1]);
        // logging_log("%d : %f\t|\t%d : %f", input->samples[i * 2], channel_left[i], input->samples[i * 2 + 1], channel_right[i]);
    }
}

// checks the input for loud enough correlation and if so, updates the corr object
void get_correlation(mics_pcm_frame *input, pcm_correlation *corr)
{
    calc_float_channels(input);

    arm_correlate_f32(channel_left, PCM_BUF_SIZE_HALF, channel_right, PCM_BUF_SIZE_HALF, result_corr);

    float32_t max_corr_value = -100;
    uint8_t max_corr_id = 0;

    for (int i = 0; i < CORR_BUF_SIZE; i++)
    {
        // logging_log("i=%d : \t '%d' '%f'", i, (int16_t)(result_corr[i] * 128), result_corr[i]);

        if (result_corr[i] > max_corr_value)
        {
            max_corr_id = i;
            max_corr_value = result_corr[i];
        }
    }

    if (max_corr_value > detection_threshold)
    {
        // logging_log("corr above threshold");
        corr->max_shift_samples = max_corr_id;
        corr->max_val = max_corr_value;
    }
}

void direction_init()
{
    tracking_result.x = 1;
    tracking_result.y = 0;
    tracking_result.z = 0;
    tracking_result.mode = MODE_SCREEN_FRONT;
    corr.mid_id = CORR_BUF_SIZE / 2;
}

void direction_update()
{
#ifdef USE_GENERATED_SINE_INPUT
    float time = HAL_GetTick() / 1000.f;
    tracking_result.x = sin(time);
    tracking_result.y = cos(time);
    return;
#endif

    get_correlation(microphones_pcm_data, &corr);

    // keep in bounds (-90° to 90°)
    int16_t shifted_sample_amount = corr.max_shift_samples - corr.mid_id;
    float delayed_distance = shifted_sample_amount * DIST_BETWEEN_SAMPLES;
    // logging_log("→ Shifted by %d sample\tdist: %f", shifted_sample_amount, delayed_distance);
    if (delayed_distance > MICS_DISTANCE)
        delayed_distance = MICS_DISTANCE;
    if (delayed_distance < -MICS_DISTANCE)
        delayed_distance = -MICS_DISTANCE;

    float angle = acos(delayed_distance / MICS_DISTANCE);

    float corrected_angle = angle + MICS_BASELINE_TO_SCREEN_ANGLE;

    angle_target = corrected_angle;

    angle_smoothed = angle_target * (1 - angle_target_smoothing) + angle_smoothed * angle_target_smoothing;

    tracking_result.x = sin(angle_smoothed);
    tracking_result.y = cos(angle_smoothed);

#ifdef HALT_AFTER_FIRST_SAMPLE
    static int halt_after_sample = 0;
    if (halt_after_sample++)
        Error_Handler();
#endif
}

void direction_input(mics_pcm_frame *input)
{
    microphones_pcm_data = input;
}

void direction_set_threshold(uint8_t threshold)
{
    detection_threshold = ((float)threshold) / 255 * (MAX_DETECTION_THRESHOLD - MIN_DETECTION_THRESHOLD) + MIN_DETECTION_THRESHOLD;
    logging_log("Mic: threshold now: %f", detection_threshold);
}

void direction_set_tracking_mode(enum al_tracking_mode mode)
{
    tracking_result.mode = mode;
}