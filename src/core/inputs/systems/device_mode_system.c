// #define zox_debug_log_device_mode_system

void DeviceModeSystem(ecs_iter_t *it) {
    unsigned char did_update = 0;
    const DeviceLinks *deviceLinks = ecs_field(it, DeviceLinks, 1);
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 2);
    DeviceModeDirty *deviceModeDirtys = ecs_field(it, DeviceModeDirty, 3);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks2 = &deviceLinks[i];
        const DeviceMode *deviceMode = &deviceModes[i];
        DeviceModeDirty *deviceModeDirty = &deviceModeDirtys[i];
        unsigned char old_device_mode = deviceMode->value;
        for (int j = 0; j < deviceLinks2->length; j++) {
            ecs_entity_t device_entity = deviceLinks2->value[j];
            if (deviceMode->value != zox_device_mode_keyboardmouse) {
                if (ecs_has(world, device_entity, Keyboard)) {
                    const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                    if (keyboard_is_any_input(keyboard)) {
                        deviceModeDirty->value = zox_device_mode_keyboardmouse;
                        // zoxel_log(" > input mode changed to keyboardmouse [k]\n");
                    }
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
                    if (gamepad_is_any_input(gamepad)) {
                        deviceModeDirty->value = zox_device_mode_gamepad;
                    }
                    continue;
                }
            }
            if (deviceMode->value != zox_device_mode_touchscreen) {
                if (ecs_has(world, device_entity, Touchscreen)) {
                    const Touchscreen *touchscreen = ecs_get(world, device_entity, Touchscreen);
                    if (touchscreen_is_any_input(touchscreen)) {
                        deviceModeDirty->value = zox_device_mode_touchscreen;
                    }
                    continue;
                }
            }
        }
        if (old_device_mode != deviceModeDirty->value) did_update = 1;
        #ifdef zox_debug_log_device_mode_system
            if (did_update) {
                zoxel_log(" + device mode switched [%i] from [%i]\n", deviceModeDirty->value, deviceMode->value);
                if (deviceModeDirty->value == zox_device_mode_keyboardmouse) {
                    zoxel_log(" == input mode changed to keyboardmouse ==\n");
                } else if (deviceModeDirty->value == zox_device_mode_touchscreen) {
                    zoxel_log(" == input mode changed to ouchscreen ==\n");
                } else if (deviceModeDirty->value == zox_device_mode_gamepad) {
                    zoxel_log(" == input mode changed to gamepad ==\n");
                }
            }
        #endif
    }
    if (!did_update) {
        // ecs_query_skip(it);
    }
}
zox_declare_system(DeviceModeSystem)