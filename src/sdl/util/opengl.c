// wrapper for SDL GL Swap Window
void app_update_gpu(ecs_world_t *world) {
    if (headless) {
        return;
    }
    if (!zox_valid(main_app)) {
        zox_log_error("[main_app] is missing");
        return;
    }
    zox_geter(main_app, SDLWindow, window)
    if (!window->value) {
        zox_log_error("[main_app] is has invalid SDLWindow");
        return;
    }
    SDL_GL_SwapWindow(window->value);
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