void StatTextSystem(ecs_iter_t *it) {
    zox_field_in(StatLink, statLinks, 1)
    zox_field_out(TextData, textDatas, 2)
    zox_field_out(ZextDirty, zextDirtys, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(StatLink, statLinks, statLink)
        if (!statLink->value || !zox_has(statLink->value, StatValue) || !zox_has(statLink->value, StatValueMax)) continue;
        zox_field_o(TextData, textDatas, textData)
        zox_field_o(ZextDirty, zextDirtys, zextDirty)
        const StatValue *statValue = zox_get(statLink->value, StatValue)
        const StatValueMax *statValueMax = zox_get(statLink->value, StatValueMax)
        char text[16];
        snprintf(text, 16, "health [%i/%i]", (int) (statValue->value),  (int) (statValueMax->value));
        if (!is_zext(textData, text)) {
            set_zext(textData, text);
            zextDirty->value = zext_update_start;
        }
    }
} zox_declare_system(StatTextSystem)
