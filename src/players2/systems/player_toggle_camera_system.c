void PlayerToggleCameraSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(CharacterLink, characterLinks, 2)
    zox_field_in(GameLink, gameLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(GameLink, gameLinks, gameLink)
        if (!gameLink->value) continue;
        const unsigned char game_state = zox_get_value(gameLink->value, GameState)
        if (game_state != zox_game_playing) continue;
        zox_field_i(CharacterLink, characterLinks, characterLink)
        // if no character link
        if (!characterLink->value) continue;
        // if disabled
        if (zox_has(characterLink->value, DisableMovement) && zox_gett(characterLink->value, DisableMovement)) continue;
        unsigned char is_toggle_camera = 0;
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) continue;
            if (zox_has(device, Mouse)) {
                /*const Mouse *mouse = zox_get(device, Mouse)
                if (mouse->middle.pressed_this_frame) is_toggle_camera = 1;*/
            } else if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                if (keyboard->y.pressed_this_frame) is_toggle_camera = 1;
            } else if (zox_has(device, Gamepad)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceButton)) {
                        const ZeviceDisabled *zeviceDisabled = zox_get(zevice_entity, ZeviceDisabled)
                        if (zeviceDisabled->value) continue;
                        const DeviceButtonType *deviceButtonType = zox_get(zevice_entity, DeviceButtonType)
                        if (deviceButtonType->value == zox_device_button_right_stick_push) {
                            const ZeviceButton *zeviceButton = zox_get(zevice_entity, ZeviceButton)
                            if (devices_get_pressed_this_frame(zeviceButton->value)) is_toggle_camera = 1;
                        }
                    }
                }
            }
        }
        if (is_toggle_camera) {
            toggle_camera_mode(world);
            // hack to disable crosshair for different camera modes
            zox_set(local_crosshair, RenderDisabled, { camera_mode != zox_camera_mode_first_person })
        }
    }
} zox_declare_system(PlayerToggleCameraSystem)
