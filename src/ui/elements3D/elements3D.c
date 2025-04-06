#ifndef zox_elements3D
#define zox_elements3D

// #define zox_enable_log_elements3D
#if defined(zox_enable_log_elements3D) && !defined(zox_disable_logs)
    #define zox_log_elements3D(msg, ...) zox_log_line(msg, ##__VA_ARGS__)
#else
    #define zox_log_elements3D(msg, ...) { }
#endif
zox_declare_tag(Element3D)
zox_component_float3(UITrail)
#include "util/prefab.c"
#include "util/can_render.c"
#include "data/data.c"
#include "prefabs/prefabs.c"
#include "systems/ui_trail_system.c"
#include "systems/element_mesh3D_system.c"
#include "systems/element3D_render_system.c"
#include "systems/elementbar3D_system.c"

zox_begin_module(Elements3D)
    zox_define_tag(Element3D)
    zox_define_component(UITrail)
    zox_system(UITrailSystem, zox_transforms_stage, [in] UIHolderLink, [in] UITrail, [out] Position3D)
    zox_system(Elementbar3DSystem, EcsOnUpdate, [in] ElementBar, [in] ElementBarSize, [in] Children, [none] MeshVertices)
    if (!headless) {
        zox_system_1(Element3DMeshSystem, zox_pip_mainthread, [none] Element3D, [in] PixelSize, [in] CanvasLink, [out] InitializeElement, [out] MeshDirty, [out] GenerateTexture,  [out] MeshGPULink, [out] UvsGPULink, [out] ColorsGPULink, [out] TextureGPULink)
        zox_render3D_plus_system(Element3DRenderSystem, [in] TransformMatrix, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] TextureGPULink, [in] RenderDisabled, [none] rendering.core.SingleMaterial)
    }
    spawn_prefabs_elements3D(world);
zox_end_module(Elements3D)

#endif