#include "chunk_terrain_build_system.c"
#include "terrain_chunks_render_system.c"
#include "chunk_bounds_debug_system.c"
#include "block_vox_spawn_system.c"
#include "chunk_flatland_system.c"
#include "grassy_plains_system.c"
zox_declare_system_state_event(RealmVoxels, GenerateRealm, zox_generate_realm_voxels, spawn_realm_voxels)

void define_systems_terrain(ecs_world_t *world) {
    zox_define_system_state_event_1(RealmVoxels, EcsOnLoad, realms.GenerateRealm, [none] realms.Realm)
    // generate terrain
    // zox_filter(generateTerrainChunkQuery, [none] TerrainChunk, [out] chunks.GenerateChunk)
    zox_system(ChunkFlatlandSystem, EcsOnUpdate,
        [none] TerrainChunk,
        [in] chunks.ChunkPosition,
        [out] chunks.GenerateChunk,
        [out] chunks.VoxelNode,
        [out] chunks.NodeDepth,
        [none] FlatlandChunk)
    zox_system(GrassyPlainsSystem, EcsOnUpdate, // generateTerrainChunkQuery,
        [none] TerrainChunk,
        [in] chunks.ChunkPosition,
        [in] rendering.RenderLod,
        [out] chunks.GenerateChunk,
        [out] chunks.VoxelNode,
        [out] chunks.NodeDepth,
        [none] !FlatlandChunk)
    // remember: needs EcsOnUpdate, zox_pip_mainthread is called when Dirty is cleaned
    zox_system_1(BlockVoxSpawnSystem, zox_pip_mainthread,
        [in] chunks.ChunkLodDirty,
        [in] chunks.ChunkPosition,
        [in] voxels.VoxLink,
        [in] chunks.NodeDepth,
        [in] rendering.RenderDistance,
        [in] rendering.RenderDisabled,
        [in] rendering.RenderLod,
        [out] chunks.VoxelNode,
        [out] chunks.BlocksSpawned,
        [none] TerrainChunk)
#ifdef zox_debug_chunk_bounds
    zox_system_1(ChunkBoundsDrawSystem, zox_pip_mainthread,
        [in] transforms3.d.Position3D,
        [in] chunks.ChunkSize,
        [in] blocks.VoxScale,
        [in] rendering.RenderDisabled,
        [none] TerrainChunk)
#endif
    // Builds our Textured Chunks (Terrain) !
    if (!headless) {
        zox_system(ChunkTerrainBuildSystem, EcsOnUpdate,
            [in] voxels.VoxLink,
            [in] chunks.VoxelNode,
            [in] chunks.NodeDepth,
            [in] rendering.RenderLod,
            [in] chunks.ChunkNeighbors,
            [in] blocks.VoxScale,
            [in] chunks.ChunkMeshDirty,
            [out] rendering.core.MeshIndicies,
            [out] rendering.core.MeshVertices,
            [out] rendering.core.MeshUVs,
            [out] rendering.core.MeshColorRGBs,
            [out] rendering.MeshDirty,
            [none] chunks.ChunkTextured)
        zox_render3D_system(TerrainChunksRenderSystem,
            [in] transforms3.d.TransformMatrix,
            [in] rendering.core.MeshGPULink,
            [in] rendering.core.UvsGPULink,
            [in] rendering.core.ColorsGPULink,
            [in] rendering.core.MeshIndicies,
            [in] voxels.VoxLink,
            [in] rendering.RenderDisabled) // builds meshes
    }
}