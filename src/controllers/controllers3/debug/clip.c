void test_fall_through_terrain(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_f) {
        zox_log("> test_fall_through_terrain")
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
            zox_log("- falling player character")
            zox_muter(characterLink->value, Position3D, position3D)
            position3D->value.y -= 1.0f;
        }
    }
}