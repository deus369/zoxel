ecs_entity_t spawn_player(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_name("player")
    zox_set(e, PlayerState, { camera_mode })
    // adds all devices created in inputs module
    zox_get_muter(e, DeviceLinks, deviceLinks)
    resize_memory_component(DeviceLinks, deviceLinks, ecs_entity_t, 4)
    deviceLinks->value[0] = keyboard_entity;
    deviceLinks->value[1] = mouse_entity;
    deviceLinks->value[2] = touchscreen_entity;
    deviceLinks->value[3] = gamepad_entity;
    for (int i = 0; i < 4; i++) zox_set(deviceLinks->value[i], PlayerLink, { e })
    return e;
}
