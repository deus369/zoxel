ecs_entity_t spawn_crosshair(ecs_world_t *world, const ecs_entity_t canvas, const  ecs_entity_t parent) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t crosshair_ui = spawn_element_basic(world, canvas, parent, int2_zero, crosshair_pixel_size, crosshair_texture_size, float2_half, 1, int2_half(canvas_size), canvas_size);
    zox_add_tag(crosshair_ui, FrameTexture)
    zox_set(crosshair_ui, FrameCorner, { 14 })
    zox_set(crosshair_ui, OutlineThickness, { 12 })
    zox_set(crosshair_ui, Color, { empty_color })
    zox_set(crosshair_ui, OutlineColor, { crosshair_color })
    zox_set(crosshair_ui, GenerateTexture, { 1 })
    zox_set(crosshair_ui, Seed, { 666 })
    // zox_log(" > crosshair [%lu]\n", crosshair_ui)
    return crosshair_ui;
}
