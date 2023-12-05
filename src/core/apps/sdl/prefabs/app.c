ecs_entity_t app_prefab;
ecs_entity_t main_app;

ecs_entity_t spawn_prefab_app(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_app")
    zox_add_tag(e, App)
    zox_add(e, SDLWindow)
    zox_add(e, Context)
    // zox_add_tag(e, ViewPort)
    app_prefab = e;
#ifdef zoxel_debug_prefabs
    zox_log(" > spawn_prefab app [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_app(ecs_world_t *world, SDL_Window* window, SDL_GLContext* context) {
    zox_instance(app_prefab)
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

#ifdef zoxel_include_vulkan

ecs_entity_t spawn_app_vulkan(ecs_world_t *world, SDL_Window* window, VkSurfaceKHR* surface) {
    zox_instance(app_prefab)
    zox_set(e, SDLWindow, { window })
    zox_set(e, VulkanSurface, { surface })
    main_app = e;
    return e;
}

#endif
