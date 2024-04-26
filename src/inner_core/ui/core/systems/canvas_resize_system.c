void CanvasResizeSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(CameraLink, cameraLinks, 1)
    zox_field_in(Children, childrens, 2)
    zox_field_out(PixelSize, pixelSizes, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(CameraLink, cameraLinks, cameraLink)
        if (!cameraLink->value) continue;
        zox_field_i_out(PixelSize, pixelSizes, pixelSize)
        const int2 screen_dimensions = zox_get_value(cameraLink->value, ScreenDimensions)
        if (pixelSize->value.x == screen_dimensions.x && pixelSize->value.y == screen_dimensions.y) continue;
        zox_field_e()
        zox_field_i_in(Children, childrens, children)
        pixelSize->value = screen_dimensions;
        // zox_log(" > viewport resize detected [%ix%i]\n", screen_dimensions.x, screen_dimensions.y)
        // zox_log("canvas children resizing: %i\n", children->length)
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t child = children->value[j];
            // if (!zox_valid(child)) zox_log("   > canvas child invalid: %lu\n", child)
            if (!zox_valid(child)) continue;
            // zox_log("  - [%i] canvas child is resizing: %lu\n", j, child)
            set_ui_transform(world, e, child, 0, screen_dimensions);
        }
    }
} zox_declare_system(CanvasResizeSystem)
