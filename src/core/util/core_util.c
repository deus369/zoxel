int cpu_core_count;
unsigned char cpu_tier;

unsigned char get_cpu_tier(int core_count) {
    if (core_count > 8) {
        zoxel_log(" > high core count detected [%i]\n", core_count);
        return 3;
    } else if (core_count > 6) {
        zoxel_log(" > average core count detected [%i]\n", core_count);
        return 2;
    } else if (core_count > 4) {
        zoxel_log(" > low (-) core count detected [%i]\n", core_count);
        return 1;
    } else {
        zoxel_log(" > lowest core count detected [%i]\n", core_count);
        return 0;
    }
}

void update_core() {
    if (!headless) {
        #ifdef zoxel_inputs
            reset_input_devices(world);
        #endif
        update_sdl(world);
        #ifdef zoxel_on_web
            update_web_canvas(world);   // handles resize event
        #endif
        if (rendering) render_pre_loop();
    }
    // ecs_log_set_level(1);    // use this to debug system pipelines
    ecs_progress(world, 0);
    if (!headless) {
        #ifdef zoxel_cameras
            set_mouse_constrained(get_mouse_constrained(), screen_dimensions);
        #endif
        if (rendering) {
            render_loop();
        }
    }
    iterate_time();
    #ifdef zoxel_log_frame_ms
        zoxel_log(" > frame time [%fms]\n", (float) (zox_delta_time * 1000.0f));
    #endif
}

int begin_core(int argc, char* argv[]) {
    int didFail = process_arguments(argc, argv);
    if (didFail == EXIT_FAILURE) return EXIT_FAILURE;
    cpu_core_count = SDL_GetCPUCount();
    cpu_tier = get_cpu_tier(cpu_core_count);
    world = open_ecs(argc, argv, profiler, cpu_core_count);
    return EXIT_SUCCESS;
}

void close_core() {
    close_ecs();
    if (!headless) {
        dispose_shaders();
        close_audio_sdl();
        SDL_Quit();
    }
}