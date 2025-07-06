#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM
#define FLECS_PIPELINE
#include <flecs.h>

#include "macros/_.c"
#include "data/_.c"
#include "util/_.c"

void initialize_flecs_profiler(ecs_world_t* world) {
#ifdef zox_using_profiler
    //zox_log("+ flecs profiler enabled\n")
    zox_import_module(FlecsRest)
    zox_import_module(FlecsMonitor)
    ecs_singleton_set(world, EcsRest, {0});
    // ecs_tracing_enable(1);
    ecs_log_set_level(0);
    ecs_measure_frame_time(world, true);
    ecs_measure_system_time(world, true);
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
    // zox_log("> flecs version [%s]", flecs_version)
    return ecs_init_w_args(argc, argv);
}

ecs_world_t* initialize_ecs(int argc, char* argv[], byte cores) {
    use_cores = cores;
    ecs_world_t *new_world = open_ecs(argc, argv);
    local_world = new_world;
    return new_world;
}

void dispose_ecs(ecs_world_t *world) {
    dispose_update_loop();
    dispose_post_update_loop();
    ecs_fini(world);
}