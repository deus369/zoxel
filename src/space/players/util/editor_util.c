unsigned char debug_colliders = 0;

void toggle_collision_debug(ecs_world_t *world) {
    if (!zox_valid(local_terrain)) return;
    debug_colliders = !debug_colliders;
    if (debug_colliders) add_physics_debug(world, prefab_character3D);
    else remove_physics_debug(world, prefab_character3D);
    const ChunkLinks *chunkLinks = zox_get(local_terrain, ChunkLinks)
    // for every chunk, use entity links, add or remove physics debug components
    // zox_log("   > chunkLinks [%i]\n", chunkLinks->value->size)
    for (int i = 0; i < chunkLinks->value->size; i++) {
        int3_hash_map_pair* pair = chunkLinks->value->data[i];
        while (pair != NULL) {
            ecs_entity_t chunk = pair->value;
            const EntityLinks *entityLinks = zox_get(chunk, EntityLinks)
            // const int3 chunk_position = zox_get_value(chunk, ChunkPosition)
            // if (entityLinks->length > 0 || int3_equals(chunk_position, (int3) { 0, -1, 0 })) zox_log("      > chunk [%lu] entities [%i]\n", chunk, entityLinks->length)
            for (int j = 0; j < entityLinks->length; j++) {
                ecs_entity_t character_entity = entityLinks->value[j];
                if (debug_colliders) add_physics_debug(world, character_entity);
                else remove_physics_debug(world, character_entity);
                // zox_log("           > character_entity [%lu]\n", character_entity)
            }
            pair = pair->next;
        }
    }
}
