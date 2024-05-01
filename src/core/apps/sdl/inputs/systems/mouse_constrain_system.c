// how to link main_window, screen_dimensions and mouse
void MouseConstrainSystem(ecs_iter_t *it) {
    zox_field_in(MouseLock, mouseLocks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(MouseLock, mouseLocks, mouseLock)
        SDL_SetRelativeMouseMode(mouseLock->value);
        if (mouseLock->value) SDL_WarpMouseInWindow(main_window, screen_dimensions.x / 2, screen_dimensions.y / 2);
    }
} zox_declare_system(MouseConstrainSystem)
