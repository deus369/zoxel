#include "util/module_macros.c"
#include "util/component_macros.c"
#include "util/system_macros.c"
#include "util/flecs_macros.c"
#include "util/flecs_extensions.c"
#include "util/entities_component.c"
#include "util/memory_component.c"
#include "util/octree_component.c"
#include "util/user_data.c"

//! Initialize Flecs ECS by spawning a world and enabling threads.
ecs_world_t* open_ecs(int argc, char* argv[], unsigned char profiler, int core_count) {
    ecs_world_t* world = ecs_init_w_args(argc, argv);
    if (profiler) {
        #if defined (FLECS_REST) && defined (FLECS_MONITOR)
            zoxel_import_module(FlecsMonitor)
            ecs_singleton_set(world, EcsRest, {0});
        #else
            zoxel_log("Error: Cannot import FlecsMonitor. Make sure to define FLECS_REST & FLECS_MONITOR.\n");
        #endif
    }
    #ifdef zoxel_debug_sdl
        zoxel_log(" > found [%i] processor cores\n", core_count);
    #endif
    if (core_count > 1) {
        ecs_set_threads(world, core_count); // enable multi threading
    }
    ecs_set_target_fps(world, 0);
    return world;
}

void close_ecs() {
    ecs_fini(world);
}