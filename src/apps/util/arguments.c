
void process_arguments_apps(ecs_world_t *world, char* args[], int count) {
    (void) world;
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "-z") == 0 || strcmp(args[i], "--headless") == 0) {
            headless = 1;
        } else if (strcmp(args[i], "-w") == 0 || strcmp(args[i], "--windowed") == 0) {
            fullscreen = 0;
        } else if (strcmp(args[i], "-f") == 0 || strcmp(args[i], "--fullscreen") == 0) {
            fullscreen = 1;
        } else if (strcmp(args[i], "-g") == 0 || strcmp(args[i], "--halfscreen") == 0) {
            halfscreen = 1;
        } else if (strcmp(args[i], "-s") == 0 || strcmp(args[i], "--splitscreen") == 0) {
            is_split_screen = 1;
        } else if (strcmp(args[i], "-b") == 0 || strcmp(args[i], "--vsync") == 0) {
            vsync = 1;
        }
    }
}