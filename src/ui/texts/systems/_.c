#include "text2D_resize_system.c"
#include "animate_text_system.c"
#include "zext_background_system.c"
#include "zext_parent_background_system.c"
zox_increment_system_with_reset(ZextDirty, zext_update_end)

void define_systems_texts(ecs_world_t *world) {
    zox_system(AnimateTextSystem, zox_pipelines_zext_textures, [out] AnimateZext, [out] ZextDirty, [out] TextData)
    zox_system_1(Text2DResizeSystem, EcsPreStore, [in] TextData, [in] TextSize, [in] TextPadding, [in] Layer2D, [in] CanvasPosition, [in] PixelSize, [in] MeshAlignment, [in] FontOutlineColor, [in] FontFillColor, [in] FontThickness, [in] FontOutlineThickness, [in] TextResolution, [in] ZextDirty, [out] RenderDisabled, [out] Children, [none] Zext, [none] Text2D)
    zox_define_increment_system(ZextDirty, EcsOnLoad, [none] Zext)
    if (!headless) {
        zox_system(ZextParentBackgroundSystem, zox_pipelines_zext_backgrounds, [none] Zext, [in] ZextDirty, [in] TextData, [in] TextSize, [in] TextPadding, [in] MeshAlignment, [in] CanvasLink, [in] ParentLink)
        zox_system(ZextBackgroundSystem, zox_pipelines_zext_backgrounds, [none] Zext, [in] ZextDirty, [in] TextData, [in] TextSize, [in] TextPadding, [in] MeshAlignment, [in] CanvasLink, [out] PixelSize, [out] TextureSize, [out] GenerateTexture, [out] MeshVertices2D, [out] MeshDirty)
    }
}