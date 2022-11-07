#ifndef Zoxel_Voxels_Core
#define Zoxel_Voxels_Core

// tags
ECS_DECLARE(Vox);
ECS_DECLARE(NoiseChunk);
//! A simple chunk with an array of voxels.
zoxel_memory_component(Chunk, unsigned char);
//! A simple chunk with an array of voxels.
zoxel_component(ChunkSize, int3);
//! A state for generating chunks.
zoxel_component(GenerateChunk, unsigned char);
//! A local position of a chunk inside a Vox.
zoxel_component(ChunkPosition, int3);
//! A list to all chunks in a Vox model.
zoxel_memory_component(ChunkLinks, ecs_entity_t);
// prefabs
#include "prefabs/chunk.c"
// util
#include "util/chunk.c"
// systems
#include "systems/GenerateChunkResetSystem.c"
#include "systems/NoiseChunkSystem.c"
#include "systems/ChunkBuildSystem.c"

ecs_entity_t voxel_prefab;

void spawn_voxel_chunk_mesh_prefab(ecs_world_t *world)
{
    const int3 size = { 16, 16, 16 };
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, custom_mesh_prefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "voxel_prefab");
    // ecs_set(world, e, EntityDirty, { 0 });
    add_seed(world, e, 666);
    add_chunk(world, e, size);
    add_noise_chunk(world, e);
    voxel_prefab = e;
}

void spawn_voxel_chunk_mesh(ecs_world_t *world, float3 position)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, voxel_prefab);
    ecs_set(world, e, Position, { position }); // {{ 0, 0.6f, 0 }});
    ecs_set(world, e, Rotation, {{ 0, 0, 0, 1.0f }});
    ecs_set(world, e, Scale1D, { 0.05f });
    ecs_set(world, e, Brightness, { 1.4f });
    // printf("Spawned Character2D [%lu]\n", (long unsigned int) e);
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, instanceShader3D);
    // set_mesh_indicies(world, e, cubeIndicies, 36);
    // set_mesh_vertices(world, e, cubeVertices, 24);
    custom_mesh = e;
}

//! The voxels core Sub Module.
/**
*   \todo First use a Point Render system to render voxel data.
*   \todo Spawn an Oct Node of 1 Voxel, if open, create 8 sub chunk nodes. 
*   \todo Only push voxel data to the GPU.
*/
void VoxelsCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, VoxelsCore);
    ECS_TAG_DEFINE(world, Vox);
    ECS_TAG_DEFINE(world, NoiseChunk);
    zoxel_memory_component_define(world, Chunk);
    ECS_COMPONENT_DEFINE(world, ChunkSize);
    ECS_COMPONENT_DEFINE(world, GenerateChunk);
    ECS_COMPONENT_DEFINE(world, ChunkPosition);
    zoxel_memory_component_define(world, ChunkLinks);
    // filters
    // zoxel_filter(generateChunkQuery, world, [none] NoiseChunk, [in] GenerateChunk);
    zoxel_filter(generateChunkQuery, world, [none] NoiseChunk, [in] GenerateChunk);
    // zoxel_filter(chunkDirtyQuery, world, [none] NoiseChunk, [in] EntityDirty);
    // systems
    zoxel_system_ctx(world, NoiseChunkSystem, EcsOnUpdate, generateChunkQuery,
        [none] NoiseChunk, [out] generic.EntityDirty, [out] Chunk, [in] ChunkSize, [in] GenerateChunk);
    zoxel_system_ctx(world, ChunkBuildSystem, EcsOnUpdate, generateChunkQuery,
        [in] generic.EntityDirty, [in] Chunk, [in] ChunkSize, [out] MeshIndicies, [out] MeshVertices);
    zoxel_system_main_thread(world, GenerateChunkResetSystem, EcsPostUpdate, [out] GenerateChunk);
    //spawn_chunk_prefab(world);
    //spawn_chunk(world);
    spawn_voxel_chunk_mesh_prefab(world);
    spawn_voxel_chunk_mesh(world, (float3) { 0, 0, 0 });
}

// components
// #include "components/ChunkLinks.c"
// ECS_COMPONENT_DECLARE(ChunkLinks);
//! Stores voxels, in an oct tree.
/**
*   \todo Store Tree Nodes as entities. Each tree node can be open or closed.
*/
#endif