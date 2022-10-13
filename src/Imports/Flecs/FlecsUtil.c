//! Helper file for Flecs!

ecs_world_t *world;

//! Initialize Flecs ECS and Modules.
ecs_world_t* InitializeECS(int argc, char* argv[], bool profiler, bool isRendering)
{
    ecs_world_t *world2 = ecs_init_w_args(argc, argv);

    // Enable Profiler
    if (profiler)
    {
        ECS_IMPORT(world2, FlecsMonitor); 
        ecs_singleton_set(world2, EcsRest, {0});
    }
    // Enable Threads (if no rendering)
    if (!isRendering)
    {
        ecs_set_threads(world2, SDL_GetCPUCount());
    }
    world = world2;
    return world;
}

void UpdateECS()
{
    ecs_progress(world, deltaTimeSDL);
}

void EndECS()
{
    ecs_fini(world);
}