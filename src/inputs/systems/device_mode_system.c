// #define zox_debug_log_device_mode_system
void DeviceModeSystem(ecs_iter_t *it) {
    zox_field_world()
    if (!auto_switch_device) {
        return;
    }
    zox_field_in(DeviceLinks, deviceLinks, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_out(DeviceModeDirty, deviceModeDirtys, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DeviceLinks, deviceLinks, deviceLinks2)
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        // first check if currently using selected inputs
        byte using_current_inputs = 0;
        for (int j = 0; j < deviceLinks2->length; j++) {
            const ecs_entity_t device = deviceLinks2->value[j];
            if (!device) {
                continue;
            }
            if (deviceMode->value == zox_device_mode_keyboardmouse) {
                if (zox_has(device, Keyboard)) {
                    zox_geter(device, Keyboard, keyboard)
                    if (keyboard_is_any_input(keyboard)) {
                        // zox_log(" > using current keyboard\n")
                        using_current_inputs = 1;
                        break;
                    }
                } else if (zox_has(device, Mouse)) {
                    if (mouse_is_any_input(world, device)) {
                        using_current_inputs = 1;
                        // zox_log(" > using current mouse\n")
                        break;
                    }
                }
            } else if (deviceMode->value == zox_device_mode_gamepad) {
                if (zox_has(device, Gamepad)) {
                    if (gamepad_is_any_input(world, device)) {
                        using_current_inputs = 1;
                        break;
                    }
                }
            } else if (deviceMode->value == zox_device_mode_touchscreen) {
                if (zox_has(device, Touchscreen)) {
                    if (touchscreen_is_any_input(world, device)) {
                        using_current_inputs = 1;
                        // zox_log(" > using current touchscreen\n")
                        break;
                    }
                }
            }
        }
        if (using_current_inputs) {
            continue;
        }
        zox_field_o(DeviceModeDirty, deviceModeDirtys, deviceModeDirty)
        const byte old_device_mode = deviceMode->value;
        for (int j = 0; j < deviceLinks2->length; j++) {
            const ecs_entity_t device = deviceLinks2->value[j];
            if (!device) continue;
            if (deviceMode->value != zox_device_mode_keyboardmouse) {
                if (zox_has(device, Keyboard)) {
                    zox_geter(device, Keyboard, keyboard)
                    if (keyboard_is_any_input(keyboard)) deviceModeDirty->value = zox_device_mode_keyboardmouse;
                    else continue;
                } else if (zox_has(device, Mouse)) {
                    if (mouse_is_any_input(world, device)) deviceModeDirty->value = zox_device_mode_keyboardmouse;
                    else continue;
                }
            }
            if (deviceMode->value != zox_device_mode_gamepad) {
                if (zox_has(device, Gamepad)) {
                    if (gamepad_is_any_input(world, device)) deviceModeDirty->value = zox_device_mode_gamepad;
                    else continue;
                }
            }
            if (deviceMode->value != zox_device_mode_touchscreen) {
                if (zox_has(device, Touchscreen)) {
                    if (touchscreen_is_any_input(world, device)) deviceModeDirty->value = zox_device_mode_touchscreen;
                    else continue;
                }
            }
            if (deviceModeDirty->value != 0) {
                // zox_log("device mode changing: %i to %i\n", deviceMode->value, DeviceModeDirty->value)
                break;
            }
        }
        if (deviceModeDirty->value == 0) {
            continue;
        }
        zox_field_e()
        // set player links here if dirty
        for (int j = 0; j < deviceLinks2->length; j++) {
            const ecs_entity_t device = deviceLinks2->value[j];
            if (!device) continue;
            if (deviceModeDirty->value == zox_device_mode_keyboardmouse) {
                if (zox_has(device, Keyboard) || zox_has(device, Mouse)) {
                    zox_set(device, PlayerLink, { e })
                } else {
                    zox_set(device, PlayerLink, { 0 })
                }
            } else if (deviceModeDirty->value == zox_device_mode_gamepad) {
                if (zox_has(device, Gamepad)) {
                    zox_set(device, PlayerLink, { e })
                } else {
                    zox_set(device, PlayerLink, { 0 })
                }
            } else if (deviceModeDirty->value == zox_device_mode_touchscreen) {
                if (zox_has(device, Touchscreen)) {
                    zox_set(device, PlayerLink, { e })
                } else {
                    zox_set(device, PlayerLink, { 0 })
                }
            }
        }
        if (deviceModeDirty->value && old_device_mode != deviceModeDirty->value) {
            // zox_log_input(" + device mode switched to [%i] from [%i]", deviceModeDirty->value, deviceMode->value)
            if (deviceModeDirty->value == zox_device_mode_keyboardmouse) zox_log_input("> device mode changed to [keyboardmouse]")
            else if (deviceModeDirty->value == zox_device_mode_touchscreen) zox_log_input("> device mode changed to [touchscreen]")
            else if (deviceModeDirty->value == zox_device_mode_gamepad) zox_log_input("> device mode changed to [gamepad]")
        }
    }
} zox_declare_system(DeviceModeSystem)