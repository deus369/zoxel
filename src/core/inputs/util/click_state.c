unsigned char get_button_click_state(unsigned char previous_state, unsigned char new_pressed) {
    unsigned char new_state = previous_state;
    if (!new_pressed) {
        if (devices_get_is_pressed(previous_state)) {
            devices_set_is_pressed(&new_state, 0);
            devices_set_released_this_frame(&new_state, 1);
        }
    } else {
        if (!devices_get_is_pressed(previous_state)) {
            devices_set_pressed_this_frame(&new_state, 1);
            devices_set_is_pressed(&new_state, 1);
        }
        // else keep pressed
    }
    return new_state;
}

unsigned char zevice_pointer_has_input(const ZevicePointer *zevicePointer) {
    return devices_get_is_pressed(zevicePointer->value) || devices_get_pressed_this_frame(zevicePointer->value);
}

unsigned char zevice_stick_has_input(const ZeviceStick *zeviceStick, const float cutoff) {
    return float_abs(zeviceStick->value.x) > cutoff || float_abs(zeviceStick->value.y) > cutoff;
}
