void ElementRaycastSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(Raycaster, raycasters, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_out(RaycasterTarget, raycasterTargets, 3)
    zox_field_out(WindowRaycasted, windowRaycasteds, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(DeviceMode, deviceModes, deviceMode)
        if (deviceMode->value != zox_device_mode_keyboardmouse && deviceMode->value != zox_device_mode_touchscreen) continue;
        zox_field_e()
        zox_field_i_in(Raycaster, raycasters, raycaster)
        zox_field_i_out(RaycasterTarget, raycasterTargets, raycasterTarget)
        zox_field_i_out(WindowRaycasted, windowRaycasteds, windowRaycasted)
        const int2 position = raycaster->value;
        int ui_layer = -1;
        ecs_entity_t ui_selected = 0;
        int window_layer = -1;
        ecs_entity_t window_selected = 0;
#ifdef zox_debug_log_element_raycasting
        zox_log(" > ui raycasting [%ix%i] screen size [%ix%i]\n", position.x, position.y, screen_dimensions.x, screen_dimensions.y)
#endif
        int k = 0;
        ecs_iter_t it2 = ecs_query_iter(world, it->ctx);
        while(ecs_query_next(&it2)) {
            const CanvasPosition *canvasPositions = ecs_field(&it2, CanvasPosition, 2);
            const PixelSize *pixelSizes = ecs_field(&it2, PixelSize, 3);
            const Layer2D *layer2Ds = ecs_field(&it2, Layer2D, 4);
            const RenderDisabled *renderDisableds = ecs_field(&it2, RenderDisabled, 5);
            for (int j = 0; j < it2.count; j++) {
                const RenderDisabled *renderDisabled = &renderDisableds[j];
                if (renderDisabled->value) continue;
                const ecs_entity_t e2 = it2.entities[j];
                const ecs_entity_t camera = get_root_canvas_camera(world, e2);
                if (!camera) continue;
                const CanvasPosition *canvasPosition2 = &canvasPositions[j];
                const PixelSize *pixelSize2 = &pixelSizes[j];
                const Layer2D *layer2D = &layer2Ds[j];
                // SelectState *selectState = &selectableStates[j];
                const int2 pixelSize = pixelSize2->value;
                const int2 canvas_position = zox_get_value(camera, ScreenPosition)
                int2 viewport_position = canvasPosition2->value;
                viewport_position.x += canvas_position.x;
                viewport_position.y += canvas_position.y;
                // bounds should be offset with canvas position
                const int4 ui_bounds = { viewport_position.x - pixelSize.x / 2, viewport_position.x + pixelSize.x / 2, viewport_position.y - pixelSize.y / 2,  viewport_position.y + pixelSize.y / 2};
                const unsigned char was_raycasted = position.x >= ui_bounds.x && position.x <= ui_bounds.y && position.y >= ui_bounds.z && position.y <= ui_bounds.w;
                if (was_raycasted) {
                    const unsigned window_raycasted = zox_has(e2, Window);
                    if (layer2D->value > ui_layer) { // !window_raycasted &&
                        ui_layer = layer2D->value;
                        ui_selected = e2;
                    }
                    if (window_raycasted && layer2D->value > window_layer) {
                        window_layer = layer2D->value;
                        window_selected = e2;
                    }
#ifdef zox_debug_log_element_raycasting
                    zox_log("     + ui [%lu] position [%ix%i] size [%ix%i]\n", ui_selected, canvas_position.x, canvas_position.y, pixelSize.x, pixelSize.y)
#endif
                }
            }
            k++;
        }
        // if only exists to block others (like Window's)
        if (!zox_has(ui_selected, SelectState)) ui_selected = 0;
        if (raycasterTarget->value != ui_selected) {
            raycaster_select_element(world, e, ui_selected);
        }
        if (windowRaycasted->value != window_selected) {
            // zox_log(" > selected window [%lu]\n", window_selected)
            windowRaycasted->value = window_selected;
            // zox_set(element, SelectState, { window_selected })
        }
    }
} zox_declare_system(ElementRaycastSystem)
