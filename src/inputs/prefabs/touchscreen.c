entity spawn_prefab_touchscreen(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("touchscreen")
    zox_add_tag(e, Touchscreen)
    zox_prefab_add(e, ScreenDimensions)
    zox_prefab_set(e, DeviceLayout, { 0 })
    return e;
}

entity spawn_touchscreen(ecs *world, const entity prefab) {
    zox_instance(prefab)
    zox_name("touchscreen")
    zox_get_muter(e, Children, children)
    for (byte i = 0; i < fingers_count; i++) {
        const entity finger = spawn_zevice_pointer(world, e, i, i);
        const entity virtual_joystick = spawn_zevice_stick(world, e, i, i);
        zox_add_tag(finger, Finger)
        zox_set(finger, VirtualZeviceLink, { virtual_joystick })
        add_to_Children(children, finger);
        add_to_Children(children, virtual_joystick);
        if (i == 0) zox_set(virtual_joystick, DeviceButtonType, { zox_device_stick_left })
        else zox_set(virtual_joystick, DeviceButtonType, { zox_device_stick_right })
    }
    return e;
}
