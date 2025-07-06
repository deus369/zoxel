// an example of a zox_game_event can be a function that grabs all players and spawns them a character
zox_game_event_array_d* game_state_event;

void initialize_events_games() {
    game_state_event = create_zox_game_event_array_d(initial_dynamic_array_size);
}

void dispose_events_games() {
    dispose_zox_game_event_array_d(game_state_event);
}

void add_to_event_game_state(zox_game_event funn) {
    add_to_zox_game_event_array_d(game_state_event, funn);
}

void trigger_event_game(ecs_world_t* world, const ecs_entity_t game, const byte old_game_state, const byte new_game_state) {
    for (int i = 0; i < game_state_event->size; i++) {
        if (game_state_event->data[i].value) (*game_state_event->data[i].value)(world, game, old_game_state, new_game_state);
    }
}

void pause_resume(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const byte game_state = zox_get_value(game, GameState)
    if (!(game_state == zox_game_playing || game_state == zox_game_paused)) {
        return;
    }
    byte is_paused = game_state == zox_game_paused;
    if (is_paused) {
        zox_set(game, GameStateTarget, { zox_game_playing })
    }
}
