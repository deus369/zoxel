ecs_entity_t spawn_prefab_icon_frame_item(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_frame_item")
    zox_add_tag(e, UserIconFrame)
    zox_add_tag(e, ItemIconFrame)
    zox_prefab_add(e, ItemLink)
    zox_prefab_add(e, UserDataLink)
    return e;
}

ecs_entity_2 spawn_icon_frame_item(ecs_world_t *world, SpawnIconFrame *data, const ecs_entity_t item) {
    const ecs_entity_2 e = spawn_icon_frame(world, data);
    zox_set(e.x, ItemLink, { item })
    zox_set(e.x, UserDataLink, { item })
    // zox_add_tag(e.y, ItemIconFrame)
    zox_set(e.y, UserDataLink, { item })
    return e;
}
