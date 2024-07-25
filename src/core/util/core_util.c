ecs_world_t* initialize_ecs(int argc, char* argv[]) {
    int didFail = process_arguments(argc, argv);
    if (didFail == EXIT_FAILURE) return NULL;
    int cpu_core_count = SDL_GetCPUCount();
    fetch_pc_info(cpu_core_count);
    world = open_ecs(argc, argv, cpu_core_count);
    return world;
}

void update_core(ecs_world_t *world) {
    if (!headless) {
        device_reset_keyboard(world, keyboard_entity);
        // device_reset_mouse(world, mouse_entity);
        update_sdl(world, main_app, viewport_dimensions);
#ifdef zoxel_on_web
        update_web_canvas(world);   // handles resize event
#endif
    }
    opengl_clear_viewport_all(viewport_clear_color); // theres only one frame buffer for each app
    run_ecs(world);
    iterate_time(world);
    app_update_gpu(world);
#ifdef zoxel_log_frame_ms
    zox_log(" > frame time [%fms]\n", (float) (zox_delta_time * 1000.0f))
#endif
}
