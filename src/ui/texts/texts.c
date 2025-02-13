#ifndef zox_mod_zexts
#define zox_mod_zexts

zox_declare_tag(Zext)
zox_declare_tag(ZextLabel)
zox_declare_tag(ZextRenderEnabler)
zox_component_byte(ZextDirty)
zox_component_byte(ZextAlignment)
zox_component_int(ZextSize)
zox_component_byte2(ZextPadding)
zox_component_double(AnimateZext)
zox_component_zext(ZextData)
#include "data/settings.c"
#include "data/zext_update.c"
#include "data/zext_spawn_data.c"
#include "util/zigel_util.c"
#include "util/resize_util.c"
#include "prefabs/prefabs.c"
#include "util/zext_util.c"
#include "systems/zext_update_system.c"
#include "systems/animate_text_system.c"
#include "systems/zext_background_system.c"
#include "systems/zext_parent_background_system.c"
zox_increment_system_with_reset(ZextDirty, zext_update_end)

zox_begin_module(Zexts)
    zox_define_tag(Zext)
    zox_define_tag(ZextLabel)
    zox_define_tag(ZextRenderEnabler)
    zox_define_component_byte(ZextDirty)
    zox_define_component_byte(ZextAlignment)
    zox_define_component_int(ZextSize)
    zox_define_component_byte2(ZextPadding)
    zox_define_component_double(AnimateZext)
    zox_define_component_zext(ZextData)
    // zox_filter(zexts, [none] Zext, [in] ZextDirty)
    zox_system(AnimateTextSystem, zox_pipelines_zext_textures, [out] AnimateZext, [out] ZextDirty, [out] ZextData)
    // zexts, zox_pip_mainthread
    zox_system_1(ZextUpdateSystem, EcsOnUpdate, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] Layer2D, [in] CanvasPosition, [in] PixelSize, [in] MeshAlignment, [in] FontOutlineColor, [in] FontFillColor, [in] FontThickness, [in] ZextDirty, [out] RenderDisabled, [out] Children, [none] Zext)
    if (!headless) zox_system(ZextParentBackgroundSystem, zox_pipelines_zext_backgrounds, [none] Zext, [in] ZextDirty, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] MeshAlignment, [in] CanvasLink, [in] ParentLink)
    if (!headless) zox_system(ZextBackgroundSystem, zox_pipelines_zext_backgrounds, [none] Zext, [in] ZextDirty, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] MeshAlignment, [in] CanvasLink, [out] PixelSize, [out] TextureSize, [out] GenerateTexture, [out] MeshVertices2D, [out] MeshDirty)
    zox_define_increment_system(ZextDirty, EcsOnLoad, [none] Zext)
    spawn_prefabs_texts(world);
zox_end_module(Zexts)

#endif
