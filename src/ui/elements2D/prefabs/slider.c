// just a panel with a label and a bar
// the bar can be clicked to reposition the handle as well
ecs_entity_t spawn_prefab_slider(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_slider")
    // transforms
    zox_prefab_set(e, ParentLink, { 0 })
    // set t texture data
    zox_set(e, FrameCorner, { default_button_corner })
    zox_set(e, OutlineThickness, { default_button_frame_thickness })
    zox_set(e, Color, { default_fill_color })
    zox_set(e, OutlineColor, { default_outline_color })
    return e;
}

ecs_entity_t spawn_slider(ecs_world_t *world,
    const CanvasSpawnData canvas_data,
    const ParentSpawnData parent_data,
    ElementSpawnData element_data)
{
    zox_instance(element_data.prefab)
    zox_name("slider")
    set_element_spawn_data(world, e, canvas_data, parent_data, &element_data);

    // spawn handle
    ParentSpawnData slider_data = {
        .e = e,
        .size = element_data.size,
        .position = element_data.position_in_canvas,
    };
    ElementSpawnData handle_data = {
        .prefab = prefab_handle,
        .layer = element_data.layer + 1,
        .position = (int2) { 0, 0 },
        .size = (int2) { 40, element_data.size.y + 24 },
        .anchor = float2_half,
    };
    ecs_entity_t handle = spawn_handle(world, canvas_data, slider_data, handle_data);
    // add it!
    Children *children = &((Children) { 0, NULL });
    add_to_Children(children, handle);
    zox_set(e, Children, { children->length, children->value })

    return e;
}