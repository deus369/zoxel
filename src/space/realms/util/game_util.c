// todo: make this an event i can latch onto in submodules

// player hooks
// extern void attach_to_character(ecs_world_t *world, ecs_entity_t player, ecs_entity_t camera, ecs_entity_t character);
// extern void detatch_from_character(ecs_world_t *world, ecs_entity_t player, ecs_entity_t camera, ecs_entity_t character);
// extern void button_event_pause_game(ecs_world_t *world, ecs_entity_t trigger_entity);
// extern ecs_entity_t local_character3D;
// do I still need render_camera_matrix? - yes - used to insert matrix in each camera system run
// extern const char *game_name;
// extern ecs_entity_t spawn_player_character2D(ecs_world_t *world, ecs_entity_t camera);

void realms_game_start(ecs_world_t *world, ecs_entity_t game) {
    set_sky_color(world, game_sky_color, game_sky_bottom_color);
    if (zox_game_type == zox_game_mode_3D) {
        int3 terrain_position = int3_zero;
        create_terrain(world, terrain_position);
        zox_set(local_terrain, RealmLink, { local_realm }) // this should be done on spawn
        // link terrain to realm too
    } else if (zox_game_type == zox_game_mode_2D) {
        zox_log(" > todo: create terrain2D and chunk2D modules\n")
    }
    unlock_achievement("test_achievement"); // idk if this can be per player
}

void realms_game_end(ecs_world_t *world, ecs_entity_t game) {
    if (zox_game_type == zox_game_mode_3D) {
        zox_delete_and_set(local_terrain)
    }
    set_sky_color(world, menu_sky_color, menu_sky_bottom_color);
}

void realms_game_state(ecs_world_t *world, ecs_entity_t game, unsigned char new_game_state) {
    unsigned char previous_game_state = zox_get_value(game, GameState)
    if (previous_game_state == zox_game_start && new_game_state == zox_game_playing) realms_game_start(world, game);
    else if (new_game_state == zox_game_start) realms_game_end(world, game);
}
