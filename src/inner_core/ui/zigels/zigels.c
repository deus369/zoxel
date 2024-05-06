#ifndef zox_zigels
#define zox_zigels

// zoxel_settings
#define zox_pip_zigels EcsOnUpdate
#define directory_fonts "fonts"character_slash
const char *default_font_ttf = "miracode.ttf"; // % is broken idk
const float point_font_margins = 0.01f;
const int font_texture_mul = 4;
const int font_texture_size = 128;
const color default_font_outline_color = (color) { 55, 125, 125, 255 };
const color default_font_fill_color = (color) { 55, 185, 125, 255 };
// zoxel_component_defines
zox_declare_tag(FontStyle)
zox_declare_tag(Font)
zox_declare_tag(FontTexture)
zox_declare_tag(Zigel)
zox_component_byte(ZigelIndex)
zox_component_color(FontFillColor)
zox_component_color(FontOutlineColor)
zox_memory_component(FontData, byte2) // line points used for generating a font texture
// spawn datas
#include "data/parent_spawn_data.c"
#include "data/canvas_spawn_data.c"
#include "data/zext_spawn_data.c"
#include "data/zigel_spawn_data.c"  // uses all of above
// zoxel_util_includes
#include "util/default_font.c"
#include "util/font_util.c"
#include "util/ttf_util.c"
// zoxel_prefab_includes
#include "prefabs/font.c"
#include "prefabs/font_style.c"
#include "prefabs/zigel.c"
#include "prefabs/ttf_font.c"
// zoxel_system_declares
#include "systems/font_texture_system.c"

int get_zigels_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Zigel));
}

void initialize_zigels(ecs_world_t *world) {
    initialize_ttf(world); // load in monocraft
}

void spawn_prefabs_zigels(ecs_world_t *world) {
    spawn_font_style_prefab(world);
    spawn_font_prefab(world);
    spawn_zigel_prefab(world);
}

zox_begin_module(Zigels)
// zoxel_component_defines
zox_define_tag(Font)
zox_define_tag(FontTexture)
zox_define_tag(FontStyle)
zox_define_tag(Zigel)
zox_define_component_byte(ZigelIndex)
zox_define_component_color(FontFillColor)
zox_define_component_color(FontOutlineColor)
zox_define_memory_component(FontData)
// zoxel_filter_defines
zox_filter(fonts, [none] FontTexture, [out] GenerateTexture)
// zoxel_system_defines
zox_system_ctx(FontTextureSystem, zox_pip_zigels, fonts, [in] ZigelIndex, [in] Color, [in] SecondaryColor, [in] TextureSize, [out] TextureData, [out] TextureDirty, [out] GenerateTexture, [none] FontTexture)
zoxel_end_module(Zigels)

#endif
