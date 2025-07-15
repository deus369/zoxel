// #define zox_log_jumping
void Player3DJumpSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_in(CharacterLink, characterLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CharacterLink, characterLinks, characterLink)
        const ecs_entity_t character = characterLink->value;
        if (!zox_valid(character) || !zox_has(character, Character3D)) {
            continue;
        }
        const DisableMovement *disableMovement = zox_get(character, DisableMovement)
        if (disableMovement->value) {
            continue;
        }
        zox_geter(character, Grounded, grounded)
        if (!grounded->value) {
            continue;
        }
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        byte is_jump_triggered = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) {
                continue;
            }
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device, Keyboard)) {
                zox_geter(device, Keyboard, keyboard)
                if (keyboard->space.is_pressed) {
                    is_jump_triggered = 1;
                }
            } else if (deviceMode->value == zox_device_mode_gamepad && zox_has(device, Gamepad)) {
                const Children *zevices = zox_get(device, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceButton)) {
                        const DeviceButtonType *deviceButtonType = zox_get(zevice_entity, DeviceButtonType)
                        if (deviceButtonType->value == zox_device_button_a) {
                            zox_geter(zevice_entity, ZeviceDisabled, zeviceDisabled)
                            if (zeviceDisabled->value) {
                                continue;
                            }
                            zox_geter(zevice_entity, ZeviceButton, zeviceButton)
                            if (devices_get_is_pressed(zeviceButton->value)) {
                                is_jump_triggered = 1;
                            }
                            break;
                        }
                    }
                }
            }
        }
        if (!is_jump_triggered) {
            continue;
        }
        if (!zox_gett_value(character, Jump)) {
            zox_set(character, Jump, { jump_timing })
#ifdef zox_log_jumping
            zox_log(" > in air [%lu] again (%f)\n", character, zox_current_time)
#endif
        }
    }
} zox_declare_system(Player3DJumpSystem)