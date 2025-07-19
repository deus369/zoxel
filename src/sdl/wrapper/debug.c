byte opengl_es_supported() {
    byte is_supported = 0;
    int num_render_drivers = SDL_GetNumRenderDrivers();
#ifdef zoxel_debug_opengl
    zox_log(" > found [%i] render drivers\n", num_render_drivers)
#endif
    for (int i = 0; i < num_render_drivers; i++) {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i, &info);
        if (strstr(info.name, "opengles")) {
#ifdef zoxel_debug_opengl
            zox_log("     + render driver [%s]\n", info.name)
#endif
            is_supported = 1;
        } else {
#ifdef zoxel_debug_opengl
            zox_log("     - render driver [%s]\n", info.name)
#endif
        }
    }
    return is_supported;
}

void print_supported_renderers() {
    const int num_render_drivers = SDL_GetNumRenderDrivers();
    zox_log(" > found [%i] render drivers\n", num_render_drivers)
    for (int i = 0; i < num_render_drivers; i++) {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i, &info);
        zox_log("     + render driver [%s]\n", info.name)
    }
}

void print_sdl() {
    zox_log(" > sdl")
    zox_log("     + platform:     %s", SDL_GetPlatform())
    zox_log("     + cpu count:    %d", SDL_GetCPUCount())
    zox_log("     + ram:          %d MB", SDL_GetSystemRAM())
    // zox_log("     + screen:       %ix%i", screen_dimensions.x, screen_dimensions.y)
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