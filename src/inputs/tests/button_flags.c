void test_device_button_flags() {
    byte test = 0;
    devices_set_is_pressed(&test, 1);
    zox_log(" test 1 set_is_pressed [%i]\n", test);
    devices_set_pressed_this_frame(&test, 1);
    zox_log(" test 2 set_pressed_this_frame [%i]\n", test);
    devices_set_released_this_frame(&test, 1);
    zox_log(" test 3 set_released_this_frame [%i]\n", test);
    devices_set_pressed_this_frame(&test, 0);
    zox_log(" test 4 set_pressed_this_frame(0) [%i]\n", test);
    devices_set_is_pressed(&test, 0);
    zox_log(" test 5 set_is_pressed(0) [%i]\n", test);
    devices_set_released_this_frame(&test, 0);
    zox_log(" test 6 set_released_this_frame(0) [%i]\n", test);
    byte test2 = 0;
    devices_set_released_this_frame(&test2, 1);
    zox_log(" test 2-1 set_released_this_frame [%i]\n", test2);
    zox_log(" test 2-2 get_released_this_frame [%s]\n", devices_get_released_this_frame(test2) ? "yes" : "no");
    devices_set_released_this_frame(&test2, 0);
    zox_log(" test 2-3 set_released_this_frame [%i]\n", test2);
    zox_log(" test 2-4 get_released_this_frame [%s]\n", devices_get_released_this_frame(test2) ? "yes" : "no");
}
