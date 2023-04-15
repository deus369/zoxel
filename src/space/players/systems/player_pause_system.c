// enter paused game state
// ecs_set(world, local_game, GameState, { zoxel_game_state_playing });

void toggle_pause_ui(ecs_world_t *world) {
    zoxel_log(" > todo: toggle pause ui\n");
    exit_game();
}

void PlayerPauseSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++) {
        const Keyboard *keyboard = &keyboards[i];
        if (keyboard->escape.pressed_this_frame) {
            toggle_pause_ui(world);
        }
    }
}
zoxel_declare_system(PlayerPauseSystem)

void PlayerPauseSystem2(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const Gamepad *gamepads = ecs_field(it, Gamepad, 1);
    for (int i = 0; i < it->count; i++) {
        const Gamepad *gamepad = &gamepads[i];
        if (gamepad->select.pressed_this_frame) {
            toggle_pause_ui(world);
        }
    }
}
zoxel_declare_system(PlayerPauseSystem2)