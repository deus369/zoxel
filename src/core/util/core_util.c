int begin_core(int argc, char* argv[]) {
    int didFail = process_arguments(argc, argv);
    if (didFail == EXIT_FAILURE) return EXIT_FAILURE;
    int cpu_core_count = SDL_GetCPUCount();
    begin_platforms(cpu_core_count);
    world = open_ecs(argc, argv, profiler, cpu_core_count);
    return EXIT_SUCCESS;
}

void close_core() {
    close_ecs();
    if (!headless) on_close_rendering(world);
    if (!headless) {
        close_sdl_input();
        close_sdl_video();
        close_audio_sdl();
    }
}

void update_core() {
    if (!headless) {
        #ifdef zoxel_inputs
            device_reset_keyboard(world, keyboard_entity);
            device_reset_mouse(world, mouse_entity);
        #endif
        update_sdl(world);
        #ifdef zoxel_on_web
            update_web_canvas(world);   // handles resize event
        #endif
        if (rendering) render_pre_loop();
    }
    // ecs_log_set_level(1);    // use this to debug system pipelines
    ecs_progress(world, 0);
    if (!headless && rendering) render_loop();
    iterate_time();
    #ifdef zoxel_log_frame_ms
        zoxel_log(" > frame time [%fms]\n", (float) (zox_delta_time * 1000.0f));
    #endif
}
