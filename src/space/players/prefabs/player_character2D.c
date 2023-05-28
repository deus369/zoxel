ecs_entity_t player_character2D_prefab;

ecs_entity_t spawn_player_character2D_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(character2D_prefab)
    zox_name("prefab_player_character2D")
    zox_add_tag(e, PlayerCharacter)
    zox_add_tag(e, PlayerCharacter2D)
    zox_add(e, CameraLink)
    zox_set(e, DisableMovement, { 0 })
    ecs_defer_end(world);
    player_character2D_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab player_character2D [%lu].\n", (long int) (e));
    #endif
    return e;
}