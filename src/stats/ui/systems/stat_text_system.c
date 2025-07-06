void StatTextSystem(ecs_iter_t *it) {
    int stat_name_text_count = 32;
    int label_text_count = 64;
    char stat_name_text[stat_name_text_count];
    zox_field_world()
    zox_field_in(StatLink, statLinks, 1)
    zox_field_out(TextData, textDatas, 2)
    zox_field_out(ZextDirty, zextDirtys, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(StatLink, statLinks, statLink)
        const ecs_entity_t stat = statLink->value;
        if (!zox_valid(stat) || !zox_has(stat, StatValue) || !zox_has(stat, StatValueMax) || !zox_has(stat, ZoxName)) {
            zox_field_e()
            zox_log_error("[%s] has invalid stat linked", zox_get_name(e))
            continue;
        }
        zox_field_o(TextData, textDatas, textData)
        zox_field_o(ZextDirty, zextDirtys, zextDirty)
        zox_geter(stat, StatValue, statValue)
        zox_geter(stat, StatValueMax, statValueMax)
        zox_geter(stat, ZoxName, stat_name)
        convert_zext_to_text_non_malloc(stat_name->value, stat_name->length, stat_name_text, stat_name_text_count);
        char text[label_text_count];
        int max_value = ceil(statValueMax->value);
        int value = floor(statValue->value);
        snprintf(text, label_text_count, "%s [%i/%i]", stat_name_text, value, max_value);
        if (!is_zext(textData, text)) {
            set_zext(textData, text);
            zextDirty->value = zext_update_start;
            // zox_field_e()
            // zox_log("+ updated stat text %s", zox_get_name(e))
        }
    }
} zox_declare_system(StatTextSystem)