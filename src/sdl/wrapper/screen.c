byte zox_app_get_monitor(ecs_world_t *world, ecs_entity_t e) {
    if (!zox_valid(e) || !zox_has(e, SDLWindow)) {
        return 0;
    }
    zox_geter_value2(e, SDLWindow, SDL_Window*, sdl_window)
    return SDL_GetWindowDisplayIndex(sdl_window);
}

byte zox_app_set_monitor(SDL_Window *window, byte index, byte center_window) {
    if (!window) {
        return 0;
    }
    SDL_Rect bounds;
    if (SDL_GetDisplayBounds(index, &bounds) != 0) {
        zox_log_error("Failed to get display bounds for display %d: %s", index, SDL_GetError());
        return 0;
    }
    int2 window_size;
    SDL_GetWindowSize(window, &window_size.x, &window_size.y);
    int target_x = bounds.x;
    int target_y = bounds.y;
    if (center_window) {
        target_x += (bounds.w - window_size.x) / 2;
        target_y += (bounds.h - window_size.y) / 2;
    }
    SDL_SetWindowPosition(window, target_x, target_y);
    // zox_log(" + zox_app_set_monitor %i at (%d, %d)", index, target_x, target_y);
    return 1;
}

void zox_app_set_monitor_e(ecs_world_t *world, ecs_entity_t e, byte monitor) {
    zox_geter_value2(e, SDLWindow, SDL_Window*, sdl_window)
    zox_app_set_monitor(sdl_window, monitor, 1);
    zox_set(e, WindowMonitor, { monitor })
}

int2 get_screen_size_monitor(byte monitor_index) {
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(monitor_index, &displayMode);
    return (int2) { displayMode.w, displayMode.h };
}

int2 get_sdl_screen_size() {
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    return (int2) { displayMode.w, displayMode.h };
}

int2 get_screen_size() {
#ifdef zoxel_on_web
    return get_webasm_screen_size();
#else
    return get_screen_size_monitor(monitor);
#endif
}
void zox_app_set_fullscreen(SDL_Window* window, byte fullscreen) {
    SDL_SetWindowFullscreen(window, fullscreen ? sdl_fullscreen_byte : 0);
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