ecs_entity_t spawn_player(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_name("player")
    zox_set(e, PlayerState, { camera_mode })
    // adds all devices created in inputs module
    DeviceLinks *deviceLinks = zox_get_mut(e, DeviceLinks)
    resize_memory_component(DeviceLinks, deviceLinks, ecs_entity_t, 4)
    deviceLinks->value[0] = keyboard_entity;
    deviceLinks->value[1] = mouse_entity;
    deviceLinks->value[2] = gamepad_entity;
    deviceLinks->value[3] = touchscreen_entity;
    zox_modified(e, DeviceLinks)
    return e;
}
