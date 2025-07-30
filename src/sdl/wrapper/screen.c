int2 get_screen_size() {
#ifdef zox_web
    return get_webasm_screen_size();
#else
    return get_screen_size_monitor(monitor);
#endif
}

int2 get_sdl_screen_size() {
    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode)) {
        zox_log_error("[SDL_GetCurrentDisplayMode] (get_sdl_screen_size) failed at %i: %s", 0, SDL_GetError());
        return (int2) { 480, 480 };
    }
    return (int2) { displayMode.w, displayMode.h };
}

void zox_app_set_fullscreen(SDL_Window* window, byte fullscreen) {
    const byte flag = fullscreen ? sdl_fullscreen_byte : 0;
    // zox_log("# fullscreen flag [%i]", flag)
    SDL_SetWindowFullscreen(window, flag);
}

void zox_app_set_maximized(SDL_Window* window, byte maximized) {
    if (maximized) {
        SDL_MaximizeWindow(window);
    } else {
        SDL_RestoreWindow(window);
    }
}

void on_sdl_window_restored(ecs_world_t *world, ecs_entity_t e) {
    if (!zox_has(e, WindowSize)) {
        zox_log_error("invalid app [%lu]", e)
        return;
    }
    zox_geter_value2(e, SDLWindow, SDL_Window*, sdl_window)
    zox_geter_value2(e, WindowSizeRestore, int2, size)
    zox_geter_value2(e, WindowPositionRestore, int2, position)

    if (size.x == 0 && size.y == 0) {
        int2 screen_size = get_screen_size();
        size.x = screen_size.x / 2;
        size.y = screen_size.y / 2;
    }

    SDL_SetWindowSize(sdl_window, size.x, size.y);
    SDL_SetWindowPosition(sdl_window, position.x, position.y);

    zox_set(e, WindowSize, { size })
    zox_set(e, WindowSizeDirty, { zox_dirty_trigger })
    zox_log_ui(" > setting to window: position [%ix%i] size [%ix%i]", position.x, position.y, size.x, size.y)
}