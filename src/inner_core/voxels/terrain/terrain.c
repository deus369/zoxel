#ifndef zoxel_voxels_terrain
#define zoxel_voxels_terrain

// long int render_terrain_chunks_system_id;
#include "settings/settings.c"
// zoxel_component_declares
zox_declare_tag(TerrainWorld)
zox_declare_tag(TerrainChunk)
zox_declare_tag(ChunkTerrain)
zox_declare_tag(Streamer)
zox_component(StreamPoint, int3)
// zoxel_prefab_includes
#include "prefabs/terrain.c"
#include "prefabs/terrain_chunk.c"
#include "prefabs/terrain_chunk_octree.c"
// zoxel_util_includes
#include "util/octree_tricks.c"
#include "util/static_octree_build.c"
// zoxel_system_declares
#include "systems/terrain_chunk_system.c"
#include "systems/chunk_uvs_build_system.c"
#include "systems/stream_point_system.c"
#include "octree_systems/chunk_octree_build_system.c"
#include "octree_systems/octree_terrain_chunk_system.c"
#include "octree_systems/terrain_chunks_render_system.c"
#include "util/create_terrain.c"

void spawn_prefabs_terrain(ecs_world_t *world) {
    spawn_prefab_terrain(world);
    int3 terrain_chunk_size = { default_chunk_length, 8 * default_chunk_length, default_chunk_length };
    spawn_prefab_terrain_chunk(world, terrain_chunk_size);
    spawn_prefab_terrain_chunk_octree(world, terrain_chunk_size);
}

zox_begin_module(Terrain)
set_terrain_render_distance();
// zoxel_component_defines
zox_define_tag(TerrainWorld)
zox_define_tag(TerrainChunk)
zox_define_tag(ChunkTerrain)
zox_define_tag(Streamer)
zox_define_component(StreamPoint)
// zoxel_filter_defines
zox_filter(generateTerrainChunkQuery, [none] TerrainChunk, [out] GenerateChunk)
zox_filter(chunks_generating, [in] GenerateChunk)
zox_filter(terrain_chunks_query, [none] TerrainChunk, [in] ChunkPosition, [in] ChunkNeighbors, [out] RenderLod, [out] ChunkDirty)
// zoxel_system_defines
zox_system_ctx(TerrainChunkSystem, EcsOnUpdate, generateTerrainChunkQuery, [none] TerrainChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] ChunkPosition, [out] GenerateChunk)
zox_system_ctx(OctreeTerrainChunkSystem, EcsOnUpdate, generateTerrainChunkQuery, [none] TerrainChunk, [in] ChunkPosition, [out] GenerateChunk, [out] ChunkDirty, [out] ChunkOctree)
zox_system_ctx(StreamPointSystem, EcsOnUpdate, terrain_chunks_query, [none] Streamer, [in] Position3D, [out] StreamPoint)
// zox_system_ctx(ChunkUVsBuildSystem, EcsOnUpdate, chunks_generating, [out] ChunkDirty, [in] ChunkData, [in] ChunkSize, [in] ChunkNeighbors, [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshDirty, [none] !MeshColorRGBs)
if (!headless) zox_system_ctx(ChunkOctreeBuildSystem, EcsOnLoad, chunks_generating, [out] ChunkDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] VoxLink, [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshColorRGBs, [out] MeshDirty)
// zox_system_ctx_1(ChunkOctreeBuildSystem, main_thread_pipeline, chunks_generating, [out] ChunkDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] VoxLink, [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshColorRGBs, [out] MeshDirty)
if (!headless) zox_system_1(TerrainChunksRenderSystem, 0, [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Brightness, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] VoxLink);
add_to_render3D_loop(ecs_id(TerrainChunksRenderSystem));
zoxel_end_module(Terrain)

#endif