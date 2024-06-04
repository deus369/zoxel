void tooltip_event_icon_skill(ecs_world_t *world, const TooltipEventData *data) {
    zox_log("SKILL SELECTED\n")
    if (data->event == zox_select_state_deselected_this_frame) {
        set_entity_with_text(world, data->tooltip, "");
    } else {
        set_entity_with_text(world, data->tooltip, "selected skill");
        /*char *result = malloc(64);
        const ZoxName *zox_name = zox_get(data->data, ZoxName)
        if (zox_name) {
            char *name_string = convert_zext_to_text(zox_name->value, zox_name->length);
            sprintf(result, "[%s] s\n", name_string);
            free(name_string);
        } else {
            sprintf(result, "[%lu] s\n", data->data);
        }
        set_entity_with_text(world, data->tooltip, result);
        free(result);*/
    }
}

ecs_entity_t spawn_prefab_icon_skill(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_skill")
    zox_prefab_set(e, TooltipEvent, { &tooltip_event_icon_skill })
    return e;
}
