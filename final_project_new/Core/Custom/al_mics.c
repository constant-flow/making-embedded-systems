#include "al_mics.h"
#include "al_logging.h"

// helpful ressource https://www.youtube.com/watch?v=zlGSxZGwj-E

const uint32_t AL_MIC_FREQUENCY = 48000;
const uint32_t AL_MIC_BITRATE = 16;
const uint32_t AL_MIC_CHANNELS = 3;

#define PDM_SAMPLES 32

#define PDM_BUF_SIZE PDM_SAMPLES * 2
#define PDM_BUF_SIZE_HALF PDM_BUF_SIZE / 2

uint16_t pdm_buffer[PDM_BUF_SIZE];
uint16_t pcm_buffer[PDM_BUF_SIZE];

uint16_t *pdm_buffer_head = pdm_buffer;
uint16_t *pcm_buffer_head = pcm_buffer;

extern I2S_HandleTypeDef hi2s3;

static int dataReady = 0;
uint8_t MX_PDM2PCM_Process(uint16_t *pdm_buffer_head, uint16_t *pcm_buffer_head);

static mics_pcm_frame frame_current;

// DMA wrote 1st half
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
    dataReady = 1;
    pdm_buffer_head = &pdm_buffer[0];
    pcm_buffer_head = &pcm_buffer[0];
}

// DMA wrote 2nd half
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    dataReady = 1;
    pdm_buffer_head = &pdm_buffer[PDM_BUF_SIZE_HALF];
    pcm_buffer_head = &pcm_buffer[PDM_BUF_SIZE_HALF];
}

void process_data()
{
    if (dataReady == 0)
        return;

    dataReady = 0;

    MX_PDM2PCM_Process(pdm_buffer_head, pcm_buffer_head);
    frame_current.samples = pcm_buffer_head;
    frame_current.pdm_samples = pdm_buffer;
}

void mics_init(TIM_HandleTypeDef *htim_i2s3)
{
    HAL_TIM_PWM_Start(htim_i2s3, TIM_CHANNEL_2);
    frame_current.count = PDM_SAMPLES;
    frame_current.samples = pcm_buffer_head;

    if (HAL_OK != HAL_I2S_Init(&hi2s3))
    {
        while (1)
        {
        };
    }

    if (HAL_OK != HAL_I2S_Receive_DMA(&hi2s3, pdm_buffer, PDM_BUF_SIZE))
    {
        while (1)
        {
        };
    }
    logging_log("✅ Mics: success");
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
