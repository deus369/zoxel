ecs_entity_t prefab_sound;

ecs_entity_t spawn_prefab_sound(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "prefab_sound");
    set_unique_entity_name(world, e, "prefab_sound");
    zoxel_add_tag(world, e, Sound);
    zoxel_set(world, e, PlaySound, { 1 });
    ecs_defer_end(world);
    prefab_sound = e;
    #ifdef zoxel_debug_prefabs
    zoxel_log_arg("spawn_prefab sound [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_sound(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_sound);
    set_unique_entity_name(world, e, "sound");
    // ecs_set(world, e, PixelSize, { size });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log_arg("Spawned sound [%lu]\n", (long int) e);
    #endif
    return e;
}