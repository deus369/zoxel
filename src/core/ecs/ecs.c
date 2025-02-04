// flecs useage, create an ecs world
#include <inttypes.h> // For PRIu64
#include "util/flecs_defines.c"

#include "macros/macros.c"
#include "data/entity_dynamic_array.c"
#include "data/general_fun.c"
#include "data/settings.c"
#include "data/entity_hashmap.c"
#include "util/util.c"

void initialize_flecs_profiler(ecs_world_t* world) {
#ifdef zox_using_profiler
    zox_log(" + initializing profiler\n")
    zox_import_module(FlecsRest)
    zox_import_module(FlecsMonitor)
    ecs_singleton_set(world, EcsRest, {0});
#endif
}

ecs_world_t* open_ecs(int argc, char* argv[], int core_count) {
    ecs_world_t* world = ecs_init_w_args(argc, argv);
    if (core_count > 1 && is_multithreading) {
        ecs_set_threads(world, core_count);
    } else {
        zox_log(" ! warning, single threads set\n")
        ecs_set_threads(world, 0);
    }
    if (target_fps) ecs_set_target_fps(world, target_fps);
    initialize_flecs_profiler(world);
    return world;
}

ecs_world_t* initialize_ecs(int argc, char* argv[], byte cpu_core_count) {
    world = open_ecs(argc, argv, cpu_core_count);
    initialize_update_loop();
    initialize_post_update_loop();
    return world;
}

void dispose_ecs(ecs_world_t *world) {
    ecs_fini(world);
    dispose_update_loop();
    dispose_post_update_loop();
}
