//! Our function that creates a chunk.
void GenerateChunkNoise(Chunk* chunk, const ChunkSize *chunkSize)
{
    const int2 valueRange = { 0, 2 };   // < max
    int index = 0;
    for (int j = 0; j < chunkSize->value.x; j++)
    {
        for (int k = 0; k < chunkSize->value.y; k++)
        {
            for (int l = 0; l < chunkSize->value.y; l++)
            {
                // int index = (j + k * chunkSize->value.x)  * chunkSize->value.y + l;
                int distanceToMidX = abs_integer(chunkSize->value.x / 2 - j);
                int distanceToMidY = abs_integer(chunkSize->value.y / 2 - k);
                int distanceToMidZ = abs_integer(chunkSize->value.z / 2 - l);
                if (distanceToMidX + distanceToMidY + distanceToMidZ >= chunkSize->value.x / 2)
                {
                    chunk->value[index] = 0;
                    index++;
                    continue;
                }
                chunk->value[index] = valueRange.x + rand() % (valueRange.y - valueRange.x);
                index++;
            }
        }
    }
}

void NoiseChunkSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery)
    {
        printf("[404; changeQuery is null]\n");
        return;
    }
    if (!ecs_query_changed(changeQuery, NULL))
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
        GenerateChunkNoise(chunk, chunkSize);
        printf("Noise Chunk Generated: [%lu] \n", (long int) it->entities[i]);
    }
}
ECS_SYSTEM_DECLARE(NoiseChunkSystem);