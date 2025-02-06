// todo: don't generate mesh until render is enabled!
// todo: use ChunkOriginDistance instead of RenderLod for camera distance for TerrainChunks
// todo: delay BlockVoxSpawnSystem to main thread pipeline like character spawning, use same trigger? rest on load? make a resetsystem 2 for this - just  make reset defines use the pipeline
#ifndef zox_mod_terrain
#define zox_mod_terrain

zox_declare_tag(FlatTerrain)
zox_declare_tag(FlatlandChunk)
zox_declare_tag(TerrainWorld)
zox_declare_tag(TerrainChunk)
zox_declare_tag(ChunkTerrain)
zox_component_entity(TerrainLink)
#include "data/platform_settings.c"
#include "data/generation_settings.c"
#include "data/settings.c"
#include "data/terrain_statistics.c"
#include "data/chunk_textured_build_data.c"
#include "data/mesh_uvs_build_data.c"
#include "prefabs/prefabs.c"
#include "util/util.c"
#include "systems/terrain_chunk_system.c"
#include "systems/chunk_terrain_build_system.c"
#include "systems/terrain_chunks_render_system.c"
#include "systems/chunk_bounds_debug_system.c"
#include "systems/block_vox_spawn_system.c"
#include "systems/block_vox_update_system.c"
#include "systems/chunk_flatland_system.c"
#include "systems/grassy_plains_system.c"
#include "systems/dungeon_block_system.c"

zox_begin_module(Terrain)
    zox_define_tag(FlatTerrain)
    zox_define_tag(FlatlandChunk)
    zox_define_tag(TerrainWorld)
    zox_define_tag(TerrainChunk)
    zox_define_tag(ChunkTerrain)
    zox_define_component_entity(TerrainLink)
    // systems
    // Builds our Textured Chunks (Terrain) !
    if (!headless) zox_system(ChunkTerrainBuildSystem, EcsOnUpdate, [in] VoxLink,  [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] VoxScale, [in] RenderDisabled, [in] ChunkMeshDirty, [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshColorRGBs, [out] MeshDirty, [none] chunks.ChunkTextured)
    // remember: needs EcsOnUpdate, zox_pip_mainthread is called when Dirty is cleaned
    zox_system_1(BlockVoxSpawnSystem, zox_pip_mainthread, [in] ChunkLodDirty, [out] ChunkOctree, [in] ChunkPosition, [in] VoxLink, [in] RenderDistance, [in] RenderDisabled, [out] BlocksSpawned, [none] TerrainChunk)
    zox_render3D_system(TerrainChunksRenderSystem, [in] TransformMatrix, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] VoxLink, [in] RenderDisabled) // builds meshes
    #ifdef zox_debug_chunk_bounds
    zox_system_1(ChunkBoundsDrawSystem, zox_pip_mainthread, [in] Position3D, [in] ChunkSize, [in] VoxScale, [in] RenderDisabled, [none] TerrainChunk)
    #endif
    // generate terrain
    zox_filter(generateTerrainChunkQuery, [none] TerrainChunk, [out] GenerateChunk)
    zox_system(ChunkFlatlandSystem, EcsOnUpdate, [none] TerrainChunk, [in] ChunkPosition, [out] GenerateChunk, [out] ChunkOctree, [none] FlatlandChunk)
    zox_system_ctx(GrassyPlainsSystem, EcsOnUpdate, generateTerrainChunkQuery, [none] TerrainChunk, [in] ChunkPosition, [out] GenerateChunk, [out] ChunkOctree, [none] !FlatlandChunk)
    zox_system(DungeonBlockSystem, EcsOnUpdate, [in] TimerState, [in] ChunkLink, [none] blocks.BlockDungeon)
    set_terrain_render_distance();
    add_to_event_game_state((zox_game_event) { &realms_game_state });
    spawn_prefabs_terrain(world);
zoxel_end_module(Terrain)

#endif