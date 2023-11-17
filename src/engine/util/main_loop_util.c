extern void engine_update();

void engine_end() {
    running = 0;
#ifdef zoxel_on_web
    emscripten_cancel_main_loop();
#endif
}

void handle_segfault(int sig) {
    zox_log(" ! segfault detected [%i], exiting zox engine\n", sig)
    // on_engine_end(world);
    exit(0);
}

void handle_terminal_close(int sig) {
    zox_logg(" > terminal close detected [control + c]\n")
    engine_end();
}

void engine_loop() {
#ifdef zoxel_on_web
    emscripten_set_main_loop(&engine_update, -1, 1); // old - 60, 1);
#else
    signal(SIGINT, handle_terminal_close);     // Handles closing from control + c
    signal(SIGSEGV, handle_segfault);
    while (running) engine_update();
#endif
}
