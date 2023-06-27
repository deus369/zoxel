unsigned char is_steam_deck() {
    if (getenv("STEAMOS_SESSIONTYPE") != NULL && strcmp(getenv("STEAMOS_SESSIONTYPE"), "steam") == 0) {
        return 1;
    } else {
        return 0;
    }
}

void debug_platform() {
    #if defined(zoxel_on_android)
        zoxel_log(" > platform [android]\n");
    #elif defined(zoxel_on_windows)
        zoxel_log(" > platform [windows]\n");
    #elif defined(zoxel_on_web)
        zoxel_log(" > platform [web]\n");
    #elif defined(zoxel_on_linux)
        zoxel_log(" > platform [linux]\n");
    #endif
    #if defined(zoxel_on_steamdeck)
        zoxel_log(" > platform [steamdeck]\n");
    #endif
    if (is_steam_deck()) {
        zoxel_log(" > platform [steamdeck] (check 2)\n");
    }
}