// A system that casts a ray into the ui elements
//  Creates an external event when selects a entity. Can be used by AI to select ui too
// #define zoxel_debug_ui_selectable_states

void set_selectable_state_mut(ecs_world_t *world, ecs_entity_t ui_entity, unsigned char state) {
    if (ui_entity != 0) { // && ecs_is_alive(world, ui_entity) && ecs_has(world, ui_entity, SelectState)) {
        SelectState *selectState = ecs_get_mut(world, ui_entity, SelectState);
        if (selectState->value != state) {
            selectState->value = state;
            ecs_modified(world, ui_entity, SelectState);
            // zoxel_log(" > setting [%lu]'s state %i\n", ui_entity, state);
        }
        #ifdef zoxel_debug_ui_selectable_states
            else {
                zoxel_log(" ! [%lu]'s state was already %i\n", ui_entity, state);
            }
        #endif
    }
    #ifdef zoxel_debug_ui_selectable_states
        else {
            zoxel_log(" ! [%lu]'s ui had no selectable state!\n", ui_entity);
        }
    #endif
}

void raycaster_select_ui(ecs_world_t *world, RaycasterTarget *raycasterTarget, ecs_entity_t ui) {
    if (raycasterTarget->value != ui) {
        // zoxel_log(" > raycaster_select_ui : selecting [%lu] from [%lu]\n", ui, raycasterTarget->value);
        set_selectable_state_mut(world, raycasterTarget->value, 0);
        raycasterTarget->value = ui;
    }
}

void raycaster_select_ui_mut(ecs_world_t *world, ecs_entity_t raycaster_entity, ecs_entity_t ui_entity) {
    RaycasterTarget *raycasterTarget = ecs_get_mut(world, raycaster_entity, RaycasterTarget);
    if (raycasterTarget->value != ui_entity) {
        // zoxel_log(" > raycaster_select_ui_mut : selecting [%lu] from [%lu]\n", ui, raycasterTarget->value);
        raycaster_select_ui(world, raycasterTarget, ui_entity);
        ecs_modified(world, raycaster_entity, RaycasterTarget);
        set_selectable_state_mut(world, ui_entity, 1);
    }
    #ifdef zoxel_debug_ui_selectable_states
        else {
            zoxel_log(" ! [%lu]'s was already set\n", ui_entity);
        }
    #endif
}

void ElementRaycastSystem(ecs_iter_t *it) {
    const Raycaster *raycasters = ecs_field(it, Raycaster, 1);
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 2);
    RaycasterTarget *raycasterTargets = ecs_field(it, RaycasterTarget, 3);
    for (int i = 0; i < it->count; i++) {
        const DeviceMode *deviceMode = &deviceModes[i];
        if (deviceMode->value != zox_device_mode_keyboardmouse && deviceMode->value != zox_device_mode_touchscreen) continue;
        const Raycaster *raycaster = &raycasters[i];
        RaycasterTarget *raycasterTarget = &raycasterTargets[i];
        int ui_layer = -1;
        ecs_entity_t ui_selected = 0;
        SelectState *ui_selected_selectableState = NULL;
        const int2 position = raycaster->value;
        #ifdef zox_debug_log_element_raycasting
            zoxel_log(" > ui raycasting [%ix%i] screen size [%ix%i]\n",
                position.x, position.y, screen_dimensions.x, screen_dimensions.y);
        #endif
        ecs_iter_t uis_it = ecs_query_iter(it->world, it->ctx);
        while(ecs_query_next(&uis_it)) {
            // printf("    - uis_it.count [%i] - (%i)\n", i, uis_it.count);
            const CanvasPixelPosition *canvasPixelPositions = ecs_field(&uis_it, CanvasPixelPosition, 2);
            const PixelSize *pixelSizes = ecs_field(&uis_it, PixelSize, 3);
            const Layer2D *layer2Ds = ecs_field(&uis_it, Layer2D, 4);
            SelectState *selectableStates = ecs_field(&uis_it, SelectState, 5);
            for (int j = 0; j < uis_it.count; j++) {
                const CanvasPixelPosition *canvasPixelPosition2 = &canvasPixelPositions[j];
                const PixelSize *pixelSize2 = &pixelSizes[j];
                const Layer2D *layer2D = &layer2Ds[j];
                const int2 canvasPixelPosition = canvasPixelPosition2->value;
                const int2 pixelSize = pixelSize2->value;
                // printf("ui raycasting [%lu] - [%i]\n", (long int) uis_it.entities[j], layer2D->value);
                int4 ui_bounds = { canvasPixelPosition.x - pixelSize.x / 2, canvasPixelPosition.x + pixelSize.x / 2,
                    canvasPixelPosition.y - pixelSize.y / 2,  canvasPixelPosition.y + pixelSize.y / 2};
                // zoxel_log("        - ui [%ix%ix%ix%i]\n", ui_bounds.x, ui_bounds.y, ui_bounds.z, ui_bounds.w);
                // centered
                SelectState *selectState = &selectableStates[j];
                unsigned char was_raycasted = position.x >= ui_bounds.x
                    && position.x <= ui_bounds.y && position.y >= ui_bounds.z && position.y <= ui_bounds.w;
                if (was_raycasted && layer2D->value > ui_layer) {
                    ui_layer = layer2D->value;
                    ui_selected = uis_it.entities[j];
                    ui_selected_selectableState = selectState;
                    #ifdef zox_debug_log_element_raycasting
                        zoxel_log("     + ui [%lu] position [%ix%i] size [%ix%i]\n", (long int) uis_it.entities[j],
                            canvasPixelPosition.x, canvasPixelPosition.y, pixelSize.x, pixelSize.y);
                    #endif
                }
                /*if (was_raycasted) {
                    printf("selectState ui was raycasted [%lu]\n", (long int) uis_it.entities[j]);
                } else if (!was_raycasted) {
                    printf("selectState ui was un raycasted [%lu]\n", (long int) uis_it.entities[j]);
                }*/
            }
        }
        if (raycasterTarget->value != ui_selected) {
            raycaster_select_ui(it->world, raycasterTarget, ui_selected);
            if (ui_layer != -1)  ui_selected_selectableState->value = 1;
            // zoxel_log(" > mouse raycasting new ui\n");
            // printf("    -> new target ui [%lu] \n", (long int) raycasterTarget->value);
        }
    }
} zox_declare_system(ElementRaycastSystem)