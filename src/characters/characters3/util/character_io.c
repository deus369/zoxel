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

void load_character_e(ecs_world_t *world, const ecs_entity_t e) {
#ifdef zox_disable_save_games
    return;
#endif
    SaveDataCharacter save;
    load_player(game_name, "player.dat", &save);
    // zox_set(e, Position3D, { float3_add(save.position, (float3) { 0, 5, 0}) });
    zox_set(e, Position3D, { float3_add(save.position, (float3) { 0, 0.1f, 0}) });
    zox_set(e, Euler, { save.euler });
    zox_set(e, Rotation3D, { quaternion_from_euler(save.euler) });
    zox_set(e, DisableGravity, { 0 });
    zox_set(e, DisableMovement, { 0 });
    // zox_log("save.euler: %fx%fx%f", save.euler.x, save.euler.y, save.euler.z)
}