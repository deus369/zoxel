#ifndef zox_mod_voxes
#define zox_mod_voxes
/**
 *  Zox Voxes
 *
 *      - colored vox models
 *
 * */

#include "data/_.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/_.c"

void dispose_voxes(ecs_world_t *world, void *ctx) {
    dispose_files_voxes(world);
}

zox_begin_module(Voxes)
    zox_module_dispose(dispose_voxes)
    define_components_voxes(world);
    define_systems_voxes(world);
    zox_define_prefabs_voxes(world);
    add_hook_terminal_command(process_arguments_voxes);
    add_hook_spawned_block(&spawned_block_vox);
zox_end_module(Voxes)

#endif