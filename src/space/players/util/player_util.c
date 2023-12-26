void add_player(ecs_entity_t e, ecs_entity_t player) {
    PlayerLinks *playerLinks = zox_get_mut(e, PlayerLinks)
    // do a list check first (later)
    resize_memory_component(PlayerLinks, playerLinks, ecs_entity_t, playerLinks->length + 1)
    playerLinks->value[playerLinks->length - 1] = player;
    zox_modified(e, PlayerLinks)
}

void play_game_players(ecs_world_t *world, ecs_entity_t game) {
    const PlayerLinks *playerLinks = zox_get(game, PlayerLinks)
    for (int i = 0; i < playerLinks->length; i++) {
        play_game_on_player(world, playerLinks->value[i]);
    }
}
