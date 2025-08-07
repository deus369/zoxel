#define main_camera_rotation_speed 60 * 0.22f
float4 main_menu_rotation_speed;

// spawns game camera and ui camera on top
entity2 spawn_player_camera(ecs *world,
    const entity player,
    const float3 camera_position,
    const float4 camera_rotation,
    const float4 screen_to_canvas,
    const int2 viewport_position,
    const int2 viewport_size,
    const int2 canvas_size)
{
    main_menu_rotation_speed = quaternion_from_euler( (float3) { 0, -main_camera_rotation_speed * degreesToRadians, 0 });
    float fov = get_camera_mode_fov(camera_mode);
    const entity e = spawn_camera_base(world,
        prefab_camera_game,
        camera_position,
        camera_rotation,
        fov,
        viewport_position,
        viewport_size,
        screen_to_canvas);
    zox_name("camera_game")
    zox_set(player, CameraLink, { e })
    const entity e2 = spawn_camera_ui(world,
        prefab_camera_ui,
        viewport_position,
        canvas_size,
        screen_to_canvas);
    zox_debug_spawn(world, e2, "camera_game_ui", "instance");
    return (entity2) { e, e2 };
}