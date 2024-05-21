void ChunkEntitiesTriggerSystem(ecs_iter_t *it) {
    zox_field_in(ChunkDirty, chunkDirtys, 2)
    zox_field_out(GenerateChunkEntities, generateChunkEntitiess, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ChunkDirty, chunkDirtys, chunkDirty)
        if (!chunkDirty->value) continue;
        zox_field_i_out(GenerateChunkEntities, generateChunkEntitiess, generateChunkEntities) // on ChunkDirty, generate chunk entities
        if (generateChunkEntities->value == zox_chunk_entities_state_initial) generateChunkEntities->value = zox_chunk_entities_state_triggered;
    }
} zox_declare_system(ChunkEntitiesTriggerSystem)
