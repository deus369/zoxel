void sdl_toggle_fullscreen(ecs_world_t *world, const ecs_entity_t e) {
    const byte is_fullscreen = !zox_get_value(e, WindowFullscreen)
    zox_set(e, WindowFullscreen, { is_fullscreen })
    sdl_set_fullscreen(zox_gett_value(e, SDLWindow), is_fullscreen);
    if (!is_fullscreen) {
        on_sdl_window_restored(world, e);
    } else {
        on_window_resized(world, e, get_screen_size());
    }
}

int get_sdl_window_header_size(SDL_Window* window) {
    int top, left, bottom, right;
    if (SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right) == 0) {
        return top;
    }
    return 0;
}

SDL_Window* create_sdl_window_basic_opengl(
    const int2 position,
    const int2 size,
    const char *name)
{
    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    #ifdef zoxel_on_android
        flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE;
    #else
        flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE; // | SDL_WINDOW_BORDERLESS;
    #endif
    SDL_Window *window = SDL_CreateWindow(name, position.x, position.y, size.x, size.y, flags);
    if (window == NULL) {
        zox_log_error("!!! SDL_CreateWindow failed: %s", SDL_GetError())
        return window;
    }
    if (*SDL_GetError()) {
        zox_log_error("#!!! [create_sdl_window...] SDL_GetError: %s", SDL_GetError())
        return 0;
    }
    return window;
}

SDL_Window* create_sdl_window_basic_vulkan(
    const int2 position,
    const int2 size,
    const char *name)
{
    int flags = SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;
    #ifdef zoxel_on_android
    flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE;
    #endif
    SDL_Window *window = SDL_CreateWindow(name, position.x, position.y, size.x, size.y, flags);
    if (window == NULL) {
        zox_log("!!! SDL_CreateWindow failed: %s\n", SDL_GetError())
        return window;
    }
    return window;
}

// opengl only now
SDL_Window* create_sdl_window(const int2 position, const int2 size, const byte fullscreen, const char *name) {
    byte is_resizeable = 1;
    #ifdef zoxel_on_android
    is_resizeable = 0;
    #endif
    SDL_Window* window = create_sdl_window_basic_opengl(position, size, name);
    if (window == NULL) {
        zox_log(" ! failed to create sdl window [%s]\n", SDL_GetError())
        return window;
    }
    SDL_SetWindowResizable(window, is_resizeable);
    SDL_GL_SwapWindow(window);
    SDL_GL_SetSwapInterval(vsync);
#if !defined(zoxel_on_web) && !defined(zoxel_on_android)
    sdl_set_fullscreen(window, fullscreen);
#endif
    return window;
}

/*if (screen_index == 1) {
    SDL_Rect displayBounds;
    SDL_GetDisplayBounds(1, &displayBounds);
    int xPos, yPos;
    SDL_GetWindowPosition(window, &xPos, &yPos);
    int borderWidth, borderHeight;
    SDL_GetWindowBordersSize(window, &borderWidth, NULL, &borderHeight, NULL);
    xPos += borderWidth;
    yPos += borderHeight;
    SDL_SetWindowPosition(window, displayBounds.x + xPos, displayBounds.y + yPos);
}*/