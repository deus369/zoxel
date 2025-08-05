void toggle_pause_ui(
    ecs_world_t *world,
    const ecs_entity_t player
) {
    zox_geter_value(player, GameLink, ecs_entity_t, game);
    zox_geter_value(game, GameState, byte, game_state);
    if (!(game_state == zox_game_playing || game_state == zox_game_paused)) {
        return;
    }
    byte is_paused = game_state == zox_game_paused;
    zox_set(game, GameStateTarget, { is_paused ? zox_game_playing : zox_game_paused });
}

// from touch_ui
void button_event_pause_game(
    ecs_world_t *world,
    const ClickEventData *event
) {
    toggle_pause_ui(world, event->clicker);
}
