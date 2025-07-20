void zox_sdl_window_size( SDL_Window* sdl_window, int2 size) {
    SDL_SetWindowSize(sdl_window, size.x, size.y);
}

void zox_app_set_size(ecs_world_t *world, ecs_entity_t e, int2 size) {
    zox_geter_value2(e, SDLWindow, SDL_Window*, sdl_window)
    zox_sdl_window_size(sdl_window, size);
    if (!int2_equals(size, zox_gett_value(e, WindowSize))) {
        zox_set(e, WindowSize, { size })
        zox_set(e, WindowSizeDirty, { zox_dirty_trigger })
    }
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
    return int2_sub(get_screen_size(), (int2) { 0, get_sdl_window_header_size(world, e) });
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

static inline int get_sdl_window_flags() {
    int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
/*#ifdef zoxel_on_android
    flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE;
#else
    flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE; // | SDL_WINDOW_BORDERLESS;
#endif*/
    return flags;
}

SDL_Window* create_sdl_window(const int2 position, const int2 size, const char *name, byte flags) {
    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    SDL_Window *window = SDL_CreateWindow(name, position.x, position.y, size.x, size.y, flags);
    if (!window) {
        zox_log_error(" CreateWindowError [%s]\n", SDL_GetError())
    } else {
        SDL_SetWindowResizable(window, window_resizeable);
        SDL_GL_SwapWindow(window);
        SDL_GL_SetSwapInterval(vsync);
    }
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