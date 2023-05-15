ecs_entity_t prefab_player;
ecs_entity_t main_player;

ecs_entity_t spawn_prefab_player(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    ecs_add_id(world, e, EcsPrefab);
    set_unique_entity_name(world, e, "prefab_player");
    zox_add_tag(e, Player);
    zox_add(e, DeviceLinks);
    zox_set(e, DeviceMode, { 0 });
    zox_set(e, Raycaster, { { 0, 0 } });
    zox_set(e, RaycasterTarget, { 0 });
    zox_set(e, NavigatorTimer, { 0 });
    ecs_defer_end(world);
    prefab_player = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" + spawned prefab player [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_player(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_player);
    set_unique_entity_name(world, e, "player");
    DeviceLinks deviceLinks = { };
    initialize_memory_component_non_pointer(deviceLinks, ecs_entity_t, 4);
    deviceLinks.value[0] = keyboard_entity;
    deviceLinks.value[1] = mouse_entity;
    deviceLinks.value[2] = gamepad_entity;
    deviceLinks.value[3] = touchscreen_entity;
    ecs_set(world, e, DeviceLinks, { deviceLinks.length, deviceLinks.value });
    ecs_defer_end(world);
    main_player = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" + spawned player [%lu]\n", (long int) e);
    #endif
    return e;
}