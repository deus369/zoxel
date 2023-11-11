void ChunkEntitiesTriggerSystem(ecs_iter_t *it) {
    const ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 2);
    GenerateChunkEntities *generateChunkEntities = ecs_field(it, GenerateChunkEntities, 3);
    for (int i = 0; i < it->count; i++) {
        const ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (!chunkDirty->value) continue;
        // on ChunkDirty, generate chunk entities
        GenerateChunkEntities *generateChunkEntities2 = &generateChunkEntities[i];
        if (generateChunkEntities2->value != zox_chunk_entities_state_initial) continue;
        generateChunkEntities2->value = zox_chunk_entities_state_triggered;
        // zoxel_log(" > chunk entities was triggered [%lu]\n", it->entities[i]);
    }
} zox_declare_system(ChunkEntitiesTriggerSystem)
