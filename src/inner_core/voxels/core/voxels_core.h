#ifndef Zoxel_Voxels_Core
#define Zoxel_Voxels_Core

// components
// #include "components/ChunkLinks.c"
// ECS_COMPONENT_DECLARE(ChunkLinks);
//! Stores voxels, in an oct tree.
/**
*   \todo Store Tree Nodes as entities. Each tree node can be open or closed.
*/

// tags
ECS_DECLARE(NoiseChunk);
//! A simple chunk with an array of voxels.
zoxel_memory_component(Chunk, unsigned char);
//! A list to all chunks in a Vox model.
zoxel_memory_component(ChunkLinks, ecs_entity_t);
//! A simple chunk with an array of voxels.
zoxel_component(ChunkSize, int3);
//! A state for generating chunks.
zoxel_component(GenerateChunk, unsigned char);
// prefabs
#include "prefabs/chunk.c"
// util
#include "util/chunk.c"
// systems
#include "systems/GenerateChunkResetSystem.c"
#include "systems/NoiseChunkSystem.c"

//! The voxels core Sub Module.
/**
*   \todo First use a Point Render system to render voxel data.
*   \todo Spawn an Oct Node of 1 Voxel, if open, create 8 sub chunk nodes. 
*   \todo Only push voxel data to the GPU.
*/
void VoxelsCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, VoxelsCore);
    ECS_TAG_DEFINE(world, NoiseChunk);
    zoxel_memory_component_define(world, Chunk);
    zoxel_memory_component_define(world, ChunkLinks);
    ECS_COMPONENT_DEFINE(world, ChunkSize);
    ECS_COMPONENT_DEFINE(world, GenerateChunk);
    zoxel_filter(generateChunkQuery, world, [none] NoiseChunk, [in] GenerateChunk);
    zoxel_system_ctx(world, NoiseChunkSystem, EcsOnUpdate, generateChunkQuery,
        [none] NoiseChunk, [out] generic.EntityDirty, [out] Chunk, [in] ChunkSize, [in] GenerateChunk);
    ECS_SYSTEM_DEFINE(world, GenerateChunkResetSystem, EcsPostUpdate, [out] GenerateChunk);
    spawn_chunk_prefab(world);
    spawn_chunk(world);
}
#endif