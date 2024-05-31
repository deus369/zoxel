void player_end_game3D_delayed(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (character) detatch_from_character(world, player, camera, character, 0);
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
    disable_inputs_until_release(world, player, zox_device_mode_none);
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)

    find_child_with_tag(canvas, MenuPaused, menu_paused)
    if (menu_paused) zox_delete(menu_paused) // for second player

    find_child_with_tag(canvas, InventoryMenu, inventory_menu)
    if (inventory_menu) zox_delete(inventory_menu)

    dispose_in_game_ui(world, player);

    trigger_canvas_fade_transition(world, canvas);

    if (zox_game_type == zox_game_mode_3D) {
        delay_event(world, &player_end_game3D_delayed, player, 1.2f);
    } else if (zox_game_type == zox_game_mode_2D) {
        delay_event(world, &player_end_game2D_delayed, player, 1.2f);
    }
}
