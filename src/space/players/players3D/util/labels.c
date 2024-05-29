int get_label_player_character3D(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t character2D = zox_get_value(player, CharacterLink)
    if (!character2D || !zox_has(character2D, Position3D)) return buffer_index;
    const float3 position3D = zox_get_value(character2D, Position3D)
    buffer_index += snprintf(buffer + buffer_index, buffer_size, "player [%ix%ix%i]\n", (int) position3D.x, (int) position3D.y, (int) position3D.z);
    return buffer_index;
}

int get_label_player_grounded(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    if (!character || !zox_has(character, Grounded)) return buffer_index;
    const unsigned char grounded = zox_get_value(character, Grounded)
    buffer_index += snprintf(buffer + buffer_index, buffer_size, "%s\n", grounded ? "Grounded" : "Airborne");
    return buffer_index;
}
