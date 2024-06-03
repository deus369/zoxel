ecs_entity_t spawn_prefab_label_background(ecs_world_t *world) {
    zox_prefab_child(prefab_zext)
    zox_prefab_name("prefab_label_background")
    add_ui_plus_components(world, e);
    zox_add_tag(e, Label)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Color, {{ 35, 88, 66, 255 }})
    return e;
}

ecs_entity_t spawn_label_background(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t parent, const ecs_entity_t canvas, int2 pixel_position, const float2 anchor, const byte2 padding, const char* text, const unsigned char font_size, const unsigned char alignment, const unsigned char layer, const int2 parent_position, const int2 parent_size, const color label_font_outline_color, const color label_font_fill_color, const unsigned char render_disabled) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    SpawnZext zextSpawnData = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
        .parent = {
            .e = parent,
            .position = parent_position,
            .size = parent_size
        },
        .element = {
            .layer = layer,
            .anchor = anchor,
            .position = pixel_position,
            .render_disabled = render_disabled,
        },
        .zext = {
            .prefab = prefab,
            .text = text,
            .font_size = font_size,
            .font_thickness = 1,
            .alignment = alignment,
            .padding = padding,
            .font_fill_color = label_font_fill_color,
            .font_outline_color = label_font_outline_color
        }
    };
    const ecs_entity_t e = spawn_zext(world, &zextSpawnData);
    zox_name("label_background")
    return e;
}
