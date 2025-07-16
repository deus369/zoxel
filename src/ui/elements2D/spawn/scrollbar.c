ecs_entity_t spawn_scrollbar(ecs_world_t *world,
    ecs_entity_t parent,
    ecs_entity_t canvas,
    int2 pixel_position,
    byte layer,
    int2 parent_pixel_position_global,
    int2 parent_pixel_size,
    int width,
    int scrollbar_margins,
    int2 canvas_size,
    int elements_count,
    int max_elements)
{
    byte child_layer = layer + 1;
    float2 anchor = (float2) { 1.0f, 0.5f };
    int2 pixel_size = (int2) { width, parent_pixel_size.y };
    int2 margins = (int2) { scrollbar_margins, 0 };
    int height = (int) parent_pixel_size.y * ( float_min(1, (float) elements_count / (float) max_elements));
    if (elements_count == 0) {
        height = parent_pixel_size.y;
    }
    zox_instance(prefab_scrollbar)
    zox_name("scrollbar")
    zox_set(e, ElementMargins, { margins })
    int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    zox_muter(e, Children, children)
    const ecs_entity_t scrollbar_handle = spawn_scrollbar_front(world,
        e,
        canvas,
        (int2) { 0, (parent_pixel_size.y - height) / 2 },   // put at top of scroll
        float2_half,
        child_layer,
        width,
        height,
        pixel_position_global,
        pixel_size,
        canvas_size);
    add_to_Children(children, scrollbar_handle);
    //zox_log("- scrollbar height set to: [%i] out of [%i]", height, parent_pixel_size.y)
    // zox_log("- scrollbar showing [%i] out of [%i]", elements_count, max_elements)
    return e;
}
