// Vodes3 are our Voxel Entities in the World!
#ifndef zox_mod_vodes3
#define zox_mod_vodes3

byte block_vox_render_at_lod = 0;
#include "hooks/_.c"
#include "systems/_.c"

void module_dispose_vodes3(ecs_world_t *world, void *ctx) {
    dispose_hook_spawned_block();
}

zox_begin_module(Vodes3)
    zox_module_dispose(module_dispose_vodes3)
    initialize_hook_spawned_block();
    define_systems_vodes3(world);
zox_end_module(Vodes3)

#endif