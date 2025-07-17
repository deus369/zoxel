uint get_label_player_chunk_link(ecs_world_t *world,
    const ecs_entity_t player,
    char *buffer,
    const uint size, uint index)
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
    return get_label_chunk_link(world, characterLink->value, buffer, size, index);
}
