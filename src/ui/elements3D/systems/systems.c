#include "ui_trail_system.c"
#include "element_mesh3D_system.c"
#include "element3D_render_system.c"
#include "elementbar3D_system.c"
#include "text_update_system.c"
#include "text3D_resize_system.c"

void define_systems_elements3D(ecs_world_t *world) {
    if (!headless) {
        zox_system_1(Element3DMeshSystem, zox_pip_mainthread, [none] Element3D, [in] PixelSize, [in] CanvasLink, [out] InitializeElement, [out] MeshDirty, [out] GenerateTexture,  [out] MeshGPULink, [out] UvsGPULink, [out] ColorsGPULink, [out] TextureGPULink)
        zox_render3D_plus_system(Element3DRenderSystem, [in] TransformMatrix, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] TextureGPULink, [in] RenderDisabled, [none] rendering.core.SingleMaterial)
    }
    zox_system(UITrailSystem, zox_transforms_stage, [in] UIHolderLink, [in] UITrail, [out] Position3D)
    zox_system(Elementbar3DSystem, EcsOnUpdate, [in] ElementBar, [in] ElementBarSize, [in] Children, [none] MeshVertices)
    zox_system(TextUpdateSystem, EcsOnUpdate, [in] ZextDirty, [in] TextData, [in] Children, [none] zexts.Zext) // , [none] Text3D)
    zox_system_1(Text3DResizeSystem, EcsOnUpdate, [in] TextData, [in] FontOutlineColor, [in] FontFillColor, [in] FontThickness, [in] ZextDirty, [in] RenderDisabled, [in] Text3DScale, [out] Children, [none] zexts.Zext, [none] Text3D)
}