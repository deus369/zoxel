void realms_start_game(ecs_world_t *world, const ecs_entity_t game) {
    if (zox_game_type == zox_game_mode_3D) {
        delay_event(world, &realms_start_game3D_delayed, game, 1.2f);
    } else if (zox_game_type == zox_game_mode_2D) {
        delay_event(world, &realms_start_game2D_delayed, game, 1.2f);
    }
    unlock_achievement("test_achievement"); // idk if this can be per player
}

void realms_game_end_delayed(ecs_world_t *world, const ecs_entity_t game) {
    set_sky_color(world, menu_sky_color, menu_sky_bottom_color);
    if (zox_game_type == zox_game_mode_3D) {
        zox_delete_and_set(local_terrain)
        destroy_terrain_grid(world);
    }
}

void realms_game_end(ecs_world_t *world, const ecs_entity_t game) {
    delay_event(world, &realms_game_end_delayed, game, 1.2f);
}

// state change goes to start and end functions
void realms_game_state(ecs_world_t *world, const ecs_entity_t game, const byte old_game_state, const byte new_game_state) {
    if (old_game_state == zox_game_start && new_game_state == zox_game_playing) {
        realms_start_game(world, game);
    } else if (new_game_state == zox_game_start) {
        realms_game_end(world, game);
    }
}