// #define zox_debug_log_device_mode_system
void DeviceModeSystem(ecs_iter_t *it) {
    if (!auto_switch_device) return;
    zox_field_in(DeviceLinks, deviceLinks, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_out(DeviceModeDirty, deviceModeDirtys, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DeviceLinks, deviceLinks, deviceLinks2)
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        // first check if currently using selected inputs:
        unsigned char using_current_inputs = 0;
        for (int j = 0; j < deviceLinks2->length; j++) {
            const ecs_entity_t device = deviceLinks2->value[j];
            if (!device) continue;
            if (deviceMode->value == zox_device_mode_keyboardmouse) {
                if (zox_has(device, Keyboard)) {
                    const Keyboard *keyboard = zox_get(device, Keyboard)
                    if (keyboard_is_any_input(keyboard)) {
                        using_current_inputs = 1;
                        break;
                    }
                } else if (zox_has(device, Mouse)) {
                    if (mouse_is_any_input(world, device)) {
                        using_current_inputs = 1;
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
                        break;
                    }
                }
            }
        }
        if (using_current_inputs) continue;
        zox_field_o(DeviceModeDirty, deviceModeDirtys, deviceModeDirty)
#ifdef zox_debug_log_device_mode_system
        unsigned char old_device_mode = deviceMode->value;
#endif
        for (int j = 0; j < deviceLinks2->length; j++) {
            const ecs_entity_t device = deviceLinks2->value[j];
            if (deviceMode->value != zox_device_mode_keyboardmouse) {
                if (zox_has(device, Keyboard)) {
                    const Keyboard *keyboard = zox_get(device, Keyboard)
                    if (keyboard_is_any_input(keyboard)) deviceModeDirty->value = zox_device_mode_keyboardmouse;
                    continue;
                } else if (zox_has(device, Mouse)) {
                    if (mouse_is_any_input(world, device)) {
                        deviceModeDirty->value = zox_device_mode_keyboardmouse;
                        // zoxel_log(" > input mode changed to keyboardmouse [m]\n");
                    }
                    continue;
                }
            }
            if (deviceMode->value != zox_device_mode_gamepad) {
                if (zox_has(device, Gamepad)) {
                    if (gamepad_is_any_input(world, device)) deviceModeDirty->value = zox_device_mode_gamepad;
                    continue;
                }
            }
            if (deviceMode->value != zox_device_mode_touchscreen) {
                if (zox_has(device, Touchscreen)) {
                    if (touchscreen_is_any_input(world, device)) deviceModeDirty->value = zox_device_mode_touchscreen;
                    continue;
                }
            }
        }
#ifdef zox_debug_log_device_mode_system
        if (deviceModeDirty->value && old_device_mode != deviceModeDirty->value) {
            zox_log(" + device mode switched to [%i] from [%i]\n", deviceModeDirty->value, deviceMode->value)
            if (deviceModeDirty->value == zox_device_mode_keyboardmouse) zox_log(" => input mode changed to keyboardmouse ==\n")
            else if (deviceModeDirty->value == zox_device_mode_touchscreen) zox_log(" => input mode changed to ouchscreen ==\n")
            else if (deviceModeDirty->value == zox_device_mode_gamepad) zox_log(" => input mode changed to gamepad ==\n")
        }
#endif
    }
} zox_declare_system(DeviceModeSystem)
