ecs_entity_t spawn_prefab_scrollbar_front(ecs_world_t *world) {
    zox_prefab_child(prefab_element)
    zox_prefab_name("prefab_scrollbar_front")
    zox_add_tag(e, Scrollbar)
    add_selectable_components(world, e);
    add_clickable_components(world, e);
    add_draggable_components(world, e);
    zox_prefab_set(e, DraggableLimits, { int4_zero })
    zox_set(e, Color, { scrollbar_front_color })
    return e;
}

ecs_entity_t spawn_scrollbar_front(ecs_world_t *world, ecs_entity_t parent, ecs_entity_t canvas, int2 pixel_position, float2 anchor, unsigned char layer, int width, int height, int2 parent_pixel_position_global, int2 parent_pixel_size, int2 canvas_size) {
    int2 pixel_size = (int2) { width, height };
    zox_instance(prefab_scrollbar_front)
    zox_name("scrollbar_front")
    zox_add_tag(e, ScrollbarButton)
    const int bounds_y = (parent_pixel_size.y / 2) - height / 2;
    zox_set(e, DraggableLimits, { (int4) { 0, 0, -bounds_y, bounds_y } })
    int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    return e;
}
