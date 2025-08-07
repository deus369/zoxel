uint add_label_stat_level(ecs_world_t *world, const ecs_entity_t character, const StatLinks *stats, const ecs_entity_t tag, char *buffer, const uint size, uint index) {
    find_array_element_with_tag_id(stats, tag, stat)
    if (!zox_valid(stat) || !zox_has(stat, StatValue)) {
        index += snprintf(buffer + index, size - index, "[%s] has no stat [%s]\n", zox_get_name(character), zox_get_name(tag));
        return index;
    }
    zox_geter(stat, ZoxName, zext)
    char *name = convert_zext_to_text(zext->value, zext->length);
    float level = zox_get_value(stat, StatValue)
    float experience_value = zox_get_value(stat, ExperienceValue)
    float experience_max = zox_get_value(stat, ExperienceMax)
    index += snprintf(buffer + index, size - index, "%s [lvl %i - %i/%i]\n", name, (int) level, (int) experience_value, (int) experience_max);
    free(name);
    return index;
}

uint add_label_stat_state(ecs_world_t *world, const ecs_entity_t character, const ecs_entity_t stat, char *buffer, const uint size, uint index) {
    if (!zox_valid(stat) || !zox_has(stat, StatValue) || !zox_has(stat, ZoxName)) {
        index += snprintf(buffer + index, size - index, "[%s] has invalid state stat\n", zox_get_name(character));
        return index;
    }
    zox_geter(stat, ZoxName, zext)
    char *name = convert_zext_to_text(zext->value, zext->length);
    float value = zox_get_value(stat, StatValue)
    float value_max = zox_get_value(stat, StatValueMax)
    index += snprintf(buffer + index, size - index, " - %s [%i/%i]\n", name, (int) value, (int) value_max);
    free(name);
    return index;
}

uint add_label_stat_value(ecs_world_t *world, const ecs_entity_t character, const ecs_entity_t stat, char *buffer, const uint size, uint index) {
    if (!zox_valid(stat) || !zox_has(stat, StatValue) || !zox_has(stat, ZoxName)) {
        index += snprintf(buffer + index, size - index, "[%s] has invalid attribute stat\n", zox_get_name(character));
        return index;
    }
    zox_geter(stat, ZoxName, zext)
    char *name = convert_zext_to_text(zext->value, zext->length);
    float value = zox_get_value(stat, StatValue)
    index += snprintf(buffer + index, size - index, " - %s [%i]\n", name, (int) value);
    free(name);
    return index;
}

// new label ui
uint get_label_player_stats(ecs_world_t *world, const ecs_entity_t player, char *buffer, const uint size, uint index) {
    if (!player) {
        index += snprintf(buffer + index, size - index, "! invalid player\n");
        return index;
    }
    zox_geter(player, CharacterLink, characterLink)
    if (!zox_valid(characterLink->value)) {
        index += snprintf(buffer + index, size - index, "[%s] has no character\n", zox_get_name(player));
        return index;
    }
    zox_geter(characterLink->value, StatLinks, stats)
    index = add_label_stat_level(world, characterLink->value, stats, StatSoul, buffer, size, index);
    for (int i = 0; i < stats->length; i++) {
        const ecs_entity_t stat = stats->value[i];
        if (!zox_valid(stat)) {
            continue;
        }
        if (zox_has(stat, StatState)) {
            index = add_label_stat_state(world, characterLink->value, stat, buffer, size, index);
        } else if (zox_has(stat, StatRegen)) {
            index = add_label_stat_value(world, characterLink->value, stat, buffer, size, index);
        } else if (zox_has(stat, StatAttribute)) {
            index = add_label_stat_value(world, characterLink->value, stat, buffer, size, index);
        }
    }
    zox_geter(characterLink->value, DotLinks, dots)
    for (int i = 0; i < dots->length; i++) {
        const ecs_entity_t dot = dots->value[i];
        if (!zox_valid(dot)) {
            continue;
        }
        index += snprintf(buffer + index, size - index, " . %s\n", zox_get_name(dot));
    }
    return index;
}

// todo: refactor this as a event hook
// used for editor
void add_to_labels_stat_links(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, entity_array_d* entities, int tree_level) {
    if (!(e && zox_has(e, StatLinks))) {
        return;
    }
    tree_level++;
    const StatLinks *component = zox_get(e, StatLinks)
    for (int i = 0; i < component->length; i++) {
        add_entity_to_labels(world,  component->value[i], labels, entities, tree_level);
    }
}

