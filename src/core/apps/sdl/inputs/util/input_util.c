void initialize_sdl_inputs() {
}

void close_sdl_input() {
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}

void initialize_sdl_input() {
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) fprintf(stderr, "  ! failed SDL joystick subsystem: %s\n", SDL_GetError());
}

void spawn_connected_devices(ecs_world_t *world) {
    initialize_sdl_gamepads();
    spawn_keyboard(world);
    spawn_mouse(world);
    spawn_touchscreen(world, prefab_touchscreen, viewport_dimensions);
#ifndef zoxel_disable_gamepads
    unsigned char gamepad_type = 0;
    if (joysticks_count > 0) {
        if (is_xbox_gamepad(joystick)) gamepad_type = zox_gamepad_layout_type_xbox;
        if (is_steamdeck_gamepad(joystick)) gamepad_type = zox_gamepad_layout_type_steamdeck;
    }
    spawn_gamepad(world, gamepad_type);
#endif
}

void input_reset_sdl() {
    sdl_reset_mouse_wheel();
}

void input_extract_from_sdl(ecs_world_t *world, const SDL_Event event, const int2 viewport_size) {
    sdl_extract_keyboard(world, event);
    sdl_extract_mouse_wheel(event);
    if (event.type == SDL_JOYDEVICEADDED) {
        if (joystick == NULL) {
            joystick = SDL_JoystickOpen(event.jdevice.which);
            int joystick_id = SDL_JoystickInstanceID(joystick);
            zox_log(" > gamepad [%d] has connected\n", joystick_id)
        }
    }
}
