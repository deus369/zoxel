#define zox_device_stick_left 0
#define zox_device_stick_right 1

ecs_entity_t prefab_device_stick;

ecs_entity_t spawn_prefab_device_stick(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_device_stick")
    zox_add_tag(e, Zevice)
    zox_set(e, ZeviceDisabled, { 0 })
    zox_set(e, DeviceStick, { float2_zero })
    zox_set(e, DeviceButtonType, { 0 })
    zox_set(e, RealButtonIndex, { 0 })
    ecs_defer_end(world);
    prefab_device_stick = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab device_stick [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_device_stick(ecs_world_t *world, unsigned char type, unsigned char index) {
    zox_instance(prefab_device_stick)
    zox_name("device_stick")
    zox_set(e, DeviceButtonType, { type })
    zox_set(e, RealButtonIndex, { index })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned device_stick [%lu].\n", (long int) (e));
    #endif
    if (ecs_has(world, e, DeviceButton)) zoxel_log("    > device stick has button\n");
    return e;
}