void close_sdl_input() {
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}

void initialize_sdl_input() {
    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) fprintf(stderr, "  ! failed SDL joystick subsystem: %s\n", SDL_GetError());
}

void spawn_connected_devices(ecs_world_t *world, ecs_entity_t app) {
    local_keyboard = spawn_keyboard(world);
    local_mouse = spawn_mouse(world);
    local_touchscreen = spawn_touchscreen(world, prefab_touchscreen);
    zox_set(local_mouse, AppLink, { app })
    zox_set(local_touchscreen, AppLink, { app })

    /*zox_set(local_keyboard, PlayerLink, { zox_players[0] })
    zox_set(local_mouse, PlayerLink, { zox_players[0] })
    zox_set(local_touchscreen, PlayerLink, { zox_players[0] })*/
#ifndef zoxel_disable_gamepads
    initialize_sdl_gamepads(world);
#else
    zox_log(" ! gamepads are disabled\n")
#endif
}

void input_reset_sdl() {
    sdl_reset_mouse_wheel();
}

void input_extract_from_sdl(ecs_world_t *world, const SDL_Event event) {
    sdl_extract_keyboard(world, event);
    sdl_extract_mouse_wheel(event);
    if (event.type == SDL_JOYDEVICEADDED) handle_new_sdl_gamepad(world, event);
}
