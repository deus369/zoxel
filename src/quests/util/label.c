uint get_label_quests(ecs_world_t *world, const ecs_entity_t player, char *buffer, const uint size, uint index) {
    if (!player) {
        index += snprintf(buffer + index, size - index, "! invalid player\n");
        return index;
    }
    zox_geter(player, CharacterLink, characterLink)
    if (!zox_valid(characterLink->value)) {
        index += snprintf(buffer + index, size - index, "[%s] has no character\n", zox_get_name(player));
        return index;
    }
    zox_geter(characterLink->value, QuestLinks, quests)
    index += snprintf(buffer + index, size - index, "[%s] has [%i] quests\n", zox_get_name(player), quests->length);
    for (int i = 0; i < quests->length; i++) {
        const ecs_entity_t action = quests->value[i];
        if (!zox_valid(action)) {
            continue;
        }
        index += snprintf(buffer + index, size - index, " - [%i] %s\n", i, zox_get_name(action));
    }
    return index;
}