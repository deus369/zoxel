#ifndef zox_terminals
#define zox_terminals

zox_declare_tag(Terminal)
// #include "prefabs/terminal.c"
#include "util/terminal_util.c"

void spawn_prefabs_terminals(ecs_world_t *world) {
    // spawn_prefab_terminal(world);
}

zox_begin_module(Terminals)
zox_define_tag(Terminal)
spawn_prefabs_terminals(world);
zoxel_end_module(Terminals)

#endif
