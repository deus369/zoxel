#define zoxel_game_state_main_menu 0
#define zoxel_game_state_playing 1
#define zoxel_game_state_paused 2
ecs_entity_t prefab_game;
ecs_entity_t local_game;

ecs_entity_t spawn_prefab_game(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_game")
    zox_add_tag(e, Game)
    zox_prefab_set(e, GameState, { zoxel_game_state_main_menu })
    prefab_game = e;
#ifdef zoxel_debug_prefabs
    zox_log(" + spawn_prefab game [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_game(ecs_world_t *world) {
    zox_instance(prefab_game)
    zox_name("game")
    local_game = e;
#ifdef zoxel_debug_spawns
    zox_log(" + spawned game [%lu]\n", e)
#endif
    return e;
}
