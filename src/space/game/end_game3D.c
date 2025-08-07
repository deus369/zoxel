void player_end_game3(
    ecs *world,
    const ecs_entity_t player
) {
    zox_geter_value(player, GameLink, ecs_entity_t, game);
    zox_geter_value(game, RealmLink, ecs_entity_t, realm);
    zox_geter_value(player, CanvasLink, ecs_entity_t, canvas);
    zox_geter_value(player, CameraLink, ecs_entity_t, camera);
    float3 camera_position = float3_zero;
    float4 camera_rotation = quaternion_identity;
    set_camera_transform_to_main_menu(&camera_position, &camera_rotation, terrain_depth);
    zox_set(camera, Position3D, { camera_position })
    zox_set(camera, Rotation3D, { camera_rotation })
    zox_set(camera, Euler, { float3_zero })
    zox_set(player, CharacterLink, { 0 })
    zox_set(camera, CharacterLink, { 0 })
    // music - attach to game from music module
    play_playlist(world, realm, 0);
    // spawn main menu here
    spawn_main_menu(world, player, canvas, game_name);
    zox_geter_value(player, CharacterLink, ecs_entity_t, character)
    if (zox_valid(character)) {
        zox_log_error("Character still alive at end of game.")
        zox_delete(character)
    }
}