//! Resets EntityDirty after one frame.
void GenerateChunkResetSystem(ecs_iter_t *it)
{
    if (!ecs_query_changed(NULL, it))
    {
        return;
    }
    ecs_query_skip(it);
    GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 1);
    for (int i = 0; i < it->count; i++)
    {
        GenerateChunk *generateChunk = &generateChunks[i];
        if (generateChunk->value == 1)
        {
            generateChunk->value = 0;
        }
    }
}
ECS_SYSTEM_DECLARE(GenerateChunkResetSystem);