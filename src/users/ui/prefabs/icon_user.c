ecs_entity_t spawn_prefab_icon_user(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_user")
    zox_add_tag(e, UserIcon)
    zox_prefab_set(e, UserDataLink, { 0 })
    zox_prefab_add(e, TooltipEvent)
    return e;
}