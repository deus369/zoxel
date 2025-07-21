void StatTextSystem(ecs_iter_t *it) {
    int stat_name_text_count = 32;
    int label_text_count = 64;
    char stat_name_text[stat_name_text_count];
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(StatLink)
    zox_sys_out(TextData)
    zox_sys_out(ZextDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(StatLink, statLink)
        zox_sys_o(TextData, textData)
        zox_sys_o(ZextDirty, zextDirty)
        const ecs_entity_t stat = statLink->value;
        if (!zox_valid(stat) || !zox_has(stat, ZoxName) || !zox_has(stat, StatValue)) {
            zox_sys_e()
            zox_log_error("[%s] has invalid stat linked", zox_get_name(e))
            continue;
        }
        if (!zox_valid(stat)) {
            continue;
        }
        zox_geter(stat, StatValue, statValue)
        int value = floor(statValue->value);
        zox_geter(stat, ZoxName, stat_name)
        convert_zext_to_text_non_malloc(stat_name->value, stat_name->length, stat_name_text, stat_name_text_count);
        char text[label_text_count];

        if (zox_has(stat, StatState)) {
            zox_geter(stat, StatValueMax, statValueMax)
            int max_value = ceil(statValueMax->value);
            snprintf(text, label_text_count, "%s [%i/%i]", stat_name_text, value, max_value);
        } else if (zox_has(stat, StatLevel)) {
            zox_geter(stat, ExperienceValue, experience)
            zox_geter(stat, ExperienceMax, experience_max)
            int experience_i = ceil(experience->value);
            int experience_max_i = ceil(experience_max->value);
            snprintf(text, label_text_count, "%s Lvl %i [%i/%i]", stat_name_text, value, experience_i, experience_max_i);
        } else {
            snprintf(text, label_text_count, "%s [%i]", stat_name_text, value);
        }


        if (!is_zext(textData, text)) {
            set_zext(textData, text);
            zextDirty->value = zext_update_start;
        }
    }
} zox_declare_system(StatTextSystem)