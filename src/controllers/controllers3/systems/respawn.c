extern ecs_entity_t game_start_player_new(ecs_world_t*, const ecs_entity_t);

void Player3RespawnSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_out(PlayerState)
    zox_sys_out(PlayerRespawn)
    zox_sys_out(CharacterLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_o(PlayerState, playerState)
        zox_sys_o(PlayerRespawn, playerRespawn)
        zox_sys_o(CharacterLink, characterLink)
        // what happened HHere...? NANI?
        if (playerRespawn->value > 0 && zox_valid(characterLink->value)) {
            zox_log("+++ Respawning Cancelled! (Character Lives) +++");
            playerRespawn->value = 0;
            playerState->value = zox_player_state_playing;
        }
        else if (playerRespawn->value > 0 && playerState->value != zox_player_state_respawning) {
            zox_log("+++ Respawning Cancelled! (PlayerState changed) +++");
            playerRespawn->value = 0;
        }
        // Playing happily!
        else if (playerState->value == zox_player_state_playing) {
            if (zox_valid(characterLink->value) && !zox_gett_value(characterLink->value, Dead)) {
                continue;
            }
            // start respawn timer!
            //  + active red overlay
            zox_log("+++ Respawning BEGINS +++")
            playerState->value = zox_player_state_respawning;
            playerRespawn->value = respawn_time;
        }
        // What happens after death??
        else if (playerState->value == zox_player_state_respawning) {
            playerRespawn->value -= zox_delta_time;
            if (playerRespawn->value <= 0) {
                zox_log("+++ Respawning Player +++")
                playerState->value = zox_player_state_playing;
                characterLink->value = game_start_player_new(world, e);
            }
        }
    }
} zoxd_system(Player3RespawnSystem)