#if !defined(zox_mod_game) // && defined(zox_mod_players)
#define zox_mod_game

// #define zox_log_boot_game

byte boot_zoxel_game(ecs_world_t *world) {
#ifndef zox_beta
    game_name = "zoxel";
#else
    game_name = "zoxel_beta";
#endif
    initialize_networking();
    if (!headless) {
        const ecs_entity_t window = spawn_main_window(world, default_window_position, default_window_size, fullscreen);
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
    // load resources
    // todo: each module should add to a load resources event for i/o game data
#ifdef zox_mod_voxels
    initialize_voxes(world);
#endif
    // Realm,  players, skybox
    const ecs_entity_t realm = spawn_realm(world, prefab_realm);
    const ecs_entity_t game = spawn_game(world, realm);
#ifdef zox_mod_weathers
    spawn_weather(world);
#endif
#ifdef zox_mod_musics
    initialize_music(world, realm);
#endif
#ifdef zox_mod_players
    spawn_players_cameras_canvases(world, game);
#endif
    intialize_game_store();
    test_steam_cloud();
    // zox_log(" ! boot completed [zoxel]\n")
    return EXIT_SUCCESS;
}

void ZoxGameImport(ecs_world_t *world) {
    zox_module(ZoxGame)
    boot_event = boot_zoxel_game;
    zox_game_type = zox_game_mode_3D;
#ifdef zox_mod_players2
    game_ui_has_taskbar = 1;
#endif
#ifdef zox_mod_weathers
    menu_sky_color = (float3) { 5 / 255.0f, 32 / 255.0f, 32  / 255.0f };
    menu_sky_bottom_color = (float3) { 5 / 255.0f, 32 / 255.0f, 32 / 255.0f };
#endif
}

#endif
