#ifdef zox_lib_sdl
void GamepadExtractSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Children)
    zox_sys_in(SDLGamepad)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Children, children)
        zox_sys_i(SDLGamepad, sdlGamepad)
        if (sdl_gamepad_handle_disconnect(sdlGamepad->value)) {
            sdl_extract_gamepad(sdlGamepad->value, world, children);
        }
    }
} zox_declare_system(GamepadExtractSystem)
#endif