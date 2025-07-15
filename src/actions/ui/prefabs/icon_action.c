byte tooltip_event_action(ecs_world_t *world, const TooltipEventData *data) {
    if (zox_has(data->data, Item)) {
        return tooltip_event_item(world, data);
    } else if (zox_has(data->data, Skill)) {
        return tooltip_event_skill(world, data);
    } else {
        if (data->data) {
            zox_log(" ! uknown action highlighted [%s]", zox_get_name(data->data))
            set_entity_text(world, data->tooltip, "unknown one");
            return 1;
        }
        return 0;
    }
}

byte process_icon_type_action(ecs_world_t *world, const ecs_entity_t data) {
    if (zox_has(data, Item)) {
        return zox_icon_type_item;
    } else if (zox_has(data, Skill)) {
        return zox_icon_type_skill;
    } else {
        return 0;
    }
}

ecs_entity_t spawn_prefab_icon_action(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("icon_action")
    zox_set(e, TooltipEvent, { &tooltip_event_action })
    zox_set(e, IconType, { zox_icon_type_action })
    return e;
}