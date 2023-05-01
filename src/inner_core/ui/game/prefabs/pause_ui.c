// this will handle resume game & exit game & options
ecs_entity_t pause_ui_prefab;
ecs_entity_t pause_ui;

ecs_entity_t spawn_prefab_pause_ui(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, window_prefab);
    ecs_add_id(world, e, EcsPrefab);
    set_unique_entity_name(world, e, "prefab_pause_ui");
    zoxel_add_tag(world, e, PauseUI);
    ecs_defer_end(world);
    pause_ui_prefab = e;
    return e;
}

// todo: return to gameplay button
// todo: return to main menu button instead of exit game
ecs_entity_t spawn_pause_ui(ecs_world_t *world, int2 position, int2 window_size, float2 anchor) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    const char *header_label = "paused";
    const char *button_label_1 = "return";
    const char *button_label_2 = "options";
    const char *button_label_3 = "exit";
    const unsigned char is_close_button = 0;
    float ui_scale = default_ui_scale;
    int font_size = 28;
    int header_margins = 4;
    #ifdef zoxel_on_android
        window_size.y = 160;
    #endif
    // scale the ui!
    window_size.x *= ui_scale;
    window_size.y *= ui_scale;
    font_size *= ui_scale;
    header_margins *= ui_scale;
    int2 button_padding = (int2) { (int) (font_size * 0.6f), (int) (font_size * 0.3f) };
    // positions
    int2 play_button_position = (int2) { 0, font_size * 2 };
    int2 options_button_position = (int2) { 0, 0 };
    int2 header_position = (int2) { 0, - font_size / 2 - header_margins / 2 };
    #ifdef zoxel_on_android
        play_button_position.y = font_size;
        options_button_position.y = -font_size;
    #endif
    header_position.y = font_size / 2 + header_margins / 2;
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, pause_ui_prefab);
    set_unique_entity_name(world, e, "pause_ui");
    float2 position2D = initialize_ui_components(world, e, main_canvas, position, window_size, anchor, 0, canvas_size);
    Children children = { };
    int children_count = 4;
    #ifdef zoxel_on_android
        children_count = 3;
    #endif
    initialize_memory_component_non_pointer(children, ecs_entity_t, children_count);
    // header
    children.value[0] = spawn_header(world, e, header_position, (int2) { window_size.x, font_size + header_margins},
        (float2) { 0.5f, 1.0f }, header_label, font_size, header_margins, 1, position2D, window_size, is_close_button, canvas_size);
    // buttons
    children.value[1] = spawn_button(world, e, play_button_position, button_padding,
        (float2) { 0.5f, 0.5f }, button_label_1, font_size, 1, position2D, window_size, canvas_size);
    // zoxel_add_tag(world, children.value[1], PlayGameButton);
    children.value[2] = spawn_button(world, e, options_button_position, button_padding,
        (float2) { 0.5f, 0.5f }, button_label_2, font_size, 1, position2D, window_size, canvas_size);
    #ifndef zoxel_on_android
        children.value[3] = spawn_button(world, e, (int2) { 0, - font_size * 2 }, button_padding,
            (float2) { 0.5f, 0.5f }, button_label_3, font_size, 1, position2D, window_size, canvas_size);
        zoxel_add_tag(world, children.value[3], ExitGameButton);
    #endif
    ecs_set(world, e, Children, { children.length, children.value });
    ecs_defer_end(world);
    pause_ui = e;
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned main menu [%lu]\n", (long int) e);
    #endif
    return e;
}