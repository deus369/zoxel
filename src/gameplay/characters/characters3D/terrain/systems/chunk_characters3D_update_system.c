// when terrain lod updates, it will update character lods
void ChunkCharactersUpdateSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(RenderLod, renderLods, 1)
    zox_field_in(EntityLinks, entityLinkss, 2)
    zox_field_in(GenerateChunkEntities, generateChunkEntitiess, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(GenerateChunkEntities, generateChunkEntitiess, generateChunkEntities)
        if (generateChunkEntities->value != zox_chunk_entities_state_spawned) continue;
        zox_field_i_in(EntityLinks, entityLinkss, entityLinks)
        if (!entityLinks->length) continue;
        if (!entityLinks->value) zox_log(" > chunk has null entityLinks [%lu]\n", it->entities[i])
        if (!entityLinks->value) continue; // this should never be null
        zox_field_i_in(RenderLod, renderLods, renderLod)
        const unsigned char camera_distance = renderLod->value;
        const unsigned char character_depth = get_character_division_from_camera(camera_distance);
        const ecs_entity_t first_e = entityLinks->value[0];
        if (!first_e) continue;
        const unsigned char character_chunk_division = zox_get_value(first_e, RenderLod)
        if (character_chunk_division == character_depth) continue;  // check if characters division is changed from chunks
        for (int j = 0; j < entityLinks->length; j++) {
            const ecs_entity_t character_entity = entityLinks->value[j];
            zox_set(character_entity, RenderLod, { character_depth })
            zox_set(character_entity, ChunkDirty, { 1 })
        }
    }
} zox_declare_system(ChunkCharactersUpdateSystem)
