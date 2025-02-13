void GamepadExtractSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(Children, childrens, 1)
    zox_field_in(SDLGamepad, sdlGamepads, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Children, childrens, children)
        zox_field_i(SDLGamepad, sdlGamepads, sdlGamepad)
        if (sdl_gamepad_handle_disconnect(sdlGamepad->value)) {
            sdl_extract_gamepad(sdlGamepad->value, world, children);
        }
    }
} zox_declare_system(GamepadExtractSystem)
