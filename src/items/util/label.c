uint get_label_player_items(ecs_world_t *world, const ecs_entity_t player, char *buffer, const uint size, uint index) {
    if (!player) {
        index += snprintf(buffer + index, size - index, "! invalid player\n");
        return index;
    }
    zox_geter(player, CharacterLink, characterLink)
    if (!zox_valid(characterLink->value)) {
        index += snprintf(buffer + index, size - index, "[%s] has no character\n", zox_get_name(player));
        return index;
    }
    zox_geter(characterLink->value, ItemLinks, items)
    index += snprintf(buffer + index, size - index, "[%s] has [%i] items\n", zox_get_name(player), items->length);
    for (int i = 0; i < items->length; i++) {
        const ecs_entity_t action = items->value[i];
        if (!zox_valid(action)) {
            continue;
        }
        index += snprintf(buffer + index, size - index, " - [%i] %s\n", i, zox_get_name(action));
    }
    return index;
}