void add_player(ecs_entity_t e, ecs_entity_t player) {
    PlayerLinks *playerLinks = zox_get_mut(e, PlayerLinks)
    // do a list check first (later)
    resize_memory_component(PlayerLinks, playerLinks, ecs_entity_t, playerLinks->length + 1)
    playerLinks->value[playerLinks->length - 1] = player;
    zox_modified(e, PlayerLinks)
}

void players_game_state(ecs_world_t *world, ecs_entity_t game, unsigned char new_game_state) {
    unsigned char previous_game_state = zox_get_value(game, GameState)
    // zox_log(" > game state change for players: %i > %i\n", previous_game_state, new_game_state)
    const PlayerLinks *playerLinks = zox_get(game, PlayerLinks)
    for (int i = 0; i < playerLinks->length; i++) {
        ecs_entity_t player = playerLinks->value[i];
        if (previous_game_state == zox_game_start && new_game_state == zox_game_playing) player_start_game(world, player);
        else if (previous_game_state == zox_game_playing && new_game_state == zox_game_paused) pause_player(world, player);
        else if (previous_game_state == zox_game_paused && new_game_state == zox_game_playing) resume_player(world, player);
        else if (new_game_state == zox_game_start) player_end_game(world, player);
    }
}
