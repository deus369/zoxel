void MouseConstrainSystem(ecs_iter_t *it) {
    // how to link main_window, screen_dimensions and mouse
    ecs_world_t *world = it->world;
    const MouseLock *mouseLocks = ecs_field(it, MouseLock, 1);
    for (int i = 0; i < it->count; i++) {
        const MouseLock *mouseLock = &mouseLocks[i];
        SDL_SetRelativeMouseMode(mouseLock->value);
        if (mouseLock->value) SDL_WarpMouseInWindow(main_window, screen_dimensions.x / 2, screen_dimensions.y / 2);
    }
} zox_declare_system(MouseConstrainSystem)


/*ifdef zox_disable_mouse_constraint
    return 0;
#endif
#ifdef zoxel_mouse_emulate_touch
    return 0;
#endif*/