ecs_entity_t spawn_main_window(ecs_world_t *world) {
    SDL_Window* window = create_sdl_window(default_window_position, default_window_size, fullscreen);
    if (window == NULL) {
        zox_log("    ! opengl did not create window, exiting zoxel\n")
        running = 0;
        return 0;
    }
    if (fullscreen) {
        viewport_dimensions = screen_dimensions;
    } else {
        viewport_dimensions = default_window_size;
    }
    mouse_lock_window = window;
    if (!is_using_vulkan) {
        SDL_GLContext* gl_context = create_sdl_opengl_context(window);
        if (gl_context == NULL) {
            zox_log("    ! opengl did not create context, exiting zoxel\n")
            running = 0;
            return 0;
        }
        const ecs_entity_t e = spawn_app_sdl(world, window, gl_context, default_window_position, default_window_size, fullscreen);
        return e;
    } else {
#ifdef zox_include_vulkan
        return spawn_main_window_vulkan(world, window);
#else
        return 0;
#endif
    }
}

void app_update_gpu(ecs_world_t *world) {
    const SDLWindow *window = zox_get(main_app, SDLWindow);
    if (window->value) SDL_GL_SwapWindow(window->value);
    else zox_logg("   ! did not swap opengl window\n")
}

// move this to an app system function?
void update_sdl(ecs_world_t *world, ecs_entity_t e, const int2 viewport_size) {
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event)) {
        input_extract_from_sdl(world, event, viewport_size);
        int eventType = event.type;
        if (eventType == SDL_QUIT) {
            zox_logg(" > window was quit\n")
            engine_end();
        } else if (eventType == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) { // handles application resizing
                if (!rendering) continue;
                int2 new_screen_size = (int2) { event.window.data1, event.window.data2 };
                on_viewport_resized(world, new_screen_size);
                screen_dimensions = new_screen_size;
                unsigned char is_fullscreen = zox_get_value(e, WindowFullscreen)
                if (!is_fullscreen) {
                    zox_set(e, WindowSize, { new_screen_size })
                }
            } else if (event.window.event == SDL_WINDOWEVENT_MOVED) { // handles application resizing
                if (!rendering) continue;
                int2 new_window_position = (int2) { event.window.data1, event.window.data2 };
                unsigned char is_fullscreen = zox_get_value(e, WindowFullscreen)
                if (!is_fullscreen) {
                    zox_set(e, WindowPosition, { new_window_position })
                }
            } else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                zox_logg(" > window was minimized\n")
                opengl_dispose_resources(world);
            } else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
                zox_logg(" > window was restored\n")
                opengl_restore_resources(world);
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                updating_time = 0;
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                updating_time = 1;
            }
        }
    }
}
