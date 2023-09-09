#ifdef zoxel_inputs
    void set_ui_clicked_mut(ecs_world_t *world, ecs_entity_t ui) {
        if (ecs_has(world, ui, Clickable)) {
            zox_set_only(ui, ClickState, { 1 }) // i made it like this due to some complication
            /*ClickState *clickState = ecs_get_mut(world, ui, ClickState);
            clickState->value = 1;
            ecs_modified(world, ui, ClickState);*/
        }
    }

    void ElementActivateSystem(ecs_iter_t *it) {
        ecs_world_t *world = it->world;
        const DeviceLinks *deviceLinks = ecs_field(it, DeviceLinks, 1);
        const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 2);
        const RaycasterTarget *raycasterTargets = ecs_field(it, RaycasterTarget, 3);
        RaycasterResult *raycasterResults = ecs_field(it, RaycasterResult, 4);
        for (int i = 0; i < it->count; i++) {
            RaycasterResult *raycasterResult = &raycasterResults[i];
            const RaycasterTarget *raycasterTarget = &raycasterTargets[i];
            if (raycasterTarget->value == 0) {
                raycasterResult->value = 0;
                continue;
            }
            ecs_entity_t e = it->entities[i];
            const DeviceLinks *deviceLinks2 = &deviceLinks[i];
            const DeviceMode *deviceMode = &deviceModes[i];
            unsigned char did_drag = 0;
            unsigned char did_activate = 0;
            // convert input to actions
            for (int j = 0; j < deviceLinks2->length; j++) {
                ecs_entity_t device_entity = deviceLinks2->value[j];
                if (deviceMode->value == zox_device_mode_keyboardmouse && ecs_has(world, device_entity, Mouse)) {
                    const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                    if (mouse->left.pressed_this_frame) {
                        did_drag = 1;
                    } else if (mouse->left.released_this_frame) {
                        did_activate = 1;
                    }
                } else if (deviceMode->value == zox_device_mode_gamepad && ecs_has(world, device_entity, Gamepad)) {
                    const Children *zevices = ecs_get(world, device_entity, Children);
                    for (int k = 0; k < zevices->length; k++) {
                        ecs_entity_t zevice_entity = zevices->value[k];
                        if (ecs_has(world, zevice_entity, ZeviceButton)) {
                            const DeviceButtonType *deviceButtonType = ecs_get(world, zevice_entity, DeviceButtonType);
                            if (deviceButtonType->value == zox_device_button_a) {
                                const ZeviceDisabled *zeviceDisabled = ecs_get(world, zevice_entity, ZeviceDisabled);
                                if (!zeviceDisabled->value) {
                                    const ZeviceButton *zeviceButton = ecs_get(world, zevice_entity, ZeviceButton);
                                    if (devices_get_pressed_this_frame(zeviceButton->value)) did_activate = 1;
                                }
                                break;
                            }
                        }
                    }
                } else if (deviceMode->value == zox_device_mode_touchscreen && ecs_has(world, device_entity, Touchscreen)) {
                    const Children *zevices = ecs_get(world, device_entity, Children);
                    for (int k = 0; k < zevices->length; k++) {
                        ecs_entity_t zevice_entity = zevices->value[k];
                        if (ecs_has(world, zevice_entity, ZevicePointer)) {
                            const ZevicePointer *zevicePointer = ecs_get(world, zevice_entity, ZevicePointer);
                            if (devices_get_pressed_this_frame(zevicePointer->value)) {
                                did_drag = 1;
                            } else if (devices_get_released_this_frame(zevicePointer->value)) {
                                did_activate = 1;
                            }
                            break;
                        }
                    }
                }
            }
            if (did_drag) {
                if (ecs_has(world, raycasterTarget->value, Dragable)) {
                    // todo: zox_set_mut => the next 3 lines basically, component, entity, new_value
                    DragableState *dragableState = ecs_get_mut(world, raycasterTarget->value, DragableState);
                    dragableState->value = 1;
                    ecs_modified(world, raycasterTarget->value, DragableState);
                    DraggerLink *draggerLink = ecs_get_mut(world, raycasterTarget->value, DraggerLink);
                    draggerLink->value = e;
                    ecs_modified(world, raycasterTarget->value, DraggerLink);
                    // zoxel_log(" > ui dragging at [%f]\n", (float) zox_current_time);
                }
                raycasterResult->value = 1;
            } else if (did_activate) {
                set_ui_clicked_mut(world, raycasterTarget->value);
                raycasterResult->value = 1;
            } else {
                raycasterResult->value = 0;
            }
        }
    } zox_declare_system(ElementActivateSystem)
#endif