ecs_entity_t spawn_virtual_joystick(
    ecs_world_t *world,
    const ecs_entity_t canvas,
    const int2 pixel_position,
    const ecs_entity_t finger,
    const ecs_entity_t virtual_joystick,
    const byte button_type
) {
    const float2 anchor = float2_zero;
    const byte layer = 4;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    int2 pixel_size = virtual_joystick_size;
    zox_instance(prefab_virtual_joystick)
    zox_name("virtual_joystick")
    ecs_entity_t parent = canvas;
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    // zox_get_muter(e, Children, children)

    Children children = (Children) { };
    ecs_entity_t joystick = spawn_virtual_joystick_pointer(world,
        canvas,
        e,
        (layer + 1),
        int2_zero,
        float2_half,
        pixel_position_global,
        pixel_size,
        canvas_size);
    add_to_Children(&children, joystick);
    zox_set_ptr(e, Children, children);

    // links
    zox_set(e, ZeviceLink, { virtual_joystick })
    zox_set(virtual_joystick, ElementLink, { e })
    // zox_gett_value(finger, DeviceButtonType)
    zox_set(finger, DeviceButtonType, { button_type })
    zox_set(virtual_joystick, DeviceButtonType, { button_type })
    if (button_type == zox_device_stick_right) {
        zox_set(e, Color, { virtual_joystick_color2 })
        zox_set(joystick, Color, { virtual_joystick_pointer_color2 })
    }
    return e;
}
