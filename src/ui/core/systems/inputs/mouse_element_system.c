// element will follow mouse position
void MouseElementSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ZeviceLink, zeviceLinks, 1)
    zox_field_in(Anchor, anchors, 2)
    zox_field_in(CanvasLink, canvasLinks, 3)
    zox_field_out(PixelPosition, pixelPositions, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        zox_field_i(ZeviceLink, zeviceLinks, zeviceLink)
        zox_field_i(Anchor, anchors, anchor)
        zox_field_o(PixelPosition, pixelPositions, pixelPosition)
        if (!canvasLink->value) {
            continue;
        }
        if (!zeviceLink->value) {
            continue;
        }
        if (!zox_has(zeviceLink->value, ZevicePointerPosition)) {
            zox_log(" > mouse link invalid, needs pointer position: %s\n", zox_get_name(zeviceLink->value))
        }
        const int2 position = zox_get_value(zeviceLink->value, ZevicePointerPosition)
        // if (!mouse) continue;
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        pixelPosition->value = position;
        pixelPosition->value.x -= anchor->value.x * canvas_size.x;
        pixelPosition->value.y -= anchor->value.y * canvas_size.y;
    }
} zox_declare_system(MouseElementSystem)
