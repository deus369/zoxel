ecs_entity_t spawn_prefab_touchscreen(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_touchscreen")
    zox_add_tag(e, Device)
    zox_add_tag(e, Touchscreen)
    zox_prefab_add(e, ScreenDimensions)
    zox_prefab_set(e, DeviceLayout, { 0 })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_touchscreen(ecs_world_t *world, const ecs_entity_t prefab, const int2 screen_dimensions) {
    zox_instance(prefab)
    zox_name("touchscreen")
    zox_set(e, ScreenDimensions, { screen_dimensions })
    // const unsigned char touchscreen_zevice_count = fingers_count + virtual_joysticks_count;
    zox_get_muter(e, Children, children)
    // resize_memory_component(Children, children, ecs_entity_t, touchscreen_zevice_count)
    for (unsigned char i = 0; i < fingers_count; i++) {
        const ecs_entity_t finger = spawn_zevice_pointer(world, e, i, i);
        const ecs_entity_t virtual_joystick = spawn_zevice_stick(world, e, i, i);
        zox_add_tag(finger, Finger)
        zox_set(finger, VirtualZeviceLink, { virtual_joystick })
        add_to_Children(children, finger);
        add_to_Children(children, virtual_joystick);
        if (i == 0) zox_set(virtual_joystick, DeviceButtonType, { zox_device_stick_left })
        else zox_set(virtual_joystick, DeviceButtonType, { zox_device_stick_right })
    }
    touchscreen_entity = e;
    return e;
}

unsigned char zevice_pointer_has_input(const ZevicePointer *zevicePointer) {
    return devices_get_is_pressed(zevicePointer->value) || devices_get_pressed_this_frame(zevicePointer->value);
}

unsigned char touchscreen_is_any_input(ecs_world_t *world, const ecs_entity_t touchscreen) {
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
