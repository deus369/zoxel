ecs_entity_t spawn_prefab_game(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_game")
    zox_add_tag(e, Game)
    zox_prefab_set(e, GameState, { zox_game_start })
    zox_prefab_set(e, RealmLink, { 0 })
    return e;
}

ecs_entity_t spawn_game(ecs_world_t *world, const ecs_entity_t realm) {
    zox_instance(prefab_game)
    zox_name("game")
    if (realm) {
        zox_set(e, RealmLink, { realm })
    }
    return e;
}
