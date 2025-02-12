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
