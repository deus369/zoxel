
#define zox_device_button_a 0
#define zox_device_button_b 1
#define zox_device_button_x 2
#define zox_device_button_y 3
#define zox_device_button_lb 4
#define zox_device_button_rb 5
#define zox_device_button_lt 6
#define zox_device_button_rt 7
#define zox_device_button_select 8
#define zox_device_button_start 9
#define zox_device_button_left_stick_push 10
#define zox_device_button_right_stick_push 11
#define zox_device_button_left_stick 12
#define zox_device_button_right_stick 13

/*
set_gamepad_button(&gamepad->a, joystick, 0);
set_gamepad_button(&gamepad->b, joystick, 1);
set_gamepad_button(&gamepad->x, joystick, 3);
set_gamepad_button(&gamepad->y, joystick, 4);
set_gamepad_button(&gamepad->lb, joystick, 6);
set_gamepad_button(&gamepad->rb, joystick, 7);
set_gamepad_button(&gamepad->lt, joystick, 8);
set_gamepad_button(&gamepad->rt, joystick, 9);
set_gamepad_button(&gamepad->select, joystick, 10);
set_gamepad_button(&gamepad->start, joystick, 11);
set_gamepad_button(&gamepad->left_stick_push, joystick, 13);
set_gamepad_button(&gamepad->right_stick_push, joystick, 14);
*/

ecs_entity_t prefab_device_button;

ecs_entity_t spawn_prefab_device_button(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_device_button")
    zox_add_tag(e, Zevice)
    zox_set(e, ZeviceDisabled, { 0 })
    zox_set(e, DeviceButton, { 0 })
    zox_set(e, DeviceButtonType, { 0 })
    zox_set(e, RealButtonIndex, { 0 })
    ecs_defer_end(world);
    prefab_device_button = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab device_button [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_device_button(ecs_world_t *world, unsigned char type, unsigned char index) {
    zox_instance(prefab_device_button)
    zox_name("device_button")
    zox_set(e, DeviceButtonType, { type })
    zox_set(e, RealButtonIndex, { index })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned device_button [%lu].\n", (long int) (e));
    #endif
    return e;
}

// button flags
#define zox_device_is_pressed 1 // 00000001
#define zox_device_pressed_this_frame 2 // 00000010
#define zox_device_released_this_frame 4 // 00000100

unsigned char devices_get_is_pressed(unsigned char value) {
    return value & zox_device_is_pressed;
}

void devices_set_is_pressed(unsigned char *value, unsigned char new_state) {
    if (new_state == 0) *value = *value & ~zox_device_is_pressed;  // removes the flag
    else *value = *value | zox_device_is_pressed;
}

void devices_set_pressed_this_frame(unsigned char *value, unsigned char new_state) {
    if (new_state == 0) *value = *value & ~zox_device_pressed_this_frame;  // removes the flag
    else *value = *value | zox_device_pressed_this_frame;
}

void devices_set_released_this_frame(unsigned char *value, unsigned char new_state) {
    if (new_state == 0) *value = *value & ~zox_device_released_this_frame;  // removes the flag
    else *value = *value | zox_device_released_this_frame;
}

unsigned char devices_get_pressed_this_frame(unsigned char value) {
    return value & zox_device_pressed_this_frame;
}

unsigned char devices_get_released_this_frame(unsigned char value) {
    return value & zox_device_released_this_frame;
}

// todo: put this in a system on load instead
unsigned char reset_device_button(DeviceButton *deviceButton) {
    unsigned char previous_value = deviceButton->value;
    if (devices_get_pressed_this_frame(deviceButton->value)) devices_set_pressed_this_frame(&deviceButton->value, 0);
    else if (devices_get_released_this_frame(deviceButton->value)) devices_set_released_this_frame(&deviceButton->value, 0);
    return previous_value != deviceButton->value;
    // if (key->pressed_this_frame) key->pressed_this_frame = 0;
    // else if (key->released_this_frame) key->released_this_frame = 0;
}