ecs_entity_t player_character2D_prefab;

ecs_entity_t spawn_player_character2D_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, character2D_prefab);
    ecs_add_id(world, e, EcsPrefab);
    set_unique_entity_name(world, e, "player_character2D_prefab");
    zox_add_tag(e, PlayerCharacter);
    zox_add_tag(e, PlayerCharacter2D);
    zox_add(e, CameraLink);
    zox_set(e, DisableMovement, { 0 });
    ecs_defer_end(world);
    player_character2D_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab player_character2D [%lu].\n", (long int) (e));
    #endif
    return e;
}