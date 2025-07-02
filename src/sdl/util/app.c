// todo: link sdl app events to sub systems
extern void opengl_dispose_resources(ecs_world_t *world);
extern void opengl_restore_resources(ecs_world_t *world);
extern void engine_end(); // engine
extern byte create_window_opengl_context(ecs_world_t *world, const ecs_entity_t e);

// todo: get position2 to work
ecs_entity_t spawn_window_opengl(ecs_world_t *world, int2 position2, const int2 size, const byte fullscreen) {
    int2 window_size = size;
    if (fullscreen) {
        window_size = screen_dimensions;
    }
    const int2 position = get_window_position(window_size, screen_dimensions);
    SDL_Window* sdl_window = create_sdl_window(position, window_size, fullscreen);
    if (sdl_window == NULL) {
        zox_log("    ! opengl did not create sdl_window, exiting zoxel\n")
        running = 0;
        return 0;
    }
    viewport_dimensions = screen_dimensions;
    const ecs_entity_t e = spawn_app_sdl(world, sdl_window, position, window_size, fullscreen);
    mouse_lock_window = e;
    if (create_window_opengl_context(world, e) == EXIT_FAILURE) {
        return 0;
    }
    return e;
}

// opengl
ecs_entity_t spawn_main_window_opengl(ecs_world_t *world, int2 position, int2 size, const byte fullscreen) {
    return spawn_window_opengl(world, position, size, fullscreen);
}

byte create_window_opengl_context(ecs_world_t *world, const ecs_entity_t e) {
    zox_geter(e, SDLWindow, sdl_window)
    SDL_GLContext* gl_context = create_sdl_opengl_context(sdl_window->value);
    if (!gl_context) {
        zox_log("    ! opengl did not create gl_context, exiting zoxel\n")
        running = 0;
        return EXIT_FAILURE;
    }
    zox_set(e, Context, { gl_context })
    return EXIT_SUCCESS;
}

// wrapper for SDL GL Swap Window
void app_update_gpu(ecs_world_t *world) {
    if (!zox_valid(main_app)) {
        zox_log("! SDL2 Window Missing\n")
        return;
    }
    zox_geter(main_app, SDLWindow, window)
    if (!window->value) {
        zox_log("! SDL2 Window Broken\n")
        return;
    }
    SDL_GL_SwapWindow(window->value);
}

// move this to an app system function?
void update_sdl(ecs_world_t *world) { // const ecs_entity_t e) { // , const int2 viewport_size
    const ecs_entity_t e = main_app;
    input_reset_sdl();
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event)) {
        input_extract_from_sdl(world, event, viewport_dimensions);
        if (event.type == SDL_QUIT) {
            engine_end();
        } else if (event.type == SDL_WINDOWEVENT) {
            // if (!rendering) continue;
            if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) { // handles application resizing
                int2 size = (int2) { event.window.data1, event.window.data2 };
                on_window_resized(world, e, size);
            } else if (event.window.event == SDL_WINDOWEVENT_MOVED) { // handles application resizing
                int2 position = (int2) { event.window.data1, event.window.data2 };
                // byte is_fullscreen = zox_get_value(e, WindowFullscreen)
                SDL_Window* sdl_window = zox_get_value(e, SDLWindow)
                int window_height = get_sdl_window_header_size(sdl_window);
                int2 size = zox_get_value(e, WindowSize)
                position.x += size.x / 2;
                position.y += size.y / 2 + window_height;
                zox_set(e, WindowPosition, { position })
                // zox_log(" > window moved: %ix%i\n", position.x, position.y)
            } else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                opengl_dispose_resources(world);
            } else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
                opengl_restore_resources(world);
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                disable_time();
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                enable_time();
            }
        }
    }
}
