// enter paused game state
// ecs_set(world, local_game, GameState, { zoxel_game_state_playing });

void toggle_pause_ui(ecs_world_t *world) {
    const GameState *gameState = ecs_get(world, local_game, GameState);
    if (!(gameState->value == zoxel_game_state_playing || gameState->value == zoxel_game_state_paused)) {
        return;
    }
    zoxel_log(" > todo: toggle pause ui\n");
    const int edge_buffer = 8 * default_ui_scale;
    const int2 window_size = { 260, 220 };
    const float2 window_anchor = { 0.5f, 0.5f };
    const int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
    // Children children = { };
    // initialize_memory_component_non_pointer(children, ecs_entity_t, 3);
    // add this entity to canvas children
    if (!ecs_is_alive(world, pause_ui)) {
        // pause game
        ecs_entity_t pause_ui = spawn_pause_ui(world, window_position, window_size, window_anchor);
        ecs_set(world, local_game, GameState, { zoxel_game_state_paused });
        ecs_set(world, main_cameras[0], FreeRoam, { 0 });
        ecs_set(world, mouse_entity, MouseLock, { 0 });
        ecs_set(world, main_character3D, DisableMovement, { 1 });
    } else {
        ecs_delete(world, pause_ui);
        ecs_set(world, local_game, GameState, { zoxel_game_state_playing });
        ecs_set(world, mouse_entity, MouseLock, { 1 });
        ecs_set(world, main_character3D, DisableMovement, { 0 });
    }
    // exit_game();

    // i should also disable player mouse and movement
}

void PlayerPauseSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    /*const DeviceLinks *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++) {
        const Keyboard *keyboard = &keyboards[i];
        if (keyboard->escape.pressed_this_frame || keyboard->enter.pressed_this_frame) {
            toggle_pause_ui(world);
        }
    }*/
    const DeviceLinks *deviceLinks = ecs_field(it, DeviceLinks, 2);
    for (int i = 0; i < it->count; i++) {
        const DeviceLinks *deviceLinks2 = &deviceLinks[i];
        unsigned char did_toggle_pause = 0;
        for (int j = 0; j < deviceLinks2->length; j++) {
            ecs_entity_t device_entity = deviceLinks2->value[j];
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
        if (did_toggle_pause) {
            toggle_pause_ui(world);
        }
    }
}
zoxel_declare_system(PlayerPauseSystem)

/*void PlayerPauseSystem2(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const Gamepad *gamepads = ecs_field(it, Gamepad, 1);
    for (int i = 0; i < it->count; i++) {
        const Gamepad *gamepad = &gamepads[i];
        if (gamepad->start.pressed_this_frame || gamepad->select.pressed_this_frame) {
            toggle_pause_ui(world);
        }
    }
}
zoxel_declare_system(PlayerPauseSystem2)*/