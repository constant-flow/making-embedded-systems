#include "al_mics.h"
#include "al_logging.h"

const uint32_t AL_MIC_FREQUENCY = 48000;
const uint32_t AL_MIC_BITRATE = 16;
const uint32_t AL_MIC_CHANNELS = 3;

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
}
