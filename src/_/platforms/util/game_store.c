// #define zox_log_achievements
#ifdef zox_include_steam
byte is_steam_running = 0;
// todo: move this to a steam module
#include "../../../../bash/steam/steamwrapper.c"

void intialize_game_store() {
    if (initialize_steam()) {
        authenticate_user();
        is_steam_running = 1;
        zox_log("> game store [steam]")
    } else {
        zox_log_error("! steam failed to initialize")
    }
}

void dispose_game_store() {
    if (is_steam_running) {
        is_steam_running = 0;
        shutdown_steam();
    }
}

void unlock_achievement(const char* achievement) {
    if (is_steam_running) {
        zox_logv(" > [steam] unlocking achievement [%s]", achievement)
        steam_unlock_achievement(achievement);
    }
}

#else

void intialize_game_store() { } //  zox_log(" > game store [none]")

void dispose_game_store() { }

void unlock_achievement(const char* achievement) {
    zox_logv(" > [none] unlocking achievement [%s]", achievement);
}

#endif

void on_boot_game_store(ecs_world_t* world, ecs_entity_t app) {
    (void)world;
    (void)app;
    intialize_game_store();
    // test_steam_cloud(); // idk
}