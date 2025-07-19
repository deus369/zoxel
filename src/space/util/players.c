void add_player(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player) {
    zox_get_muter(e, PlayerLinks, players)
    byte new_length = players->length + 1;
    resize_memory_component(PlayerLinks, players, ecs_entity_t, new_length)
    players->value[new_length - 1] = player;
    zox_set(player, GameLink, { e })
}

int spawn_players(ecs_world_t *world, const ecs_entity_t game) {
    int players = 0;
    if (headless) {
        return players;   // no players in headless mode
    }
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
            if (i == 0) {
                zox_set(e, DeviceModeDirty, { zox_device_mode_keyboardmouse })
            } else if (i == 1) {
                zox_set(e, DeviceModeDirty, { zox_device_mode_gamepad })
            }
        }
    }
    return players;
}