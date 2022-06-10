#include "al_mics.h"
#include "al_logging.h"
#include "pdm2pcm.h"

// helpful ressource https://www.youtube.com/watch?v=zlGSxZGwj-E

const uint32_t AL_MIC_FREQUENCY = DEFAULT_AUDIO_IN_FREQ;
const uint32_t AL_MIC_BITRATE = DEFAULT_AUDIO_IN_BIT_RESOLUTION;
const uint32_t AL_MIC_CHANNELS = DEFAULT_AUDIO_IN_CHANNEL_NBR;

#define PDM_BUF_SIZE (INTERNAL_BUFF_SIZE)
#define PDM_BUF_SIZE_HALF (PDM_BUF_SIZE / 2)

#define PCM_BUF_SIZE (PDM_BUF_SIZE / 8)
#define PCM_BUF_SIZE_HALF (PCM_BUF_SIZE / 2)

#define PCM_SLOTS 2

uint16_t pdm_buffer[PDM_BUF_SIZE];
uint16_t pcm_buffer[PCM_BUF_SIZE * PCM_SLOTS];

uint16_t *pdm_buffer_head = pdm_buffer;
uint16_t *pcm_buffer_head = pcm_buffer;
uint16_t pcm_buffer_head_index = 0;

static mics_pcm_frame frame_current;

volatile uint8_t data_ready = 0;
volatile uint8_t playing = 0;

// #define USE_GENERATED_MIC_INPUT

void process_data()
{
    if (0 == data_ready)
        return;

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
    pcm_buffer_head = &pcm_buffer[pcm_buffer_head_index];
#endif

    frame_current.samples = pcm_buffer_head;
    frame_current.pdm_samples = pdm_buffer_head;
    data_ready = 0;
}

void setup_input_from_generator()
{
    const uint16_t CHANNEL_L = 0;
    const uint16_t CHANNEL_R = 1;
    uint16_t shift = 8;

    uint16_t noise[PCM_BUF_SIZE];
    for (int i = 0; i < PCM_BUF_SIZE; i += 2)
    {
        noise[i] = rand();
    }

    for (int i = 0; i < PCM_BUF_SIZE; i += 2)
    {
        pcm_buffer[i + CHANNEL_L] = noise[i];
        pcm_buffer[i + CHANNEL_R] = noise[(i + shift) % PCM_BUF_SIZE];
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
    frame_current.count = PCM_BUF_SIZE;
    frame_current.samples = pcm_buffer_head;

    if (AUDIO_OK != BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, 70, DEFAULT_AUDIO_IN_FREQ))
    {
        Error_Handler();
    }

    BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);

#ifdef USE_GENERATED_MIC_INPUT
    setup_input_from_generator();
#else // use mems microphones
    setup_input_from_mems_mics();
#endif
}

void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
    data_ready = 1;
    pdm_buffer_head = &pdm_buffer[PDM_BUF_SIZE_HALF];
    process_data();
    // pcm_buffer_head = &pcm_buffer[PCM_BUF_SIZE_HALF];
}

void BSP_AUDIO_IN_TransferComplete_CallBack()
{
    data_ready = 2;
    pdm_buffer_head = &pdm_buffer[0];
    process_data();
    // pcm_buffer_head = &pcm_buffer[0];
}

void mics_update()
{
    // logging_log("Mics: ✅ rec");
    process_data();
}

mics_pcm_frame *mic_get_sample()
{
    return &frame_current;
}
