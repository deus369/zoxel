ecs_entity_t spawn_prefab_elementbar2D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_elementbar2D")
    add_ui_plus_components(world, e);
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, Color, { back_bar_color })
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    zox_prefab_set(e, ElementBar, { 1 })
    zox_prefab_set(e, ElementBarSize, { float2_zero })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_elementbar2D(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t ui_holder, const ecs_entity_t canvas, const ecs_entity_t parent, int2 pixel_position, const int2 pixel_size, const byte2 zext_padding, const float2 anchor, const unsigned char layer, const int2 parent_pixel_position_global, const int2 parent_pixel_size, const int2 canvas_size, const unsigned char render_disabled) {
    const unsigned char front_bar_layer = layer + 1;
    const unsigned char zext_layer = layer + 2;
    // const color label_font_outline_color = (color) { 125, 255, 255, 255 };
    const color label_font_outline_color = (color) { 33, 33, 33, 255 };
    const color label_font_fill_color = (color) { 0, 255, 255, 255 };
    // this fits our font_size to our given pixel_size
    // todo: perhaps make this a system / propoprety so it resizes font_size based on text updates
    const unsigned char text_length = 11; // health [100] - 11 characters
    unsigned char font_size = pixel_size.y - zext_padding.y * 2;
    const int zext_width = pixel_size.x - zext_padding.x * 2;
    const unsigned char font_size_width = zext_width /text_length;
    if (font_size > font_size_width) font_size = font_size_width;
    const int2 zext_size = (int2) { zext_width , font_size };
    anchor_element_position2D(&pixel_position, anchor, pixel_size);
    const int2 position_in_canvas = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    const float2 position2D = get_element_position(position_in_canvas, canvas_size);
    zox_instance(prefab)
    zox_name("elementbar2D")
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, int2_one, anchor, layer, position2D, position_in_canvas);
    if (render_disabled) zox_set(e, RenderDisabled, { render_disabled })
    const unsigned char frontbar_padding = 6;
    zox_set(e, ElementBarSize, { (float2) { (pixel_size.x - frontbar_padding * 2) / (float) pixel_size.x, 1 } })
    // zox_set(e, Color, { back_bar_color })
    const ecs_entity_t front_bar = spawn_elementbar2D_front(world, canvas, e, position_in_canvas, pixel_size, canvas_size, front_bar_layer, render_disabled);
    SpawnZext zextSpawnData = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
        .parent = {
            .e = e,
            .position = position_in_canvas,
            .size = pixel_size
        },
        .element = {
            .prefab = prefab_zext,
            .layer = zext_layer,
            .anchor = float2_half,
            .render_disabled = render_disabled,
            .size = zext_size
        },
        .zext = {
            .font_size = font_size,
            .font_thickness = 3,
            .font_fill_color = label_font_fill_color,
            .font_outline_color = label_font_outline_color
        }
    };
    const ecs_entity_t zext = spawn_zext(world, &zextSpawnData);
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, 2)
    children->value[0] = front_bar;
    children->value[1] = zext;
    zox_modified(e, Children)
    return e;
}
