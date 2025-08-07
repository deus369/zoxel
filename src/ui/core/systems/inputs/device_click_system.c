// todo: reuse parts of ZeviceClickSystem in this
// this is now from zevice
void DeviceClickSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DeviceDisabled)
    zox_sys_in(PlayerLink)
    zox_sys_in(RaycasterTarget)
    zox_sys_in(WindowRaycasted)
    zox_sys_in(Children)
    zox_sys_out(ClickingEntity)
    zox_sys_out(WindowTarget)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DeviceDisabled, deviceDisabled)
        zox_sys_i(PlayerLink, playerLink)
        zox_sys_i(RaycasterTarget, raycasterTarget)
        zox_sys_i(WindowRaycasted, windowRaycasted)
        zox_sys_i(Children, children)
        zox_sys_o(ClickingEntity, clickingEntity)
        zox_sys_o(WindowTarget, windowTarget)
        const entity player = playerLink->value;
        if (deviceDisabled->value) {
            continue;
        }
        if (!player) continue;
        if (!player || !zox_has(player, CanvasLink)) continue;
        const entity canvas = zox_get_value(player, CanvasLink)
        if (!canvas) continue;
        byte click_type = 0;
        for (int j = 0; j < children->length; j++) {
            const entity zevice = children->value[j];
            if (!zevice) continue;
            if (!zox_has(zevice, ZeviceButton)) continue;
            if (!zox_has(zevice, DeviceButtonType)) continue;
            const byte button_type = zox_get_value(zevice, DeviceButtonType)
            if (button_type == zox_device_button_a) {
                const byte disabled = zox_get_value(zevice, ZeviceDisabled)
                if (!disabled) {
                    const byte click_value = zox_get_value(zevice, ZeviceButton)
                    if (devices_get_pressed_this_frame(click_value)) click_type = 1;
                    else if (devices_get_released_this_frame(click_value)) click_type = 2;
                }
            }
        }
        if (click_type == 0) continue;
        const byte device_mode = zox_get_value(player, DeviceMode)
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
                byte drag_mode = zox_drag_mode_none;
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
