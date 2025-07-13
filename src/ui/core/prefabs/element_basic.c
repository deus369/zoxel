ecs_entity_t spawn_prefab_element_basic(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_element_basic")
    // texture
    zox_add_tag(e, Texture)
    zox_prefab_set(e, TextureData, { 0, NULL })
    zox_prefab_set(e, TextureSize, { int2_zero })
    zox_prefab_set(e, TextureDirty, { 0 })
    zox_prefab_set(e, Color, { color_white })   // do i need this here? does basic lack texture info for generation?
    // rendering
    zox_add_tag(e, ElementRender)
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, Brightness, { 1 })
    zox_prefab_set(e, Alpha, { 1 })
    if (!headless) {
        zox_prefab_set(e, MeshDirty, { mesh_state_trigger2 })
        zox_prefab_set(e, MeshAlignment, { zox_mesh_alignment_centred })
        zox_prefab_add(e, MeshIndicies)
        zox_prefab_add(e, MeshVertices2D)
        zox_prefab_add(e, MeshUVs)
        zox_prefab_set(e, MeshGPULink, { { 0, 0 } })
        zox_prefab_set(e, TextureGPULink, { 0 })
        zox_prefab_set(e, UvsGPULink, { 0 })
        prefab_set_ui_mesh(world, e);
    }
    return e;
}

ecs_entity_t spawn_element_basic(ecs_world_t *world,
    const ecs_entity_t canvas,
    const ecs_entity_t parent,
    int2 position,
    const int2 pixel_size,
    const int2 texture_size,
    const float2 anchor,
    const byte layer,
    const int2 parent_position,
    const int2 parent_size)
{
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int2 position_in_canvas = get_element_pixel_position_global(parent_position, parent_size, position, anchor);
    const float2 position_real = get_element_position(position_in_canvas, canvas_size);
    anchor_element_position2D(&position, anchor, pixel_size);
    zox_instance(prefab_element_basic)
    zox_name("element_basic")
    initialize_element(world, e, parent, canvas, position, pixel_size, texture_size, anchor, layer, position_real, position_in_canvas);
    return e;
}

ecs_entity_t spawn_element_basic_on_canvas(ecs_world_t *world,
    const ecs_entity_t canvas,
    const int2 position,
    const int2 pixel_size,
    const int2 texture_size,
    const float2 anchor)
{
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    return spawn_element_basic(world, canvas, canvas, position, pixel_size, texture_size, anchor, 0, int2_half(canvas_size), canvas_size);
}
