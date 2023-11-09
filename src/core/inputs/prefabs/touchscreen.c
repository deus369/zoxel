ecs_entity_t prefab_touchscreen;
ecs_entity_t touchscreen_entity;
const unsigned char fingers_count = 1;
const unsigned char virtual_joysticks_count = 1;

ecs_entity_t spawn_prefab_touchscreen(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_touchscreen")
    zox_add_tag(e, Device)
    zox_add_tag(e, Touchscreen)
    zox_prefab_set(e, DeviceLayout, { 0 })
    zox_prefab_set(e, Children, { 0, NULL })
    prefab_touchscreen = e;
    #ifdef zoxel_debug_prefabs
        zox_log(" > spawn_prefab touchscreen [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_touchscreen(ecs_world_t *world) {
    zox_instance(prefab_touchscreen)
    zox_name("touchscreen")
    const unsigned char touchscreen_zevice_count = fingers_count + virtual_joysticks_count;
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, touchscreen_zevice_count)
    for (unsigned char i = 0; i < fingers_count; i++) children->value[i] = spawn_zevice_pointer(world, i, i);
    for (unsigned char i = fingers_count; i < fingers_count + virtual_joysticks_count; i++) children->value[i] = spawn_zevice_stick(world, i, i);
    zox_modified(e, Children)
    touchscreen_entity = e;
    #ifdef zoxel_debug_spawns
        zox_log(" > spawned touchscreen [%lu]\n", e)
    #endif
    return e;
}

unsigned char zevice_pointer_has_input(const ZevicePointer *zevicePointer) {
    return devices_get_is_pressed(zevicePointer->value);
}

unsigned char touchscreen_is_any_input(ecs_world_t *world, ecs_entity_t touchscreen) {
    if (!touchscreen || !ecs_is_alive(world, touchscreen)) return 0;
    const Children *children = zox_get(touchscreen, Children)
    for (int i = 0; i < children->length; i++) {
        ecs_entity_t e = children->value[i];
        if (!zox_has(e, ZevicePointer)) continue;
        const ZevicePointer *zevicePointer = zox_get(e, ZevicePointer)
        if (zevice_pointer_has_input(zevicePointer)) return 1;
    }
    return 0;
}

/*void device_reset_touchscreen(ecs_world_t *world, ecs_entity_t touchscreen) {
    if (!touchscreen || !ecs_is_alive(world, touchscreen)) return;
    const Children *children = ecs_get(world, touchscreen, Children);
    for (int i = 0; i < children->length; i++) {
        ecs_entity_t e = children->value[i];
        if (!ecs_has(world, e, ZevicePointer)) continue;
        ZevicePointer *zeviceButton = ecs_get_mut(world, e, ZevicePointer);
        if (reset_device_pointer(zeviceButton)) ecs_modified(world, e, ZevicePointer);
        ZevicePointerDelta *zevicePointerDelta = ecs_get_mut(world, e, ZevicePointerDelta);
        if (zevicePointerDelta->value.x == 0 && zevicePointerDelta->value.y == 0) continue;
        zevicePointerDelta->value = int2_zero;
        ecs_modified(world, e, ZevicePointerDelta);
    }
}*/
