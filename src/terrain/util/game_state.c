// Start Game
void game_start_terrain(ecs_world_t *world, const ecs_entity_t game) {
    if (zox_game_type == zox_game_mode_3D) {
        delay_event(world, &game_start_terrain3D, game, start_game_delay);
    } else if (zox_game_type == zox_game_mode_2D) {
        delay_event(world, &game_start_terrain2D, game, start_game_delay);
    }
    unlock_achievement("test_achievement"); // idk if this can be per player
}

// Entry Point
// state change goes to start and end functions
void game_state_terrain(ecs_world_t *world, const ecs_entity_t game, const byte old_game_state, const byte new_game_state) {
    if (old_game_state == zox_game_start && new_game_state == zox_game_playing) {
        game_start_terrain(world, game);
    } else if (new_game_state == zox_game_start) {
        if (is_end_game_delays) {
            delay_event(world, &game_end_terrain, game, end_game_delay2);
        } else {
            game_end_terrain(world, game);
        }
    }
}