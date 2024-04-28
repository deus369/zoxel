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

void set_game_state(ecs_world_t *world, ecs_entity_t game, unsigned char new_game_state) {
    // zox_log(" > setting game state [%i]\n", new_game_state)
    zox_set(game, GameState, { new_game_state })
}

void trigger_event_game(ecs_world_t* world, const ecs_entity_t game, const unsigned char new_game_state) {
    const unsigned char old_game_stat = zox_get_value(game, GameState)
    if (new_game_state == old_game_stat) return;
    for (int i = 0; i < game_state_event->size; i++) {
        if (game_state_event->data[i].value) (*game_state_event->data[i].value)(world, game, new_game_state);
    }
    set_game_state(world, game, new_game_state);
}
