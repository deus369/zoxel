// #define zox_log_achievements
#ifdef zox_include_steam
unsigned char is_steam_running = 0;
#include "../../../../bash/steam/steamwrapper.c"

void intialize_game_store() {
    if (initialize_steam()) {
        authenticate_user();
        is_steam_running = 1;
        zox_log(" > game store [steam]\n")
    } else zox_log(" ! steam failed to initialize\n")
}

void dispose_game_store() {
    if (is_steam_running) {
        is_steam_running = 0;
        shutdown_steam();
    }
}

void unlock_achievement(const char* achievement) {
    if (is_steam_running) {
#ifdef zox_log_achievements
        zox_log(" > [steam] unlocking achievement [%s]\n", achievement)
#endif
        steam_unlock_achievement(achievement);
    } else {
        zox_log(" > [steam] cannot unlock achievement [%s]\n", achievement)
    }
}

#else

void intialize_game_store() { zox_log(" > game store [none]\n") }
void dispose_game_store() { }
void unlock_achievement(const char* achievement) {
#ifdef zox_log_achievements
    zox_log(" > [none] unlocking achievement [%s]\n", achievement)
#endif
}

#endif
