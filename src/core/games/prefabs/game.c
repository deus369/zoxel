ecs_entity_t prefab_game;
// ecs_entity_t local_game;

ecs_entity_t spawn_prefab_game(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_game")
    zox_add_tag(e, Game)
    zox_prefab_set(e, GameState, { zox_game_start })
    prefab_game = e;
    return e;
}

ecs_entity_t spawn_game(ecs_world_t *world) {
    zox_instance(prefab_game)
    zox_name("game")
    // local_game = e;
    return e;
}
