#ifndef zox_voxels_animations
#define zox_voxels_animations

const double animating_chunk_speed = 0.5;
zox_component_double(AnimateChunk)
#include "prefabs/animating_chunk.c"
#include "systems/animate_chunk_system.c"
#include "systems/noise_chunk_system.c"
ecs_entity_t prefab_chunk_animating;

void spawn_prefabs_voxel_animations(ecs_world_t *world) {
    prefab_chunk_animating = spawn_prefab_animating_chunk(world, prefab_chunk);
}

zox_begin_module(VoxelsAnimations)
    zox_define_component_double(AnimateChunk)
    zox_filter(noise_chunks,
        [none] chunks.NoiseChunk,
        [out] chunks.GenerateChunk)
    zox_system(AnimateChunkSystem, EcsOnUpdate,
        [out] AnimateChunk,
        [out] chunks.GenerateChunk)
    zox_system_ctx(NoiseVoxelNodeSystem, EcsPreUpdate, noise_chunks,
        [in] rendering.RenderLod,
        [in] chunks.NodeDepth,
        [out] chunks.ChunkDirty,
        [out] chunks.VoxelNode,
        [out] chunks.GenerateChunk,
        [none] chunks.NoiseChunk)
    spawn_prefabs_voxel_animations(world);
zox_end_module(VoxelsAnimations)

#endif