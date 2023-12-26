extern unsigned char is_split_screen;
#ifdef zoxel_ui
extern ecs_entity_t fps_display;
#endif
#define main_camera_rotation_speed 60 * 0.22f

// todo: move things internally to zox: camera, ui canvas,
// move spawning to first frame, game systems, etc
// spawning:
//      > main menu
//      > terrain
// this loads both in engine resources (shaders) and external (voxes, sounds)

unsigned char boot_zoxel_game(ecs_world_t *world) {
    if (initialize_zox(world) == EXIT_FAILURE) return EXIT_FAILURE;
    if (!headless) load_app_icon(main_window, resources_folder_name"textures/game_icon.png");
    // Realm,  players, skybox
    ecs_entity_t realm = spawn_realm(world);
    create_game_stats(world, realm);
    ecs_entity_t game = spawn_game(world);
    zox_set(game, RealmLink, { realm })
    spawn_weather(world);
    if (!headless) spawn_music(world, instrument_piano); // _square
    // Cameras
    set_camera_mode_pre_defined(world);
    int2 screen_dimensions2 = screen_dimensions;
    if (is_split_screen) {
        screen_dimensions2.x /= 2;
        set_main_cameras(2);
    }
    unsigned char camera_fov = get_camera_mode_fov(camera_mode);
    float3 camera_begin_position = float3_zero;
    float4 camera_spawn_rotation = quaternion_identity;
    get_camera_start_transform(&camera_begin_position, &camera_spawn_rotation);
    main_cameras[0] = spawn_base_camera(world, camera_begin_position, camera_spawn_rotation, screen_dimensions2, (int2) { }, camera_fov);
    float4 rotationer = quaternion_from_euler( (float3) { 0, -main_camera_rotation_speed * degreesToRadians, 0 });
    zox_prefab_set(main_cameras[0], EternalRotation, { rotationer })
    if (is_split_screen) {
        //! \todo connect a gamepad to this camera
        camera_begin_position.z += 0.4f;
        main_cameras[1] = spawn_base_camera(world, camera_begin_position, quaternion_identity, screen_dimensions2, (int2) { screen_dimensions2.x, 0 }, camera_fov);
    }
    spawn_ui_camera(world, screen_dimensions2);
    if (!headless) {
        spawn_connected_devices(world);
        ecs_entity_t player = spawn_player(world);
        zox_set(player, CameraLink, { main_cameras[0] })
    }

    // UI
    ecs_entity_t canvas = spawn_canvas(world, screen_dimensions2);
    spawn_canvas_overlay(world, canvas);
    spawn_font_style(world);
    spawn_zoxel_main_menu(world);
    // debug/testing
#ifdef zoxel_start_with_debug_ui
    toggle_ui(world, &game_debug_label, &spawn_game_debug_label);
#endif
#ifdef zox_test_voxel_mesh
    test_animating_chunks(world, camera_begin_position);
#endif
#ifdef zox_test_voxes
    test_voxes(world, camera_begin_position);
#endif
#ifdef zox_spawn_terrain_on_startup
    ecs_entity_t terrain = create_terrain(world);
    zox_set(terrain, RealmLink, { realm })
#endif
    test_steam_cloud();
    // move grid to terrain spawning
    // spawn_terrain_grid(real_chunk_scale);
    return EXIT_SUCCESS;
}
