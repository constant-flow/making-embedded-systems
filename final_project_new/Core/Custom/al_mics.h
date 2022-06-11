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
void mics_update();

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
