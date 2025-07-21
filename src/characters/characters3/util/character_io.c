void load_character_p(float3 *position, float3 *euler, float4 *rotation) {
#ifdef zox_disable_save_games
    return;
#endif
    SaveDataCharacter save;
    load_player(game_name, "player.dat", &save);
    *position = save.position;
    *euler = save.euler;
    *rotation = quaternion_from_euler(save.euler);
}

void load_character_e(ecs_world_t *world, const ecs_entity_t character) {
#ifdef zox_disable_save_games
    return;
#endif
    SaveDataCharacter save;
    load_player(game_name, "player.dat", &save);
    zox_set(character, Position3D, { save.position })
    zox_set(character, Euler, { save.euler })
    zox_set(character, Rotation3D, { quaternion_from_euler(save.euler) })
    // zox_log("save.euler: %fx%fx%f", save.euler.x, save.euler.y, save.euler.z)
}