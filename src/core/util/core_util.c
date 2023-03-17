//! The main update loop.
void update_core() {
    begin_timing()
    if (!headless) {
        reset_input_devices(world);
        update_sdl(world);
        #ifdef WEB_BUILD
        update_web_canvas(world);   // handles resize event
        #endif
        render_pre_loop();
    }
    // ecs_log_set_level(1);    // use this to debug system pipelines
    ecs_progress(world, 0);
    if (!headless) {
        set_mouse_constrained(get_mouse_constrained());
        render_loop_temp(); // opengl render commands
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
    int cpuCoreCount = SDL_GetCPUCount();
    world = open_ecs(argc, argv, profiler, cpuCoreCount); // begin ecs
    return EXIT_SUCCESS;
}

void close_core() {
    close_ecs();
    if (!headless) {
        dispose_opengl();
        SDL_Quit();
    }
}