void delete_virtual_joystick(ecs_world_t *world, const ecs_entity_t canvas) {
    find_child_with_tag(canvas, JoystickUI, joystick_ui)
    if (joystick_ui) zox_delete(joystick_ui)
}

void handle_touch_drag(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t zevice_entity, const ecs_entity_t linked_virtual_joystick, const unsigned char is_playing) {
    const ZevicePointer *zevicePointer = zox_get(zevice_entity, ZevicePointer)
    if (devices_get_pressed_this_frame(zevicePointer->value)) {
        delete_virtual_joystick(world, canvas);
        const ZevicePointerPosition *zevicePointerPosition = zox_get(zevice_entity, ZevicePointerPosition)
        if (is_playing) spawn_virtual_joystick(world, canvas, zevicePointerPosition->value);
    } else if (devices_get_released_this_frame(zevicePointer->value)) {
        ZeviceStick *zeviceStick = zox_get_mut(linked_virtual_joystick, ZeviceStick)
        zeviceStick->value = float2_zero;
        zox_modified(linked_virtual_joystick, ZeviceStick);
        delete_virtual_joystick(world, canvas);
    } else if (devices_get_is_pressed(zevicePointer->value)) {
        find_child_with_tag(canvas, JoystickUI, joystick_ui)
        if (!joystick_ui) return; // only  do this if joystick_ui exist
        const ZevicePointerPosition *zevicePointerPosition = zox_get(zevice_entity, ZevicePointerPosition)
        const PixelPosition *virtual_joystick_position = zox_get(joystick_ui, PixelPosition)
        const Children *ui_children = zox_get(joystick_ui, Children)
        const PixelSize *virtual_joystick_size = zox_get(joystick_ui, PixelSize)
        const ecs_entity_t joystick_pointer = ui_children->value[0];
        const PixelSize *virtual_joystick_pointer_size = zox_get(joystick_pointer, PixelSize)
        const int2 delta_position = int2_sub(zevicePointerPosition->value, virtual_joystick_position->value);
        int2 size_limits = int2_multiply_float(int2_sub(virtual_joystick_size->value, virtual_joystick_pointer_size->value), 0.5f);
        size_limits.x -= 10;
        size_limits.y -= 10;
        PixelPosition *pixel_position = zox_get_mut(joystick_pointer, PixelPosition)
        ZeviceStick *zeviceStick = zox_get_mut(linked_virtual_joystick, ZeviceStick);
        pixel_position->value.x = delta_position.x;
        pixel_position->value.y = delta_position.y;
        int2_limit(&pixel_position->value, size_limits);
        const float2 input_value = (float2) { pixel_position->value.x / (float) size_limits.x, pixel_position->value.y / (float) size_limits.y };
        zeviceStick->value = input_value;
        zox_modified(joystick_pointer, PixelPosition)
        zox_modified(linked_virtual_joystick, ZeviceStick)
    }
}
