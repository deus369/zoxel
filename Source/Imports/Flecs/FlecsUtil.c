//! Helper file for Flecs!

ecs_world_t *world;

//! Initialize Flecs ECS and Modules.
void SpawnWorld(int argc, char* argv[], bool profiler)
{
    world = ecs_init_w_args(argc, argv);
    // Enable Threads (if no rendering)
    // Enable Profiler
    if (profiler)
    {
        #ifdef FLECS_REST
        ECS_IMPORT(world, FlecsMonitor); 
        ecs_singleton_set(world, EcsRest, {0});
        #endif
    }
}

// extern int SDL_GetCPUCount();

void SetMultiThreading(int cpuCoreCount)
{
    if (cpuCoreCount > 1)
    {
        ecs_set_threads(world, cpuCoreCount);
    }
}

void UpdateECS()
{
    // ecs_progress(world, deltaTimeSDL);
}

void EndECS()
{
    ecs_fini(world);
}