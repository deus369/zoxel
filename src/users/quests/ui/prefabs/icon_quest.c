void tooltip_event_icon_quest(ecs_world_t *world, const TooltipEventData *data) {
    if (data->event == zox_select_state_deselected_this_frame) {
        set_entity_with_text(world, data->tooltip, "");
    } else {
        // set_entity_with_text(world, data->tooltip, "selected skill");
        unsigned char used_name = 0;
        char result[64]; // char *result = malloc(64);
        if (data->data && zox_has(data->data, ZoxName)) {
            const ZoxName *zox_name = zox_get(data->data, ZoxName)
            if (zox_name && zox_name->length > 0) {
                char *name_string = convert_zext_to_text(zox_name->value, zox_name->length);
                if (name_string != NULL) {
                    used_name = 1;
                    sprintf(result, "quest [%s]\n", name_string);
                    free(name_string);
                }
            }
        }
        if (!used_name) {
            sprintf(result, "[%lu] q\n", data->data);
        }
        set_entity_with_text(world, data->tooltip, result);
        // free(result);
    }
}

ecs_entity_t spawn_prefab_icon_quest(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_quest")
    zox_prefab_set(e, TooltipEvent, { &tooltip_event_icon_quest })
    return e;
}
