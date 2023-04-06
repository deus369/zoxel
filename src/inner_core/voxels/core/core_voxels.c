#ifndef zoxel_voxels_core
#define zoxel_voxels_core

const float overall_voxel_scale = 32.0f; // 64.0f; // 4.0f // 2.0f;
// const float3 center_mesh_offset = { - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f, - overall_voxel_scale / 2.0f };
const float3 center_mesh_offset = { 0, 0, 0 };
const int chunk_length = 16;
const int3 chunk_size = { chunk_length, chunk_length, chunk_length };
const double noiseChunkAnimateSpeed = 0.5; // 1 / 8.0;
const int dissapearChance = 92;
const float spawnRange = 0.96f;
zoxel_declare_tag(LinkChunk)
zoxel_component(ChunkSize, int3)                        //! A simple chunk with an array of voxels.
zoxel_component(AnimateChunk, double)                   //! A state for animating textures.
zoxel_byte_component(GenerateChunk)                     //! A state for generating chunks.
zoxel_byte_component(ChunkDirty)                        //! A state for generating chunk meshes.
zoxel_memory_component(ChunkData, unsigned char)        //! A simple chunk with an array of voxels.
zoxel_memory_component(ChunkNeighbors, ecs_entity_t)    //! A list to all chunks in a Vox model.
zoxel_octree_component(ChunkOctree, unsigned char, 0)   //! A chunk that stores voxels in an octree.
zoxel_byte_component(ChunkDivision)                     //! The resolution of each chunk, distance to nearest camera.
#include "util/voxel_mesh_util.c"
#include "util/chunk_build_util.c"
#include "util/voxel_util.c"
#include "prefabs/chunk.c"
#include "prefabs/voxel_chunk_mesh.c"
#include "prefabs/noise_chunk.c"
#include "fun/test_noise_chunks.c"
#include "systems/noise_chunk_system.c"
#include "systems/animate_chunk_system.c"
#include "systems/chunk_build_system.c"
#include "systems/chunk_colors_build_system.c"
#include "systems/chunk_link_system.c"
zoxel_reset_system(GenerateChunkResetSystem, GenerateChunk)
// zoxel_reset_system(ChunkDirtyResetSystem, ChunkDirty)

zoxel_begin_module(VoxelsCore)
zoxel_define_tag(LinkChunk)
zoxel_define_component(ChunkDirty)
zoxel_define_component(ChunkSize)
zoxel_define_component(GenerateChunk)
zoxel_define_component(ChunkDivision)
zoxel_define_memory_component(ChunkData)
zoxel_define_memory_component(ChunkNeighbors)
zoxel_octree_component_define(ChunkOctree)
zoxel_define_component(AnimateChunk)    // move to another module
zoxel_define_reset_system(GenerateChunkResetSystem, GenerateChunk)
// zoxel_define_reset_system(ChunkDirtyResetSystem, ChunkDirty)
zoxel_system(ChunkLinkSystem, EcsPostUpdate, [none] LinkChunk, [in] Position3D, [out] ChunkPosition, [out] ChunkLink)
if (!headless) {
    zoxel_filter(generateChunkQuery, world, [in] GenerateChunk)
    zoxel_system_ctx(world, ChunkBuildSystem, EcsOnUpdate, generateChunkQuery, [out] ChunkDirty, [in] ChunkData, [in] ChunkSize,
        [out] MeshIndicies, [out] MeshVertices, [out] MeshDirty, [none] !MeshUVs, [none] !MeshColors)
    zoxel_system_ctx(world, ChunkColorsBuildSystem, EcsOnUpdate, generateChunkQuery, [out] ChunkDirty, [in] ChunkData,
        [in] ChunkSize, [in] Colors, [out] MeshIndicies, [out] MeshVertices, [out] MeshColors, [out] MeshDirty, [none] !MeshUVs)
}
// _main_thread
zoxel_system(AnimateChunkSystem, EcsOnLoad, [out] AnimateChunk, [out] GenerateChunk)
zoxel_filter(generateNoiseChunkQuery, world, [none] NoiseChunk, [in] GenerateChunk)
zoxel_system_ctx(world, NoiseChunkSystem, EcsPostLoad, generateNoiseChunkQuery, [none] NoiseChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] GenerateChunk)
spawn_voxel_chunk_mesh_prefab(world);
spawn_prefab_noise_chunk(world);
#ifdef zoxel_test_voxels
test_noise_chunks();
#endif
zoxel_end_module(VoxelsCore)

// \todo for things like this, declare system in component declaration - a variable that resets~

#endif