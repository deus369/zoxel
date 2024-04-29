void add_player(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player) {
    PlayerLinks *playerLinks = zox_get_mut(e, PlayerLinks)
    resize_memory_component(PlayerLinks, playerLinks, ecs_entity_t, playerLinks->length + 1)
    playerLinks->value[playerLinks->length - 1] = player;
    zox_modified(e, PlayerLinks)
    zox_set(player, GameLink, { e })
}

// game state implementation for players module
void players_game_state(ecs_world_t *world, const ecs_entity_t game, const unsigned char new_game_state) {
    unsigned char previous_game_state = zox_get_value(game, GameState)
    const PlayerLinks *playerLinks = zox_get(game, PlayerLinks)
    for (int i = 0; i < playerLinks->length; i++) {
        const ecs_entity_t player = playerLinks->value[i];
        if (previous_game_state == zox_game_start && new_game_state == zox_game_playing) player_start_game(world, player);
        else if (previous_game_state == zox_game_playing && new_game_state == zox_game_paused) pause_player(world, player);
        else if (previous_game_state == zox_game_paused && new_game_state == zox_game_playing) resume_player(world, player);
        else if (new_game_state == zox_game_start) player_end_game(world, player);
    }
}
