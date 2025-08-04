byte tooltip_event_stat(ecs_world_t *world, const TooltipEventData *data) {
    if (!data->data || !zox_has(data->data, Stat)) {
        if (data->data) {
            zox_log("e [%s] has no Stat", zox_get_name(data->data));
        }
        return 0;
    }
    char result[64];
    char *name_string = NULL;
    const ZoxName *zox_name = zox_get(data->data, ZoxName)
    if (zox_name) {
        name_string = convert_zext_to_text(zox_name->value, zox_name->length);
    } else {
        name_string = "none";
        //sprintf(result, "[%lu] lvl 1\n", data->data);
    }
    if (zox_has(data->data, StatLevel)) {
        const float value = zox_get_value(data->data, StatValue)
        const float experience = zox_get_value(data->data, ExperienceValue)
        const float experience_max = zox_get_value(data->data, ExperienceMax)
        sprintf(result, "[%s] lvl %i [%i/%i]\n", name_string, (int) value, (int) experience, (int) experience_max);
    } else if (zox_has(data->data, StatState)) {
        const float value = zox_get_value(data->data, StatValue)
        const float value_max = zox_get_value(data->data, StatValueMax)
        sprintf(result, "[%s] [%i/%i]\n", name_string, (int) value, (int) value_max);
    } else if (zox_has(data->data, StatRegen)) {
        const float value = zox_get_value(data->data, StatValue)
        sprintf(result, "[%s] [%i]\n", name_string, (int) value);
    } else if (zox_has(data->data, StatAttribute)) {
        const float value = zox_get_value(data->data, StatValue)
        sprintf(result, "[%s] [%i]\n", name_string, (int) value);
    } else {
        sprintf(result, "[%s]\n", name_string);
    }
    set_entity_text(world, data->tooltip, result);
    if (name_string) {
        free(name_string);
    }
    zox_set(data->tooltip, RenderDisabled, { 0 })
    return 1;
}

ecs_entity_t spawn_prefab_icon_stat(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("icon_stat")
    zox_prefab_set(e, TooltipEvent, { &tooltip_event_stat })
    return e;
}
