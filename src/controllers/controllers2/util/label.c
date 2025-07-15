int get_label_player_character2D(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t character2D = zox_get_value(player, CharacterLink)
    if (!character2D || !zox_has(character2D, Position2D)) return buffer_index;
    const float2 position2D = zox_get_value(character2D, Position2D)
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "player [%ix%i]\n", (int) position2D.x, (int) position2D.y);
    return buffer_index;
}

uint get_label_character2_player(ecs_world_t *world,
    const ecs_entity_t player,
    char *buffer,
    const uint size,
    uint index)
{
    if (!player) {
        index += snprintf(buffer + index, size - index, "! invalid player\n");
        return index;
    }
    zox_geter(player, CharacterLink, characterLink)
    if (!zox_valid(characterLink->value)) {
        index += snprintf(buffer + index, size - index, "[%s] has no character\n", zox_get_name(player));
        return index;
    }
    zox_geter_value(player, CameraLink, ecs_entity_t, camera)
    zox_geter_value(characterLink->value, Position2D, float2, position2)
    zox_geter_value(camera, Position3D, float3, camera_position3)
    index += snprintf(buffer + index, size - index, "player [%s]:\n", zox_get_name(player));
    index += snprintf(buffer + index, size - index, "   - is controlling [%s]\n",  zox_get_name(characterLink->value));
    index += snprintf(buffer + index, size - index, "   - is looking from [%s]\n", zox_get_name(camera));
    index += snprintf(buffer + index, size - index, "   - located at [%fx%f]\n", position2.x, position2.y);
    index += snprintf(buffer + index, size - index, "   - camera at [%fx%f]x%f]\n", camera_position3.x, camera_position3.y, camera_position3.z);
    return index;
}