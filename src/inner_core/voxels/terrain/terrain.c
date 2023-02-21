#ifndef zoxel_voxels_terrain
#define zoxel_voxels_terrain

// voxels settings
#define max_octree_depth 4
#define inner_render_buffer 0
#define terrain_rows 12
#define terrain_vertical 2
#define octree_min_height -1.995f // 0.005f
#ifdef voxel_octrees
    #define terrain_amplifier 120.0
    #define terrain_frequency 0.1216 // 0.004216
#else
    #define terrain_amplifier 64.0
    #define terrain_frequency 0.00216 // 0.004216
#endif
const int3 terrain_chunk_size = { chunk_length, 8 * chunk_length, chunk_length };
float chunk_real_size = overall_voxel_scale / 2.0f; // 1.0f;   // size achunk takes up
const unsigned char terrain_min_height = 8;
const int terrain_octaves = 12;
const uint32_t terrain_seed = 32666;
// the rest
zoxel_declare_tag(TerrainWorld)
zoxel_declare_tag(TerrainChunk)
zoxel_declare_tag(ChunkTerrain)
zoxel_declare_tag(Streamer)
zoxel_component(StreamPoint, int3)                        //! A stream point in the terrain module.
#include "prefabs/terrain.c"
#include "prefabs/terrain_chunk.c"
#include "prefabs/terrain_chunk_octree.c"
#include "systems/terrain_chunk_system.c"
#include "systems/octree_terrain_chunk_system.c"
#include "systems/octree_chunk_uvs_build_system.c"
#include "systems/chunk_uvs_build_system.c"
#include "systems/stream_point_system.c"
#include "util/create_terrain.c"

//! The Terrain Sub Module of Voxels.
void TerrainImport(ecs_world_t *world)
{
    zoxel_module(Terrain)
    zoxel_define_tag(TerrainWorld)
    zoxel_define_tag(TerrainChunk)
    zoxel_define_tag(ChunkTerrain)
    zoxel_define_tag(Streamer)
    zoxel_define_component(StreamPoint)
    zoxel_filter(generateTerrainChunkQuery, world, [none] TerrainChunk, [in] GenerateChunk)
    zoxel_filter(generateChunkQuery, world, [in] GenerateChunk)
    //zoxel_filter(streamerPositionQuery, world, [none] Streamer, [in] Position3D)
    zoxel_system_ctx(world, TerrainChunkSystem, EcsPostLoad, generateTerrainChunkQuery,
        [none] TerrainChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] ChunkPosition, [in] GenerateChunk)
    zoxel_system_ctx(world, OctreeTerrainChunkSystem, EcsPostLoad, generateTerrainChunkQuery,
        [none] TerrainChunk, [in] ChunkPosition, [in] GenerateChunk, [out] ChunkDirty, [out] ChunkOctree)
    zoxel_filter(terrain_chunks_query, world,
        [none] TerrainChunk, [in] ChunkPosition, [in] ChunkNeighbors, [out] ChunkDivision, [out] ChunkDirty)
    zoxel_system_ctx_main_thread(world, StreamPointSystem, EcsOnUpdate, terrain_chunks_query,
        [none] Streamer, [in] Position3D, [out] StreamPoint)
    zoxel_system_ctx(world, ChunkUVsBuildSystem, EcsOnUpdate, generateChunkQuery,
        [in] ChunkDirty, [in] ChunkData, [in] ChunkSize, [in] ChunkNeighbors,
        [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshDirty,
        [none] !MeshColors)
    zoxel_system_ctx(world, OctreeChunkUVsBuildSystem, EcsOnUpdate, generateChunkQuery,
        [in] ChunkDirty, [in] ChunkOctree, [in] ChunkDivision, [in] ChunkNeighbors,
        [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshDirty,
        [none] !MeshColors)
    spawn_prefab_terrain(world);
    spawn_prefab_terrain_chunk(world, terrain_chunk_size);
    spawn_prefab_terrain_chunk_octree(world, terrain_chunk_size);
}
#endif