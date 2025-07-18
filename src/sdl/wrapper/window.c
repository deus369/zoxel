void zox_app_set_size(ecs_world_t *world, ecs_entity_t e, int2 size) {
    zox_geter_value2(e, SDLWindow, SDL_Window*, sdl_window)
    SDL_SetWindowSize(sdl_window, size.x, size.y);
    zox_set(e, WindowSize, { size })
    set_viewport_size(world, size);
}

void zox_app_set_position(ecs_world_t *world, ecs_entity_t e, int2 position) {
    zox_geter_value2(e, SDLWindow, SDL_Window*, sdl_window)
    SDL_SetWindowPosition(sdl_window, position.x, position.y);
    zox_set(e, WindowPosition, { position })
}

int get_sdl_window_header_size(ecs_world_t* world, ecs_entity_t e) {
    zox_geter_value2(e, SDLWindow, SDL_Window*, sdl_window)
    int top, left, bottom, right;
    if (!SDL_GetWindowBordersSize(sdl_window, &top, &left, &bottom, &right)) {
        return top;
    } else {
        return 0;
    }
}

int2 get_window_size_without_header(ecs_world_t* world, ecs_entity_t e, int2 window_size) {
    return int2_sub(window_size, (int2) { 0, get_sdl_window_header_size(world, e) });
}

// this should... account for taskbar too?
int2 get_maximized_size(ecs_world_t* world, ecs_entity_t e) {
    return int2_sub(get_screen_size(),
        (int2) { 0, get_sdl_window_header_size(world, e) });
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

// opengl only now const byte fullscreen,
SDL_Window* create_sdl_window(const int2 position, const int2 size, const char *name) {
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
    // links window to OpenGL
    SDL_GL_SwapWindow(window);
    SDL_GL_SetSwapInterval(vsync);
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