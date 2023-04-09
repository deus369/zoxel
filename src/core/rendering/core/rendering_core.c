#ifndef zoxel_rendering_core
#define zoxel_rendering_core

// 0 | EcsPreStore | EcsOnValidate
#define mesh_update_pipeline EcsPreStore
int mesh_update_pipeline2;
// 0 | EcsOnStore
#define render3D_update_pipeline 0     
#define render2D_update_pipeline 0
zoxel_memory_component(MeshVertices, float3)
zoxel_memory_component(MeshVertices2D, float2)
zoxel_memory_component(MeshUVs, float2)
zoxel_memory_component(MeshColors, color)
#include "components/mesh_indicies.c"
#include "components/material_gpu_link.c"
#include "components/texture_gpu_link.c"
#include "components/mesh_gpu_link.c"
#include "components/uvs_gpu_link.c"
#include "components/shader_gpu_link.c"
#include "util/mesh_util.c"
#include "util/render_util.c"
#include "systems/mesh_update_system.c"
#include "systems/mesh_colors_update_system.c"
#include "systems/mesh_uvs_update_system.c"
#include "systems/mesh2D_update_system.c"
#include "systems/mesh2D_uvs_update_system.c"
zoxel_reset_system(MeshDirtySystem, MeshDirty)
#include "render2D_systems/render2D_system.c"
#include "render2D_systems/render2D_mesh_system.c"
#include "render2D_systems/render2D_instance_system.c"
#include "render3D_systems/render3D_system.c"
#include "render3D_systems/render3D_instance_system.c"
#include "render3D_systems/render3D_colored_system.c"
#include "fun/render_loop.c"
#include "fun/resource_management.c"

zoxel_begin_module(RenderingCore)
zoxel_define_component(MaterialGPULink)
zoxel_define_component(TextureGPULink)
zoxel_define_component(MeshGPULink)
zoxel_define_component(UvsGPULink)
zoxel_define_memory_component(MeshIndicies)
zoxel_define_memory_component(MeshVertices)
zoxel_define_memory_component(MeshVertices2D)
zoxel_define_memory_component(MeshUVs)
zoxel_define_memory_component(MeshColors)
ecs_set_hooks(world, MaterialGPULink, { .dtor = ecs_dtor(MaterialGPULink) });
ecs_set_hooks(world, TextureGPULink, { .dtor = ecs_dtor(TextureGPULink) });
ecs_set_hooks(world, MeshGPULink, { .dtor = ecs_dtor(MeshGPULink) });
ecs_set_hooks(world, UvsGPULink, { .dtor = ecs_dtor(UvsGPULink) });
#ifdef zoxel_transforms2D
    zoxel_system_1(InstanceRender2DSystem, render2D_update_pipeline,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink,
        [none] !MeshGPULink);
    zoxel_system_1(RenderMaterial2DSystem, render2D_update_pipeline,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [in] MaterialGPULink,
        [in] TextureGPULink, [none] !MeshGPULink);
    zoxel_system_1(RenderMeshMaterial2DSystem, render2D_update_pipeline,
        [in] Position2D, [in] Rotation2D, [in] Scale1D,
        [in] Layer2D, [in] Brightness, [in] MeshGPULink,
        [in] MaterialGPULink, [in] TextureGPULink);
#endif
#ifdef zoxel_transforms3D
    zoxel_system_1(Render3DSystem, render3D_update_pipeline, [in] Position3D, [in] Rotation3D, [in] Scale1D,
        [in] Brightness, [in] MeshGPULink, [in] MaterialGPULink, [in] MeshIndicies, [none] !UvsGPULink, [none] !MeshColors);
    zoxel_system_1(Render3DColoredSystem, render3D_update_pipeline, [in] Position3D, [in] Rotation3D, [in] Scale1D,
        [in] Brightness, [in] MeshGPULink, [in] MaterialGPULink, [in] MeshIndicies, [none] !UvsGPULink, [none] MeshColors);
    zoxel_system_1(InstanceRender3DSystem, render3D_update_pipeline,
        [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink, [none] !MeshGPULink);
#endif
// gpu uploads
mesh_update_pipeline2 = mesh_update_pipeline;
zoxel_system_1(MeshUpdateSystem, mesh_update_pipeline, [out] MeshDirty, [in] MeshIndicies, [in] MeshVertices,
    [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshUVs, [none] !MeshColors);
zoxel_system_1(Mesh2DUpdateSystem, mesh_update_pipeline, [out] MeshDirty, [in] MeshIndicies, [in] MeshVertices2D,
    [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshUVs, [none] !MeshColors);
zoxel_system_1(MeshUvsUpdateSystem, mesh_update_pipeline, [out] MeshDirty, [in] MeshIndicies,
    [in] MeshVertices, [in] MeshUVs, [in] MeshGPULink, [in] MaterialGPULink, [in] UvsGPULink, [none] !MeshColors);
zoxel_system_1(Mesh2DUvsUpdateSystem, mesh_update_pipeline, [out] MeshDirty, [in] MeshIndicies,
    [in] MeshVertices2D, [in] MeshUVs, [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshColors);
zoxel_system_1(MeshColorsUpdateSystem, mesh_update_pipeline, [out] MeshDirty, [in] MeshIndicies,
    [in] MeshVertices, [in] MeshColors, [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshUVs);
// zoxel_define_reset_system(MeshDirtySystem, MeshDirty);
zoxel_end_module(RenderingCore)

//! \todo Create a Cube with unique mesh - for chunk - add these components and update mesh for voxel chunk.
//      - Test Mesh - simply create a test entity now with mesh and set to dirty
//      - set data as cube and render
//      - Animate rotate the cube - for testing
//! \todo GPU Meshes?

#endif