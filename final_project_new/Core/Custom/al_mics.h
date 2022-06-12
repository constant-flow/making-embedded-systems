/**
 ******************************************************************************
 * @file           : al_mics.h
 * @brief          : PDM Microphone capturing and conversion to PCM
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

#if !defined(HEADER_AL_MICS)
#define HEADER_AL_MICS

#include "stm32469i_discovery.h"
#include "stm32469i_discovery_audio.h"

#define AL_MIC_FREQUENCY DEFAULT_AUDIO_IN_FREQ
#define AL_MIC_BITRATE DEFAULT_AUDIO_IN_BIT_RESOLUTION
#define AL_MIC_CHANNELS DEFAULT_AUDIO_IN_CHANNEL_NBR

#define PDM_BUF_SIZE (INTERNAL_BUFF_SIZE)
#define PDM_BUF_SIZE_HALF (PDM_BUF_SIZE / 2)

#define PCM_BUF_SIZE (PDM_BUF_SIZE / 8)
#define PCM_BUF_SIZE_HALF (PCM_BUF_SIZE / 2)

void mics_init();

struct al_mic_pcm_frame
{
    uint16_t count;
    uint16_t *samples;
    uint16_t *pdm_samples;
    uint8_t is_new_sample;
};

typedef struct al_mic_pcm_frame mics_pcm_frame;

mics_pcm_frame *mic_get_sample();

#endif // HEADER_AL_MICS
