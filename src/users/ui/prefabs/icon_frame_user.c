ecs_entity_t spawn_prefab_icon_frame_user(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_icon_frame_user")
    zox_add_tag(e, UserIconFrame)
    zox_prefab_add(e, UserDataLink)
    zox_prefab_add(e, TooltipEvent)
    return e;
}

void set_icon_from_user_data(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t data) {
    zox_set(e, UserDataLink, { data })
    if (!data) {
        clear_texture_data(world, e);
        zox_set(e, GenerateTexture, { zox_generate_texture_trigger })
        zox_set(e, TextureSize, { int2_single(default_icon_texture_size) })
        return;
    }
    if (!zox_has(data, TextureLink)) {
        zox_log(" ! issue with data texture [%s] ? %i\n", zox_get_name(data), zox_has(data, TextureLink))
        return;
    }
    const ecs_entity_t texture = zox_get_value(data, TextureLink)
    if (!texture) {
        zox_log(" ! texture is invalid from [%s]\n", zox_get_name(data))
        return;
    }
    zox_set(e, GenerateTexture, { zox_generate_texture_none })
    clone_texture_data(world, e, texture);
    zox_set(e, TextureDirty, { 1 })
}

ecs_entity_2 spawn_icon_frame_user(ecs_world_t *world, SpawnIconFrame *data, const ecs_entity_t user_data) {
    const ecs_entity_2 e = spawn_icon_frame(world, data);
    const ecs_entity_t icon = e.y;
    set_icon_from_user_data(world, icon, user_data);
    return e;
}
