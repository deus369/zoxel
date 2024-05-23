#ifndef zox_platforms
#define zox_platforms

// specific platform implementation code

int cpu_core_count;
#include "util/cpu_util.c"
#include "util/platform_debug_util.c"
#include "util/webasm_util.c"

void fetch_pc_info(int cpu_core_count_) {
    cpu_core_count = cpu_core_count_;
    cpu_tier = get_cpu_tier(cpu_core_count);
}

void spawn_prefabs_platforms(ecs_world_t *world) {
    // spawn_prefab_terminal(world);
}

zox_begin_module(Platforms)
// zox_define_tag(Terminal)
spawn_prefabs_platforms(world);
zoxel_end_module(Platforms)

#endif
