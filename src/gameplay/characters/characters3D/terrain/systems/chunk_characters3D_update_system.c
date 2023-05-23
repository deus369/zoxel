void ChunkCharactersUpdateSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 2);
    const ChunkDivision *chunkDivisions = ecs_field(it, ChunkDivision, 3);
    const EntityLinks *entityLinks = ecs_field(it, EntityLinks, 4);
    for (int i = 0; i < it->count; i++) {
        const ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value == 0) continue;
        const EntityLinks *entityLinks2 = &entityLinks[i];
        if (entityLinks2->length == 0) continue;
        const ChunkDivision *chunkDivision = &chunkDivisions[i];
        unsigned char camera_distance = chunkDivision->value;
        unsigned char character_depth = get_character_division_from_camera(camera_distance);
        unsigned char character_chunk_division = ecs_get(world, entityLinks2->value[0], ChunkDivision)->value;
        // check if characters division is changed from chunks
        if (character_chunk_division == character_depth) continue;
        //zoxel_log(" > characters in chunk updating %lu > %i [depth %i to %i]\n", it->entities[i],
        //    entityLinks2->length, character_chunk_division, character_depth);
        for (int j = 0; j < entityLinks2->length; j++) {
            ecs_entity_t character_entity = entityLinks2->value[j];
            ecs_set(world, character_entity, ChunkDivision, { character_depth });
            ecs_set(world, character_entity, ChunkDirty, { 1 });
        }
    }
}
zox_declare_system(ChunkCharactersUpdateSystem)