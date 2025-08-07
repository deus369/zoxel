// todo: stretch to canvas_size, AnchorSize
entity spawn_render_texture(
    ecs *world,
    const entity prefab,
    const entity canvas,
    const int2 layout_size,
    const int2 texture_size,
    const entity camera
) {
    const byte layer = 0;
    const entity parent = canvas;
    const int2 position = int2_zero;
    const float2 anchor = float2_half;
    int2 position_in_canvas = get_element_pixel_position_global(int2_half(layout_size), layout_size, position, anchor);
    const float2 position_real = get_element_position(position_in_canvas, layout_size);
    zox_instance(prefab)
    zox_name("render_texture")
    initialize_element(world,
        e,
        parent,
        canvas,
        position,
        layout_size,
        texture_size,
        anchor,
        layer,
        position_real,
        position_in_canvas);
    zox_set(e, CameraLink, { camera })
    return e;
}