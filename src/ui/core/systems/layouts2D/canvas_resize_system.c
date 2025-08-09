// todo: get dimensions off app using AppLink from Canvas, check it's dimensions
void CanvasResizeSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(CameraLink)
    zox_sys_in(Children)
    zox_sys_in(ScreenToCanvas)
    zox_sys_in(AppLink)
    zox_sys_out(PixelSize)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(CameraLink, cameraLink)
        zox_sys_i(Children, children)
        zox_sys_i(ScreenToCanvas, screenToCanvas)
        zox_sys_i(AppLink, appLink)
        zox_sys_o(PixelSize, pixelSize)
        if (!zox_valid(cameraLink->value) || !zox_valid(appLink->value)) {
            continue;
        }
        zox_geter_value(appLink->value, WindowSize, int2, screen_size)
        const int2 pixel_size = screen_to_canvas_size(screen_size, screenToCanvas->value);
        if (int2_equals(pixel_size, pixelSize->value)) {
            continue;
        }
        // zox_log("canvas resized [%ix%i]", pixel_size.x, pixel_size.y)
        pixelSize->value = pixel_size;
        for (int j = 0; j < children->length; j++) {
            const entity child = children->value[j];
            if (!zox_valid(child)) {
                continue;
            }
            // zox_log("  - child [%s] resized", zox_get_name(child))
            set_ui_transform(world, e, child, pixel_size, int2_half(pixel_size), pixel_size);
        }
    }
} zoxd_system(CanvasResizeSystem)
