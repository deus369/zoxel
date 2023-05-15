void DeviceModeSystem(ecs_iter_t *it) {
    unsigned char did_update = 0;
    const DeviceLinks *deviceLinks = ecs_field(it, DeviceLinks, 1);
    DeviceMode *deviceModes = ecs_field(it, DeviceMode, 2);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks2 = &deviceLinks[i];
        DeviceMode *deviceMode = &deviceModes[i];
        for (int j = 0; j < deviceLinks2->length; j++) {
            ecs_entity_t device_entity = deviceLinks2->value[j];
            if (ecs_has(world, device_entity, Keyboard)) {
                if (deviceMode->value != zox_device_mode_keyboardmouse) { // == zox_device_mode_none || deviceMode->value == zox_device_mode_gamepad) {
                    const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                    if (keyboard_is_any_input(keyboard)) {
                        deviceMode->value = zox_device_mode_keyboardmouse;
                        did_update = 1;
                        zoxel_log(" > input mode changed to keyboardmouse [k]\n");
                    }
                }
            } else if (ecs_has(world, device_entity, Mouse)) {
                if (deviceMode->value != zox_device_mode_keyboardmouse) { //  == zox_device_mode_none || deviceMode->value == zox_device_mode_gamepad) {
                    const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                    if (mouse_is_any_input(mouse)) {
                        deviceMode->value = zox_device_mode_keyboardmouse;
                        did_update = 1;
                        zoxel_log(" > input mode changed to keyboardmouse [m]\n");
                    }
                }
            } else if (ecs_has(world, device_entity, Gamepad)) {
                if (deviceMode->value != zox_device_mode_gamepad) { //  == zox_device_mode_none || deviceMode->value == zox_device_mode_keyboardmouse) {
                    const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                    if (gamepad_is_any_input(gamepad)) {
                        deviceMode->value = zox_device_mode_gamepad;
                        did_update = 1;
                        zoxel_log(" > input mode changed to gamepad\n");
                    }
                }
            } else if (ecs_has(world, device_entity, Touchscreen)) {
                if (deviceMode->value != zox_device_mode_touchscreen) { // == zox_device_mode_none || deviceMode->value == zox_device_mode_keyboardmouse) {
                    const Touchscreen *touchscreen = ecs_get(world, device_entity, Touchscreen);
                    if (touchscreen_is_any_input(touchscreen)) {
                        deviceMode->value = zox_device_mode_touchscreen;
                        did_update = 1;
                        zoxel_log(" > input mode changed to touschreen\n");
                    }
                }
            }
        }
    }
    if (!did_update) {
        ecs_query_skip(it);
    }/* else {
        zoxel_log(" ===+++ updated device mode +++===\n");
    }*/
}
zox_declare_system(DeviceModeSystem)