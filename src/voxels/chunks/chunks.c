#ifndef zox_mod_voxels_chunks
#define zox_mod_voxels_chunks

#include "data/_include.c"
#include "util/_include.c"
#include "prefabs/_include.c"
#include "systems/_include.c"

zox_begin_module(Chunks)
    zox_define_components_chunks(world);
    zox_define_systems_chunks(world);
    spawn_prefabs_chunks(world);
    add_hook_key_down(key_down_toggle_debug_chunks);
zox_end_module(Chunks)

#endif