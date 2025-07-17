void on_settings_slider_slid(ecs_world_t* world, const SlideEventData* data) {
    zox_geter_value(data->dragged, ParentLink, ecs_entity_t, slider)
    zox_geter_value(slider, SliderLabel, const char*, slider_name)
    zox_sset_float(world, slider_name, data->value);
}

ecs_entity_t spawn_menu_options(
    ecs_world_t *world,
    const ecs_entity_t player,
    const ecs_entity_t canvas,
    const int2 position,
    const float2 anchor)
{
    // more data
    const int max_labels = max_settings;
    const byte visible_count = 12;
    const byte is_scrollbar = 1;
    const byte layer = 1;
    const byte header_font_size = 80;
    const byte font_size = 32;
    const byte is_close_button = 0;
    CanvasSpawnData canvas_data = {
        .e = canvas,
        .size = zox_gett_value(canvas, PixelSize),
    };

    // # Window #
    ElementSpawnData window_element_data = {
        .prefab = prefab_window,
        .position = (int2) { 0, 0 },
        .size = (int2) { 520, 580 },
        .anchor = float2_half,
        .layer = layer,
    };
    ParentSpawnData window_parent_data = {
        .e = canvas_data.e,
        .size = canvas_data.size,
        .position = int2_half(canvas_data.size),
    };
    SpawnWindow2 window_data = {
        .header_text = "Ponder",
        .header_font_size = 32,
        .header_padding = 4,
        .is_scrollbar = 0,
    };
    const ecs_entity_t e = spawn_window2(world,
        canvas_data,
        window_parent_data,
        &window_element_data,
        &window_data);
    zox_add_tag(e, MenuOptions)
    zox_name("menu_options")

    // # List #

    SpawnListElement elements[max_labels];
    int elements_count = 0;
    for (int i = 0; i < settings_count; i++) {
        setting s = settings[i];
        // zox_log("spawning setting %s [%f] [%fx%f]", s.name, s.value_float, s.min_float, s.max_float)
        // set slider label
        if (s.type == zox_data_type_float) {
            elements[elements_count] = (SpawnListElement) {
                .type = 1,
                .text = s.name,
                .on_slide = &on_settings_slider_slid,
                .value = s.value_float,
                .value_bounds = (float2) { s.min_float, s.max_float },
            };
            elements_count++;
        }
        // todo: support other types
    }
    elements[elements_count] = (SpawnListElement) {
        .text = "return",
        .on_click = &button_event_menu_main,
    };
    elements_count++;
    ParentSpawnData list_parent_data = {
        .e = e,
        .size = window_element_data.size,
        .position = window_element_data.position_in_canvas,
    };
    ElementSpawnData list_element_data = {
        .prefab = prefab_list,
        .position = (int2) { 0, -25 },
        .size = (int2) { window_element_data.size.x, window_element_data.size.y - 50 },
        .anchor = float2_half,
        .layer = layer + 1,
    };
    SpawnList ui_list_data = (SpawnList) {
        .elements = elements,
        .count = elements_count,
        .visible_count = visible_count,
        .font_size = font_size,
        .fill = (color) { 0, 0, 0, 0 },
        .outline = (color) { 0, 255, 255, 55 },
    };
    const ecs_entity_t list = spawn_list(world,
        canvas_data,
        list_parent_data,
        list_element_data,
        ui_list_data);
    add_to_Children(window_data.children, list);

    // return our window
    return e;
}