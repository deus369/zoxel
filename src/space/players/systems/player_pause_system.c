void PlayerPauseSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    for (int i = 0; i < it->count; i++) {
        unsigned char did_toggle_pause = 0;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Keyboard)) {
                const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                if (keyboard->escape.pressed_this_frame || keyboard->enter.pressed_this_frame) {
                    did_toggle_pause = 1;
                    break;
                }
            } else if (ecs_has(world, device_entity, Gamepad)) {
                /*const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                if (gamepad->start.pressed_this_frame || gamepad->select.pressed_this_frame) {
                    did_toggle_pause = 1;
                    break;
                }*/
                const Children *device_buttons = ecs_get(world, device_entity, Children);
                for (int k = 0; k < device_buttons->length; k++) {
                    ecs_entity_t device_button_entity = device_buttons->value[k];
                    if (ecs_has(world, device_button_entity, DeviceButton)) {
                        const DeviceButtonType *deviceButtonType = ecs_get(world, device_button_entity, DeviceButtonType);
                        if (deviceButtonType->value == zox_device_button_start || deviceButtonType->value == zox_device_button_select) {
                            const DeviceButton *deviceButton = ecs_get(world, device_button_entity, DeviceButton);
                            if (devices_get_pressed_this_frame(deviceButton->value)) did_toggle_pause = 1;
                            // break;
                        }
                    }
                }
            }
        }
        if (did_toggle_pause) toggle_pause_ui(world, it->entities[i]);
        // zoxel_log(" > alive ui? %s\n", ecs_is_alive(world, pause_ui) ? "alive" : "dead");
    }
} zox_declare_system(PlayerPauseSystem)