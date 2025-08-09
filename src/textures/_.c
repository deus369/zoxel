#ifndef zoxm_textures
#define zoxm_textures

#include "data/_.c"
#include "generation/_.c"
#include "prefabs/_.c"
#include "systems/_.c"
#include "tests/test_texture.c"
#include "util/sdl_textures.c"
#include "io/_.c"
#include "debug/_.c"

// todo: rename Textures as TextureLinks, and Textures to Textures again
zox_begin_module(Textures)
    define_components_textures(world);
    define_systems_textures(world);
    add_hook_spawn_prefabs(spawn_prefabs_textures_core);
    zox_import_module(TexturesIO);
zox_end_module(Textures)

#endif
