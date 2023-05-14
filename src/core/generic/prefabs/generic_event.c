ecs_entity_t generic_event_prefab;

void spawn_prefab_generic_event(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "generic_event_prefab");
    // zox_add_tag(e, Event);
    zox_add_tag(e, DestroyInFrame);
    zox_set(e, GenericEvent, { 0 });
    ecs_defer_end(world);
    generic_event_prefab = e;
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab generic_event [%lu].\n", (long int) (e));
    #endif
}

ecs_entity_t spawn_generic_event(ecs_world_t *world, unsigned char state) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, generic_event_prefab);
    set_unique_entity_name(world, e, "event");
    ecs_set(world, e, GenericEvent, { state });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned Event [%lu]\n", (long int) e);
    #endif
    return e;
}