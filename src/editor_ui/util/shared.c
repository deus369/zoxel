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
