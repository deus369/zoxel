ecs_entity_t spawn_prefab_statbar2D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_statbar2D")
    zox_add_tag(e, Statbar)
    zox_prefab_set(e, StatLink, { 0 })
    return e;
}

ecs_entity_t spawn_statbar2D(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent, const ecs_entity_t player, const ecs_entity_2 character_group, int row) {
    const byte layer = 1;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const float2 anchor = float2_top_left;
    const int2 size = (int2) { 256, 32 };
    const byte2 padding = (byte2) { 16, 8 };
    const int2 position = (int2) { 8, 8 - size.y / 2 - (size.y + 8) * row };
    color back_color = back_bar_color;
    if (row == 1) back_color = (color) { back_bar_color.g, back_bar_color.r, back_bar_color.b, back_bar_color.a };
    else if (row == 2) back_color = (color) { back_bar_color.b, back_bar_color.g, back_bar_color.r, back_bar_color.a };
    color front_color = front_bar_color;
    if (row == 1) front_color = (color) { front_bar_color.g, front_bar_color.r, front_bar_color.b, front_bar_color.a };
    else if (row == 2) front_color = (color) { front_bar_color.b, front_bar_color.g, front_bar_color.r, front_bar_color.a };
    const ecs_entity_2 e2 = spawn_elementbar2D(world, prefab_statbar2D, player, canvas, parent, position, size, padding, anchor, layer, int2_half(canvas_size), canvas_size, canvas_size, 0, back_color, front_color);
    zox_set_unique_name(e2.x, "statbar2D")
    if (character_group.y) {
        zox_set(e2.x, StatLink, { character_group.y })
        zox_set(e2.y, StatLink, { character_group.y })
    }
    return e2.x;
}
