void tooltip_event_icon_skill(ecs_world_t *world, const TooltipEventData *data) {
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
        sprintf(result, "[%" PRIu64 "]\n", data->data);
    }
    set_entity_text(world, data->tooltip, result);
    // zox_log(" > tooltip icon skill set [%lu] selected at %f\n", data->tooltip, zox_current_time)
}