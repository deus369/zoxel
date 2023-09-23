ecs_entity_t prefab_player;
ecs_entity_t main_player;
ecs_entity_t local_player;

ecs_entity_t spawn_prefab_player(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_prefab_name("prefab_player")
    zox_add_tag(e, Player)
    zox_set(e, PlayerState, { camera_mode })
    zox_add(e, DeviceLinks)
    zox_set(e, DeviceMode, { 0 })
    zox_set(e, DeviceModeDirty, { 0 })
    zox_set(e, Raycaster, { { 0, 0 } })
    zox_set(e, RaycasterTarget, { 0 })
    zox_set(e, RaycasterResult, { 0 })
    zox_set(e, NavigatorState, { 0 })
    zox_set(e, NavigatorTimer, { 0 })
    zox_set(e, CharacterLink, { 0 })
    zox_set(e, CameraLink, { 0 })
    zox_set(e, ElementLinks, { 0, NULL })
    ecs_defer_end(world);
    prefab_player = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" + spawned prefab player [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_player(ecs_world_t *world) {
    zox_instance(prefab_player)
    zox_name("player")
    zox_set_only(e, PlayerState, { camera_mode })
    DeviceLinks *deviceLinks = ecs_get_mut(world, e, DeviceLinks);
    initialize_memory_component(deviceLinks, ecs_entity_t, 4)
    //DeviceLinks deviceLinks = { };
    //initialize_memory_component_non_pointer(deviceLinks, ecs_entity_t, 4)
    deviceLinks->value[0] = keyboard_entity;
    deviceLinks->value[1] = mouse_entity;
    deviceLinks->value[2] = gamepad_entity;
    deviceLinks->value[3] = touchscreen_entity;
    // zox_set_only(e, DeviceLinks, { deviceLinks.length, deviceLinks.value })
    ecs_modified(world, e, DeviceLinks);
    main_player = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" + spawned player [%lu]\n", (long int) e);
    #endif
    return e;
}