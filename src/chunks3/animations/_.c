#ifndef zox_voxels_animations
#define zox_voxels_animations

const double animating_chunk_speed = 0.5;
zoxc_double(AnimateChunk);
#include "prefabs/animating_chunk.c"
#include "systems/animate_chunk_system.c"
#include "systems/noise_chunk_system.c"
entity prefab_chunk_animating;

void spawn_prefabs_voxel_animations(ecs *world) {
    prefab_chunk_animating = spawn_prefab_animating_chunk(world, prefab_chunk);
}

zox_begin_module(VoxelsAnimations)
    zox_define_component_double(AnimateChunk);
    zox_filter(noise_chunks,
        [none] chunks3.NoiseChunk,
        [out] chunks3.GenerateChunk);
    zox_system(AnimateChunkSystem, EcsOnUpdate,
        [out] AnimateChunk,
        [out] chunks3.GenerateChunk);
    // NOTE: Writes to VoxelNode
    zox_system_ctx(NoiseVoxelNodeSystem, EcsPreUpdate, noise_chunks,
        [in] chunks3.NodeDepth,
        [out] chunks3.ChunkDirty,
        [out] chunks3.VoxelNode,
        [out] chunks3.GenerateChunk,
        [none] chunks3.NoiseChunk);
    add_hook_spawn_prefabs(spawn_prefabs_voxel_animations);
zox_end_module(VoxelsAnimations)

#endif