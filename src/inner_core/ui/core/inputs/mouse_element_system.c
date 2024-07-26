// element will follow mouse position
void MouseElementSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ZeviceLink, zeviceLinks, 1)
    zox_field_in(Anchor, anchors, 2)
    zox_field_in(CanvasLink, canvasLinks, 3)
    zox_field_out(PixelPosition, pixelPositions, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        if (!canvasLink->value) continue;
        zox_field_i(ZeviceLink, zeviceLinks, zeviceLink)
        if (!zeviceLink->value) continue;
        if (!zox_has(zeviceLink->value, ZevicePointerPosition)) {
            zox_log(" > mouse link invalid, needs pointer position: %s\n", zox_get_name(zeviceLink->value))
        }
        const int2 position = zox_get_value(zeviceLink->value, ZevicePointerPosition)
        // if (!mouse) continue;
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        zox_field_i(Anchor, anchors, anchor)
        zox_field_o(PixelPosition, pixelPositions, pixelPosition)
        pixelPosition->value = position;
        pixelPosition->value.x -= anchor->value.x * canvas_size.x;
        pixelPosition->value.y -= anchor->value.y * canvas_size.y;
        // zox_log(" > following [%s] at [%ix%i]\n", zox_get_name(it->entities[i]),pixelPosition->value.x, pixelPosition->value.y)
        // float2 position2D = zox_get_value(it->entities[i], Position2D)
        // zox_log("   - p [%fx%f]\n", position2D.x, position2D.y)
        // int2 size = zox_get_value(it->entities[i], PixelSize)
        // zox_log("   - p [%ix%i]\n", size.x, size.y)
        // zox_log("   - d [%i]\n", zox_gett_value(it->entities[i], RenderDisabled))
    }
} zox_declare_system(MouseElementSystem)

// zox_field_in(RenderDisabled, renderDisableds, 2)
// zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
// if (renderDisabled->value) continue; // disabled because looks weird
