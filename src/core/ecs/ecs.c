// flecs useage, create an ecs world
ecs_world_t *world;
// settings
unsigned char is_multithreading = 1;
unsigned char target_frame_rate = 0;
unsigned char profiler = 0;
// util helper functions
#include "macros/names.c"
#include "util/module_macros.c"
#include "util/component_macros.c"
#include "util/system_macros.c"
#include "util/flecs_macros.c"
#include "util/flecs_extensions.c"
#include "util/entities_component.c"
#include "util/memory_component.c"

ecs_world_t* open_ecs(int argc, char* argv[], unsigned char profiler, int core_count) {
    ecs_world_t* world = ecs_init_w_args(argc, argv);
    if (profiler) {
#if defined (FLECS_REST) && defined (FLECS_MONITOR)
        zox_import_module(FlecsMonitor)
        ecs_singleton_set(world, EcsRest, {0});
#else
        zox_logg("Error: Cannot import FlecsMonitor. Make sure to define FLECS_REST & FLECS_MONITOR.\n")
#endif
    }
#ifdef zox_print_sdl
    zox_log(" > found [%i] processor cores\n", core_count)
#endif
    if (core_count > 1 && is_multithreading) ecs_set_threads(world, core_count); // enable multi threading
    else ecs_set_threads(world, 0);
    if (target_frame_rate != 0) ecs_set_target_fps(world, target_frame_rate);
    return world;
}

void dispose_ecs(ecs_world_t *world) {
    ecs_fini(world);
}
