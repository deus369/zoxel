

int get_label_player_character2D(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t character2D = zox_get_value(player, CharacterLink)
    if (!character2D || !zox_has(character2D, Position2D)) return buffer_index;
    const float2 position2D = zox_get_value(character2D, Position2D)
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "player [%ix%i]\n", (int) position2D.x, (int) position2D.y);
    return buffer_index;
}