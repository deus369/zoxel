#ifndef zox_mod_zigels
#define zox_mod_zigels

#include "settings/_.c"
#include "components/_.c"
#include "data/_.c"
#include "util/_.c"
#include "prefabs/_.c"
#include "util/io.c"
#include "systems/_.c"

zox_begin_module(Zigels)
    define_components_zigels(world);
    zox_filter(fonts,
        [none] FontTexture,
        [out] textures.GenerateTexture)
    zox_system_ctx(FontTextureSystem, zox_pip_zigels, fonts,
        [in] ZigelIndex,
        [in] colorz.Color,
        [in] colorz.SecondaryColor,
        [in] rendering.TextureSize,
        [in] zigels.FontThickness,
        [in] zigels.FontOutlineThickness,
        [out] textures.TextureData,
        [out] rendering.TextureDirty,
        [out] textures.GenerateTexture,
        [none] FontTexture)
    add_hook_files_load(load_files_fonts);
    spawn_prefabs_zigels(world);
zox_end_module(Zigels)

#endif