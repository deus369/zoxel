// for any elements with parent that is canvas
void ElementPositionSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(PixelPosition, pixelPositions, 1)
    zox_field_in(PixelSize, pixelSizes, 2)
    zox_field_in(ParentLink, parentLinks, 3)
    zox_field_in(Anchor, anchors, 4)
    zox_field_in(CanvasLink, canvasLinks, 5)
    zox_field_out(Position2D, position2Ds, 6)
    zox_field_out(CanvasPosition, canvasPositions, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(PixelPosition, pixelPositions, pixelPosition)
        zox_field_i(PixelSize, pixelSizes, pixelSize)
        zox_field_i(ParentLink, parentLinks, parentLink)
        zox_field_i(Anchor, anchors, anchor)
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        if (!zox_valid(canvasLink->value) || parentLink->value != canvasLink->value) {
            continue;
        }
        zox_field_o(Position2D, position2Ds, position2D)
        zox_field_o(CanvasPosition, canvasPositions, canvasPosition)
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        const int2 pixel_position = pixelPosition->value;
        const float2 anchor2 = anchor->value;
        int2 position_in_canvas = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor2);
        const float2 position_real = get_element_position(position_in_canvas, canvas_size);
        canvasPosition->value = position_in_canvas;
        position2D->value = position_real;
        if (zox_has(e, Children)) {
            zox_geter(e, Children, children)
            for (int j = 0; j < children->length; j++) {
                const ecs_entity_t child = children->value[j];
                set_element_position(world, child, position_in_canvas, pixelSize->value, canvas_size);
            }
        }
    }
} zox_declare_system(ElementPositionSystem)