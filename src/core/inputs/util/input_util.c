void spawn_connected_devices(ecs_world_t *world)
{
    // printf("Devices detected: 2\n");
    spawn_keyboard(world);
    spawn_mouse(world);
    // spawn_mouse(world); //! \todo Why?? Why does this only count systems with 1 count in iterators.
}

void input_extract_from_sdl(ecs_world_t *world, SDL_Event event)
{
    extract_keyboard(world, event);
    extract_mouse(world, event);
}

void reset_input_devices(ecs_world_t *world)
{
    reset_keyboard(world);
    reset_mouse(world);
}