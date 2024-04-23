ecs_entity_t prefab_virtual_joystick;
ecs_entity_t virtual_joystick;  // reference for now

ecs_entity_t spawn_prefab_virtual_joystick(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_virtual_joystick")
    zox_add_tag(e, Button)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 2 })
    zox_prefab_set(e, OutlineThickness, { 2 })
    zox_prefab_set(e, Color, { virtual_joystick_color })
    zox_prefab_set(e, Children, { 0, NULL })
    add_ui_plus_components(world, e);
    prefab_virtual_joystick = e;
    return e;
}

ecs_entity_t spawn_virtual_joystick(ecs_world_t *world, int2 pixel_position) {
    ecs_entity_t canvas = main_canvas;
    int2 pixel_size = virtual_joystick_size;
    fix_for_screen_size(&pixel_size, screen_dimensions);
    float2 anchor = float2_zero;
    const unsigned char layer = 4;
    int2 canvas_size = zox_get_value(canvas, PixelSize)
    zox_instance(prefab_virtual_joystick)
    zox_name("virtual_joystick")
    ecs_entity_t parent = canvas;
    int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, 1)
    children->value[0] = spawn_virtual_joystick_pointer(world, e, canvas, (layer + 1), (int2) { 0, 0 }, (float2) { 0.5f, 0.5f }, pixel_position_global, pixel_size, canvas_size);
    zox_modified(e, Children)
    virtual_joystick = e;
    return e;
}
