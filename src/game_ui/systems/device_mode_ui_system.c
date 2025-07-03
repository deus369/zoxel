// handles changes in device mode state
void DeviceModeUISystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(DeviceMode, deviceModes, 1)
    zox_field_in(DeviceModeDirty, deviceModeDirtys, 2)
    zox_field_in(GameLink, gameLinks, 3)
    zox_field_in(CanvasLink, canvasLinks, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DeviceModeDirty, deviceModeDirtys, deviceModeDirty)
        if (deviceModeDirty->value == 0) {
            return;
        }
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        if (deviceModeDirty->value == deviceMode->value) {
            return;
        }
        zox_field_e()
        zox_field_i(GameLink, gameLinks, gameLink)
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        const ecs_entity_t canvas = canvasLink->value; // zox_get_value(e, CanvasLink)
        byte game_state = 0;
        if (gameLink->value) {
            game_state = zox_get_value(gameLink->value, GameState)
        }
        // handle previous mode
        if (deviceMode->value == zox_device_mode_touchscreen) {
            SDL_ShowCursor(SDL_DISABLE);
            if (game_state == zox_game_playing) {
                dispose_menu_game_touch(world, e);
            }
        } else if (deviceMode->value == zox_device_mode_keyboardmouse) {
            SDL_ShowCursor(SDL_ENABLE);
        }
        // handle new mode
        if (deviceModeDirty->value == zox_device_mode_gamepad) {
            zox_field_e()
            raycaster_select_first_button(world, e, canvas);
        } else if (deviceModeDirty->value == zox_device_mode_keyboardmouse) {
            raycaster_select_element(world, e, 0);
            SDL_ShowCursor(SDL_DISABLE);
        } else if (deviceModeDirty->value == zox_device_mode_touchscreen) {
            if (game_state == zox_game_playing) {
                spawn_in_game_ui_touch(world, e, canvas);
            }
        }
        // todo: this isnt being called, fix it!
        spawn_device_gizmo(world, canvas, deviceModeDirty->value);
        menu_start_triggered(world, e, canvas);
    }
} zox_declare_system(DeviceModeUISystem)