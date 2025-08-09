int2 get_element_label_position(int index, const byte font_size, const byte2 button_padding, const int button_inner_margins, const int2 window_size, const int2 list_margins, const byte is_scrollbar, const int scrollbar_width, const int scrollbar_margins) {
    int2 label_position = (int2) { 0, (int) (window_size.y / 2) - (index + 0.5f) * (font_size + button_padding.y * 2) - list_margins.y - index * button_inner_margins };
    if (is_scrollbar) label_position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;
    return label_position;
}


void resize_window_scrollbar(ecs_world_t *world, Children *children, const int2 window_size, const int2 canvas_size, const int elements_visible, const int labels_count) {
    const ecs_entity_t scrollbar = children->value[1];
    const ecs_entity_t scrollbar_front = zox_gett_value(scrollbar, Children)[0];
    const int scrollbar_height = (int) window_size.y * ( float_min(1, (float) elements_visible / (float) labels_count));
    const int2 scrollbar_size = (int2) { zox_gett_value(scrollbar, PixelSize).x, scrollbar_height };
    zox_set(scrollbar_front, PixelSize, { scrollbar_size })
    zox_set(scrollbar_front, TextureSize, { scrollbar_size })
    const int bounds_y = (window_size.y / 2) - scrollbar_height / 2;
    zox_set(scrollbar_front, DraggableLimits, { (int4) { 0, 0, -bounds_y, bounds_y } })
    zox_set(scrollbar_front, PixelPosition, { (int2) { 0, (window_size.y - scrollbar_height) / 2 } })
    on_resized_element(world, scrollbar_front, scrollbar_size, int2_to_float2(canvas_size));
}

ecs_entity_t spawn_button_old(ecs_world_t *world,
    const ecs_entity_t parent,
    const ecs_entity_t canvas,
    const int2 pixel_position,
    const byte2 padding,
    const float2 anchor,
    const char* text,
    const int font_size,
    const byte layer,
    const int2 parent_pixel_position_global,
    const int2 parent_pixel_size,
    const int2 canvas_size,
    const byte render_disabled)
{
    const int2 zext_size = (int2) { font_size * strlen(text), font_size };
    const int2 pixel_size = (int2) { zext_size.x + padding.x * 2, zext_size.y + padding.y * 2 };
    const int2 global_position = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    const float2 position2D = get_element_position(global_position, canvas_size);
    zox_instance(prefab_button)
    zox_name("button")
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, global_position);
    zox_set(e, Color, { button_fill })
    zox_set(e, OutlineColor, { button_outline })
    zox_set(e, RenderDisabled, { render_disabled })
    Children children = (Children) { 0 };
    SpawnZext spawnZext = {
        .canvas = {
            .e = canvas,
            .size = canvas_size },
        .parent = {
            .e = e,
            .position = global_position,
            .size = pixel_size },
        .element = {
            .prefab = prefab_zext,
            .layer = layer + 1,
            .anchor = float2_half,
            .size = zext_size,
            .render_disabled = render_disabled, },
        .zext = {
            .text = text,
            .font_size = font_size,
            .font_thickness = 1,
            .padding = padding,
            .font_fill_color = default_font_fill_color,
            .font_outline_color = default_font_outline_color } };
    const ecs_entity_t zext = spawn_zext(world, &spawnZext);
    add_to_Children(&children, zext);
    zox_set_ptr(e, Children, children)
    return e;
}