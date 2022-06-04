#include "al_mics.h"
#include "al_logging.h"

// helpful ressource https://www.youtube.com/watch?v=zlGSxZGwj-E

const uint32_t AL_MIC_FREQUENCY = 48000;
const uint32_t AL_MIC_BITRATE = 16;
const uint32_t AL_MIC_CHANNELS = 3;

#define PDM_BUF_SIZE 64
uint16_t pdm_buffer[PDM_BUF_SIZE];
uint16_t pcm_buffer[PDM_BUF_SIZE];

extern I2S_HandleTypeDef hi2s3;

static int dataReady = 0;

void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
    dataReady = 1;
}

#define buf_size 128
uint16_t buf[buf_size];

void mics_init()
{
    if (HAL_OK != HAL_I2S_Init(&hi2s3))
    {
        while (1)
        {
        };
    }

    if (HAL_OK != HAL_I2S_Receive_DMA(&hi2s3, buf, buf_size))
    {
        while (1)
        {
        };
    }
    logging_log("✅ Mics: success");
}

void mics_update()
{
    if (dataReady)
    {
        logging_log("Mics: ✅ rec");
    }
}
