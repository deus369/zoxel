#ifndef zoxel_texts
#define zoxel_texts

// \todo Display a UI Element anchored, with a pixel position.
// \todo Change colour when ray hits a button
// zox_define_reset_system(ZextDirtyResetSystem, ZextDirty)

// zoxel_settings
const double zext_animation_speed = 10.0;
// zoxel_component_defines
zox_declare_tag(FontStyle) //! Contains a bunch of fonts!
zox_declare_tag(Font)
zox_declare_tag(FontTexture)
zox_declare_tag(Zigel) //! An individual text character entity.
zox_declare_tag(Zext)  //! UI text, holds zigels
zox_component(ZigelIndex, unsigned char)      //! an index for which font we will use
zox_component(ZextSize, int)
zox_component(ZextDirty, unsigned char)
zox_byte_component(ZextAlignment)
zox_component(ZextPadding, byte2)
zox_component(AnimateZext, double) 
zox_memory_component(FontData, byte2) //! An array of points used for generating a font texture
zox_memory_component(ZextData, unsigned char)  //! Holds zigel indexes
// zoxel_util_includes
#include "util/default_font.c"
// zoxel_prefab_includes
#include "prefabs/font.c"
#include "prefabs/font_style.c"
#include "prefabs/zigel.c"
#include "util/zext_util.c"
#include "prefabs/zext.c"
// zoxel_system_declares
#include "systems/font_texture_system.c"
#include "systems/zext_update_system.c"
#include "systems/zext_background_update_system.c"
#include "systems/animate_text_system.c"
zox_reset_system(ZextDirtyResetSystem, ZextDirty)

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
zox_define_component(ZigelIndex)
zox_define_component(ZextSize)
zox_define_component(ZextDirty)
zox_define_component(AnimateZext)
zox_define_component(ZextAlignment)
zox_define_component(ZextPadding)
zox_define_memory_component(FontData)
zox_define_memory_component(ZextData)
// zoxel_filter_defines
zox_filter(zexts, [none] Zext, [in] ZextDirty)
zox_filter(fonts, [none] FontTexture, [out] GenerateTexture)
// zoxel_system_defines
zox_system(AnimateTextSystem, EcsOnUpdate, [out] AnimateZext, [out] ZextDirty, [out] ZextData)
zox_system_ctx(FontTextureSystem, EcsPostUpdate, fonts, [none] FontTexture, [out] TextureDirty, [out] TextureData, [in] TextureSize, [out] GenerateTexture, [in] ZigelIndex, [in] Color)
if (!headless) zox_system(ZextBackgroundUpdateSystem, EcsPostUpdate, [none] Zext, [in] ZextDirty, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] MeshAlignment, [in] CanvasLink, [out] PixelSize, [out] TextureSize, [out] GenerateTexture, [out] MeshVertices2D, [out] MeshDirty)
zox_system_ctx_1(ZextUpdateSystem, main_thread_pipeline, zexts, [none] Zext, [out] ZextDirty, [out] Children, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] Layer2D, [in] Position2D, [in] PixelSize, [in] MeshAlignment)
zoxel_end_module(Texts)

#endif