// flecs useage, create an ecs world
#include <inttypes.h> // For PRIu64
typedef unsigned int uint;
typedef unsigned char byte;
#include "util/flecs_defines.c"
#include "data/settings.c"
zoxel_dynamic_array(ecs_entity_t)
create_is_in_array_d(ecs_entity_t)
#include "macros/names.c"
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

extern int process_arguments(int argc, char* argv[]);
extern int SDL_GetCPUCount();
extern void fetch_pc_info(int cpu_core_count_);

ecs_world_t* initialize_ecs(int argc, char* argv[]) {
    int didFail = process_arguments(argc, argv);
    if (didFail == EXIT_FAILURE) {
        return NULL;
    }
    int cpu_core_count = SDL_GetCPUCount();
    fetch_pc_info(cpu_core_count);
    world = open_ecs(argc, argv, cpu_core_count);
    return world;
}

void run_ecs(ecs_world_t *world)  {
    if (debug_pipelines) {
        ecs_log_set_level(1);    // debug system pipelines
    }
    ecs_progress(world, 0);
}

void dispose_ecs(ecs_world_t *world) {
    ecs_fini(world);
}
