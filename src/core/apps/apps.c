#ifndef zoxel_apps
#define zoxel_apps
#include <stdbool.h>

//! apps Module.
bool vsync = false;
bool fullscreen = false;
#include "util/SDLUtil.c"
#include "util/FlecsUtil.c"

void AppsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Apps);
    OpenWindow();
}
#endif