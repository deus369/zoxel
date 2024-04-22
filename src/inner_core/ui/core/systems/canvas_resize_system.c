void CanvasResizeSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(CameraLink, cameraLinks, 1)
    zox_field_out(PixelSize, pixelSizes, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(CameraLink, cameraLinks, cameraLink)
        if (!cameraLink->value) continue;
        const int2 screen_dimensions = zox_get_value(cameraLink->value, ScreenDimensions)
        zox_field_i_out(PixelSize, pixelSizes, pixelSize)
        if (pixelSize->value.x == screen_dimensions.x && pixelSize->value.y == screen_dimensions.y) continue;
        pixelSize->value = screen_dimensions;
        // now do the other stuff
        zox_log("viewport resize detected [%ix%i]\n", screen_dimensions.x, screen_dimensions.y)
        resize_element_system_screen_size = screen_dimensions;
        // todo: use children here instead of calling a system... but
        //       that involves keeping links up to date for canvas children
        ecs_run(world, ecs_id(ResizeElementSystem), 0, NULL);
    }
} zox_declare_system(CanvasResizeSystem)
