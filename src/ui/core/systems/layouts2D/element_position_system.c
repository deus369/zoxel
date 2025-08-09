// for any elements with parent that is canvas
void ElementPositionSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(PixelPosition)
    zox_sys_in(PixelSize)
    zox_sys_in(ParentLink)
    zox_sys_in(Anchor)
    zox_sys_in(CanvasLink)
    zox_sys_out(Position2D)
    zox_sys_out(CanvasPosition)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(PixelPosition, pixelPosition)
        zox_sys_i(PixelSize, pixelSize)
        zox_sys_i(ParentLink, parentLink)
        zox_sys_i(Anchor, anchor)
        zox_sys_i(CanvasLink, canvasLink)
        zox_sys_o(Position2D, position2D)
        zox_sys_o(CanvasPosition, canvasPosition)
        if (!zox_valid(canvasLink->value) || parentLink->value != canvasLink->value) {
            continue;
        }
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
                const entity child = children->value[j];
                set_element_position(world, child, position_in_canvas, pixelSize->value, canvas_size);
            }
        }
    }
} zoxd_system(ElementPositionSystem)