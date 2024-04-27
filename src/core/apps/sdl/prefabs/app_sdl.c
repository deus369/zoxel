ecs_entity_t prefab_app_sdl;

ecs_entity_t spawn_prefab_app_sdl(ecs_world_t *world) {
    zox_prefab_child(prefab_app)
    zox_prefab_name("prefab_app_sdl")
    zox_prefab_set(e, SDLWindow, { NULL })
    zox_prefab_set(e, Context, { NULL })
    // zox_add_tag(e, ViewPort)
    prefab_app_sdl = e;
    return e;
}

ecs_entity_t spawn_app_sdl(ecs_world_t *world, SDL_Window* window, SDL_GLContext* context, unsigned char fullscreen) {
    zox_instance(prefab_app_sdl)
    zox_name("app_sdl")
    zox_set(e, SDLWindow, { window })
    zox_set(e, Context, { context })
    zox_set(e, WindowFullscreen, { fullscreen })
    main_app = e;
    return e;
}

void finish_opengl_rendering(ecs_world_t *world) {
    const SDLWindow *window = zox_get(main_app, SDLWindow);
    if (window->value) SDL_GL_SwapWindow(window->value);
    else zox_logg("   ! did not swap opengl window\n")
}
