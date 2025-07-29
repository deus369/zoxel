int virtual_joysticks_spawn_count = 0;
unsigned first_joystick_type = zox_device_stick_left;

void handle_touch_drag(ecs_world_t *world,
    const ecs_entity_t canvas,
    const ecs_entity_t finger,
    const ecs_entity_t virtual_joystick,
    const byte is_game_state_playing)
{
    if (!zox_valid(finger) || !zox_has(finger, ZevicePointer) || !zox_has(finger, ZevicePointerPosition)) {
        return;
    }
    zox_geter(finger, ZevicePointer, zevicePointer)
    if (devices_get_pressed_this_frame(zevicePointer->value)) {
        // delete_virtual_joystick(world, canvas);
        zox_geter(finger, ZevicePointerPosition, zevicePointerPosition)
        if (is_game_state_playing) {
            byte button_type = zox_device_stick_left;
            zox_geter_value(finger, DeviceLink, ecs_entity_t, touchscreen)
            if (!zox_valid(touchscreen) || !zox_has(touchscreen, ScreenDimensions)) {
                zox_log_error("touchscreen invalid")
                return;
            }
            zox_geter_value(touchscreen, ScreenDimensions, int2, size)
            if (zevicePointerPosition->value.x >= size.x / 2) {
                button_type = zox_device_stick_right;
            }
            spawn_virtual_joystick(world, canvas, zevicePointerPosition->value, finger, virtual_joystick, button_type);
            virtual_joysticks_spawn_count++;
        }
    } else {
        // ui wasn't spawned, return
        if (!zox_has(virtual_joystick, ElementLink)) {
            return;
        }
        const ecs_entity_t joystick_element = zox_get_value(virtual_joystick, ElementLink)
        if (!zox_valid(joystick_element)) {
            return;
        }
        if (devices_get_released_this_frame(zevicePointer->value)) {
            zox_get_muter(virtual_joystick, ZeviceStick, zeviceStick)
            zeviceStick->value = float2_zero;
            if (joystick_element) {
                zox_delete(joystick_element)
                zox_set(virtual_joystick, ElementLink, { 0 })
                virtual_joysticks_spawn_count--;
            }
        } else if (devices_get_is_pressed(zevicePointer->value)) {
            zox_geter(finger, ZevicePointerPosition, zevicePointerPosition)
            zox_geter(joystick_element, PixelPosition, virtual_joystick_position)
            zox_geter(joystick_element, Children, ui_children)
            zox_geter(joystick_element, PixelSize, virtual_joystick_size)
            const ecs_entity_t joystick_pointer = ui_children->value[0];
            if (!zox_valid(joystick_pointer)) {
                zox_log_error("invalid joystick_pointer, parent [%s]", zox_get_name(joystick_element))
                return;
            }
            zox_geter(joystick_pointer, PixelSize, virtual_joystick_pointer_size)
            const int2 delta_position = int2_sub(zevicePointerPosition->value, virtual_joystick_position->value);
            int2 size_limits = int2_multiply_float(int2_sub(virtual_joystick_size->value, virtual_joystick_pointer_size->value), 0.5f);
            size_limits.x -= 10;
            size_limits.y -= 10;
            zox_get_muter(joystick_pointer, PixelPosition, pixel_position)
            zox_get_muter(virtual_joystick, ZeviceStick, zeviceStick)
            pixel_position->value.x = delta_position.x;
            pixel_position->value.y = delta_position.y;
            int2_limit(&pixel_position->value, size_limits);
            const float2 input_value = (float2) { pixel_position->value.x / (float) size_limits.x, pixel_position->value.y / (float) size_limits.y };
            zeviceStick->value = input_value;
        } else {
            if (joystick_element) {
                zox_delete(joystick_element)  // assume not touching
                zox_set(virtual_joystick, ElementLink, { 0 })
                virtual_joysticks_spawn_count--;
            }
        }
    }
}
