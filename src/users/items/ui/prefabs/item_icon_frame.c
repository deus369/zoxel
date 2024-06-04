
/*ecs_entity_t spawn_prefab_icon_frame_item(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_frame_item")
    zox_add_tag(e, ItemIconFrame)
    // zox_prefab_add(e, ItemLink)
    zox_prefab_set(e, TooltipEvent, { &tooltip_event_icon_frame_item })
    return e;
}*/

// todo: spawn_icon_frame_user - reuse this for all user data
/*ecs_entity_2 spawn_icon_frame_item(ecs_world_t *world, SpawnIconFrame *data, const ecs_entity_t user_data) {
    const ecs_entity_2 e = spawn_icon_frame(world, data);
    zox_set(e.x, ItemLink, { item })
    zox_set(e.x, UserDataLink, { item })
    // zox_add_tag(e.y, ItemIconFrame)
    zox_set(e.y, UserDataLink, { item })
    if (item) {
        zox_set(e.y, GenerateTexture, { zox_generate_texture_none })
        // zox_remove(e.y, GenerateTexture)
        const ecs_entity_t texture = zox_get_value(item, TextureLink)
        clone_texture_data(world, e.y, texture);
        zox_set(e.y, TextureDirty, { 1 })
    }
    return e;
}*/
