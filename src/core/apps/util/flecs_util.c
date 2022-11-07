//! Helper file for Flecs!
ecs_world_t *world;

//! Initialize Flecs ECS by spawning a world and enabling threads.
void open_ecs(int argc, char* argv[], bool profiler)
{
    // spawn ecs world
    world = ecs_init_w_args(argc, argv);
    // enable Profiler
    if (profiler)
    {
        #if defined (FLECS_REST) && defined (FLECS_MONITOR)
        ECS_IMPORT(world, FlecsMonitor); 
        ecs_singleton_set(world, EcsRest, {0});
        #endif
    }
    // enable multi threading
    int cpuCoreCount = SDL_GetCPUCount();
    printf("System Found [%i processors].\n", cpuCoreCount);
    if (cpuCoreCount > 1)
    {
        ecs_set_threads(world, cpuCoreCount);
    }
}

void close_ecs()
{
    ecs_fini(world);
}