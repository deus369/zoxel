ecs_entity_t spawn_prefab_icon_frame_item(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_frame_item")
    zox_add_tag(e, ItemIconFrame)
    zox_prefab_add(e, ItemLink)
    return e;
}

ecs_entity_t spawn_icon_frame_item(ecs_world_t *world, SpawnIconFrame *data, const ecs_entity_t item) {
    const ecs_entity_t e = spawn_icon_frame(world, data);
    zox_set(e, ItemLink, { item })
    return e;
}
