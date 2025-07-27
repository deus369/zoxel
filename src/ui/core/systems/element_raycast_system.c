void ElementRaycastSystem(ecs_iter_t *it) {
    zox_sys_query()
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Raycaster)
    zox_sys_in(DeviceLink)
    zox_sys_out(RaycasterTarget)
    zox_sys_out(WindowRaycasted)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(DeviceLink, deviceLink)
        zox_sys_i(Raycaster, raycaster)
        zox_sys_o(RaycasterTarget, raycasterTarget)
        zox_sys_o(WindowRaycasted, windowRaycasted)
        if (!deviceLink->value) {
            continue;
        }
        const ecs_entity_t player = zox_get_value(deviceLink->value, PlayerLink)
        if (!player) {
            continue;
        }
        const byte device_mode = zox_get_value(player, DeviceMode)
        if (device_mode != zox_device_mode_keyboardmouse && device_mode != zox_device_mode_touchscreen) {
            continue;
        }
        const ecs_entity_t player_canvas = zox_get_value(player, CanvasLink)
        const ecs_entity_t player_camera_ui = zox_get_value(player_canvas, CameraLink)
        const int2 position = raycaster->value;
        int ui_layer = -1;
        ecs_entity_t ui_selected = 0;
        int window_layer = -1;
        ecs_entity_t window_selected = 0;
        zox_sys_query_begin()
        while (zox_sys_query_loop()) {
            zox_sys_begin_2()
            zox_sys_in_2(CanvasPosition)
            zox_sys_in_2(PixelSize)
            zox_sys_in_2(Layer2D)
            zox_sys_in_2(RenderDisabled)
            for (int j = 0; j < it2.count; j++) {
                zox_sys_i_2(RenderDisabled, renderDisabled)
                zox_sys_i_2(CanvasPosition, canvasPosition2)
                zox_sys_i_2(PixelSize, pixelSize2)
                zox_sys_i_2(Layer2D, layer2D)
                /*const RenderDisabled *renderDisabled = &renderDisableds[j];
                const CanvasPosition *canvasPosition2 = &canvasPositions[j];
                const PixelSize *pixelSize2 = &pixelSizes[j];
                const Layer2D *layer2D = &layer2Ds[j];*/
                if (renderDisabled->value) {
                    continue;
                }
                const ecs_entity_t e2 = it2.entities[j];
                const ecs_entity_t camera = get_root_canvas_camera(world, e2);
                if (!camera) {
                    continue;
                }
                if (player_camera_ui != camera) {
                    continue; // only do checks for player canvases
                }
                // SelectState *selectState = &selectableStates[j];
                const int2 pixelSize = pixelSize2->value;
                const int2 canvas_position = zox_get_value(camera, ScreenPosition)
                const int2 canvas_size = zox_get_value(camera, ScreenDimensions)
                const byte ray_in_viewport = position.x >= canvas_position.x && position.x <= canvas_position.x + canvas_size.x && position.y >= canvas_position.y && position.y <= canvas_position.y + canvas_size.y;
                if (!ray_in_viewport) {
                    continue;
                }
                int2 viewport_position = canvasPosition2->value;
                viewport_position.x += canvas_position.x;
                viewport_position.y += canvas_position.y;
                // bounds should be offset with canvas position
                const int4 ui_bounds = { viewport_position.x - pixelSize.x / 2, viewport_position.x + pixelSize.x / 2, viewport_position.y - pixelSize.y / 2,  viewport_position.y + pixelSize.y / 2};
                const byte was_raycasted = position.x >= ui_bounds.x && position.x <= ui_bounds.y && position.y >= ui_bounds.z && position.y <= ui_bounds.w;
                if (was_raycasted) {
                    const unsigned window_raycasted = zox_has(e2, WindowRaycastTarget);
                    if (layer2D->value > ui_layer) { // !window_raycasted &&
                        ui_layer = layer2D->value;
                        ui_selected = e2;
                    }
                    if (window_raycasted && layer2D->value > window_layer) {
                        if (!zox_has(e2, Window)) {
                            // if header/body use parent
                            window_selected = zox_get_value(e2, ParentLink)
                            window_layer = zox_get_value(ui_selected, Layer2D);
                        } else {
                            window_selected = e2;
                            window_layer = layer2D->value;
                        }
                    }
                }
            }
        }
        zox_sys_query_end()
        // if only exists to block others (like Window's)
        if (ui_selected && !zox_has(ui_selected, SelectState)) {
            ui_selected = 0;
        }
        if (raycasterTarget->value != ui_selected) {
            raycaster_select_element(world, e, ui_selected);
        }
        if (windowRaycasted->value != window_selected) {
            raycaster_select_window(world, e, window_selected);
        }
    }
} zox_declare_system(ElementRaycastSystem)