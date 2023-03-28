extern void engine_update();

//! Quits the application from running indefinitely.
void exit_game() {
    running = 0;
    #ifdef WEB_BUILD    
    emscripten_cancel_main_loop();
    #endif
}

void sigint_handler(int sig) {
    zoxel_log(" > zoxel engine is exiting [control + c]\n");
    exit_game();
}

void engine_loop() {
    #ifdef WEB_BUILD
        emscripten_set_main_loop(&engine_update, -1, 1); // old - 60, 1);
    #else
        signal(SIGINT, sigint_handler);     // Handles closing from control + c
        while (running)
        {
            engine_update();
        }
    #endif
}