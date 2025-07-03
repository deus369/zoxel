const double time_update_system_stat_text_rate = 0.5;
double time_update_system_stat_text = 0;

void StatTextSystem(ecs_iter_t *it) {
    time_update_system_stat_text += zox_delta_time;
    if (time_update_system_stat_text >= time_update_system_stat_text_rate) {
        time_update_system_stat_text = 0;
    } else {
        return;
    }
    int stat_name_text_count = 32;
    int label_text_count = 64;
    char stat_name_text[stat_name_text_count];
    zox_field_in(StatLink, statLinks, 1)
    zox_field_out(TextData, textDatas, 2)
    zox_field_out(ZextDirty, zextDirtys, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(StatLink, statLinks, statLink)
        const ecs_entity_t stat = statLink->value;
        if (!zox_valid(stat) || !zox_has(stat, StatValue) || !zox_has(stat, StatValueMax) || !zox_has(stat, ZoxName)) {
            continue;
        }
        zox_field_o(TextData, textDatas, textData)
        zox_field_o(ZextDirty, zextDirtys, zextDirty)
        const StatValue *statValue = zox_get(stat, StatValue)
        const StatValueMax *statValueMax = zox_get(stat, StatValueMax)
        const ZoxName *stat_name = zox_get(stat, ZoxName)
        convert_zext_to_text_non_malloc(stat_name->value, stat_name->length, stat_name_text, stat_name_text_count);
        char text[label_text_count];
        int max_value = ceil(statValueMax->value);
        int value = floor(statValue->value);
        snprintf(text, label_text_count, "%s [%i/%i]", stat_name_text, value, max_value);
        if (!is_zext(textData, text)) {
            set_zext(textData, text);
            zextDirty->value = zext_update_start;
        }
    }
} zox_declare_system(StatTextSystem)