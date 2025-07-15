extern void engine_end();

void print_help_menu(const char* arg0) {
    zox_log("\n");
    zox_log("-=-=-=-=-=--=-=-=-=-=--=-=-=-=-=--=-=-=-=-=-\n");
    zox_log("\n");
    zox_log("Welcome to Zoxel Help Menu\n\n");
    zox_log("    Usage: %s [options]\n", arg0);
    zox_log("\n");
    zox_log("    Options:\n");
    zox_log("\n");
    zox_log("        -h --help            print this help\n");
    zox_log("        -z --headless        enable headless\n");
    zox_log("        -v --vulkan          enables vulkan\n");
    zox_log("        -w --windowed        windowed mode\n");
    zox_log("        -f --fullscreen      fullscreen window\n");
    zox_log("        -g --halfscreen      halfscreen window\n");
    zox_log("        -s --splitscreen     split screen local coop\n");
    zox_log("        -p --profiler        enable profiler\n");
    zox_log("        -x --server          enable server mode\n");
    zox_log("        -e --opengles        enables opengl es\n");
    zox_log("        -b --vsync           enable vsync\n");
    zox_log("        --singlethread       run with only one thread\n");
    zox_log("\n");
    zox_log("    Extras:\n");
    zox_log("\n");
    zox_log("        --freeroam           freeroam camera on game start\n");
    zox_log("        --tiny               set game terrain size to 2\n");
    zox_log("        --medium             set game terrain size to 6\n");
    zox_log("        --large              set game terrain size to 12\n");
    zox_log("\n");
    zox_log("-=-=-=-=-=--=-=-=-=-=--=-=-=-=-=--=-=-=-=-=-\n");
    zox_log("\n");
    engine_end();
}

void process_arguments_help(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "-h") == 0 || strcmp(args[i], "--help") == 0) {
            print_help_menu(args[0]);
        }
    }
}