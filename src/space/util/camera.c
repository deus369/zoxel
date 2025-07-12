ecs_entity_t spawn_player_camera(ecs_world_t *world,
    const ecs_entity_t player,
    const byte index,
    const float3 camera_position,
    const float4 camera_rotation,
    const int2 viewport_position,
    const int2 viewport_size,
    const float4 screen_to_canvas)
{
    main_menu_rotation_speed = quaternion_from_euler( (float3) { 0, -main_camera_rotation_speed * degreesToRadians, 0 });
    float fov = get_camera_mode_fov(camera_mode);
    const ecs_entity_t e = spawn_camera_base(world, prefab_camera_game, camera_position, camera_rotation, fov, viewport_position, viewport_size, screen_to_canvas);
    zox_set(player, CameraLink, { e })
    // ui stuff
    initialize_camera_post_processing(world, e, viewport_size);
    const ecs_entity_t e2 = spawn_camera_ui(world, prefab_camera_ui, viewport_position, viewport_size);
    // global links (THESE BAD)
    main_cameras[index] = e;
    ui_cameras[index] = e2;
    return e;
}