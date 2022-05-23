#if !defined(HEADER_AL_STATE)
#define HEADER_AL_STATE

#include "stdint.h"

// set all states to default
void init_state();

// Tracking
void set_tracking_mode(int16_t newMode);
uint16_t get_tracking_mode();
void processed_tracking_mode_change();
int changed_tracking_mode();

// Sound detection
int set_tracking_threshold(int16_t newLevel);
int changed_tracking_threshold();
int16_t get_tracking_threshold();
void processed_tracking_threshold_change();

#endif // HEADER_AL_STATE
