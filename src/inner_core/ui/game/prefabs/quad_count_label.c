ecs_entity_t prefab_quad_count_label;
ecs_entity_t quads_label;

ecs_entity_t spawn_prefab_quad_count_label(ecs_world_t *world) {
    ecs_entity_t e = ecs_clone(world, 0, label_background_prefab, 1);
    // ecs_set_name(world, e, "prefab_fps_display"); // bugged atm
    zox_add_tag(e, QuadsCountLabel)
    zox_set(e, QuadsCount, { 0 })
    if (!headless) prefab_set_mesh2D_vertices(world, e, square_vertices_right_aligned, 4);
    prefab_quad_count_label = e;
    return e;
}

ecs_entity_t spawn_quad_count_label(ecs_world_t *world, ecs_entity_t parent) {
    unsigned char font_size = 24;
    byte2 padding = (byte2) { 12, 8 };
    int edge_line_thickness = canvas_edge_size * 2 + 2; // this is real size.. convert to pixel size?
    float2 anchor = { 1.0f, 0.0f };
    int2 position = { -edge_line_thickness / 3, (font_size / 2) + edge_line_thickness }; // - 4 * (pixel_size.x / 2), font_size / 2 };
    int layer = 1;
    const PixelSize *parent_pixel_size = ecs_get(world, parent, PixelSize);
    ecs_entity_t e = spawn_label_background(world, prefab_quad_count_label, parent, position, anchor, padding, "", font_size,
        zox_mesh_alignment_right, layer, float2_zero, parent_pixel_size->value);
    quads_label = e;
    return e;
}