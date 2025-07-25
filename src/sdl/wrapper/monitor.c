byte zox_app_get_monitor(ecs_world_t *world, ecs_entity_t e) {
    if (!zox_valid(e) || !zox_has(e, SDLWindow)) {
        return 0;
    }
    zox_geter_value2(e, SDLWindow, SDL_Window*, sdl_window)
    return SDL_GetWindowDisplayIndex(sdl_window);
}

int2 calculate_monitor_position(byte index, byte center_window, int2 ws) {
    SDL_Rect b;
    if (SDL_GetDisplayBounds(index, &b)) {
        zox_log_error("Failed to get display bounds for display %d: %s", index, SDL_GetError());
        return int2_zero;
    }
    int2 position = (int2) { b.x, b.y };
    if (center_window) {
        position.x += (b.w - ws.x) / 2;
        position.y += (b.h - ws.y) / 2;
    }
    return position;
}

byte zox_app_set_monitor(SDL_Window *window, byte index, byte center_window) {
    if (!window) {
        return 0;
    }
    SDL_Rect b;
    if (SDL_GetDisplayBounds(index, &b)) {
        zox_log_error("Failed to get display bounds for display %d: %s", index, SDL_GetError());
        return 0;
    }
    int2 position = (int2) { b.x, b.y };
    if (center_window) {
        int2 ws;
        SDL_GetWindowSize(window, &ws.x, &ws.y);
        position.x -= (b.w - ws.x) / 2;
        position.y -= (b.h - ws.y) / 2;
    }
    SDL_SetWindowPosition(window, position.x, position.y);
    if (is_log_monitors) {
        zox_log(" + zox_app_set_monitor [%i] at [%ix%i]", index, position.x, position.y)
        zox_log("   + screen bounds [%ix%i]", b.x, b.y)
        for (int i = 0; i <= 4; i++) {
            SDL_Rect b2;
            if (!SDL_GetDisplayBounds(i, &b2)) {
                zox_log(" - testing screen [%i] bounds [%ix%i - %ix%i]", i, b2.x, b2.y, b2.w, b2.h)
            }
        }
    }
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