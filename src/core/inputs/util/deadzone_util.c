// #define zox_debug_deadzones

// dead zone magic
const float joystick_deadzone_time = 0.2f;
int joystick_deadzones_values[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int joystick_deadzones_new_values[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double joystick_deadzone_times[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned char joystick_deadzones_setting[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned char joystick_deadzones_set[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int apply_joystick_deadzone(const int index, int axis_value) {
#if defined(zox_disable_gamepad_deadzones)
    return axis_value;
#endif
    if (zox_current_time < 0.1) return axis_value;
    // double current_time = joystick_deadzone_times[index]; // zox_current_time
    if (joystick_deadzones_set[index]) { // current_time >= joystick_deadzone_time) {
        axis_value = axis_value - joystick_deadzones_values[index];
        if (axis_value < -32768) axis_value = -32768;
        else if (axis_value > 32768) axis_value = 32768;
        return axis_value;
    } else if (!joystick_deadzones_setting[index]) {
        // can start deadzoning?
        joystick_deadzones_setting[index] = 1;
        joystick_deadzone_times[index] = zox_current_time;
        joystick_deadzones_new_values[index] = axis_value;
#ifdef zox_debug_deadzones
        zox_log(" > joystick probing possible deadzone [%i::%i]\n", index, axis_value)
#endif
    } else {
        // if deadzonining and value is still the same for x seconds, set new deadzon
        if (joystick_deadzones_new_values[index] == axis_value) {
            if (zox_current_time - joystick_deadzone_times[index] >= joystick_deadzone_time) {
                joystick_deadzones_set[index] = 1;
                joystick_deadzones_values[index] = axis_value;
#ifdef zox_debug_deadzones
                zox_log(" > joystick deadzone set [%i::%i]\n", index, axis_value)
#endif
            }
        } else {
            // start timing again
            joystick_deadzone_times[index] = zox_current_time;
            joystick_deadzones_new_values[index] = axis_value;
#ifdef zox_debug_deadzones
            zox_log(" > joystick reset deadzone [%i] set: %f\n", index, axis_value)
#endif
        }
    }
    return axis_value;
}
