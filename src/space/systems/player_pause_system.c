void PlayerPauseSystem(ecs_iter_t *it) {
    byte did_toggle_pause = 0; // for now, no support for different games at once
    ecs_entity_t triggering_player = 0;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DeviceLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DeviceLinks, deviceLinks)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device) || zox_gett_value(device, DeviceDisabled)) {
                continue;
            }
            if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                if (keyboard->escape.pressed_this_frame ||
                    (!keyboard->left_alt.is_pressed && !keyboard->right_alt.is_pressed && keyboard->enter.pressed_this_frame)) {
                    did_toggle_pause = 1;
                    break;
                }
            } else if (zox_has(device, Gamepad)) {
                const Children *zevices = zox_get(device, Children)
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
        if (did_toggle_pause) {
            triggering_player = it->entities[i];
            break;
        }
    }
    if (did_toggle_pause) toggle_pause_ui(world, triggering_player);
} zox_declare_system(PlayerPauseSystem)
