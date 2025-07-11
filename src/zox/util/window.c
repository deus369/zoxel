int engine_spawn_window(ecs_world_t *world) {
#ifdef zox_mod_games
    const ecs_entity_t window = spawn_window_opengl(world, default_window_position, default_window_size, fullscreen, game_name);
#else
    const ecs_entity_t window = spawn_window_opengl(world, default_window_position, default_window_size, fullscreen, "nogame");
#endif
    if (window == 0) {
        return EXIT_FAILURE;
    }
    initialize_rendering(world);
    // Files
    load_files_shaders(world);
    load_files_fonts(world);
#ifdef zox_mod_textures
    load_files_textures(world);
#endif
#ifdef zox_mod_sounds
    load_files_sounds(world);
#endif
#ifdef zox_mod_voxels
    initialize_voxes(world);
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