ecs_entity_t prefab_game;

ecs_entity_t spawn_prefab_game(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, ""); // prefab_game");
    set_unique_entity_name(world, e, "prefab_game");
    zoxel_add_tag(world, e, Game);
    zoxel_set(world, e, GameState, { 0 });
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab game [%lu].\n", (long int) (e));
    #endif
    prefab_game = e;
    return e;
}

ecs_entity_t spawn_game(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_game);
    set_unique_entity_name(world, e, "game");
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned game [%lu]\n", (long int) e);
    #endif
    return e;
}