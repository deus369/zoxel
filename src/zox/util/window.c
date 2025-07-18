int engine_spawn_window(ecs_world_t *world) {
    initialize_apps_sdl(world);
    const char* window_name;
#ifdef zox_mod_games
    window_name = game_name;
#else
    window_name = "nogame";
#endif
    load_settings(world, game_name);
    const ecs_entity_t window = spawn_window_opengl(world,
        window_name,
        default_window_position,
        default_window_size,
        fullscreen,
        maximized,
        monitor);
    if (window == 0) {
        return EXIT_FAILURE;
    }
    main_app = window;
    initialize_rendering(world);
    initialize_sounds(world);
    // Files
    load_files_shaders(world);
    load_files_fonts(world);
#ifdef zox_mod_textures
    load_files_textures(world);
#endif
#ifdef zox_mod_sounds
    load_files_sounds(world);
#endif
#ifdef zox_mod_voxes
    load_files_voxes(world);
#endif
    // Shaders
    load_shaders(world);
    char* icon_path = get_asset_path("textures", "game_icon.png")
    #ifdef zox_mod_textures
    load_app_icon(zox_gett_value(window, SDLWindow), icon_path);
    #endif
    free(icon_path);
    return EXIT_SUCCESS;
}