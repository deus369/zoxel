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

// this is now from zevice
void DeviceClickSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(PlayerLink, playerLinks, 1)
    zox_field_in(Children, childrens, 4)
    zox_field_in(RaycasterTarget, raycasterTargets, 2)
    zox_field_out(RaycasterResult, raycasterResults, 5)
    zox_field_in(WindowRaycasted, windowRaycasteds, 3)
    zox_field_out(WindowTarget, windowTargets, 7)
    zox_field_out(ClickingEntity, clickingEntitys, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(PlayerLink, playerLinks, playerLink)
        const ecs_entity_t player = playerLink->value;
        if (!player || !zox_has(player, CanvasLink)) continue;
        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
        if (!canvas) continue;
        zox_field_i(Children, childrens, children)
        unsigned char click_type = 0;
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t zevice = children->value[j];
            if (!zevice) continue;
            if (!zox_has(zevice, ZeviceButton)) continue;
            if (!zox_has(zevice, DeviceButtonType)) continue;
            const unsigned char button_type = zox_get_value(zevice, DeviceButtonType)
            if (button_type == zox_device_button_a) {
                const unsigned char disabled = zox_get_value(zevice, ZeviceDisabled)
                if (!disabled) {
                    const unsigned char click_value = zox_get_value(zevice, ZeviceButton)
                    if (devices_get_pressed_this_frame(click_value)) click_type = 1;
                    else if (devices_get_released_this_frame(click_value)) click_type = 2;
                }
            }
        }
        if (click_type == 0) continue;
        const unsigned char device_mode = zox_get_value(player, DeviceMode)
        zox_field_e()
        zox_field_i(RaycasterTarget, raycasterTargets, raycasterTarget)
        zox_field_i(WindowRaycasted, windowRaycasteds, windowRaycasted)
        zox_field_o(RaycasterResult, raycasterResults, raycasterResult)
        zox_field_o(ClickingEntity, clickingEntitys, clickingEntity)
        zox_field_o(WindowTarget, windowTargets, windowTarget)
        // used for virtual joysticks to see if a t arget was raycasted, todo: move to raycast system
        // raycasterResult->value = raycasterTarget->value || windowRaycasted->value;
        // released
        if (click_type == 1) {
            clickingEntity->value = raycasterTarget->value; // clicked
            on_element_clicked(world, player, clickingEntity->value);
        }
        if (click_type == 1) { // clicked
            if (windowRaycasted->value != windowTarget->value) {
                windowTarget->value = windowRaycasted->value;
                // zox_log(" > player window target [%lu]\n", windowTarget->value)
                // todo: set it's window to top
                // now set WindowToTop entity to windowTarget->value
                // then next in canvas system, reset windows layers to top of window stack
                zox_set(canvas, WindowToTop, { windowTarget->value })
            }
            if (zox_has(raycasterTarget->value, Dragable)) {
                unsigned char drag_mode = zox_drag_mode_none;
                if (device_mode == zox_device_mode_keyboardmouse) drag_mode = zox_drag_mode_mouse;
                else if (device_mode == zox_device_mode_touchscreen) drag_mode = zox_drag_mode_finger;
                set_element_dragged(world, player, raycasterTarget->value, drag_mode);
            }
        } else if (click_type == 2) { // released
            if (raycasterTarget->value == clickingEntity->value) on_element_released(world, player, raycasterTarget->value);
            clickingEntity->value = 0;
        }
    }
} zox_declare_system(DeviceClickSystem)

void ElementClickSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLink, deviceLinks, 1)
    zox_field_in(RaycasterTarget, raycasterTargets, 2)
    zox_field_in(WindowRaycasted, windowRaycasteds, 3)
    zox_field_out(RaycasterResult, raycasterResults, 4)
    zox_field_out(ClickingEntity, clickingEntitys, 5)
    zox_field_out(WindowTarget, windowTargets, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DeviceLink, deviceLinks, deviceLink)
        const ecs_entity_t player = zox_get_value(deviceLink->value, PlayerLink)
        const unsigned char device_mode = zox_get_value(player, DeviceMode)
        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
        zox_field_e()
        zox_field_i(RaycasterTarget, raycasterTargets, raycasterTarget)
        zox_field_i(WindowRaycasted, windowRaycasteds, windowRaycasted)
        zox_field_o(RaycasterResult, raycasterResults, raycasterResult)
        zox_field_o(ClickingEntity, clickingEntitys, clickingEntity)
        zox_field_o(WindowTarget, windowTargets, windowTarget)
        unsigned click_type = 0;
        if (zox_has(e, ZevicePointer)) {
            const unsigned char click_value = zox_get_value(e, ZevicePointer)
            if (devices_get_pressed_this_frame(click_value)) click_type = 1;
            else if (devices_get_released_this_frame(click_value)) click_type = 2;
        }
        if (zox_has(e, ZeviceButton)) {
            const DeviceButtonType *deviceButtonType = zox_get(e, DeviceButtonType)
            if (deviceButtonType->value == zox_device_button_a) {
                const ZeviceDisabled *zeviceDisabled = zox_get(e, ZeviceDisabled)
                if (!zeviceDisabled->value) {
                    const unsigned char click_value = zox_get_value(e, ZeviceButton)
                    if (devices_get_pressed_this_frame(click_value)) click_type = 1;
                    else if (devices_get_released_this_frame(click_value)) click_type = 2;
                }
            }
        }
        // used for virtual joysticks to see if a t arget was raycasted, todo: move to raycast system
        raycasterResult->value = raycasterTarget->value || windowRaycasted->value;
        // released
        if (click_type == 0) continue;
        else if (click_type == 1) {
            clickingEntity->value = raycasterTarget->value; // clicked
            on_element_clicked(world, player, clickingEntity->value);
        }
        if (click_type == 1) { // clicked
            if (windowRaycasted->value != windowTarget->value) {
                windowTarget->value = windowRaycasted->value;
                // zox_log(" > player window target [%lu]\n", windowTarget->value)
                // todo: set it's window to top
                // now set WindowToTop entity to windowTarget->value
                // then next in canvas system, reset windows layers to top of window stack
                zox_set(canvas, WindowToTop, { windowTarget->value })
            }
            if (zox_has(raycasterTarget->value, Dragable)) {
                unsigned char drag_mode = zox_drag_mode_none;
                if (device_mode == zox_device_mode_keyboardmouse) drag_mode = zox_drag_mode_mouse;
                else if (device_mode == zox_device_mode_touchscreen) drag_mode = zox_drag_mode_finger;
                set_element_dragged(world, player, raycasterTarget->value, drag_mode);
            }
        } else if (click_type == 2) { // released
            if (raycasterTarget->value == clickingEntity->value) on_element_released(world, player, raycasterTarget->value);
            clickingEntity->value = 0;
        }
    }
} zox_declare_system(ElementClickSystem)

        /*for (int j = 0; j < deviceLinks->length; j++) { // convert inputs to actions
            const ecs_entity_t device = deviceLinks->value[j];
            if (device_mode == zox_device_mode_keyboardmouse && zox_has(device, Mouse)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (!zox_has(zevice, ZevicePointer)) continue;
                    const unsigned char click_value = zox_get_value(zevice, ZevicePointer)
                    if (devices_get_pressed_this_frame(click_value)) click_type = 1;
                    else if (devices_get_released_this_frame(click_value)) click_type = 2;
                }
            } else if (device_mode == zox_device_mode_gamepad && zox_has(device, Gamepad)) {
                const Children *zevices = zox_get(device, Children)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (!zox_has(zevice, ZeviceButton)) continue;
                    const DeviceButtonType *deviceButtonType = zox_get(zevice, DeviceButtonType)
                    if (deviceButtonType->value == zox_device_button_a) {
                        const ZeviceDisabled *zeviceDisabled = zox_get(zevice, ZeviceDisabled)
                        if (!zeviceDisabled->value) {
                            const unsigned char click_value = zox_get_value(zevice, ZeviceButton)
                            if (devices_get_pressed_this_frame(click_value)) click_type = 1;
                            else if (devices_get_released_this_frame(click_value)) click_type = 2;
                        }
                        break;
                    }
                }
            } else if (device_mode == zox_device_mode_touchscreen && zox_has(device, Touchscreen)) {
                const Children *zevices = zox_get(device, Children)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (!zox_has(zevice, ZevicePointer)) continue;
                    const unsigned char click_value = zox_get_value(zevice, ZevicePointer)
                    if (devices_get_pressed_this_frame(click_value)) click_type = 1;
                    else if (devices_get_released_this_frame(click_value)) click_type = 2;
                }
            }
        }*/
