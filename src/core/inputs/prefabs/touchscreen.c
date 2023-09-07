ecs_entity_t prefab_touchscreen;
ecs_entity_t touchscreen_entity;

ecs_entity_t spawn_prefab_touchscreen(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("touchscreen_prefab")
    zox_add_tag(e, Device)
    zox_add_tag(e, Touchscreen)
    // zox_set(e, Touchscreen, touchscreen_zero)
    zox_set(e, DeviceLayout, { 0 })
    zox_set(e, Children, { 0, NULL })
    ecs_defer_end(world);
    prefab_touchscreen = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab touchscreen [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_touchscreen(ecs_world_t *world) {
    zox_instance(prefab_touchscreen)
    zox_name("touchscreen")
    const unsigned char fingers_count = 2;
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, fingers_count)
    for (unsigned char i = 0; i < fingers_count; i++) {
        children.value[i] = spawn_zevice_pointer(world, i, i);
    }
    zox_set_only(e, Children, { children.length, children.value })
    touchscreen_entity = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned touchscreen [%lu].\n", (long int) (e));
    #endif
    return e;
}

unsigned char zevice_pointer_has_input(const ZevicePointer *zevicePointer) {
    return devices_get_is_pressed(zevicePointer->value);
}

unsigned char touchscreen_is_any_input(ecs_world_t *world, ecs_entity_t touchscreen) {
    const Children *children = ecs_get(world, touchscreen, Children);
    for (int i = 0; i < children->length; i++) {
        ecs_entity_t e = children->value[i];
        if (ecs_has(world, e, ZevicePointer)) {
            ZevicePointer *zevicePointer = ecs_get_mut(world, e, ZevicePointer);
            if (zevice_pointer_has_input(zevicePointer)) return 1;
        }
    }
    return 0;
}

void device_reset_touchscreen(ecs_world_t *world, ecs_entity_t touchscreen) {
    if (!touchscreen || !ecs_is_alive(world, touchscreen)) return;
    const Children *children = ecs_get(world, touchscreen, Children);
    for (int i = 0; i < children->length; i++) {
        ecs_entity_t e = children->value[i];
        if (ecs_has(world, e, ZevicePointer)) {
            ZevicePointer *zeviceButton = ecs_get_mut(world, e, ZevicePointer);
            if (reset_device_pointer(zeviceButton)) ecs_modified(world, e, ZevicePointer);
            ZevicePointerDelta *zevicePointerDelta = ecs_get_mut(world, e, ZevicePointerDelta);
            if (!(zevicePointerDelta->value.x == 0 && zevicePointerDelta->value.y == 0)) {
                zevicePointerDelta->value = int2_zero;
                ecs_modified(world, e, ZevicePointerDelta);
            }
        }
    }
}