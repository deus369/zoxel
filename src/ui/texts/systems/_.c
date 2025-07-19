#include "text2D_resize_system.c"
#include "animate_text_system.c"
#include "zext_background_system.c"
#include "zext_parent_background_system.c"
zox_increment_system_with_reset(ZextDirty, zext_update_end)

void define_systems_texts(ecs_world_t *world) {
    zox_define_increment_system(ZextDirty, EcsOnLoad, [none] Zext)
    zox_system(AnimateTextSystem, zox_pipelines_zext_textures,
        [out] AnimateZext,
        [out] texts.ZextDirty,
        [out] texts.TextData)
    zox_system_1(Text2DResizeSystem, EcsPreStore,
        [in] texts.TextData,
        [in] texts.TextSize,
        [in] TextPadding,
        [in] elements.core.Layer2D,
        [in] elements.core.CanvasPosition,
        [in] layouts2.PixelSize,
        [in] rendering.MeshAlignment,
        [in] zigels.FontOutlineColor,
        [in] zigels.FontFillColor,
        [in] zigels.FontThickness,
        [in] zigels.FontOutlineThickness,
        [in] TextResolution,
        [in] texts.ZextDirty,
        [out] rendering.RenderDisabled,
        [out] hierarchys.Children,
        [none] Zext,
        [none] Text2D)
    if (!headless) {
        zox_system(ZextParentBackgroundSystem, zox_pipelines_zext_backgrounds,
            [none] Zext,
            [in] texts.ZextDirty,
            [in] texts.TextData,
            [in] texts.TextSize,
            [in] TextPadding,
            [in] rendering.MeshAlignment,
            [in] elements.core.CanvasLink,
            [in] hierarchys.ParentLink)
        zox_system(ZextBackgroundSystem, zox_pipelines_zext_backgrounds,
            [none] Zext,
            [in] texts.ZextDirty,
            [in] texts.TextData,
            [in] texts.TextSize,
            [in] TextPadding,
            [in] rendering.MeshAlignment,
            [in] elements.core.CanvasLink,
            [out] layouts2.PixelSize,
            [out] textures.core.TextureSize,
            [out] textures.core.GenerateTexture,
            [out] rendering.core.MeshVertices2D,
            [out] rendering.MeshDirty)
    }
}