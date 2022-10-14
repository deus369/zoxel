//! Helper file for Flecs!

ecs_world_t *world;

//! Initialize Flecs ECS and Modules.
void InitializeECS(int argc, char* argv[], bool profiler, bool isThreading, int coreCount)
{
    printf("Initializing ECS\n");
    world = ecs_init_w_args(argc, argv);
    // Enable Threads (if no rendering)
    if (isThreading)
    {
        ecs_set_threads(world, coreCount);
    }
    // Enable Profiler
    if (profiler)
    {
        ECS_IMPORT(world, FlecsMonitor); 
        ecs_singleton_set(world, EcsRest, {0});
    }
}

void UpdateECS()
{
    // ecs_progress(world, 0);
    ecs_progress(world, deltaTimeSDL);
}

void EndECS()
{
    ecs_fini(world);
}