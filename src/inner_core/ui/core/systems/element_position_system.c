void ElementPositionSystem(ecs_iter_t *it) {
    zox_iter_world()
    ecs_query_t *change_query = it->ctx;
    ecs_iter_t change_iter = ecs_query_iter(world, change_query);
    while (ecs_query_next(&change_iter)) {
        if (change_iter.table != it->table) ecs_query_skip(&change_iter);
    }
    zox_field_in(PixelPosition, pixelPositions, 2)
    zox_field_in(ParentLink, parentLinks, 3)
    zox_field_in(Anchor, anchors, 4)
    zox_field_in(CanvasLink, canvasLinks, 5)
    zox_field_out(Position2D, position2Ds, 6)
    zox_field_out(CanvasPosition, canvasPositions, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i_in(PixelPosition, pixelPositions, pixelPosition)
        zox_field_i_in(ParentLink, parentLinks, parentLink)
        zox_field_i_in(Anchor, anchors, anchor)
        zox_field_i_in(CanvasLink, canvasLinks, canvasLink)
        if (!zox_valid(canvasLink->value) || parentLink->value != canvasLink->value) continue;
        zox_field_i_out(Position2D, position2Ds, position2D)
        zox_field_i_out(CanvasPosition, canvasPositions, canvasPosition)
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        const int2 pixel_position = pixelPosition->value;
        const float2 anchor2 = anchor->value;
        const int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor2);
        const float2 position = get_element_position(pixel_position_global, canvas_size);
        canvasPosition->value = pixel_position_global;
        position2D->value = position;
        if (zox_has(e, Children)) {
            const int2 pixel_size = zox_get_value(e, PixelSize)
            const Children *children = zox_get(e, Children)
            for (int j = 0; j < children->length; j++) set_element_position(world, children->value[j], pixel_position_global, pixel_size, canvas_size);
        }
#ifdef debug_element_position_change_query
        zox_log("    - PixelPosition Updated [%lu]\n", e)
#endif
    }
} zox_declare_system(ElementPositionSystem)
