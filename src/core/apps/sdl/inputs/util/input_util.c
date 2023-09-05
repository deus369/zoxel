void initialize_sdl_inputs() {
    // todo: initialize it here
}

void spawn_connected_devices(ecs_world_t *world) {
    initialize_sdl_gamepads();
    spawn_keyboard(world);
    spawn_mouse(world);
    //if (joysticks_count > 0)
    unsigned char gamepad_type = 0;
    if (joysticks_count > 0) gamepad_type = is_xbox_gamepad(joystick);
    spawn_gamepad(world, gamepad_type);
    spawn_touchscreen(world);
}

void input_extract_from_sdl(ecs_world_t *world, SDL_Event event, int2 screen_dimensions) {
    // zoxel_log("extracting sdl inputs\n");
    sdl_extract_keyboard(world, event);
    sdl_extract_mouse(world, event, screen_dimensions);
    sdl_extract_touchscreen(world, event, screen_dimensions);
    // extract_gamepad(world, event);
    if (event.type == SDL_JOYDEVICEADDED) {
        if (joystick == NULL) {
            joystick = SDL_JoystickOpen(event.jdevice.which);
            int joystick_id = SDL_JoystickInstanceID(joystick);
            zoxel_log(" > gamepad [%d] has connected\n", joystick_id);
        }
    }
}