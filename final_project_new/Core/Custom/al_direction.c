#include "al_direction.h"
#include "math.h"

#define PI 3.14159265358979323846264338328
static tracking_dir last_dir = {0.0f, 0.0f, 0.0f, MODE_UNINITIALIZED};
static mics_pcm_frame *audio_frame;

// #define USE_GENERATED_SINE_INPUT

// distance between microphones in cm
#define MICS_DISTANCE 12.4f
#define MICS_BASELINE_TO_SCREEN_ANGLE (tan(1.8f/11.7f)-PI/2)  

// in cm/s
#define SPEED_OF_SOUND 34300

// how far (in cm) did a soundwave travel one sample later ()
#define DIST_BETWEEN_SAMPLES ((float) SPEED_OF_SOUND / DEFAULT_AUDIO_IN_FREQ)

typedef struct pcm_correlation {
    int16_t max_shift_samples; // how many samples were the the two signals shifted
    uint16_t max_val; // how much did they correlate
} pcm_correlation;

static pcm_correlation corr;

void direction_reset()
{
    last_dir.x = 1;
    last_dir.y = 0;
    last_dir.z = 0;
    last_dir.mode = MODE_UNINITIALIZED;
}

tracking_dir *direction_get()
{
    return &last_dir;
}

void get_correlation(mics_pcm_frame *input, pcm_correlation *corr) {
    //TODO: calculate the real correlation between signals

    corr->max_shift_samples = 0;
    corr->max_val = 100;
}

void direction_update()
{
#ifdef USE_GENERATED_SINE_INPUT
    float time = HAL_GetTick() / 1000.f;
    last_dir.x = sin(time);
    last_dir.y = cos(time);
    return;
#endif

    get_correlation(audio_frame, &corr);

    // keep in bounds (-90° to 90°)
    float delayed_distance = corr.max_shift_samples * DIST_BETWEEN_SAMPLES;
    if(delayed_distance > MICS_DISTANCE) delayed_distance = MICS_DISTANCE;
    if(delayed_distance < -MICS_DISTANCE) delayed_distance = -MICS_DISTANCE; 

    float angle = acos(delayed_distance / MICS_DISTANCE);

    float corrected_angle = angle + MICS_BASELINE_TO_SCREEN_ANGLE;
    last_dir.x = sin(corrected_angle);
    last_dir.y = cos(corrected_angle);
}

void direction_input(mics_pcm_frame *input)
{
    audio_frame = input;
}