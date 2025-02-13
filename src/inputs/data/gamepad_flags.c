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
#define zox_device_button_dpad_down 14
#define zox_device_button_dpad_up 15
#define zox_device_button_dpad_left 16
#define zox_device_button_dpad_right 17

byte is_dpad_button(const byte index) {
    return index >= zox_device_button_dpad_down && index <= zox_device_button_dpad_right;
}
