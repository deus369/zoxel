#include "chunk_terrain_build_system.c"
#include "terrain_chunks_render_system.c"
#include "chunk_bounds_debug_system.c"
#include "block_vox_spawn_system.c"
#include "chunk_flatland_system.c"
#include "grassy_plains_system.c"
#include "dungeon_block_system.c"
zox_declare_system_state_event(RealmVoxels, GenerateRealm, zox_generate_realm_voxels, spawn_realm_voxels)

void define_systems_terrain(ecs_world_t *world) {
    // Builds our Textured Chunks (Terrain) !
    if (!headless) {
        zox_system(ChunkTerrainBuildSystem, EcsOnUpdate, [in] VoxLink,  [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] VoxScale, [in] RenderDisabled, [in] ChunkMeshDirty, [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshColorRGBs, [out] MeshDirty, [none] chunks.ChunkTextured)
    }
    // remember: needs EcsOnUpdate, zox_pip_mainthread is called when Dirty is cleaned
    zox_system_1(BlockVoxSpawnSystem, zox_pip_mainthread, [in] ChunkLodDirty, [out] ChunkOctree, [in] ChunkPosition, [in] VoxLink, [in] RenderDistance, [in] RenderDisabled, [out] BlocksSpawned, [in] RenderLod, [none] TerrainChunk)
    zox_render3D_system(TerrainChunksRenderSystem, [in] TransformMatrix, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] VoxLink, [in] RenderDisabled) // builds meshes
#ifdef zox_debug_chunk_bounds
    zox_system_1(ChunkBoundsDrawSystem, zox_pip_mainthread, [in] Position3D, [in] ChunkSize, [in] VoxScale, [in] RenderDisabled, [none] TerrainChunk)
#endif
    // generate terrain
    zox_filter(generateTerrainChunkQuery, [none] TerrainChunk, [out] GenerateChunk)
    zox_system(ChunkFlatlandSystem, EcsOnUpdate, [none] TerrainChunk, [in] ChunkPosition, [out] GenerateChunk, [out] ChunkOctree, [none] FlatlandChunk)
    zox_system_ctx(GrassyPlainsSystem, EcsOnUpdate, generateTerrainChunkQuery, [none] TerrainChunk, [in] ChunkPosition, [in] RenderLod, [out] GenerateChunk, [out] ChunkOctree, [none] !FlatlandChunk)
    zox_system(DungeonBlockSystem, EcsOnUpdate, [in] TimerState, [in] ChunkLink, [none] blocks.BlockDungeon)
    zox_define_system_state_event_1(RealmVoxels, EcsOnLoad, GenerateRealm)
}