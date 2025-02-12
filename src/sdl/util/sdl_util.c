void print_sdl() {
#ifdef zox_print_sdl
    zox_log(" > sdl stats\n")
    zox_log("     + platform:     %s\n", SDL_GetPlatform())
    zox_log("     + cpu count:    %d\n", SDL_GetCPUCount())
    zox_log("     + ram:          %d MB\n", SDL_GetSystemRAM())
    zox_log("     + screen:       %ix%i\n", screen_dimensions.x, screen_dimensions.y)
    /*zox_log("     + sse:          %s\n", (SDL_HasSSE() ? "true" : "false"));
    zox_log("     + sse2:         %s\n", (SDL_HasSSE2() ? "true" : "false"));
    zox_log("     + sse3:         %s\n", (SDL_HasSSE3() ? "true" : "false"));
    zox_log("     + sse4.1:       %s\n", (SDL_HasSSE41() ? "true" : "false"));
    zox_log("     + sse4.2:       %s\n", (SDL_HasSSE42() ? "true" : "false"));*/
    SDL_version compiled;
    SDL_version linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    zox_log("     + compiled SDL version [%d.%d.%d]\n", compiled.major, compiled.minor, compiled.patch)
    zox_log("     + linking SDL version [%d.%d.%d]\n", linked.major, linked.minor, linked.patch)
#endif
}

void close_sdl_video() {
    SDL_VideoQuit();
    // SDL_Quit();
}

int initialize_sdl_video(ecs_world_t *world) {
    if (SDL_VideoInit(NULL) != 0) {
        zox_log(" - failed to initialize sdl [%s]\n", SDL_GetError())
        return EXIT_FAILURE;
    }
    screen_dimensions = get_screen_size();
    // zox_log(" > screen dimensions init to [%ix%i]\n", screen_dimensions.x, screen_dimensions.y)
    print_sdl();
#ifdef zox_include_vulkan
    if (!load_vulkan_library()) return EXIT_FAILURE;
#else
    is_using_vulkan = 0;
#endif
    if (!is_using_vulkan) set_sdl_attributes();
    return EXIT_SUCCESS;
}