ecs_entity_2 spawn_slider(ecs_world_t *world,
    const CanvasSpawnData canvas_data,
    const ParentSpawnData parent_data,
    ElementSpawnData element_data,
    const SpawnSliderData slider_data)
{
    zox_instance(element_data.prefab)
    zox_name("slider")
    zox_set(e, SliderLabel, { slider_data.name })
    set_element_spawn_data(world, e, canvas_data, parent_data, &element_data);
    Children *children = &((Children) { 0, NULL });
    ParentSpawnData new_parent_data = {
        .e = e,
        .size = element_data.size,
        .position = element_data.position_in_canvas,
    };

    // spawn handle
    int layout_x = -element_data.size.x / 2 + (int) (element_data.size.x * slider_data.value);
    ElementSpawnData handle_data = {
        .prefab = slider_data.prefab_handle,
        .layer = element_data.layer + 2,
        .position = (int2) { layout_x, 0 },
        .size = (int2) { 40, element_data.size.y + 24 },
        .render_disabled = element_data.render_disabled,
        .anchor = float2_half,
    };
    ecs_entity_t handle = spawn_handle(world, canvas_data, new_parent_data, handle_data);
    zox_set(handle, SlideBounds, { slider_data.bounds })
    add_to_Children(children, handle);

    // # Slider Text #
    SpawnZext zextSpawnData = {
        .canvas = canvas_data,
        .parent = {
            .e = e,
            .position = element_data.position_in_canvas,
            .size = element_data.size,
        },
        .element = {
            .prefab = prefab_zext,
            .layer = element_data.layer + 1,
            .anchor = (float2) { 0.5f, 0.5f },
            .position = int2_zero,
        },
        .zext = {
            .text = slider_data.name,
            .font_size = 24,
            .font_resolution = 64,
            .font_thickness = 2,
            .font_outline_thickness = 6,
            //.font_fill_color = header_font_fill,
            //.font_outline_color = header_font_outline,
            .font_fill_color = (color) { 0, 155, 155, 122 },
            .font_outline_color = (color) { 255, 0, 0, 88 },
        }
    };
    const ecs_entity_t text = spawn_zext(world, &zextSpawnData);
    add_to_Children(children, text);

    // finish up
    zox_set(e, Children, { children->length, children->value })
    // todo: with text label!
    // return, include the handle
    return (ecs_entity_2) { e, handle };
}