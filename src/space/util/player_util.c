void add_player(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player) {
    PlayerLinks *playerLinks = zox_get_mut(e, PlayerLinks)
    byte new_length = playerLinks->length + 1;
    resize_memory_component(PlayerLinks, playerLinks, ecs_entity_t, new_length)
    playerLinks->value[new_length - 1] = player;
    zox_modified(e, PlayerLinks)
    zox_set(player, GameLink, { e })
}

// game state implementation for players module
void players_game_state(ecs_world_t *world, const ecs_entity_t game, const byte previous_game_state, const byte new_game_state) {
    const PlayerLinks *playerLinks = zox_get(game, PlayerLinks)
    for (int i = 0; i < playerLinks->length; i++) {
        const ecs_entity_t player = playerLinks->value[i];
        if (previous_game_state == zox_game_start && new_game_state == zox_game_playing) player_start_game(world, player);
        else if (previous_game_state == zox_game_playing && new_game_state == zox_game_paused) pause_player(world, player);
        else if (previous_game_state == zox_game_paused && new_game_state == zox_game_playing) resume_player(world, player);
        else if (new_game_state == zox_game_start) player_end_game(world, player);
    }
}

int spawn_players(ecs_world_t *world, const ecs_entity_t game) {
    int players = 0;
    if (headless) return players;   // no players in headless mode
    spawn_connected_devices(world);
    if (is_split_screen) {
        players = 2;
        auto_switch_device = 0;
    }
    else {
        players = 1;
    }
    for (int i = 0; i < players; i++) {
        const ecs_entity_t e = spawn_player(world, prefab_player);
        add_player(world, game, e);
        zox_set(e, CameraLink, { main_cameras[i] })
        zox_players[i] = e;
        if (players == 2) {
            if (i == 0) zox_set(e, DeviceModeDirty, { zox_device_mode_keyboardmouse })
            else if (i == 1) zox_set(e, DeviceModeDirty, { zox_device_mode_gamepad })
        }
    }
    return players;
}
