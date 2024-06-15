// button flags
#define zox_device_is_pressed 1 // 00000001
#define zox_device_pressed_this_frame 2 // 00000010
#define zox_device_released_this_frame 4 // 00000100

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

unsigned char devices_get_is_pressed(unsigned char value) {
    return value & zox_device_is_pressed;
}

unsigned char devices_get_pressed_this_frame(unsigned char value) {
    return value & zox_device_pressed_this_frame;
}

unsigned char devices_get_released_this_frame(unsigned char value) {
    return value & zox_device_released_this_frame;
}

void test_device_button_flags() {
    unsigned char test = 0;
    devices_set_is_pressed(&test, 1);
    zoxel_log(" test 1 set_is_pressed [%i]\n", test);
    devices_set_pressed_this_frame(&test, 1);
    zoxel_log(" test 2 set_pressed_this_frame [%i]\n", test);
    devices_set_released_this_frame(&test, 1);
    zoxel_log(" test 3 set_released_this_frame [%i]\n", test);
    devices_set_pressed_this_frame(&test, 0);
    zoxel_log(" test 4 set_pressed_this_frame(0) [%i]\n", test);
    devices_set_is_pressed(&test, 0);
    zoxel_log(" test 5 set_is_pressed(0) [%i]\n", test);
    devices_set_released_this_frame(&test, 0);
    zoxel_log(" test 6 set_released_this_frame(0) [%i]\n", test);
    unsigned char test2 = 0;
    devices_set_released_this_frame(&test2, 1);
    zoxel_log(" test 2-1 set_released_this_frame [%i]\n", test2);
    zoxel_log(" test 2-2 get_released_this_frame [%s]\n", devices_get_released_this_frame(test2) ? "yes" : "no");
    devices_set_released_this_frame(&test2, 0);
    zoxel_log(" test 2-3 set_released_this_frame [%i]\n", test2);
    zoxel_log(" test 2-4 get_released_this_frame [%s]\n", devices_get_released_this_frame(test2) ? "yes" : "no");
}
