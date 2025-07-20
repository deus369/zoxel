ecs_entity_t prefab_app_sdl;

ecs_entity_t spawn_prefab_app_sdl(ecs_world_t *world) {
    zox_prefab_child(prefab_app)
    zox_prefab_name("app_sdl")
    zox_prefab_set(e, SDLWindow, { NULL })
    zox_prefab_set(e, Context, { NULL })
    zox_prefab_set(e, WindowFullscreen, { 0 })
    // zox_add_tag(e, ViewPort)
    return e;
}

ecs_entity_t spawn_app_sdl(ecs_world_t *world,
    const char* name,
    const byte fullscreen,
    const byte maximized,
    const byte monitor)
{
    int2 screen_size = get_screen_size_monitor(monitor);
    int2 size_restore = int2_half(screen_size);
    int2 size = fullscreen ? screen_size : size_restore;
    // calculate position
    int2 position = calculate_monitor_position(monitor, 1, size_restore);
    byte flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    if (fullscreen) {
        flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP;
        if (maximized) {
            flags = flags | SDL_WINDOW_MAXIMIZED;
        }
    }
    SDL_Window* sdl_window = create_sdl_window(position, size, name, flags);
    if (!sdl_window) {
        zox_log_error(" opengl did not create sdl_window, exiting zoxel")
        return 0;
    }
    if (!fullscreen && maximized) {
        zox_app_set_maximized(sdl_window, maximized);
    }

    zox_instance(prefab_app_sdl)
    zox_name("app_sdl")
    zox_set(e, SDLWindow, { sdl_window })
    // current transform data
    zox_set(e, WindowPosition, { position })
    zox_set(e, WindowSize, { size })
    // window restore data
    zox_set(e, WindowPositionRestore, { position })
    zox_set(e, WindowSizeRestore, { size_restore })
    // our properties
    zox_set(e, WindowFullscreen, { fullscreen })
    zox_set(e, WindowMaximized, { maximized })
    zox_set(e, WindowMonitor, { monitor })

    // debugs
    zox_log_sdl("+ spawned window !")
    zox_log_sdl("   - position [%ix%i]", position.x, position.y)
    zox_log_sdl("   - size [%ix%i]", size.x, size.y)
    zox_log_sdl("   - fullscreen [%i]", fullscreen)
    zox_log_sdl("   - maximized [%i]", maximized)
    zox_log_sdl("   - monitor [%i]", monitor)

    return e;
}
