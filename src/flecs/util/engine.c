void engine_end() {
    running = 0;
#ifdef zoxel_on_web
    emscripten_cancel_main_loop();
#endif
}

void handle_segfault(int sig) {
    zox_log_error("segfault detected [%i], exiting..", sig)
    exit(0);
}

void handle_terminal_close(int sig) {
    zox_log("...")
    zox_log("# SOOooo you wanna deffffyyy my orders? heh..")
    zox_log("*ominous noises*")
    engine_end();
}

// handles loop with special check on web builds
void engine_loop(ecs_world_t *world) {
#ifdef zoxel_on_web
    emscripten_set_main_loop(&update_ecs_local, -1, 1); // old - 60, 1);
#else
    signal(SIGINT, handle_terminal_close);     // Handles closing from control + c
    signal(SIGSEGV, handle_segfault);
    while (running) {
        update_ecs(world);
    }
#endif
}

void dispose_zox(ecs_world_t *world) {
    dispose_update_loop();
    dispose_post_update_loop();
    ecs_fini(world);
}