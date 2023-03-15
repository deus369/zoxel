extern unsigned char is_split_screen;
extern ecs_entity_t fps_display;

//! Spawns our first game entities.
void boot_zoxel_game(ecs_world_t *world) {
    zoxel_log(" > booting [zoxel]\n");
    // spawn cameras first
    int2 screen_dimensions2 = screen_dimensions;
    if (is_split_screen) {
        screen_dimensions2.x /= 2;
        set_main_cameras(2);
    }
    float3 camera_begin_position = { 0, 0.0f, 0.0f };
    #ifdef voxels_spawn_terrain
        #ifdef voxel_octrees
            camera_begin_position = (float3) { 0, 0.26f * 2 * overall_voxel_scale, 0 };
        #else
            camera_begin_position = (float3) { 0, 0.52f * 2 * overall_voxel_scale, 0 };
        #endif
    #endif
    main_cameras[0] = spawn_base_camera(world, camera_begin_position,
        quaternion_identity(), screen_dimensions2, (int2) { });
    float4 rotationer = quaternion_from_euler( (float3) { 0, -0.12f * degreesToRadians, 0 });
    zoxel_set(world, main_cameras[0] , EternalRotation, { rotationer });
    if (is_split_screen) {
        //! \todo connect a gamepad to this camera
        camera_begin_position.z += 0.4f;
        main_cameras[1] = spawn_base_camera(world, camera_begin_position,
            quaternion_identity(), screen_dimensions2, (int2) { screen_dimensions2.x, 0 });
    }
    ecs_entity_t realm = spawn_realm(world);
    ecs_entity_t game = spawn_game(world);
    ecs_set(world, game, RealmLink, { realm });
    if (!headless) {
        spawn_connected_devices(world);
        // spawn_player_character3D(world, get_main_camera());
    }
    spawn_ui_camera(world, screen_dimensions2);
    spawn_canvas(world, screen_dimensions2);
    spawn_canvas_edge_lines(world, main_canvas);
    spawn_font_style(world);
    spawn_zoxel_main_menu(world);
    fps_display = spawn_fps_display(world, main_canvas, 32);
    // quads_label = spawn_quad_count_label(world, main_canvas, 32);
    #ifdef voxels_spawn_terrain
        create_terrain(world);
    #endif
    spawn_music(world, instrument_piano);
    zoxel_log(" > success booting [zoxel]\n");
}