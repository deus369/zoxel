void spawn_connected_devices(ecs_world_t *world)
{
    // printf("Devices detected: 2\n");
    spawn_keyboard(world);
    spawn_mouse(world);
    if (joysticks_count > 0)
    {
        spawn_gamepad(world);
    }
}

void input_extract_from_sdl(ecs_world_t *world, SDL_Event event)
{
    extract_keyboard(world, event);
    extract_mouse(world, event);
    // extract_gamepad(world, event);
    if (event.type == SDL_JOYDEVICEADDED)
    {
        joystick = SDL_JoystickOpen(event.jdevice.which);
        int joystick_id = SDL_JoystickInstanceID(joystick);
        zoxel_log("Joystick [%d] has been reconnected.\n", joystick_id);
    }
}

void reset_input_devices(ecs_world_t *world)
{
    reset_gamepad(world, gamepad_entity);
    reset_keyboard(world, keyboardEntity);
    reset_mouse(world);
}