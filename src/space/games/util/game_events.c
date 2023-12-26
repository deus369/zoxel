// an example of a zox_game_event can be a function that grabs all players and spawns them a character
zox_game_event_array_d* on_start_game;

void initialize_events_games() {
    on_start_game = create_zox_game_event_array_d(initial_dynamic_array_size);
}

void dispose_events_games() {
    dispose_zox_game_event_array_d(on_start_game);
}

void add_to_event_start_game(zox_game_event funn) {
    add_to_zox_game_event_array_d(on_start_game, funn);
}

void trigger_event_on_start_game(ecs_world_t* world, ecs_entity_t game) {
    for (int i = 0; i < on_start_game->size; i++) {
        if (on_start_game->data[i].value) (*on_start_game->data[i].value)(world, game);
    }
}
