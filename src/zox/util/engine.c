void engine_end() {
    running = 0;
#ifdef zoxel_on_web
    emscripten_cancel_main_loop();
#endif
}

void handle_segfault(int sig) {
    zox_log(" ! segfault detected [%i], exiting zox engine\n", sig)
    exit(0);
}

void handle_terminal_close(int sig) {
    zox_logg(" > terminal close detected [control + c]\n")
    engine_end();
}

void update_zox_frame() {
#ifdef zoxel_time_main_loop
    begin_timing_absolute()
#endif
    update_core(world);
    update_inner_core(world);
#ifdef zoxel_time_main_loop
    end_timing_cutoff(" - engine update lagged", zoxel_time_main_loop_cutoff)
#endif
}

void update_zox() {
#ifdef zoxel_on_web
    emscripten_set_main_loop(&update_zox_frame, -1, 1); // old - 60, 1);
#else
    signal(SIGINT, handle_terminal_close);     // Handles closing from control + c
    signal(SIGSEGV, handle_segfault);
    while (running) update_zox_frame();
#endif
}

void dispose_zox(ecs_world_t *world) {
    dispose_game_store();
    dispose_ecs(world); // everything will use flecs events to dispose
}
