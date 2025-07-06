void player_start_game(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, main_menu)
    if (main_menu) {
        zox_delete(main_menu)
    }
    disable_inputs_until_release(world, player, zox_device_mode_none, 1);
    trigger_canvas_fade_transition(world, canvas, 0.7f, 6.0f);
    if (zox_game_type == zox_game_mode_3D) {
        delay_event(world, &player_start_game3D_delayed, player, 1.4f);
    } else if (zox_game_type == zox_game_mode_2D) {
        delay_event(world, &player_start_game2D_delayed, player, 1.4f);
    }
}

void player_end_game(ecs_world_t *world, const ecs_entity_t player, const byte is_delays) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuPaused, menu_paused)
    find_child_with_tag(canvas, Taskbar, taskbar)
    disable_inputs_until_release(world, player, zox_device_mode_none, 1);
    if (is_delays) {
        trigger_canvas_fade_transition(world, canvas, 0.5, end_game_delay_fade);
    }
    if (zox_gett_value(player, DeviceMode) == zox_device_mode_keyboardmouse) {
        if (zox_valid(mouse_entity)) {
            zox_set(mouse_entity, MouseLock, { 0 })
        }
    }
    // remove player uis
    if (zox_valid(menu_paused)) {
        zox_delete(menu_paused) // for second player
    }
    if (zox_valid(taskbar)) {
        zox_delete(taskbar)
    }
    if (zox_game_type == zox_game_mode_3D) {
        if (is_delays) {
            delay_event(world, &player_end_game3D, player, end_game_delay);
        } else {
            player_end_game3D(world, player);
        }
    } else if (zox_game_type == zox_game_mode_2D) {
        delay_event(world, &player_end_game2D, player, end_game_delay);
    }
}

// game state implementation for players module
void players_game_state(ecs_world_t *world, const ecs_entity_t game, const byte previous_game_state, const byte new_game_state) {
    // attach this onto realm or something
    if (previous_game_state == zox_game_start && new_game_state == zox_game_playing) {
        zox_geter(game, RealmLink, realmLink)
        zox_set(realmLink->value, GenerateRealm, { zox_generate_realm_start })
    }
    zox_geter(game, PlayerLinks, players)
    for (int i = 0; i < players->length; i++) {
        const ecs_entity_t player = players->value[i];
        if (previous_game_state == zox_game_start && new_game_state == zox_game_playing) {
            player_start_game(world, player);
        } else if (previous_game_state == zox_game_playing && new_game_state == zox_game_paused) {
            pause_player(world, player);
        } else if (previous_game_state == zox_game_paused && new_game_state == zox_game_playing) {
            resume_player(world, player);
        } else if (new_game_state == zox_game_start) {
            player_end_game(world, player, is_end_game_delays);
        }
    }
}