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
    const int max_labels = max_settings;
    const byte max_elements = 8;
    const byte is_scrollbar = 1;

    const byte layer = 1;
    const byte header_font_size = 80;
    const byte font_size = 32;
    const byte is_close_button = 0;

    byte types[max_labels];
    text_group labels[max_labels];
    ClickEvent click_events[max_labels];
    SlideEvent slide_events[max_labels];
    int labels_count = 0;
    for (int i = 0; i < settings_count; i++, labels_count += 2) {
        setting s = settings[i];
        int j = labels_count;
        int k = labels_count + 1;
        // set slider label
        types[j] = 0;
        labels[j] = (text_group) { s.name };
        click_events[j] = (ClickEvent) { NULL };
        slide_events[j] = (SlideEvent) { NULL };
        // set slider
        types[k] = 1;
        labels[k] = (text_group) { "" };
        click_events[k] = (ClickEvent) { NULL };
        slide_events[k] = (SlideEvent) { &on_settings_slider_slid };
    }

    // add return button
    types[labels_count] = 0;
    labels[labels_count] = (text_group) { "return" };
    click_events[labels_count] = (ClickEvent) { &button_event_menu_main };
    slide_events[labels_count] = (SlideEvent) { NULL };
    labels_count++;

    const ecs_entity_t e = spawn_ui_list(world,
        prefab_ui_list,
        canvas,
        menu_options_header_label,
        labels_count,
        max_elements,
        labels,
        click_events,
        slide_events,
        types,
        position,
        anchor,
        is_close_button,
        header_font_size,
        font_size,
        layer,
        is_scrollbar,
        player);
    zox_add_tag(e, MenuOptions)
    zox_name("menu_options")

    return e;
}

// todo: pass in proper structs into spawn_ui_list
//      - pass out  position_in_canvas and pixel_size

// todo: for options ui:
//      - spawn window ui
//      - spawn panel
//      - use this function to spawn list elements only with different inputs

    // todo:
    //      - parent it to list
    //      - make element_clickable, element_dragable prefabs

    /*CanvasSpawnData canvas_data = {
        .e = canvas,
        .size = zox_gett_value(canvas, PixelSize),
    };
    ParentSpawnData menu_options_data = {
        .e = canvas_data.e, // e,
        .size = canvas_data.size,
        .position = int2_half(canvas_data.size),
    };
    ElementSpawnData slider_data = {
        .prefab = prefab_slider,
        .position = (int2) { 0, 128 },
        .size = (int2) { 256, 48 },
        .anchor = float2_half,
        .layer = layer + 1,
    };
    ecs_entity_2 slider = spawn_slider(world, canvas_data, menu_options_data, slider_data);
    zox_set(slider.y, SlideEvent, { &set_master_volume })*/

    // link child!
    //zox_get_muter(e, Children, children)
    // Children *children = &((Children) { 0, NULL });
    // add_to_Children(children, slider.x);
    //zox_set(e, Children, { children->length, children->value })


// { "volume +" },
// { "volume -" },
// { &button_event_volume_increase },
// { &button_event_volume_decrease },