void toggle_pause_ui(ecs_world_t *world) {
    const GameState *gameState = ecs_get(world, local_game, GameState);
    /*if (gameState->value == zoxel_game_state_main_menu) {
        play_game(world);
        return;
    }*/
    if (!(gameState->value == zoxel_game_state_playing || gameState->value == zoxel_game_state_paused)) return;
    const int edge_buffer = 8 * default_ui_scale;
    const float2 window_anchor = { 0.0f, 1.0f };
    const int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
    //zoxel_log(" > alive ui? %s\n", ecs_is_alive(world, pause_ui) ? "alive" : "dead");
    unsigned char is_paused = ecs_is_alive(world, pause_ui); // pause_ui != 0; // ecs_is_alive(world, pause_ui2);
    if (!is_paused) {
        zoxel_log(" > game state => [playing] to [paused]\n");
        zox_set_only(local_game, GameState, { zoxel_game_state_paused })
        zox_set_only(main_cameras[0], FreeRoam, { 0 })
        zox_set_only(mouse_entity, MouseLock, { 0 })
        zox_set_only(main_character3D, DisableMovement, { 1 })
        pause_ui = spawn_pause_ui(world, window_position, window_anchor);
    } else {
        zoxel_log(" > game [paused] to [playing]\n");
        zox_set_only(local_game, GameState, { zoxel_game_state_playing })
        zox_set_only(mouse_entity, MouseLock, { 1 })
        zox_set_only(main_character3D, DisableMovement, { 0 })
        zox_delete(pause_ui)
        pause_ui = 0;
    }
}