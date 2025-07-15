// todo: stretch to canvas_size, AnchorSize
ecs_entity_t spawn_render_texture(ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t canvas,
    const int2 canvas_size,
    const ecs_entity_t camera)
{
    const byte layer = 0;
    const ecs_entity_t parent = canvas;
    const int2 position = int2_zero;
    const float2 anchor = float2_half;
    const int2 size = canvas_size;
    int2 position_in_canvas = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, position, anchor);
    const float2 position_real = get_element_position(position_in_canvas, canvas_size);
    zox_instance(prefab)
    zox_name("render_texture")
    zox_set(e, CameraLink, { camera })
    initialize_element(world, e, parent, canvas, position, size, size, anchor, layer, position_real, position_in_canvas);
    return e;
}