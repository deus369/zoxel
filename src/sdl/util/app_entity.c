void zox_set_app_fullscreen(ecs_world_t* world, ecs_entity_t e, byte fullscreen) {
    if (!zox_valid(e) || !zox_has(e, WindowFullscreen)) {
        zox_log_error("invalid app in [zox_set_app_fullscreen]")
        return;
    }
    zox_set(e, WindowFullscreen, { fullscreen })
    zox_app_set_fullscreen(zox_gett_value(e, SDLWindow), fullscreen);
    int2 size;
    if (fullscreen) {
        size = get_screen_size();
        zox_log_sdl("+ setting app fullscreen")
    } else {
        size = zox_get_value(e, WindowSizeRestore)
        zox_log_sdl("+ setting app windowed")
    }
    set_viewport_size(world, size);
}

// sdl implementation for maximized state
void zox_set_app_maximized(ecs_world_t* world, ecs_entity_t e, byte maximized) {
    if (!zox_valid(e) || !zox_has(e, WindowFullscreen)) {
        zox_log_error("invalid app in [zox_set_app_fullscreen]")
        return;
    }
    zox_geter_value(e, WindowFullscreen, byte, fullscreen)
    zox_set(e, WindowMaximized, { maximized })
    if (!fullscreen) {
        int2 size;
        int2 position;
        if (maximized) {
            size = get_maximized_size(world, e);
            // position = int2_half(get_screen_size());
            zox_log_sdl("+ maximizing app [%ix%i]", size.x, size.y)
            zox_app_set_size(world, e, size);
        } else {
            zox_geter_value(e, WindowSizeRestore, int2, restore_size)
            zox_geter_value(e, WindowPositionRestore, int2, restore_position)
            size = restore_size;
            position = restore_position;
            zox_log_sdl("+ restoring app [%ix%i] at [%ix%i]", size.x, size.y, position.x, position.y)
            zox_app_set_size(world, e, size);
            zox_app_set_position(world, e, position);
        }
    }
}


// todo: get position2 to work
ecs_entity_t spawn_window_opengl(ecs_world_t *world,
    const char *name,
    int2 position2,
    const int2 size,
    const byte fullscreen,
    const byte maximized,
    const byte monitor)
{
    int2 window_size = size;
    if (fullscreen) {
        window_size = screen_dimensions;
    }
    const int2 position = get_window_position(window_size, screen_dimensions);
    SDL_Window* sdl_window = create_sdl_window(position, window_size, name);
    if (!sdl_window) {
        zox_log_error(" opengl did not create sdl_window, exiting zoxel")
        running = 0;
        return 0;
    }
    viewport_dimensions = screen_dimensions;
    const ecs_entity_t e = spawn_app_sdl(world,
        sdl_window,
        position,
        window_size,
        fullscreen,
        maximized,
        monitor);
    mouse_lock_window = e;
    if (create_window_opengl_context(world, e) == EXIT_FAILURE) {
        zox_log_error(" opengl_context creation failed")
        return 0;
    }
    return e;
}