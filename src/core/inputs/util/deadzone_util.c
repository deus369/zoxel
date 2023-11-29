// #define zox_debug_deadzones
// dead zone magic
const float joystick_deadzone_time = 1.0f;
unsigned char joystick_deadzones[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double joystick_deadzone_times[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float joystick_deadzones_values[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float joystick_deadzones_new_values[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

float apply_joystick_deadzone(int index, float axis_value) {
#if defined(zox_disable_gamepad_deadzones)
    return axis_value;
#endif
    if (zox_current_time >= 3) return axis_value;
    // checks for deadzones
    if (joystick_deadzones[index] == 0) {
        // can start deadzoning?
        if (axis_value == joystick_deadzones_new_values[index]) {
            if (axis_value != joystick_deadzones_values[index] && float_abs(axis_value) < 0.4f) { // 
                joystick_deadzones[index] = 1;
                joystick_deadzone_times[index] = zox_current_time;
                // zoxel_log(" > joystick probing possible deadzone [%i::%f]\n", index, axis_value);
            }
        }
        joystick_deadzones_new_values[index] = axis_value;
    } else {
        // if deadzonining and value is still the same for x seconds, set new deadzon
        if (joystick_deadzones_new_values[index] == axis_value) {
            // zoxel_log(" > joystick probing deadzone [%i] time passed: %f\n", index, (zox_current_time - joystick_deadzone_times[index]));
            if (zox_current_time - joystick_deadzone_times[index] >= joystick_deadzone_time) {
                joystick_deadzones[index] = 0;
                joystick_deadzones_values[index] = axis_value;
#ifdef zox_debug_deadzones
                zox_log(" > joystick deadzone set [%i::%f]\n", index, axis_value)
#endif
            }
        } else {
            // cancel it
            joystick_deadzones[index] = 0;
            joystick_deadzones_new_values[index] = axis_value;
            // zoxel_log(" > joystick reset deadzone [%i] set: %f\n", index, axis_value);
        }
    }
    axis_value -= joystick_deadzones_values[index];
    return axis_value;
}
