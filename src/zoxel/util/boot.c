
extern bool is_split_screen;

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
    main_cameras[0] = spawn_base_camera(world, (float3) { 0, 3.6f, 0.62f },
        quaternion_identity(), screen_dimensions2, (int2) { });
    if (is_split_screen)
    {
        //! \todo connect a gamepad to this camera
        main_cameras[1] = spawn_base_camera(world, (float3) { 0, 3.6f, 1.62f },
            quaternion_identity(), screen_dimensions2, (int2) { screen_dimensions2.x, 0 });
    }
    spawn_ui_camera(world, screen_dimensions2);
    // spawn devices
    spawn_connected_devices(world);
    // spawn font, canvas and ui
    spawn_font_style(world);
    spawn_canvas(world, screen_dimensions2);
    #ifdef zoxel_test_uis
    spawn_test_uis(world);   // spawns test ui
    #endif
    // spawn_player_character3D(world, get_main_camera());
    spawn_zoxel_main_menu(world);
    fps_display = spawn_fps_display(world, main_canvas, 32);
}