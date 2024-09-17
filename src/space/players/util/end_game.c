void player_end_game3D_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (character) detatch_camera_from_character(world, player, camera, character, 0);
    zox_set(player, CharacterLink, { 0 })
    float3 camera_position = float3_zero;
    float4 camera_rotation = quaternion_identity;
    set_camera_transform_to_main_menu(&camera_position, &camera_rotation);
    zox_set(camera, Position3D, { camera_position })
    zox_set(camera, Rotation3D, { camera_rotation })
    zox_set(camera, Euler, { float3_zero })
    zox_set(camera, CharacterLink, { 0 })
    spawn_main_menu(world, player, canvas, game_name, int2_zero, float2_half);
}

void player_end_game2D_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    zox_delete(world_grid2D)
    zox_delete(character)
    zox_set(player, CharacterLink, { 0 })
    zox_set(camera, CharacterLink, { 0 })
    spawn_main_menu(world, player, canvas, game_name, int2_zero, float2_half);
}

void player_end_game(ecs_world_t *world, const ecs_entity_t player) {
    disable_inputs_until_release(world, player, zox_device_mode_none, 1);
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)

    find_child_with_tag(canvas, MenuPaused, menu_paused)
    if (menu_paused) zox_delete(menu_paused) // for second player
    find_child_with_tag(canvas, Taskbar, taskbar)
    if (taskbar) zox_delete(taskbar)

    find_child_with_tag(canvas, MenuStatus, menu_status)
    if (menu_status) zox_delete(menu_status)
    find_child_with_tag(canvas, MenuItems, menu_items)
    if (menu_items) zox_delete(menu_items)
    find_child_with_tag(canvas, MenuStats, menu_stats)
    if (menu_stats) zox_delete(menu_stats)
    find_child_with_tag(canvas, MenuSkills, menu_skills)
    if (menu_skills) zox_delete(menu_skills)
    find_child_with_tag(canvas, MenuQuests, menu_quests)
    if (menu_quests) zox_delete(menu_quests)
    find_child_with_tag(canvas, MenuActions, menu_actions)
    if (menu_actions) zox_delete(menu_actions)

    dispose_menu_game(world, player);
    trigger_canvas_fade_transition(world, canvas, 0.5, 1.0);

    if (zox_game_type == zox_game_mode_3D) {
        delay_event(world, &player_end_game3D_delayed, player, 1.2f);
    } else if (zox_game_type == zox_game_mode_2D) {
        delay_event(world, &player_end_game2D_delayed, player, 1.2f);
    }
}
