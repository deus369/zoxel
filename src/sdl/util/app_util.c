extern void opengl_dispose_resources(ecs_world_t *world);
extern void opengl_restore_resources(ecs_world_t *world);
extern void engine_end(); // engine
extern unsigned char create_window_opengl_context(ecs_world_t *world, const ecs_entity_t e);

// todo: get position2 to work
ecs_entity_t spawn_window_opengl(ecs_world_t *world, int2 position2, const int2 size, const unsigned char fullscreen) {
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

ecs_entity_t spawn_main_window(ecs_world_t *world, int2 position, int2 size, const unsigned char fullscreen) {
    if (is_using_vulkan) {
#ifndef zox_include_vulkan
        zox_log("! vulkan wasn't included in build\n")
        return 0;
#else
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
#endif
    } else {
        return spawn_window_opengl(world, position, size, fullscreen);
    }
}

unsigned char create_window_opengl_context(ecs_world_t *world, const ecs_entity_t e) {
    SDL_Window* sdl_window = zox_get_value(e, SDLWindow)
    SDL_GLContext* gl_context = create_sdl_opengl_context(sdl_window);
    if (!gl_context) {
        zox_log("    ! opengl did not create gl_context, exiting zoxel\n")
        running = 0;
        return EXIT_FAILURE;
    }
    zox_set(e, Context, { gl_context })
    return EXIT_SUCCESS;
}

void app_update_gpu(ecs_world_t *world) {
    if (main_app == 0) return;
    const SDLWindow *window = zox_get(main_app, SDLWindow);
    if (window->value) SDL_GL_SwapWindow(window->value);
    else zox_log("   ! did not swap opengl window\n")
}

// move this to an app system function?
void update_sdl(ecs_world_t *world) { // const ecs_entity_t e) { // , const int2 viewport_size
    const ecs_entity_t e = main_app;
    input_reset_sdl();
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event)) {
        input_extract_from_sdl(world, event, viewport_dimensions);
        int eventType = event.type;
        if (eventType == SDL_QUIT) {
            // zox_log(" > window was quit\n")
            engine_end();
        } else if (eventType == SDL_WINDOWEVENT) {
            if (!rendering) continue;
            if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) { // handles application resizing
                int2 size = (int2) { event.window.data1, event.window.data2 };
                on_window_resized(world, e, size);
            } else if (event.window.event == SDL_WINDOWEVENT_MOVED) { // handles application resizing
                int2 position = (int2) { event.window.data1, event.window.data2 };
                // unsigned char is_fullscreen = zox_get_value(e, WindowFullscreen)
                SDL_Window* sdl_window = zox_get_value(e, SDLWindow)
                int window_height = get_sdl_window_header_size(sdl_window);
                int2 size = zox_get_value(e, WindowSize)
                position.x += size.x / 2;
                position.y += size.y / 2 + window_height;
                zox_set(e, WindowPosition, { position })
                // zox_log(" > window moved: %ix%i\n", position.x, position.y)
            } else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                // zox_log(" > window was minimized\n")
                opengl_dispose_resources(world);
            } else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
                // zox_log(" > window was restored\n")
                opengl_restore_resources(world);
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                // updating_time = 0;
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                // updating_time = 1;
            }
        }
    }
}
