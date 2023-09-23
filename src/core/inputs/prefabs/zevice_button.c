ecs_entity_t prefab_zevice_button;

ecs_entity_t spawn_prefab_device_button(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_prefab_name("prefab_zevice_button")
    zox_add_tag(e, Zevice)
    zox_set(e, ZeviceDisabled, { 0 })
    zox_set(e, ZeviceButton, { 0 })
    zox_set(e, DeviceButtonType, { 0 })
    zox_set(e, RealButtonIndex, { 0 })
    ecs_defer_end(world);
    prefab_zevice_button = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab device_button [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_device_button(ecs_world_t *world, unsigned char type, unsigned char index) {
    zox_instance(prefab_zevice_button)
    zox_name("zevice_button")
    zox_set(e, DeviceButtonType, { type })
    zox_set(e, RealButtonIndex, { index })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned device_button [%lu].\n", (long int) (e));
    #endif
    return e;
}

// todo: put this in a system on load instead
unsigned char reset_device_button(ZeviceButton *zeviceButton) {
    unsigned char previous_value = zeviceButton->value;
    if (devices_get_pressed_this_frame(zeviceButton->value)) devices_set_pressed_this_frame(&zeviceButton->value, 0);
    else if (devices_get_released_this_frame(zeviceButton->value)) devices_set_released_this_frame(&zeviceButton->value, 0);
    return previous_value != zeviceButton->value;
}