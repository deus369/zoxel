extern void engine_update();

void exit_app() {
    running = 0;
    #ifdef zoxel_on_web    
        emscripten_cancel_main_loop();
    #endif
}

void sigint_handler(int sig) {
    zoxel_log(" > zoxel engine is exiting [control + c]\n");
    exit_app();
}

void engine_loop() {
    #ifdef zoxel_on_web
        emscripten_set_main_loop(&engine_update, -1, 1); // old - 60, 1);
    #else
        signal(SIGINT, sigint_handler);     // Handles closing from control + c
        while (running) engine_update();
    #endif
}