ecs_entity_t spawn_player(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_name("player")
    // zox_set(e, PlayerState, { camera_mode })
    // adds all devices created in inputs module
    zox_get_muter(e, DeviceLinks, deviceLinks)
    // todo: connect to devices based on assignment on start screen
    if (local_keyboard) {
        add_to_DeviceLinks(deviceLinks, local_keyboard);
        zox_set(local_keyboard, PlayerLink, { e });
    }
    if (local_mouse) {
        add_to_DeviceLinks(deviceLinks, local_mouse);
        zox_set(local_mouse, PlayerLink, { e });
    }
    if (local_touchscreen) {
        add_to_DeviceLinks(deviceLinks, local_touchscreen);
        zox_set(local_touchscreen, PlayerLink, { e });
    }
    if (gamepad_entity) {
        add_to_DeviceLinks(deviceLinks, gamepad_entity);
        zox_set(gamepad_entity, PlayerLink, { e });
    }
    return e;
}
