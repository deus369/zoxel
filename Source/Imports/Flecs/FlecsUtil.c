//! Helper file for Flecs!

ecs_world_t *world;

//! Initialize Flecs ECS and Modules.
void SpawnWorld(int argc, char* argv[], bool profiler, bool isThreading, int coreCount)
{
    world = ecs_init_w_args(argc, argv);
    // Enable Threads (if no rendering)
    if (isThreading)
    {
        ecs_set_threads(world, coreCount);
    }
    // Enable Profiler
    if (profiler)
    {
        #ifdef FLECS_REST
        ECS_IMPORT(world, FlecsMonitor); 
        ecs_singleton_set(world, EcsRest, {0});
        #endif
    }
}

void SpawnWorld2(bool isThreading, int coreCount)
{
    world = ecs_init_w_args(0, NULL);
    // Enable Threads (if no rendering)
    if (isThreading)
    {
        ecs_set_threads(world, coreCount);
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