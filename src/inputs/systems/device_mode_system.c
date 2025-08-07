// System responsible for device switching for a DeviceUser
void DeviceModeSystem(iter *it) {
    zox_sys_world()
    if (!auto_switch_device) {
        return;
    }
    zox_sys_begin()
    zox_sys_in(DeviceLinks)
    zox_sys_in(DeviceMode)
    zox_sys_out(DeviceModeDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DeviceLinks, deviceLinks2)
        zox_sys_i(DeviceMode, deviceMode)
        zox_sys_o(DeviceModeDirty, deviceModeDirty)
        // first check if currently using selected inputs
        byte using_current_inputs = 0;
        for (int j = 0; j < deviceLinks2->length; j++) {
            const entity device = deviceLinks2->value[j];
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
        const byte old_device_mode = deviceMode->value;
        for (int j = 0; j < deviceLinks2->length; j++) {
            const entity device = deviceLinks2->value[j];
            if (!device) {
                continue;
            }
            if (deviceMode->value != zox_device_mode_keyboardmouse) {
                if (zox_has(device, Keyboard)) {
                    zox_geter(device, Keyboard, keyboard)
                    if (keyboard_is_any_input(keyboard)) {
                        deviceModeDirty->value = zox_device_mode_keyboardmouse;
                    } else {
                        continue;
                    }
                } else if (zox_has(device, Mouse)) {
                    if (mouse_is_any_input(world, device)) {
                        deviceModeDirty->value = zox_device_mode_keyboardmouse;
                    } else {
                        continue;
                    }
                }
            }
            if (deviceMode->value != zox_device_mode_gamepad) {
                if (zox_has(device, Gamepad)) {
                    if (gamepad_is_any_input(world, device)) {
                        deviceModeDirty->value = zox_device_mode_gamepad;
                    } else {
                        continue;
                    }
                }
            }
            if (deviceMode->value != zox_device_mode_touchscreen) {
                if (zox_has(device, Touchscreen)) {
                    if (touchscreen_is_any_input(world, device)) {
                        deviceModeDirty->value = zox_device_mode_touchscreen;
                    } else {
                        continue;
                    }
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
        // set player links here if dirty
        for (int j = 0; j < deviceLinks2->length; j++) {
            const entity device = deviceLinks2->value[j];
            if (!zox_valid(device)) {
                continue;
            }
            if (deviceModeDirty->value == zox_device_mode_keyboardmouse) {
                byte enabled = zox_has(device, Keyboard) || zox_has(device, Mouse);
                zox_set(device, DeviceDisabled, { !enabled });
            } else if (deviceModeDirty->value == zox_device_mode_gamepad) {
                byte enabled = zox_has(device, Gamepad);
                zox_set(device, DeviceDisabled, { !enabled });
            } else if (deviceModeDirty->value == zox_device_mode_touchscreen) {
                byte enabled = zox_has(device, Touchscreen);
                zox_set(device, DeviceDisabled ,{ !enabled });
            }
        }
        if (deviceModeDirty->value && old_device_mode != deviceModeDirty->value) {
            // zox_log_input(" + device mode switched to [%i] from [%i]", deviceModeDirty->value, deviceMode->value)
            if (deviceModeDirty->value == zox_device_mode_keyboardmouse) {
                zox_log_input("> device mode changed to [keyboardmouse]")
            } else if (deviceModeDirty->value == zox_device_mode_touchscreen) {
                zox_log_input("> device mode changed to [touchscreen]")
            } else if (deviceModeDirty->value == zox_device_mode_gamepad) {
                zox_log_input("> device mode changed to [gamepad]")
            }
        }
    }
} zox_declare_system(DeviceModeSystem)