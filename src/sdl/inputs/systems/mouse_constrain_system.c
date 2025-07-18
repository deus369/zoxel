// how to link main_window, viewport_dimensions and mouse
void MouseConstrainSystem(ecs_iter_t *it) {
    zox_sys_world()
    // todo: support for multi window contstraints, pass in multiple sdl windows here
    if (!zox_valid(mouse_lock_window)) {
        return;
    }
    zox_geter_value2(mouse_lock_window, SDLWindow, SDL_Window*, sdl_window)
    const int2 lock_position = get_mouse_center_point(world, mouse_lock_window);
    zox_sys_begin()
    zox_sys_in(MouseLock)
    zox_sys_in(Children)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MouseLock, mouseLock)
        zox_sys_i(Children, children)
        SDL_SetRelativeMouseMode(mouseLock->value);
        if (mouseLock->value) {
            // const int2 new_mouse_position = (int2) { viewport_dimensions.x / 2, viewport_dimensions.y / 2  };
            SDL_WarpMouseInWindow(sdl_window, lock_position.x, lock_position.y);
            for (int j = 0; j < children->length; j++) {
                const ecs_entity_t zevice = children->value[j];
                if (zox_has(zevice, ZevicePointerPosition)) {
                    zox_get_muter(zevice, ZevicePointerPosition, position)
                    position->value = lock_position;
                }
            }
        }
    }
} zox_declare_system(MouseConstrainSystem)
