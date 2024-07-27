void ZeviceClickSystem(ecs_iter_t *it) {
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
} zox_declare_system(ZeviceClickSystem)
