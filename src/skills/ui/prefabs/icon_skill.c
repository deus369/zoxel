ecs_entity_t spawn_prefab_icon_skill(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_skill")
    zox_prefab_set(e, TooltipEvent, { &tooltip_event_icon_skill })
    zox_set(e, IconType, { zox_icon_type_skill })
    return e;
}