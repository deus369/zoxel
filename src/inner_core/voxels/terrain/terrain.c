#ifndef zoxel_voxels_terrain
#define zoxel_voxels_terrain

#include "settings/settings.c"
zox_declare_tag(TerrainWorld)
zox_declare_tag(TerrainChunk)
zox_declare_tag(ChunkTerrain)
zox_declare_tag(Streamer)
zox_component(StreamPoint, int3)
#include "prefabs/terrain.c"
#include "prefabs/terrain_chunk.c"
#include "prefabs/terrain_chunk_octree.c"
#include "util/octree_tricks.c"
#include "util/static_octree_build.c"
#include "systems/terrain_chunk_system.c"
#include "systems/chunk_uvs_build_system.c"
#include "systems/stream_point_system.c"
#include "octree_systems/chunk_octree_build_system.c"
#include "octree_systems/octree_terrain_chunk_system.c"
#include "octree_systems/render3D_uvs_system.c"
#include "util/create_terrain.c"
long int Render3DUvsSystem_id;

zox_begin_module(Terrain)
set_terrain_render_distance();
// zoxel_component_defines
zox_define_tag(TerrainWorld)
zox_define_tag(TerrainChunk)
zox_define_tag(ChunkTerrain)
zox_define_tag(Streamer)
zox_define_component(StreamPoint)
zox_filter(generateTerrainChunkQuery, [none] TerrainChunk, [in] GenerateChunk)
zox_filter(chunks_generating, [in] GenerateChunk)
zox_filter(terrain_chunks_query, [none] TerrainChunk, [in] ChunkPosition, [in] ChunkNeighbors, [out] RenderLod, [out] ChunkDirty)
// zoxel_prefab_defines
spawn_prefab_terrain(world);
int3 terrain_chunk_size = { default_chunk_length, 8 * default_chunk_length, default_chunk_length };
spawn_prefab_terrain_chunk(world, terrain_chunk_size);
spawn_prefab_terrain_chunk_octree(world, terrain_chunk_size);
// zoxel_system_defines
zox_system_ctx(TerrainChunkSystem, EcsPostLoad, generateTerrainChunkQuery,
    [none] TerrainChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] ChunkPosition, [in] GenerateChunk)
zox_system_ctx(OctreeTerrainChunkSystem, EcsPostLoad, generateTerrainChunkQuery,
    [none] TerrainChunk, [in] ChunkPosition, [in] GenerateChunk, [out] ChunkDirty, [out] ChunkOctree)
zox_system_ctx_1(StreamPointSystem, EcsOnUpdate, terrain_chunks_query,
    [none] Streamer, [in] Position3D, [out] StreamPoint)
zox_system_ctx(ChunkUVsBuildSystem, EcsOnUpdate, chunks_generating, [out] ChunkDirty, [in] ChunkData, [in] ChunkSize, [in] ChunkNeighbors,
    [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshDirty, [none] !MeshColorRGBs)
zox_system_ctx(ChunkOctreeBuildSystem, EcsPostUpdate, chunks_generating,
    [out] ChunkDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] VoxLink,
    [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshColorRGBs, [out] MeshDirty)
// zox_system(OctreeChunkMeshSystem, EcsPreUpdate, [out] MeshDirty, [in] ChunkNeighbors, [out] MeshDirty)
zox_system_1(Render3DUvsSystem, render3D_update_pipeline, [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Brightness, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies,
#ifdef voxels_terrain_multi_material
    [in] MaterialGPULink, [in] TextureGPULink);
#else
    [in] VoxLink);
#endif
Render3DUvsSystem_id = ecs_id(Render3DUvsSystem);
zoxel_end_module(Terrain)

/*  terrain_spawn_distance
    1,      // 0
    2,      // 1
    4,      // 2
    8,      // 3
    16,     // 4
    32,     // 5
    64,     // 6
    128     // 7
*/

#endif