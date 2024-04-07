void player_end_game(ecs_world_t *world, ecs_entity_t player) {
    dispose_in_game_ui(world, player);
    zox_delete_and_set(pause_ui)
    // spawn/delete on that players canvas
    const float2 main_menu_anchor = float2_half; // { 0.5f, 0.5f };
    const int2 main_menu_position = int2_zero;
    spawn_main_menu(world, game_name, main_menu_position, main_menu_anchor);
    // pause inputs
    disable_inputs_until_release(world, player, zox_device_mode_none);
    // todo: get player linked main camera
    ecs_entity_t main_camera = main_cameras[0]; // get player camera link instead
    ecs_entity_t character = 0;
    if (camera_follow_mode == zox_camera_follow_mode_attach) character = zox_get_value(main_camera, ParentLink)
    else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) character = zox_get_value(main_camera, CameraFollowLink)
    if (character) detatch_from_character(world, player, main_camera, local_character3D);
    float3 camera_position = float3_zero;
    float4 camera_rotation = quaternion_identity;
    get_camera_start_transform(&camera_position, &camera_rotation);
    zox_set(main_camera, Position3D, { camera_position })
    zox_set(main_camera, Rotation3D, { camera_rotation })
    local_character3D = 0;
}
