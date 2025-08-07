void test_game_end(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_g) {
        zox_log("> game toggling")
        if (!zox_valid(local_realm) || !zox_has(local_realm, GameLink)) {
            zox_log_error("no realm (local)")
            return;
        }
        zox_geter(local_realm, GameLink, gameLink)
        if (zox_valid(gameLink->value)) {
            zox_geter(gameLink->value, GameState, gameState)
            if (gameState->value == zox_game_start) {
                zox_log("+ game starting %i", gameState->value)
                zox_set(gameLink->value, GameStateTarget, { zox_game_load })
            } else if (gameState->value == zox_game_playing || gameState->value == zox_game_paused) {
                zox_log("- game ending: %i", gameState->value)
                zox_set(gameLink->value, GameStateTarget, { zox_game_start })
            }
        }
    }
}