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
        [out] texturez.GenerateTexture)
    zox_system_ctx(FontTextureSystem, zox_pip_zigels, fonts,
        [in] ZigelIndex,
        [in] colorz.Color,
        [in] colorz.SecondaryColor,
        [in] rendering.TextureSize,
        [in] zigels.FontThickness,
        [in] zigels.FontOutlineThickness,
        [out] texturez.TextureData,
        [out] rendering.TextureDirty,
        [out] texturez.GenerateTexture,
        [none] FontTexture)
    spawn_prefabs_zigels(world);
zox_end_module(Zigels)

#endif