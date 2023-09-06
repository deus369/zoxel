// todo: move this to engine code

extern void engine_update();

void engine_end() {
    zoxel_log(" > zoxel is exiting\n");
    running = 0;
    #ifdef zoxel_on_web    
        emscripten_cancel_main_loop();
    #endif
}

void handle_terminal_close(int sig) {
    zoxel_log(" > terminal close detected [control + c]\n");
    engine_end();
}

void engine_loop() {
    #ifdef zoxel_on_web
        emscripten_set_main_loop(&engine_update, -1, 1); // old - 60, 1);
    #else
        signal(SIGINT, handle_terminal_close);     // Handles closing from control + c
        while (running) engine_update();
    #endif
}