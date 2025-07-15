ecs_entity_t spawn_prefab_virtual_joystick(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("virtual_joystick")
    zox_add_tag(e, JoystickUI)
    zox_add_tag(e, Button)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 2 })
    zox_prefab_set(e, OutlineThickness, { 2 })
    zox_prefab_set(e, Color, { virtual_joystick_color })
    zox_prefab_add(e, Children)
    add_ui_plus_components(world, e);
    zox_prefab_add(e, ZeviceLink)
    return e;
}

ecs_entity_t spawn_virtual_joystick(ecs_world_t *world, const ecs_entity_t canvas, const int2 pixel_position, const ecs_entity_t finger, const ecs_entity_t virtual_joystick, const byte button_type) {
    const float2 anchor = float2_zero;
    const byte layer = 4;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    int2 pixel_size = virtual_joystick_size;
    fix_for_screen_size(&pixel_size, viewport_dimensions);
    zox_instance(prefab_virtual_joystick)
    zox_name("virtual_joystick")
    ecs_entity_t parent = canvas;
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    zox_get_muter(e, Children, children)
    resize_memory_component(Children, children, ecs_entity_t, 1)
    children->value[0] = spawn_virtual_joystick_pointer(world, canvas, e, (layer + 1), int2_zero, float2_half, pixel_position_global, pixel_size, canvas_size);
    // links
    zox_set(e, ZeviceLink, { virtual_joystick })
    zox_set(virtual_joystick, ElementLink, { e })
    // zox_gett_value(finger, DeviceButtonType)
    zox_set(finger, DeviceButtonType, { button_type })
    zox_set(virtual_joystick, DeviceButtonType, { button_type })
    if (button_type == zox_device_stick_right) {
        zox_set(e, Color, { virtual_joystick_color2 })
        zox_set(children->value[0], Color, { virtual_joystick_pointer_color2 })
    }
    return e;
}
