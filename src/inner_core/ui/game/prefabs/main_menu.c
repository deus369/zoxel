ecs_entity_t main_menu_prefab;

ecs_entity_t spawn_prefab_main_menu(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, window_prefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "prefab_main_menu");
    zoxel_add_tag(world, e, MainMenu);
    main_menu_prefab = e;
    ecs_defer_end(world);
    return e;
}

ecs_entity_t spawn_main_menu(ecs_world_t *world, const char *header_label,
    int2 position, int2 window_size, float2 anchor, bool is_close_button)
{
    int font_size = 28;
    int header_margins = 4;
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, main_menu_prefab);
    set_unique_entity_name(world, e, "main_menu");
    float2 position2D = initialize_ui_components(world, e, main_canvas, position, window_size, anchor, 0,
        ecs_get(world, main_canvas, PixelSize)->value);
    Children children = { };
    int children_count = 4;
    #ifdef disable_main_menu_buttons
    children_count = 1;
    #endif
    initialize_memory_component_non_pointer(children, ecs_entity_t, children_count);
    children.value[0] = spawn_header(world, e, 
        (int2) { 0, - font_size / 2 - header_margins / 2 },
        (int2) { window_size.x, font_size + header_margins},
        (float2) { 0.5f, 1.0f },
        header_label, font_size, header_margins, 1,
        position2D, window_size,
        is_close_button);
    #ifndef disable_main_menu_buttons
    children.value[1] = spawn_button(world, e,
        (int2) { 0, font_size * 2 },
        (int2) { font_size * 6, font_size },
        (float2) { 0.5f, 0.5f },
        "Play", font_size, 1,
        position2D, window_size);
    zoxel_add_tag(world, children.value[1], PlayGameButton);
    children.value[2] = spawn_button(world, e,
        (int2) { 0, 0 },
        (int2) { font_size * 8, font_size },
        (float2) { 0.5f, 0.5f },
        "Options", font_size, 1,
        position2D, window_size);
    children.value[3] = spawn_button(world, e,
        (int2) { 0, - font_size * 2 },
        (int2) { font_size * 6, font_size },
        (float2) { 0.5f, 0.5f },
        "Exit", font_size, 1,
        position2D, window_size);
    zoxel_add_tag(world, children.value[3], ExitGameButton);
    #endif
    ecs_set(world, e, Children, { children.length, children.value });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log_arg("Spawned main menu [%lu]\n", (long int) e);
    #endif
    return e;
}