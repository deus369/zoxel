#include "_includes.c"
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

void initialize_threads(ecs_world_t* world) {
    if (use_cores > 1 && is_multithreading) {
        ecs_set_threads(world, use_cores);
    } else {
        zox_log(" ! warning, single threads set\n")
        ecs_set_threads(world, 0);
    }
}

void set_target_fps(ecs_world_t *world, byte target_fps) {
    ecs_set_target_fps(world, target_fps);
}

void initialize_ecs_settings(ecs_world_t *world) {
    initialize_threads(world);
    initialize_flecs_profiler(world);
    set_target_fps(world, target_fps);
}

ecs_world_t* open_ecs(int argc, char* argv[]) {
    return ecs_init_w_args(argc, argv);
}

ecs_world_t* initialize_ecs(int argc, char* argv[], byte cores) {
    use_cores = cores;
    world = open_ecs(argc, argv);
    return world;
}

void dispose_ecs(ecs_world_t *world) {
    ecs_fini(world);
    dispose_update_loop();
    dispose_post_update_loop();
}
