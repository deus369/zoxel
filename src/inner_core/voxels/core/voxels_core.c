#ifndef zoxel_voxels_core
#define zoxel_voxels_core

#include "settings/settings.c"
// zoxel_component_includes
zoxel_declare_tag(LinkChunk)
zoxel_component(ChunkSize, int3)                        //! A simple chunk with an array of voxels.
zoxel_byte_component(GenerateChunk)                     //! A state for generating chunks.
zoxel_byte_component(ChunkDirty)                        //! A state for generating chunk meshes.
zoxel_memory_component(ChunkData, unsigned char)        //! A simple chunk with an array of voxels.
zoxel_memory_component(ChunkNeighbors, ecs_entity_t)    //! A list to all chunks in a Vox model.
zoxel_octree_component(ChunkOctree, unsigned char, 0)   //! A chunk that stores voxels in an octree.
zoxel_byte_component(ChunkDivision)                     //! The resolution of each chunk, distance to nearest camera.
// zoxel_util_includes
#include "util/voxel_mesh_util.c"
#include "util/chunk_build_util.c"
#include "util/voxel_util.c"
// zoxel_prefab_includes
#include "prefabs/chunk.c"
#include "prefabs/voxel_chunk_mesh.c"
#include "prefabs/noise_chunk.c"
// zoxel_fun_includes
#include "fun/test_noise_chunks.c"
// zoxel_system_includes
#include "systems/noise_chunk_system.c"
#include "systems/chunk_build_system.c"
#include "systems/chunk_colors_build_system.c"
#include "systems/chunk_link_system.c"
zoxel_reset_system(GenerateChunkResetSystem, GenerateChunk)

zoxel_begin_module(VoxelsCore)
// zoxel_component_defines
zoxel_define_tag(LinkChunk)
zoxel_define_component(ChunkDirty)
zoxel_define_component(ChunkSize)
zoxel_define_component(GenerateChunk)
zoxel_define_component(ChunkDivision)
zoxel_define_memory_component(ChunkData)
zoxel_define_memory_component(ChunkNeighbors)
zoxel_octree_component_define(ChunkOctree)
// zoxel_prefab_defines
spawn_voxel_chunk_mesh_prefab(world);
spawn_prefab_noise_chunk(world);
// zoxel_system_defines
zoxel_define_reset_system(GenerateChunkResetSystem, GenerateChunk)
zoxel_system(ChunkLinkSystem, EcsPostUpdate, [none] LinkChunk, [in] VoxLink, [in] Position3D, [out] ChunkPosition, [out] ChunkLink)
if (!headless) {
    zoxel_filter(generateChunkQuery, world, [in] GenerateChunk)
    zoxel_system_ctx(world, ChunkBuildSystem, EcsOnUpdate, generateChunkQuery, [out] ChunkDirty, [in] ChunkData, [in] ChunkSize, [out] MeshIndicies, [out] MeshVertices, [out] MeshDirty, [none] !MeshUVs, [none] !MeshColorRGBs)
    zoxel_system_ctx(world, ChunkColorsBuildSystem, EcsOnUpdate, generateChunkQuery, [out] ChunkDirty, [in] ChunkData, [in] ChunkSize, [in] ColorRGBs, [out] MeshIndicies, [out] MeshVertices, [out] MeshColorRGBs, [out] MeshDirty, [none] !MeshUVs)
}
// zoxel_testing
#ifdef zoxel_test_voxels
test_noise_chunks();
#endif
set_max_octree_length(max_octree_depth);
zoxel_end_module(VoxelsCore)

#endif