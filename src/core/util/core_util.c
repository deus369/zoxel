int cpu_core_count;

void update_core() {
    begin_timing_absolute()
    if (!headless) {
        #ifdef zoxel_inputs
            reset_input_devices(world);
        #endif
        update_sdl(world);
        #ifdef WEB_BUILD
            update_web_canvas(world);   // handles resize event
        #endif
        render_pre_loop();
    }
    // ecs_log_set_level(1);    // use this to debug system pipelines
    ecs_progress(world, 0);
    if (!headless) {
        #ifdef zoxel_cameras
            set_mouse_constrained(get_mouse_constrained(), screen_dimensions);
        #endif
        render_loop();
    }
    zoxel_delta_time = get_timing_passed();
    #ifdef zoxel_log_frame_ms
        zoxel_log(" > frame time [%fms]\n", (float) (zoxel_delta_time * 1000.0f));
    #endif
}

int begin_core(int argc, char* argv[]) {
    int didFail = process_arguments(argc, argv);
    if (didFail == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    cpu_core_count = SDL_GetCPUCount();
    world = open_ecs(argc, argv, profiler, cpu_core_count); // begin ecs
    return EXIT_SUCCESS;
}

void close_core() {
    if (!headless) {
        dispose_opengl();
    }
    close_ecs();
    if (!headless) {
        close_audio_sdl();
        SDL_Quit();
    }
}