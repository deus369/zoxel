#include "chunk_terrain_build_system.c"
#include "terrain_chunks_render_system.c"
#include "chunk_bounds_debug_system.c"
#include "chunk_flatland_system.c"
#include "grassy_plains_system.c"
#include "block_vox_spawn_system.c"
#include "block_vox_despawn_system.c"
#include "block_vox_lod_system.c"
#include "block_vox_removed_system.c"
zox_declare_system_state_event(RealmVoxels, GenerateRealm, zox_generate_realm_voxels, spawn_realm_voxels)

void define_systems_terrain(ecs_world_t *world) {
    zox_define_system_state_event_1(RealmVoxels, EcsOnLoad, realms.GenerateRealm, [none] realms.Realm)
    // generate terrain
    zox_system(ChunkFlatlandSystem, EcsOnUpdate,
        [in] chunks3.ChunkPosition,
        [out] chunks3.GenerateChunk,
        [out] chunks3.VoxelNode,
        [out] chunks3.NodeDepth,
        [none] TerrainChunk,
        [none] FlatlandChunk)
    zox_system(GrassyPlainsSystem, EcsOnUpdate,
        [in] chunks3.ChunkPosition,
        [in] rendering.RenderLod,
        [out] chunks3.GenerateChunk,
        [out] chunks3.VoxelNode,
        [out] chunks3.NodeDepth,
        [out] chunks3.VoxelNodeDirty,
        [none] !FlatlandChunk,
        [none] TerrainChunk)
    zox_system(BlockVoxDespawnSystem, EcsOnUpdate,
        [in] chunks3.VoxelNodeDirty,
        [in] rendering.RenderDistanceDirty,
        [in] rendering.RenderLod,
        [out] chunks3.VoxelNode,
        [out] chunks3.BlocksSpawned,
        [none] TerrainChunk)
    zox_system(BlockVoxLodSystem, EcsOnUpdate,
        [in] rendering.RenderDistanceDirty,
        [in] rendering.RenderDistance,
        [in] chunks3.VoxelNode,
        [in] chunks3.BlocksSpawned,
        [none] TerrainChunk)
    zox_system(BlockVoxRemovedSystem, EcsOnUpdate,
        [in] chunks3.VoxelNodeDirty,
        [in] chunks3.BlocksSpawned,
        [out] chunks3.VoxelNode,
        [none] TerrainChunk)

    // remember: needs EcsOnUpdate, zox_pip_mainthread is called when Dirty is cleaned
    zox_system_1(BlockVoxSpawnSystem, zox_pip_mainthread,
        [in] chunks3.VoxelNodeDirty,
        [in] rendering.RenderDistanceDirty,
        [in] chunks3.ChunkPosition,
        [in] chunks3.VoxLink,
        [in] chunks3.NodeDepth,
        [in] rendering.RenderDisabled,
        [in] rendering.RenderLod,
        [in] rendering.RenderDistance,
        [out] chunks3.VoxelNode,
        [out] chunks3.BlocksSpawned,
        [none] TerrainChunk)
#ifdef zox_debug_chunk_bounds
    zox_system_1(ChunkBoundsDrawSystem, zox_pip_mainthread,
        [in] transforms3.Position3D,
        [in] chunks3.ChunkSize,
        [in] blocks.VoxScale,
        [in] rendering.RenderDisabled,
        [none] TerrainChunk)
#endif
    // Builds our Textured Chunks (Terrain) !
    if (!headless) {
        zox_system(ChunkTerrainBuildSystem, EcsOnUpdate,
            [in] chunks3.VoxLink,
            [in] chunks3.VoxelNode,
            [in] chunks3.NodeDepth,
            [in] rendering.RenderLod,
            [in] chunks3.ChunkNeighbors,
            [in] blocks.VoxScale,
            [in] chunks3.ChunkMeshDirty,
            [out] rendering.MeshIndicies,
            [out] rendering.MeshVertices,
            [out] rendering.MeshUVs,
            [out] rendering.MeshColorRGBs,
            [out] rendering.MeshDirty,
            [none] chunks3.ChunkTextured)
        zox_render3D_system(TerrainChunksRenderSystem,
            [in] transforms3.TransformMatrix,
            [in] rendering.MeshGPULink,
            [in] rendering.UvsGPULink,
            [in] rendering.ColorsGPULink,
            [in] rendering.MeshIndicies,
            [in] chunks3.VoxLink,
            [in] rendering.RenderDisabled) // builds meshes
    }
}