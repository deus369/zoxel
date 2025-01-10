extern void opengl_dispose_resources(ecs_world_t *world);
extern void opengl_restore_resources(ecs_world_t *world);
extern void engine_end(); // engine

ecs_entity_t spawn_main_window(ecs_world_t *world, int2 position, int2 size, const unsigned char fullscreen) {
    if (fullscreen) {
        size = screen_dimensions;
    }
    position = get_window_position(size, screen_dimensions);
    SDL_Window* sdl_window = create_sdl_window(position, size, fullscreen);
    if (sdl_window == NULL) {
        zox_log("    ! opengl did not create sdl_window, exiting zoxel\n")
        running = 0;
        return 0;
    }
    viewport_dimensions = screen_dimensions; // size;
    if (!is_using_vulkan) {
        const ecs_entity_t e = spawn_app_sdl(world, sdl_window, position, size, fullscreen);
        mouse_lock_window = e;
        return e;
    } else {
#ifdef zox_include_vulkan
        return spawn_main_window_vulkan(world, sdl_window);
#else
        return 0;
#endif
    }
}

unsigned char create_window_opengl_context(ecs_world_t *world, const ecs_entity_t e) {
    SDL_Window* sdl_window = zox_get_value(e, SDLWindow)
    SDL_GLContext* gl_context = create_sdl_opengl_context(sdl_window);
    zox_log(" ! gl_context is fine? [%s]\n", SDL_GetError())
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
void update_sdl(ecs_world_t *world, const ecs_entity_t e, const int2 viewport_size) {
    input_reset_sdl();
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event)) {
        input_extract_from_sdl(world, event, viewport_size);
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
