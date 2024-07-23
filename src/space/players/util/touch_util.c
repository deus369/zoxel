/*void delete_virtual_joystick(ecs_world_t *world, const ecs_entity_t canvas) {
    find_child_with_tag(canvas, JoystickUI, joystick_ui)
    if (joystick_ui) zox_delete(joystick_ui)
}*/

void handle_touch_drag(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t finger, const ecs_entity_t virtual_joystick, const unsigned char is_game_state_playing) {
    const ZevicePointer *zevicePointer = zox_get(finger, ZevicePointer)
    if (devices_get_pressed_this_frame(zevicePointer->value)) {
        // delete_virtual_joystick(world, canvas);
        const ZevicePointerPosition *zevicePointerPosition = zox_get(finger, ZevicePointerPosition)
        if (is_game_state_playing) spawn_virtual_joystick(world, canvas, zevicePointerPosition->value, finger, virtual_joystick);
    } else {
        if (!zox_has(virtual_joystick, ElementLink)) {
            return;
        }
        const ecs_entity_t joystick_element = zox_get_value(virtual_joystick, ElementLink)
        if (devices_get_released_this_frame(zevicePointer->value)) {
            zox_get_muter(virtual_joystick, ZeviceStick, zeviceStick)
            zeviceStick->value = float2_zero;
            if (joystick_element) zox_delete(joystick_element)
            zox_set(virtual_joystick, ElementLink, { 0 })
        } else if (devices_get_is_pressed(zevicePointer->value)) {
            const ZevicePointerPosition *zevicePointerPosition = zox_get(finger, ZevicePointerPosition)
            const PixelPosition *virtual_joystick_position = zox_get(joystick_element, PixelPosition)
            const Children *ui_children = zox_get(joystick_element, Children)
            const PixelSize *virtual_joystick_size = zox_get(joystick_element, PixelSize)
            const ecs_entity_t joystick_pointer = ui_children->value[0];
            const PixelSize *virtual_joystick_pointer_size = zox_get(joystick_pointer, PixelSize)
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
            if (joystick_element) zox_delete(joystick_element)  // assume not touching
            zox_set(virtual_joystick, ElementLink, { 0 })
        }
    }
}
