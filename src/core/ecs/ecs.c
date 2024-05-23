// flecs useage, create an ecs world
#include "util/flecs_defines.c"
#include "data/settings.c"
zoxel_dynamic_array(ecs_entity_t)
create_is_in_array_d(ecs_entity_t)
#include "macros/names.c"
#include "util/module_macros.c"
#include "util/component_macros.c"
#include "util/system_macros.c"
#include "util/filter_macros.c"
#include "util/flecs_macros.c"
#include "util/hashmap_component.c"
#include "util/flecs_extensions.c"
#include "util/entities_component.c"
#include "util/memory_component.c"
#include "util/reset_system.c"

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
/*#ifdef zox_print_sdl
    zox_log(" > found [%i] processor cores\n", core_count)
#endif*/
    zox_log(" > found [%i] processor cores\n", core_count)
    if (core_count > 1 && is_multithreading) ecs_set_threads(world, core_count);
    else {
        zox_log(" ! warning, single threads set\n")
        ecs_set_threads(world, 0);
    }
    if (target_fps) ecs_set_target_fps(world, target_fps);
    initialize_flecs_profiler(world);
    return world;
}

void run_ecs(ecs_world_t *world)  {
    if (debug_pipelines) ecs_log_set_level(1);    // debug system pipelines
    ecs_progress(world, 0);
}

void dispose_ecs(ecs_world_t *world) {
    ecs_fini(world);
}
