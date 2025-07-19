void GameStateSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(RealmLink)
    zox_sys_in(GameStateTarget)
    zox_sys_out(GameState)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(RealmLink, realmLink)
        zox_sys_i(GameStateTarget, gameStateTarget)
        zox_sys_o(GameState, gameState)
        if (gameStateTarget->value == gameState->value || !zox_valid(realmLink->value)) {
            continue;
        }
        if (gameStateTarget->value == zox_game_load) {
            gameState->value = gameStateTarget->value;
            zox_set(e, GameStateTarget, { zox_game_loading })
            zox_set(realmLink->value, GenerateRealm, { zox_generate_realm_start })
            // zox_log("loading realm at [%f]", zox_current_time)
        } else if (gameStateTarget->value == zox_game_loading) {
            if (!zox_gett_value(realmLink->value, GenerateRealm)) {
                gameState->value = gameStateTarget->value;
                zox_set(e, GameStateTarget, { zox_game_playing })
                // zox_log("finished loading realm at [%f]", zox_current_time)
            }
        } else {
            byte old_state = gameState->value;
            byte new_state = gameStateTarget->value;
            gameState->value = new_state;
            trigger_event_game(world, e, old_state, gameStateTarget->value);
        }
    }
} zox_declare_system(GameStateSystem)

// when state changes, we can do events here
//      game has children which includes all players
//      game_state_start > game_state_menu = load main menu for player 1
//      game_state_menu > pre play = unload main menu, load a countdown / load ui
//      game_state_pre_play > play = load game, load player characters
//      game_state_play > game_state_paused = pause entities in game
//      game_state_paused > game_state_play = unpause entities
//      game_state_play | game_state_paused > game_state_end = go to exit ui
//      game_state_end > game_state_menu = return to main menu scene + ui