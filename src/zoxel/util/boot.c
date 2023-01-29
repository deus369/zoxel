extern unsigned char is_split_screen;

//! Spawns our first game entities.
void boot_zoxel_game(ecs_world_t *world)
{
    zoxel_log("Booting [Zoxel]\n");
    update();   // update once? so ui does its thing properly
    // spawn cameras first
    int2 screen_dimensions2 = screen_dimensions;
    if (is_split_screen)
    {
        screen_dimensions2.x /= 2;
        set_main_cameras(2);
    }
    float3 camera_begin_position = { 0, 0.0f, 0.0f };
    #ifdef zoxel_test_voxels_terrain
    #ifdef voxel_octrees
    camera_begin_position = (float3) { 0, 0.06f * overall_voxel_scale, 0 };
    #else
    camera_begin_position = (float3) { 0, 0.52f * 2 * overall_voxel_scale, 0 };
    #endif
    #endif
    main_cameras[0] = spawn_base_camera(world, camera_begin_position,
        quaternion_identity(), screen_dimensions2, (int2) { });
    if (is_split_screen)
    {
        //! \todo connect a gamepad to this camera
        camera_begin_position.z += 0.4f;
        main_cameras[1] = spawn_base_camera(world, camera_begin_position,
            quaternion_identity(), screen_dimensions2, (int2) { screen_dimensions2.x, 0 });
    }
    ecs_entity_t realm = spawn_realm(world);
    ecs_entity_t game = spawn_game(world);
    ecs_set(world, game, RealmLink, { realm });
    // fps_display = spawn_fps_display(world, main_canvas, 32);
    if (!headless)
    {
        // spawn devices
        spawn_connected_devices(world);
        // spawn_player_character3D(world, get_main_camera());
    }
    spawn_ui_camera(world, screen_dimensions2);
    spawn_font_style(world);
    spawn_canvas(world, screen_dimensions2);
    spawn_zoxel_main_menu(world);
    #ifdef zoxel_test_uis
    spawn_test_uis(world);   // spawns test ui
    #endif
    spawn_canvas_edge_lines(world, main_canvas);
    spawn_music(world);
}