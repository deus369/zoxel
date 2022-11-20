#ifndef zoxel_core
#define zoxel_core

// Settings for main
bool headless = false;
bool running = true;
bool profiler = false;
// --- core ---
#include "maths/maths.c"
#include "generic/generic.c"
#include "apps/apps.c"
#include "inputs/inputs.c"
#include "timing/timing.c"
#include "transforms/transforms.c"
#include "cameras/cameras.c"
#include "rendering/rendering.c"

void CoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, Core);
    ECS_IMPORT(world, Generic);
    ECS_IMPORT(world, Maths);
    if (!headless)
    {
        ECS_IMPORT(world, Apps);
    }
    ECS_IMPORT(world, Inputs);
    ECS_IMPORT(world, Timing);
    ECS_IMPORT(world, Transforms);
    if (!headless)
    {
        ECS_IMPORT(world, Rendering);
    }
    ECS_IMPORT(world, Cameras);
}

#endif