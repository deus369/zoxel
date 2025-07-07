void player_end_game3D(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const ecs_entity_t realm = zox_get_value(game, RealmLink)
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
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
    spawn_main_menu(world, player, canvas, game_name, int2_zero, float2_half);
}