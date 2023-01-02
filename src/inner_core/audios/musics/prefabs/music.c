ecs_entity_t prefab_music;

ecs_entity_t spawn_prefab_music(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "prefab_music");
    set_unique_entity_name(world, e, "prefab_music");
    zoxel_add_tag(world, e, Music);
    zoxel_set(world, e, GenerateMusic, { 1 });
    zoxel_add(world, e, MusicData);
    zoxel_set(world, e, MusicTime, { 0 });
    ecs_defer_end(world);
    prefab_music = e;
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab music [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_music(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_music);
    set_unique_entity_name(world, e, "music");
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned music [%lu]\n", (long int) e);
    #endif
    return e;
}