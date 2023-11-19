void PlayerPauseSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    for (int i = 0; i < it->count; i++) {
        unsigned char did_toggle_pause = 0;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                if (keyboard->escape.pressed_this_frame || keyboard->enter.pressed_this_frame) {
                    did_toggle_pause = 1;
                    break;
                }
            } else if (zox_has(device_entity, Gamepad)) {
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceButton)) {
                        const ZeviceDisabled *zeviceDisabled = zox_get(zevice_entity, ZeviceDisabled)
                        if (zeviceDisabled->value) continue;
                        const DeviceButtonType *deviceButtonType = zox_get(zevice_entity, DeviceButtonType)
                        if (deviceButtonType->value == zox_device_button_start || deviceButtonType->value == zox_device_button_select) {
                            const ZeviceButton *zeviceButton = zox_get(zevice_entity, ZeviceButton)
                            if (devices_get_pressed_this_frame(zeviceButton->value)) did_toggle_pause = 1;
                        }
                    }
                }
            }
        }
        if (did_toggle_pause) toggle_pause_ui(world, it->entities[i]);
        // zoxel_log(" > alive ui? %s\n", ecs_is_alive(world, pause_ui) ? "alive" : "dead");
    }
} zox_declare_system(PlayerPauseSystem)
