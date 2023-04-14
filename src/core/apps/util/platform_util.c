void debug_platform() {
    if (is_steam_deck()) {
        zoxel_log(" > running on steamdeck\n");
    }
    #if defined(zoxel_on_android)
        zoxel_log(" > compiled for android\n");
    #elif defined(zoxel_on_windows)
        zoxel_log(" > compiled for windows\n");
    #elif defined(zoxel_on_web)
        zoxel_log(" > compiled for web\n");
    #elif defined(zoxel_on_linux)
        zoxel_log(" > compiled for linux\n");
    #endif
    #if defined(zoxel_on_steamdeck)
        zoxel_log(" > compiled for steamdeck\n");
    #endif
}