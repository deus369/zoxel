// todo: rewrite this test (aura now on skill not player character)
void key_down_test_aura(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_y) {
        const ecs_entity_t player = zox_players[0];
        if (!player) {
            zox_log("! player is null\n")
            return;
        }
        const ecs_entity_t character = zox_get_value(player, CharacterLink)
        if (!zox_valid(character)) {
            zox_log("! character is null\n")
            return;
        }
        if (zox_has(character, Aura)) {
            zox_remove_tag(character, Aura)
            zox_log(" > removed Aura from character\n")
        } else {
            zox_add_tag(character, Aura)
            zox_log(" > added Aura to character\n")
        }
    }
}