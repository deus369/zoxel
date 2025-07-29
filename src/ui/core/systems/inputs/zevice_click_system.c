void ZeviceClickSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DeviceLink)
    zox_sys_in(RaycasterTarget)
    zox_sys_in(WindowRaycasted)
    zox_sys_out(RaycasterResult)
    zox_sys_out(ClickingEntity)
    zox_sys_out(WindowTarget)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(DeviceLink, deviceLink)
        zox_sys_i(RaycasterTarget, raycasterTarget)
        zox_sys_i(WindowRaycasted, windowRaycasted)
        zox_sys_o(RaycasterResult, raycasterResult)
        zox_sys_o(ClickingEntity, clickingEntity)
        zox_sys_o(WindowTarget, windowTarget)
        const ecs_entity_t device = deviceLink->value;
        if (!zox_valid(device)) {
            zox_log_error(" device null from zevice [%lu]", it->entities[i])
            continue;
        }
        if (zox_gett_value(device, DeviceDisabled)) {
            continue;
        }
        const ecs_entity_t player = zox_get_value(device, PlayerLink)
        if (!player) {
            // zox_log(" ! device has null player [%lu]\n", device)
            continue;
        }
        const byte device_mode = zox_get_value(player, DeviceMode)
        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
        unsigned click_type = 0;
        if (zox_has(e, ZevicePointer)) {
            const byte click_value = zox_get_value(e, ZevicePointer)
            if (devices_get_pressed_this_frame(click_value)) click_type = 1;
            else if (devices_get_released_this_frame(click_value)) click_type = 2;
        }
        if (zox_has(e, ZeviceButton)) {
            const DeviceButtonType *deviceButtonType = zox_get(e, DeviceButtonType)
            if (deviceButtonType->value == zox_device_button_a) {
                const ZeviceDisabled *zeviceDisabled = zox_get(e, ZeviceDisabled)
                if (!zeviceDisabled->value) {
                    const byte click_value = zox_get_value(e, ZeviceButton)
                    if (devices_get_pressed_this_frame(click_value)) {
                        click_type = 1;
                    } else if (devices_get_released_this_frame(click_value)) {
                        click_type = 2;
                    }
                }
            }
        }
        // used for virtual joysticks to see if a t arget was raycasted, todo: move to raycast system
        raycasterResult->value = raycasterTarget->value || windowRaycasted->value;
        // released
        if (click_type == 0) {
            continue;
        } else if (click_type == 1) {
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
            if (raycasterTarget->value && zox_has(raycasterTarget->value, Dragable)) {
                byte drag_mode = zox_drag_mode_none;
                if (device_mode == zox_device_mode_keyboardmouse) drag_mode = zox_drag_mode_mouse;
                else if (device_mode == zox_device_mode_touchscreen) drag_mode = zox_drag_mode_finger;
                set_element_dragged(world, player, raycasterTarget->value, drag_mode);
            }
        } else if (click_type == 2) { // released
            if (raycasterTarget->value == clickingEntity->value) {
                on_element_released(world, player, raycasterTarget->value);
            }
            clickingEntity->value = 0;
        }
    }
} zox_declare_system(ZeviceClickSystem)
