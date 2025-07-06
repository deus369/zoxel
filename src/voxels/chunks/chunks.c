#ifndef zox_mod_voxels_chunks
#define zox_mod_voxels_chunks

#include "states/_.c"
#include "components/_.c"
#include "data/_.c"
#include "util/_.c"
#include "prefabs/_.c"
#include "systems/_.c"

zox_begin_module(Chunks)
    define_components_chunks(world);
    define_systems_chunks(world);
    spawn_prefabs_chunks(world);
    add_hook_key_down(key_down_toggle_debug_chunks);
zox_end_module(Chunks)

#endif