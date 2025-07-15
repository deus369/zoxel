ecs_entity_t spawn_icon_mouse_follow(ecs_world_t *world, SpawnIcon *data) {
    const ecs_entity_t e = spawn_icon(world, data);
    icon_mouse_follow = e;
    return e;
}

ecs_entity_t spawn_icon_mouse_follow_canvas(ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t canvas,
    const int2 canvas_size,
    const byte layer,
    const float2 anchor,
    const float icon_size,
    const ecs_entity_t zevice)
{
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
    if (zevice) {
        zox_set(e, ZeviceLink, { zevice })
    }
    return e;
}