ecs_entity_t spawn_prefab_quad_count_label(ecs_world_t *world) {
    // const ecs_entity_t e = ecs_clone(world, 0, prefab_label_background, 1);
    zox_prefab_child(prefab_label_background)
    zox_add_tag(e, QuadsCountLabel)
    zox_prefab_set(e, QuadsCount, { -1 })
    prefab_set_mesh2D_vertices(world, e, square_vertices_right_aligned, 4);
    prefab_quad_count_label = e;
    return e;
}

ecs_entity_t spawn_quad_count_label(ecs_world_t *world, const ecs_entity_t canvas) {
    const ecs_entity_t parent = canvas;
    const unsigned char font_size = 24;
    const byte2 padding = (byte2) { 12, 8 };
    const float2 anchor = { 1, 0 };
    const int2 pixel_position = (int2) { -8, 8 };
    const int layer = 1;
    const int2 parent_pixel_size = zox_get_value(parent, PixelSize)
    const ecs_entity_t e = spawn_label_background(world, prefab_quad_count_label, parent, canvas, pixel_position, anchor, padding, "", font_size, zox_mesh_alignment_bottom_right, layer, int2_half(parent_pixel_size), parent_pixel_size, default_label_font_outline_color, default_label_font_fill_color, 0);
    return e;
}
