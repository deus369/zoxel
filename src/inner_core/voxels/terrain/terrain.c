#ifndef zoxel_voxels_terrain
#define zoxel_voxels_terrain

#include "fun/settings.c"
zoxel_declare_tag(TerrainWorld)
zoxel_declare_tag(TerrainChunk)
zoxel_declare_tag(ChunkTerrain)
zoxel_declare_tag(Streamer)
zoxel_component(StreamPoint, int3)
zoxel_byte_component(ChunkDirtier)
#include "prefabs/terrain.c"
#include "prefabs/terrain_chunk.c"
#include "prefabs/terrain_chunk_octree.c"
#include "util/octree_tricks.c"
#include "util/static_octree_build.c"
#include "systems/terrain_chunk_system.c"
#include "systems/chunk_uvs_build_system.c"
#include "systems/stream_point_system.c"
#include "octree_systems/octree_terrain_chunk_system.c"
#include "octree_systems/octree_chunk_build_system.c"
#include "octree_systems/octree_chunk_mesh_system.c"
#include "octree_systems/render3D_uvs_system.c"
#include "util/create_terrain.c"
long int Render3DUvsSystem_id;

zoxel_begin_module(Terrain)
set_terrain_render_distance();

zoxel_define_tag(TerrainWorld)
zoxel_define_tag(TerrainChunk)
zoxel_define_tag(ChunkTerrain)
zoxel_define_tag(Streamer)
zoxel_define_component(StreamPoint)
zoxel_define_component(ChunkDirtier)

zoxel_filter(generateTerrainChunkQuery, world, [none] TerrainChunk, [in] GenerateChunk)
zoxel_filter(generateChunkQuery, world, [in] GenerateChunk)
zoxel_system_ctx(world, TerrainChunkSystem, EcsPostLoad, generateTerrainChunkQuery,
    [none] TerrainChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] ChunkPosition, [in] GenerateChunk)
zoxel_system_ctx(world, OctreeTerrainChunkSystem, EcsPostLoad, generateTerrainChunkQuery,
    [none] TerrainChunk, [in] ChunkPosition, [in] GenerateChunk, [out] ChunkDirty, [out] ChunkOctree)
zoxel_filter(terrain_chunks_query, world,
    [none] TerrainChunk, [in] ChunkPosition, [in] ChunkNeighbors, [out] ChunkDivision, [out] ChunkDirty)
zoxel_system_ctx_main_thread(world, StreamPointSystem, EcsOnUpdate, terrain_chunks_query,
    [none] Streamer, [in] Position3D, [out] StreamPoint)
zoxel_system_ctx(world, ChunkUVsBuildSystem, EcsOnUpdate, generateChunkQuery, [out] ChunkDirty, [in] ChunkData, [in] ChunkSize, [in] ChunkNeighbors,
    [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshDirty, [none] !MeshColors)
zoxel_system_ctx(world, OctreeChunkBuildSystem, EcsOnUpdate, generateChunkQuery,
    [out] ChunkDirty, [in] ChunkOctree, [in] ChunkDivision, [in] ChunkNeighbors,
    [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] ChunkDirtier, [none] !MeshColors)
zoxel_system(OctreeChunkMeshSystem, EcsPreUpdate, [out] ChunkDirtier, [in] ChunkNeighbors, [out] MeshDirty)
zoxel_system_1(Render3DUvsSystem, render3D_update_pipeline, // EcsOnStore,
    [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Brightness,
    [in] MeshGPULink, [in] UvsGPULink, [in] MeshIndicies,
    #ifdef voxels_terrain_multi_material
        [in] MaterialGPULink, [in] TextureGPULink);
    #else
        [in] VoxLink);
    #endif
Render3DUvsSystem_id = ecs_id(Render3DUvsSystem);

spawn_prefab_terrain(world);
int3 terrain_chunk_size = { default_chunk_length, 8 * default_chunk_length, default_chunk_length };
spawn_prefab_terrain_chunk(world, terrain_chunk_size);
spawn_prefab_terrain_chunk_octree(world, terrain_chunk_size);

zoxel_end_module(Terrain)

// todo: move texture to terrain entity and not terrain chunks

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