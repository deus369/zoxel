ecs_entity_t prefab_label_background;

ecs_entity_t spawn_prefab_label_background(ecs_world_t *world) {
    zox_prefab_child(prefab_zext)
    zox_prefab_name("prefab_label_background")
    add_ui_plus_components(world, e);
    zox_add_tag(e, Label)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Color, {{ 35, 88, 66, 255 }})
    prefab_label_background = e;
    return e;
}

ecs_entity_t spawn_label_background(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t parent, const ecs_entity_t canvas, int2 pixel_position, const float2 anchor, const byte2 padding, const char* text, int font_size, unsigned char alignment, unsigned char layer, const int2 parent_pixel_position_global, const int2 parent_pixel_size) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int2 pixel_size = (int2) { font_size * sizeof(text) + padding.x * 2, font_size + padding.y * 2 };
    const float2 element_anchor = (float2) { 0.5f, anchor.y }; // because text rendering will reposition it, for now do this
    const float2 zext_anchor = anchor;
    anchor_element_position2D(&pixel_position, element_anchor, pixel_size);
    // const int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, element_anchor);
    // const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    const color label_font_outline_color = (color) { 76, 33, 33, 255 };
    const color label_font_fill_color = (color) { 132, 12, 12, 255 };
    ZextSpawnData zextSpawnData = {
        .canvas = { .e = canvas, .size = canvas_size },
        .parent = { .e = parent, .position = parent_pixel_position_global, .size = parent_pixel_size },
        .element = { .layer = layer, .position = pixel_position, .anchor = zext_anchor },
        .prefab = prefab,
        .text = text,
        .font_size = font_size,
        .alignment = alignment,
        .padding = padding,
        .font_fill_color = label_font_fill_color,
        .font_outline_color = label_font_outline_color,
    };
    const ecs_entity_t e = spawn_zext(world, &zextSpawnData);
    zox_name("label_background")
    return e;
}
