// handles changes in device mode state
void DeviceModeResponseSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceMode, deviceModes, 1)
    zox_field_in(DeviceModeDirty, deviceModeDirtys, 2)
    zox_field_in(GameLink, gameLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(GameLink, gameLinks, gameLink)
        if (!gameLink->value) continue;
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        zox_field_i(DeviceModeDirty, deviceModeDirtys, deviceModeDirty)
        const unsigned char game_state = zox_get_value(gameLink->value, GameState)
        if (deviceModeDirty->value != 0 && deviceModeDirty->value != deviceMode->value) {
            zox_field_e()
            const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
            // handle previous mode
            if (deviceMode->value == zox_device_mode_touchscreen) {
                if (game_state == zox_game_playing) dispose_in_game_ui_touch(world);
            }
            // handle new mode
            if (deviceModeDirty->value == zox_device_mode_gamepad) {
                raycaster_select_first_button(world, e, canvas);
            } else if (deviceModeDirty->value == zox_device_mode_keyboardmouse) {
                raycaster_select_element(world, e, 0);
            } else if (deviceModeDirty->value == zox_device_mode_touchscreen) {
                if (game_state == zox_game_playing) spawn_in_game_ui_touch(world, canvas);
            }
        }
    }
} zox_declare_system(DeviceModeResponseSystem)
