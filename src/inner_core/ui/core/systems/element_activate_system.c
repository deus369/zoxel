#ifdef zoxel_inputs
    void set_ui_clicked_mut(ecs_world_t *world, ecs_entity_t ui) {
        if (ecs_has(world, ui, Clickable)) {
            ClickableState *clickableState = ecs_get_mut(world, ui, ClickableState);
            clickableState->value = 1;
            ecs_modified(world, ui, ClickableState);
        }
    }

    // should we check input mode here first?
    //! Using mouse - or action - activate a ui element.
    void ElementActivateSystem(ecs_iter_t *it) {
        ecs_world_t *world = it->world;
        const DeviceLinks *deviceLinks = ecs_field(it, DeviceLinks, 1);
        const RaycasterTarget *raycasterTargets = ecs_field(it, RaycasterTarget, 2);
        for (int i = 0; i < it->count; i++) {
            const RaycasterTarget *raycasterTarget = &raycasterTargets[i];
            if (raycasterTarget->value == 0) continue;
            const DeviceLinks *deviceLinks2 = &deviceLinks[i];
            for (int j = 0; j < deviceLinks2->length; j++) {
                ecs_entity_t device_entity = deviceLinks2->value[j];
                if (ecs_has(world, device_entity, Mouse)) {
                    const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                    if (mouse->left.pressed_this_frame) {
                        if (ecs_has(world, raycasterTarget->value, Dragable)) {
                            DragableState *dragableState = ecs_get_mut(world, raycasterTarget->value, DragableState);
                            DraggerLink *draggerLink = ecs_get_mut(world, raycasterTarget->value, DraggerLink);
                            dragableState->value = 1;
                            draggerLink->value = it->entities[i];
                            ecs_modified(world, raycasterTarget->value, DragableState);
                            ecs_modified(world, raycasterTarget->value, DraggerLink);
                        }
                    } else if (mouse->left.released_this_frame) {
                        set_ui_clicked_mut(world, raycasterTarget->value);
                    }
                } else if (ecs_has(world, device_entity, Touchscreen)) {
                    const Touchscreen *touchscreen = ecs_get(world, device_entity, Touchscreen);
                    if (touchscreen->primary_touch.value.pressed_this_frame) {
                        if (ecs_has(world, raycasterTarget->value, Dragable)) {
                            DragableState *dragableState = ecs_get_mut(world, raycasterTarget->value, DragableState);
                            DraggerLink *draggerLink = ecs_get_mut(world, raycasterTarget->value, DraggerLink);
                            dragableState->value = 1;
                            draggerLink->value = it->entities[i];
                            ecs_modified(world, raycasterTarget->value, DragableState);
                            ecs_modified(world, raycasterTarget->value, DraggerLink);
                            zoxel_log(" > ui dragging at [%f]\n", (float) zox_current_time);
                        }
                    } else if (touchscreen->primary_touch.value.released_this_frame) {
                        set_ui_clicked_mut(world, raycasterTarget->value);
                        zoxel_log(" > ui activated at [%f]\n", (float) zox_current_time);
                    }
                } else if (ecs_has(world, device_entity, Gamepad)) {
                    const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                    if (gamepad->a.released_this_frame) {    // pressed_this_frame
                        set_ui_clicked_mut(world, raycasterTarget->value);
                    }
                }
            }
        }
    }
    zox_declare_system(ElementActivateSystem)
#endif