// todo: handle this per zevice level, keep SDL_joystick as an entity and just pull from of parent of zevice
void GamepadExtractSystem(ecs_iter_t *it) {
    // get list of sdl joyosticks ? todo: disconnect system for devices
    sdl_gamepad_handle_disconnect(joystick);
    ecs_world_t *world = it->world;
    const Children *childrens = ecs_field(it, Children, 2);
    for (int i = 0; i < it->count; i++) {
        const Children *childrenss = &childrens[i];
        sdl_extract_gamepad(joystick, world, childrenss);
    }
    // zox_log("   > GamepadExtractSystem [%i]\n", it->count)
} zox_declare_system(GamepadExtractSystem)
