#ifndef Zoxel_Voxels_Core
#define Zoxel_Voxels_Core

const double noiseChunkAnimateSpeed = 0.25; // 1 / 8.0;
const float overall_voxel_scale = 2.0f;
const int chunk_length = 32;
const int dissapearChance = 92;
const float spawnRange = 0.22f;
const int3 chunk_size = { chunk_length, chunk_length, chunk_length };
ecs_entity_t voxel_prefab;
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
//! A state for animating textures.
zoxel_component(AnimateChunk, double);
// util
#include "util/chunk.c"
// prefabs
#include "prefabs/chunk.c"
// systems
#include "systems/generate_chunk_reset_system.c"
#include "systems/noise_chunk_system.c"
#include "systems/chunk_build_system.c"
#include "systems/animate_chunk_system.c"

void spawn_voxel_chunk_mesh_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, custom_mesh_prefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "voxel_prefab");
    // ecs_set(world, e, EntityDirty, { 0 });
    add_seed(world, e, 666);
    add_chunk(world, e, chunk_size);
    add_noise_chunk(world, e);
    zoxel_add_component(world, e, AnimateChunk);
    // zoxel_set_component(world, e, AnimateChunk, { - (rand() % noiseChunkAnimateSpeed) }); // 0.0 });
    voxel_prefab = e;
}

void spawn_voxel_chunk_mesh(ecs_world_t *world, float3 position)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, voxel_prefab);
    ecs_set(world, e, Position, { position }); // {{ 0, 0.6f, 0 }});
    ecs_set(world, e, Rotation, {{ 0, 0, 0, 1.0f }});
    ecs_set(world, e, Scale1D, { 0.05f });
    ecs_set(world, e, Brightness, { 1.4f });
    ecs_set(world, e, AnimateChunk, { (((rand() % 100) / 100.0f) * noiseChunkAnimateSpeed) }); // 0.0 });
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, instanceShader3D);
    // printf("Spawned Character2D [%lu]\n", (long unsigned int) e);
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
    ECS_COMPONENT_DEFINE(world, AnimateChunk);
    // filters
    // zoxel_filter(generateChunkQuery, world, [none] NoiseChunk, [in] GenerateChunk);
    zoxel_filter(generateChunkQuery, world, [none] NoiseChunk, [in] GenerateChunk);
    // zoxel_filter(chunkDirtyQuery, world, [none] NoiseChunk, [in] EntityDirty);
    // systems
    ECS_SYSTEM_DEFINE(world, AnimateChunkSystem, EcsOnUpdate, [out] AnimateChunk, [out] GenerateChunk);
    zoxel_system_ctx(world, NoiseChunkSystem, EcsOnUpdate, generateChunkQuery,
        [none] NoiseChunk, [out] generic.EntityDirty, [out] Chunk, [in] ChunkSize, [in] GenerateChunk);
    zoxel_system_ctx(world, ChunkBuildSystem, EcsOnUpdate, generateChunkQuery,
        [in] generic.EntityDirty, [in] Chunk, [in] ChunkSize, [out] MeshIndicies, [out] MeshVertices);
    zoxel_system_main_thread(world, GenerateChunkResetSystem, EcsPostUpdate, [out] GenerateChunk);
    //spawn_chunk_prefab(world);
    //spawn_chunk(world);
    spawn_voxel_chunk_mesh_prefab(world);
    spawn_voxel_chunk_mesh(world, (float3) { 0, -spawnRange, 0 });
    spawn_voxel_chunk_mesh(world, (float3) { 0, spawnRange, 0 });
    spawn_voxel_chunk_mesh(world, (float3) { -spawnRange, 0, 0 });
    spawn_voxel_chunk_mesh(world, (float3) { spawnRange, 0, 0 });
}

// components
// #include "components/ChunkLinks.c"
// ECS_COMPONENT_DECLARE(ChunkLinks);
//! Stores voxels, in an oct tree.
/**
*   \todo Store Tree Nodes as entities. Each tree node can be open or closed.
*/
#endif