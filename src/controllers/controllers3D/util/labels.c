int get_label_player_character3D(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    if (!character || !zox_has(character, Position3D)) return buffer_index;
    const float3 position3D = zox_get_value(character, Position3D)
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "player [%ix%ix%i]\n", (int) position3D.x, (int) position3D.y, (int) position3D.z);
    return buffer_index;
}

int get_label_player_grounded(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    if (!character || !zox_has(character, Grounded)) return buffer_index;
    const byte grounded = zox_get_value(character, Grounded)
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "%s\n", grounded ? "Grounded" : "Airborne");
    return buffer_index;
}

int get_label_player_chunk_position(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    if (!player || !zox_has(player, CharacterLink)) return buffer_index;
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    if (!character || !zox_has(character, ChunkLink)) return buffer_index;
    const ecs_entity_t chunk = zox_get_value(character, ChunkLink)
    if (!chunk || !zox_has(chunk, ChunkPosition)) return buffer_index;
    const int3 chunk_position = zox_get_value(chunk, ChunkPosition)
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "chunk position [%ix%ix%i]\n",  chunk_position.x, chunk_position.y, chunk_position.z);
    return buffer_index;
}
