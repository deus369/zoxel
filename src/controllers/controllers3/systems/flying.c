void PlayerFlySystem(ecs_iter_t *it) {
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(DeviceLinks);
    zox_sys_in(DeviceMode);
    zox_sys_in(CharacterLink);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(CharacterLink, characterLink);
        zox_sys_i(DeviceLinks, deviceLinks);
        zox_sys_i(DeviceMode, deviceMode);

        const ecs_entity_t character = characterLink->value;
        if (!zox_valid(character) || !zox_has(character, Character3)) {
            continue;
        }

        zox_geter(character, DisableMovement, disableMovement)
        if (disableMovement->value) {
            continue;
        }

        zox_geter_value(character, FlyMode, byte, flying);
        if (!flying) {
            continue;
        }

        float input = 0;

        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device) || zox_gett_value(device, DeviceDisabled)) {
                continue;
            }
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device, Keyboard)) {
                zox_geter(device, Keyboard, keyboard)
                if (keyboard->q.is_pressed) input -= fly_run_acc;
                if (keyboard->e.is_pressed) input += fly_run_acc;
            }
        }

        if (input) {
            zox_get_muter(character, Acceleration3D, acc);
            acc->value.y += input;
        }
    }
} zoxd_system(PlayerFlySystem)