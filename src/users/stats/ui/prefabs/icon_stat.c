void tooltip_event_icon_stat(ecs_world_t *world, const TooltipEventData *data) {
    if (data->event == zox_select_state_deselected_this_frame) {
        set_entity_with_text(world, data->tooltip, "");
        zox_set(data->tooltip, RenderDisabled, { 1 })
    } else {
        char *result = malloc(64);
        const ZoxName *zox_name = zox_get(data->data, ZoxName)
        if (zox_name) {
            char *name_string = convert_zext_to_text(zox_name->value, zox_name->length);
            sprintf(result, "[%s] lvl 1\n", name_string);
            free(name_string);
        } else {
            sprintf(result, "[%lu] lvl 1\n", data->data);
        }
        set_entity_with_text(world, data->tooltip, result);
        free(result);
        zox_set(data->tooltip, RenderDisabled, { 0 })
    }
}

ecs_entity_t spawn_prefab_icon_stat(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_stat")
    zox_prefab_set(e, TooltipEvent, { &tooltip_event_icon_stat })
    return e;
}
