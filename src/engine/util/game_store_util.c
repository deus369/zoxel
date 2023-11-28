#ifdef zox_include_steam
    void intialize_game_store() {
        if (initialize_steam()) {
            authenticate_user();
            is_steam_running = 1;
        }
    }

    void dispose_game_store() {
        if (is_steam_running) {
            shutdown_steam();
        }
    }
#else
    void intialize_game_store() { zox_logg("  > no game store in build to initialize\n") }
    void dispose_game_store() { zox_logg("  > no game store in build to dispose\n") }
    unsigned char unlock_achievement(const char* achievement) {
        zox_log("   > unlocking achievement [%s]\n", achievement)
    }
#endif
