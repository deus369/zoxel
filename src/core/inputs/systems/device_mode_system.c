void DeviceModeSystem(ecs_iter_t *it) {
    const DeviceLinks *deviceLinks = ecs_field(it, DeviceLinks, 1);
    DeviceMode *deviceModes = ecs_field(it, DeviceMode, 2);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks2 = &deviceLinks[i];
        DeviceMode *deviceMode = &deviceModes[i];
        for (int j = 0; j < deviceLinks2->length; j++) {
            ecs_entity_t device_entity = deviceLinks2->value[j];
            if (ecs_has(world, device_entity, Keyboard)) {
                if (deviceMode->value == zox_device_mode_none || deviceMode->value == zox_device_mode_gamepad) {
                    const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                    if (keyboard_is_any_input(keyboard)) {
                        deviceMode->value = zox_device_mode_keyboardmouse;
                        zoxel_log(" > input mode changed to keyboardmouse [k]\n");
                    }
                }
            } else if (ecs_has(world, device_entity, Mouse)) {
                if (deviceMode->value == zox_device_mode_none || deviceMode->value == zox_device_mode_gamepad) {
                    const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                    if (mouse_is_any_input(mouse)) {
                        deviceMode->value = zox_device_mode_keyboardmouse;
                        zoxel_log(" > input mode changed to keyboardmouse [m]\n");
                    }
                }
            } else if (ecs_has(world, device_entity, Gamepad)) {
                if (deviceMode->value == zox_device_mode_none || deviceMode->value == zox_device_mode_keyboardmouse) {
                    const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                    if (gamepad_is_any_input(gamepad)) {
                        deviceMode->value = zox_device_mode_gamepad;
                        zoxel_log(" > input mode changed to gamepad\n");
                    }
                }
            }
        }
    }
}
zoxel_declare_system(DeviceModeSystem)