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
    zox_log(" > terminal close detected [control + c]\n")
    engine_end();
}

// handles loop with special check on web builds
void engine_loop() {
#ifdef zoxel_on_web
    emscripten_set_main_loop(&update_ecs, -1, 1); // old - 60, 1);
#else
    signal(SIGINT, handle_terminal_close);     // Handles closing from control + c
    signal(SIGSEGV, handle_segfault);
    while (running) {
        update_ecs();
    }
#endif
}

void dispose_zox(ecs_world_t *world) {
    dispose_game_store();
    dispose_ecs(world); // everything will use flecs events to dispose
}
