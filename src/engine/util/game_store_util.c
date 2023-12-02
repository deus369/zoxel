#ifdef zox_include_steam
unsigned char is_steam_running = 0;
#include "../../../bash/steam/steamwrapper.c"

void intialize_game_store() {
    if (initialize_steam()) {
        authenticate_user();
        is_steam_running = 1;
        zox_logg(" > game store [steam]\n")
    } else zox_logg(" ! steam failed to initialize\n")
}

void dispose_game_store() {
    if (is_steam_running) {
        is_steam_running = 0;
        shutdown_steam();
    }
}

void unlock_achievement(const char* achievement) {
    if (is_steam_running) {
        zox_log("   > unlocking achievement [%s]\n", achievement)
        steam_unlock_achievement(achievement);
    } else {
        zox_log("   > [steam] cannot unlock achievement [%s]\n", achievement)
    }
}

#else

void intialize_game_store() { zox_logg(" > game store [none]\n") }
void dispose_game_store() { }
void unlock_achievement(const char* achievement) {
    zox_log("   > unlocking achievement [%s]\n", achievement)
}

#endif
