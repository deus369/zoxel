#ifndef zoxel_platforms
#define zoxel_platforms

// specific platform implementation code

// zoxel_settings
int cpu_core_count;
// zoxel_component_includes
// zoxel_prefab_includes
// #include "prefabs/terminal.c"
// zoxel_util_includes
// #include "util/platforms_defines.c"
#include "util/cpu_util.c"
#include "util/platform_debug_util.c"
#include "util/webasm_util.c"

void begin_platforms(int cpu_core_count_) {
    cpu_core_count = cpu_core_count_;
    cpu_tier = get_cpu_tier(cpu_core_count);
}

void spawn_prefabs_platforms(ecs_world_t *world) {
    // spawn_prefab_terminal(world);
}

zox_begin_module(Platforms)
// zoxel_component_defines
// zox_define_tag(Terminal)
// zoxel_system_defines
zoxel_end_module(Platforms)

#endif
