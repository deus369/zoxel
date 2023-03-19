extern void main_update();

//! Quits the application from running indefinitely.
void exit_game() {
    running = 0;
    #ifdef WEB_BUILD
    emscripten_cancel_main_loop();
    #endif
}

void sigint_handler(int sig) {
    // Signal was SIGINT
    // zoxel_log("Zoxel Engine is closing from control + c.\n");
    exit_game();
}

void main_loop() {
    // Set up the signal handler for SIGINT
    signal(SIGINT, sigint_handler);
    #ifdef WEB_BUILD
        emscripten_set_main_loop(&main_update, -1, 1); // old - 60, 1);
    #else
        while (running)
        {
            main_update();
        }
    #endif
}