#ifndef Zoxel_Voxels_Core
#define Zoxel_Voxels_Core

// components
// #include "components/ChunkLinks.c"
// ECS_COMPONENT_DECLARE(ChunkLinks);
//! Stores voxels, in an oct tree.
/**
*   \todo Store Tree Nodes as entities. Each tree node can be open or closed.
*/

//! A simple chunk with an array of voxels.
zoxel_memory_component(Chunk, unsigned char);
//! A list to all chunks in a Vox model.
zoxel_memory_component(ChunkLinks, ecs_entity_t);
// systems

//! The voxels core Sub Module.
/**
*   \todo First use a Point Render system to render voxel data.
*   \todo Spawn an Oct Node of 1 Voxel, if open, create 8 sub chunk nodes. 
*   \todo Only push voxel data to the GPU.
*/
void VoxelsCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, VoxelsCore);
    zoxel_memory_component_define(world, Chunk);
    zoxel_memory_component_define(world, ChunkLinks);
}
#endif