void toggle_pause_ui(ecs_world_t *world) {
    const GameState *gameState = ecs_get(world, local_game, GameState);
    if (!(gameState->value == zoxel_game_state_playing || gameState->value == zoxel_game_state_paused)) return;
    const int edge_buffer = 8 * default_ui_scale;
    const float2 window_anchor = { 0.0f, 1.0f };
    const int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
    if (!ecs_is_alive(world, pause_ui)) {
        spawn_pause_ui(world, window_position, window_anchor);
        zox_set_only(local_game, GameState, { zoxel_game_state_paused })
        zox_set_only(main_cameras[0], FreeRoam, { 0 })
        zox_set_only(mouse_entity, MouseLock, { 0 })
        zox_set_only(main_character3D, DisableMovement, { 1 })
    } else {
        zox_delete(pause_ui)
        zox_set_only(local_game, GameState, { zoxel_game_state_playing })
        zox_set_only(mouse_entity, MouseLock, { 1 })
        zox_set_only(main_character3D, DisableMovement, { 0 })
    }
    // exit_game();
    // i should also disable player mouse and movement
}

void PlayerPauseSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    for (int i = 0; i < it->count; i++) {
        unsigned char did_toggle_pause = 0;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Keyboard)) {
                const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                if (keyboard->escape.pressed_this_frame || keyboard->enter.pressed_this_frame) {
                    did_toggle_pause = 1;
                    break;
                }
            } else if (ecs_has(world, device_entity, Gamepad)) {
                const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                if (gamepad->start.pressed_this_frame || gamepad->select.pressed_this_frame) {
                    did_toggle_pause = 1;
                    break;
                }
            }
        }
        if (did_toggle_pause) toggle_pause_ui(world);
    }
}
zox_declare_system(PlayerPauseSystem)