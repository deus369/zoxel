// Camera2D prefab
ecs_entity_t app_prefab;

ecs_entity_t spawn_app_prefab(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "app_prefab");
    zoxel_add_tag(world, e, App);
    // zoxel_add_tag(world, e, ViewPort);
    zoxel_add(world, e, SDLWindow);
    zoxel_add(world, e, Context);
    app_prefab = e;
    ecs_defer_end(world);
    return e;
}

ecs_entity_t main_app;

ecs_entity_t spawn_app(ecs_world_t *world, SDL_Window* window, SDL_GLContext* context)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, app_prefab);
    ecs_set(world, e, SDLWindow, { window });
    ecs_set(world, e, Context, { context });
    // printf("Spawned Camera [%lu]\n", (long unsigned int) e);
    main_app = e;
    ecs_defer_end(world);
    return e;
}

void finish_opengl_rendering(ecs_world_t *world)
{
    const SDLWindow *window = ecs_get(world, main_app, SDLWindow);
    SDL_GL_SwapWindow(window->value);
}