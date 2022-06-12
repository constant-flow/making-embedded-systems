/**
 ******************************************************************************
 * @file           : al_mics.c
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

#include "al_mics.h"
#include "al_logging.h"
#include "pdm2pcm.h"

// helpful ressource https://www.youtube.com/watch?v=zlGSxZGwj-E

/*****************************************************************************/
// Used to verify correlation is working with synthetic pcm data
// #define USE_GENERATED_MIC_INPUT
/*****************************************************************************/

#define PCM_SLOTS 2

// input from stereo mems mic in PDM
uint16_t pdm_buffer[PDM_BUF_SIZE];

// converted from pdm to pcm
uint16_t pcm_buffer[PCM_BUF_SIZE * PCM_SLOTS];

// pointers/index for double bufferung
uint16_t *pdm_buffer_head = pdm_buffer;
uint16_t *pcm_buffer_head = pcm_buffer;
uint16_t pcm_buffer_head_index = 0;

// data frame to pass
static mics_pcm_frame frame_current;

// status flags
volatile uint8_t data_ready = 0;
volatile uint8_t playing = 0;
volatile uint8_t new_result = 0;

void process_data()
{
    if (0 == data_ready)
        return;

    new_result = 1;

#ifndef USE_GENERATED_MIC_INPUT
    BSP_AUDIO_IN_PDMToPCM(pdm_buffer_head, pcm_buffer_head);

    pcm_buffer_head_index += PCM_BUF_SIZE_HALF;
    if (pcm_buffer_head_index >= PCM_SLOTS * 2)
    {
        if (0 == playing)
        {
            playing = 1;
            BSP_AUDIO_OUT_Play(pcm_buffer, PCM_BUF_SIZE * PCM_SLOTS);
        }
        pcm_buffer_head_index = 0;
    }

#endif

    frame_current.samples = pcm_buffer_head;
    frame_current.pdm_samples = pdm_buffer_head;
    data_ready = 0;
    pcm_buffer_head = &pcm_buffer[pcm_buffer_head_index];
}

// generates pcm_data for L/R channel to test correlation
void setup_input_from_generator()
{
    const uint16_t CHANNEL_L = 0;
    const uint16_t CHANNEL_R = 1;
    uint16_t shift = -7;

    uint16_t noise[PCM_BUF_SIZE];
    uint16_t signal[PCM_BUF_SIZE];

    uint16_t noise_reduction = 2048;
    uint16_t noise_factor = 0;
    for (int i = 0; i < PCM_BUF_SIZE; i++)
    {
        noise[i] = rand() / noise_reduction * noise_factor;
        signal[i] = UINT16_MAX / 2;
    }

    signal[2] = UINT16_MAX;
    signal[3] = UINT16_MAX / 3;
    signal[4] = UINT16_MAX / 4;
    signal[5] = UINT16_MAX / 8;
    signal[6] = UINT16_MAX / 16;

    for (int i = 0; i < PCM_BUF_SIZE_HALF; i += 1)
    {
        uint8_t shift_pos = (i + shift) % PCM_BUF_SIZE_HALF;
        pcm_buffer[i * 2 + CHANNEL_L] = noise[i] + signal[i];
        pcm_buffer[i * 2 + CHANNEL_R] = noise[shift_pos] + signal[shift_pos];
    }

    logging_log("⚠️ Mics: Init success from generator not mems microphones");
}

void setup_input_from_mems_mics()
{
    if (AUDIO_OK != BSP_AUDIO_IN_Init(AL_MIC_FREQUENCY, AL_MIC_BITRATE, AL_MIC_CHANNELS))
    {
        logging_log("❌ Mics init failed");
        Error_Handler();
    }

    if (AUDIO_OK != BSP_AUDIO_IN_Record(pdm_buffer, PDM_BUF_SIZE))
    {
        logging_log("❌ Mics init failed");
        Error_Handler();
    }

    logging_log("✅ Mics: Init success");
}

void mics_init()
{
    for (int i = 0; i < PCM_BUF_SIZE * PCM_SLOTS; i++)
    {
        pcm_buffer[i] = 1234;
    }

    frame_current.count = PCM_BUF_SIZE;
    frame_current.samples = pcm_buffer_head;

    // use audio output for testing the audio quality
    if (AUDIO_OK != BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, 70, DEFAULT_AUDIO_IN_FREQ))
    {
        Error_Handler();
    }

    // required to get L/R disconnected in audible headphone output
    BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);

#ifdef USE_GENERATED_MIC_INPUT
    setup_input_from_generator();
#else // use mems microphones
    setup_input_from_mems_mics();
#endif
}

// ping-pong input buffer half 1
void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
    data_ready = 1;
    pdm_buffer_head = &pdm_buffer[PDM_BUF_SIZE_HALF];
    process_data(); // putting this into ther interrupt lead to better quality
}

// ping-pong input buffer half 2
void BSP_AUDIO_IN_TransferComplete_CallBack()
{
    data_ready = 2;
    pdm_buffer_head = &pdm_buffer[0];
    process_data(); // putting this into ther interrupt lead to better quality
}

mics_pcm_frame *mic_get_sample()
{
    frame_current.is_new_sample = new_result;
    new_result = 0;
    return &frame_current;
}
