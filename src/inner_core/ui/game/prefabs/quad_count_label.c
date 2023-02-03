ecs_entity_t prefab_quad_count_label;
ecs_entity_t quads_label;

ecs_entity_t spawn_prefab_quad_count_label(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_clone(world, 0, label_prefab, 1);
    // ecs_set_name(world, e, "prefab_fps_display"); // bugged atm
    zoxel_add_tag(world, e, QuadsCountLabel);
    ecs_defer_end(world);
    prefab_quad_count_label = e;
    return e;
}

ecs_entity_t spawn_quad_count_label(ecs_world_t *world, ecs_entity_t parent, int font_size)
{
    int textLength = 3;
    int2 pixel_size = (int2) { font_size * textLength, font_size };
    float2 anchor = { 0.0f, 1.0f };
    int2 position = { 6 * (pixel_size.x / 2), - font_size / 2 };
    int layer = 1;
    const PixelSize *parent_pixel_size = ecs_get(world, parent, PixelSize);
    ecs_entity_t e = spawn_label(world, prefab_quad_count_label, parent, position, anchor, "", font_size, layer,
        (float2) { }, parent_pixel_size->value);
    quads_label = e;
    return e;
}