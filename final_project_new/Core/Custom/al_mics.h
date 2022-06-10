#if !defined(HEADER_AL_MICS)
#define HEADER_AL_MICS

#include "stm32469i_discovery.h"
#include "stm32469i_discovery_audio.h"

void mics_init(TIM_HandleTypeDef *htim_i2s3);
void mics_update();

struct al_mic_pcm_frame
{
    uint16_t count;
    uint16_t *samples;
    uint16_t *pdm_samples;
};

typedef struct al_mic_pcm_frame mics_pcm_frame;

mics_pcm_frame *mic_get_sample();

#endif // HEADER_AL_MICS
