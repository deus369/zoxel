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
    spawn_players_cameras_canvases(world);
    // debug/testing
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
