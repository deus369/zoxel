ecs_entity_t main_terrain_world;

int get_chunk_index(int i, int j, int rows)
{
    return (i + rows) * (rows + rows + 1) + (j + rows);
}

int get_terrain_chunks_count(int rows, int vertical_rows)
{
    return (vertical_rows + vertical_rows + 1) * (rows + rows + 1) * (rows + rows + 1);
}

int get_chunk_index_2(int i, int j, int k, int rows, int vertical)
{
    i += rows;
    j += vertical;
    k += rows;
    return i * (rows + rows + 1) + j * (rows + rows + 1) * (rows + rows + 1) + k;
    // return i * (rows + rows + 1) + k * (rows + rows + 1) * (rows + rows + 1) + j;
}

void create_terrain(ecs_world_t *world)
{
    #ifdef voxel_octrees
        int chunks_total_length = get_terrain_chunks_count(terrain_rows, terrain_vertical);
    #else
        int chunks_total_length = get_terrain_chunks_count(terrain_rows, 0);
    #endif
    // printf("Spawning Terrain Chunks [%i]\n\n", chunks_total_length); 
    // todo: create a hashmap here
    ecs_defer_begin(world);
    ecs_entity_t terrain_world = spawn_terrain(world, prefab_terrain, float3_zero, 1.0f);  // todo link world to chunks and vice versa
    ecs_entity_t chunks[chunks_total_length];
    /*for (int i = 0; i < chunks_total_length; i++)
    {
        chunks[i] = 0;
    }*/
    for (int i = -terrain_rows; i <= terrain_rows; i++)
    {
        for (int k = -terrain_rows; k <= terrain_rows; k++)
        {
            #ifdef voxel_octrees
            for (int j = -terrain_vertical; j <= terrain_vertical; j++)
            #else
            int j = 0;
            #endif
            {
                // printf("%ix%i index is %i\n", i, j, get_chunk_index(i, j, terrain_rows));
                // printf("%ix%ix%i index is %i out of %i\n", i, j, k, get_chunk_index_2(i, j, k, terrain_rows), chunks_total_length)
                #ifdef voxel_octrees
                chunks[get_chunk_index_2(i, j, k, terrain_rows, terrain_vertical)] = spawn_terrain_chunk_octree(world,
                    prefab_terrain_chunk_octree,
                    terrain_world,
                    (int3) { i, j, k },
                    (float3) { i * chunk_real_size, j * chunk_real_size, k * chunk_real_size },
                    0.5f);
                #else
                chunks[get_chunk_index_2(i, j, k, terrain_rows, 0)] = spawn_terrain_chunk(world, prefab_terrain_chunk,
                    (int3) { i, 0, k }, (float3) { i * chunk_real_size, 0, k * chunk_real_size }, 0.5f);
                #endif
            }
        }
    }
    /*for (int i = 0; i < chunks_total_length; i++)
    {
        if (chunks[i] == 0)
        {
            zoxel_log("One chunk not set at: %i\n", i);
        }
    }*/
    // now for all of them, set their neighbors
    for (int i = -terrain_rows; i <= terrain_rows; i++)
    {
        for (int k = -terrain_rows; k <= terrain_rows; k++)
        {
            #ifdef voxel_octrees
                for (int j = -terrain_vertical; j <= terrain_vertical; j++)
                {
                    set_chunk_neighbors_six_directions(world,
                        chunks[get_chunk_index_2(i, j, k, terrain_rows, terrain_vertical)],
                        i == -terrain_rows ? 0 : chunks[get_chunk_index_2(i - 1, j, k, terrain_rows, terrain_vertical)],
                        i == terrain_rows ? 0 : chunks[get_chunk_index_2(i + 1, j, k, terrain_rows, terrain_vertical)],
                        j == -terrain_vertical ? 0 : chunks[get_chunk_index_2(i, j - 1, k, terrain_rows, terrain_vertical)],
                        j == terrain_vertical ? 0 : chunks[get_chunk_index_2(i, j + 1, k, terrain_rows, terrain_vertical)],
                        k == -terrain_rows ? 0 : chunks[get_chunk_index_2(i, j, k - 1, terrain_rows, terrain_vertical)],
                        k == terrain_rows ? 0 : chunks[get_chunk_index_2(i, j, k + 1, terrain_rows, terrain_vertical)]);
                }
            #else
                int j = 0;
                set_chunk_neighbors(world,
                        chunks[get_chunk_index_2(i, j, k, terrain_rows, 0)],
                        i == -terrain_rows ? 0 : chunks[get_chunk_index_2(i - 1, j, k, terrain_rows, 0)],
                        i == terrain_rows ? 0 : chunks[get_chunk_index_2(i + 1, j, k, terrain_rows, 0)],
                        k == -terrain_rows ? 0 : chunks[get_chunk_index_2(i, j, k - 1, terrain_rows, 0)],
                        k == terrain_rows ? 0 : chunks[get_chunk_index_2(i, j, k + 1, terrain_rows, 0)]);
            #endif
        }
    }
    ChunkLinks chunkLinks = { };
    initialize_memory_component_non_pointer(chunkLinks, ecs_entity_t, chunks_total_length);
    for (int i = 0; i < chunks_total_length; i++)
    {
        chunkLinks.value[i] = chunks[i];
    }
    ecs_set(world, terrain_world, ChunkLinks, { chunkLinks.length, chunkLinks.value });
    main_terrain_world = terrain_world;
    ecs_defer_end(world);
}
