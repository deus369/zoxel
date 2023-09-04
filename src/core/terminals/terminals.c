#ifndef zoxel_terminals
#define zoxel_terminals

// used for terminal functions
// todo:
//  > get input from terminal

// zoxel_settings
// zoxel_component_includes
zox_declare_tag(Terminal)
// zoxel_prefab_includes
// #include "prefabs/terminal.c"
// zoxel_util_includes
#include "util/terminal_util.c"

void spawn_prefabs_terminals(ecs_world_t *world) {
    // spawn_prefab_terminal(world);
}

zox_begin_module(Terminals)
// zoxel_component_defines
zox_define_tag(Terminal)
// zoxel_system_defines
zoxel_end_module(Terminals)

#endif
