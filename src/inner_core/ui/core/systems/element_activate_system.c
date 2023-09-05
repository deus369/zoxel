#ifdef zoxel_inputs
    void set_ui_clicked_mut(ecs_world_t *world, ecs_entity_t ui) {
        if (ecs_has(world, ui, Clickable)) {
            zox_set_only(ui, ClickableState, { 1 })
            /*ClickableState *clickableState = ecs_get_mut(world, ui, ClickableState);
            clickableState->value = 1;
            ecs_modified(world, ui, ClickableState);*/
        }
    }

    void ElementActivateSystem(ecs_iter_t *it) {
        ecs_world_t *world = it->world;
        const DeviceLinks *deviceLinks = ecs_field(it, DeviceLinks, 1);
        const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 2);
        const RaycasterTarget *raycasterTargets = ecs_field(it, RaycasterTarget, 3);
        for (int i = 0; i < it->count; i++) {
            const RaycasterTarget *raycasterTarget = &raycasterTargets[i];
            if (raycasterTarget->value == 0) continue;
            const DeviceLinks *deviceLinks2 = &deviceLinks[i];
            const DeviceMode *deviceMode = &deviceModes[i];
            unsigned char did_activate = 0;
            for (int j = 0; j < deviceLinks2->length; j++) {
                ecs_entity_t device_entity = deviceLinks2->value[j];
                if (deviceMode->value == zox_device_mode_keyboardmouse && ecs_has(world, device_entity, Mouse)) {
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
                        did_activate = 1;
                    }
                } else if (deviceMode->value == zox_device_mode_touchscreen && ecs_has(world, device_entity, Touchscreen)) {
                    const Touchscreen *touchscreen = ecs_get(world, device_entity, Touchscreen);
                    if (touchscreen->primary_touch.value.pressed_this_frame) {
                        if (ecs_has(world, raycasterTarget->value, Dragable)) {
                            DragableState *dragableState = ecs_get_mut(world, raycasterTarget->value, DragableState);
                            DraggerLink *draggerLink = ecs_get_mut(world, raycasterTarget->value, DraggerLink);
                            dragableState->value = 1;
                            draggerLink->value = it->entities[i];
                            ecs_modified(world, raycasterTarget->value, DragableState);
                            ecs_modified(world, raycasterTarget->value, DraggerLink);
                            // zoxel_log(" > ui dragging at [%f]\n", (float) zox_current_time);
                        }
                    } else if (touchscreen->primary_touch.value.released_this_frame) did_activate = 1;
                } else if (deviceMode->value == zox_device_mode_gamepad && ecs_has(world, device_entity, Gamepad)) {
                    const Children *zevices = ecs_get(world, device_entity, Children);
                    for (int k = 0; k < zevices->length; k++) {
                        ecs_entity_t zevice_entity = zevices->value[k];
                        if (ecs_has(world, zevice_entity, DeviceButton)) {
                            const DeviceButtonType *deviceButtonType = ecs_get(world, zevice_entity, DeviceButtonType);
                            if (deviceButtonType->value == zox_device_button_a) {
                                const ZeviceDisabled *zeviceDisabled = ecs_get(world, zevice_entity, ZeviceDisabled);
                                if (!zeviceDisabled->value) {
                                    const DeviceButton *deviceButton = ecs_get(world, zevice_entity, DeviceButton);
                                    if (devices_get_pressed_this_frame(deviceButton->value)) did_activate = 1;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            if (did_activate) set_ui_clicked_mut(world, raycasterTarget->value);
        }
    } zox_declare_system(ElementActivateSystem)
#endif

// const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
// if (gamepad->a.pressed_this_frame) set_ui_clicked_mut(world, raycasterTarget->value);