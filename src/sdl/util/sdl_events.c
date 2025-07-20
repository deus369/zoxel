// todo: link sdl app events to sub systems
extern void opengl_dispose_resources(ecs_world_t *world);
extern void opengl_restore_resources(ecs_world_t *world);
extern void engine_end(); // engine
extern byte create_window_opengl_context(ecs_world_t *world, const ecs_entity_t e);

// move this to an app system function?
void update_sdl(ecs_world_t *world) {
    const ecs_entity_t e = main_app;
    input_reset_sdl();
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event)) {
        input_extract_from_sdl(world, event);
        if (event.type == SDL_QUIT) {
            engine_end();
        } else if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                on_window_resized(world, e, (int2) { event.window.data1, event.window.data2 });
            } else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) { // handles application resizing
                on_window_resized(world, e, (int2) { event.window.data1, event.window.data2 });
            } else if (event.window.event == SDL_WINDOWEVENT_MOVED) { // handles application resizing
                sdl_on_window_moved(world, e, (int2) { event.window.data1, event.window.data2 });
            } else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
                on_window_maximized(world, e, (int2) { event.window.data1, event.window.data2 });
            } else if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
                opengl_restore_resources(world);
                enable_time();
                on_window_restored(world, e, (int2) { event.window.data1, event.window.data2 });
            } else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                opengl_dispose_resources(world);
                disable_time();
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                disable_time();
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                enable_time();
            } /*else {
                zox_log("-> unknown sdl event [%i]", event.window.event)
            }*/
        }
    }
}
