void print_sdl() {
    zox_log(" > sdl")
    zox_log("     + platform:     %s", SDL_GetPlatform())
    zox_log("     + cpu count:    %d", SDL_GetCPUCount())
    zox_log("     + ram:          %d MB", SDL_GetSystemRAM())
    zox_log("     + screen:       %ix%i", screen_dimensions.x, screen_dimensions.y)
    zox_log("     + sse:          %s", (SDL_HasSSE() ? "true" : "false"));
    zox_log("     + sse2:         %s", (SDL_HasSSE2() ? "true" : "false"));
    zox_log("     + sse3:         %s", (SDL_HasSSE3() ? "true" : "false"));
    zox_log("     + sse4.1:       %s", (SDL_HasSSE41() ? "true" : "false"));
    zox_log("     + sse4.2:       %s", (SDL_HasSSE42() ? "true" : "false"));
    SDL_version compiled;
    SDL_version linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    zox_log("     + compiled SDL version [%d.%d.%d]", compiled.major, compiled.minor, compiled.patch)
    zox_log("     + linking SDL version [%d.%d.%d]", linked.major, linked.minor, linked.patch)
}

void close_sdl_video() {
    SDL_VideoQuit();
    // SDL_Quit();
}

int initialize_sdl_video(ecs_world_t *world) {
    if (SDL_VideoInit(NULL)) {
        zox_log(" - failed to initialize sdl [%s]\n", SDL_GetError())
        return EXIT_FAILURE;
    }
    screen_dimensions = get_screen_size();
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