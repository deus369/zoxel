#ifndef zoxel_voxels_core
#define zoxel_voxels_core

#include "settings/settings.c"
// zoxel_component_includes
zox_declare_tag(Voxel)
zox_declare_tag(ColorChunk)
zox_declare_tag(LinkChunk)
zox_component(ChunkSize, int3)                        //! A simple chunk with an array of voxels
zox_byte_component(GenerateChunk)                     //! A state for generating chunks
zox_byte_component(ChunkDirty)                        //! A state for generating chunk meshes
zox_memory_component(ChunkData, unsigned char)        //! A simple chunk with an array of voxels
zox_memory_component(ChunkNeighbors, ecs_entity_t)    //! A list to all chunks in a Vox model
zoxel_octree_component(ChunkOctree, unsigned char, 0)   //! A chunk that stores voxels in an octree
zox_entities_component(VoxelLinks)
// zoxel_util_includes
#include "util/voxel_mesh_util.c"
#include "util/chunk_util.c"
#include "util/chunk_octree_util.c"
#include "util/chunk_build_util.c"
#include "util/voxel_util.c"
// zoxel_prefab_includes
#include "prefabs/voxel.c"
#include "prefabs/chunk.c"
#include "prefabs/noise_chunk.c"
// zoxel_fun_includes
#include "fun/test_noise_chunks.c"
// zoxel_system_includes
#include "systems/chunk_build_system.c"
#include "systems/chunk_colors_build_system.c"
#include "systems/chunk_link_system.c"
#include "systems/chunk_octree_colors_build_system.c"
zox_reset_system(GenerateChunkResetSystem, GenerateChunk)

zox_begin_module(VoxelsCore)
// zoxel_component_defines
zox_define_tag(Voxel)
zox_define_tag(ColorChunk)
zox_define_tag(LinkChunk)
zox_define_component(ChunkDirty)
zox_define_component(ChunkSize)
zox_define_component(GenerateChunk)
zox_define_memory_component(ChunkData)
zox_define_memory_component(ChunkNeighbors)
zoxel_octree_component_define(ChunkOctree)
zox_define_entities_component(VoxelLinks, [in] VoxelLinks)
// zoxel_prefab_defines
spawn_prefab_voxel(world);
spawn_prefab_chunk(world);
spawn_prefab_noise_chunk(world);
set_max_octree_length(max_octree_depth);
// zoxel_system_defines
zox_filter(chunks_generating, [in] GenerateChunk)
zox_define_reset_system(GenerateChunkResetSystem, GenerateChunk)
if (!headless) {
    zox_system_ctx(ChunkBuildSystem, EcsOnUpdate, chunks_generating, [out] ChunkDirty, [in] ChunkData, [in] ChunkSize, [out] MeshIndicies, [out] MeshVertices, [out] MeshDirty, [none] !MeshUVs, [none] !MeshColorRGBs)
    zox_system_ctx(ChunkColorsBuildSystem, EcsOnUpdate, chunks_generating, [out] ChunkDirty, [in] ChunkData, [in] ChunkSize, [in] ColorRGBs, [out] MeshIndicies, [out] MeshVertices, [out] MeshColorRGBs, [out] MeshDirty, [none] !MeshUVs)
}
zox_system_ctx(ChunkOctreeColorsBuildSystem, EcsPostUpdate, chunks_generating,
    [out] ChunkDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] ColorRGBs, [in] ChunkSize,
    [out] MeshIndicies, [out] MeshVertices, [out] MeshColorRGBs, [out] MeshDirty, [none] ColorChunk, [none] !MeshUVs)
zox_system(ChunkLinkSystem, EcsPostUpdate, [none] LinkChunk, [in] VoxLink, [in] Position3D, [out] ChunkPosition, [out] ChunkLink)
zoxel_end_module(VoxelsCore)

#endif