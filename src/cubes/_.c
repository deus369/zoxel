#ifndef zoxm_cubes
#define zoxm_cubes

#include "data/_.c"
#include "prefabs/_.c"
#include "debug/_.c"

zox_begin_module(Cubes)
    add_hook_spawn_prefabs(spawn_prefabs_cubes);
zox_end_module(Cubes)

#endif
