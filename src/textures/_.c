#ifndef zox_mod_textures
#define zox_mod_textures

#include "data/_.c"
#include "generation/_.c"
#include "prefabs/_.c"
#include "systems/_.c"
#include "tests/test_texture.c"
#include "util/sdl_textures.c"
#include "io/textures_io.c"

// todo: rename Textures as TextureLinks, and Textures to Textures again
zox_begin_module(Textures)
    define_components_textures(world);
    define_systems_textures(world);
    spawn_prefabs_textures_core(world);
    zox_import_module(TexturesIO)
zox_end_module(Textures)

#endif
