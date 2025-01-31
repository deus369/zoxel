ecs_entity_t spawn_prefab_gamepad(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("gamepad")
    zox_add_tag(e, Gamepad)
    zox_prefab_set(e, DeviceLayout, { 0 })
    return e;
}

ecs_entity_t spawn_gamepad(ecs_world_t *world, const unsigned char gamepad_type) {
    zox_instance(prefab_gamepad)
    zox_name("gamepad")
    zox_set(e, DeviceLayout, { gamepad_type })
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, 20)
    // spawns zevice_button at 0 to 13
    for (unsigned char i = 0; i < 14; i++) {
        // use gamepad layout
        unsigned char joystick_index = 0;
        if (gamepad_type == zox_gamepad_layout_type_xbox) {
            if (i == zox_device_button_lt) joystick_index = 11;
            else if (i == zox_device_button_rt) joystick_index = 12;
            else if (i == zox_device_button_select) joystick_index = 6;
            else if (i == zox_device_button_start) joystick_index = 7;
            else if (i == zox_device_button_left_stick_push) joystick_index = 9;
            else if (i == zox_device_button_right_stick_push) joystick_index = 10;
            else joystick_index = i;
        } else if (gamepad_type == zox_gamepad_layout_type_steamdeck) {
            // buttons
            if (i == zox_device_button_select) joystick_index = 6;
            else if (i == zox_device_button_start) joystick_index = 7;
            else if (i == zox_device_button_a) joystick_index = 0;
            else if (i == zox_device_button_b) joystick_index = 1;
            else if (i == zox_device_button_x) joystick_index = 2;
            else if (i == zox_device_button_y) joystick_index = 3;
            // bumpers
            else if (i == zox_device_button_lb) joystick_index = 4;
            else if (i == zox_device_button_rb) joystick_index = 5;
            else if (i == zox_device_button_lt) joystick_index = 8;
            else if (i == zox_device_button_rt) joystick_index = 9;
            // joysticks
            else if (i == zox_device_button_left_stick_push) joystick_index = 10;
            else if (i == zox_device_button_right_stick_push) joystick_index = 11;
            else joystick_index = i;
        } else {
            if (i == zox_device_button_x) joystick_index = 3;
            else if (i == zox_device_button_y) joystick_index = 4;
            else if (i == zox_device_button_lb) joystick_index = 6;
            else if (i == zox_device_button_rb) joystick_index = 7;
            else if (i == zox_device_button_lt) joystick_index = 8;
            else if (i == zox_device_button_rt) joystick_index = 9;
            else if (i == zox_device_button_select) joystick_index = 10;
            else if (i == zox_device_button_start) joystick_index = 11;
            else if (i == zox_device_button_left_stick_push) joystick_index = 13;
            else if (i == zox_device_button_right_stick_push) joystick_index = 14;
            else joystick_index = i;
        }
        children->value[i] = spawn_device_button(world, i, joystick_index);
    }
    // spawns zevice_stick at 14, 15
    for (unsigned char i = 0; i < 2; i++) {
        unsigned char j = 14 + i;
        unsigned char joystick_index;
        if (gamepad_type == zox_gamepad_layout_type_steamdeck) {
            if (i == 0) joystick_index = 0; // 0, 1
            else joystick_index = 3; // 3, 4
        } else {
            joystick_index = i * 2;
        }
        children->value[j] = spawn_zevice_stick(world, e, i, joystick_index);
    }
    children->value[16] = spawn_device_button(world, 16, zox_device_button_dpad_down);
    children->value[17] = spawn_device_button(world, 17, zox_device_button_dpad_up);
    children->value[18] = spawn_device_button(world, 18, zox_device_button_dpad_left);
    children->value[19] = spawn_device_button(world, 19, zox_device_button_dpad_right);
    // todo: spawn LT and RT as axis for steamdeck

    zox_modified(e, Children)
    gamepad_entity = e;
    return e;
}

unsigned char gamepad_is_any_input(ecs_world_t *world, const ecs_entity_t gamepad) {
    const Children *children = zox_get(gamepad, Children)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e = children->value[i];
#ifndef zox_disable_gamepad_stick_as_any_input
        if (zox_has(e, ZeviceStick)) {
            const ZeviceStick *zeviceStick = zox_get(e, ZeviceStick)
            return zevice_stick_has_input(zeviceStick, joystick_min_cutoff);
        } else
#endif
        if (zox_has(e, ZeviceButton)) {
            const ZeviceButton *zeviceButton = zox_get(e, ZeviceButton)
            if (devices_get_pressed_this_frame(zeviceButton->value)) return 1;
        }
    }
    return 0;
}
