// how to link main_window, viewport_dimensions and mouse
void MouseConstrainSystem(ecs_iter_t *it) {
    // todo: support for multi window contstraints, pass in multiple sdl windows here
    if (!mouse_lock_window) return;
    const int2 locked_dimensions = viewport_dimensions;
    zox_field_in(MouseLock, mouseLocks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(MouseLock, mouseLocks, mouseLock)
        SDL_SetRelativeMouseMode(mouseLock->value);
        if (mouseLock->value) SDL_WarpMouseInWindow(mouse_lock_window, locked_dimensions.x / 2, locked_dimensions.y / 2);
    }
} zox_declare_system(MouseConstrainSystem)
