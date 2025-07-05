uint get_label_realm_colors(ecs_world_t *world, const ecs_entity_t player, char *buffer, const uint size, uint index) {
    if (!zox_valid(player)) {
        index += snprintf(buffer + index, size - index, "! invalid player\n");
        return index;
    }
    zox_geter(player, GameLink, gameLink)
    zox_geter(gameLink->value, RealmLink, realmLink)
    if (!zox_valid(realmLink->value) || !zox_has(realmLink->value, Colors)) {
        index += snprintf(buffer + index, size - index, "[%s] has invalid realm\n", zox_get_name(player));
        return index;
    }
    zox_geter(realmLink->value, Colors, colors)
    zox_geter(realmLink->value, Seed, seed)
    index += snprintf(buffer + index, size - index, "[%s]\n", zox_get_name(realmLink->value));
    index += snprintf(buffer + index, size - index, " - total [%i]\n", colors->length);
    index += snprintf(buffer + index, size - index, " - seed [%lu]\n", seed->value);
    for (int i = 0; i < colors->length; i++) {
        const color c = colors->value[i];
        index += snprintf(buffer + index, size - index, " - [%i] [%i.%i.%i]\n", i, c.r, c.g, c.b);
    }
    return index;
}