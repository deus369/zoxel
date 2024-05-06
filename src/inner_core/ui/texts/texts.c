#ifndef zoxel_texts
#define zoxel_texts

// zoxel_settings
#define zox_pipelines_zext_backgrounds EcsPostUpdate
#define zox_pipelines_zext_textures EcsOnUpdate
const double zext_animation_speed = 10.0;
// zoxel_component_defines
zox_declare_tag(Zext)
zox_declare_tag(ZextLabel)
zox_component_byte(ZextDirty)
zox_component_byte(ZextAlignment)
zox_component_int(ZextSize)
zox_component_byte2(ZextPadding)
zox_component_double(AnimateZext)
zox_component_zext(ZextData)   // zigel indexes
// zoxel_util_includes
#include "util/zigel_util.c"
#include "util/resize_util.c"
// zoxel_prefab_includes
#include "prefabs/zext.c"
#include "util/zext_util.c"
// zoxel_system_declares
#include "systems/zext_update_system.c"
#include "systems/animate_text_system.c"
#include "systems/zext_background_system.c"
#include "systems/zext_parent_background_system.c"

int get_zexts_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Zext));
}

void spawn_prefabs_texts(ecs_world_t *world) {
    spawn_prefab_zext(world);
}

zox_begin_module(Zexts)
// zoxel_component_defines
zox_define_tag(Zext)
zox_define_tag(ZextLabel)
zox_define_component_byte(ZextDirty)
zox_define_component_byte(ZextAlignment)
zox_define_component_int(ZextSize)
zox_define_component_byte2(ZextPadding)
zox_define_component_double(AnimateZext)
zox_define_component_zext(ZextData)
// zoxel_filter_defines
zox_filter(zexts, [none] Zext, [in] ZextDirty)
// zoxel_system_defines
zox_system(AnimateTextSystem, zox_pipelines_zext_textures, [out] AnimateZext, [out] ZextDirty, [out] ZextData)
zox_system_ctx_1(ZextUpdateSystem, main_thread_pipeline, zexts, [none] Zext, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] Layer2D, [in] CanvasPosition, [in] PixelSize, [in] MeshAlignment, [in] RenderDisabled, [out] ZextDirty, [out] Children)
if (!headless) zox_system(ZextParentBackgroundSystem, zox_pipelines_zext_backgrounds, [none] Zext, [in] ZextDirty, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] MeshAlignment, [in] CanvasLink, [in] ParentLink)
if (!headless) zox_system(ZextBackgroundSystem, zox_pipelines_zext_backgrounds, [none] Zext, [in] ZextDirty, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] MeshAlignment, [in] CanvasLink, [out] PixelSize, [out] TextureSize, [out] GenerateTexture, [out] MeshVertices2D, [out] MeshDirty, [in] InitializeEntityMesh)
zoxel_end_module(Zexts)

#endif
