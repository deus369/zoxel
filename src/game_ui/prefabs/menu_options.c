void set_master_volume(ecs_world_t* world, const SlideEventData* data) {
    // zox_log("volume set to %f", data->value)
    master_volume = data->value;
}

ecs_entity_t spawn_menu_options(
    ecs_world_t *world,
    const ecs_entity_t player,
    const ecs_entity_t canvas,
    const int2 position,
    const float2 anchor)
{
    const byte layer = 1;
    const byte header_font_size = 80;
    const byte font_size = 42;
    const byte is_close_button = 0;
    const int labels_count = 3;
    const text_group labels[] = {
        { "Volume" },
        { "" },
        { "return" },
    };
    const ClickEvent click_events[] = {
        { NULL },
        { NULL },
        { &button_event_menu_main }
    };
    const SlideEvent slide_events[] = {
        { NULL },
        { &set_master_volume },
        { NULL },
    };
    const byte types[] = {
        0,
        1,
        0,
    };
    // { "volume +" },
    // { "volume -" },
    // { &button_event_volume_increase },
    // { &button_event_volume_decrease },

    // todo: for options ui:
    //      - spawn window ui
    //      - spawn panel
    //      - use this function to spawn list elements only with different inputs

    // todo: pass in proper structs into spawn_ui_list
    //      - pass out  position_in_canvas and pixel_size
    const ecs_entity_t e = spawn_ui_list(world,
        prefab_ui_list,
        canvas,
        menu_options_header_label,
        labels_count,
        labels_count,
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
        0,
        player);
    zox_add_tag(e, MenuOptions)
    zox_name("menu_options")

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


    return e;
}