ecs_entity_t spawn_statbar2(
    ecs_world_t *world,
    const ecs_entity_t canvas,
    const ecs_entity_t parent,
    const ecs_entity_t player,
    const entity2 character_group,
    const color_rgb c,
    const byte layer,
    const float2 anchor,
    const int2 size,
    const int2 position
) {
    const ecs_entity_t stat = character_group.y;
    if (!zox_valid(stat)) {
        zox_log_error("stat null [spawn_statbar2]")
        return 0;
    }
    // const byte layer = 1;
    // const float2 anchor = float2_top_left;
    // const int2 size = (int2) { 300, 32 };
    const byte2 padding = (byte2) { 16, 8 };    // text?
    // const int2 position = (int2) { 8, 8 - size.y / 2 - (size.y + 8) * row };
    color back_color = (color) { c.r / 2, c.g / 2, c.b / 2, back_bar_color.a };
    color front_color = (color) { c.r, c.g, c.b, back_bar_color.a };

    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const entity2 e2 = spawn_elementbar2D(world,
        prefab_statbar2D,
        canvas,
        parent,
        position,
        size,
        padding,
        anchor,
        layer,
        int2_half(canvas_size),
        canvas_size,
        canvas_size,
        0,
        back_color,
        front_color);
    zox_set_unique_name(e2.x, "statbar2");
    zox_set_unique_name(e2.y, "statbar2_text");
    zox_set(e2.x, StatLink, { stat });
    zox_set(e2.y, StatLink, { stat });
    zox_add_tag(e2.y, StatsLabel);
    return e2.x;
}