void button_event_pause_game(ecs_world_t *world, ecs_entity_t trigger_entity) {
    toggle_pause_ui(world, main_player);
}

void toggle_pause_ui(ecs_world_t *world, ecs_entity_t player) {
    const GameState *gameState = zox_get(local_game, GameState)
#ifdef zox_play_game_on_start
    if (gameState->value == zoxel_game_state_main_menu) {
        play_game(world);
        return;
    }
#endif
    if (!(gameState->value == zoxel_game_state_playing || gameState->value == zoxel_game_state_paused)) return;
    const float2 window_anchor = float2_half; // { 0.5f, 0.5f };
    const int2 window_position = int2_zero;
    //zoxel_log(" > alive ui? %s\n", ecs_is_alive(world, pause_ui) ? "alive" : "dead");
    unsigned char is_paused = gameState->value == zoxel_game_state_paused; // ecs_is_alive(world, pause_ui); // pause_ui != 0; // ecs_is_alive(world, pause_ui2);
    ecs_entity_t character3D = zox_get_value(player, CharacterLink)
    if (!is_paused) {
        // zoxel_log(" > game state => [playing] to [paused] for [%lu]\n", character3D);
        zox_set(local_game, GameState, { zoxel_game_state_paused })
        disable_inputs_until_release(world, player, zox_device_mode_none);
        zox_set(main_cameras[0], FreeRoam, { 0 })
        zox_set(mouse_entity, MouseLock, { 0 })
        zox_set(character3D, DisableMovement, { 1 })
        pause_ui = spawn_pause_ui(world, window_position, window_anchor);
        dispose_in_game_ui(world, player);
        unlock_achievement("test_achievement2");
    } else {
        // zoxel_log(" > game [paused] to [playing] for [%lu]\n", character3D);
        zox_set(local_game, GameState, { zoxel_game_state_playing })
        disable_inputs_until_release(world, player, zox_device_mode_none);
        zox_set(mouse_entity, MouseLock, { 1 })
        zox_set(character3D, DisableMovement, { 0 })
        zox_delete(pause_ui)
        pause_ui = 0;
        spawn_in_game_ui(world, player);
    }
}

// const int edge_buffer = 8 * default_ui_scale;
// const float2 window_anchor = { 0, 1 };
// const int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
