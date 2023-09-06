ecs_entity_t prefab_zevice_pointer;

ecs_entity_t spawn_prefab_zevice_pointer(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_zevice_pointer")
    zox_add_tag(e, Zevice)
    zox_set(e, ZeviceDisabled, { 0 })
    zox_set(e, ZevicePointer, { 0 })
    zox_set(e, ZevicePointerPosition, { int2_zero })
    zox_set(e, ZevicePointerDelta, { int2_zero })
    zox_set(e, DeviceButtonType, { 0 })
    zox_set(e, RealButtonIndex, { 0 })
    ecs_defer_end(world);
    prefab_zevice_pointer = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab zevice_pointer [%lu].\n", (long int) (e));
    #endif
    unsigned char test = 0;
    devices_set_is_pressed(&test, 1);
    zoxel_log(" test 1 set_is_pressed [%i]\n", test);
    devices_set_pressed_this_frame(&test, 1);
    zoxel_log(" test 2 set_pressed_this_frame [%i]\n", test);
    devices_set_released_this_frame(&test, 1);
    zoxel_log(" test 3 set_released_this_frame [%i]\n", test);

    devices_set_pressed_this_frame(&test, 0);
    zoxel_log(" test 4 set_pressed_this_frame(0) [%i]\n", test);
    devices_set_is_pressed(&test, 0);
    zoxel_log(" test 5 set_is_pressed(0) [%i]\n", test);
    devices_set_released_this_frame(&test, 0);
    zoxel_log(" test 6 set_released_this_frame(0) [%i]\n", test);
    return e;
}

ecs_entity_t spawn_zevice_pointer(ecs_world_t *world, unsigned char type, unsigned char index) {
    zox_instance(prefab_zevice_pointer)
    zox_name("zevice_pointer")
    zox_set(e, DeviceButtonType, { type })
    zox_set(e, RealButtonIndex, { index })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned zevice_pointer [%lu].\n", (long int) (e));
    #endif
    if (ecs_has(world, e, DeviceButton)) zoxel_log("    > device stick has button\n");
    return e;
}

unsigned char reset_device_pointer(ZevicePointer *zevicePointer) {
    unsigned char previous_value = zevicePointer->value;
    if (devices_get_pressed_this_frame(zevicePointer->value)) devices_set_pressed_this_frame(&zevicePointer->value, 0);
    else if (devices_get_released_this_frame(zevicePointer->value)) devices_set_released_this_frame(&zevicePointer->value, 0);
    return previous_value != zevicePointer->value;
}