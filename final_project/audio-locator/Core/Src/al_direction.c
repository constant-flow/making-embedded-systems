#include "al_direction.h"
#include "math.h"

static tracking_dir last_dir = {0.0f, 0.0f, 0.0f, MODE_UNINITIALIZED};

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

void direction_update()
{
    float time = HAL_GetTick() / 1000.f;
    last_dir.x = sin(time);
    last_dir.y = cos(time);
}