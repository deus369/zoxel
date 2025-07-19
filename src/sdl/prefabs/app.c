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
    SDL_Window* window,
    const int2 position,
    const int2 size,
    const byte fullscreen,
    const byte maximized,
    const byte monitor)
{
    zox_instance(prefab_app_sdl)
    zox_name("app_sdl")
    zox_set(e, SDLWindow, { window })
    zox_set(e, WindowPosition, { position })
    zox_set(e, WindowPositionRestore, { position })
    zox_set(e, WindowSize, { size })
    zox_set(e, WindowSizeRestore, { size })
    zox_set(e, WindowFullscreen, { fullscreen })
    zox_set(e, WindowMaximized, { maximized })
    // set sdl window properties here
    zox_app_set_fullscreen(window, fullscreen);
    if (!fullscreen && maximized) {
        zox_app_set_maximized(window, maximized);
    }
    zox_app_set_monitor(window, monitor, 1);
    zox_log_sdl("+ spawned window !")
    zox_log_sdl("   - position [%ix%i]", position.x, position.y)
    zox_log_sdl("   - size [%ix%i]", size.x, size.y)
    zox_log_sdl("   - fullscreen [%i]", fullscreen)
    zox_log_sdl("   - maximized [%i]", maximized)
    zox_log_sdl("   - monitor [%i]", monitor)
    return e;
}
