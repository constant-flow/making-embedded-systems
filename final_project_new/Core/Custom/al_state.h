#if !defined(HEADER_AL_STATE)
#define HEADER_AL_STATE

#include "stdint.h"

// set all states to default
void state_init();

// Tracking
void state_set_tracking_mode(int16_t newMode);
uint16_t state_get_tracking_mode();
void state_processed_tracking_mode_change();
int state_changed_tracking_mode();

// Sound detection
int state_set_tracking_threshold(int16_t newLevel);
int state_changed_tracking_threshold();
int16_t state_get_tracking_threshold();
void state_processed_tracking_threshold_change();
void state_tracking_mode_toggle();

#endif // HEADER_AL_STATE
