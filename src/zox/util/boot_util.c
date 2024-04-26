// shared boot things
extern unsigned char is_split_screen;
#ifdef zoxel_ui
extern ecs_entity_t fps_display;
#endif
#define main_camera_rotation_speed 60 * 0.22f
ecs_entity_t zoxel_main_menu;

void spawn_players(ecs_world_t *world) {
    if (!headless) {
        spawn_connected_devices(world);
        const ecs_entity_t player = spawn_player(world);
        zox_set(player, CameraLink, { main_cameras[0] })
        add_player(local_game, player);
    }
}

void spawn_player_cameras(ecs_world_t *world) {
    set_camera_mode_pre_defined(world);
    int2 screen_dimensions2 = screen_dimensions;
    if (is_split_screen) {
        screen_dimensions2.x /= 2;
        set_main_cameras(2);
    }
    const unsigned char camera_fov = get_camera_mode_fov(camera_mode);
    float3 camera_begin_position = float3_zero;
    float4 camera_spawn_rotation = quaternion_identity;
    get_camera_start_transform(&camera_begin_position, &camera_spawn_rotation);
    main_cameras[0] = spawn_base_camera(world, camera_begin_position, camera_spawn_rotation, screen_dimensions2, (int2) { }, camera_fov);
    const float4 rotationer = quaternion_from_euler( (float3) { 0, -main_camera_rotation_speed * degreesToRadians, 0 });
    zox_prefab_set(main_cameras[0], EternalRotation, { rotationer })
    if (is_split_screen) {
        camera_begin_position.z += 0.4f;
        main_cameras[1] = spawn_base_camera(world, camera_begin_position, quaternion_identity, screen_dimensions2, (int2) { screen_dimensions2.x, 0 }, camera_fov);
    }
    spawn_ui_camera(world, screen_dimensions2);
    if (main_player) zox_set(main_player, CameraLink, { main_cameras[0] })
}

// todo: spawn unique canvas per viewport, viewports per player
ecs_entity_t spawn_default_ui(ecs_world_t *world, ecs_entity_t camera) {
    const ecs_entity_t canvas = spawn_canvas(world, screen_dimensions, camera);
    spawn_canvas_overlay(world, canvas);
    spawn_font_style(world);
    return canvas;
}

void zox_spawn_main_menu(ecs_world_t *world, const char *game_name, ecs_entity_t canvas) {
#ifdef zox_disable_main_menu
    return;
#endif
#ifdef zoxel_game_ui
    if (zoxel_main_menu != 0 && ecs_is_alive(world, zoxel_main_menu)) {
        zox_delete(zoxel_main_menu)
        zoxel_main_menu = 0;
        return;
    }
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

