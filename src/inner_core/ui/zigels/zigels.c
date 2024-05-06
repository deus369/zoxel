#ifndef zox_zigels
#define zox_zigels

// zoxel_settings
#define zox_pip_zigels EcsOnUpdate
// zoxel_component_defines
zox_declare_tag(FontStyle)
zox_declare_tag(Font)
zox_declare_tag(FontTexture)
zox_declare_tag(Zigel)
zox_component_byte(ZigelIndex)
zox_memory_component(FontData, byte2)           // points used for generating a font texture
// zoxel_util_includes
#include "util/default_font.c"
#include "util/font_util.c"
// zoxel_prefab_includes
#include "prefabs/font.c"
#include "prefabs/font_style.c"
#include "prefabs/zigel.c"
#include "util/ttf_util.c"
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
zox_define_memory_component(FontData)
// zoxel_filter_defines
zox_filter(fonts, [none] FontTexture, [out] GenerateTexture)
// zoxel_system_defines
zox_system_ctx(FontTextureSystem, zox_pip_zigels, fonts, [none] FontTexture, [out] TextureDirty, [out] TextureData, [in] TextureSize, [out] GenerateTexture, [in] ZigelIndex, [in] Color)
zoxel_end_module(Zigels)

#endif
