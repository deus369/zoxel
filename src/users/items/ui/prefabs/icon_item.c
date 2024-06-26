void tooltip_event_icon_item(ecs_world_t *world, const TooltipEventData *data) {
    /*if (data->event == zox_select_state_deselected_this_frame) {
        set_entity_with_text(world, data->tooltip, "");
        // zox_set(data->tooltip, RenderDisabled, { 1 })
    } else*/ {
        char result[64]; // char *result = malloc(64);
        const ZoxName *zox_name = zox_get(data->data, ZoxName)
        if (zox_name && zox_name->value && zox_name->length) {
            char *name_string = convert_zext_to_text(zox_name->value, zox_name->length);
            sprintf(result, "[%s] x1\n", name_string);
            free(name_string);
        } else {
            sprintf(result, "[%" PRIu64 "]\n", data->data);
        }
        set_entity_with_text(world, data->tooltip, result);
        // free(result);
    }
}

ecs_entity_t spawn_prefab_icon_item(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_item")
    zox_set(e, TooltipEvent, { &tooltip_event_icon_item })
    zox_set(e, IconType, { zox_icon_type_item })
    return e;
}
