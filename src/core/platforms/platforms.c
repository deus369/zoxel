#ifndef zoxel_platforms
#define zoxel_platforms

// specific platform implementation code
// todo:
//  > activate keyboard on steam deck

// zoxel_settings
// zoxel_component_includes
// zoxel_prefab_includes
// #include "prefabs/terminal.c"
// zoxel_util_includes
#include "util/platforms_util.c"
#include "util/platform_debug_util.c"
#include "util/webasm_util.c"

void spawn_prefabs_platforms(ecs_world_t *world) {
    // spawn_prefab_terminal(world);
}

zox_begin_module(Platforms)
// zoxel_component_defines
// zox_define_tag(Terminal)
// zoxel_system_defines
zoxel_end_module(Platforms)

#endif
