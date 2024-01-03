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
    spawn_players(world);
    spawn_player_cameras(world);
    spawn_default_ui(world);
    zox_spawn_main_menu(world, game_name);

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
