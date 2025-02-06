#ifndef zox_mod_textures
#define zox_mod_textures

#include "core/textures_core.c"
#include "util/sdl_textures.c"
#include "io/textures_io.c"

zox_begin_module(Textures)
    zox_import_module(TexturesCore)
    zox_import_module(TexturesIO)
zoxel_end_module(Textures)

#endif
