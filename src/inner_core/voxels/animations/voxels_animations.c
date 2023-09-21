#ifndef zoxel_voxels_animations
#define zoxel_voxels_animations

const double animating_chunk_speed = 0.5; // 1 / 8.0;
// zoxel_component_includes
zox_component(AnimateChunk, double)
// zoxel_util_includes
// zoxel_prefab_includes
#include "prefabs/animating_chunk.c"
// zoxel_fun_includes
// zoxel_system_includes
#include "systems/animate_chunk_system.c"
#include "systems/noise_chunk_system.c"

void spawn_prefabs_voxel_animations(ecs_world_t *world) {
    spawn_prefab_animating_chunk(world);
}

zox_begin_module(VoxelsAnimations)
// zoxel_component_defines
zox_define_component(AnimateChunk)
// zoxel_system_defines
zox_filter(noise_chunks, [none] NoiseChunk, [out] GenerateChunk)
zox_system(AnimateChunkSystem, EcsOnUpdate, [out] AnimateChunk, [out] GenerateChunk)
zox_system_ctx(NoiseChunkSystem, EcsOnUpdate, noise_chunks, [none] NoiseChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [out] GenerateChunk)
zox_system_ctx(NoiseChunkOctreeSystem, EcsOnUpdate, noise_chunks, [none] NoiseChunk, [out] ChunkDirty, [out] ChunkOctree, [in] RenderLod, [out] GenerateChunk)
zoxel_end_module(VoxelsAnimations)

#endif