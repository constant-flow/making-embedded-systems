#include "al_direction.h"
#include "arm_math.h"
#include "al_logging.h"
#include "main.h"

#define MIN_DETECTION_THRESHOLD 0.1f
#define MAX_DETECTION_THRESHOLD 5.0f

static tracking_dir last_dir = {0.0f, 0.0f, 0.0f, MODE_UNINITIALIZED};
static mics_pcm_frame *audio_frame;

static float detection_threshold = MIN_DETECTION_THRESHOLD;
static float angle_target = 0;
static float angle_target_smoothing = 0.995f;
static float angle_smoothed = 0;

// #define USE_GENERATED_SINE_INPUT
// #define HALT_AFTER_FIRST_SAMPLE

// distance between microphones in cm
#define MICS_DISTANCE 12.4f
#define MICS_BASELINE_TO_SCREEN_ANGLE (tan(1.8f / 11.7f) - PI / 2)

// in cm/s
#define SPEED_OF_SOUND 34300

// how far (in cm) did a soundwave travel one sample later ()
#define DIST_BETWEEN_SAMPLES ((float)SPEED_OF_SOUND / DEFAULT_AUDIO_IN_FREQ)

#define CORR_BUF_SIZE (PCM_BUF_SIZE_HALF * 2 - 1)

typedef struct pcm_correlation
{
    int16_t max_shift_samples; // how many samples were the the two signals phase shifted
    uint16_t max_val;          // how much did they correlate
    uint16_t mid_id;           // which sample id in the correlation means
                               //`phase shift` = 0 (both signals came at the same time)
} pcm_correlation;

static pcm_correlation corr;
static float32_t channel_right[PCM_BUF_SIZE_HALF];
static float32_t channel_left[PCM_BUF_SIZE_HALF];
static float32_t result_corr[CORR_BUF_SIZE];

tracking_dir *direction_get()
{
    return &last_dir;
}

inline float toFloat(uint16_t val)
{
    return ((float32_t)val) / ((float32_t)UINT16_MAX) - 0.5f;
}

void calc_float_channels(mics_pcm_frame *input)
{
    for (int i = 0; i < PCM_BUF_SIZE_HALF; i++)
    {
        channel_left[i] = toFloat(input->samples[i * 2]);
        channel_right[i] = toFloat(input->samples[i * 2 + 1]);
        // logging_log("%d : %f\t|\t%d : %f", input->samples[i * 2], channel_left[i], input->samples[i * 2 + 1], channel_right[i]);
    }
    // logging_log("@@@");
}

void get_correlation(mics_pcm_frame *input, pcm_correlation *corr)
{
    calc_float_channels(input);

    arm_correlate_f32(channel_left, PCM_BUF_SIZE_HALF, channel_right, PCM_BUF_SIZE_HALF, result_corr);

    float32_t max_corr_value = -100;
    uint8_t max_corr_id = 0;

    for (int i = 0; i < CORR_BUF_SIZE; i++)
    {
        // logging_log("i=%d : \t '%d' '%f'", i, (int16_t)(result_corr[i] * 128), result_corr[i]);

        if (result_corr[i] > max_corr_value)
        {
            max_corr_id = i;
            max_corr_value = result_corr[i];
        }
    }
    // logging_log("---");

    if (max_corr_value > detection_threshold)
    {
        // logging_log("corr above threshold");
        corr->max_shift_samples = max_corr_id;
        corr->max_val = max_corr_value;
    }
}

void direction_init()
{
    last_dir.x = 1;
    last_dir.y = 0;
    last_dir.z = 0;
    last_dir.mode = MODE_SCREEN_FRONT;
    corr.mid_id = CORR_BUF_SIZE / 2;
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
    int16_t shifted_sample_amount = corr.max_shift_samples - corr.mid_id;
    float delayed_distance = shifted_sample_amount * DIST_BETWEEN_SAMPLES;
    // logging_log("→ Shifted by %d sample\tdist: %f", shifted_sample_amount, delayed_distance);
    if (delayed_distance > MICS_DISTANCE)
        delayed_distance = MICS_DISTANCE;
    if (delayed_distance < -MICS_DISTANCE)
        delayed_distance = -MICS_DISTANCE;

    float angle = acos(delayed_distance / MICS_DISTANCE);

    float corrected_angle = angle + MICS_BASELINE_TO_SCREEN_ANGLE;

    angle_target = corrected_angle;

    angle_smoothed = angle_target * (1 - angle_target_smoothing) + angle_smoothed * angle_target_smoothing;

    last_dir.x = sin(angle_smoothed);
    last_dir.y = cos(angle_smoothed);

#ifdef HALT_AFTER_FIRST_SAMPLE
    static int halt_after_sample = 0;
    if (halt_after_sample++)
        Error_Handler();
#endif
}

void direction_input(mics_pcm_frame *input)
{
    audio_frame = input;
}

void direction_set_threshold(uint8_t threshold)
{
    detection_threshold = ((float)threshold) / 255 * (MAX_DETECTION_THRESHOLD - MIN_DETECTION_THRESHOLD) + MIN_DETECTION_THRESHOLD;
    logging_log("Mic: threshold now: %f", detection_threshold);
}

void direction_set_tracking_mode(enum al_tracking_mode mode)
{
    last_dir.mode = mode;
}