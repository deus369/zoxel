ecs_entity_t local_crosshair = 0;

ecs_entity_t spawn_crosshair(ecs_world_t *world, const ecs_entity_t canvas, const  ecs_entity_t parent) {
    unsigned char layer = 1;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t e = spawn_element_basic(world, canvas, parent, int2_zero, crosshair_pixel_size, crosshair_texture_size, float2_half, layer, int2_half(canvas_size), canvas_size);
    zox_add_tag(e, FrameTexture)
    zox_set(e, FrameCorner, { 14 })
    zox_set(e, OutlineThickness, { 12 })
    zox_set(e, Color, { empty_color })
    zox_set(e, OutlineColor, { crosshair_color })
    zox_set(e, GenerateTexture, { 1 })
    zox_set(e, Seed, { 666 })
    // zox_log(" > crosshair [%lu]\n", crosshair_ui)
    local_crosshair = e;
    return e;
}
