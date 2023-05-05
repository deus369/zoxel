ecs_entity_t zoxel_main_menu;

void spawn_zoxel_main_menu(ecs_world_t *world) {
    #ifdef zoxel_game_ui
        if (zoxel_main_menu != 0 && ecs_is_alive(world, zoxel_main_menu)) {
            ecs_delete(world, zoxel_window);
            zoxel_main_menu = 0;
            return;
        }
        Children children = { };
        initialize_memory_component_non_pointer(children, ecs_entity_t, 3);
        // main menu
        const int edge_buffer = 8 * default_ui_scale;
        int2 window_size = { 260, 220 };
        float2 window_anchor = { 0.0f, 1.0f };
        int2 window_position = { 0 + edge_buffer, 0 - edge_buffer };
        const char *game_name = "zoxel";
        zoxel_main_menu = spawn_main_menu(world, game_name, window_position, window_size, window_anchor, 0);
        #ifdef zoxel_debug_fps
            fps_display = spawn_fps_display(world, main_canvas, 32);
        #endif
        #ifdef zoxel_debug_quads
            quads_label = spawn_quad_count_label(world, main_canvas, 32);
        #endif
        children.value[0] = zoxel_main_menu;
        children.value[1] = fps_display;
        children.value[2] = quads_label;
        ecs_set(world, main_canvas, Children, { children.length, children.value });
        #ifdef zoxel_lines2D
            spawn_canvas_edge_lines(world, main_canvas);
        #endif
    #endif
}