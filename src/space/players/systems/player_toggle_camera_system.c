void PlayerToggleCameraSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const CharacterLink *characterLinks = ecs_field(it, CharacterLink, 3);
    for (int i = 0; i < it->count; i++) {
        // todo: use player GameLink here
        const GameState *gameState = zox_get(local_game, GameState)
        if (gameState->value != zoxel_game_state_playing) continue;
        const CharacterLink *characterLink = &characterLinks[i];
        if (!characterLink->value) continue;
        if (zox_has(characterLink->value, DisableMovement)) {
            const DisableMovement *disableMovement = zox_get(characterLink->value, DisableMovement)
            if (disableMovement->value) continue;
        }
        unsigned char is_toggle_camera = 0;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Mouse)) {
                const Mouse *mouse = zox_get(device_entity, Mouse)
                if (mouse->middle.pressed_this_frame) is_toggle_camera = 1;
            } else if (zox_has(device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                if (keyboard->y.pressed_this_frame) is_toggle_camera = 1;
            } else if (zox_has(device_entity, Gamepad)) {
                const Children *zevices = zox_get(device_entity, Children)
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
        // if (is_toggle_camera) zoxel_log("   > toggling camera state  [%lu]\n", characterLink->value);
        if (is_toggle_camera) toggle_camera_mode(world);
        //toggle_camera_perspective(world, characterLink->value);
    }
} zox_declare_system(PlayerToggleCameraSystem)
