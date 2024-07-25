// how to link main_window, viewport_dimensions and mouse
void MouseConstrainSystem(ecs_iter_t *it) {
    // todo: support for multi window contstraints, pass in multiple sdl windows here
    if (!mouse_lock_window) return;
    zox_field_in(MouseLock, mouseLocks, 1)
    zox_field_in(Children, childrens, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(MouseLock, mouseLocks, mouseLock)
        SDL_SetRelativeMouseMode(mouseLock->value);
        if (mouseLock->value) {
            zox_field_i(Children, childrens, children)
            const int2 new_mouse_position = (int2) { viewport_dimensions.x / 2, viewport_dimensions.y / 2  };
            SDL_WarpMouseInWindow(mouse_lock_window, new_mouse_position.x, new_mouse_position.y);
            for (int j = 0; j < children->length; j++) {
                const ecs_entity_t zevice = children->value[j];
                if (zox_has(zevice, ZevicePointerPosition)) {
                    zox_get_muter(zevice, ZevicePointerPosition, position)
                    position->value = new_mouse_position;
                }
            }
        }
    }
} zox_declare_system(MouseConstrainSystem)
