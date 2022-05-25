#if !defined(HEADER_AL_DIRECTION)
#define HEADER_AL_DIRECTION

enum al_tracking_mode
{
    MODE_UNINITIALIZED = 0,
    MODE_2D = 2,
    MODE_3D = 3
};

typedef enum al_tracking_mode tracking_mode;

struct al_tracking_direction
{
    float x;
    float y;
    float z;
    tracking_mode mode;
};

typedef struct al_tracking_direction tracking_dir;

void direction_reset();
tracking_dir *direction_get();
void direction_update();

#endif // HEADER_AL_DIRECTION
