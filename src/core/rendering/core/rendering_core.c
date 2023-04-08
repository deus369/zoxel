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
#include "util/render_loop.c"

extern ecs_entity_t main_terrain_world;
extern ecs_entity_t *terrain_chunks;
extern int terrain_chunks_count;

void delete_all_opengl_resources(ecs_world_t *world) {
    // delete opengl resources
    // shaders, textures,
    dispose_opengl();
    const MaterialGPULink *materialGPULink = ecs_get(world, main_terrain_world, MaterialGPULink);
    if (materialGPULink->value != 0) {
        glDeleteProgram(materialGPULink->value);
    }
    const TextureGPULink *textureGPULink = ecs_get(world, main_terrain_world, TextureGPULink);
    if (textureGPULink->value != 0) {
        glDeleteTextures(1, &textureGPULink->value);
    }
    for (int i = 0; i < terrain_chunks_count; i++) {
        ecs_entity_t terrain_chunk = terrain_chunks[i];
        // zoxel_log("     + setting chunk [%lu] to material [%i]\n", terrain_chunk, material_id);
        ecs_set(world, terrain_chunk, MeshDirty, { 1 });
        const MeshGPULink *meshGPULink = ecs_get(world, terrain_chunk, MeshGPULink);
        if (meshGPULink->value.x != 0) {
            glDeleteBuffers(1, &meshGPULink->value.x);
        }
        if (meshGPULink->value.y != 0) {
            glDeleteBuffers(1, &meshGPULink->value.y);
        }
        const UvsGPULink *uvsGPULink = ecs_get(world, terrain_chunk, UvsGPULink);
        if (uvsGPULink->value != 0) {
            glDeleteBuffers(1, &uvsGPULink->value);
        }
    }
}

void restore_all_opengl_resources(ecs_world_t *world) {
    // restore opengl resources here
    zoxel_log(" > restoring all opengl resources\n");
    load_all_shaders();
    #ifndef voxels_terrain_multi_material
        GLuint material_id = spawn_gpu_material_program(shader3D_textured);
        ecs_set(world, main_terrain_world, MaterialGPULink, { material_id });
        ecs_set(world, main_terrain_world, TextureDirty, { 1 });
    #endif
    for (int i = 0; i < terrain_chunks_count; i++) {
        ecs_entity_t terrain_chunk = terrain_chunks[i];
        // zoxel_log("     + setting chunk [%lu] to material [%i]\n", terrain_chunk, material_id);
        ecs_set(world, terrain_chunk, MeshDirty, { 1 });
        // ecs_set(world, terrain_chunk, TextureDirty, { 1 });
    }
}

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
    zoxel_system_1(Render3DSystem, render3D_update_pipeline, // EcsOnStore,
        [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Brightness,
        [in] MeshGPULink, [in] MaterialGPULink, [in] MeshIndicies,
        [none] !UvsGPULink);
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