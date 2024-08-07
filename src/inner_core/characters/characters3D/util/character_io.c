typedef struct {
    float3 position;
    float3 euler;
    // float4 rotation;
} SavePlayer;
SavePlayer player_save;
load_and_save_data(SavePlayer, player)

void load_character_p(float3 *position, float4 *rotation) {
#ifdef zox_disable_save_games
    return;
#endif
    load_player(game_name, "player.dat", &player_save);
    *position = player_save.position;
    *rotation = quaternion_from_euler(player_save.euler);
}

void load_character_e(ecs_world_t *world, const ecs_entity_t character) {
#ifdef zox_disable_save_games
    return;
#endif
    load_player(game_name, "player.dat", &player_save);
    zox_set(character, Position3D, { float3_add(player_save.position, (float3) { 0, 0.01f, 0 }) })
    zox_set(character, Euler, { player_save.euler })
    zox_set(character, Rotation3D, { quaternion_from_euler(player_save.euler) })
    zox_set(character, Velocity3D, { float3_zero })
    zox_set(character, Acceleration3D, { float3_zero })
}

void save_character_e(ecs_world_t *world, const ecs_entity_t character) {
#ifdef zox_disable_save_games
    return;
#endif
    player_save.position = zox_get_value(character, Position3D)
    player_save.euler = zox_get_value(character, Euler)
    // player_save.rotation = zox_get_value(character, Rotation3D)
    save_player(game_name, "player.dat", &player_save);
}
