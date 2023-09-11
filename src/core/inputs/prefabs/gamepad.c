#define zox_gamepad_layout_type_normal 0
#define zox_gamepad_layout_type_xbox 1
#define zox_gamepad_layout_type_steamdeck 2

ecs_entity_t prefab_gamepad;
ecs_entity_t gamepad_entity;

ecs_entity_t spawn_prefab_gamepad(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("gamepad_prefab")
    zox_add_tag(e, Device)
    zox_add_tag(e, Gamepad)
    zox_set(e, DeviceLayout, { 0 })
    zox_set(e, Children, { 0, NULL })
    // zox_set(e, Gamepad, gamepad_zero)
    ecs_defer_end(world);
    prefab_gamepad = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab gamepad [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_gamepad(ecs_world_t *world, unsigned char gamepad_type) {
    zox_instance(prefab_gamepad)
    zox_name("gamepad")
    zox_set_only(e, DeviceLayout, { gamepad_type })
    // zoxel_log("gamepad_type [%i]\n", gamepad_type);
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, 16)
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
        children.value[i] = spawn_device_button(world, i, joystick_index);
    }
    for (unsigned char i = 0, j = 14; j < 16; i++, j++) {
        unsigned char joystick_index = i * 2;
        if (i == 1 && gamepad_type == zox_gamepad_layout_type_steamdeck) joystick_index++;
        children.value[j] = spawn_device_stick(world, i, joystick_index);
    }
    /*
        set_gamepad_button(&gamepad->a, joystick, 0);
        set_gamepad_button(&gamepad->b, joystick, 1);
        set_gamepad_button(&gamepad->x, joystick, 2);
        set_gamepad_button(&gamepad->y, joystick, 3);
        set_gamepad_button(&gamepad->lb, joystick, 4);
        set_gamepad_button(&gamepad->rb, joystick, 5);
        set_gamepad_button(&gamepad->select, joystick, 6);
        set_gamepad_button(&gamepad->start, joystick, 7);
        set_gamepad_button(&gamepad->left_stick_push, joystick, 9);
        set_gamepad_button(&gamepad->right_stick_push, joystick, 10);
        set_gamepad_button(&gamepad->lt, joystick, 11);
        set_gamepad_button(&gamepad->rt, joystick, 12);
    */
    zox_set_only(e, Children, { children.length, children.value })
    gamepad_entity = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned gamepad [%lu].\n", (long int) (e));
    #endif
    return e;
}

unsigned char zevice_stick_has_input(const ZeviceStick *zeviceStick, float cutoff) {
    return float_abs(zeviceStick->value.x) > cutoff || float_abs(zeviceStick->value.y) > cutoff;
}

/*void device_reset_gamepad(ecs_world_t *world, ecs_entity_t gamepad) {
    if (!gamepad || !ecs_is_alive(world, gamepad)) return;
    const Children *children = ecs_get(world, gamepad, Children);
    for (int i = 0; i < children->length; i++) {
        ecs_entity_t e = children->value[i];
        if (ecs_has(world, e, ZeviceButton)) {
            ZeviceButton *zeviceButton = ecs_get_mut(world, e, ZeviceButton);
            if (reset_device_button(zeviceButton)) ecs_modified(world, e, ZeviceButton);
        }
    }
}*/

unsigned char gamepad_is_any_input(ecs_world_t *world, ecs_entity_t gamepad) {
    const Children *children = ecs_get(world, gamepad, Children);
    for (int i = 0; i < children->length; i++) {
        ecs_entity_t e = children->value[i];
        #ifndef zox_disable_gamepad_stick_as_any_input
            if (ecs_has(world, e, ZeviceStick)) {
                const ZeviceStick *zeviceStick = ecs_get(world, e, ZeviceStick);
                // if (set_gamepad_axis2(zeviceStick, joystick, realButtonIndex->value)) ecs_modified(world, e, ZeviceStick);
                return zevice_stick_has_input(zeviceStick, joystick_min_cutoff2); // float_abs(zeviceStick->value.x) >= joystick_min_cutoff2 || float_abs(zeviceStick->value.y) >= joystick_min_cutoff2;
            } else 
        #endif
        if (ecs_has(world, e, ZeviceButton)) {
            const ZeviceButton *zeviceButton = ecs_get(world, e, ZeviceButton);
            if (devices_get_pressed_this_frame(zeviceButton->value)) return 1;
        }
    }
    return 0;
}

/*ZeviceButton *zeviceButton = ecs_get_mut(world, e, ZeviceButton);
reset_device_button(zeviceButton);
ecs_modified(world, e, ZeviceButton);*/
/*if (ecs_has(world, e, ZeviceStick)) {
    // zoxel_log(" > device stick found [%i] %lu\n", i, e);
    ZeviceStick *zeviceStick = ecs_get_mut(world, e, ZeviceStick);
    if (set_gamepad_axis2(zeviceStick, joystick, realButtonIndex->value)) ecs_modified(world, e, ZeviceStick);
    // if (ecs_has(world, e, ZeviceButton)) zoxel_log("    ! error with device stick, contains device button data[%i]\n", e);
} else */