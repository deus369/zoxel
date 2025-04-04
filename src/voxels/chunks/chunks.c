#ifndef zox_mod_voxels_chunks
#define zox_mod_voxels_chunks

#include "data/data.c"
#include "util/util.c"
#include "prefabs/prefabs.c"
#include "systems/systems.c"

zox_begin_module(Chunks)
    define_components_chunks(world);
    define_systems_chunks(world);
    spawn_prefabs_chunks(world);
    add_hook_key_down(key_down_toggle_debug_chunks);
zox_end_module(Chunks)

#endif
