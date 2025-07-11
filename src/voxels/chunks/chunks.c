#ifndef zox_mod_voxels_chunks
#define zox_mod_voxels_chunks

#include "settings/_.c"
#include "states/_.c"
#include "components/_.c"
#include "data/_.c"
#include "util/_.c"
#include "prefabs/_.c"
#include "systems/_.c"
#include "debug/_.c"

void module_dispose_chunks(ecs_world_t *world, void *ctx) {
    dispose_hook_spawned_block();
}

zox_begin_module(Chunks)
    zox_module_dispose(module_dispose_chunks)
    define_components_chunks(world);
    define_systems_chunks(world);
    initialize_hook_spawned_block();
    add_hook_key_down(key_down_toggle_debug_chunks);
    spawn_prefabs_chunks(world);
zox_end_module(Chunks)

#endif