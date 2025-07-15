#include "ui_trail_system.c"
#include "element_mesh3D_system.c"
#include "element3D_render_system.c"
#include "elementbar3D_system.c"
#include "text_update_system.c"
#include "text3D_resize_system.c"

void define_systems_elements3D(ecs_world_t *world) {
    zox_system(UITrailSystem, zox_transforms_stage, [in] elements.core.UIHolderLink, [in] UITrail, [out] transforms3.Position3D)
    zox_system(Elementbar3DSystem, EcsOnUpdate, [in] elements.core.ElementBar, [in] elements.core.ElementBarSize, [in] hierarchys.Children, [none] rendering.core.MeshVertices)
    zox_system(TextUpdateSystem, EcsOnUpdate, [in] texts.ZextDirty, [in] texts.TextData, [in] hierarchys.Children, [none] texts.Zext) // , [none] Text3D)
    zox_system_1(Text3DResizeSystem, EcsOnUpdate, [in] texts.TextData, [in] zigels.FontOutlineColor, [in] zigels.FontFillColor, [in] zigels.FontThickness, [in] texts.ZextDirty, [in] rendering.RenderDisabled, [in] Text3DScale, [in] texts.TextSize, [out] hierarchys.Children, [none] texts.Zext, [none] Text3D)
    if (!headless) {
        zox_system_1(Element3DMeshSystem, zox_pip_mainthread, [none] Element3D, [in] layouts2.PixelSize, [in] elements.core.CanvasLink, [out] elements.core.InitializeElement, [out] rendering.MeshDirty, [out] textures.core.GenerateTexture,  [out] rendering.core.MeshGPULink, [out] rendering.core.UvsGPULink, [out] rendering.core.ColorsGPULink, [out] rendering.core.TextureGPULink)
        zox_render3D_plus_system(Element3DRenderSystem, [in] transforms3.TransformMatrix, [in] rendering.core.MeshGPULink, [in] rendering.core.UvsGPULink, [in] rendering.core.ColorsGPULink, [in] rendering.core.MeshIndicies, [in] rendering.core.TextureGPULink, [in] rendering.RenderDisabled, [none] rendering.core.SingleMaterial)
    }
}