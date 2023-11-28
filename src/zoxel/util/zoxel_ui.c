ecs_entity_t zoxel_main_menu;

void spawn_zoxel_main_menu(ecs_world_t *world) {
#ifdef zoxel_game_ui
    if (zoxel_main_menu != 0 && ecs_is_alive(world, zoxel_main_menu)) {
        zox_delete(zoxel_window)
        zoxel_main_menu = 0;
        return;
    }
    float2 main_menu_anchor = { 0.5f, 0.5f };
    int2 main_menu_position = int2_zero;
    zoxel_main_menu = spawn_main_menu(world, game_name, main_menu_position, main_menu_anchor, 0);
#ifdef zoxel_debug_fps
    fps_display = spawn_fps_display(world, main_canvas);
#endif
#ifdef zoxel_debug_quads
    quads_label = spawn_quad_count_label(world, main_canvas);
#endif
    Children *children = zox_get_mut(main_canvas, Children);
    resize_memory_component(Children, children, ecs_entity_t, 3)
    children->value[0] = zoxel_main_menu;
    children->value[1] = fps_display;
    children->value[2] = quads_label;
    zox_modified(main_canvas, Children)
    // disable until line2Ds reposition/scale based on canvas
#ifdef zoxel_lines2D
    //     spawn_canvas_edge_lines(world, main_canvas);
#endif
#endif
}
