void pause_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const ecs_entity_t character3D = zox_get_value(player, CharacterLink)
    const float2 window_anchor = float2_half;
    const int2 window_position = int2_zero;
    dispose_in_game_ui(world, player); // check this, ingame ui should now be linked to player, got from canvas
    disable_inputs_until_release(world, player, zox_device_mode_none);
    zox_set(camera, FreeRoam, { 0 })
    zox_set(mouse_entity, MouseLock, { 0 })
    zox_set(character3D, DisableMovement, { 1 })
    spawn_menu_paused(world, player, canvas, window_position, window_anchor);
    unlock_achievement("achievement_paused_game"); // test_achievement2
}

void resume_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuPaused, menu_paused)
    zox_delete(menu_paused)
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    disable_inputs_until_release(world, player, zox_device_mode_none);
    zox_set(mouse_entity, MouseLock, { 1 })
    zox_set(character, DisableMovement, { 0 })
    const ecs_entity_t health_stat = zox_gett(character, StatLinks)->value[0];
    spawn_in_game_ui(world, player, (ecs_entity_2) { character, health_stat });
}

void pause_resume(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const GameState *gameState = zox_get(game, GameState)
    if (!(gameState->value == zox_game_playing || gameState->value == zox_game_paused)) return;
    unsigned char is_paused = gameState->value == zox_game_paused;
    if (is_paused) trigger_event_game(world, game, zox_game_playing);
}

void toggle_pause_ui(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const GameState *gameState = zox_get(game, GameState)
    if (!(gameState->value == zox_game_playing || gameState->value == zox_game_paused)) return;
    unsigned char is_paused = gameState->value == zox_game_paused;
    if (!is_paused) trigger_event_game(world, game, zox_game_paused);
    else trigger_event_game(world, game, zox_game_playing);
}
