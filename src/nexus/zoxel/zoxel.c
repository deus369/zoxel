#if !defined(zox_mod_game) // && defined(zox_mod_players)
#define zox_mod_game

// todo: initialize event modules can hook onto for loading i/o
//      - should occur after all modules are imported, but before game is booted
// - each module should add to a load resources event for i/o game data
// #define zox_log_boot_game
// #define zox_enable_log_start_game

byte boot_zoxel_game(ecs_world_t *world) {
    game_name = "Zoxel";
    zox_log_start_game("> boot started [%s]", game_name)
    initialize_networking();
#ifdef zox_mod_voxels
    initialize_voxes(world);
#endif
    const ecs_entity_t realm = spawn_realm(world, prefab_realm);
    const ecs_entity_t game = spawn_game(world, realm);
    intialize_game_store();
    zox_log_start_game("> boot completed [zoxel]")
    if (!headless) {
        const ecs_entity_t window = spawn_main_window_opengl(world, default_window_position, default_window_size, fullscreen);
        if (window == 0) {
            return EXIT_FAILURE;
        }
        initialize_rendering(world);
        load_shaders(world);
        char* icon_path = get_asset_path("textures", "game_icon.png")
        #ifdef zox_mod_textures
        load_app_icon(zox_gett_value(window, SDLWindow), icon_path);
        #endif
        free(icon_path);
    }
    // spawn after shaders exist
    #ifdef zox_mod_weathers
    spawn_weather(world);
    #endif
    #ifdef zox_mod_musics
    spawn_realm_playlist(world, realm);
    #endif
    #ifdef zox_mod_players
    spawn_players_cameras_canvases(world, game);
    spawn_players_start_ui(world);
    #endif
    test_steam_cloud(); // idk
    return EXIT_SUCCESS;
}

void ZoxGameImport(ecs_world_t *world) {
    zox_module(ZoxGame)
    boot_event = boot_zoxel_game;
    zox_game_type = zox_game_mode_3D;
#ifdef zox_mod_space
    game_ui_has_taskbar = 1;
#endif
#ifdef zox_mod_weathers
    menu_sky_color = (float3) { 5 / 255.0f, 32 / 255.0f, 32  / 255.0f };
    menu_sky_bottom_color = (float3) { 5 / 255.0f, 32 / 255.0f, 32 / 255.0f };
#endif
}

#endif
