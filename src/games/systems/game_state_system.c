// when state changes, we can do events here
//      game has children which includes all players
//      game_state_start > game_state_menu = load main menu for player 1
//      game_state_menu > pre play = unload main menu, load a countdown / load ui
//      game_state_pre_play > play = load game, load player characters
//      game_state_play > game_state_paused = pause entities in game
//      game_state_paused > game_state_play = unpause entities
//      game_state_play | game_state_paused > game_state_end = go to exit ui
//      game_state_end > game_state_menu = return to main menu scene + ui

void GameStateSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(RealmLink, realmLinks, 1)
    zox_field_in(GameStateTarget, gameStateTargets, 2)
    zox_field_out(GameState, gameStates, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RealmLink, realmLinks, realmLink)
        if (!realmLink->value || zox_gett_value(realmLink->value, GenerateRealm)) {
            continue;
        }
        zox_field_i(GameStateTarget, gameStateTargets, gameStateTarget)
        zox_field_o(GameState, gameStates, gameState)
        if (gameStateTarget->value == gameState->value) {
            continue;
        }
        zox_field_e()
        byte old_state = gameState->value;
        byte new_state = gameStateTarget->value;
        gameState->value = new_state;
        trigger_event_game(world, e, old_state, gameStateTarget->value);
    }
} zox_declare_system(GameStateSystem)