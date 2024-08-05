const int particleSpawnCount = 266;
const float debug_rotation_speed = 12;
const float debug_rotation_addition = 5;
extern ecs_entity_t local_character3D; // change to devicece links and use e!

// quality of life
void QolShortcutsSystem(ecs_iter_t *it) {
    unsigned char is_toggle_fullscreen = 0;
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        unsigned char is_shift_action_left = 0;
        unsigned char is_shift_action_right = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) continue;
            if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                if (keyboard->f11.pressed_this_frame) {
                    is_toggle_fullscreen = 1;
                    // zox_log(" > toggled fullscreen mode\n")
                } else if (keyboard->f10.pressed_this_frame) {
                    is_render_fog = !is_render_fog;
                    // zox_log(" > set fog [%i]\n", is_render_fog)
                } else if (keyboard->f9.pressed_this_frame) {
                    toggle_free_roam_camera(world, e);
                    // zox_log(" > set camera free roam [%i]\n", camera_mode)
                }
                else if (keyboard->e.pressed_this_frame) save_player_e(world, e);
                else if (keyboard->r.pressed_this_frame) load_player_e(world, e);

                else if (keyboard->_1.pressed_this_frame) set_player_action(world, e, 0);
                else if (keyboard->_2.pressed_this_frame) set_player_action(world, e, 1);
                else if (keyboard->_3.pressed_this_frame) set_player_action(world, e, 2);
                else if (keyboard->_4.pressed_this_frame) set_player_action(world, e, 3);
                else if (keyboard->_5.pressed_this_frame) set_player_action(world, e, 4);
                else if (keyboard->_6.pressed_this_frame) set_player_action(world, e, 5);
                else if (keyboard->_7.pressed_this_frame) set_player_action(world, e, 6);
                else if (keyboard->_8.pressed_this_frame) set_player_action(world, e, 7);

            // Actio Switching!!

            } else if (zox_has(device, Mouse)) {
                /*const Mouse *mouse = zox_get(device, Mouse)
                if (mouse->wheel.y > 0) is_shift_action_right = 1;
                else if (mouse->wheel.y < 0) is_shift_action_left = 1;*/
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceWheel)) {
                        const int2 wheel = zox_get_value(zevice_entity, ZeviceWheel)
                        if (wheel.y > 0) is_shift_action_right = 1;
                        else if (wheel.y < 0) is_shift_action_left = 1;
                    }
                }
            } else if (zox_has(device, Gamepad)) {
                const Children *zevices = zox_get(device, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceButton)) {
                        const ZeviceDisabled *zeviceDisabled = zox_get(zevice_entity, ZeviceDisabled)
                        if (zeviceDisabled->value) continue;
                        const unsigned char device_button_type = zox_get_value(zevice_entity, DeviceButtonType)
                        const unsigned char zevice_button = zox_get_value(zevice_entity, ZeviceButton)
                        if (device_button_type == zox_device_button_lb) {
                            if (devices_get_pressed_this_frame(zevice_button)) is_shift_action_left = 1;
                        } else if (device_button_type == zox_device_button_rb) {
                            if (devices_get_pressed_this_frame(zevice_button)) is_shift_action_right = 1;
                        }
                        const unsigned char real_button_index = zox_get_value(zevice_entity, RealButtonIndex)
                        if (real_button_index == zox_device_button_dpad_left) {
                            if (devices_get_pressed_this_frame(zevice_button)) is_shift_action_left = 1;
                        } else if (real_button_index == zox_device_button_dpad_right) {
                            if (devices_get_pressed_this_frame(zevice_button)) is_shift_action_right = 1;
                        }
                    }
                }
            }
        }

        if (is_shift_action_left) player_action_ui_move(world, e, -1);
        else if (is_shift_action_right) player_action_ui_move(world, e, 1);
    }
    if (is_toggle_fullscreen) sdl_toggle_fullscreen(world, main_app);
} zox_declare_system(QolShortcutsSystem)

// toggle player connected application
/*if ((keyboard->left_alt.is_pressed || keyboard->right_alt.is_pressed) && keyboard->enter.pressed_this_frame) is_toggle_fullscreen = 1;
else */
