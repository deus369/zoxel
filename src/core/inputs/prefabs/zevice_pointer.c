ecs_entity_t prefab_zevice_pointer;

ecs_entity_t spawn_prefab_zevice_pointer(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_zevice_pointer")
    zox_add_tag(e, Zevice)
    zox_prefab_set(e, ID, { 0 })
    zox_prefab_set(e, ZeviceDisabled, { 0 })
    zox_prefab_set(e, ZevicePointer, { 0 })
    zox_prefab_set(e, ZevicePointerPosition, { int2_zero })
    zox_prefab_set(e, ZevicePointerDelta, { int2_zero })
    zox_prefab_set(e, DeviceButtonType, { 0 })
    zox_prefab_set(e, RealButtonIndex, { 0 })
    prefab_zevice_pointer = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab zevice_pointer [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_zevice_pointer(ecs_world_t *world, unsigned char type, unsigned char index) {
    zox_instance(prefab_zevice_pointer)
    zox_name("zevice_pointer")
    zox_prefab_set(e, DeviceButtonType, { type })
    zox_prefab_set(e, RealButtonIndex, { index })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned zevice_pointer [%lu].\n", (long int) (e));
    #endif
    if (ecs_has(world, e, ZeviceButton)) zoxel_log("    > device stick has button\n");
    return e;
}

unsigned char reset_device_pointer2(unsigned char *value) {
    unsigned char previous_value = *value;
    if (devices_get_pressed_this_frame(previous_value)) devices_set_pressed_this_frame(value, 0);
    else if (devices_get_released_this_frame(previous_value)) devices_set_released_this_frame(value, 0);
    return previous_value != *value;
}

unsigned char reset_device_pointer(ZevicePointer *zevicePointer) {
    unsigned char previous_value = zevicePointer->value;
    if (devices_get_pressed_this_frame(zevicePointer->value)) devices_set_pressed_this_frame(&zevicePointer->value, 0);
    else if (devices_get_released_this_frame(zevicePointer->value)) devices_set_released_this_frame(&zevicePointer->value, 0);
    return previous_value != zevicePointer->value;
}