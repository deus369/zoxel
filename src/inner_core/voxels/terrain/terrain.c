#ifndef zoxel_voxels_terrain
#define zoxel_voxels_terrain

#define max_octree_depth 5
#define terrain_rows 6
const int3 terrain_chunk_size = { chunk_length, 8 * chunk_length, chunk_length };
float chunk_real_size = overall_voxel_scale / 2.0f; // 1.0f;   // size achunk takes up
const unsigned char terrain_min_height = 8;
const double terrain_amplifier = 120.0;
const double terrain_frequency = 0.004216;
const int terrain_octaves = 12;
const uint32_t terrain_seed = 32666;
zoxel_declare_tag(TerrainChunk)
zoxel_declare_tag(ChunkTerrain)
#include "prefabs/terrain_chunk.c"
#include "prefabs/terrain_chunk_octree.c"
#include "systems/terrain_chunk_system.c"
#include "systems/octree_terrain_chunk_system.c"
#include "systems/octree_chunk_uvs_build_system.c"

int get_chunk_index(int i, int j, int rows)
{
    return (i + rows) * (rows + rows + 1) + (j + rows);
}

//! The Terrain Sub Module of Voxels.
void TerrainImport(ecs_world_t *world)
{
    zoxel_module(Terrain)
    zoxel_define_tag(TerrainChunk)
    zoxel_define_tag(ChunkTerrain)
    zoxel_filter(generateTerrainChunkQuery, world, [none] TerrainChunk, [in] GenerateChunk)
    zoxel_system_ctx(world, TerrainChunkSystem, EcsPostLoad, generateTerrainChunkQuery,
        [none] TerrainChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] ChunkPosition, [in] GenerateChunk)
    zoxel_system_ctx(world, OctreeTerrainChunkSystem, EcsPostLoad, generateTerrainChunkQuery,
        [none] TerrainChunk, [out] ChunkDirty, [out] ChunkOctree, [in] ChunkSize, [in] ChunkPosition, [in] GenerateChunk)
    
    zoxel_filter(generateChunkQuery, world, [in] GenerateChunk)
    zoxel_system_ctx(world, OctreeChunkUVsBuildSystem, EcsOnUpdate, generateChunkQuery,
        [in] ChunkDirty, [in] ChunkOctree, [in] ChunkDivision, [in] ChunkNeighbors,
        [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshDirty,
        [none] !MeshColors)
    spawn_prefab_terrain_chunk(world, terrain_chunk_size);
    spawn_prefab_terrain_chunk_octree(world, terrain_chunk_size);
    #ifdef zoxel_test_voxels_terrain
    // todo: create a hashmap here
    ecs_defer_begin(world);
    int chunks_total_length = (terrain_rows + terrain_rows + 1) * (terrain_rows + terrain_rows + 1);
    ecs_entity_t chunks[chunks_total_length];
    for (int i = 0; i < chunks_total_length; i++)
    {
        chunks[i] = 0;
    }
    for (int i = -terrain_rows; i <= terrain_rows; i++)
    {
        for (int j = -terrain_rows; j <= terrain_rows; j++)
        {
            // printf("%ix%i index is %i\n", i, j, get_chunk_index(i, j, terrain_rows));
            #ifdef voxel_octrees
            chunks[get_chunk_index(i, j, terrain_rows)] = spawn_terrain_chunk_octree(world, prefab_terrain_chunk_octree,
                (int3) { i, 0, j }, (float3) { i * chunk_real_size, 0, j * chunk_real_size }, 0.5f);
            #else
            chunks[get_chunk_index(i, j, terrain_rows)] = spawn_terrain_chunk(world, prefab_terrain_chunk,
                (int3) { i, 0, j }, (float3) { i * chunk_real_size, 0, j * chunk_real_size }, 0.5f);
            #endif
        }
    }
    for (int i = 0; i < chunks_total_length; i++)
    {
        if (chunks[i] == 0)
        {
            zoxel_log("One chunk not set at: %i\n", i);
        }
    }
    // now for all of them, set their neighbors
    for (int i = -terrain_rows; i <= terrain_rows; i++)
    {
        for (int j = -terrain_rows; j <= terrain_rows; j++)
        {
            set_chunk_neighbors(world,
                chunks[get_chunk_index(i, j, terrain_rows)],
                i == -terrain_rows ? 0 : chunks[get_chunk_index(i - 1, j, terrain_rows)],
                i == terrain_rows ? 0 : chunks[get_chunk_index(i + 1, j, terrain_rows)],
                j == -terrain_rows ? 0 : chunks[get_chunk_index(i, j - 1, terrain_rows)],
                j == terrain_rows ? 0 : chunks[get_chunk_index(i, j + 1, terrain_rows)]);
        }
    }
    ecs_defer_end(world);
    #endif
}
#endif