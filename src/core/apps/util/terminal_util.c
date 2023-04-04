

//! Zoxel can also be a command tool... Wuut?!?!!
void print_help_menu(const char* arg0) {
    zoxel_log("\n");
    zoxel_log("-=-=-=-=-=--=-=-=-=-=--=-=-=-=-=--=-=-=-=-=-\n");
    zoxel_log("\n");
    zoxel_log("Welcome to Zoxel Help Menu\n\n");
    zoxel_log("    Usage: %s [options]\n", arg0);
    zoxel_log("\n");
    zoxel_log("    Options:\n");
    zoxel_log("\n");
    zoxel_log("        -h --help        print this help\n");
    zoxel_log("        -z --headless       enable headless\n");
    zoxel_log("        -f --fullscreen  fullscreen window\n");
    zoxel_log("        -g --halfscreen  halfscreen window\n");
    zoxel_log("        -s --splitscreen split screen local coop\n");
    zoxel_log("        -v --vsync       enable vsync\n");
    zoxel_log("        -p --profiler       enable profiler\n");
    zoxel_log("        -x --server       enable server mode\n");
    zoxel_log("        -e --opengles       enables opengl es\n");
    zoxel_log("\n");
    zoxel_log("-=-=-=-=-=--=-=-=-=-=--=-=-=-=-=--=-=-=-=-=-\n");
    zoxel_log("\n");
}

//! Convert starting arguments to Settings.
int process_arguments(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help_menu(argv[0]);
            return EXIT_FAILURE;
        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fullscreen") == 0) {
            fullscreen = 1;
        } else if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--halfscreen") == 0) {
            halfscreen = 1;
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--splitscreen") == 0) {
            is_split_screen = 1;
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vsync") == 0) {
            vsync = 1;
        } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--profiler") == 0) {
            profiler = 1;
        } else if (strcmp(argv[i], "-z") == 0 || strcmp(argv[i], "--headless") == 0) {
            headless = 1;
        } else if (strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "--server") == 0) {
            server_mode = 1;
        } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--opengles") == 0) {
            override_opengl_es = 1;
        }
    }
    return EXIT_SUCCESS;
}