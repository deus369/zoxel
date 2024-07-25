ecs_entity_t icon_mouse_follow;

ecs_entity_t spawn_prefab_icon_mouse_follow(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_add_tag(e, Icon)
    zox_add_tag(e, IconTexture)  // general one
    zox_prefab_set(e, IconType, { 0 })
    // zox_prefab_set(e, ParentLink, { 0 })
    add_mouse_follow_components(world, e);
    zox_set(e, IconRadius, { default_icon_radius })
    zox_set(e, RenderDisabled, { 1 })
    return e;
}

ecs_entity_t spawn_icon_mouse_follow(ecs_world_t *world, SpawnIcon *data) {
    const ecs_entity_t e = spawn_icon(world, data);
    icon_mouse_follow = e;
    return e;
}

ecs_entity_t spawn_icon_mouse_follow_canvas(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const int2 canvas_size, const unsigned char layer, const float2 anchor, const float icon_size) {
    SpawnIcon spawnIcon = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
        .parent = {
            .e = canvas,
            .position = int2_half(canvas_size),
            .size = canvas_size
        },
        .element = {
            .prefab = prefab,
            .size = int2_single(icon_size),
            .anchor = anchor,
            .layer = layer,
        },
        .texture = {
            .fill_color = default_fill_color_icon,
            .outline_color = default_outline_color_icon
        }
    };
    const ecs_entity_t e = spawn_icon(world, &spawnIcon);

    zox_geter(mouse_entity, Children, zevices)
    zox_set(e, ZeviceLink, { zevices->value[0] })

    icon_mouse_follow = e;
    return e;
}
