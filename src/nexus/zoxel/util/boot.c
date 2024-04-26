// todo: refactor cameras, do they even need ScreenPosition? we should just have CanvasLinks, and each camera is linked to a bunch? idk

unsigned char boot_zoxel_game(ecs_world_t *world) {
#ifndef zox_beta
    game_name = "Zoxel";
#else
    game_name = "Zoxel b";
#endif
    if (initialize_zox(world) == EXIT_FAILURE) return EXIT_FAILURE;
    if (!headless) {
        char* icon_path = concat_file_path(resources_path, "textures"character_slash"game_icon.png");
        load_app_icon(main_window, icon_path);
        free(icon_path);
    }
    // Realm,  players, skybox
    const ecs_entity_t realm = spawn_realm(world);
    create_game_stats(world, realm);
    const ecs_entity_t game = spawn_game(world);
    zox_set(game, RealmLink, { realm })
    spawn_weather(world);
    if (!headless) spawn_music(world, instrument_piano); // _square
    load_element_styles(world);
    spawn_players(world);
    set_camera_mode_pre_defined(world);
    set_main_cameras((int) players_playing);
    const unsigned char camera_fov = get_camera_mode_fov(camera_mode);
    float3 camera_position = float3_zero;
    float4 camera_rotation = quaternion_identity;
    for (int i = 0; i < players_playing; i++) {
        get_camera_start_transform(&camera_position, &camera_rotation);
        const float4 screen_to_canvas = (float4) { 1 / (float) players_playing, 1, i / (float) players_playing, 0 };
        const int2 viewport_size = screen_to_canvas_size(screen_dimensions, screen_to_canvas);
        const int2 viewport_position = screen_to_canvas_position(screen_dimensions, screen_to_canvas);
        const ecs_entity_t camera = spawn_player_camera(world, i, camera_position, camera_rotation, viewport_position, viewport_size, screen_to_canvas);
        const ecs_entity_t ui_camera = ui_cameras[i];
        const ecs_entity_t canvas = spawn_default_ui(world, ui_camera, viewport_size, screen_to_canvas);
        zox_spawn_main_menu(world, game_name, canvas);
        zox_canvases[i] = canvas;
        zox_set(zox_players[i], CanvasLink, { canvas })
        if (i == 0) main_canvas = canvas;
    }
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
