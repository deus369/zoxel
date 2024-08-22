void initialize_sdl_inputs() {
}

void close_sdl_input() {
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}

void initialize_sdl_input() {
    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) fprintf(stderr, "  ! failed SDL joystick subsystem: %s\n", SDL_GetError());
}

void spawn_connected_devices(ecs_world_t *world) {
    keyboard_entity = spawn_keyboard(world);
    mouse_entity = spawn_mouse(world);
    touchscreen_entity = spawn_touchscreen(world, prefab_touchscreen, viewport_dimensions);
#ifndef zoxel_disable_gamepads
    initialize_sdl_gamepads();
#else
    zox_log(" ! gamepads are disabled\n")
#endif
}

void input_reset_sdl() {
    sdl_reset_mouse_wheel();
}

void input_extract_from_sdl(ecs_world_t *world, const SDL_Event event, const int2 viewport_size) {
    sdl_extract_keyboard(world, event);
    sdl_extract_mouse_wheel(event);
    if (event.type == SDL_JOYDEVICEADDED) handle_new_sdl_gamepad(world, event);
}
