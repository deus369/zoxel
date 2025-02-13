#include "menu_main.c"
#include "menu_options.c"
#include "menu_paused.c"
#include "game_loading.c"

void toggle_pause_ui(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const byte game_state = zox_get_value(game, GameState)
    if (!(game_state == zox_game_playing || game_state == zox_game_paused)) return;
    byte is_paused = game_state == zox_game_paused;
    if (!is_paused) set_game_state_target(world, game, zox_game_paused);
    else set_game_state_target(world, game, zox_game_playing);
}

// from touch_ui
void button_event_pause_game(ecs_world_t *world, const ClickEventData *event) {
    toggle_pause_ui(world, event->clicker);
}