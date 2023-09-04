ecs_entity_t app_prefab;
ecs_entity_t main_app;

ecs_entity_t spawn_prefab_app(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_app")
    zox_add_tag(e, App)
    // zox_add_tag(e, ViewPort)
    zox_add(e, SDLWindow)
    zox_add(e, Context)
    ecs_defer_end(world);
    app_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab app [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_app(ecs_world_t *world, SDL_Window* window, SDL_GLContext* context) {
    zox_instance(app_prefab)
    zox_set_only(e, SDLWindow, { window })
    zox_set_only(e, Context, { context })
    main_app = e;
    return e;
}

void finish_opengl_rendering(ecs_world_t *world) {
    const SDLWindow *window = ecs_get(world, main_app, SDLWindow);
    if (window->value) SDL_GL_SwapWindow(window->value);
    else zoxel_log("    ! did not swap opengl window\n");
}

#ifdef zoxel_include_vulkan
    ecs_entity_t spawn_app_vulkan(ecs_world_t *world, SDL_Window* window, VkSurfaceKHR* surface) {
        ecs_defer_begin(world);
        zox_instance(app_prefab)
        zox_set_only(e, SDLWindow, { window })
        zox_set_only(e, VulkanSurface, { surface })
        ecs_defer_end(world);
        main_app = e;
        return e;
    }
#endif