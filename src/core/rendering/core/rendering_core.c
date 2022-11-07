#ifndef Zoxel_RenderingCore
#define Zoxel_RenderingCore
//! rendering core Module.

//! \todo Create a Cube with unique mesh - for chunk - add these components and update mesh for voxel chunk.
//      - Test Mesh - simply create a test entity now with mesh and set to dirty
//      - set data as cube and render
//      - Animate rotate the cube - for testing

const int custom_mesh_spawn_count = 64;
// Tags
ECS_DECLARE(Mesh);
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
// systems
#include "systems/InstanceRender2DSystem.c"
#include "systems/RenderMaterial2DSystem.c"
#include "systems/InstanceRender3DSystem.c"
#include "systems/InstanceRender3D2System.c"
#include "systems/MeshUpdateSystem.c"
#include "systems/EternalRotationSystem.c"

void set_mesh_indicies(MeshIndicies* meshIndicies, const int indicies[], int length)
{
    printf("2 - MeshIndicies: %i\n", meshIndicies->length);
    re_initialize_memory_component(meshIndicies, int, length);
    for (int i = 0; i < meshIndicies->length; i++)
    {
        meshIndicies->value[i] = indicies[i];
    }
}

void set_mesh_vertices(MeshVertices* meshVertices, const float vertices[], int length)
{
    re_initialize_memory_component(meshVertices, float, length);
    for (int i = 0; i < meshVertices->length; i++)
    {
        meshVertices->value[i] = vertices[i];
    }
}

void set_mesh_indicies_world(ecs_world_t *world, ecs_entity_t e, const int indicies[], int length)
{
    // printf("set_mesh_indicies length %i\n", length);
    MeshIndicies *meshIndicies = ecs_get_mut(world, e, MeshIndicies);
    initialize_memory_component(meshIndicies, int, length);
    for (int i = 0; i < meshIndicies->length; i++)
    {
        meshIndicies->value[i] = indicies[i];
        // printf("Index [%i] is [%i]\n", i, indicies[i]);
    }
    ecs_modified(world, e, MeshIndicies);
}

void set_mesh_vertices_world(ecs_world_t *world, ecs_entity_t e, const float vertices[], int length)
{
    // printf("set_mesh_vertices length %i\n", length);
    MeshVertices *meshVertices = ecs_get_mut(world, e, MeshVertices);
    initialize_memory_component(meshVertices, float, length);
    for (int i = 0; i < meshVertices->length; i++)
    {
        meshVertices->value[i] = vertices[i];
        // printf("Vertex [%i] is [%fx%fx%f]\n", i, vertices[i].x,  vertices[i].y, vertices[i].z);
    }
    ecs_modified(world, e, MeshVertices);
}

ecs_entity_t custom_mesh;
ecs_entity_t custom_mesh_prefab;

void spawn_custom_mesh_prefab(ecs_world_t *world)
{
    // int2 textureSize = { 16, 16 };
    custom_mesh_prefab = ecs_new_prefab(world, "test_custom_mesh");
    // printf("Spawned test_custom_mesh [%lu].\n", (long int) (e));
    #ifdef zoxel_transforms3D
    add_transform3Ds(world, custom_mesh_prefab);
    #endif
    // add_seed(world, custom_mesh_prefab, 444);
    zoxel_set_component(world, custom_mesh_prefab, EntityDirty, { 1 });
    zoxel_add_component(world, custom_mesh_prefab, MeshIndicies);
    zoxel_add_component(world, custom_mesh_prefab, MeshVertices);
    add_gpu_mesh(world, custom_mesh_prefab);
    add_gpu_material(world, custom_mesh_prefab);
    float4 rotationer = quaternion_from_euler( (float3) { 0.1f * degreesToRadians, 0.2f * degreesToRadians, 0 });
    zoxel_set_component(world, custom_mesh_prefab, EternalRotation, { rotationer });
    zoxel_add_component(world, custom_mesh_prefab, Brightness);
    // spawn prefab
}

void spawn_custom_mesh(ecs_world_t *world, ecs_entity_t prefab, float3 position)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, custom_mesh_prefab);
    ecs_set(world, e, Position, { position }); // {{ 0, 0.6f, 0 }});
    ecs_set(world, e, Rotation, {{ 0, 0, 0, 1.0f }});
    ecs_set(world, e, Scale1D, { 0.05f });
    ecs_set(world, e, Brightness, { 1.4f });
    // printf("Spawned Character2D [%lu]\n", (long unsigned int) e);
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, instanceShader3D);
    set_mesh_indicies_world(world, e, cubeIndicies, 36);
    set_mesh_vertices_world(world, e, cubeVertices, 24);
    custom_mesh = e;
}

//! The rendering core Sub Module.
/**
*   \todo CPU Meshes?
*/
void RenderingCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, RenderingCore);
    // printf("Initializing rendering core.");
    ECS_TAG_DEFINE(world, Mesh);
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
    ecs_set_hooks(world, MaterialGPULink, {
        .ctor = ecs_ctor(MaterialGPULink),
        .move = ecs_move(MaterialGPULink),
        .dtor = ecs_dtor(MaterialGPULink)
    });
    ecs_set_hooks(world, TextureGPULink, { .dtor = ecs_dtor(TextureGPULink) });
    ecs_set_hooks(world, MeshGPULink, { .dtor = ecs_dtor(MeshGPULink) });
    ecs_set_hooks(world, TextureCoordinatesGPULink, { .dtor = ecs_dtor(TextureCoordinatesGPULink) });
    // systems
    ECS_SYSTEM_DEFINE(world, InstanceRender2DSystem, 0,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink, [none] !MeshGPULink);
    ECS_SYSTEM_DEFINE(world, RenderMaterial2DSystem, 0,
        [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [in] MaterialGPULink, [in] TextureGPULink, [none] !MeshGPULink);
    ECS_SYSTEM_DEFINE(world, InstanceRender3DSystem, 0,
        [in] Position, [in] Rotation, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink, [none] !MeshGPULink);
    ECS_SYSTEM_DEFINE(world, InstanceRender3D2System, 0,
        [in] Position, [in] Rotation, [in] Scale1D, [in] Brightness, [in] MeshGPULink, [in] MaterialGPULink, [in] MeshIndicies);
    ECS_SYSTEM_DEFINE(world, EternalRotationSystem, EcsOnUpdate, [out] Rotation, [in] EternalRotation);
    ECS_SYSTEM_DEFINE(world, MeshUpdateSystem, EcsOnValidate,
        [in] generic.EntityDirty, [in] MeshIndicies, [in] MeshVertices, [in] MeshGPULink, [in] MaterialGPULink);
    spawn_custom_mesh_prefab(world);
    //spawn_custom_mesh(world, custom_mesh_prefab, (float3) { 0, 0.6f, 0});
    //spawn_custom_mesh(world, custom_mesh_prefab, (float3) { 0.2f, 0.6f, 0});
    float2 spawnBounds = { 2.2f, 1.2f };
    for (int i = 0; i < custom_mesh_spawn_count; i++)
    {
        spawn_custom_mesh(world, custom_mesh_prefab, (float3) {
            -spawnBounds.x + (rand() % 100) * 0.02f * spawnBounds.x,
            -spawnBounds.y + (rand() % 100) * 0.02f * spawnBounds.y, 0 });
    }
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
}*/
#endif