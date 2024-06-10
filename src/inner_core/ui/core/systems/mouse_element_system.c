// element will follow mouse position
void MouseElementSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(MouseLink, mouseLinks, 1)
    zox_field_in(RenderDisabled, renderDisableds, 2)
    zox_field_in(Anchor, anchors, 3)
    zox_field_in(CanvasLink, canvasLinks, 4)
    zox_field_out(PixelPosition, pixelPositions, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        // if (renderDisabled->value) continue; // disabled because looks weird
        zox_field_i(MouseLink, mouseLinks, mouseLink)
        if (!mouseLink->value) continue;
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        if (!canvasLink->value) continue;
        const Mouse *mouse = zox_get(mouseLink->value, Mouse)
        if (!mouse) continue;
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        zox_field_i(Anchor, anchors, anchor)
        zox_field_o(PixelPosition, pixelPositions, pixelPosition)
        pixelPosition->value = mouse->position;
        pixelPosition->value.x -= anchor->value.x * canvas_size.x;
        pixelPosition->value.y -= anchor->value.y * canvas_size.y;
    }
} zox_declare_system(MouseElementSystem)
