extern const char *game_name;

void sdl_toggle_fullscreen(ecs_world_t *world, const ecs_entity_t e) { // SDL_Window* window) {
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

SDL_Window* create_sdl_window_basic(const byte is_using_vulkan, const int2 position, const int2 size) {
    int flags;
    if (is_using_vulkan) flags = SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;
    else flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    #ifdef zoxel_on_android
    flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE;
    #endif
    #ifdef zox_log_screens
    zox_log(" + screen %i out of %i\n", (screen_index + 1), screens_count)
    #endif
    //zox_log(" + screen_bounds: %fx%f\n", screen_bounds.x, screen_bounds.y)
    SDL_Window *window = SDL_CreateWindow(game_name, position.x, position.y, size.x, size.y, flags);
    if (window == NULL) {
        zox_log("!!! SDL_CreateWindow failed: %s\n", SDL_GetError())
        return window;
    }
    if (*SDL_GetError()) {
        zox_log(" ! !SDL_CreateWindow: %s\n", SDL_GetError())
        return 0;
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
    return window;
}

SDL_Window* create_sdl_window(const int2 position, const int2 size, const byte fullscreen) {
    byte is_resizeable = 1;
    #ifdef zoxel_on_android
    is_resizeable = 0;
    #endif
    SDL_Window* window = create_sdl_window_basic(is_using_vulkan, position, size);
    if (window == NULL && is_using_vulkan) {
        zox_log(" ! vulkan is not supported on this device, defaulting to [SDL_WINDOW_OPENGL]\n")
        is_using_vulkan = 0;
        window = create_sdl_window_basic(is_using_vulkan, position, size);
    }
    if (window == NULL) {
        zox_log(" ! failed to create sdl window [%s]\n", SDL_GetError())
        return window;
    }
    if (is_using_vulkan) return window;
    SDL_SetWindowResizable(window, is_resizeable);
    SDL_GL_SwapWindow(window);
    SDL_GL_SetSwapInterval(vsync);
    #if !defined(zoxel_on_web) && !defined(zoxel_on_android)
    sdl_set_fullscreen(window, fullscreen);
    #endif
    return window;
}