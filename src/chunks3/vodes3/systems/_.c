#include "vodes_removed.c"
#include "vodes_despawn.c"
#include "vodes_spawn.c"
#include "vodes_lods.c"

void define_systems_vodes3(ecs_world_t* world) {
// NOTE: Writes to VoxelNode
    zox_system(VodesDespawnSystem, zoxp_write_voxels,
            [in] chunks3.VoxelNodeDirty,
            [in] rendering.RenderDistanceDirty,
            [in] rendering.RenderLod,
            [out] chunks3.VoxelNode,
            [out] chunks3.BlocksSpawned)
    // NOTE: Writes to VoxelNode
    zox_system(VodesRemoveSystem, zoxp_write_voxels,
            [in] chunks3.VoxelNodeDirty,
            [in] chunks3.BlocksSpawned,
            [out] chunks3.VoxelNode)
    zox_system(VodesLodSystem, EcsOnUpdate,
            [in] rendering.RenderDistanceDirty,
            [in] rendering.RenderDistance,
            [in] chunks3.VoxelNode,
            [in] chunks3.BlocksSpawned)
    zox_system_1(VodesSpawnSystem, zoxp_write_voxels,
            [in] chunks3.VoxelNodeDirty,
            [in] rendering.RenderDistanceDirty,
            [in] chunks3.ChunkPosition,
            [in] chunks3.VoxLink,
            [in] chunks3.NodeDepth,
            [in] rendering.RenderDisabled,
            [in] rendering.RenderLod,
            [in] rendering.RenderDistance,
            [out] chunks3.VoxelNode,
            [out] chunks3.BlocksSpawned)
}