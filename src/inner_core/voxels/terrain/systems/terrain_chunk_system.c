const unsigned char terrain_min_height = 8;
const double terrain_amplifier = 120.0;
const double terrain_frequency = 0.004216;
const int terrain_octaves = 12;
const uint32_t terrain_seed = 32666;

int3 voxel_chunk_position(int3 chunk_position, int3 chunk_size)
{
    int3 voxel_position = int3_multiply_int3(chunk_position, chunk_size);
    if (voxel_position.x < 0)
    {
        voxel_position.x += 1;
    }
    if (voxel_position.y < 0)
    {
        voxel_position.y += 1;
    }
    if (voxel_position.z < 0)
    {
        voxel_position.z += 1;
    }
    return voxel_position;
}

int3 voxel_chunk_position_xz(int3 chunk_position, int3 chunk_size)
{
    int3 voxel_position = int3_multiply_int3(chunk_position, chunk_size);
    if (voxel_position.x < 0)
    {
        voxel_position.x += 1;
    }
    if (voxel_position.z < 0)
    {
        voxel_position.z += 1;
    }
    return voxel_position;
}


//! Our function that creates a chunk.
void GenerateChunkTerrain(ChunkData* chunk, const int3 chunkSize, const int3 chunkPosition)
{
    // srand(666);
    int3 local_position;
    int3 global_position;
    int3 chunk_position_offset = voxel_chunk_position_xz(chunkPosition, chunkSize);
    for (local_position.x = 0; local_position.x < chunkSize.x; local_position.x++)
    {
        for (local_position.z = 0; local_position.z < chunkSize.z; local_position.z++)
        {
            local_position.y = 0;
            global_position = int3_add(local_position, chunk_position_offset);
            // printf("global_position [%ix%ix%i]\n", global_position.x, global_position.y, global_position.z);
            // printf("global_position: [%fx%fx%f]\n", global_position.x, global_position.y, global_position.z);
            float2 noise_point = float2_from_int2((int2) { global_position.x, global_position.z });
            noise_point.x += 3200;
            noise_point.y += 3200;
            int terrain_height2 = terrain_min_height +
                // int_floor(terrain_amplifier * simplex_fun_2D(noise_point, terrain_frequency));
                // int_floor(terrain_amplifier * perlin_noise(noise_point.x, noise_point.y, terrain_frequency, seed));
                int_floor(terrain_amplifier * perlin_terrain(noise_point.x, noise_point.y,
                    terrain_frequency, terrain_seed, terrain_octaves));
                // int_floor(terrain_amplifier * generate_noise_2D(noise_point, terrain_frequency));
            if (terrain_height2 < terrain_min_height)
            {
                terrain_height2 = terrain_min_height;
            }
            // unsigned char terrain_height2 = terrain_height + rand() % terrain_height_amplifier;
            for (local_position.y = 0; local_position.y < chunkSize.y; local_position.y++)
            {
                int array_index = int3_array_index(local_position, chunkSize);
                if (local_position.y <= terrain_height2)
                {
                    chunk->value[array_index] = 1;
                }
                else
                {
                    chunk->value[array_index] = 0;
                }
                // valueRange.x + rand() % (valueRange.y - valueRange.x);
                /*if (k == 0 && l == 0)
                    chunk->value[array_index] = 1;
                else
                    chunk->value[array_index] = 0;*/
                // array_index++;
            }
        }
    }
}

void TerrainChunkSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 2);
    ChunkData *chunks = ecs_field(it, ChunkData, 3);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 4);
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 5);
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 6);
    for (int i = 0; i < it->count; i++)
    {
        const GenerateChunk *generateChunk = &generateChunks[i];
        //! Only rebuild if GenerateChunk is set to 1 and EntityDirty is false.
        if (generateChunk->value == 0)
        {
            continue;
        }
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value != 0)
        {
            continue;
        }
        chunkDirty->value = 1;
        ChunkData *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        const ChunkPosition *chunkPosition = &chunkPositions[i];
        re_initialize_memory_component(chunk, unsigned char, chunkSize->value.x * chunkSize->value.y * chunkSize->value.z);
        GenerateChunkTerrain(chunk, chunkSize->value, chunkPosition->value);
        // printf("Terrain ChunkData Generated: [%lu] \n", (long int) it->entities[i]);
    }
}
zoxel_declare_system(TerrainChunkSystem)