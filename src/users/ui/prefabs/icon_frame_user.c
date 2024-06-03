ecs_entity_t spawn_prefab_icon_frame_user(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_frame_user")
    zox_add_tag(e, UserIconFrame)
    zox_prefab_add(e, UserDataLink)
    return e;
}

ecs_entity_2 spawn_icon_frame_user(ecs_world_t *world, SpawnIconFrame *data, const ecs_entity_t user_data) {
    const ecs_entity_2 e = spawn_icon_frame(world, data);
    zox_set(e.x, UserDataLink, { user_data })
    zox_set(e.y, UserDataLink, { user_data })
    if (user_data && zox_has(user_data, TextureLink)) {
        zox_set(e.y, GenerateTexture, { zox_generate_texture_none })
        // zox_remove(e.y, GenerateTexture)
        const ecs_entity_t texture = zox_get_value(user_data, TextureLink)
        clone_texture_data(world, e.y, texture);
        zox_set(e.y, TextureDirty, { 1 })
    }
    return e;
}
