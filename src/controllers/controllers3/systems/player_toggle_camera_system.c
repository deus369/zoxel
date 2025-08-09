void PlayerToggleCameraSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(PlayerState)
    zox_sys_in(DeviceLinks)
    zox_sys_in(GameLink)
    zox_sys_in(CharacterLink)
    zox_sys_in(CameraLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(PlayerState, playerState)
        zox_sys_i(DeviceLinks, deviceLinks)
        zox_sys_i(GameLink, gameLink)
        zox_sys_i(CharacterLink, characterLink)
        zox_sys_i(CameraLink, cameraLink)
        if (!zox_valid(gameLink->value) || !zox_valid(cameraLink->value)) {
            continue;
        }
        zox_geter_value(gameLink->value, GameState, byte, game_state)
        if (game_state != zox_game_playing) {
            continue;
        }
        byte is_toggle_camera = 0;
        byte is_toggle_freeroam = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device)) {
                continue;
            }
            if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                if (keyboard->f1.pressed_this_frame) {
                    is_toggle_camera = 1;
                } else if (keyboard->f2.pressed_this_frame) {
                    is_toggle_freeroam = 1;
                }
            } else if (zox_has(device, Gamepad)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceButton)) {
                        zox_geter(zevice_entity, ZeviceDisabled, zeviceDisabled)
                        if (zeviceDisabled->value) {
                            continue;
                        }
                        zox_geter(zevice_entity, DeviceButtonType, deviceButtonType)
                        if (deviceButtonType->value == zox_device_button_right_stick_push) {
                            zox_geter(zevice_entity, ZeviceButton, zeviceButton)
                            if (devices_get_pressed_this_frame(zeviceButton->value)) {
                                is_toggle_camera = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (is_toggle_camera && zox_valid(characterLink->value)) {
            if (playerState->value == zox_player_state_playing) {
                // hack to disable crosshair for different camera modes
                byte mode = toggle_camera_mode(world, cameraLink->value);

                byte is_first_person = mode == zox_camera_mode_first_person;
                zox_set(local_crosshair, RenderDisabled, { !is_first_person })
                // zox_log("> crosshair [%s]", is_crosshair_shown ? "visible" : "invisible")
            }
        } else if (is_toggle_freeroam) {
            if (playerState->value == zox_player_state_playing || playerState->value == zox_player_state_free_roam) {
                toggle_free_roam_camera(world, e);
                set_children_component_byte(world, local_menu_game, zox_id(RenderDisabled), playerState->value != zox_player_state_playing);
                // zox_set(local_crosshair, RenderDisabled, { playerState->value == zox_player_state_playing })
            }
        }
    }
} zoxd_system(PlayerToggleCameraSystem)