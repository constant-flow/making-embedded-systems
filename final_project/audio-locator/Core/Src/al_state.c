#include "al_state.h"

struct audio_locator_state
{
    // 2D or 3D
    int16_t tracking_mode;
    // signals a change in tracking mode
    int16_t changed_tracking_mode;

    // how much do signals need to correlate to trigger a detection
    int16_t detector_level;
    int16_t detector_level_changed;
};

struct audio_locator_state state;

void init_state()
{
    state.tracking_mode = 2;
    state.changed_tracking_mode = 1;

    state.detector_level = 255;
    state.detector_level_changed = 1;
}

void set_tracking_mode(int16_t newMode)
{
    if (state.tracking_mode == newMode)
        return;
    if (newMode == 2 || newMode == 3)
    {
        state.changed_tracking_mode = 1;
        state.tracking_mode = newMode;
    }
}

uint16_t get_tracking_mode()
{
    return state.tracking_mode;
}

int changed_tracking_mode()
{
    return state.changed_tracking_mode;
}

void processed_tracking_mode_change()
{
    state.changed_tracking_mode = 0;
}

int set_tracking_threshold(int16_t newLevel)
{
    // if (newLevel > 255)
    //     return 0; // out of expected bounds

    state.detector_level = newLevel;
    state.detector_level_changed = 1;
    return 1;
}

int changed_tracking_threshold()
{
    return state.detector_level_changed;
}

void processed_tracking_threshold_change()
{
    state.detector_level_changed = 0;
}

int16_t get_tracking_threshold()
{
    return state.detector_level;
}
