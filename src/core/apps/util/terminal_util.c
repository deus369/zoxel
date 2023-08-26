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
    zoxel_log("        -v --vulkan       enables vulkan\n");
    zoxel_log("        -f --fullscreen  fullscreen window\n");
    zoxel_log("        -g --halfscreen  halfscreen window\n");
    zoxel_log("        -s --splitscreen split screen local coop\n");
    zoxel_log("        -p --profiler       enable profiler\n");
    zoxel_log("        -x --server       enable server mode\n");
    zoxel_log("        -e --opengles       enables opengl es\n");
    zoxel_log("        -b --vsync       enable vsync\n");
    zoxel_log("\n");
    zoxel_log("-=-=-=-=-=--=-=-=-=-=--=-=-=-=-=--=-=-=-=-=-\n");
    zoxel_log("\n");
}

extern unsigned char zox_lowres_characters_mode;
extern unsigned char terrain_mode;
#define terrain_mode_tiny 1
#define terrain_mode_medium 2
#define terrain_mode_large 3

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
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--vsync") == 0) {
            vsync = 1;
        } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--profiler") == 0) {
            profiler = 1;
        } else if (strcmp(argv[i], "-z") == 0 || strcmp(argv[i], "--headless") == 0) {
            headless = 1;
        } else if (strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "--server") == 0) {
            server_mode = 1;
        } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--opengles") == 0) {
            override_opengl_es = 1;
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vulkan") == 0) {
            is_vulkan = 1;
        } else if (strcmp(argv[i], "--tiny") == 0) {
            terrain_mode = terrain_mode_tiny;
        } else if (strcmp(argv[i], "--medium") == 0) {
            terrain_mode = terrain_mode_medium;
        } else if (strcmp(argv[i], "--large") == 0) {
            terrain_mode = terrain_mode_large;
        } else if (strcmp(argv[i], "--lowrescharacters") == 0) {
            zox_lowres_characters_mode = 1;
        } else if (strcmp(argv[i], "--singlethread") == 0) {
            is_multithreading = 0;
        }
    }
    return EXIT_SUCCESS;
}