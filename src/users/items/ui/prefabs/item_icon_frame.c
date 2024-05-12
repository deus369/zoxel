ecs_entity_t spawn_prefab_icon_frame_item(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_frame_item")
    zox_add_tag(e, ItemIconFrame)
    return e;
}
