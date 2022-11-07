#ifndef zoxel_apps
#define zoxel_apps
#include <stdbool.h>

//! apps Module.
bool vsync = false;
bool fullscreen = false;
#include "util/sdl_util.c"
#include "util/flecs_util.c"

void AppsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Apps);
    OpenWindow();
}
#endif