// when terrain lod updates, it will update character lods
void ChunkCharactersUpdateSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const RenderLod *renderLods = ecs_field(it, RenderLod, 2);
    const EntityLinks *entityLinks = ecs_field(it, EntityLinks, 3);
    GenerateChunkEntities *generateChunkEntities = ecs_field(it, GenerateChunkEntities, 4);
    for (int i = 0; i < it->count; i++) {
        GenerateChunkEntities *generateChunkEntities2 = &generateChunkEntities[i];
        if (generateChunkEntities2->value != zox_chunk_entities_state_spawned) continue;
        const EntityLinks *entityLinks2 = &entityLinks[i];
        if (entityLinks2->length == 0) continue;
        // zoxel_log(" > entityLinks2->length: %i\n", entityLinks2->length);
        const RenderLod *renderLod = &renderLods[i];
        unsigned char camera_distance = renderLod->value;
        unsigned char character_depth = get_character_division_from_camera(camera_distance);
        // if (entityLinks2->value[0] == 0) zoxel_log("issues with character entity\n");
        if (entityLinks2->value[0] == 0) continue;
        unsigned char character_chunk_division = ecs_get(world, entityLinks2->value[0], RenderLod)->value;
        if (character_chunk_division == character_depth) continue;  // check if characters division is changed from chunks
        //zoxel_log(" > characters in chunk updating %lu > %i [depth %i to %i]\n", it->entities[i], entityLinks2->length, character_chunk_division, character_depth);
        for (int j = 0; j < entityLinks2->length; j++) {
            ecs_entity_t character_entity = entityLinks2->value[j];
            zox_set(character_entity, RenderLod, { character_depth })
            zox_set(character_entity, ChunkDirty, { 1 })
        }
        // generateChunkEntities2->value = 0;
        // zoxel_log(" > chunk characters were updated %i\n", entityLinks2->length);
    }
} zox_declare_system(ChunkCharactersUpdateSystem)