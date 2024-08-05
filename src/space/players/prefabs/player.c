ecs_entity_t spawn_player(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_name("player")
    zox_set(e, PlayerState, { camera_mode })
    // adds all devices created in inputs module
    zox_get_muter(e, DeviceLinks, deviceLinks)
    // todo: connect to devices based on assignment on start screen
    if (keyboard_entity) add_to_DeviceLinks(deviceLinks, keyboard_entity);
    if (mouse_entity) add_to_DeviceLinks(deviceLinks, mouse_entity);
    if (touchscreen_entity) add_to_DeviceLinks(deviceLinks, touchscreen_entity);
    if (gamepad_entity) add_to_DeviceLinks(deviceLinks, gamepad_entity);
    for (int i = 0; i < deviceLinks->length; i++) {
        const ecs_entity_t device = deviceLinks->value[i];
        if (!device) continue;
        zox_set(device, PlayerLink, { e })
    }
    return e;
}
