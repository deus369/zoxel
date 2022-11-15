#ifndef zoxel_voxels_core
#define zoxel_voxels_core

const double noiseChunkAnimateSpeed = 0.5; // 1 / 8.0;
const float overall_voxel_scale = 2.0f;
const int chunk_length = 32;
const int dissapearChance = 92;
const float spawnRange = 0.22f;
const int3 chunk_size = { chunk_length, chunk_length, chunk_length };
const int terrain_rows = 1;
const float chunk_real_size = 1.0f;   // size achunk takes up
// tags
ECS_DECLARE(Vox);
ECS_DECLARE(NoiseChunk);
ECS_DECLARE(TerrainChunk);
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
#include "util/voxel_mesh_util.c"
#include "util/chunk.c"
// prefabs
#include "prefabs/chunk.c"
#include "prefabs/voxel_chunk_mesh.c"
// systems
zoxel_reset_system(GenerateChunkResetSystem, GenerateChunk);
// #include "systems/generate_chunk_reset_system.c"
#include "systems/noise_chunk_system.c"
#include "systems/terrain_chunk_system.c"
#include "systems/chunk_build_system.c"
#include "systems/animate_chunk_system.c"

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
    ECS_TAG_DEFINE(world, TerrainChunk);
    zoxel_memory_component_define(world, Chunk);
    ECS_COMPONENT_DEFINE(world, ChunkSize);
    ECS_COMPONENT_DEFINE(world, GenerateChunk);
    ECS_COMPONENT_DEFINE(world, ChunkPosition);
    zoxel_memory_component_define(world, ChunkLinks);
    ECS_COMPONENT_DEFINE(world, AnimateChunk);
    // filters
    // zoxel_filter(generateChunkQuery, world, [none] NoiseChunk, [in] GenerateChunk);
    // zoxel_filter(chunkDirtyQuery, world, [none] NoiseChunk, [in] EntityDirty);
    // systems
    ECS_SYSTEM_DEFINE(world, AnimateChunkSystem, EcsOnUpdate, [out] AnimateChunk, [out] GenerateChunk);

    zoxel_filter(generateNoiseChunkQuery, world, [none] NoiseChunk, [in] GenerateChunk);
    zoxel_system_ctx(world, NoiseChunkSystem, EcsOnUpdate, generateNoiseChunkQuery,
        [none] NoiseChunk, [out] generic.EntityDirty, [out] Chunk, [in] ChunkSize, [in] GenerateChunk);

    zoxel_filter(generateTerrainChunkQuery, world, [none] TerrainChunk, [in] GenerateChunk);
    zoxel_system_ctx(world,TerrainChunkSystem, EcsOnUpdate, generateTerrainChunkQuery,
        [none] TerrainChunk, [out] generic.EntityDirty, [out] Chunk, [in] ChunkSize, [in] GenerateChunk);

    zoxel_filter(generateChunkQuery, world, [in] GenerateChunk);
    zoxel_system_ctx(world, ChunkBuildSystem, EcsOnUpdate, generateChunkQuery,
        [in] generic.EntityDirty, [in] Chunk, [in] ChunkSize, [out] MeshIndicies, [out] MeshVertices);
    // zoxel_system_main_thread(world, GenerateChunkResetSystem, EcsPostUpdate, [out] GenerateChunk);
    zoxel_reset_system_define(GenerateChunkResetSystem, GenerateChunk);
    //spawn_chunk_prefab(world);
    //spawn_chunk(world);
    spawn_voxel_chunk_mesh_prefab(world);
    #ifdef zoxel_test_voxels
    spawn_voxel_noise_chunk_mesh(world, (float3) { 0, -spawnRange, 0 }, 0.05f);
    spawn_voxel_noise_chunk_mesh(world, (float3) { 0, spawnRange, 0 }, 0.05f);
    spawn_voxel_noise_chunk_mesh(world, (float3) { -spawnRange, 0, 0 }, 0.05f);
    spawn_voxel_noise_chunk_mesh(world, (float3) { spawnRange, 0, 0 }, 0.05f);
    for (int i = - terrain_rows; i <= terrain_rows; i++)
    {
        for (int j = - terrain_rows; j <= terrain_rows; j++)
        {
            ecs_entity_t terrain_mesh = spawn_voxel_chunk_mesh(
                world, (float3) { i * chunk_real_size, -1, j * chunk_real_size }, 0.5f);
            zoxel_add_tag(world, terrain_mesh, TerrainChunk);
        }
    }
    #endif
}

// components
// #include "components/ChunkLinks.c"
// ECS_COMPONENT_DECLARE(ChunkLinks);
//! Stores voxels, in an oct tree.
/**
*   \todo Store Tree Nodes as entities. Each tree node can be open or closed.
*/
#endif