ecs_entity_t engine_spawn_window(ecs_world_t *world) {
    const char* window_name;
#ifdef zox_mod_games
    window_name = game_name;
#else
    window_name = "nogame";
#endif
    const ecs_entity_t app = spawn_window_opengl(world,
        window_name,
        fullscreen,
        maximized,
        monitor);
    if (!app) {
        return 0;
    }
    main_app = app;
    // Shaders
    /*
    char* icon_path = get_asset_path("textures", "game_icon.png")
#ifdef zox_mod_textures
    load_app_icon(zox_gett_value(app, SDLWindow), icon_path);
#endif
    free(icon_path);*/
    return app;
}