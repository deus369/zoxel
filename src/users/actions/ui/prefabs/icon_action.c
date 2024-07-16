void tooltip_event_icon_action(ecs_world_t *world, const TooltipEventData *data) {
    if (zox_has(data->data, Item)) {
        // zox_log(" > item highlighted\n")
        tooltip_event_icon_item(world, data);
    } else if (zox_has(data->data, Skill)) {
        // zox_log(" > skill highlighted\n")
        tooltip_event_icon_skill(world, data);
    } else {
        zox_log(" ! uknown action highlighted\n")
    }
}

unsigned char process_icon_type_action(ecs_world_t *world, const ecs_entity_t data) {
    if (zox_has(data, Item)) {
        return zox_icon_type_item;
    } else if (zox_has(data, Skill)) {
        return zox_icon_type_skill;
    } else {
        return 0;
    }
}

// clicked event?

ecs_entity_t spawn_prefab_icon_action(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_action")
    zox_set(e, TooltipEvent, { &tooltip_event_icon_action })
    zox_set(e, IconType, { zox_icon_type_action })
    return e;
}
