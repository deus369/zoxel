void player_end_game_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (character) detatch_from_character(world, player, camera, character, 0);
    zox_set(player, CharacterLink, { 0 })
    float3 camera_position = float3_zero;
    float4 camera_rotation = quaternion_identity;
    set_camera_start_transform(&camera_position, &camera_rotation);
    zox_set(camera, Position3D, { camera_position })
    zox_set(camera, Rotation3D, { camera_rotation })
    zox_set(camera, Euler, { float3_zero })
    zox_set(camera, CharacterLink, { 0 })
    const float2 main_menu_anchor = float2_half;
    const int2 main_menu_position = int2_zero;
    spawn_main_menu(world, player, canvas, game_name, main_menu_position, main_menu_anchor);
}

void player_end_game(ecs_world_t *world, const ecs_entity_t player) {
    disable_inputs_until_release(world, player, zox_device_mode_none);
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuPaused, menu_paused)
    if (menu_paused) zox_delete(menu_paused) // for second player
    dispose_in_game_ui(world, player);
    trigger_canvas_fade_transition(world, canvas);
    delay_event(world, &player_end_game_delayed, player, 1.2f);
}
