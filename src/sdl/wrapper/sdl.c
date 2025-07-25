int initialize_sdl_video(ecs_world_t *world) {
    if (SDL_VideoInit(NULL)) {
        zox_log(" - failed to initialize sdl [%s]\n", SDL_GetError())
        return EXIT_FAILURE;
    }
    // screen_dimensions = get_screen_size();
    if (is_log_sdl) {
        print_sdl();
    }
#ifdef zox_include_vulkan
    if (!load_vulkan_library()) {
        return EXIT_FAILURE;
    }
#endif
    set_sdl_attributes();
    screens_count = SDL_GetNumVideoDisplays();
    if (screens_count == 1) {
        screen_index = 0;
    }
    return EXIT_SUCCESS;
}

void close_sdl_video() {
    SDL_VideoQuit();
    // SDL_Quit();
}