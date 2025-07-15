byte tooltip_event_skill(ecs_world_t *world, const TooltipEventData *data) {
    if (!data->data || !zox_has(data->data, Skill)) {
        return 0;
    }
    byte used_name = 0;
    char result[64];
    if (data->data && zox_has(data->data, ZoxName)) {
        const ZoxName *zox_name = zox_get(data->data, ZoxName)
        if (zox_name && zox_name->length > 0) {
            char *name_string = convert_zext_to_text(zox_name->value, zox_name->length);
            if (name_string != NULL) {
                used_name = 1;
                sprintf(result, "[%s] lvl [1]\n", name_string);
                free(name_string);
            }
        }
    }
    if (!used_name) {
        sprintf(result, "[%lu]\n", data->data);
    }
    set_entity_text(world, data->tooltip, result);
    // zox_log(" > tooltip icon skill set [%lu] selected at %f\n", data->tooltip, zox_current_time)
    return 1;
}

ecs_entity_t spawn_prefab_icon_skill(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("icon_skill")
    zox_prefab_set(e, TooltipEvent, { &tooltip_event_skill })
    zox_set(e, IconType, { zox_icon_type_skill })
    return e;
}