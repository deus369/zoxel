entity spawn_scrollbar_front(ecs *world,
    const entity parent,
    const entity canvas,
    const int2 pixel_position,
    const float2 anchor,
    const byte layer,
    const int width,
    const int height,
    const int2 parent_position,
    const int2 parent_size,
    const int2 canvas_size)
{
    const int2 pixel_size = (int2) { width, height };
    const int bounds_y = (parent_size.y / 2) - height / 2;
    const int2 position_in_canvas = get_element_pixel_position_global(parent_position, parent_size, pixel_position, anchor);
    const float2 position2D = get_element_position(position_in_canvas, canvas_size);
    zox_instance(prefab_scrollbar_front)
    zox_name("scrollbar_front")
    zox_add_tag(e, ScrollbarButton)
    zox_set(e, DraggableLimits, { (int4) { 0, 0, -bounds_y, bounds_y } })
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, position_in_canvas);
    return e;
}
