#if !defined(HEADER_AL_DISPLAY)
#define HEADER_AL_DISPLAY

#include "al_direction.h"
#include "al_mics.h"

void al_display_update();
void al_display_init();

void display_set_tracking(tracking_dir *dir);
void display_set_audio(mics_pcm_frame *new_pcm_frame);

void al_draw_audio(void);

#endif // HEADER_AL_DISPLAY
