#ifndef zoxel_voxels_animations
#define zoxel_voxels_animations

// zoxel_component_includes
zoxel_component(AnimateChunk, double)                   //! A state for animating textures

// zoxel_util_includes

// zoxel_prefab_includes

// zoxel_fun_includes

// zoxel_system_includes
#include "systems/animate_chunk_system.c"

zoxel_begin_module(VoxelsAnimations)

// zoxel_component_defines
zoxel_define_component(AnimateChunk)

// zoxel_system_defines
zoxel_system(AnimateChunkSystem, EcsOnLoad, [out] AnimateChunk, [out] GenerateChunk)
zoxel_filter(generateNoiseChunkQuery, world, [none] NoiseChunk, [in] GenerateChunk)
zoxel_system_ctx(NoiseChunkSystem, EcsPostLoad, generateNoiseChunkQuery, [none] NoiseChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] GenerateChunk)

// zoxel_prefab_defines

zoxel_end_module(VoxelsAnimations)

#endif