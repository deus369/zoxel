void toggle_player_death(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_j) {
        zox_log("> player character death toggling")
        if (!zox_valid(local_realm) || !zox_has(local_realm, GameLink)) {
            zox_log_error("no realm (local)")
            return;
        }
        zox_geter(local_realm, GameLink, gameLink)
        if (!zox_valid(gameLink->value)) {
            zox_log_error("realm has no game")
            return;
        }
        zox_geter(gameLink->value, PlayerLinks, players)
        const ecs_entity_t player = players->value[0];
        zox_geter(player, CharacterLink, characterLink)
        if (zox_valid(characterLink->value)) {
            zox_log("- killing player character")
            zox_delete(characterLink->value)
        } else {
            zox_log("+ spawning player character")
            game_start_player_new(world, player);
        }
    }
}