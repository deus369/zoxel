ecs_entity_t prefab_app_sdl;

ecs_entity_t spawn_prefab_app_sdl(ecs_world_t *world) {
    zox_prefab_child(prefab_app)
    zox_prefab_name("app_sdl")
    zox_prefab_set(e, SDLWindow, { NULL })
    zox_prefab_set(e, Context, { NULL })
    zox_prefab_set(e, WindowFullscreen, { 0 })
    // zox_add_tag(e, ViewPort)
    prefab_app_sdl = e;
    return e;
}

// SDL_GLContext* context,
ecs_entity_t spawn_app_sdl(ecs_world_t *world, SDL_Window* window, const int2 position, const int2 size, const byte fullscreen) {
    zox_instance(prefab_app_sdl)
    zox_name("app_sdl")
    zox_set(e, SDLWindow, { window })
    zox_set(e, WindowPosition, { position })
    zox_set(e, WindowSize, { size })
    zox_set(e, WindowFullscreen, { fullscreen })
    main_app = e;
    return e;
}
