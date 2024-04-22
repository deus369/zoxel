void ElementRaycastSystem(ecs_iter_t *it) {
    zox_iter_world()
    const Raycaster *raycasters = ecs_field(it, Raycaster, 1);
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 2);
    RaycasterTarget *raycasterTargets = ecs_field(it, RaycasterTarget, 3);
    for (int i = 0; i < it->count; i++) {
        const DeviceMode *deviceMode = &deviceModes[i];
        if (deviceMode->value != zox_device_mode_keyboardmouse && deviceMode->value != zox_device_mode_touchscreen) continue;
        const Raycaster *raycaster = &raycasters[i];
        RaycasterTarget *raycasterTarget = &raycasterTargets[i];
        const int2 position = raycaster->value;
        int ui_layer = -1;
        ecs_entity_t ui_selected = 0;
        SelectState *ui_selected_selectableState = NULL;
#ifdef zox_debug_log_element_raycasting
        zox_log(" > ui raycasting [%ix%i] screen size [%ix%i]\n", position.x, position.y, screen_dimensions.x, screen_dimensions.y)
#endif
        int k = 0;
        ecs_iter_t uis_it = ecs_query_iter(world, it->ctx);
        while(ecs_query_next(&uis_it)) {
            const CanvasPosition *canvasPositions = ecs_field(&uis_it, CanvasPosition, 2);
            const PixelSize *pixelSizes = ecs_field(&uis_it, PixelSize, 3);
            const Layer2D *layer2Ds = ecs_field(&uis_it, Layer2D, 4);
            const RenderDisabled *renderDisableds = ecs_field(&uis_it, RenderDisabled, 5);
            SelectState *selectableStates = ecs_field(&uis_it, SelectState, 6);
            for (int j = 0; j < uis_it.count; j++) {
                const RenderDisabled *renderDisabled = &renderDisableds[j];
                if (renderDisabled->value) continue;
                const CanvasPosition *canvasPosition2 = &canvasPositions[j];
                const PixelSize *pixelSize2 = &pixelSizes[j];
                const Layer2D *layer2D = &layer2Ds[j];
                SelectState *selectState = &selectableStates[j];
                const int2 canvasPosition = canvasPosition2->value;
                const int2 pixelSize = pixelSize2->value;
                int4 ui_bounds = { canvasPosition.x - pixelSize.x / 2, canvasPosition.x + pixelSize.x / 2, canvasPosition.y - pixelSize.y / 2,  canvasPosition.y + pixelSize.y / 2};
                unsigned char was_raycasted = position.x >= ui_bounds.x && position.x <= ui_bounds.y && position.y >= ui_bounds.z && position.y <= ui_bounds.w;
                if (was_raycasted && layer2D->value > ui_layer) {
                    ui_layer = layer2D->value;
                    ui_selected = uis_it.entities[j];
                    ui_selected_selectableState = selectState;
#ifdef zox_debug_log_element_raycasting
                    zox_log("     + ui [%lu] position [%ix%i] size [%ix%i]\n", ui_selected, canvasPosition.x, canvasPosition.y, pixelSize.x, pixelSize.y)
#endif
                }
            }
            k++;
        }
        if (raycasterTarget->value != ui_selected) {
            if (raycasterTarget->value) zox_set_mut(raycasterTarget->value, Brightness, ui_default_brightness)
            if (raycasterTarget->value) set_selectable_state_mut(world, raycasterTarget->value, 0);
            raycaster_select_ui(world, raycasterTarget, ui_selected);
            raycasterTarget->value = ui_selected;
            if (ui_selected_selectableState) ui_selected_selectableState->value = 1;
            if (raycasterTarget->value) zox_set_mut(raycasterTarget->value, Brightness, ui_selected_brightness)
        }
    }
} zox_declare_system(ElementRaycastSystem)
