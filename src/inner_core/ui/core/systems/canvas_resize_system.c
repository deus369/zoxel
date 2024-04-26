void CanvasResizeSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(CameraLink, cameraLinks, 1)
    zox_field_in(Children, childrens, 2)
    zox_field_in(ScreenToCanvas, screenToCanvass, 3)
    zox_field_out(PixelSize, pixelSizes, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(CameraLink, cameraLinks, cameraLink)
        if (!cameraLink->value) continue;
        zox_field_i_out(PixelSize, pixelSizes, pixelSize)
        zox_field_i_in(ScreenToCanvas, screenToCanvass, screenToCanvas)
        // // (cameraLink->value, ScreenDimensions) - todo: get dimensions off app
        int2 viewport_dimensions = screen_to_canvas_size(screen_dimensions, screenToCanvas->value);
        if (pixelSize->value.x == viewport_dimensions.x && pixelSize->value.y == viewport_dimensions.y) continue;
        zox_field_e()
        zox_field_i_in(Children, childrens, children)
        pixelSize->value = viewport_dimensions;
        // zox_log(" > viewport resize detected [%ix%i]\n", screen_dimensions.x, screen_dimensions.y)
        // zox_log("canvas children resizing: %i\n", children->length)
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t child = children->value[j];
            // if (!zox_valid(child)) zox_log("   > canvas child invalid: %lu\n", child)
            if (!zox_valid(child)) continue;
            // zox_log("  - [%i] canvas child is resizing: %lu\n", j, child)
            set_ui_transform(world, e, child, 0, viewport_dimensions);
        }
    }
} zox_declare_system(CanvasResizeSystem)
