#ifdef zoxm_actions

void ActionsShortcutSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DeviceLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(DeviceLinks, deviceLinks)
        byte is_shift_action_left = 0;
        byte is_shift_action_right = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device)) {
                continue;
            }
            if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                if (keyboard->_1.pressed_this_frame) {
                    set_player_action(world, e, 0);
                } else if (keyboard->_2.pressed_this_frame) set_player_action(world, e, 1);
                else if (keyboard->_3.pressed_this_frame) set_player_action(world, e, 2);
                else if (keyboard->_4.pressed_this_frame) set_player_action(world, e, 3);
                else if (keyboard->_5.pressed_this_frame) set_player_action(world, e, 4);
                else if (keyboard->_6.pressed_this_frame) set_player_action(world, e, 5);
                else if (keyboard->_7.pressed_this_frame) set_player_action(world, e, 6);
                else if (keyboard->_8.pressed_this_frame) set_player_action(world, e, 7);
            } else if (zox_has(device, Mouse)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceWheel)) {
                        const int2 wheel = zox_get_value(zevice_entity, ZeviceWheel)
                        if (wheel.y > 0) {
                            is_shift_action_right = 1;
                        } else if (wheel.y < 0) {
                            is_shift_action_left = 1;
                        }
                    }
                }
            } else if (zox_has(device, Gamepad)) {
                const Children *zevices = zox_get(device, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceButton)) {
                        const ZeviceDisabled *zeviceDisabled = zox_get(zevice_entity, ZeviceDisabled)
                        if (zeviceDisabled->value) {
                            continue;
                        }
                        const byte device_button_type = zox_get_value(zevice_entity, DeviceButtonType)
                        const byte zevice_button = zox_get_value(zevice_entity, ZeviceButton)
                        if (device_button_type == zox_device_button_lb) {
                            if (devices_get_pressed_this_frame(zevice_button)) {
                                is_shift_action_left = 1;
                            }
                        } else if (device_button_type == zox_device_button_rb) {
                            if (devices_get_pressed_this_frame(zevice_button)) {
                                is_shift_action_right = 1;
                            }
                        }
                        const byte real_button_index = zox_get_value(zevice_entity, RealButtonIndex)
                        if (real_button_index == zox_device_button_dpad_left) {
                            if (devices_get_pressed_this_frame(zevice_button)) {
                                is_shift_action_left = 1;
                            }
                        } else if (real_button_index == zox_device_button_dpad_right) {
                            if (devices_get_pressed_this_frame(zevice_button)) {
                                is_shift_action_right = 1;
                            }
                        }
                    }
                }
            }
        }
        if (is_shift_action_left) {
            player_action_ui_move(world, e, -1);
        } else if (is_shift_action_right) {
            player_action_ui_move(world, e, 1);
        }
    }
} zoxd_system(ActionsShortcutSystem)

#endif
