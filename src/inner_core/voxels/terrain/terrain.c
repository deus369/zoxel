#ifndef zoxel_voxels_terrain
#define zoxel_voxels_terrain

#define max_octree_depth 5
#define inner_render_buffer 0
#define terrain_rows 12
#define terrain_vertical 2
#define octree_min_height -1.995f // 0.005f
#define terrain_frequency 0.1216 // 0.004216
#define terrain_amplifier 120.0
const int3 terrain_chunk_size = { chunk_length, 8 * chunk_length, chunk_length };
float chunk_real_size = overall_voxel_scale / 2.0f; // 1.0f;   // size achunk takes up
const unsigned char terrain_min_height = 8;
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

int get_terrain_chunks_count(int rows, int vertical_rows)
{
    return (vertical_rows + vertical_rows + 1) * (rows + rows + 1) * (rows + rows + 1);
}

int get_chunk_index_2(int i, int j, int k, int rows)
{
    i += rows;
    j += terrain_vertical;
    k += rows;
    return i * (rows + rows + 1) + j * (rows + rows + 1) * (rows + rows + 1) + k;
    // return i * (rows + rows + 1) + k * (rows + rows + 1) * (rows + rows + 1) + j;
}

void create_terrain()
{
    int chunks_total_length = get_terrain_chunks_count(terrain_rows, terrain_vertical);
    printf("Spawning Terrain Chunks [%i]\n\n", chunks_total_length);
    // todo: create a hashmap here
    ecs_defer_begin(world);
    ecs_entity_t chunks[chunks_total_length];
    for (int i = 0; i < chunks_total_length; i++)
    {
        chunks[i] = 0;
    }
    for (int i = -terrain_rows; i <= terrain_rows; i++)
    {
        for (int k = -terrain_rows; k <= terrain_rows; k++)
        {
            for (int j = -terrain_vertical; j <= terrain_vertical; j++)
            {
                // printf("%ix%i index is %i\n", i, j, get_chunk_index(i, j, terrain_rows));
                // printf("%ix%ix%i index is %i out of %i\n", i, j, k, get_chunk_index_2(i, j, k, terrain_rows), chunks_total_length)
                #ifdef voxel_octrees
                chunks[get_chunk_index_2(i, j, k, terrain_rows)] = spawn_terrain_chunk_octree(world,
                    prefab_terrain_chunk_octree,
                    (int3) { i, j, k },
                    (float3) { i * chunk_real_size, j * chunk_real_size, k * chunk_real_size },
                    0.5f);
                #else
                chunks[get_chunk_index(i, k, terrain_rows)] = spawn_terrain_chunk(world, prefab_terrain_chunk,
                    (int3) { i, 0, k }, (float3) { i * chunk_real_size, 0, k * chunk_real_size }, 0.5f);
                #endif
            }
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
        for (int k = -terrain_rows; k <= terrain_rows; k++)
        {
            for (int j = -terrain_vertical; j <= terrain_vertical; j++)
            {
                set_chunk_neighbors_six_directions(world,
                    chunks[get_chunk_index_2(i, j, k, terrain_rows)],
                    i == -terrain_rows ? 0 : chunks[get_chunk_index_2(i - 1, j, k, terrain_rows)],
                    i == terrain_rows ? 0 : chunks[get_chunk_index_2(i + 1, j, k, terrain_rows)],
                    j == -terrain_vertical ? 0 : chunks[get_chunk_index_2(i, j - 1, k, terrain_rows)],
                    j == terrain_vertical ? 0 : chunks[get_chunk_index_2(i, j + 1, k, terrain_rows)],
                    k == -terrain_rows ? 0 : chunks[get_chunk_index_2(i, j, k - 1, terrain_rows)],
                    k == terrain_rows ? 0 : chunks[get_chunk_index_2(i, j, k + 1, terrain_rows)]);
            }
        }
    }
    ecs_defer_end(world);
}

//! The Terrain Sub Module of Voxels.
void TerrainImport(ecs_world_t *world)
{
    zoxel_module(Terrain)
    zoxel_define_tag(TerrainChunk)
    zoxel_define_tag(ChunkTerrain)
    zoxel_filter(generateTerrainChunkQuery, world, [none] TerrainChunk, [in] GenerateChunk)
    zoxel_filter(generateChunkQuery, world, [in] GenerateChunk)
    zoxel_system_ctx(world, TerrainChunkSystem, EcsPostLoad, generateTerrainChunkQuery,
        [none] TerrainChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] ChunkPosition, [in] GenerateChunk)
    zoxel_system_ctx(world, OctreeTerrainChunkSystem, EcsPostLoad, generateTerrainChunkQuery,
        [none] TerrainChunk, [out] ChunkDirty, [out] ChunkOctree, [in] ChunkSize, [in] ChunkPosition, [in] GenerateChunk)
    zoxel_system_ctx(world, OctreeChunkUVsBuildSystem, EcsOnUpdate, generateChunkQuery,
        [in] ChunkDirty, [in] ChunkOctree, [in] ChunkDivision, [in] ChunkNeighbors,
        [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshDirty,
        [none] !MeshColors)
    spawn_prefab_terrain_chunk(world, terrain_chunk_size);
    spawn_prefab_terrain_chunk_octree(world, terrain_chunk_size);
    #ifdef zoxel_test_voxels_terrain
    create_terrain();
    #endif
}
#endif