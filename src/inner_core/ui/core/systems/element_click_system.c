void set_element_dragged(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element, const unsigned char drag_mode) {
    DraggableState *dragableState = zox_get_mut(element, DraggableState)
    if (!dragableState->value) {
        DraggerLink *draggerLink = zox_get_mut(element, DraggerLink)
        dragableState->value = drag_mode;
        draggerLink->value = player;
        zox_modified(element, DraggableState)
        zox_modified(element, DraggerLink)
#ifdef zox_log_ui_dragging
        zox_log(" > ui dragging at [%f]\n", (float) zox_current_time)
#endif
    }
}

void ElementClickSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_in(RaycasterTarget, raycasterTargets, 3)
    zox_field_in(WindowRaycasted, windowRaycasteds, 4)
    zox_field_out(RaycasterResult, raycasterResults, 5)
    zox_field_out(ClickingEntity, clickingEntitys, 6)
    zox_field_out(WindowTarget, windowTargets, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(RaycasterTarget, raycasterTargets, raycasterTarget)
        zox_field_i(WindowRaycasted, windowRaycasteds, windowRaycasted)
        // if (!(raycasterTarget->value || windowRaycasted->value)) continue;
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        zox_field_o(RaycasterResult, raycasterResults, raycasterResult)
        zox_field_o(ClickingEntity, clickingEntitys, clickingEntity)
        zox_field_o(WindowTarget, windowTargets, windowTarget)
        unsigned click_type = 0;
        for (int j = 0; j < deviceLinks->length; j++) { // convert inputs to actions
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device_entity, Mouse)) {
                const Mouse *mouse = zox_get(device_entity, Mouse)
                if (mouse->left.pressed_this_frame) click_type = 1;
                else if (mouse->left.released_this_frame) click_type = 2;
            } else if (deviceMode->value == zox_device_mode_gamepad && zox_has(device_entity, Gamepad)) {
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceButton)) {
                        const DeviceButtonType *deviceButtonType = zox_get(zevice_entity, DeviceButtonType)
                        if (deviceButtonType->value == zox_device_button_a) {
                            const ZeviceDisabled *zeviceDisabled = zox_get(zevice_entity, ZeviceDisabled)
                            if (!zeviceDisabled->value) {
                                const ZeviceButton *zeviceButton = zox_get(zevice_entity, ZeviceButton)
                                if (devices_get_pressed_this_frame(zeviceButton->value)) click_type = 1;
                                else if (devices_get_released_this_frame(zeviceButton->value)) click_type = 2;
                            }
                            break;
                        }
                    }
                }
            } else if (deviceMode->value == zox_device_mode_touchscreen && zox_has(device_entity, Touchscreen)) {
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZevicePointer)) {
                        const ZevicePointer *zevicePointer = zox_get(zevice_entity, ZevicePointer)
                        if (devices_get_pressed_this_frame(zevicePointer->value)) click_type = 1;
                        else if (devices_get_released_this_frame(zevicePointer->value)) click_type = 2;
                        break;
                    }
                }
            }
        }
        // used for virtual joysticks to see if a t arget was raycasted, todo: move to raycast system
        raycasterResult->value = raycasterTarget->value || windowRaycasted->value;
        // released
        if (click_type == 0) continue;
        else if (click_type == 1) {
            clickingEntity->value = raycasterTarget->value; // clicked
            on_element_clicked(world, e, clickingEntity->value);
        }
        if (click_type == 1) { // clicked
            if (windowRaycasted->value != windowTarget->value) {
                windowTarget->value = windowRaycasted->value;
                // zox_log(" > player window target [%lu]\n", windowTarget->value)
                // todo: set it's window to top
                const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
                // now set WindowToTop entity to windowTarget->value
                // then next in canvas system, reset windows layers to top of window stack
                zox_set(canvas, WindowToTop, { windowTarget->value })
            }
            if (zox_has(raycasterTarget->value, Dragable)) {
                unsigned char drag_mode = zox_drag_mode_none;
                if (deviceMode->value == zox_device_mode_keyboardmouse) drag_mode = zox_drag_mode_mouse;
                else if (deviceMode->value == zox_device_mode_touchscreen) drag_mode = zox_drag_mode_finger;
                set_element_dragged(world, e, raycasterTarget->value, drag_mode);
            }
        } else if (click_type == 2) { // released
            if (raycasterTarget->value == clickingEntity->value) on_element_released(world, e, raycasterTarget->value);
            // else on_element_clicked(world, e, 0);
            clickingEntity->value = 0;
        }
    }
} zox_declare_system(ElementClickSystem)
