ecs_entity_t *terrain_chunks;
int terrain_chunks_count;

int get_chunk_index(int i, int j, int rows) {
    return (i + rows) * (rows + rows + 1) + (j + rows);
}

int get_terrain_chunks_count(int rows, int vertical_rows) {
    return (vertical_rows + vertical_rows + 1) * (rows + rows + 1) * (rows + rows + 1);
}

int get_chunk_index_2(int i, int j, int k, int rows, int vertical) {
    i += rows;
    j += vertical;
    k += rows;
    return i * (rows + rows + 1) + j * (rows + rows + 1) * (rows + rows + 1) + k;
}

void create_terrain(ecs_world_t *world) {
    #ifdef voxel_octrees
        int chunks_total_length = get_terrain_chunks_count(terrain_spawn_distance, terrain_vertical);
    #else
        int chunks_total_length = get_terrain_chunks_count(terrain_spawn_distance, 0);
    #endif
    // printf("Spawning Terrain Chunks [%i]\n\n", chunks_total_length); 
    // todo: create a hashmap here
    ecs_defer_begin(world);
    ecs_entity_t terrain_world = spawn_terrain(world, prefab_terrain, float3_zero, 1.0f);  // todo link world to chunks and vice versa
    ecs_entity_t chunks[chunks_total_length];
    int3 chunk_positions[chunks_total_length];
    for (int i = -terrain_spawn_distance; i <= terrain_spawn_distance; i++) {
        for (int k = -terrain_spawn_distance; k <= terrain_spawn_distance; k++) {
            #ifdef voxel_octrees
                for (int j = -terrain_vertical; j <= terrain_vertical; j++)
            #else
                int j = 0;
            #endif
            {
                // printf("%ix%i index is %i\n", i, j, get_chunk_index(i, j, terrain_spawn_distance));
                // printf("%ix%ix%i index is %i out of %i\n", i, j, k, get_chunk_index_2(i, j, k, terrain_spawn_distance), chunks_total_length)
                #ifdef voxel_octrees
                    int index = get_chunk_index_2(i, j, k, terrain_spawn_distance, terrain_vertical);
                    int3 chunk_position = (int3) { i, j, k };
                    chunks[index] = spawn_terrain_chunk_octree(world, prefab_terrain_chunk_octree, terrain_world,
                        chunk_position, (float3) { i * chunk_real_size, j * chunk_real_size, k * chunk_real_size }, 0.5f);
                    chunk_positions[index] = chunk_position;
                #else
                    chunks[get_chunk_index_2(i, j, k, terrain_spawn_distance, 0)] = spawn_terrain_chunk(world, prefab_terrain_chunk,
                        (int3) { i, 0, k }, (float3) { i * chunk_real_size, 0, k * chunk_real_size }, 0.5f);
                #endif
            }
        }
    }
    // now for all of them, set their neighbors
    for (int i = -terrain_spawn_distance; i <= terrain_spawn_distance; i++) {
        for (int k = -terrain_spawn_distance; k <= terrain_spawn_distance; k++) {
            #ifdef voxel_octrees
                for (int j = -terrain_vertical; j <= terrain_vertical; j++) {
                    set_chunk_neighbors_six_directions(world,
                        chunks[get_chunk_index_2(i, j, k, terrain_spawn_distance, terrain_vertical)],
                        i == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i - 1, j, k, terrain_spawn_distance, terrain_vertical)],
                        i == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i + 1, j, k, terrain_spawn_distance, terrain_vertical)],
                        j == -terrain_vertical ? 0 : chunks[get_chunk_index_2(i, j - 1, k, terrain_spawn_distance, terrain_vertical)],
                        j == terrain_vertical ? 0 : chunks[get_chunk_index_2(i, j + 1, k, terrain_spawn_distance, terrain_vertical)],
                        k == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k - 1, terrain_spawn_distance, terrain_vertical)],
                        k == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k + 1, terrain_spawn_distance, terrain_vertical)]);
                }
            #else
                int j = 0;
                set_chunk_neighbors(world,
                        chunks[get_chunk_index_2(i, j, k, terrain_spawn_distance, 0)],
                        i == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i - 1, j, k, terrain_spawn_distance, 0)],
                        i == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i + 1, j, k, terrain_spawn_distance, 0)],
                        k == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k - 1, terrain_spawn_distance, 0)],
                        k == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k + 1, terrain_spawn_distance, 0)]);
            #endif
        }
    }
    terrain_chunks = malloc(sizeof(ecs_entity_t) * chunks_total_length);
    for (int i = 0; i < chunks_total_length; i++) {
        terrain_chunks [i] = chunks[i];
    }
    terrain_chunks_count = chunks_total_length;
    ChunkLinks chunkLinks = { };
    chunkLinks.value = create_int3_hash_map(chunks_total_length);
    for (int i = 0; i < chunks_total_length; i++) {
        int3_hash_map_add(chunkLinks.value, chunk_positions[i], chunks[i]);
    }
    ecs_set(world, terrain_world, ChunkLinks, { chunkLinks.value });
    ecs_defer_end(world);
}

/*ChunkLinks chunkLinks = { };
initialize_memory_component_non_pointer(chunkLinks, ecs_entity_t, chunks_total_length);
for (int i = 0; i < chunks_total_length; i++) {
    chunkLinks.value[i] = chunks[i];
}
ecs_set(world, terrain_world, ChunkLinks, { chunkLinks.length, chunkLinks.value });*/