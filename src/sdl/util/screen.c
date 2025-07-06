// todo: make a viewport_dirty byte on app, cameras linked to app viewport can refresh
extern void resize_cameras(ecs_world_t *world, const int2 screen_size);

int2 get_sdl_screen_size() {
    int2 screen_size = int2_zero;
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    screen_size.x = displayMode.w;
    screen_size.y = displayMode.h;
    if (!(screen_size.x > 0 && screen_size.x < 22000 && screen_size.y > 0 && screen_size.y < 22000)) {
        zox_log(" - screen size is wrong [%ix%i]\n", screen_size.x, screen_size.y)
        zox_log(" > setting to 480x480\n")
        return (int2) { 480, 480 };
    }
    return screen_size;
}

int2 get_screen_size() {
    #ifdef zoxel_on_web
        return get_webasm_screen_size();
    #else
        return get_sdl_screen_size();
    #endif
}

void on_viewport_resized(ecs_world_t *world, const int2 new_size) {
    if (int2_equals(new_size, viewport_dimensions)) {
        return;
    }
    viewport_dimensions = new_size;
    if(viewport_dimensions.y <= 0) viewport_dimensions.y = 1;
    resize_cameras(world, viewport_dimensions); // set viewport size - triggers canvas resizing
}

void sdl_set_fullscreen(SDL_Window* window, byte is_fullscreen) {
    SDL_SetWindowFullscreen(window, is_fullscreen ? sdl_fullscreen_byte : 0);
}

void on_window_resized(ecs_world_t *world, const ecs_entity_t e, const int2 size) {
    if (int2_equals(size, screen_dimensions)) {
        // zox_log(" > screen dimensions already at [%ix%i]\n", screen_dimensions.x, screen_dimensions.y)
        return;
    }
    zox_log_ui(" > window resized [%ix%i]", size.x, size.y)
    screen_dimensions = size;
    on_viewport_resized(world, screen_dimensions);
    zox_set(e, WindowSize, { screen_dimensions })
    // apps_on_screen_resize(world, screen_dimensions);
    if (!zox_gett_value(e, WindowFullscreen)) zox_set(e, WindowSizeRestore, { screen_dimensions })
        zox_log_ui(" > screen dimensions set to [%ix%i]", screen_dimensions.x, screen_dimensions.y)
}

void on_sdl_window_restored(ecs_world_t *world, ecs_entity_t e) {
    if (!zox_has(e, WindowSize)) {
        zox_log(" ! no WindowSize on app [%lu]\n", e)
        return;
    }
    int2 size = zox_get_value(e, WindowSizeRestore)
    if (size.x == 0 && size.y == 0) {
        size.x = screen_dimensions.x / 2;
        size.y = screen_dimensions.y / 2;
    }
    const int2 window_position = get_window_position(size, screen_dimensions);
    SDL_Window* sdl_window = zox_get_value(e, SDLWindow)
    SDL_SetWindowSize(sdl_window, size.x, size.y);
    SDL_SetWindowPosition(sdl_window, window_position.x, window_position.y);
    zox_set(e, WindowSize, { size })
    zox_log_ui(" > setting to window: position [%ix%i] size [%ix%i]", window_position.x, window_position.y, size.x, size.y)
}