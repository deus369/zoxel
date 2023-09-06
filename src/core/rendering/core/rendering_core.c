#ifndef zoxel_rendering_core
#define zoxel_rendering_core

// zoxel_settings
#define render3D_update_pipeline 0
#define render2D_update_pipeline 0
// zoxel_component_includes
zox_declare_tag(Shader)
zox_declare_tag(Material)
zox_declare_tag(SingleMaterial)
zox_memory_component(MeshVertices, float3)
zox_memory_component(MeshVertices2D, float2)
zox_memory_component(MeshUVs, float2)
zox_memory_component(MeshColors, color)
zox_memory_component(MeshColorRGBs, color_rgb)
#include "components/mesh_indicies.c"
#include "components/material_gpu_link.c"
#include "components/texture_gpu_link.c"
#include "components/mesh_gpu_link.c"
#include "components/uvs_gpu_link.c"
#include "components/colors_gpu_link.c"
#include "components/shader_gpu_link.c"
// zoxel_util_includes
#include "util/mesh_util.c"
// zoxel_prefab_includes
#include "prefabs/shader.c"
#include "prefabs/material.c"
// zoxel_system_includes
#include "systems/mesh_restore_system.c"
#include "systems/mesh_dispose_system.c"
// zox_reset_system(MeshDirtySystem, MeshDirty)
#include "render2D_systems/mesh2D_update_system.c"
#include "render2D_systems/mesh2D_uvs_update_system.c"
#include "render2D_systems/render2D_system.c"
#include "render2D_systems/render2D_instance_system.c"
#include "render2D_systems/element_render_system.c" // move to ui core
// zoxel_function_includes
#include "fun/render_loop.c"
#include "fun/gpu_dispose.c"
#include "fun/gpu_restore.c"

void spawn_prefabs_rendering_core(ecs_world_t *world) {
    spawn_prefab_shader(world);
    spawn_prefab_material(world);
}

void on_close_rendering_core(ecs_world_t *world) {
    dispose_render_loop();
}

zox_begin_module(RenderingCore)
initialize_render_loop();
// zoxel_component_defines
zox_define_tag(Shader)
zox_define_tag(Material)
zox_define_tag(SingleMaterial)
zox_define_component(MaterialInstancedGPULink)
zox_define_component_w_dest(ShaderGPULink)
zox_define_component_w_dest(MaterialGPULink)
zox_define_component_w_dest(TextureGPULink)
zox_define_component_w_dest(MeshGPULink)
zox_define_component_w_dest(UvsGPULink)
zox_define_component_w_dest(ColorsGPULink)
zox_define_memory_component(MeshIndicies)
zox_define_memory_component(MeshVertices)
zox_define_memory_component(MeshVertices2D)
zox_define_memory_component(MeshUVs)
zox_define_memory_component(MeshColors)
zox_define_memory_component(MeshColorRGBs)
// zoxel_system_defines
#ifdef zoxel_transforms2D
    zox_system_1(InstanceRender2DSystem, render2D_update_pipeline, [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink, [none] !MeshGPULink)
    zox_system_1(RenderMaterial2DSystem, render2D_update_pipeline, [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [in] MaterialGPULink, [in] TextureGPULink, [none] !MeshGPULink)
    zox_system_1(ElementRenderSystem, render2D_update_pipeline, [none] ElementRender, [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Layer2D, [in] Brightness, [in] MeshGPULink, [in] UvsGPULink, [in] MaterialInstancedGPULink, [in] TextureGPULink, [in] MeshDirty)
#endif
// gpu restore/dispose
zox_system_1(MeshGPUDisposeSystem, 0, [in] MeshGPULink)
zox_system_1(MeshColorsGPUDisposeSystem, 0,[in] ColorsGPULink)
zox_system_1(MeshUvsGPUDisposeSystem, 0,[in] UvsGPULink)
zox_system_1(ShaderGPUDisposeSystem, 0, [in] ShaderGPULink)
zox_system_1(MeshGPURestoreSystem, 0, [out] MeshDirty)
zox_system_1(Mesh2DUvsUpdateSystem, main_thread_pipeline, [out] MeshDirty, [in] MeshIndicies, [in] MeshVertices2D, [in] MeshUVs, [in] MeshGPULink, [in] UvsGPULink, [none] !MeshColorRGBs)
zoxel_end_module(RenderingCore)

#endif

// zox_system_1(Mesh2DUpdateSystem, main_thread_pipeline, [out] MeshDirty, [in] MeshIndicies, [in] MeshVertices2D, [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshUVs, [none] !MeshColorRGBs)
// zox_system_1(Mesh2DInstancedUpdateSystem, main_thread_pipeline, [out] MeshDirty, [in] MeshIndicies, [in] MeshVertices2D, [in] MeshGPULink, [in] MaterialInstancedGPULink, [none] !MeshUVs, [none] !MeshColorRGBs)
