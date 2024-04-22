void GamepadExtractSystem(ecs_iter_t *it) {
    sdl_gamepad_handle_disconnect(joystick);
    zox_iter_world()
    const Children *childrens = ecs_field(it, Children, 2);
    for (int i = 0; i < it->count; i++) {
        const Children *childrenss = &childrens[i];
        sdl_extract_gamepad(joystick, world, childrenss);
    }
} zox_declare_system(GamepadExtractSystem)
