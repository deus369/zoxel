#define zox_gamepad_layout_type_normal 0
#define zox_gamepad_layout_type_xbox 1
#define zox_gamepad_layout_type_steamdeck 2

ecs_entity_t prefab_gamepad;
ecs_entity_t gamepad_entity;

ecs_entity_t spawn_prefab_gamepad(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_gamepad")
    zox_add_tag(e, Device)
    zox_add_tag(e, Gamepad)
    zox_prefab_set(e, DeviceLayout, { 0 })
    zox_prefab_add(e, Children)
    prefab_gamepad = e;
    return e;
}

ecs_entity_t spawn_gamepad(ecs_world_t *world, const unsigned char gamepad_type) {
    zox_instance(prefab_gamepad)
    zox_name("gamepad")
    zox_set(e, DeviceLayout, { gamepad_type })
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, 16)
    // spawns zevice_button at 0 to 13
    for (unsigned char i = 0; i < 14; i++) {
        // use gamepad layout
        unsigned char joystick_index = 0;
        if (gamepad_type == zox_gamepad_layout_type_xbox || gamepad_type == zox_gamepad_layout_type_steamdeck) {
            if (i == zox_device_button_lt) joystick_index = 11;
            else if (i == zox_device_button_rt) joystick_index = 12;
            else if (i == zox_device_button_select) joystick_index = 6;
            else if (i == zox_device_button_start) joystick_index = 7;
            else if (i == zox_device_button_left_stick_push) joystick_index = 9;
            else if (i == zox_device_button_right_stick_push) joystick_index = 10;
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
    for (unsigned char i = 0, j = 14; j < 16; i++, j++) {
        unsigned char joystick_index = i * 2;
        if (i == 1 && gamepad_type == zox_gamepad_layout_type_steamdeck) joystick_index++;
        children->value[j] = spawn_zevice_stick(world, i, joystick_index);
    }
    zox_modified(e, Children)
    gamepad_entity = e;
    return e;
}

unsigned char zevice_stick_has_input(const ZeviceStick *zeviceStick, const float cutoff) {
    return float_abs(zeviceStick->value.x) > cutoff || float_abs(zeviceStick->value.y) > cutoff;
}

unsigned char gamepad_is_any_input(ecs_world_t *world, const ecs_entity_t gamepad) {
    const Children *children = zox_get(gamepad, Children)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e = children->value[i];
#ifndef zox_disable_gamepad_stick_as_any_input
        if (zox_has(e, ZeviceStick)) {
            const ZeviceStick *zeviceStick = zox_get(e, ZeviceStick)
            return zevice_stick_has_input(zeviceStick, joystick_min_cutoff2);
        } else
#endif
        if (zox_has(e, ZeviceButton)) {
            const ZeviceButton *zeviceButton = zox_get(e, ZeviceButton)
            if (devices_get_pressed_this_frame(zeviceButton->value)) return 1;
        }
    }
    return 0;
}
