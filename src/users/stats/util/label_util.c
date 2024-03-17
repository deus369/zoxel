int get_label_local_character_level(ecs_world_t *world, char buffer[], int buffer_size, int buffer_index) {
    if (local_character3D) {
        const StatLinks *userStatLinks = zox_get(local_character3D, StatLinks)
        ecs_entity_t soul_stat = userStatLinks->value[1];
        if (!zox_has(soul_stat, StatValue)) return buffer_index;
        float level = zox_get_value(soul_stat, StatValue)
        float experience_value = zox_get_value(soul_stat, ExperienceValue)
        float experience_max = zox_get_value(soul_stat, ExperienceMax)
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " lvl %i [%i/%i]", (int) level, (int) experience_value, (int) experience_max);
    }
    return buffer_index;
}

int get_label_local_character_health(ecs_world_t *world, char buffer[], int buffer_size, int buffer_index) {
    if (local_character3D) {
        const StatLinks *statLinks = zox_get(local_character3D, StatLinks)
        ecs_entity_t health_stat = statLinks->value[0];

        if (!zox_has(health_stat, StatValue)) return buffer_index;

        float health_value = zox_get_value(health_stat, StatValue)
        float health_value_max = zox_get_value(health_stat, StatValueMax)

        //if (!zox_has(meta_stat_health, ZoxName)) zox_logg(" ! meta_stat_health has no ZoxName\n")
        //if (!zox_has(health_stat, ZoxName)) zox_logg(" ! health_stat has no ZoxName\n")
        if (!zox_has(health_stat, ZoxName)) return buffer_index;

        const ZoxName *health_name = zox_get(health_stat, ZoxName)
        char *name_string = convert_zext_to_text(health_name->value, health_name->length);
        // snprintf(text, hierarchy_max_line_characters, "%s", health_name_string);

        buffer_index += snprintf(buffer + buffer_index, buffer_size, " %s [%i/%i] ", name_string, (int) health_value, (int) health_value_max);

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

int debug_can_jump(ecs_world_t *world, char buffer[], int buffer_size, int buffer_index) {
    if (local_character3D) {
        const unsigned char can_jump = zox_get_value(local_character3D, Grounded)
        const int is_jump = (int) 1000.0 * zox_get_value(local_character3D, Jump)
        // const unsigned char movement_disabled = zox_get_value(local_character3D, DisableMovement)
        // buffer_index += snprintf(buffer + buffer_index, buffer_size, " grounded [%i] movement_disabled [%i]", can_jump, movement_disabled);
        buffer_index += snprintf(buffer + buffer_index, buffer_size, " grounded [%i] jump [%i ms]", can_jump, is_jump);
        //buffer_index += snprintf(buffer + buffer_index, buffer_size, " grounded [%i]", can_jump);
    }
    return buffer_index;
}
