// this will handle resume game & exit game & options
ecs_entity_t options_ui_prefab;

ecs_entity_t spawn_prefab_options_ui(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, window_prefab);
    ecs_add_id(world, e, EcsPrefab);
    set_unique_entity_name(world, e, "prefab_options_ui");
    zoxel_add_tag(world, e, PauseUI);
    ecs_defer_end(world);
    options_ui_prefab = e;
    return e;
}

ecs_entity_t spawn_options_ui(ecs_world_t *world, const char *header_label, int2 position, int2 window_size, float2 anchor, unsigned char is_close_button) {
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
    int2 play_button_position = (int2) { 0, font_size * 2 };
    int2 options_button_position = (int2) { 0, 0 };
    int2 header_position = (int2) { 0, - font_size / 2 - header_margins / 2 };
    #ifdef zoxel_on_android
        play_button_position.y = font_size;
        options_button_position.y = -font_size;
    #endif
    header_position.y = font_size / 2 + header_margins / 2;
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, options_ui_prefab);
    set_unique_entity_name(world, e, "options_ui");
    float2 position2D = initialize_ui_components(world, e, main_canvas, position, window_size, anchor, 0, ecs_get(world, main_canvas, PixelSize)->value);
    Children children = { };
    int children_count = 4;
    #ifdef zoxel_on_android
        children_count = 3;
    #endif
    initialize_memory_component_non_pointer(children, ecs_entity_t, children_count);
    children.value[0] = spawn_header(world, e, 
        header_position,
        (int2) { window_size.x, font_size + header_margins},
        (float2) { 0.5f, 1.0f },
        header_label, font_size, header_margins, 1,
        position2D, window_size,
        is_close_button);
    // spawn buttons!
    children.value[1] = spawn_button(world, e,
        play_button_position,
        (int2) { font_size * 6, font_size },
        (float2) { 0.5f, 0.5f },
        "Unpause", font_size, 1,
        position2D, window_size);
    zoxel_add_tag(world, children.value[1], PlayGameButton);
    children.value[2] = spawn_button(world, e,
        options_button_position,
        (int2) { font_size * 8, font_size },
        (float2) { 0.5f, 0.5f },
        "Options", font_size, 1,
        position2D, window_size);
    #ifndef zoxel_on_android
    children.value[3] = spawn_button(world, e,
        (int2) { 0, - font_size * 2 },
        (int2) { font_size * 6, font_size },
        (float2) { 0.5f, 0.5f },
        "Quit", font_size, 1,
        position2D, window_size);
    zoxel_add_tag(world, children.value[3], ExitGameButton);
    #endif
    ecs_set(world, e, Children, { children.length, children.value });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned main menu [%lu]\n", (long int) e);
    #endif
    return e;
}