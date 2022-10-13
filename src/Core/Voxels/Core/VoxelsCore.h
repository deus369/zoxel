

// Components
#include "Components/ChunkLinks.c"
ECS_COMPONENT_DECLARE(ChunkLinks);
#include "Components/Chunk.c"
ECS_COMPONENT_DECLARE(Chunk);
// Systems

//! The Voxels Core Sub Module.
/**
*   \todo First use a Point Render system to render voxel data.
*   \todo Spawn an Oct Node of 1 Voxel, if open, create 8 sub chunk nodes. 
*   \todo Only push voxel data to the GPU.
*/
void InitializeVoxelsCore(ecs_world_t *world)
{
    ECS_COMPONENT_DEFINE(world, ChunkLinks);
    ECS_COMPONENT_DEFINE(world, Chunk);
}