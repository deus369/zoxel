ecs_entity_2 spawn_slider(ecs_world_t *world,
    const CanvasSpawnData canvas_data,
    const ParentSpawnData parent_data,
    ElementSpawnData element_data,
    const SpawnSliderData slider_data)
{
    zox_instance(element_data.prefab)
    zox_name("slider")
    set_element_spawn_data(world, e, canvas_data, parent_data, &element_data);
    // spawn handle
    ParentSpawnData new_parent_data = {
        .e = e,
        .size = element_data.size,
        .position = element_data.position_in_canvas,
    };
    ElementSpawnData handle_data = {
        .prefab = slider_data.prefab_handle,
        .layer = element_data.layer + 1,
        .position = (int2) { 0, 0 },
        .size = (int2) { 40, element_data.size.y + 24 },
        .anchor = float2_half,
    };
    ecs_entity_t handle = spawn_handle(world, canvas_data, new_parent_data, handle_data);
    // link child!
    Children *children = &((Children) { 0, NULL });
    add_to_Children(children, handle);
    zox_set(e, Children, { children->length, children->value })
    // todo: with text label!
    // return, include the handle
    return (ecs_entity_2) { e, handle };
}