// handles changes in device mode state
void DeviceModeUISystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DeviceMode)
    zox_sys_in(DeviceModeDirty)
    zox_sys_in(GameLink)
    zox_sys_in(CanvasLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(GameLink, gameLink)
        zox_sys_i(CanvasLink, canvasLink)
        zox_sys_i(DeviceModeDirty, deviceModeDirty)
        zox_sys_i(DeviceMode, deviceMode)
        if (!deviceModeDirty->value || deviceModeDirty->value == deviceMode->value) {
            return;
        }
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
            zox_sys_e()
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
} zoxd_system(DeviceModeUISystem)