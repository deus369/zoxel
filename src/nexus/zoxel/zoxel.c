#if !defined(zox_mod_game) // && defined(zox_mod_players)
#define zox_mod_game

// #define zox_log_boot_game

unsigned char boot_zoxel_game(ecs_world_t *world) {
#ifndef zox_beta
    game_name = "Zoxel";
#else
    game_name = "Zoxel b";
#endif
#ifdef zox_log_boot_game
    zox_log("boot_zoxel_game\n")
#endif
    const ecs_entity_t window = spawn_main_window(world);
    if (window == 0) {
        return EXIT_FAILURE;
    }
#ifdef zox_log_boot_game
    zox_log("boot_zoxel_game2\n")
    #endif
    if (!headless) {
        initialize_rendering(world);
        load_shaders(world);
#ifdef zox_log_boot_game
        zox_log("boot_zoxel_game3\n")
#endif
        char* icon_path = get_asset_path("textures", "game_icon.png")
        char* cursor_path = get_asset_path("textures", "cursors/cursor_01.png")
#ifdef zox_mod_textures
        load_app_icon(zox_gett_value(window, SDLWindow), icon_path);
#endif
        set_sdl_cursor(cursor_path, int2_zero);
        free(icon_path);
        free(cursor_path);
    }
#ifdef zox_log_boot_game
    zox_log("boot_zoxel_game4\n")
#endif
    // Realm,  players, skybox
    const ecs_entity_t realm = spawn_realm(world, prefab_realm);
    const ecs_entity_t game = spawn_game(world);
    zox_set(game, RealmLink, { realm })
#ifdef zox_log_boot_game
    zox_log("boot_zoxel_game5\n")
#endif
#ifdef zox_mod_weathers
    spawn_weather(world);
#endif
#ifdef zox_mod_musics
    if (!headless) spawn_music(world, prefab_music); // _square
    #endif
#ifdef zox_log_boot_game
    zox_log(" > boot_zoxel_game 6\n")
#endif
#ifdef zox_mod_players
    spawn_players_cameras_canvases(world, game);
#endif
    intialize_game_store();
    test_steam_cloud();
#ifdef zox_log_boot_game
    zox_log(" > boot zoxel completedboot_zoxel_game7\n")
#endif
    return EXIT_SUCCESS;
}

void ZoxGameImport(ecs_world_t *world) {
    zox_module(ZoxGame)
    boot_event = boot_zoxel_game;
    zox_game_type = zox_game_mode_3D;
#ifdef zox_mod_weathers
    menu_sky_color = (float3) { 5 / 255.0f, 32 / 255.0f, 32  / 255.0f };
    menu_sky_bottom_color = (float3) { 5 / 255.0f, 32 / 255.0f, 32 / 255.0f };
#endif
}

#endif
