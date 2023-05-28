ecs_entity_t pause_ui_prefab;
ecs_entity_t pause_ui;

ecs_entity_t spawn_prefab_pause_ui(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(window_prefab)
    zox_name("prefab_pause_ui")
    zox_add_tag(e, PauseUI);
    ecs_defer_end(world);
    pause_ui_prefab = e;
    return e;
}

ecs_entity_t spawn_pause_ui(ecs_world_t *world, int2 position, float2 anchor) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    const char *header_label = "paused";
    const char *button_label_1 = "return";
    const char *button_label_2 = "options";
    const char *button_label_3 = "leave";
    int2 window_size = { 260, 220 };
    const unsigned char is_close_button = 0;
    float ui_scale = default_ui_scale;
    int font_size = 28;
    int header_margins = 12;
    #ifdef zoxel_on_android
        window_size.y = 160;
    #endif
    // scale the ui!
    window_size.x *= ui_scale;
    window_size.y *= ui_scale;
    font_size *= ui_scale;
    header_margins *= ui_scale;
    int2 button_padding = (int2) { (int) (font_size * 0.6f), (int) (font_size * 0.3f) };
    int header_height = (font_size + header_margins - 1); //  * 2;
    anchor_position2D(&position, window_size, anchor, header_height);
    // positions
    int2 play_button_position = (int2) { 0, font_size * 2 };
    int2 options_button_position = (int2) { 0, 0 };
    int2 header_position = (int2) { 0, header_height / 2.0f }; //- font_size / 2 - header_margins / 2 };
    header_position.y = font_size / 2 + header_margins / 2;
    ecs_defer_begin(world);
    zox_instance(pause_ui_prefab)
    zox_name("pause_ui")
    float2 position2D = initialize_ui_components(world, e, main_canvas, position, window_size, anchor, 0, canvas_size);
    Children children = { };
    int children_count = 4;
    initialize_memory_component_non_pointer(children, ecs_entity_t, children_count);
    // header
    children.value[0] = spawn_header(world, e, header_position, (int2) { window_size.x, font_size + header_margins},
        (float2) { 0.5f, 1.0f }, header_label, font_size, header_margins, 1, position2D, window_size, is_close_button, canvas_size);
    // buttons
    children.value[1] = spawn_button(world, e, play_button_position, button_padding,
        (float2) { 0.5f, 0.5f }, button_label_1, font_size, 1, position2D, window_size, canvas_size);
    zox_set(children.value[1], ClickEvent, { &button_event_return_to_game });
    // zox_add_tag(children.value[1], PlayGameButton);
    children.value[2] = spawn_button(world, e, options_button_position, button_padding,
        (float2) { 0.5f, 0.5f }, button_label_2, font_size, 1, position2D, window_size, canvas_size);
    children.value[3] = spawn_button(world, e, (int2) { 0, - font_size * 2 }, button_padding,
        (float2) { 0.5f, 0.5f }, button_label_3, font_size, 1, position2D, window_size, canvas_size);
    zox_set(children.value[3], ClickEvent, { &button_event_stop_playing_game });
    ecs_set(world, e, Children, { children.length, children.value });
    ecs_defer_end(world);
    pause_ui = e;
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned main menu [%lu]\n", (long int) e);
    #endif
    select_first_button(world, children.value[1]);
    return e;
}