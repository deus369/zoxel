// A system that casts a ray into the ui elements
//  Creates an external event when selects a entity. Can be used by AI to select ui too
// #define zoxel_debug_ui_selectable_states

void set_element_brightness_mut(ecs_world_t *world, ecs_entity_t e, float value) {
    if (!e) return;
    Brightness *brightness = zox_get_mut(e, Brightness)
    if (brightness->value != value) {
        brightness->value = value;
        zox_modified(e, Brightness);
    }
}

void set_selectable_state_mut(ecs_world_t *world, ecs_entity_t ui_entity, unsigned char state) {
    if (ui_entity != 0) { // && ecs_is_alive(world, ui_entity) && zox_has(ui_entity, SelectState)) {
        SelectState *selectState = zox_get_mut(ui_entity, SelectState)
        if (selectState->value != state) {
            selectState->value = state;
            zox_modified(ui_entity, SelectState);
            // zoxel_log(" > setting [%lu]'s state %i\n", ui_entity, state);
        }
#ifdef zoxel_debug_ui_selectable_states
        else {
            zox_log(" ! [%lu]'s state was already %i\n", ui_entity, state)
        }
#endif
    }
#ifdef zoxel_debug_ui_selectable_states
    else {
        zox_log(" ! [%lu]'s ui had no selectable state!\n", ui_entity)
    }
#endif
}

void raycaster_select_ui(ecs_world_t *world, RaycasterTarget *raycasterTarget, ecs_entity_t ui_entity) {
    if (raycasterTarget->value != ui_entity) {
        if (raycasterTarget->value && ecs_is_alive(world, raycasterTarget->value)) set_selectable_state_mut(world, raycasterTarget->value, 0);
        raycasterTarget->value = ui_entity;
        // zox_log(" ===== UI SELECTED [%lu] =====\n",  ui_entity)
        /*if (raycasterTarget->value != 0) zox_set(raycasterTarget->value, SelectState, { 0 })
        if (ui_entity != 0) zox_set(ui_entity, SelectState, { 1 })*/
    }
}

void raycaster_select_ui_mut(ecs_world_t *world, ecs_entity_t raycaster_entity, ecs_entity_t ui_entity) {
    RaycasterTarget *raycasterTarget = ecs_get_mut(world, raycaster_entity, RaycasterTarget);
    if (raycasterTarget->value != ui_entity) {
        raycaster_select_ui(world, raycasterTarget, ui_entity);
        zox_modified(raycaster_entity, RaycasterTarget)
        set_selectable_state_mut(world, ui_entity, 1);
        zox_set(raycaster_entity, RaycasterTarget, { ui_entity })
        // zox_log(" > raycaster_select_ui_mut : selecting [%lu]\n", ui_entity)
    }
#ifdef zoxel_debug_ui_selectable_states
    else zox_log(" ! [%lu]'s was already set\n", ui_entity)
#endif
}

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
                // zox_log("ui raycasting [%lu] - [%i]\n", uis_it.entities[j], layer2D->value)
                // zox_log("        - ui [%ix%ix%ix%i]\n", ui_bounds.x, ui_bounds.y, ui_bounds.z, ui_bounds.w)
                // centered
                unsigned char was_raycasted = position.x >= ui_bounds.x && position.x <= ui_bounds.y && position.y >= ui_bounds.z && position.y <= ui_bounds.w;
                if (was_raycasted && layer2D->value > ui_layer) {
                    ui_layer = layer2D->value;
                    ui_selected = uis_it.entities[j];
                    // if (ui_selected_selectableState) ui_selected_selectableState->value = 0;
                    ui_selected_selectableState = selectState;
#ifdef zox_debug_log_element_raycasting
                    zox_log("     + ui [%lu] position [%ix%i] size [%ix%i]\n", ui_selected, canvasPosition.x, canvasPosition.y, pixelSize.x, pixelSize.y)
#endif
                    // zox_log("   > was_raycasted [%i:%i] - %i of %i uis in table\n", i, k, j, uis_it.count)
                }
            }
            // zox_log("    - uis_it.count [%i:%i] - (%i)\n", i, k, uis_it.count)
            k++;
        }
        if (raycasterTarget->value != ui_selected) {
            // set_element_brightness_mut(world, raycasterTarget->value, 1.0f);
            if (raycasterTarget->value) zox_set_mut(raycasterTarget->value, Brightness, ui_default_brightness)
            if (raycasterTarget->value) set_selectable_state_mut(world, raycasterTarget->value, 0);
            raycaster_select_ui(world, raycasterTarget, ui_selected);
            raycasterTarget->value = ui_selected;
            if (ui_selected_selectableState) ui_selected_selectableState->value = 1;
            // set_element_brightness_mut(world, raycasterTarget->value, 1.3f);
            if (raycasterTarget->value) zox_set_mut(raycasterTarget->value, Brightness, ui_selected_brightness)
        }
    }
} zox_declare_system(ElementRaycastSystem)
