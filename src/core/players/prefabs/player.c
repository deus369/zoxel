ecs_entity_t spawn_prefab_player(ecs_world_t *world, const unsigned char player_state) {
    zox_prefab()
    zox_prefab_name("prefab_player")
    zox_add_tag(e, Player)
    zox_prefab_set(e, PlayerState, { player_state })
    return e;
}
