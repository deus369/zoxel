//! Helper file for Flecs!
ecs_world_t *world;

//! Initialize Flecs ECS by spawning a world and enabling threads.
void open_ecs(int argc, char* argv[], unsigned char profiler, int core_count)
{
    // spawn ecs world
    world = ecs_init_w_args(argc, argv);
    // enable Profiler
    if (profiler)
    {
        #if defined (FLECS_REST) && defined (FLECS_MONITOR)
        ECS_IMPORT(world, FlecsMonitor); 
        ecs_singleton_set(world, EcsRest, {0});
        #else
        zoxel_log("Error: Cannot import FlecsMonitor. Make sure to define FLECS_REST & FLECS_MONITOR.\n");
        #endif
    }
    // enable multi threading
    #ifdef zoxel_debug_sdl
    zoxel_log("System Found [%i processors].\n", core_count);
    #endif
    if (core_count > 1)
    {
        ecs_set_threads(world, core_count);
    }
}

void close_ecs()
{
    ecs_fini(world);
}