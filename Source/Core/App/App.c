#ifndef Zoxel_App
#define Zoxel_App
#include <stdbool.h>

//! App Module.
bool vsync = false;
bool fullscreen = false;
#include "Util/SDLUtil.c"
#include "Util/FlecsUtil.c"

void AppImport(ecs_world_t *world)
{
    ECS_MODULE(world, App);
    OpenWindow();
}
#endif