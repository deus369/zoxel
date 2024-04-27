ecs_entity_t prefab_player;
ecs_entity_t main_player;
ecs_entity_t local_player;

ecs_entity_t spawn_prefab_player(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_player")
    // core players data
    zox_add_tag(e, Player)
    zox_prefab_set(e, PlayerState, { camera_mode })
    // Player -> Devices
    zox_prefab_set(e, DeviceMode, { 0 })
    zox_prefab_set(e, DeviceModeDirty, { 0 })
    zox_prefab_set(e, DeviceLinks, { 0, NULL })
    // this is all UI interaction
    zox_prefab_set(e, Raycaster, { { 0, 0 } })
    zox_prefab_set(e, RaycasterTarget, { 0 })
    zox_prefab_set(e, RaycasterResult, { 0 })
    zox_prefab_set(e, ClickingEntity, { 0 })
    zox_prefab_set(e, NavigatorState, { 0 })
    zox_prefab_set(e, NavigatorTimer, { 0 })
    zox_prefab_set(e, ElementLinks, { 0, NULL })
    zox_prefab_set(e, CanvasLink, { 0 })
    // Player -> Character/Camera
    zox_prefab_set(e, CharacterLink, { 0 })
    zox_prefab_set(e, CameraLink, { 0 })
    prefab_player = e;
    return e;
}

ecs_entity_t spawn_player(ecs_world_t *world) {
    zox_instance(prefab_player)
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
