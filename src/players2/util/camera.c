ecs_entity_t spawn_player_camera(ecs_world_t *world, const ecs_entity_t player, const unsigned char index, const float3 camera_position, const float4 camera_rotation, const int2 viewport_position, const int2 viewport_size, const float4 screen_to_canvas) {
    main_menu_rotation_speed = quaternion_from_euler( (float3) { 0, -main_camera_rotation_speed * degreesToRadians, 0 });
    float fov = get_camera_mode_fov(camera_mode);
    const ecs_entity_t e = spawn_camera_base(world, prefab_camera_game, camera_position, camera_rotation, fov, viewport_position, viewport_size, screen_to_canvas);
    #ifdef zox_log_camera_spawning
    zox_log(" + spawned base camera\n")
    #endif
    zox_add_tag(e, Camera3D)
    const ecs_entity_t e2 = spawn_camera_ui(world, prefab_camera_ui, viewport_position, viewport_size);
    #ifdef zox_log_camera_spawning
    zox_log(" + spawned ui camera\n")
    #endif
    #ifdef zox_mod_animations
    // zox_set(e, EternalRotation, { main_menu_rotation_speed })
    #endif
    zox_set(player, CameraLink, { e })
    main_cameras[index] = e;
    ui_cameras[index] = e2;
    // adds a frame buffer object and render buffer to the camera
    #ifndef zox_disable_post_processing
        zox_add_tag(e, RenderCamera)
        #ifdef zox_log_camera_spawning
            zox_log(" + spawnubg frame buffer object\n")
        #endif
        GLuint fbo = spawn_frame_buffer_object(world, e); // test fbo
        if (fbo) {
            GLuint render_buffer = spawn_render_buffer(world, e, viewport_size); // test fbo
            if (render_buffer) {
                connect_render_buffer_to_fbo(fbo, render_buffer);
            }
        }
    #endif
    return e;
}
