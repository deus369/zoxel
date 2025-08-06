ecs_entity_t spawn_prefab_player(ecs_world_t *world) {
    zox_prefab();
    zox_prefab_name("player");
    zox_add_tag(e, Player);
    zox_prefab_set(e, PlayerState, { zox_player_state_main_menu });
    zox_prefab_set(e, PlayerRespawn, { 0 });
    zox_prefab_set(e, GameLink, { 0 });
    zox_prefab_set(e, PlayerPauseEvent, { 0 });
    return e;
}
