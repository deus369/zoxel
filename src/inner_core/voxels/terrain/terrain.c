#ifndef zoxel_voxels_terrain
#define zoxel_voxels_terrain

const int terrain_rows = 8;
const int3 terrain_chunk_size = { chunk_length, 8 * chunk_length, chunk_length };
float chunk_real_size = overall_voxel_scale / 2.0f; // 1.0f;   // size achunk takes up
zoxel_declare_tag(ChunkTerrain)
// #include "util/vox_read_util.c"
#include "prefabs/terrain_chunk.c"
// #include "systems/noise_chunk_system.c"

int get_chunk_index(int i, int j, int terrain_rows)
{
    return (i + terrain_rows) * (terrain_rows + terrain_rows + 1) + (j + terrain_rows);
}

//! The Terrain Sub Module of Voxels.
void TerrainImport(ecs_world_t *world)
{
    zoxel_module(Terrain)
    zoxel_define_tag(ChunkTerrain)
    spawn_prefab_terrain_chunk(world, terrain_chunk_size);
    // spawn_prefab_vox(world);
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
            chunks[get_chunk_index(i, j, terrain_rows)] = spawn_terrain_chunk(world, terrain_chunk_prefab,
                (int3) { i, 0, j }, (float3) { i * chunk_real_size, 0, j * chunk_real_size }, 0.5f);
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