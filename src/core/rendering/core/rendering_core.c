#ifndef zoxel_rendering_core
#define zoxel_rendering_core
//! rendering core Module.

//! \todo Create a Cube with unique mesh - for chunk - add these components and update mesh for voxel chunk.
//      - Test Mesh - simply create a test entity now with mesh and set to dirty
//      - set data as cube and render
//      - Animate rotate the cube - for testing

const int custom_mesh_spawn_count = 64;
// Tags
ECS_DECLARE(Mesh);
ECS_DECLARE(ElementRender);
// components
//! Used to set the brightness of an entity.
zoxel_component(Brightness, float);
zoxel_memory_component(MeshIndicies, int);
zoxel_memory_component(MeshVertices, float);
#include "components/MaterialGPULink.c"
#include "components/TextureGPULink.c"
#include "components/MeshGPULink.c"
#include "components/TextureCoordinatesGPULink.c"
zoxel_component(EternalRotation, float4);
// util
#include "util/mesh_util.c"
// prefabs
#include "prefabs/custom_mesh.c"
// systems
#include "systems/eternal_rotation_system.c"
#include "systems/mesh_update_system.c"
#include "systems/render2D_instance_system.c"
#include "systems/render2D_system.c"
#include "systems/render3D_instance_system.c"
#include "systems/render3D_unique_system.c"

//! The rendering core Sub Module.
/**
*   \todo CPU Meshes?
*/
void RenderingCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, RenderingCore);
    // printf("Initializing rendering core.");
    ECS_TAG_DEFINE(world, Mesh);
    ECS_TAG_DEFINE(world, ElementRender);
    // components
    ECS_COMPONENT_DEFINE(world, Brightness);
    zoxel_memory_component_define(world, MeshIndicies);
    zoxel_memory_component_define(world, MeshVertices);
    ECS_COMPONENT_DEFINE(world, MaterialGPULink);
    ECS_COMPONENT_DEFINE(world, TextureGPULink);
    ECS_COMPONENT_DEFINE(world, MeshGPULink);
    ECS_COMPONENT_DEFINE(world, TextureCoordinatesGPULink);
    ECS_COMPONENT_DEFINE(world, EternalRotation);
    // gpu destruction hooks
    ecs_set_hooks(world, MaterialGPULink, { .dtor = ecs_dtor(MaterialGPULink) });
    ecs_set_hooks(world, TextureGPULink, { .dtor = ecs_dtor(TextureGPULink) });
    ecs_set_hooks(world, MeshGPULink, { .dtor = ecs_dtor(MeshGPULink) });
    ecs_set_hooks(world, TextureCoordinatesGPULink, { .dtor = ecs_dtor(TextureCoordinatesGPULink) });
    // move this to animations systems
    ECS_SYSTEM_DEFINE(world, EternalRotationSystem, EcsOnUpdate, [out] Rotation, [in] EternalRotation);
    // systems
    ECS_SYSTEM_DEFINE(world, InstanceRender2DSystem, 0,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink, [none] !MeshGPULink);
    ECS_SYSTEM_DEFINE(world, RenderMaterial2DSystem, 0,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [in] MaterialGPULink, [in] TextureGPULink, [none] !MeshGPULink);
    ECS_SYSTEM_DEFINE(world, RenderMaterial2DScale2DSystem, 0,
        [in] Position2D, [in] Rotation2D, [in] Scale2D, [in] Brightness, [in] MaterialGPULink, [in] TextureGPULink, [none] !MeshGPULink);
    ECS_SYSTEM_DEFINE(world, RenderMeshMaterial2DSystem, 0,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [in] MeshGPULink, [in] MaterialGPULink, [in] TextureGPULink);
    ECS_SYSTEM_DEFINE(world, InstanceRender3DSystem, 0,
        [in] Position, [in] Rotation, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink, [none] !MeshGPULink);
    ECS_SYSTEM_DEFINE(world, Render3DUniqueSystem, 0,
        [in] Position, [in] Rotation, [in] Scale1D, [in] Brightness, [in] MeshGPULink, [in] MaterialGPULink, [in] MeshIndicies);
    ECS_SYSTEM_DEFINE(world, MeshUpdateSystem, EcsOnValidate,
        [in] generic.EntityDirty, [in] MeshIndicies, [in] MeshVertices, [in] MeshGPULink, [in] MaterialGPULink);
    spawn_custom_mesh_prefab(world);
    //spawn_custom_mesh(world, custom_mesh_prefab, (float3) { 0, 0.6f, 0});
    //spawn_custom_mesh(world, custom_mesh_prefab, (float3) { 0.2f, 0.6f, 0});
    #ifdef zoxel_test_cubes
    float2 spawnBounds = { 2.2f, 1.2f };
    for (int i = 0; i < custom_mesh_spawn_count; i++)
    {
        spawn_custom_mesh(world, custom_mesh_prefab, (float3) {
            -spawnBounds.x + (rand() % 100) * 0.02f * spawnBounds.x,
            -spawnBounds.y + (rand() % 100) * 0.02f * spawnBounds.y, 0 });
    }
    #endif
}

//set_mesh_indicies(world, e, cubeIndicies3, 12);
//set_mesh_vertices(world, e, cubeVertices3, 24);

// printf("instanceShader3D: %i %i\n", instanceShader3D.x, instanceShader3D.y);
/*const MeshIndicies *meshIndicies = ecs_get(world, e, MeshIndicies);
for (int j = 0; j < meshIndicies->length; j++)
{
    printf("    - (2) Index [%i] is [%i]\n", j, meshIndicies->value[j]);
}
const MeshVertices *meshVertices = ecs_get(world, e, MeshVertices);
for (int j = 0; j < meshVertices->length; j++)
{
    printf("    - (2) Vertex [%i] is [%fx%fx%f]\n", j, meshVertices->value[j].x, meshVertices->value[j].y, meshVertices->value[j].z);
}*///,
        //.move = ecs_move(MaterialGPULink),
        //.dtor = ecs_dtor(MaterialGPULink)
#endif