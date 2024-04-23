void player_end_game(ecs_world_t *world, ecs_entity_t player) {
    ecs_entity_t canvas = main_canvas;
    dispose_in_game_ui(world, player);
    zox_delete_and_set(pause_ui)
    const float2 main_menu_anchor = float2_half;
    const int2 main_menu_position = int2_zero;
    spawn_main_menu(world, canvas, game_name, main_menu_position, main_menu_anchor);
    // pause inputs
    disable_inputs_until_release(world, player, zox_device_mode_none);
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    ecs_entity_t character = 0;
    if (camera_follow_mode == zox_camera_follow_mode_attach) character = zox_get_value(camera, ParentLink)
    else if (camera_follow_mode == zox_camera_follow_mode_follow_xz) character = zox_get_value(camera, CameraFollowLink)
    if (character) detatch_from_character(world, player, camera, local_character3D);
    float3 camera_position = float3_zero;
    float4 camera_rotation = quaternion_identity;
    get_camera_start_transform(&camera_position, &camera_rotation);
    zox_set(camera, Position3D, { camera_position })
    zox_set(camera, Rotation3D, { camera_rotation })
    local_character3D = 0;
}
