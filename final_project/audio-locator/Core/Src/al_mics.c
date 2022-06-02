#include "al_mics.h"
#include "al_logging.h"

const uint32_t AL_MIC_FREQUENCY = 48000;
const uint32_t AL_MIC_BITRATE = 16;
const uint32_t AL_MIC_CHANNELS = 3;

#define PDM_BUF_SIZE 64
uint16_t pdm_buffer[PDM_BUF_SIZE];
uint16_t pcm_buffer[PDM_BUF_SIZE];

void mics_init()
{
    uint8_t ret = AUDIO_OK;
    ret = BSP_AUDIO_IN_Init(AL_MIC_FREQUENCY, AL_MIC_BITRATE, AL_MIC_CHANNELS);
    if (ret != AUDIO_OK)
    {
        logging_log("Mics: ❌ BSP_AUDIO_IN_Init failed");
    }
    logging_log("✅ Mics: success");
}

void mics_update()
{
    logging_log("Mics: Record start");
    if (AUDIO_OK != BSP_AUDIO_IN_Record(pdm_buffer, PDM_BUF_SIZE))
    {
        logging_log("Mics: ❌ Record failed");
        HAL_Delay(1000);
    }
    logging_log("Mics: ✅ rec");

    // if (AUDIO_OK != BSP_AUDIO_IN_PDMToPCM(pdm_buffer, pcm_buffer))
    // {
    //     logging_log("Mics: ❌ PCM Conversion failed");
    //     HAL_Delay(1000);
    // }
    // logging_log("Mics: ✅ conv");
}
