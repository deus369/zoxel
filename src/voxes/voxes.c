#ifndef zox_mod_voxes
#define zox_mod_voxes
/**
 *  Zox Voxes
 *
 *      - colored vox models
 *
 * */

#include "data/_include.c"
#include "prefabs/_include.c"
#include "util/_include.c"
#include "systems/_include.c"

void dispose_voxes(ecs_world_t *world, void *ctx) {
    dispose_files_voxes(world);
}

void initialize_voxes(ecs_world_t *world) {
    load_files_voxes(world, prefab_vox_file);
}

zox_begin_module(Voxes)
    zox_module_dispose(dispose_voxes)
    zox_define_components_voxes(world);
    zox_define_systems_voxes(world);
    zox_define_prefabs_voxes(world);
    add_hook_terminal_command(process_arguments_voxes);
zox_end_module(Voxes)

#endif