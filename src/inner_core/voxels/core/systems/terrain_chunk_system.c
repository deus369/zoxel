const unsigned char terrain_noise = 2;

//! Our function that creates a chunk.
void GenerateChunkTerrain(Chunk* chunk, const ChunkSize *chunkSize)
{
    // const int2 valueRange = { 0, 2 };   // < max
    unsigned char terrain_height = 0; // (chunkSize->value.y / 4) + rand() % ((int) (chunkSize->value.y * (3.0f / 4.0f)));
    int3 local_position;
    // precount our face data for initialization
    for (local_position.x = 0; local_position.x < chunkSize->value.x; local_position.x++)
    {
        for (local_position.z = 0; local_position.z < chunkSize->value.z; local_position.z++)
        {
            unsigned char terrain_height2 = terrain_height + rand() % terrain_noise;
            for (local_position.y = 0; local_position.y < chunkSize->value.y; local_position.y++)
            {
                int array_index = int3_array_index(local_position, chunkSize->value);
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
    ChunkDirty *entityDirtys = ecs_field(it, ChunkDirty, 2);
    Chunk *chunks = ecs_field(it, Chunk, 3);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 4);
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 5);
    for (int i = 0; i < it->count; i++)
    {
        const GenerateChunk *generateChunk = &generateChunks[i];
        //! Only rebuild if GenerateChunk is set to true and EntityDirty is false.
        if (generateChunk->value == 0)
        {
            continue;
        }
        ChunkDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value != 0)
        {
            continue;
        }
        entityDirty->value = 1;
        Chunk *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        re_initialize_memory_component(chunk, unsigned char, chunkSize->value.x * chunkSize->value.y * chunkSize->value.z);
        GenerateChunkTerrain(chunk, chunkSize);
        printf("Terrain Chunk Generated: [%lu] \n", (long int) it->entities[i]);
    }
}
ECS_SYSTEM_DECLARE(TerrainChunkSystem);