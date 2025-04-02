#ifndef zox_mod_cubes
#define zox_mod_cubes

#include "data/settings.c"
#include "data/mesh.c"
#include "data/cube2.c"
#include "data/cube_basic.c"
#include "prefabs/prefabs.c"

zox_begin_module(Cubes)
    spawn_prefabs_cubes(world);
zox_end_module(Cubes)

#endif
