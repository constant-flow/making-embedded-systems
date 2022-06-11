#if !defined(HEADER_AL_DIRECTION)
#define HEADER_AL_DIRECTION

#include "al_mics.h"

// available tracking modes
// 2D: track in plane
// 3D: track in space
//
// use type tracking_mode
enum al_tracking_mode
{
    MODE_UNINITIALIZED = 0,
    MODE_2D = 2,
    MODE_3D = 3
};

typedef enum al_tracking_mode tracking_mode;

// direction struct containing coordinates (x,y,z) and the used tracking mode (mode) e.g. 2D, 3D
// use type tracking_dir
struct al_tracking_direction
{
    float x;
    float y;
    float z;
    tracking_mode mode;
};

typedef struct al_tracking_direction tracking_dir;

// returns last calculated direction towards a loud noise
tracking_dir *direction_get();

// calculate (possibly) new direction
void direction_update();

// initializes parameters, resets the tracking dir and tracking mode
void direction_init();

void direction_input(mics_pcm_frame *input);

#endif // HEADER_AL_DIRECTION
