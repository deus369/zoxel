ecs_entity_t spawn_prefab_scrollbar(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_scrollbar")
    add_ui_plus_components(world, e);
    add_selectable_components(world, e);
    add_clickable_components(world, e);
    zox_add_tag(e, Scrollbar)
    zox_prefab_set(e, ElementMargins, { int2_zero })
    add_frame_texture_type(world, e, scrollbar_color, default_outline_color, default_button_corner, default_button_frame_thickness);
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_scrollbar(ecs_world_t *world, ecs_entity_t parent, ecs_entity_t canvas, int2 pixel_position, unsigned char layer, int2 parent_pixel_position_global, int2 parent_pixel_size, int width, int scrollbar_margins, int2 canvas_size, int elements_count, int max_elements) {
    unsigned char child_layer = layer + 1;
    float2 anchor = (float2) { 1.0f, 0.5f };
    int2 pixel_size = (int2) { width, parent_pixel_size.y };
    int2 margins = (int2) { scrollbar_margins, 0 };
    int height = (int) parent_pixel_size.y * ( float_min(1, (float) elements_count / (float) max_elements));
    if (elements_count == 0) height = parent_pixel_size.y;
    zox_instance(prefab_scrollbar)
    zox_name("scrollbar")
    zox_set(e, ElementMargins, { margins })
    int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    Children *children = zox_get_mut(e, Children)
    add_to_Children(children, spawn_scrollbar_front(world, e, canvas, int2_zero, float2_half, child_layer, width, height, pixel_position_global, pixel_size, canvas_size));
    zox_modified(e, Children)
    return e;
}
