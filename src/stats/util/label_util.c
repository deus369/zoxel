int get_label_local_character_level(ecs_world_t *world, const ecs_entity_t character, char buffer[], int buffer_size, int buffer_index) {
    if (!character) return buffer_index;
    const StatLinks *stats = zox_get(character, StatLinks)
    find_array_component_with_tag(stats, StatSoul, soul_stat)
    if (!zox_has(soul_stat, StatValue)) return buffer_index;
    float level = zox_get_value(soul_stat, StatValue)
    float experience_value = zox_get_value(soul_stat, ExperienceValue)
    float experience_max = zox_get_value(soul_stat, ExperienceMax)
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "lvl %i [%i/%i]\n", (int) level, (int) experience_value, (int) experience_max);
    return buffer_index;
}

int get_label_element_links(ecs_world_t *world, const ecs_entity_t e, char buffer[], int buffer_size, int buffer_index) {
    if (!e || !zox_has(e, ElementLinks)) return buffer_index;
    const ElementLinks *elementLinks = zox_get(e, ElementLinks)
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "[%s]'s elements [%i]\n", zox_get_name(e), elementLinks->length);
    for (int i = 0; i < elementLinks->length; i++) {
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "  [%i] %s\n", i, zox_get_name(elementLinks->value[i]));
    }
    return buffer_index;
}

int get_label_children(ecs_world_t *world, const ecs_entity_t e, char buffer[], int buffer_size, int buffer_index) {
    if (!e || !zox_has(e, Children)) return buffer_index;
    const Children *children = zox_get(e, Children)
    buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "[%s]'s children [%i]\n", zox_get_name(e), children->length);
    for (int i = 0; i < children->length; i++) {
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, "  [%i] %s\n", i, zox_get_name(children->value[i]));
    }
    return buffer_index;
}

int get_label_local_character_health(ecs_world_t *world, const ecs_entity_t character, char buffer[], int buffer_size, int buffer_index) {
    if (character) {
        const StatLinks *statLinks = zox_get(character, StatLinks)
        find_array_component_with_tag(statLinks, HealthStat, health_stat)

        if (!zox_has(health_stat, StatValue)) return buffer_index;

        float health_value = zox_get_value(health_stat, StatValue)
        float health_value_max = zox_get_value(health_stat, StatValueMax)

        //if (!zox_has(meta_stat_health, ZoxName)) zox_log(" ! meta_stat_health has no ZoxName\n")
        //if (!zox_has(health_stat, ZoxName)) zox_log(" ! health_stat has no ZoxName\n")
        if (!zox_has(health_stat, ZoxName)) return buffer_index;

        const ZoxName *health_name = zox_get(health_stat, ZoxName)
        char *name_string = convert_zext_to_text(health_name->value, health_name->length);
        // snprintf(text, hierarchy_max_line_characters, "%s", health_name_string);
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " %s [%i/%i] ", name_string, (int) health_value, (int) health_value_max);
        free(name_string);
    }
    return buffer_index;
}

// used for editor
void add_to_labels_stat_links(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level) {
    if (!(e && zox_has(e, StatLinks))) return;
    tree_level++;
    const StatLinks *component = zox_get(e, StatLinks)
    for (int i = 0; i < component->length; i++) add_entity_to_labels(world,  component->value[i], labels, entities, tree_level);
}

int debug_can_jump(ecs_world_t *world, const ecs_entity_t character, char buffer[], int buffer_size, int buffer_index) {
    if (character) {
        const unsigned char can_jump = zox_get_value(character, Grounded)
        const int is_jump = (int) 1000.0 * zox_get_value(character, Jump)
        // const unsigned char movement_disabled = zox_get_value(character, DisableMovement)
        // buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " grounded [%i] movement_disabled [%i]", can_jump, movement_disabled);
        buffer_index += snprintf(buffer + buffer_index, buffer_size - buffer_index, " grounded [%i] jump [%i ms]", can_jump, is_jump);
    }
    return buffer_index;
}
