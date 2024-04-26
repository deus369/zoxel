ecs_entity_t fps_display_prefab;
ecs_entity_t fps_display;

ecs_entity_t spawn_prefab_fps_display(ecs_world_t *world) {
    // ecs_entity_t e = ecs_new_entity(world, "prefab_fps_display");
    const ecs_entity_t e = ecs_clone(world, 0, prefab_label_background, 1);
    zox_prefab_name("prefab_fps_display")
    zox_add_tag(e, FPSDisplay)
    zox_prefab_set(e, FPSDisplayTicker, { 0 })
    // if (!headless) prefab_set_mesh2D_vertices(world, e, square_vertices_right_aligned, 4);
    fps_display_prefab = e;
    return e;
}

ecs_entity_t spawn_fps_display(ecs_world_t *world, const ecs_entity_t canvas) {
    const unsigned char layer = 1;
    const unsigned char font_size = 32;
    const byte2 padding = (byte2) { 12, 8 };
    const float2 anchor = { 1.0f, 1.0f };
    const int2 pixel_position = int2_zero;
    const int2 parent_pixel_size = zox_get_value(canvas, PixelSize)
    return spawn_label_background(world, fps_display_prefab, canvas, canvas, pixel_position, anchor, padding, "", font_size, zox_mesh_alignment_right, layer, int2_half(parent_pixel_size), parent_pixel_size); // "FPS"
}
