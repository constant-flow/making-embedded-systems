#include "al_state.h"

struct audio_locator_state
{
    // 2D or 3D
    int16_t tracking_mode;
    // signals a change in tracking mode
    int16_t state_changed_tracking_mode;

    // how much do signals need to correlate to trigger a detection
    int16_t detector_level;
    int16_t detector_level_changed;
};

struct audio_locator_state state;

void state_init()
{
    state.tracking_mode = 1;
    state.state_changed_tracking_mode = 1;

    state.detector_level = 255;
    state.detector_level_changed = 1;
}

void state_set_tracking_mode(int16_t newMode)
{
    if (state.tracking_mode == newMode)
        return;
    if (newMode == 1 || newMode == 2)
    {
        state.state_changed_tracking_mode = 1;
        state.tracking_mode = newMode;
    }
}

uint16_t state_get_tracking_mode()
{
    return state.tracking_mode;
}

int state_changed_tracking_mode()
{
    return state.state_changed_tracking_mode;
}

void state_processed_tracking_mode_change()
{
    state.state_changed_tracking_mode = 0;
}

int state_set_tracking_threshold(int16_t newLevel)
{
    if (newLevel > 255 || newLevel < 0)
        return 0; // out of expected bounds

    state.detector_level = newLevel;
    state.detector_level_changed = 1;
    return 1;
}

int state_changed_tracking_threshold()
{
    return state.detector_level_changed;
}

void state_processed_tracking_threshold_change()
{
    state.detector_level_changed = 0;
}

int16_t state_get_tracking_threshold()
{
    return state.detector_level;
}

void state_tracking_mode_toggle()
{
    if (state_get_tracking_mode() == 2)
    {
        state_set_tracking_mode(1);
    }
    else
    {
        state_set_tracking_mode(2);
    }
}
