#ifndef zoxel_rendering_core
#define zoxel_rendering_core

#define mesh_update_pipeline EcsPreStore // EcsOnValidate
#define render3D_update_pipeline EcsOnStore // 0, EcsOnStore
#define render2D_update_pipeline 0 // 0, EcsOnStore
zoxel_memory_component(MeshVertices, float3)
zoxel_memory_component(MeshVertices2D, float2)
zoxel_memory_component(MeshUVs, float2)
zoxel_memory_component(MeshColors, color)
#include "components/mesh_indicies.c"
#include "components/MaterialGPULink.c"
#include "components/TextureGPULink.c"
#include "components/mesh_gpu_link.c"
#include "components/uvs_gpu_link.c"
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
#include "render3D_systems/render3D_uvs_system.c"
#include "render3D_systems/render3D_instance_system.c"
#include "util/render_loop.c"

//! The rendering core Sub Module.
void RenderingCoreImport(ecs_world_t *world)
{
    zoxel_module(RenderingCore)
    zoxel_define_component(MaterialGPULink)
    zoxel_define_component(TextureGPULink)
    zoxel_define_component(MeshGPULink)
    zoxel_define_component(UvsGPULink)
    zoxel_memory_component_define(MeshIndicies)
    zoxel_memory_component_define(MeshVertices)
    zoxel_memory_component_define(MeshVertices2D)
    zoxel_memory_component_define(MeshUVs)
    zoxel_memory_component_define(MeshColors)
    ecs_set_hooks(world, MaterialGPULink, { .dtor = ecs_dtor(MaterialGPULink) });
    ecs_set_hooks(world, TextureGPULink, { .dtor = ecs_dtor(TextureGPULink) });
    ecs_set_hooks(world, MeshGPULink, { .dtor = ecs_dtor(MeshGPULink) });
    ecs_set_hooks(world, UvsGPULink, { .dtor = ecs_dtor(UvsGPULink) });
    // render2D
    zoxel_system_main_thread(world, InstanceRender2DSystem, render2D_update_pipeline,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink,
        [none] !MeshGPULink);
    zoxel_system_main_thread(world, RenderMaterial2DSystem, render2D_update_pipeline,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [in] MaterialGPULink,
        [in] TextureGPULink, [none] !MeshGPULink);
    zoxel_system_main_thread(world, RenderMeshMaterial2DSystem, render2D_update_pipeline,
        [in] Position2D, [in] Rotation2D, [in] Scale1D,
        [in] Layer2D, [in] Brightness, [in] MeshGPULink,
        [in] MaterialGPULink, [in] TextureGPULink);
    // render3D
    zoxel_system_main_thread(world, Render3DSystem, render3D_update_pipeline, // EcsOnStore,
        [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Brightness,
        [in] MeshGPULink, [in] MaterialGPULink, [in] MeshIndicies,
        [none] !UvsGPULink);
    zoxel_system_main_thread(world, Render3DUvsSystem, render3D_update_pipeline, // EcsOnStore,
        [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Brightness,
        [in] MeshGPULink, [in] MaterialGPULink, [in] UvsGPULink,
        [in] TextureGPULink, [in] MeshIndicies);
    zoxel_system_main_thread(world, InstanceRender3DSystem, render3D_update_pipeline,
        [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink, [none] !MeshGPULink);
    // updates
    zoxel_system_main_thread(world, MeshUpdateSystem, mesh_update_pipeline,
        [in] MeshDirty, [in] MeshIndicies,[in] MeshVertices,
        [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshUVs, [none] !MeshColors);
    zoxel_system_main_thread(world, Mesh2DUpdateSystem, mesh_update_pipeline,
        [in] MeshDirty, [in] MeshIndicies,[in] MeshVertices2D,
        [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshUVs, [none] !MeshColors);
    zoxel_system_main_thread(world, MeshUvsUpdateSystem, mesh_update_pipeline,
        [in] MeshDirty, [in] MeshIndicies, [in] MeshVertices, [in] MeshUVs,
        [in] MeshGPULink, [in] MaterialGPULink, [in] UvsGPULink,
        [none] !MeshColors);
    zoxel_system_main_thread(world, Mesh2DUvsUpdateSystem, mesh_update_pipeline,
        [in] MeshDirty, [in] MeshIndicies, [in] MeshVertices2D, [in] MeshUVs,
        [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshColors);
    zoxel_system_main_thread(world, MeshColorsUpdateSystem, mesh_update_pipeline,
        [in] MeshDirty, [in] MeshIndicies, [in] MeshVertices, [in] MeshColors,
        [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshUVs);
    zoxel_reset_system_define(MeshDirtySystem, MeshDirty);
}

//! \todo Create a Cube with unique mesh - for chunk - add these components and update mesh for voxel chunk.
//      - Test Mesh - simply create a test entity now with mesh and set to dirty
//      - set data as cube and render
//      - Animate rotate the cube - for testing
//! \todo GPU Meshes?
#endif