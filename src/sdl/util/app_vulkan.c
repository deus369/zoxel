ecs_entity_t spawn_main_window_vulkan(ecs_world_t *world, int2 position, int2 size, const byte fullscreen) {
    #ifdef zox_include_vulkan
    if (fullscreen) {
        size = screen_dimensions;
    }
    position = get_window_position(size, screen_dimensions);
    viewport_dimensions = screen_dimensions; // size;
    SDL_Window* sdl_window = create_sdl_window(position, size, fullscreen);
    if (sdl_window == NULL) {
        zox_log("    ! opengl did not create sdl_window, exiting zoxel\n")
        running = 0;
        return 0;
    }
    if (*SDL_GetError()) {
        zox_log(" ! is_using_vulkan: %s\n", SDL_GetError())
        return 0;
    }
    return spawn_main_window_vulkan(world, sdl_window);
    #else
    zox_log("! vulkan wasn't included in build\n")
    return 0;
    #endif
}
