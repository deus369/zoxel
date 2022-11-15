//! Our function that creates a chunk.
void GenerateChunkTerrain(Chunk* chunk, const ChunkSize *chunkSize)
{
    // const int2 valueRange = { 0, 2 };   // < max
    unsigned char terrain_height = rand() % 16;
    int array_index = 0;
    for (int j = 0; j < chunkSize->value.x; j++)
    {
        for (int k = 0; k < chunkSize->value.y; k++)
        {
            for (int l = 0; l < chunkSize->value.z; l++)
            {
                // int array_index = (j + k * chunkSize->value.x)  * chunkSize->value.y + l;
                /*int distanceToMidX = abs_integer(chunkSize->value.x / 2 - j);
                int distanceToMidY = abs_integer(chunkSize->value.y / 2 - k);
                int distanceToMidZ = abs_integer(chunkSize->value.z / 2 - l);
                if (distanceToMidX + distanceToMidY >= chunkSize->value.x / 2
                    || distanceToMidX + distanceToMidZ >= chunkSize->value.x / 2
                    || distanceToMidZ + distanceToMidY >= chunkSize->value.x / 2)
                {
                    chunk->value[array_index] = 0;
                    array_index++;
                    continue;
                }
                if (rand() % 100 <= dissapearChance)
                {
                    chunk->value[array_index] = 0;
                    array_index++;
                    continue;
                }*/

                if (k <= terrain_height + rand() % 3)
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
                array_index++;
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
    EntityDirty *entityDirtys = ecs_field(it, EntityDirty, 2);
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
        EntityDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value != 0)
        {
            continue;
        }
        entityDirty->value = 1;
        Chunk *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        re_initialize_memory_component(chunk, unsigned char, chunkSize->value.x * chunkSize->value.y * chunkSize->value.z);
        GenerateChunkTerrain(chunk, chunkSize);
        // printf("Terrain Chunk Generated: [%lu] \n", (long int) it->entities[i]);
    }
}
ECS_SYSTEM_DECLARE(TerrainChunkSystem);