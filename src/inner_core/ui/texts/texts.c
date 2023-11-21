#ifndef zoxel_texts
#define zoxel_texts

// \todo Display a UI Element anchored, with a pixel position.
// \todo Change colour when ray hits a button

// zoxel_settings
#define zox_pipelines_zext_textures EcsOnUpdate // EcsOnUpdate | EcsPostUpdate
#define zox_pipelines_zext_backgrounds EcsPreStore // EcsPostUpdate
const double zext_animation_speed = 10.0;
// zoxel_component_defines
zox_declare_tag(FontStyle)
zox_declare_tag(Font)
zox_declare_tag(FontTexture)
zox_declare_tag(Zigel)
zox_declare_tag(Zext)
zox_declare_tag(ZextLabel)
zox_component_byte(ZextDirty)
zox_component_byte(ZigelIndex)
zox_component_byte(ZextAlignment)
zox_component_int(ZextSize)
zox_component_byte2(ZextPadding)
zox_component(AnimateZext, double) 
zox_memory_component(FontData, byte2)           // points used for generating a font texture
zox_memory_component(ZextData, unsigned char)   // zigel indexes
// zoxel_util_includes
#include "util/default_font.c"
#include "util/zigel_util.c"
// zoxel_prefab_includes
#include "prefabs/font.c"
#include "prefabs/font_style.c"
#include "prefabs/zigel.c"
#include "prefabs/zext.c"
#include "util/zext_util.c"
// zoxel_system_declares
#include "systems/font_texture_system.c"
#include "systems/zext_update_system.c"
#include "systems/animate_text_system.c"
#include "systems/zext_background_system.c"
#include "systems/zext_parent_background_system.c"

int get_zigels_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Zigel));
}

int get_zexts_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Zext));
}

void spawn_prefabs_texts(ecs_world_t *world) {
    spawn_font_style_prefab(world);
    spawn_font_prefab(world);
    spawn_zigel_prefab(world);
    spawn_zext_prefab(world);
}

zox_begin_module(Texts)
// zoxel_component_defines
zox_define_tag(Font)
zox_define_tag(Zigel)
zox_define_tag(FontTexture)
zox_define_tag(Zext)
zox_define_tag(FontStyle)
zox_define_tag(ZextLabel)
zox_define_component_byte(ZextDirty)
zox_define_component_byte(ZigelIndex)
zox_define_component_byte(ZextAlignment)
zox_define_component_int(ZextSize)
zox_define_component_byte2(ZextPadding)
zox_define_component(AnimateZext)
zox_define_memory_component(FontData)
zox_define_memory_component(ZextData)
// zoxel_filter_defines
zox_filter(zexts, [none] Zext, [in] ZextDirty)
zox_filter(fonts, [none] FontTexture, [out] GenerateTexture)
// zoxel_system_defines
zox_system(AnimateTextSystem, zox_pipelines_zext_textures, [out] AnimateZext, [out] ZextDirty, [out] ZextData)
zox_system_ctx(FontTextureSystem, zox_pipelines_zext_textures, fonts, [none] FontTexture, [out] TextureDirty, [out] TextureData, [in] TextureSize, [out] GenerateTexture, [in] ZigelIndex, [in] Color)
if (!headless) zox_system(ZextBackgroundSystem, zox_pipelines_zext_backgrounds, [none] Zext, [in] ZextDirty, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] MeshAlignment, [in] CanvasLink, [out] PixelSize, [out] TextureSize, [out] GenerateTexture, [out] MeshVertices2D, [out] MeshDirty)
if (!headless) zox_system(ZextParentBackgroundSystem, zox_pipelines_zext_backgrounds, [none] Zext, [in] ZextDirty, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] MeshAlignment, [in] CanvasLink, [in] ParentLink)
zox_system_ctx_1(ZextUpdateSystem, main_thread_pipeline, zexts, [none] Zext, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] Layer2D, [in] CanvasPosition, [in] PixelSize, [in] MeshAlignment, [in] RenderDisabled, [out] ZextDirty, [out] Children)
zoxel_end_module(Texts)

#endif
