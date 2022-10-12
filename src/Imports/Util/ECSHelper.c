#include "../../Imports/Flecs/flecs.h"
// --- Core ---
#include "../../Core/Core/Core.h"
#include "../../Core/Inputs/Inputs.h"
#include "../../Core/Transforms2D/Transforms2D.h"
#include "../../Space/Physics2D/Physics2D.h"
#include "../../Core/Textures/Textures.h"
// --- Space ---
#include "../../Core/Rendering/Rendering.h"
// --- Gameplay ---

ecs_world_t *world;

//! Initialize Flecs ECS and Modules.
void InitializeECS(int argc, char* argv[], bool profiler, bool isRendering)
{
    world = ecs_init_w_args(argc, argv);
    // Core Modules
    InitializeTransforms2D(world);
    InitializeInputs(world);
    if (isRendering)
    {
        InitializeRendering(world);
    }
    InitializeTextures(world);
    // Space Modules
    InitializePhysics2D(world);
    // Gameplay Modules
    // Enable Profiler
    if (profiler)
    {
        ECS_IMPORT(world, FlecsMonitor); 
        ecs_singleton_set(world, EcsRest, {0});
    }
    // Enable Threads (if no rendering)
    if (!isRendering)
    {
        ecs_set_threads(world, SDL_GetCPUCount());
    }
}

void UpdateECS()
{
    ecs_progress(world, deltaTimeSDL);
}

void EndECS()
{
    ecs_fini(world);
}