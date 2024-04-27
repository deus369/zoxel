// shared boot things
extern unsigned char is_split_screen;
#ifdef zoxel_ui
extern ecs_entity_t fps_display;
#endif
#define main_camera_rotation_speed 60 * 0.22f
ecs_entity_t zoxel_main_menu;

void spawn_players(ecs_world_t *world) {
    if (headless) return;   // no players in headless mode
    spawn_connected_devices(world);
    if (is_split_screen) players_playing = 2;
    else players_playing = 1;
    for (int i = 0; i < players_playing; i++) {
        const ecs_entity_t e = spawn_player(world);
        add_player(local_game, e);
        zox_set(e, CameraLink, { main_cameras[i] })
        zox_players[i] = e;
        if (i == 0) main_player = e;
    }
}

ecs_entity_t spawn_player_camera(ecs_world_t *world, const unsigned char index, const float3 camera_position, const float4 camera_rotation, const int2 viewport_position, const int2 viewport_size, const float4 screen_to_canvas) {
    const float4 rotationer = quaternion_from_euler( (float3) { 0, -main_camera_rotation_speed * degreesToRadians, 0 });
    const ecs_entity_t e = spawn_base_camera(world, camera_position, camera_rotation, camera_fov, viewport_position, viewport_size, screen_to_canvas);
    const ecs_entity_t e2 = spawn_camera_ui(world, viewport_position, viewport_size);
    zox_prefab_set(e, EternalRotation, { rotationer })
    zox_set(zox_players[index], CameraLink, { e })
    main_cameras[index] = e;
    ui_cameras[index] = e2;
    return e;
}

void load_element_styles(ecs_world_t *world) {
    spawn_font_style(world);
}

// todo: spawn unique canvas per viewport, viewports per player
ecs_entity_t spawn_default_ui(ecs_world_t *world, const ecs_entity_t camera, const int2 dimensions, const float4 screen_to_canvas) {
    const ecs_entity_t canvas = spawn_canvas(world, camera, dimensions, screen_to_canvas);
    spawn_canvas_overlay(world, canvas, dimensions);
    return canvas;
}

void zox_spawn_main_menu(ecs_world_t *world, const char *game_name, ecs_entity_t canvas) {
#ifdef zox_disable_main_menu
    return;
#endif
#ifdef zoxel_game_ui
    const float2 main_menu_anchor = { 0.5f, 0.5f };
    const int2 main_menu_position = int2_zero;
    zoxel_main_menu = spawn_main_menu(world, canvas, game_name, main_menu_position, main_menu_anchor);
#ifdef zoxel_debug_fps
    fps_display = spawn_fps_display(world, canvas);
#endif
#ifdef zoxel_debug_quads
    quads_label = spawn_quad_count_label(world, canvas);
#endif
    // disable until line2Ds reposition/scale based on canvas
#ifdef zoxel_lines2D
    spawn_canvas_edge_lines(world, canvas);
#endif
#endif
}

