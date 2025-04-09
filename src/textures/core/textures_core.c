#ifndef zox_mod_textures_core
#define zox_mod_textures_core

#include "data/components.c"
#include "data/settings.c"
#include "data/generate_texture_states.c"
#include "util/util.c"
#include "prefabs/prefabs.c"
#include "systems/systems.c"
#include "tests/test_texture.c"

zox_begin_module(TexturesCore)
    define_components_textures(world);
    define_systems_textures(world);
    spawn_prefabs_textures_core(world);
zox_end_module(TexturesCore)

#endif
