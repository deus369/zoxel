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
zox_end_module(Chunks)

#endif
