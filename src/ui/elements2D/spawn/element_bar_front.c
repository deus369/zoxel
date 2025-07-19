ecs_entity_t spawn_elementbar2D_front(ecs_world_t *world,
    const ecs_entity_t canvas,
    const ecs_entity_t parent,
    const int2 parent_position,
    const int2 parent_size,
    const int2 canvas_size,
    const byte layer,
    const byte render_disabled,
    const color front_color)
{
    const byte margin = 6;
    const int2 pixel_size = (int2) { parent_size.x - margin * 2, parent_size.y - margin * 2 };
    const float2 anchor = (float2) { 0, 0.5f }; //  float2_half;
    const int2 position = int2_zero; // parent_position
    const int2 position_in_canvas = get_element_pixel_position_global(parent_position, parent_size, position, anchor);
    const float2 position2D = get_element_position(position_in_canvas, canvas_size);
    zox_instance(prefab_elementbar2D_front)
    zox_name("elementbar2D_front")
    zox_set(e, Color, { front_color })
    initialize_element(world, e, parent, canvas, int2_zero, pixel_size, int2_one, anchor, layer, position2D, position_in_canvas);
    zox_set(e, RenderDisabled, { render_disabled })
    zox_set(e, MeshDirty, { mesh_state_trigger })
    return e;
}