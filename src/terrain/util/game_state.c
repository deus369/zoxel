// Entry Point
// state change goes to start and end functions
void game_state_terrain(ecs_world_t *world, const ecs_entity_t game, const byte old_game_state, const byte new_game_state) {
    if (old_game_state == zox_game_loading && new_game_state == zox_game_playing) {
        game_start_terrain(world, game, is_start_game_delays);
    } else if (new_game_state == zox_game_start) {
        if (is_end_game_delays) {
            delay_event(world, &game_end_terrain, game, end_game_delay2);
        } else {
            game_end_terrain(world, game);
        }
    }
}