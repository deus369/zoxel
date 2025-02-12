// resets the single frame states
unsigned char reset_button_state(const unsigned char previous_state) {
    unsigned char new_state = previous_state;
    if (devices_get_pressed_this_frame(previous_state)) devices_set_pressed_this_frame(&new_state, 0);
    else if (devices_get_released_this_frame(previous_state)) devices_set_released_this_frame(&new_state, 0);
    return new_state;
}

unsigned char reset_device_button(ZeviceButton *zeviceButton) {
    unsigned char previous_value = zeviceButton->value;
    if (devices_get_pressed_this_frame(zeviceButton->value)) devices_set_pressed_this_frame(&zeviceButton->value, 0);
    else if (devices_get_released_this_frame(zeviceButton->value)) devices_set_released_this_frame(&zeviceButton->value, 0);
    return previous_value != zeviceButton->value;
}
