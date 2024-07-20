#ifndef zox_mod_zigels
#define zox_mod_zigels

zox_declare_tag(FontStyle)
zox_declare_tag(TTFFontStyle)
zox_declare_tag(Font)
zox_declare_tag(FontTexture)
zox_declare_tag(Zigel)
zox_component_byte(FontThickness)
zox_component_byte(ZigelIndex)
zox_component_color(FontFillColor)
zox_component_color(FontOutlineColor)
zox_component_entity(FontLink)
zox_memory_component(FontData, byte2) // line points used for generating a font texture
#include "data/settings.c"
#include "data/parent_spawn_data.c"
#include "data/canvas_spawn_data.c"
#include "data/zext_spawn_data.c"
#include "data/zigel_spawn_data.c"  // uses all of above
#include "util/default_font.c"
#include "util/font_util.c"
#include "util/ttf_util.c"
#include "prefabs/prefabs.c"
#include "util/font_io.c"
#include "systems/font_texture_system.c"

zox_begin_module(Zigels)
zox_define_tag(FontStyle)
zox_define_tag(TTFFontStyle)
zox_define_tag(Font)
zox_define_tag(FontTexture)
zox_define_tag(Zigel)
zox_define_component_byte(FontThickness)
zox_define_component_byte(ZigelIndex)
zox_define_component_color(FontFillColor)
zox_define_component_color(FontOutlineColor)
zox_define_memory_component(FontData)
zox_define_component_entity(FontLink)
zox_filter(fonts, [none] FontTexture, [out] GenerateTexture)
zox_system_ctx(FontTextureSystem, zox_pip_zigels, fonts, [in] ZigelIndex, [in] Color, [in] SecondaryColor, [in] TextureSize, [in] FontThickness, [out] TextureData, [out] TextureDirty, [out] GenerateTexture, [none] FontTexture)
spawn_prefabs_zigels(world);
load_styles(world);
zoxel_end_module(Zigels)

#endif
