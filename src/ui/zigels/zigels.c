#ifndef zox_mod_zigels
#define zox_mod_zigels

#include "components/_.c"
#include "settings/_.c"
#include "data/_.c"
#include "util/_.c"
#include "prefabs/_.c"
#include "util/io.c"
#include "systems/_.c"

zox_begin_module(Zigels)
    zox_define_components_zigels(world);
    zox_filter(fonts, [none] FontTexture, [out] GenerateTexture)
    zox_system_ctx(FontTextureSystem, zox_pip_zigels, fonts, [in] ZigelIndex, [in] Color, [in] SecondaryColor, [in] TextureSize, [in] FontThickness, [in] FontOutlineThickness, [out] TextureData, [out] TextureDirty, [out] GenerateTexture, [none] FontTexture)
    spawn_prefabs_zigels(world);
    load_styles(world);
zox_end_module(Zigels)

#endif