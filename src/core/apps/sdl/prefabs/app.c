ecs_entity_t prefab_app;
ecs_entity_t main_app;

ecs_entity_t spawn_prefab_app(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_app")
    zox_add_tag(e, App)
    zox_prefab_set(e, SDLWindow, { NULL })
    zox_prefab_set(e, Context, { NULL })
    // zox_add_tag(e, ViewPort)
    prefab_app = e;
#ifdef zoxel_debug_prefabs
    zox_log(" > spawn_prefab app [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_app(ecs_world_t *world, SDL_Window* window, SDL_GLContext* context) {
    zox_instance(prefab_app)
    zox_name("app")
    zox_set(e, SDLWindow, { window })
    zox_set(e, Context, { context })
    main_app = e;
#ifdef zoxel_debug_spawns
    zox_log(" > spawned app [%lu]\n", e)
#endif
    return e;
}

void finish_opengl_rendering(ecs_world_t *world) {
    const SDLWindow *window = ecs_get(world, main_app, SDLWindow);
    if (window->value) SDL_GL_SwapWindow(window->value);
    else zox_logg("   ! did not swap opengl window\n")
}
