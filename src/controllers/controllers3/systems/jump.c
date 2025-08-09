// #define zox_log_jumping

// todo: it shouldnt use setters
//      - we should get player data from a Character!
void Player3DJumpSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DeviceLinks)
    zox_sys_in(DeviceMode)
    zox_sys_in(CharacterLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(CharacterLink, characterLink)
        zox_sys_i(DeviceMode, deviceMode)
        zox_sys_i(DeviceLinks, deviceLinks)

        const ecs_entity_t character = characterLink->value;
        if (!zox_valid(character) || !zox_has(character, Character3)) {
            continue;
        }

        zox_geter(character, DisableMovement, disableMovement);
        if (disableMovement->value) {
            continue;
        }

        zox_geter_value(character, JumpState, byte, jump_state);
        if (jump_state != zox_dirty_none) {
            continue;
        }

        zox_geter_value(character, CanJump, byte, can_jump);
        if (!can_jump) { // || can_jump >= jump_cooldown_state) {
            continue;
        }

        byte is_jump_triggered = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device) || zox_gett_value(device, DeviceDisabled)) {
                continue;
            }
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device, Keyboard)) {
                zox_geter(device, Keyboard, keyboard)
                if (keyboard->space.is_pressed) {
                    is_jump_triggered = 1;
                }
            } else if (deviceMode->value == zox_device_mode_gamepad && zox_has(device, Gamepad)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceButton)) {
                        zox_geter(zevice_entity, DeviceButtonType, deviceButtonType)
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
            zox_set(character, JumpState, { zox_dirty_trigger });
#ifdef zox_log_jumping
            zox_log("+ %s jumping (%f)", zox_get_name(character), zox_current_time);
#endif
        }
    }
} zoxd_system(Player3DJumpSystem)