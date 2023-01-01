#ifndef zoxel_core
#define zoxel_core

// Settings for main
unsigned char profiler = 0;
// --- core ---
#include "debug_logs/debug_logs.c"
#include "ecs/ecs_util.c"
#include "maths/maths.c"
#include "generic/generic.c"
#include "timing/timing.c"
#include "transforms/transforms.c"
#include "networking/networking.c"
#include "apps/apps.c"
#include "inputs/inputs.c"
#include "cameras/cameras.c"
#include "rendering/rendering.c"
#include "core_util.c"

//! Handles modules that are for basic stuff at lowest level
void CoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, Core);
    ECS_IMPORT(world, Generic);
    ECS_IMPORT(world, Maths);
    ECS_IMPORT(world, Timing);
    ECS_IMPORT(world, Transforms);
    ECS_IMPORT(world, Networking);
    if (!headless)
    {
        ECS_IMPORT(world, Apps);
        ECS_IMPORT(world, Inputs);
    }
    ECS_IMPORT(world, Rendering);   // imports just shared components
    ECS_IMPORT(world, Cameras);
}
#endif