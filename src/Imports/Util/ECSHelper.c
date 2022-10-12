#include "../../Imports/Flecs/flecs.h"
// --- Core ---
#include "../../Core/Core/Core.h"
#include "../../Core/Inputs/Inputs.h"
#include "../../Core/Transforms2D/Transforms2D.h"
#include "../../Space/Physics2D/Physics2D.h"
#include "../../Core/Textures/Textures.h"
#include "../../Core/Players/Players.h"
// --- Space ---
#include "../../Core/Rendering/Rendering.h"
// --- Gameplay ---

ecs_world_t *world;

//! Initialize Flecs ECS and Modules.
void InitializeECS(int argc, char* argv[], bool profiler, bool isRendering)
{
    world = ecs_init_w_args(argc, argv);
    // Core Modules
    ECS_IMPORT(world, Inputs);
    ECS_IMPORT(world, Transforms2D);
    if (isRendering)
    {
        ECS_IMPORT(world, Rendering);
    }
    ECS_IMPORT(world, Textures);
    ECS_IMPORT(world, Players);
    // Space Modules
    ECS_IMPORT(world, Physics2D);
    // Gameplay Modules

    // Spawn things from Modules
    ECS_IMPORT(world, Inputs);
    ECS_IMPORT(world, Players);

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