// #define zox_debug_log_device_mode_system

void DeviceModeSystem(ecs_iter_t *it) {
    const DeviceLinks *deviceLinks = ecs_field(it, DeviceLinks, 1);
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 2);
    DeviceModeDirty *deviceModeDirtys = ecs_field(it, DeviceModeDirty, 3);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks2 = &deviceLinks[i];
        const DeviceMode *deviceMode = &deviceModes[i];
        // first check if currently using selected inputs:
        unsigned char using_current_inputs = 0;
        for (int j = 0; j < deviceLinks2->length; j++) {
            ecs_entity_t device_entity = deviceLinks2->value[j];
            if (deviceMode->value == zox_device_mode_keyboardmouse) {
                if (ecs_has(world, device_entity, Keyboard)) {
                    const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                    if (keyboard_is_any_input(keyboard)) {
                        using_current_inputs = 1;
                        break;
                    }
                } else if (ecs_has(world, device_entity, Mouse)) {
                    const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                    if (mouse_is_any_input(mouse)) {
                        using_current_inputs = 1;
                        break;
                    }
                }
            } else if (deviceMode->value == zox_device_mode_gamepad) {
                if (ecs_has(world, device_entity, Gamepad)) {
                    const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                    if (gamepad_is_any_input(gamepad)) {
                        using_current_inputs = 1;
                        break;
                    }
                }
            } else if (deviceMode->value == zox_device_mode_touchscreen) {
                if (ecs_has(world, device_entity, Touchscreen)) {
                    const Touchscreen *touchscreen = ecs_get(world, device_entity, Touchscreen);
                    if (touchscreen_is_any_input(touchscreen)) {
                        using_current_inputs = 1;
                        break;
                    }
                }
            }
        }
        if (using_current_inputs) continue;
        DeviceModeDirty *deviceModeDirty = &deviceModeDirtys[i];
        #ifdef zox_debug_log_device_mode_system
            unsigned char old_device_mode = deviceMode->value;
        #endif
        for (int j = 0; j < deviceLinks2->length; j++) {
            ecs_entity_t device_entity = deviceLinks2->value[j];
            if (deviceMode->value != zox_device_mode_keyboardmouse) {
                if (ecs_has(world, device_entity, Keyboard)) {
                    const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                    if (keyboard_is_any_input(keyboard)) deviceModeDirty->value = zox_device_mode_keyboardmouse;
                    continue;
                } else if (ecs_has(world, device_entity, Mouse)) {
                    const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                    if (mouse_is_any_input(mouse)) {
                        deviceModeDirty->value = zox_device_mode_keyboardmouse;
                        // zoxel_log(" > input mode changed to keyboardmouse [m]\n");
                    }
                    continue;
                }
            }
            if (deviceMode->value != zox_device_mode_gamepad) {
                if (ecs_has(world, device_entity, Gamepad)) {
                    const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                    if (gamepad_is_any_input(gamepad)) deviceModeDirty->value = zox_device_mode_gamepad;
                    continue;
                }
            }
            if (deviceMode->value != zox_device_mode_touchscreen) {
                if (ecs_has(world, device_entity, Touchscreen)) {
                    const Touchscreen *touchscreen = ecs_get(world, device_entity, Touchscreen);
                    if (touchscreen_is_any_input(touchscreen)) deviceModeDirty->value = zox_device_mode_touchscreen;
                    continue;
                }
            }
        }
        #ifdef zox_debug_log_device_mode_system
            if (deviceModeDirty->value != 0 && old_device_mode != deviceModeDirty->value) {
                zoxel_log(" + device mode switched to [%i] from [%i]\n", deviceModeDirty->value, deviceMode->value);
                if (deviceModeDirty->value == zox_device_mode_keyboardmouse) {
                    zoxel_log("     == input mode changed to keyboardmouse ==\n");
                } else if (deviceModeDirty->value == zox_device_mode_touchscreen) {
                    zoxel_log("     == input mode changed to ouchscreen ==\n");
                } else if (deviceModeDirty->value == zox_device_mode_gamepad) {
                    zoxel_log("     == input mode changed to gamepad ==\n");
                }
            }
        #endif
    }
} zox_declare_system(DeviceModeSystem)