ecs_entity_t generic_event_prefab;

void spawn_prefab_generic_event(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_generic_event")
    zox_add_tag(e, DestroyInFrame)
    zox_set(e, GenericEvent, { 0 })
    ecs_defer_end(world);
    generic_event_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab generic_event [%lu].\n", (long int) (e));
    #endif
}

ecs_entity_t spawn_generic_event(ecs_world_t *world, unsigned char state) {
    // ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, generic_event_prefab);
    zox_instance(generic_event_prefab)
    zox_name("event")
    zox_set_only(e, GenericEvent, { state })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned event [%lu]\n", (long int) e);
    #endif
    return e;
}