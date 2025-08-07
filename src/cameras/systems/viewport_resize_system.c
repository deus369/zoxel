void ViewportResizeSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(WindowSizeDirty)
    zox_sys_in(WindowSize)
    zox_sys_in(CameraLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(WindowSizeDirty, windowSizeDirty)
        zox_sys_i(WindowSize, windowSize)
        zox_sys_i(CameraLinks, cameraLinks)
        if (windowSizeDirty->value) {
            //zox_log_error("viewport is a dirty [%i] cameras at [%ix%i]", cameraLinks->length, windowSize->value.x, windowSize->value.y)
            // refresh viewport
            for (int j = 0; j < cameraLinks->length; j++) {
                const entity camera = cameraLinks->value[j];
                if (!zox_valid(camera)) { //  || !zox_has(camera, Camera3D)
                    continue;
                }
                const float4 screen_to_canvas = zox_get_value(camera, ScreenToCanvas)
                const int2 size = screen_to_canvas_size(windowSize->value, screen_to_canvas);
                const int2 position = screen_to_canvas_position(windowSize->value, screen_to_canvas);
                zox_set(camera, ScreenPosition, { position })
                if (zox_has(camera, Camera3D)) {
                    const int2 scaled_size = scale_viewport(size);
                    zox_set(camera, ScreenDimensions, { scaled_size })
                } else {
                    zox_set(camera, ScreenDimensions, { size })
                }
                //zox_log("   - setting camera [%s] size [%ix%i]", zox_get_name(camera), size.x, size.y)
            }
        }
    }
} zox_declare_system(ViewportResizeSystem)