ecs_entity_t spawn_prefab_fps_display(ecs_world_t *world) {
    zox_prefab_child(prefab_label_background)
    zox_prefab_name("prefab_fps_display")
    zox_add_tag(e, FPSDisplay)
    zox_prefab_set(e, FPSDisplayTicker, { 0 })
    zox_prefab_set(e, FontOutlineColor, {{ 200, 80, 80, 255 }})
    zox_prefab_set(e, FontFillColor, {{ 244, 33, 33, 255 }})
    fps_display_prefab = e;
    return e;
}

ecs_entity_t spawn_fps_display(ecs_world_t *world, const ecs_entity_t canvas) {
    const ecs_entity_t parent = canvas;
    const unsigned char layer = 1;
    const unsigned char font_size = 32;
    const byte2 padding = (byte2) { 12, 8 };
    const float2 anchor = { 1.0f, 1.0f };
    const int2 pixel_position = (int2) { -16, -16 };
    const int2 parent_pixel_size = zox_get_value(canvas, PixelSize)
    return spawn_label_background(world, fps_display_prefab, parent, canvas, pixel_position, anchor, padding, "", font_size, zox_mesh_alignment_top_right, layer, int2_half(parent_pixel_size), parent_pixel_size, default_label_font_outline_color, default_label_font_fill_color); // "FPS"
}
