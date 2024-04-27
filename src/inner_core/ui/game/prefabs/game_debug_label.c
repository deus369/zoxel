ecs_entity_t prefab_game_debug_label;

ecs_entity_t spawn_prefab_game_debug_label(ecs_world_t *world) {
    zox_prefab_child(prefab_label_background)
    zox_add_tag(e, GameDebugLabel)
    // zox_prefab_set(e, QuadsCount, { 0 })
    if (!headless) prefab_set_mesh2D_vertices(world, e, square_vertices_right_aligned, 4);
    prefab_game_debug_label = e;
    return e;
}

ecs_entity_t spawn_game_debug_label(ecs_world_t *world, const ecs_entity_t canvas) {
    const ecs_entity_t parent = canvas;
    const int layer = 1;
    const unsigned char font_size = 24;
    const byte2 padding = (byte2) { 12, 8 };
    const float2 anchor = { 1.0f, 0.0f };
    const int2 pixel_position = int2_zero;
    const int2 parent_pixel_size = zox_get_value(parent, PixelSize)
    const ecs_entity_t e = spawn_label_background(world, prefab_game_debug_label, parent, canvas, pixel_position, anchor, padding, "", font_size, zox_mesh_alignment_right, layer, int2_half(parent_pixel_size), parent_pixel_size);
    return e;
}
