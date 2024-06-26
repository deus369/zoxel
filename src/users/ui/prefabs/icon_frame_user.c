ecs_entity_t spawn_prefab_icon_frame_user(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_frame_user")
    zox_add_tag(e, UserIconFrame)
    zox_prefab_add(e, UserDataLink)
    zox_prefab_add(e, TooltipEvent)
    return e;
}

ecs_entity_2 spawn_icon_frame_user(ecs_world_t *world, SpawnIconFrame *data, const ecs_entity_t user_data) {
    const ecs_entity_2 e = spawn_icon_frame(world, data);
    const ecs_entity_t icon_frame = e.x;
    const ecs_entity_t icon = e.y;
    zox_set(icon_frame, UserDataLink, { user_data })
    zox_set(icon, UserDataLink, { user_data })
    if (user_data && zox_has(user_data, TextureLink)) {
        zox_set(icon, GenerateTexture, { zox_generate_texture_none })
        // zox_remove(icon, GenerateTexture)
        const ecs_entity_t texture = zox_get_value(user_data, TextureLink)
        clone_texture_data(world, icon, texture);
        zox_set(icon, TextureDirty, { 1 })
        zox_set(icon, Color,  { color_white })
    }
    return e;
}