uint get_label_player_element_links(ecs_world_t *world, const ecs_entity_t player, char *buffer, const uint size, uint index) {
    if (!zox_valid(player)) {
        index += snprintf(buffer + index, size - index, "! invalid player\n");
        return index;
    }
    zox_geter(player, CharacterLink, characterLink)
    if (!zox_valid(characterLink->value) || !zox_has(characterLink->value, ElementLinks)) {
        index += snprintf(buffer + index, size - index, "[%s] has invalid character\n", zox_get_name(player));
        return index;
    }
    zox_geter(characterLink->value, ElementLinks, elements)
    index += snprintf(buffer + index, size - index, "[%s]'s elements [%i]\n", zox_get_name(characterLink->value), elements->length);
    for (int i = 0; i < elements->length; i++) {
        index += snprintf(buffer + index, size - index, " - [%i] %s\n", i, zox_get_name(elements->value[i]));
    }
    return index;
}

/*int get_label_local_character_level(ecs_world_t *world, const ecs_entity_t character, char buffer[], int buffer_size, int buffer_index) {
 *    if (!character) return buffer_index;
 *    const StatLinks *stats = zox_get(character, StatLinks)
 *    find_array_element_with_tag(stats, StatSoul, soul_stat)
 *    if (!zox_has(soul_stat, StatValue)) return buffer_index;
 *    float level = zox_get_value(soul_stat, StatValue)
 *    float experience_value = zox_get_value(soul_stat, ExperienceValue)
 *    float experience_max = zox_get_value(soul_stat, ExperienceMax)
 *    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "lvl %i [%i/%i]\n", (int) level, (int) experience_value, (int) experience_max);
 *    return buffer_index;
 * }
 *
 *
 * int get_label_children(ecs_world_t *world, const ecs_entity_t e, char buffer[], int buffer_size, int buffer_index) {
 *    if (!e || !zox_has(e, Children)) return buffer_index;
 *    const Children *children = zox_get(e, Children)
 *    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "[%s]'s children [%i]\n", zox_get_name(e), children->length);
 *    for (int i = 0; i < children->length; i++) {
 *        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "  [%i] %s\n", i, zox_get_name(children->value[i]));
 *    }
 *    return buffer_index;
 * }
 *
 * int get_label_local_character_health(ecs_world_t *world, const ecs_entity_t character, char buffer[], int buffer_size, int buffer_index) {
 *    if (character) {
 *        const StatLinks *statLinks = zox_get(character, StatLinks)
 *        find_array_element_with_tag(statLinks, HealthStat, health_stat)
 *
 *        if (!zox_has(health_stat, StatValue)) return buffer_index;
 *
 *        float health_value = zox_get_value(health_stat, StatValue)
 *        float health_value_max = zox_get_value(health_stat, StatValueMax)
 *
 *        //if (!zox_has(meta_stat_health, ZoxName)) zox_log(" ! meta_stat_health has no ZoxName\n")
 *        //if (!zox_has(health_stat, ZoxName)) zox_log(" ! health_stat has no ZoxName\n")
 *        if (!zox_has(health_stat, ZoxName)) return buffer_index;
 *
 *        const ZoxName *health_name = zox_get(health_stat, ZoxName)
 *        char *name_string = convert_zext_to_text(health_name->value, health_name->length);
 *        // snprintf(text, hierarchy_max_line_characters, "%s", health_name_string);
 *        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " %s [%i/%i] ", name_string, (int) health_value, (int) health_value_max);
 *        free(name_string);
 *    }
 *    return buffer_index;
 * }*/

int debug_can_jump(ecs_world_t *world, const ecs_entity_t character, char buffer[], int buffer_size, int buffer_index) {
    if (character) {
        const byte can_jump = zox_get_value(character, Grounded)
        const int is_jump = (int) 1000.0 * zox_get_value(character, Jump)
        // const byte movement_disabled = zox_get_value(character, DisableMovement)
        // buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " grounded [%i] movement_disabled [%i]", can_jump, movement_disabled);
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " grounded [%i] jump [%i ms]", can_jump, is_jump);
    }
    return buffer_index;
}

