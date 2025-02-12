unsigned char touchscreen_is_any_input(ecs_world_t *world, const ecs_entity_t e) {
    if (!e || !zox_alive(e)) {
        return 0;
    }
    zox_geter(e, Children, children)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e2 = children->value[i];
        if (!e2 || !zox_has(e2, ZevicePointer) || !zox_has(e2, Finger)) continue;
        zox_geter(e2, ZevicePointer, zevicePointer)
        if (zevice_pointer_has_input(zevicePointer)) return 1;
    }
    return 0;
}

unsigned char mouse_is_any_input(ecs_world_t *world, const ecs_entity_t e) {
    if (!e || !zox_alive(e)) {
        return 0;
    }
    const Children *children = zox_get(e, Children)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e = children->value[i];
        if (!zox_has(e, ZevicePointer)) {
            continue;
        }
        zox_geter(e, ZevicePointer, zevicePointer)
        if (zevice_pointer_has_input(zevicePointer)) {
            return 1;
        }
    }
    return 0;
}

byte gamepad_is_any_input(ecs_world_t *world, const ecs_entity_t e) {
    if (!e || !zox_alive(e)) {
        return 0;
    }
    const Children *children = zox_get(e, Children)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e2 = children->value[i];
        #ifndef zox_disable_gamepad_stick_as_any_input
        if (zox_has(e2, ZeviceStick)) {
            zox_geter(e2, ZeviceStick, zeviceStick)
            return zevice_stick_has_input(zeviceStick, joystick_min_cutoff);
        } else
        #endif
            if (zox_has(e2, ZeviceButton)) {
                zox_geter(e2, ZeviceButton, zeviceButton)
                if (devices_get_pressed_this_frame(zeviceButton->value)) {
                    return 1;
                }
            }
    }
    return 0;
}