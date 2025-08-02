ecs_entity_t spawn_window2(ecs_world_t *world,
    const CanvasSpawnData canvas_data,
    const ParentSpawnData parent_data,
    ElementSpawnData* element_data,
    SpawnWindow2* window_data)
{
    const byte header_height = window_data->header_font_size + window_data->header_padding.y * 2;
    zox_instance(element_data->prefab)
    zox_name("window")
    set_element_spawn_data(world, e, canvas_data, parent_data, element_data);
    zox_set(e, HeaderHeight, { header_height })

    // start children
    Children* children = window_data->children;
    // zox_muter(e, Children, children)
    // Children children = (Children) { };

    const ParentSpawnData e_parent_data = {
        .e = e,
        .position = element_data->position_in_canvas,
        .size = element_data->size,
    };

    // # Window Header #
    // todo: pass more of t this in from top
    ElementSpawnData header_element_data = {
        .prefab = prefab_header,
        .anchor = (float2) { 0.5f, 1.0f },
        .position = (int2) { 0, 0 },
        .size = (int2) { element_data->size.x, header_height },
        .layer = element_data->layer + 1,
    };
    SpawnHeaderData header_data = {
        .prefab_zext = prefab_zext,
        // .color = color_white,
    };
    SpawnTextData header_text_data = {
        .text = window_data->header_text,
        .font_size = window_data->header_font_size,
        .font_resolution = header_font_resolution,
        .font_thickness = header_font_thickness_fill,
        .font_outline_thickness = header_font_thickness_outline,
        .font_fill_color = header_font_fill,
        .font_outline_color = header_font_outline,
        .padding = window_data->header_padding,
    };
    // n/a
    SpawnButtonData close_button_data = { };
    const ecs_entity_t header = spawn_header3(world,
        canvas_data,
        e_parent_data,
        header_element_data,
        close_button_data,
        header_text_data,
        header_data);
    add_to_Children(children, header);
    set_window_bounds_to_canvas(world, e, canvas_data.size, element_data->size, element_data->anchor);

    // spawn body

    // spawn scrollbar

    // add_to_Children(children, scrollbar);

    // window_data->children = children;

    return e;
}