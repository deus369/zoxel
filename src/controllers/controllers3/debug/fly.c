void toggle_flymode(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_f) {
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
        zox_geter_value(player, CharacterLink, entity, character);
        if (!zox_valid(character)) {
            return;
        }
        zox_geter_value_non_const(character, FlyMode, byte, flying);
        flying = !flying;
        zox_set(character, FlyMode, { flying });
        zox_set(character, DisableGravity, { flying });
        zox_log("Chacter FlyMode [%s]", flying ? "Enabled" : "Disabled");
    }
}