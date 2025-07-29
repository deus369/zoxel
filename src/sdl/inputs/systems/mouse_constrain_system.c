void MouseConstrainSystem(ecs_iter_t *it) {
    zox_sys_world()
    // todo: support for multi window contstraints, pass in multiple sdl windows here
    //if (!zox_valid(main_app)) {
    //    return;
    //}
    //zox_geter_value2(main_app, SDLWindow, SDL_Window*, sdl_window)
    zox_sys_begin()
    zox_sys_in(DeviceDisabled)
    zox_sys_in(MouseLock)
    zox_sys_in(Children)
    zox_sys_in(AppLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DeviceDisabled, deviceDisabled)
        zox_sys_i(MouseLock, mouseLock)
        zox_sys_i(Children, children)
        zox_sys_i(AppLink, appLink)
        if (!zox_valid(appLink->value) || deviceDisabled->value) {
            continue;
        }
        zox_geter_value2(appLink->value, SDLWindow, SDL_Window*, sdl_window)
        const int2 lock_position = get_mouse_center_point(world, appLink->value);
        // now lock
        SDL_SetRelativeMouseMode(mouseLock->value);
        if (mouseLock->value) {
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
